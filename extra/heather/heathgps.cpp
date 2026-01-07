#define EXTERN extern
#include "heather.ch"
//
// Thunderbolt TSIP monitor
//
// Copyright (C) 2008,2009 Mark S. Sims - all rights reserved
// Win32 port by John Miles, KE5FX (jmiles@pop.net)
// 
// This file contains the TSIP message parser and GPS receiver control code
// It also displays the basic GPS data
//


#define SIG_THRESHOLD 40.0

extern char *months[];
extern char *dst_list[];
extern double cos_factor;

u16 early_end;        // flag set if tsip message ended early
int last_msg;         // the previous TSIP message type

int rolled;           // flag set if rollover compensation is in use
unsigned int leap_days; // days until leap second

u08 have_rcvr_mode;   // flag set if we have the receiver operating mode
u08 last_rcvr_mode;   // the previous receiver operating mode
unsigned long wakeup_tsip_msg;  // flag set if any tsip message has been received

u08 saw_kalman_on;    // flag set if the dynamics Kalman filter is ever on
u08 saw_version;      // flag set if version message seen

u08 try_nortel;       // if flag set, try nortel format osc messages
u08 waking;           // flag set if in wakeup mode
u08 luxor_time_set;   // flag set if luxor time message has been sent
#define LUXOR_ID 0xDC // luxor TSIP packets start with this code


char *level_type = "   ";  // AMU or dB
int last_survey;

int first_request = 1;

void secondary_timing();

//
//
//   Trimble TSIP protocol handling stuff
//
//


void debug_stream(unsigned c)
{
   ++kol;
// if(log_comments && (c >= ' ') && (c <= 0x7F)) fprintf(log_file, "(%c)", c);
   if(last_was_dle) {
      if(c == DLE) {
         if(kol >= 16) {
            if(log_comments) fprintf(log_file, "\n      ");
            kol = (-1);
         }
         if(log_comments) fprintf(log_file, "%02X:%02X ", c,c);
      }
      else if(c == ETX) {
         if(log_comments) fprintf(log_file, "%02X:%02X ", DLE,(unsigned) (c&0xFF));
      }
      else {
         if(log_comments) {
            fprintf(log_file, "\n%02X:%02X", DLE,(unsigned) (c&0xFF));
            if(c == 0x8F) fprintf(log_file, "-");
            else          fprintf(log_file, " ");
         }
         kol = (-1);
      }
      last_was_dle = 0;
   }
   else if(c == DLE) last_was_dle = 1;
   else {
      if(kol >= 16) {
         if(log_comments) fprintf(log_file, "\n      ");
         kol = 0;
      }
      if(log_comments) fprintf(log_file, "%02X ", (unsigned) (c&0xFF));
   }
}


//
//
//   Get basic TSIP items from the serial port
//
//


void parse_tsip_message();


void get_tsip_message()
{
u08 c;

   // this routine buffers up an incoming TSIP message
   if(SERIAL_DATA_AVAILABLE() == 0) return;

   c = get_serial_char();
   if(rcv_error) {      // parity/framing/overrun errors
      rcv_error = 0;
//!!!!!qqqq    goto rst_msg;
   }

   if(tsip_sync == 0) {         // syncing to start of message, search for a DLE
      if(c == DLE) tsip_sync = 1;
      tsip_wptr = 0;
      tsip_rptr = 0;
      return;
   }
   else if(tsip_sync == 1) {    // DLE had been seen, now checking next byte
      if(c == DLE) {            // DLE DLE is a 0x10 data byte
         goto rst_msg;
      }
      else if(c == ETX) {       // DLE ETX is end-of-message
         goto rst_msg;          // ... should never happen here
      }
      else {                    // DLE xx is message start
         tsip_sync = 2;         // ... so accumulate the message
         if(tsip_wptr < MAX_TSIP) {
            tsip_buf[tsip_wptr++] = c;
         }
         else {                 // buffer overlow
            tsip_error |= 0x8000; // !!!!t
            goto rst_msg;
         }
      }
   }
   else if(tsip_sync == 2) {    // buffer up the message
      if(c == DLE) tsip_sync = 3;
      else if(tsip_wptr < MAX_TSIP) {
         tsip_buf[tsip_wptr++] = c;
      }
      else {
         tsip_error |= 0x8000;   // !!!!t
      }
   }
   else if(tsip_sync == 3) {   // last char was a DLE
      if(c == ETX) {           // DLE ETX is end-of-message
         parse_tsip_message(); // so process the buffered message

         rst_msg:
         tsip_wptr = 0;
         tsip_sync = 0;
      }
      else {                   // DLE DLE is a DLE data byte and DLE xx is message ID
         if(tsip_wptr < MAX_TSIP) {  // so add it to the message buffer
            tsip_buf[tsip_wptr++] = c;
         }
         else {
            tsip_error |= 0x8000;
         }
         tsip_sync = 2;
      }
   }
   else {     // should never happen
      goto rst_msg;
   }
}


unsigned get_next_tsip()
{
   early_end = 0;
   if(tsip_rptr >= tsip_wptr) {  // no more message to read
      return 0x2000;     // !!!!t
   }

   return tsip_buf[tsip_rptr++];
}

unsigned get_next_tsip_byte()
{
u16 c;

   if(early_end) {  // we are skipping message data
      if(log_comments && log_stream && log_file) {
         fprintf(log_file, "[%04X]", early_end);
      }
      return early_end;
   }

   c = get_next_tsip();  // get next data stream element
   if(c & 0xFF00) {      // we saw something that was not expected
      if(log_comments && log_stream && log_file) {
         fprintf(log_file, "<%04X>", c);
      }
      early_end = c;
   }
   return c;
}


u08 tsip_byte()   
{
u16 c;

   c = get_next_tsip_byte();
   if(c & 0xFF00) tsip_error |= 0x08;
   return (u08) (c & 0xFF);
}

u16 tsip_word()   /* get next two byte (word) field from binary message */
{
u08 i;
u08 word[2];
u16 c;

   for(i=0; i<2; i++) {
      c = get_next_tsip_byte();
      if(c & 0xFF00) tsip_error |= 0x10; 
      if(ENDIAN) word[i] = (u08) c;
      else       word[1-i] = (u08) c;
   }
   return * ((u16 *) (void *) &word[0]);
}

u32 tsip_dword()   /* get next dword field from binary message */
{
u08 i;
u08 word[4];
u16 c;

   for(i=0; i<4; i++) {
      c = get_next_tsip_byte();
      if(c & 0xFF00) tsip_error |= 0x20;
      if(ENDIAN) word[i] =(u08) c;
      else       word[3-i] = (u08) c;
   }
   return * ((u32 *) (void *) &word[0]);
}

float tsip_single()   /* get next four byte floating number from binary message */
{
u08 i;
u08 word[4];
u16 c;

   for(i=0; i<4; i++) {
      c = get_next_tsip_byte();
      if(c & 0xFF00) tsip_error |= 0x40;
      if(ENDIAN) word[i] = (u08) c;
      else       word[3-i] = (u08) c;
   }
   return * ((float *) (void *) &word[0]);
}

double tsip_double()   /* get next eight byte floating number from binary message */
{
u08 i;
u08 word[8];
u16 c;

   for(i=0; i<8; i++) {
      c = get_next_tsip_byte();
      if(c & 0xFF00) tsip_error |= 0x80;
      if(ENDIAN) word[i] = (u08) c;
      else       word[7-i] = (u08) c;
   }
   return * ((double *) (void *) &word[0]);
}

u08 tsip_end(u08 report_err)
{
   if(tsip_rptr != tsip_wptr) {  // we are not at the end of the message
      tsip_error |= 0x1000;  // !!!!t
//    if(log_comments && log_file) fprintf(log_file, "#!! rptr:%d  wptr:%d\n", tsip_rptr,tsip_wptr);
   }
   if(tsip_error) {
//    if(log_comments && log_file) fprintf(log_file, "#!! tsip_error:%04X\n", tsip_error);
      ++bad_packets;
      return 1;
   }
   tsip_rptr = tsip_wptr = 0;
   return 0;
}


//
//
//   Send basic TSIP items out the serial port
//
//

void send_byte(u08 val)
{
   sendout(val);  
   if(val == DLE) {
      sendout(DLE);  // DLE character must be sent twice
   }
}

void send_word(u16 val)
{
u08 *s;
int i;

   s = (u08 *) (void *) &val;
   for(i=0; i<2; i++) {
      if(ENDIAN) send_byte(s[i]);
      else       send_byte(s[1-i]);
   }
}

void send_dword(u32 val)
{
u08 *s;
int i;

   s = (u08 *) (void *) &val;
   for(i=0; i<4; i++) {
      if(ENDIAN) send_byte(s[i]);
      else       send_byte(s[3-i]);
   }
}

void send_single(float val)
{
u08 *s;
int i;

   s = (u08 *) (void *) &val;
   for(i=0; i<4; i++) {
      if(ENDIAN) send_byte(s[i]);
      else       send_byte(s[3-i]);
   }
}

void send_double(double val)
{
u08 *s;
int i;

   s = (u08 *) (void *) &val;
   for(i=0; i<8; i++) {
      if(ENDIAN) send_byte(s[i]);
      else       send_byte(s[7-i]);
   }
}

void send_msg_start(u08 id)
{
   sendout(DLE);
   send_byte(id);
}

void send_msg_end()
{
   sendout(DLE);
   sendout(ETX);
}


//
//
//   Message request and parameter setting messages
//
//


void request_fw_ver()
{
   if(luxor) return;
   send_msg_start(0x1C);   //!!! ThunderBolt-E, Resolution only
   send_byte(0x01);
   send_msg_end();
}

void request_unk_ver()
{
   if(luxor) return;
   send_msg_start(0x1C);   //!!! ??? receiver only
   send_byte(0x02);
   send_msg_end();
}

void request_hw_ver()
{
   if(luxor) return;
   send_msg_start(0x1C);   //!!! ThunderBolt-E, Resolution only
   send_byte(0x03);
   send_msg_end();
}


void request_luxor_ver()
{
   if(luxor == 0) return;
   send_msg_start(LUXOR_ID); 
   send_byte(0x00);
   send_msg_end();
}

void set_luxor_time()
{
#ifdef __linux__
   if(luxor == 0) return;
#else
SYSTEMTIME t;

   if(luxor == 0) return;

   GetSystemTime(&t);

   send_msg_start(LUXOR_ID); 
   send_byte(0x02);
   send_byte((u08) t.wSecond);
   send_byte((u08) t.wMinute);
   send_byte((u08) t.wHour);
   send_byte((u08) t.wDay);
   send_byte((u08) t.wMonth);
   send_byte((u08) (t.wYear-2000));
   send_msg_end();
#endif

   luxor_time_set = 1;
}

void set_luxor_sens(u08 lux1, u08 lux2)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x03);
   send_byte(lux1);
   send_byte(lux2);
   send_msg_end();
}

void set_batt_pwm(u16 pwm)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x06);
   send_word(pwm);
   send_msg_end();

   if(pwm == 0) {    // cancel alarm timers
      alarm_time = alarm_date = 0;
      egg_timer = 0;
      repeat_egg = 0;
   }
}


void set_pwm_step()
{
   if(batt_pwm_res == 8) PWM_STEP = (256.0F / 65536.0F);
   else if(batt_pwm_res == 9) PWM_STEP = (128.0F / 65536.0F);
   else { 
      PWM_STEP = (64.0F / 65536.0F);
      batt_pwm_res = 10;
   }
}

void set_luxor_config()
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x07);
   send_single(batt_lvc);
   send_single(batt_hvc);
   send_single(batt_ovc);
   send_single(batt_watts);
   send_single(load_lvc);
   send_single(load_hvc);
   send_single(load_ovc);
   send_single(load_watts);
   send_single(auxv_lvc);
   send_single(auxv_hvc);
   send_single(tc1_ovt);
   send_single(tc2_ovt);
   send_single(msg_timeout);

   send_single((float) lux1_time);
   send_single((float) lux2_time);
   send_single((float) emis1);
   send_single((float) emis2);

   send_byte(batt_pwm_res);
   send_msg_end();

   set_pwm_step();

   Sleep(500);   // !!!!!! allow time for message to be processed
}

void get_luxor_config()
{
   if(luxor == 0) return;

   batt_lvc = tsip_single();
   batt_hvc = tsip_single(); 
   batt_ovc = tsip_single(); 
   batt_watts = tsip_single();
   load_lvc = tsip_single(); 
   load_hvc = tsip_single(); 
   load_ovc = tsip_single(); 
   load_watts = tsip_single();
   auxv_lvc = tsip_single(); 
   auxv_hvc = tsip_single(); 
   tc1_ovt = tsip_single(); 
   tc2_ovt = tsip_single(); 
   msg_timeout = tsip_single();

   lux1_time = (u08) tsip_single();
   lux2_time = (u08) tsip_single();
   emis1 = tsip_single(); 
   emis2 = tsip_single(); 

   batt_pwm_res = tsip_byte();
   set_pwm_step();
   tsip_end(1);
}

void set_luxor_cal()
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x11);
   send_single(vref_m);
   send_single(vref_b);
   send_single(temp1_m);
   send_single(temp1_b);
   send_single(temp2_m);
   send_single(temp2_b);
   send_single(vcal_m);
   send_single(vcal_b);
   send_single(batti_m);
   send_single(batti_b);
   send_single(ledi_m);
   send_single(ledi_b);
   send_single(lux1_m);
   send_single(lux1_b);
   send_single(lux2_m);
   send_single(lux2_b);
   send_single(adc2_m);
   send_single(adc2_b);
   send_single(rb_m);
   send_single(rb_b);
   send_msg_end();

   Sleep(500);   // !!!!!! allow time for message to be processed
}

void get_luxor_cal()
{
   if(luxor == 0) return;

   vref_m = tsip_single();
   vref_b = tsip_single();
   temp1_m = tsip_single();
   temp1_b = tsip_single();
   temp2_m = tsip_single();
   temp2_b = tsip_single();
   vcal_m = tsip_single();
   vcal_b = tsip_single();
   batti_m = tsip_single();
   batti_b = tsip_single();
   ledi_m = tsip_single();
   ledi_b = tsip_single();
   lux1_m = tsip_single();
   lux1_b = tsip_single();
   lux2_m = tsip_single();
   lux2_b = tsip_single();
   adc2_m = tsip_single();
   adc2_b = tsip_single();
   rb_m = tsip_single();
   rb_b = tsip_single();

   tsip_end(1);
}


void set_luxor_runtime(u32 seconds)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x0A);
   send_dword(seconds);
   send_msg_end();
}

void set_luxor_delay(u16 msecs)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x0B);
   send_word(msecs);
   send_msg_end();
}


#define CLICK_TIME 500

void end_sweep()
{
   cc_mode = 0;
   sweep_stop = 0.0F;
   sweep_val = 0.0F;
   cc_state = 0;
   if(update_stop) {
      pause_data = 1;
      view_all();
      redraw_screen();
   }
   update_stop = 0;
}


void set_driver_mode()
{
int i, j;
int len;
int count;
float vals[128];
float val;

   // This routine sets the LED driver mode by pulsing the battery on and off.
   // It is also used to switch the battery on, off, or PWM it.

   end_sweep();
   count = 0;
   i = 0;
   len = strlen(edit_buffer);

   while(i < len) {   // get a list of numbers on the line
      for(j=i; j<len; j++) {   // find next number field
         if(edit_buffer[j] == 0) goto no_num;
         if(edit_buffer[j] == 0x0A) goto no_num;
         if(edit_buffer[j] == 0x0D) goto no_num;
         if(edit_buffer[j] == '.') goto got_num;
         if(isdigit(edit_buffer[j])) goto got_num;
         if(edit_buffer[j] == '*') {  // '*' is a double 100 msec pulse
            if(count >= 125) break;
            vals[count++] = 100;     // off
            vals[count++] = 100;     // on
            vals[count++] = 100;     // off
            vals[count++] = 100;     // on
         }
      }
      break;

      got_num:
      i = j;
      val = 0;
      sscanf(&edit_buffer[i], "%f", &val);
      vals[count] = val;
      ++count;
      if(count >= 128) break;

      while(i < len) {  // skip over number
         ++i;
         if(edit_buffer[i] == 0) goto no_num;
         if(edit_buffer[i] == 0x0A) goto no_num;
         if(edit_buffer[i] == 0x0D) goto no_num;
         if(edit_buffer[i] == '.') continue;
         if(edit_buffer[i] < '0') break;
         if(edit_buffer[i] > '9') break;
         if(edit_buffer[i] == '*') break;
      }
   }

   no_num:
   if(count == 0) {  // no numbers on the line, toggle battery state
      if(batt_pwm) {
         set_batt_pwm(0);
      }
      else {
update_check();
         set_batt_pwm(65535);
      }
//    set_luxor_delay(CLICK_TIME);
      Sleep(CLICK_TIME);
   }
   else if((count == 1) && (vals[0] <= 1.0)) {  // single number
      if(vals[0] == 0.0F) {
         set_batt_pwm(0);
      }
      else {
update_check();
         if(vals[0] == 1.0F) set_batt_pwm(65535);
         else set_batt_pwm((u16) (val*65536.0F));
      }
   }
   else {  // pulse the battery
      for(i=0; i<count; i++) {
         if(i & 1) {  // an ON time
            set_batt_pwm(65535);
         }
         else {           // an OFF time
            set_batt_pwm(0);
         }
//       set_luxor_delay((u16) vals[i]);
         Sleep((DWORD) vals[i]);
         set_batt_pwm(65535);
      }
   }
}

void set_emissivity(float em1, float em2)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x04);
   send_single(em1);
   send_single(em2);
   send_msg_end();
}

void set_cal_mode(u08 cal_mode)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x05);
   send_byte(cal_mode);
   send_msg_end();
}

void reset_luxor_wdt(u08 flag)
{
   if(luxor == 0) return;

   send_msg_start(LUXOR_ID); 
   send_byte(0x09);
   send_byte(flag);
   send_msg_end();
}

void request_c2()
{
   if(luxor) return;
   send_msg_start(0xC2);   //!!! ??? receiver
   send_msg_end();
}

void request_7A_00()
{
   if(luxor) return;
   send_msg_start(0x7A);   //!!! ??? receiver
   send_byte(0x00);
   send_msg_end();
}

void request_rcvr_health()
{
   if(luxor) return;
   send_msg_start(0x26);   //!!! ThunderBolt-E only
   send_msg_end();
}

void request_utc_info()
{
   if(luxor) return;
   send_msg_start(0x38);   // get UTC (leapsecond) info from sat data
   send_byte(0x01);
   send_byte(0x05);
   send_byte(0x00);
   send_msg_end();
}


void write_all_nvs()
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);   //!!! ThunderBolt-E only
   send_byte(0x26);
   send_msg_end();
}


void restart_gpsdo()
{
   // re-awaken a GPSDO after a reset
   if(saw_nortel || saw_ntpx) {
      vidstr(EDIT_ROW+4, EDIT_COL, PROMPT_COLOR, "There is a 20 second reset delay...");
      refresh_page();
      Sleep(20000);
      SetDtrLine(1);
      SendBreak();
   }
}


void request_cold_reset()
{
   if(read_only) return;
   if(luxor) {
      send_msg_start(LUXOR_ID);
      send_byte(0x10);
      send_msg_end();
      Sleep(100);

      set_luxor_time();
   }
   else {
      send_msg_start(0x1E);
      send_byte('K');
      send_msg_end();
      restart_gpsdo();
   }
}

void request_warm_reset()
{
   if(read_only) return;
   if(luxor) {
      set_luxor_time();
   }
   else {
      send_msg_start(0x25);
      send_msg_end();
      restart_gpsdo();
   }
}

void request_factory_reset()
{
   if(read_only) return;
   if(luxor) {
      send_msg_start(LUXOR_ID);   // erase EEPROM config
      send_byte(0x08);
      send_msg_end();
      Sleep(100);

      request_cold_reset();
   }
   else {
      send_msg_start(0x1E);
      send_byte('F');
      send_msg_end();
      restart_gpsdo();
   }
}

void request_version()
{
   if(luxor) return;
   send_msg_start(0x1F);
   if(0) {  // requests (undocumented) extended receiver configuration info
      send_byte(0x01);
      send_byte(0x00);
   }
   send_msg_end();
}

void request_almanac(u08 prn)
{
   if(luxor) return;
   send_msg_start(0x20);
   send_byte(prn);
   send_msg_end();
}

void request_sat_list()
{
   if(luxor) return;
   send_msg_start(0x24);
   send_msg_end();
}

void request_0x21()
{
   if(luxor) return;
   send_msg_start(0x21);
   send_msg_end();
}

void request_sig_levels()
{
   if(luxor) return;
   send_msg_start(0x27);
   send_msg_end();
}

void request_alm_health()
{
   if(res_t) return;
   if(luxor) return;

   send_msg_start(0x29);
   send_msg_end();
}

void set_xyz(float x, float y, float z)
{
   if(read_only) return;
   if(luxor) return;

   send_msg_start(0x31);
   send_single(x);
   send_single(y);
   send_single(z);
   send_msg_end();
}

void set_lla(float slat, float slon, float salt)
{
   if(read_only) return;
   need_posns = 1;
   if(luxor) {
      lat = slat;
      lon = slon;
      alt = salt;
   }
   else {
      send_msg_start(0x32);
      send_single(slat);
      send_single(slon);
      send_single(salt);
      send_msg_end();
   }
}

void set_single_sat(u08 prn)
{
   if(read_only) return;
   if(luxor) return;

   send_msg_start(0x34);
   send_byte(prn);
   send_msg_end();
}

void request_io_options()
{
   if(luxor) return;
   send_msg_start(0x35);
   send_msg_end();
}

void set_io_options(u08 posn, u08 vel, u08 timing, u08 aux)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x35);
   send_byte(posn);
   send_byte(vel);
   send_byte(timing);
   send_byte(aux);
   send_msg_end();
}

void request_last_posn()
{
   if(luxor) return;
   send_msg_start(0x37);
   send_msg_end();
}

void request_system_data(u08 mode, u08 prn)
{
   if(luxor) return;
   send_msg_start(0x38);
   send_byte(0x01);
   send_byte(mode);
   send_byte(prn);
   send_msg_end();
}

void twiddle_health(u08 mode, u08 prn)
{
   if(read_only) return;
   if(luxor) return;
   if(res_t == 2) return;

   send_msg_start(0x39);
   send_byte(mode);
   send_byte(prn);
   send_msg_end();
}

void request_sat_health()
{
   if(luxor) return;
   twiddle_health(3, 0x00);  // request enable/disable status of all sats
   twiddle_health(6, 0x00);  // request heed/ignore status of all sats
}

void request_last_raw(u08 prn)
{
   if(luxor) return;
   send_msg_start(0x3A);
   send_byte(prn);
   send_msg_end();
}

void request_eph_status(u08 prn)
{
   if(res_t) return;
   if(luxor) return;

   send_msg_start(0x3B);
   send_byte(prn);
   send_msg_end();
}

void request_sat_status(u08 prn)
{
   if(luxor) return;
   send_msg_start(0x3C);
   send_byte(prn);
   send_msg_end();
}

void request_eeprom_status()
{
   if(luxor) return;
   if(res_t) return;          // !!! Thunderbolt only
   if(saw_ntpx) return;

   send_msg_start(0x3F);
   send_byte(0x11);
   send_msg_end();
}


void request_filter_config()
{
   if(luxor) return;
   send_msg_start(0x70);
   send_msg_end();
}

void set_filter_config(u08 pv, u08 stat, u08 alt, u08 kalman, int save)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x70);
   send_byte(pv);
   send_byte(stat);
   send_byte(alt);
   send_byte(kalman); // rsvd on ThunderBolt,  kalman on ThunderBolt-E
   send_msg_end();
   if(0 && save) save_segment(255);
}


void request_rcvr_config()
{
   if(luxor) return;
   send_msg_start(0xBB);
   send_byte(0x00);
   send_msg_end();
}


void config_rcvr(u08 mode, u08 dynamics, float elev, float amu, float pdop_mask, float pdop_switch, u08 foliage)
{
int i;

   //!!! values of FF and -1.0 say to not change that value
   if(luxor) return;
   if(read_only == 0) {     // it's OK to change the receiver settings
      send_msg_start(0xBB);
      send_byte(0x00);
      send_byte(mode);          // 4=full posn  7=overdetermined clock
      send_byte(0xFF);          // ignored
      send_byte(dynamics);      // 4=stationary dynamics  
      send_byte(0xFF);          // ignored
      send_single(elev);        // 0.175F = 10 degree mask angle
      send_single(amu);         // 4.0 amu mask
      send_single(pdop_mask);   // 8.0 pdop mask
      send_single(pdop_switch); // 6.0 pdop switch
      send_byte(0xFF) ;         // 0xFF ignored
      send_byte(foliage) ;      // 1 = some foliage
      for(i=23; i<=39; i++) send_byte(0xFF);
      send_msg_end();
   }

   have_rcvr_mode = 0;
   request_filter_config();
   request_sat_list();
   request_rcvr_config();

   if(mode != 0xFF) {
      if(mode == 7) fix_mode = 0;
      else          fix_mode = 1;
      configed_mode = mode;
   }
   else if(read_only == 0) {
      save_segment(3);    // save receiver config
   }
}


float set_el_level(void)
{
float level;

   #ifdef SIG_LEVELS
      level = (float) good_el_level();
   #else
      level = GOOD_EL_LEVEL;
   #endif

   set_el_mask(level);
   return level;
}

void request_serial_config(u08 port)
{
   if(luxor) return;
   send_msg_start(0xBC);
   send_byte(port);
   send_msg_end();
}

void set_serial_config()
{
   //!!!
   if(read_only) return;
   if(luxor) return;
}


void request_datum()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x15);
   send_msg_end();
}


void request_manuf_params()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x41);
   send_msg_end();
}

void request_prodn_params()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x42);
   send_msg_end();
}

void revert_segment(u08 segment)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x45);
   send_byte(segment);
   send_msg_end();
}


void request_pps()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x4A);
   send_msg_end();
}

void set_pps(u08 pps_enable,  u08 pps_polarity,  double cable_delay,  float threshold, int save)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x4A);
   send_byte(pps_enable);
   send_byte(0x00);
   send_byte(pps_polarity);
   send_double(cable_delay);
   send_single(threshold);
   send_msg_end();

   if(save) save_segment(6);       // save timing config in EEPROM
}


void request_pps_mode()
{
   if(read_only) return;    // !!!Resolution-T only
   if(luxor) return;
   if(saw_ntpx) return;

   send_msg_start(0x8E);
   send_byte(0x4E);
   send_msg_end();
}

void request_pps_width()
{
   if(read_only) return;    // !!!Which receivers can do this?
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x4F);
   send_msg_end();
}

void set_pps_mode(int mode)
{
   if(read_only) return;    // !!! Resolution-T only
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x4E);
   send_byte(mode);
   send_msg_end();
}


void save_segment(u08 segment)
{
   if(read_only) return;
   if(luxor) return;
   if(no_eeprom_writes) return;
   if(res_t) {
      if(segment == 7) start_self_survey(1);  // save survey params
      else             write_all_nvs();       // save current config
   }
   else {
      send_msg_start(0x8E);
      send_byte(0x4C);
      send_byte(segment);
      send_msg_end();
   }

   BEEP();   // !!! if you hear lots of beeps,  you may be wearing out the EEPROM
}


void request_dac_voltage()
{
   if(luxor) return;
   if(res_t) return;
   send_msg_start(0x8E);
   send_byte(0xA0);
   send_msg_end();
}

void set_dac_voltage(float volts)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA0);
   send_byte(0x00);
   send_single(volts);
   send_msg_end();
}

void set_dac_value(u32 value)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA0);
   send_byte(0x01);
   send_dword(value);
   send_msg_end();
}


void request_osc_sense()
{
   if(luxor) return;
   if(res_t) return;
   send_msg_start(0x8E);  // not available on ThunderBolt-E or early ThunderBolts
   send_byte(0xA1);
   send_msg_end();
}

void set_osc_sense(u08 mode, int save)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);  // not available on ThunderBolt-E or early ThunderBolts
   send_byte(0xA1);
   send_byte(mode);
   send_msg_end();

   if(save) save_segment(6);       // save timing config in EEPROM
}


void request_timing_mode()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA2);
   send_msg_end();
}

void set_timing_mode(u08 mode)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA2);
   send_byte(mode);
   send_msg_end();
}


void set_discipline_mode(u08 mode)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA3);
   send_byte(mode);
   send_msg_end();

   if(mode == 0) {
      osc_integral = 0.0;
      have_osc = 0;
   }
}


void exit_test_mode()
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA4);
   send_byte(0x00);
   send_msg_end();
}

void set_test_mode()
{
   //!!!
   if(read_only) return;
   if(luxor) return;
}


void request_packet_mask()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA5);
   send_msg_end();
}

void set_packet_mask(u16 mask1, u16 mask2)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA5);
   send_word(mask1);
   send_word(mask2);
   send_msg_end();
}


void request_discipline_params(u08 type)
{
   if(luxor) return;
   if(res_t) return;

   send_msg_start(0x8E);
   send_byte(0xA8);
   send_byte(type);
   send_msg_end();
}

void request_all_dis_params()
{
   request_discipline_params(0x00);
   request_discipline_params(0x01);
   request_discipline_params(0x02);
   request_discipline_params(0x03);
   request_discipline_params(0x04); // undocumented - allowable DAC range?
}


void set_discipline_params(int save)
{
   if(read_only) return;
   if(luxor) return;

   if(have_osc_params & 0x01) { 
      send_msg_start(0x8E);
      send_byte(0xA8);
      send_byte(0x00);
      send_single(user_time_constant);
      send_single(user_damping_factor);
      send_msg_end();
   }

   if(have_osc_params & 0x02) { 
      send_msg_start(0x8E);
      send_byte(0xA8);
      send_byte(0x01);
      send_single(user_osc_gain);
      send_single(user_min_volts);
      send_single(user_max_volts);
      send_msg_end();
   }

   if(have_osc_params & 0x04) { 
      send_msg_start(0x8E);
      send_byte(0xA8);
      send_byte(0x02);
      send_single(user_jam_sync);
      send_single(user_max_freq_offset);
      send_msg_end();
   }

   if(have_osc_params & 0x08) { 
      send_msg_start(0x8E);
      send_byte(0xA8);
      send_byte(0x03);
      send_single(user_initial_voltage);
      send_msg_end();
   }

   if(1 && (have_osc_params & 0x10)) { // !!!! undocumented - allowable dac range
      send_msg_start(0x8E);
      send_byte(0xA8);
      send_byte(0x04);
      send_single(user_min_range);
      send_single(user_max_range);
      send_msg_end();
   }

   if(save) {
      if((have_osc_params & 0x1F) == 0x1F) {  // !!!!! 0x0F: we have all osc params available
         save_segment(9);
      }
      else if(saw_ntpx && ((have_osc_params & 0x03) == 0x03)) {
         save_segment(9);
      }
   }
}


void request_survey_params()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA9);
   send_msg_end();
}

void set_survey_params(u08 enable_survey,  u08 save_survey, u32 survey_len)
{
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA9);
   send_byte(enable_survey);
   send_byte(save_survey);
   send_dword(survey_len);
   send_dword(0x0000);
   send_msg_end();
}

void start_self_survey(u08 val)
{
   // val=0 - start survey
   // val=1 - save position (Tbolt-E)
   // val=2 - delete position (Tbolt-E)
   if(read_only) return;
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xA6);
   send_byte(val);
   send_msg_end();

   if(val == 0) {
      surveying = 1;
   }
// plot_lla = 1;
// show_fixes = 1;
   request_survey_params();
}

void stop_self_survey()
{
// set_survey_params(0, 0, 0L);
// start_self_survey(0);
   if(read_only) return;
   if(luxor) return;
   set_rcvr_config(7);
}


void request_primary_timing()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xAB);
   send_byte(0x02);
   send_msg_end();
}

void request_secondary_timing()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xAC);
   send_byte(0x02);
   send_msg_end();
}

void request_ae_packet(u08 subcode)
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0xAE);
   send_byte(subcode);
   send_msg_end();
}



//
//
//   Incomming message handlers
//
//

void saw_ebolt()
{
   // This routine is called if message that is only supported
   // on the Thunderbolt-E is received.

   if((small_font == 1) && (SCREEN_HEIGHT < 600) && (text_mode == 0)) {
      temp_sats = 8;
      eofs = 1;
   }
   else if((TEXT_HEIGHT <= 12) || (SCREEN_HEIGHT >= 768)) {
      temp_sats = 12;
      eofs = 1;
   }
   else {
      if(plot_stat_info)  temp_sats = 11;
      else if(res_t == 2) temp_sats = 14;
      else                temp_sats = 12;
      eofs = 0;
   }

   // there is no room to show all the sats if the big clock is on
   if(0 && plot_digital_clock && (time_col >= (TEXT_COLS/2))) { 
      temp_sats = 8; //// what if sat_info is in plot area?
   }

   ebolt = 1;
   if(ebolt != last_ebolt) {
      max_sats = temp_sats;
if(res_t == 2) max_sats = 14;
else if(res_t) max_sats = 12;
      last_ebolt = ebolt;
      redraw_screen();   // redraw the screen
   }
}

void ebolt_version()
{   // ThunderBolt-E only
u08 rsvd1;
u08 major;
u08 minor;
u08 build;
u08 rev_month;
u08 rev_day;
u16 rev_year;
u08 len;
u32 serno;
u08 rev_hour;
int i;

// printf("Packet 1C (Tbolt-E version):\n");
   rev_month = rev_day = rev_hour = 0;
   rev_year = 0;

   subcode = tsip_byte();
   if(subcode == 0x81) {  // firmware version
      rsvd1 = tsip_byte();
      major = tsip_byte();
      minor = tsip_byte();
      build = tsip_byte();
      rev_month = tsip_byte();
      rev_day = tsip_byte();
      rev_year = tsip_word();
      len = tsip_byte();
      for(i=0; i<UNIT_LEN; i++) unit_name[i] = ' ';
      unit_name[UNIT_LEN] = 0;
  
      out[0] = 0;
      for(i=0; i<len; i++) {
         if(i >= MAX_TEXT_COLS) {
            tsip_byte();
            continue;
         }
         out[i] = tsip_byte();
         out[i+1] = 0;
         if(i < UNIT_LEN) {
            unit_name[i] = out[i];
         }
      }
  
      strupr(out);
      if(res_t == 0) {
         if(strstr(out, "RESOLUTION")) {
            if(strstr(out, "SMT")) res_t = 2;
            else                   res_t = 1;
            config_res_t_plots();
         }
      }
      if(mini_t == 0) {
         if(strstr(out, "MINI")) {
            mini_t = 1;
            saw_mini = 1;
         }
      }
      strncpy(unit_name, out, UNIT_LEN);
   }
   else if(subcode == 0x83) {  // hardware version
      serno = tsip_dword();
      rev_day = tsip_byte();
      rev_month = tsip_byte();
      rev_year = tsip_word();
      rev_hour = tsip_byte();
      hw_code = tsip_word();
      len = tsip_byte();
      out[0] = 0;
      for(i=0; i<len; i++) {
         if(i >= MAX_TEXT_COLS) {
            tsip_byte();
            continue;
         }
         out[i] = tsip_byte();
         out[i+1] = 0;
      }
   }
   else {  // unknown
      //!!! process packet contents
   }

   tsip_end(1);   
   if(tsip_error) return;

   saw_ebolt();
   saw_version |= 0x02;

   if(1) {  //!!!!!
      if(rev_month > 12) return;
      if(rev_month == 0) return;
      if(rev_day > 31) return;
      if(rev_day == 0) return;
      if(rev_year < 1990) return;
      if(rev_year > 2100) return;
      if(rev_hour > 24) return;
   }

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;
if(just_read) return;

   if(0 && (subcode == 0x83)) {  // !!! disabled since hw_code clashes with sn_prefix
      sprintf(out, "Mfg: %02d:00  %02d %s %04d", 
         rev_hour, rev_day, months[rev_month], rev_year);
      vidstr(VER_ROW+3, VER_COL, WHITE, out);

      if(com_port >= 10)      sprintf(out, "Ser: %2u.%-8lu COM:%d",  hw_code, (unsigned long) serno, com_port);
      else if (com_port)      sprintf(out, "Ser: %2u.%-8lu  COM:%d", hw_code, (unsigned long) serno, com_port);
      else if(usb_port >= 10) sprintf(out, "Ser: %2u.%-8lu USB:%d",  hw_code, (unsigned long) serno, usb_port);
      else if(usb_port)       sprintf(out, "Ser: %2u.%-8lu  USB:%d", hw_code, (unsigned long) serno, usb_port);
#ifdef TCP_IP 
      else                    sprintf(out," IP: %s", IP_addr); // TCP 
#endif
      vidstr(VER_ROW+4, VER_COL, WHITE, out);
   }
}

void msg_41()
{
// printf("Packet 41 (NTPX ????):\n");
unsigned long v1;
unsigned long v2;
u16 v3;

   v1 = tsip_dword();
   v2 = tsip_dword();
   v3 = tsip_word();
//sprintf(plot_title, "msg 0x41: v1:%08lX  v2:%08lX  word:%04X", v1,v2,v3);
   tsip_end(1);
   if(tsip_error) return;
}

void single_ecef_fix()
{
float fix_x,fix_y,fix_z;
float time_of_fix;

// printf("Packet 42 (XYZ ECEF):\n");
   fix_x = tsip_single();
   fix_y = tsip_single();
   fix_z = tsip_single();
   time_of_fix = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
}


void get_pps_mode()
{
// printf("Packet 8F 4E (pps rate):\n");
   pps_rate = tsip_byte();
   tsip_end(1);
   if(tsip_error) return;
}

void velocity_fix()
{
float x_vel,y_vel,z_vel;
float bias_rate;
float time_of_fix;

// printf("Packet 43 (XYZ ECEF velocity):\n");

   x_vel = tsip_single();
   y_vel = tsip_single();
   z_vel = tsip_single();
   bias_rate = tsip_single();
   time_of_fix = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
}

void show_version_header()
{
   if     (read_only) vidstr(VER_ROW+0, VER_COL, BLUE, "Read-only mode set  ");
   else if(no_send)   vidstr(VER_ROW+0, VER_COL, BLUE, "COM output disabled ");
   else if(just_read) vidstr(VER_ROW+0, VER_COL, BLUE, "TSIP decode disabled");
   else if(disable_kbd > 1) {
      if(script_file) {
         vidstr(VER_ROW+0, VER_COL, BLUE, "Script file error    "); 
      }
      else {
         #ifdef DOS
            vidstr(VER_ROW+0, VER_COL, BLUE, "Press BREAK to exit  "); 
         #else
            vidstr(VER_ROW+0, VER_COL, BLUE, "Keyboard disabled    "); 
         #endif
      }
   }
   else if(disable_kbd) vidstr(VER_ROW+0, VER_COL, BLUE, "Press ESC Y to exit");
   else if(plot_version) {
       sprintf(out, "V%s - %s    ", VERSION, date_string);
       vidstr(VER_ROW+0, VER_COL, BLUE, out);
    }
   else vidstr(VER_ROW+0, VER_COL, BLUE, "Press SPACE for help ");
}

void version_info()
{
// printf("Packet 45 (Software version):\n");

   ap_major = tsip_byte();
   ap_minor = tsip_byte();
   ap_month = tsip_byte();
   ap_day = tsip_byte();
   ap_year = tsip_byte();
   if(ap_year > 80) ap_year += 1900;
   else             ap_year += 2000;

   core_major = tsip_byte();
   core_minor = tsip_byte();
   core_month = tsip_byte();
   core_day = tsip_byte();
   core_year = tsip_byte();
   if(core_year > 80) core_year += 1900;
   else               core_year += 2000;

   tsip_end(1);
   if(tsip_error) return;

   saw_version |= 0x01;

   if(ap_month > 12) return;
   if(ap_month == 0) return;
   if(ap_day > 31) return;
   if(ap_day == 0) return;
   if(core_month > 12) return;
   if(core_month == 0) return;
   if(core_day > 31) return;
   if(core_day == 0) return;
   if(ap_year < 1980) return;
   if(ap_year > 2080) return;
   if(core_year < 1980) return;
   if(core_year > 2080) return;

   have_info |= VERSION_INFO;

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;
if(just_read) return;

   show_version_header();

   sprintf(out, "App: %2d.%-2d  %02d %s %02d", 
      ap_major, ap_minor,  ap_day, months[ap_month], ap_year);   //!!! docs say 1900
   vidstr(VER_ROW+1, VER_COL, WHITE, out);
   sprintf(out, "GPS: %2d.%-2d  %02d %s %02d", 
      core_major, core_minor,  core_day, months[core_month], core_year);  //!!! docs say 1900
   vidstr(VER_ROW+2, VER_COL, WHITE, out);
}

void ebolt_health1()
{
u08 sv_fix;
u08 antenna_fault;

// printf("Packet 46 (Tbolt-E health):\n");

   sv_fix = tsip_byte();
   antenna_fault = tsip_byte();
   tsip_end(1);
   if(tsip_error) return;

   saw_version |= 0x04;
   saw_ebolt();
}

void find_sat_changes()
{
int i, j;

   // see if the satellite constellation has changed
   j = 0;
   sat_count = 0;
   last_const = this_const;
   this_const = 0;
   for(i=1; i<=32; i++) {
      if(sat[i].level_msg == 0x00) continue;
      if(++j > max_sats) break;

      if(sat[i].tracking > 0) {
         this_const |= (1L << (i-1));
         ++sat_count;
      }
   }

   if(this_const != last_const) {
      new_const = (sat_count | CONST_CHANGE);
   }
}


void show_osc_params(int row, int col)
{
double dac;
double drift;
double tempco;
char c[10];
int prn;

   prn = 0;
   c[0] = 0;

   if(all_adevs) {
      if(SCREEN_WIDTH > 800)   col += 3;
      else if(small_font == 1) col -= 3;
   }

   if(jam_sync < 10.0)       sprintf(out, "Jam sync threshold:   %.3f ns    ", jam_sync);
   else if(jam_sync < 100.0) sprintf(out, "Jam sync threshold:  %.3f ns    ", jam_sync);
   else                      sprintf(out, "Jam sync threshold: %.3f ns    ", jam_sync);
   if(saw_ntpx) vidstr(row++, col, GREY,  out);
   else         vidstr(row++, col, WHITE, out);

   if(max_freq_offset < 10.0) sprintf(out, "Max freq offset:      %.3f%s    ", max_freq_offset, ppb_string);
   else                       sprintf(out, "Max freq offset:     %.3f%s    ", max_freq_offset, ppb_string);
   if(saw_ntpx) vidstr(row++, col, GREY,  out);
   else         vidstr(row++, col, WHITE, out);

   sprintf(out, "Time constant:      %.3f secs    ", time_constant);
   vidstr(row++, col, WHITE, out);

   sprintf(out, "Damping factor:       %.3f    ", damping_factor);
   vidstr(row++, col, WHITE, out);

   sprintf(out, "Osc gain:            %+.6f Hz/V    ", osc_gain);
   vidstr(row++, col, gain_color, out);

   sprintf(out, "Initial DAC voltage: %+.6f V    ", initial_voltage);
   if(saw_ntpx) vidstr(row++, col, GREY,  out);
   else         vidstr(row++, col, WHITE, out);

   sprintf(out, "Min EFC voltage:     %+.6f V    ", min_volts);
   vidstr(row++, col, WHITE, out);

   sprintf(out, "Max EFC voltage:     %+.6f V    ", max_volts);
   vidstr(row++, col, WHITE, out);

   if(min_dac_v || max_dac_v) {
      sprintf(out, "EFC DAC range:       %+.2f to %+.2f V ", min_dac_v, max_dac_v);
      if(saw_ntpx) vidstr(row++, col, GREY,  out);
      else         vidstr(row++, col, WHITE, out);
   }


   
   // Calculate oscillator drift rate per day based upon the dac
   // voltage change over the plot display interval.  This assumes
   // that the temperature is stable.
   dac = plot[DAC].a1;
   drift = (dac * (double) osc_gain) * 24.0*3600.0;  // Hz per day
   sprintf(out, "Osc drift rate: %14.6e parts/day   ", drift/10.0E6F);
   vidstr(row+1, col, WHITE, out);

   // Calculate oscillator freq change with temperature over the plot
   // display interval.  This assumes that the temperature has changed
   // during the display interval.
   tempco = plot[TEMP].a1;  // degrees/sec
   if(tempco) {
      tempco = plot[OSC].a1 / tempco;  // (ppb/sec) divided by (degrees/sec)
      tempco /= (-1.0E9);              // convert ppb/degree C into parts/C
      sprintf(out, "Osc tempco:     %14.6e parts/%cC   ", tempco, DEGREES);
      vidstr(row+2, col, WHITE, out);
   }

   show_sun_azel(row+1, col+42);

#ifdef SIG_LEVELS
   row = DIS_ROW+0+eofs+5;
   col = DIS_COL;
   if(amu_mode) strcpy(out, "satellite max AMU: ");
   else         strcpy(out, "satellite max dBc: ");
   vidstr(row, col, WHITE, out); 
   ++row;
   strcpy(out, "  01: ");
   for(prn=1; prn<=32; prn++) {
      sprintf(c, "%2d ", (int) (max_sat_db[prn]+0.5F));
      strcat(out, c);
      if((prn%5) == 0) { 
         vidstr(row, col, WHITE, out); 
         sprintf(out, "  %02d: ", prn+1);
         ++row;
      }
   };
   vidstr(row, col, WHITE, out); 
#endif

   if(0) {  // alternate osc parameter calculations
      if(view_interval == 0) return;
      if(plot_mag == 0) return;
      if(plot[DAC].stat_count == 0.0) return;
      if(plot[OSC].stat_count == 0.0) return;
      ++row;

      dac = plot[DAC].sum_change / plot[DAC].stat_count / view_interval;
      dac /= plot_mag;
      drift = (dac * (double) osc_gain) * 24.0*3600.0;  // Hz per day
      sprintf(out, "Osc drift rate: %14.6e parts/day   ", drift/10.0E6F);
      vidstr(row++, col, WHITE, out);

      tempco = plot[TEMP].sum_change / plot[TEMP].stat_count / view_interval;
      tempco /= plot_mag;
      if(tempco) {
         tempco = (plot[OSC].sum_change/plot[OSC].stat_count/view_interval) / tempco;  // (ppb/sec) divided by (degrees/sec)
         tempco /= (-1.0E9);              // convert ppb/degree C into parts/C
         sprintf(out, "Osc tempco:     %14.6e parts/%cC   ", tempco, DEGREES);
         vidstr(row++, col, WHITE, out);
      }
   }

   return;
}

void show_satinfo()
{
int i, j;
float az;
float el;
u08 el_dir;
float dop;
float phase;
float sig;
float clock;
float acc;
COORD row, col;
u08 time_exit;
char format_string[256];
char el_string[10];
char bias_string[20];
int len, max_len;
u08 info_under_azel;

   // This routine draws the satellite info table.  It also calls the
   // digital clock display routine (since on small screens the digital clock
   // takes the place of the sat info display).  It also controls the alarm
   // clock operation.
   if(text_mode && first_key) {
      find_sat_changes();
      return;
   }
   
   time_exit = 0;
   print_using = 0;
   format_string[0] = 0;

   if(all_adevs) {   // screen is showing all the adev tables
      if(text_mode) {
         col = 0;
         row = TEXT_ROWS - 8;
      }
      else {
         if(SCREEN_WIDTH >= 1280) col = CRIT_COL + 19;
         else                     col = CRIT_COL + 12;
         row = 0;
      }
   }
   else {    // normal screen mode
      col = SAT_COL;
      row = SAT_ROW+eofs;
      if(text_mode) ++row;
      else if((TEXT_HEIGHT <= 14) || (SCREEN_HEIGHT >= 768)) ++row;
   }

   if(sound_alarm) {
      if(ticker & 0x01)      time_color = ALARM_COLOR;
      else if(dst_ofs)       time_color = DST_TIME_COLOR;
      else if(time_zone_set) time_color = DST_TIME_COLOR;  // !!! std_time_color is rather dim for the big clock
      else                   time_color = WHITE;
      #ifdef DIGITAL_CLOCK
         reset_vstring();
      #endif
   }

   // if sats are not in use show the osc control info
// if(osc_params || (osc_discipline == 0)) {  
   if(osc_params && (all_adevs == 0) && (zoom_screen == 0)) {
      show_osc_params(row, col);
      find_sat_changes();
      return;
   }

   info_under_azel = 0;
   if(SHARED_AZEL && (AZEL_BOTTOM+(TEXT_HEIGHT*(8+1)) < SCREEN_HEIGHT)) {  
      if(SCREEN_HEIGHT <= 1024) {
         info_under_azel = 1;
      }
      else if(plot_watch && plot_digital_clock && ebolt) info_under_azel = 1;
      else if(all_adevs) info_under_azel = 1;
   }

   digital_clock_shown = 0;
   #ifdef DIGITAL_CLOCK
      if((plot_digital_clock && ((all_adevs == 0) || (SCREEN_WIDTH > 800))) || zoom_screen) {
         time_exit = show_digital_clock(row, col);
         if((time_exit == 0) && (all_adevs == 0)) info_under_azel = 0;

         // there is room to sneak in the sat info table below the az/el map
         if(info_under_azel) {  
            row = AZEL_BOTTOM/TEXT_HEIGHT;
            col = (AZEL_COL/TEXT_WIDTH) + 5; 
            if(ebolt) ;        
            else if(all_adevs) col -= 2;
         }
         else if(time_exit) { // no room on screen for sat info and digital clock
            find_sat_changes();
            return;
         }
      }
   #endif  // DIGITAL_CLOCK
   if(zoom_screen) {
      find_sat_changes();
      return;
   }
   if(luxor) return;

   if(all_adevs) {  // if no room to show info,  just check for sat changes
      if(text_mode) {
         find_sat_changes();
         return;
      }
      if(first_key && (row >= PLOT_TEXT_ROW)) {
         find_sat_changes();
         return;
      }
      if((digital_clock_shown || ((row+max_sats+1) >= all_adev_row))) {
         if(info_under_azel && ((plot_lla == 0) || (all_adevs == 0))) {  
            row = AZEL_BOTTOM/TEXT_HEIGHT;
            col = (AZEL_COL/TEXT_WIDTH) + 5; 
            if(ebolt) ;        
            else if(all_adevs) col -= 2;
         }
         else {
            find_sat_changes();
            return;
         }
      }
   }

   // print the sat info table header
   #ifdef VARIABLE_FONT
      if(all_adevs) {
         // first erase the old table area
         VFX_rectangle_fill(stage, 
                         (col * TEXT_WIDTH) + TEXT_X_MARGIN, 
                         (row * TEXT_HEIGHT) + TEXT_Y_MARGIN, 
                         (SCREEN_WIDTH-1),
                         ((row * TEXT_HEIGHT) + (9 * TEXT_HEIGHT)) + TEXT_Y_MARGIN,
                         LD_DRAW, RGB_TRIPLET(0,0,0));
         if(ebolt) {
            sprintf(out, "PRN    %cAZ      %cEL      %s    DOPPLER     CODE", DEGREES, DEGREES, level_type);
         }
         else {
            sprintf(out, "PRN    %cAZ      %cEL      %s     CLOCK_BIAS      ACCU", DEGREES, DEGREES, level_type);
         }
      }
      else {
         // first erase the old table area
         VFX_rectangle_fill(stage, 
                         (col * TEXT_WIDTH) + TEXT_X_MARGIN, 
                         (row * TEXT_HEIGHT) + TEXT_Y_MARGIN, 
                         ((col * TEXT_WIDTH) + 450) + TEXT_X_MARGIN,
                         ((row * TEXT_HEIGHT) + ((max_sats+1) * TEXT_HEIGHT)) + TEXT_Y_MARGIN-1,
                         LD_DRAW, RGB_TRIPLET(0,0,0));
         if(res_t) {      
            sprintf(out, "PRN    %cAZ      %cEL      %s     DOPPLER     CODE             ", DEGREES, DEGREES, level_type);
         }
         else if(ebolt) {  // ThunderBolt-E gives no satellite clock bias data
            sprintf(out, "PRN    %cAZ      %cEL      %s     DOPPLER     CODE         ACCU", DEGREES, DEGREES, level_type);
         }
         else {
            sprintf(out, "PRN    %cAZ      %cEL      %s     DOPPLER     CODE         CLOCK_BIAS       ACCU", DEGREES, DEGREES, level_type);
         }
      }
      VFX_io_done = 1;
      strcpy(format_string, out);   // we use the header spacing to align the output columns
      vidstr(row++, col, WHITE, out);
      print_using = &format_string[0];
   #endif // VARIABLE_FONT

   #ifdef FIXED_FONT
      if(all_adevs) {
         if(ebolt) {
            sprintf(out, "PRN  %cAZ    %cEL    %s   DOPPLER    CODE", DEGREES, DEGREES, level_type);
         }
         else {
            sprintf(out, "PRN  %cAZ    %cEL    %s    CLOCK BIAS  ACCU", DEGREES, DEGREES, level_type);
         }
      }
      else {
         if(res_t) {
            sprintf(out, "PRN  %cAZ    %cEL    %s   DOPPLER    CODE         ", DEGREES, DEGREES, level_type);
         }
         else if(ebolt) {  // ThunderBolt-E gives no satellite clock bias data
            sprintf(out, "PRN  %cAZ    %cEL    %s   DOPPLER    CODE     ACCU", DEGREES, DEGREES, level_type);
         }
         else {
            sprintf(out, "PRN  %cAZ    %cEL    %s   DOPPLER    CODE     CLOCK BIAS  ACCU", DEGREES, DEGREES, level_type);
         }
      }
      vidstr(row++, col, WHITE, out);
   #endif // FIXED_FONT


   // now draw the sat info table
   j = 0;
   sat_count = 0;
   last_const = this_const;
   this_const = 0;
   max_len = 0;
   min_clock = 0.0F;
   clock_sum = 0.0F;
   clock_count = 0.0F;
   for(i=1; i<=32; i++) {
      if(sat[i].level_msg == 0x00) continue;
      if(++j > max_sats) break;
      if(all_adevs && (j > 8)) break;  // only room for 8 sats here
      if((col < (TEXT_COLS/2)) && (row >= MOUSE_ROW)) break;

      // filter out potentially bogus data
      az = sat[i].azimuth;
      if((az < 0.0) || (az > 360.0)) az = 0.0;
      el = sat[i].elevation;
      if((el < 0.0) || (el > 90.0)) el = 0.0;
      el_dir = sat[i].el_dir;
      if(el_dir == 0) el_dir = ' ';
      else if(el == 0.0) el_dir = ' ';
      dop = sat[i].doppler;
      if((dop <= -10000.0) || (dop >= 10000.0)) dop = 0.0;
      phase = sat[i].code_phase;
      if((phase <= -100000.0) || (phase >= 100000.0)) phase = 0.0;
      sig = sat[i].sig_level;
      if(sig >= 100.0F) sig = 0.0F;
      if(sig <= (-100.0F)) sig = 0.0F;
      if(sig < 0.0F) sig = 0.0F - sig;

      clock = sat[i].sat_bias;
      if((clock < -1.0e-6) || (clock > 1.0e-6)) clock = 0.0;
      else {
         if(min_clock == 0) min_clock = clock;
         else if(ABS(clock) < ABS(min_clock)) min_clock = clock;
      }

      if((sig > SIG_THRESHOLD) && clock) {
         clock_sum += clock;
         clock_count += 1.0F;
      }

      acc = sat[i].sv_accuracy;
      if((acc < 0.0) || (acc >= 100.0)) acc = 0.0;

      out[0] = 0;

      if(el < 10.0F) sprintf(el_string, " %-3.1f", el);
      else           sprintf(el_string, "%-4.1f", el);
      if(el_string[3] == ' ') el_string[3] = el_dir;
      else                    el_string[4] = el_dir;
      el_string[5] = 0;

      if(clock == 0.0) strcpy(bias_string, " 0.000e+000");
      else             sprintf(bias_string, "%#11.4g", clock);

      #ifdef VARIABLE_FONT
         blank_underscore = 1;
         print_using = &format_string[0];
         if(all_adevs) {
            if(ebolt) {
               sprintf(out, " %02d__  %5.1f  %s %5.1f  %8.2f  %8.2f  ",
                  i, az, el_string, sig, dop, phase);
            }
            else {
               sprintf(out, " %02d__  %5.1f  %s  %4.1f  %s  _%-4.2f  ",
                  i, az, el_string, sig, bias_string, acc);
            }
         }
         else {
            if(res_t) {
               sprintf(out, " %02d__  %5.1f  %s  %5.1f  %8.2f  %8.2f      ",
                  i, az, el_string, sig, dop, phase);
            }
            else if(ebolt) {
               sprintf(out, " %02d__  %5.1f  %s  %5.1f  %8.2f  %8.2f  %-4.2f",
                  i, az, el_string, sig, dop, phase, acc);
            }
            else {
               sprintf(out, " %02d__  %5.1f  %s  %5.1f  %8.2f  %8.2f  %s  _%-4.2f",
                  i, az, el_string, sig, dop, phase, bias_string, acc);
            }
         }
      #endif // VARIABLE_FONT

      #ifdef FIXED_FONT
         if(all_adevs) {
            if(ebolt) {
               sprintf(out, " %02d  %5.1f  %s %5.1f  %8.2f  %8.2f",
                  i, az, el_string, sig, dop, phase);
            }
            else {
               sprintf(out, " %02d  %5.1f  %s  %-4.1f  %s  %4.2f",
                  i, az, el_string, sig, bias_string, acc);
            }
         }
         else {
            if(res_t) {
               sprintf(out, " %02d  %5.1f  %s %5.1f  %8.2f  %8.2f       ",
                  i, az, el_string, sig, dop, phase);
            }
            else if(ebolt) {
               sprintf(out, " %02d  %5.1f  %s %5.1f  %8.2f  %8.2f  %-5.2f",
                  i, az, el_string, sig, dop, phase, acc);
            }
            else {
               sprintf(out, " %02d  %5.1f  %s %5.1f  %8.2f  %8.2f %s  %-5.2f",
                  i, az, el_string, sig, dop, phase, bias_string, acc);
            }
         }
      #endif  //FIXED_FONT

      if(sat[i].tracking <= 0) {
         vidstr(row++, col, YELLOW, out);
      }
      else {
         vidstr(row++, col, GREEN, out);
         this_const |= (1L << (i-1));
         ++sat_count;
      }

      len = strlen(out);
      if(len > max_len) max_len = len;
   }

   if(clock_count) clock_sum = (clock_sum * 1.0E9F) / clock_count;
   else            clock_sum = (float) pps_offset;

   print_using = 0;
   blank_underscore = 0;

   if(this_const != last_const) {
      new_const = (sat_count | CONST_CHANGE);
   }

   while(++j <= max_sats) {  // show spaces for unused satellites
      if(all_adevs && (j > 8)) break;  // only room for 8 sats here
      if((col < (TEXT_COLS/2)) && (row >= MOUSE_ROW)) break;
      #ifdef FIXED_FONT
         vidstr(row, col, WHITE, &blanks[TEXT_COLS-max_len]);
      #endif
      if(small_font == 1) vidstr(row, col, WHITE, "  ..");
      else                vidstr(row, col, WHITE, " ..");
      ++row;
   }
}

void format_lla(double lat, double lon,  double alt,  int row, int col)
{
u08 color;
char s[4];
double x;
int deg, min;
double sec;
char *lat_s, *lon_s, *alt_s;

   if(text_mode && first_key) return;
   if(zoom_screen && (zoom_lla == 0)) return;
   if(luxor) return;

   if((SCREEN_WIDTH <= 800) && (col > (TEXT_COLS/2))) {
      lat_s = "Lat:";
      lon_s = "Lon:";
      alt_s = "Alt:";
   }
   else {
      lat_s = "Lat: ";
      lon_s = "Lon: ";
      alt_s = "Alt: ";
   }

   color = WHITE;
   if(minor_alarms & 0x0200) color = YELLOW;
   else if(minor_alarms & 0x0020) {  // self-survey in progress
      color = YELLOW;
   }

   if(lat < 0.0) s[0] = s[2] = 'S';
   else          s[0] = s[2] = 'N';
   if(dms) s[1] = 0;
   else {
      s[0] = DEGREES;
      s[1] = ' ';
      s[3] = 0;
   }

   x = DABS(lat*RAD_TO_DEG);
   if(plot_loc == 0) sprintf(out, "%s              ", lon_s); // (double) (int) x;
   else if(dms) {
      deg = (int) x;
      min = (int) (60.0 * ((double) x - (double) deg));
      sec = ((x - (double) deg) - ((double) min / 60.0)) * 3600.0;
      sprintf(out, "%s%2d%c%02d'%06.3f\"%s", lat_s, deg, DEGREES, min, sec, s);
   }
   else sprintf(out, "%s%11.7lf%s", lat_s, x, s);
   vidstr(row+0, col, color, out);

   if(dms) {
      if(lon < 0.0) s[0] = 'W';
      else          s[0] = 'E';
   }
   else {
      if(lon < 0.0) s[2] = 'W';
      else          s[2] = 'E';
   }

   x = DABS(lon*RAD_TO_DEG);
   if(plot_loc == 0) sprintf(out, "%s              ", lon_s); // (double) (int) x;
   else if(dms) {
      deg = (int) x;
      min = (int) (60.0 * ((double) x - (double) deg));
      sec = ((x - (double) deg) - ((double) min / 60.0)) * 3600.0;
      sprintf(out, "%s%2d%c%02d'%06.3f\"%s", lon_s, deg, DEGREES, min, sec, s);
   }
   else sprintf(out, "%s%11.7lf%s", lon_s, x, s);
   vidstr(row+1, col, color, out);

   x = alt;
   if(plot_loc == 0) sprintf(out, "%s                ", alt_s);  // (double) (int) x;
   else if(alt >= 1000.0) {
      if(alt_scale[0] == 'f') sprintf(out, "%s%11.4lf'   ", alt_s, x*100.0/2.54/12.0);
      else                    sprintf(out, "%s%12.5lf m ", alt_s, x);
   }
   else {
      if(alt_scale[0] == 'f') sprintf(out, "%s%11.7lf'   ", alt_s, x*100.0/2.54/12.0);
      else                    sprintf(out, "%s%12.8lf m ", alt_s, x);
   }
   vidstr(row+2, col, color, out);
}

void show_lla()
{
   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;
   if(all_adevs && (all_adev_row < (ALL_ROW+5))) return;

   if(lat < (0.0-PI)) return;    // filter out any bogosity
   if(lat > PI) return;
   if(lon < (0.0-PI)) return;
   if(lon > PI) return;
   if(alt > 10000.0) return;
   if(alt < (0.0-1000.0)) return;

   // get a default precise position from the last self-surveyed coordinates
   if((have_initial_posn == 0) && (lla_log == 0)) {  
      precise_lat = lat;
      cos_factor = cos(precise_lat);
      precise_lon = lon;
      precise_alt = alt;
      if(rcvr_mode == 7) have_initial_posn = 1;
   }
   
   #ifdef PRECISE_STUFF
      if(lla_file && (gps_status == 0) && have_time && (precision_survey || show_fixes)) {
         fprintf(lla_file, "%-6lu %d %13.8lf  %13.8lf  %8.3lf\n", 
         (unsigned long) tow, gps_status, lat*RAD_TO_DEG, lon*RAD_TO_DEG, alt);
      }

      // user requested a precision survey from the command line
      if(have_initial_posn && have_time && user_precision_survey) {
         if(user_precision_survey == 1) {  // start precise survey
            user_precision_survey = 0;
            start_precision_survey();
         }
         else {  // start 3D fix mode
            user_precision_survey = 0;
            start_3d_fixes(4);
            config_screen();
            redraw_screen();
         }
      }
   #endif  // PRECISE_STUFF

   format_lla(lat, lon, alt,  POSN_ROW+1+eofs, POSN_COL);
}

void sig_levels()
{
u08 count;
u08 i;
u08 prn;
float sig_level;

// printf("Packet 47 (Signal levels):\n");

   for(i=1; i<=32; i++) {
      sat[i].level_msg = 0x00;
      if(log_db) sat[i].sig_level = 0;
   }

   count = tsip_byte();
   for(i=0; i<count; i++) {
      prn = tsip_byte();
      sig_level = tsip_single();
      if(prn > 32) prn = 0;  // put any bogus data in unused entry in array
      sat[prn].sig_level = sig_level;
      sat[prn].level_msg = 0x47;
   }
   tsip_end(1);
   if(tsip_error) return;
}


void get_alm_health()
{
int i;

// printf("Packet 49 (Almanac health page):\n");
   for(i=1; i<=32; i++) {
      sat[i].health_flag = tsip_byte();
   }
   tsip_end(1);
   if(tsip_error) return;
}

void single_lla_fix()
{
float lat, lon, alt;
float clock_bias;
float time_of_fix;

// printf("Packet 4A (LLA fix):\n");
   lat = tsip_single();
   lon = tsip_single();
   alt = tsip_single();
// sprintf(plot_title, "slla:%g %g %g", lat*RAD_TO_DEG,lon*RAD_TO_DEG, alt);
   clock_bias = tsip_single();
   time_of_fix = tsip_single();
   tsip_end(1);
   if(tsip_error) return;

// show_lla();
}

void ebolt_health2()
{
u08 id;
u08 rtc;
u08 superpackets;

// printf("Packet 4B (Tbolt-E health):\n");

   id = tsip_byte();
   rtc = tsip_byte();
   superpackets = tsip_byte();
   tsip_end(1);
   if(tsip_error) return;

   saw_version |= 0x08;
   saw_ebolt();
}

void io_options()
{
u08 posn;
u08 vel;
u08 timing;
u08 aux;

// printf("Packet 55 (I/O options):\n");

   posn = tsip_byte();
   vel = tsip_byte();
   timing = tsip_byte();
   aux = tsip_byte();
   if(aux & 0x08) {
      level_type = "dBc";
      amu_mode = 0;
   }
   else {
      level_type = "AMU";
      amu_mode = 1;
   }
   tsip_end(1);
   if(tsip_error) return;
}


void enu_velocity_fix()
{
float x_vel,y_vel,z_vel;
float bias_rate;
float time_of_fix;

// printf("Packet 56 (ENU velocity):\n");

   x_vel = tsip_single();
   y_vel = tsip_single();
   z_vel = tsip_single();
   bias_rate = tsip_single();
   time_of_fix = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
}


void last_fix_info()
{
u08 source_of_fix;
u08 tracking_mode;
float time_of_fix;
u16 week_of_fix;

// printf("Packet 57 (last fix info):\n");

   source_of_fix = tsip_byte();
   tracking_mode = tsip_byte();
   time_of_fix = tsip_single();
   week_of_fix = tsip_word();
   tsip_end(1);
   if(tsip_error) return;
}


void packet_58()
{
u08 op;
u08 type;
u08 prn;
u08 len;
u08 i;

double a0;
float a1;
short delta_ls;
float tot;
double wn_lsf;
unsigned short wnt;
unsigned short dn;
short delta_lsf;
double jd;

// printf("Packet 58 (GPS system data):\n");
   op = tsip_byte();
   type = tsip_byte();
   prn = tsip_byte();
   len = tsip_byte();

//sprintf(plot_title, "packet 58: op:%d  type:%d  prn:%d  len:%d", op,type,prn,len);

   if(type == 0x05) {  // UTC data
      for(i=4; i<=16; i++) {
         tsip_byte();
      }                      
      a0 = tsip_double();
      a1 = tsip_single();
      delta_ls = tsip_word();
      tot = tsip_single();
      wnt = tsip_word();
      wn_lsf = (double) (short) tsip_word();
      dn = tsip_word();
      delta_lsf = tsip_word();

      jd = jdate(1980, 1, 6);        // gps start time
      jd += (wn_lsf * 7.0) + (dn-1); // Julian day of leapsecond
jd += rollover / (1024.0 * 7.0 * 24.0 * 60.0 * 60.0);
      gregorian(jd);                 // Gregorian day of leapsecond

      jd -= jdate(year, month, day);
      jd -= jtime(hours, minutes, seconds);
      leap_days = (int) jd;  //!!!!dn + ((int) wn_lsf-gps_week)*7;
//    ++leap_days;

//sprintf(plot_title, "dls:%d  wnlsf:%g  dn:%d  dlsf:%d   wks:%d  days:%d  %d/%d/%d  jt:%g   ", 
//delta_ls, wn_lsf, dn, delta_lsf, (int) wn_lsf-gps_week, leap_days, g_year,g_month,g_day, jd);
   }
   else {
      for(i=0; i<len; i++) {   //!!! we should probably process this data
         tsip_byte();
      }
   }

   tsip_end(1);
   if(tsip_error) return;
}


void sat_health()
{
u08 op;
u08 vals[1+32];
u08 i;

// printf("Packet 59 (Sat disable/health):\n");

   op = tsip_byte();
   if(op == 3) {  // sat selection enabled / disabled
      for(i=1; i<=32; i++) sat[i].disabled = tsip_byte();
   }
   else if(op == 6) {  // sat selection enabled / disabled
      for(i=1; i<=32; i++) sat[i].forced_healthy = tsip_byte();
   }
   else {
      for(i=1; i<=32; i++) vals[i] = tsip_byte();
   }
   tsip_end(1);
   if(tsip_error) return;
}

void raw_data()
{
u08 prn;

// printf("Packet 5A (Raw measurement data):\n");

   prn = tsip_byte();
   if(prn > 32) prn = 0;  // put any bogus data in unused entry in array

   sat[prn].sample_len = tsip_single();
   if(log_db == 0) sat[prn].sig_level = tsip_single();
   else tsip_single();
   sat[prn].level_msg = 0x5A;
   sat[prn].code_phase = tsip_single();
   sat[prn].doppler = tsip_single();
   sat[prn].raw_time = tsip_double();
   tsip_end(1);
   if(tsip_error) return;
}

void eph_status()
{
u08 prn;

// printf("Packet 5B (Sat ephemeris status):\n");

   prn = tsip_byte();
   if(prn > 32) prn = 0;  // put any bogus data in unused entry in array

   sat[prn].eph_time = tsip_single();
   sat[prn].eph_health = tsip_byte();
   sat[prn].iode = tsip_byte();
   sat[prn].toe = tsip_single();
   sat[prn].fit_flag = tsip_byte();
   sat[prn].sv_accuracy = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
}

void sat_tracking(int extended_fmt)
{
u08 prn;
float el;

// printf("Packet 5C (Sat tracking):\n");
// also packet 5d
      
   prn = tsip_byte();
   if(prn > 32) prn = 0;  // put any bogus data in unused entry in array

   sat[prn].chan = tsip_byte();
   sat[prn].chan >>= 3;
   sat[prn].acq_flag = tsip_byte();
   sat[prn].eph_flag = tsip_byte();
   if(log_db == 0) sat[prn].sig_level = tsip_single();
   else            tsip_single();
   sat[prn].level_msg = 0x5C;
   sat[prn].time_of_week = tsip_single();

   el = tsip_single() * (float) RAD_TO_DEG;
   if(el > sat[prn].elevation) sat[prn].el_dir = UP_ARROW;
   else if(el < sat[prn].elevation) sat[prn].el_dir = DOWN_ARROW;
   sat[prn].elevation = el;

   sat[prn].azimuth = tsip_single() * (float) RAD_TO_DEG;
   sat[prn].age = tsip_byte();
   sat[prn].msec = tsip_byte();
   sat[prn].bad_flag = tsip_byte();
   sat[prn].collecting = tsip_byte();
   if(extended_fmt == 0x5D) {
      sat[prn].how_used = tsip_byte();
      sat[prn].sv_type = tsip_byte();
   }
   tsip_end(1);
   if(tsip_error) {
      sat[prn].level_msg = 0x00;
      return;
   }

#ifdef SIG_LEVELS
   if(sat[prn].level_msg != 0) { 
      if(sat[prn].sig_level > max_sat_db[prn]) {
         max_sat_db[prn] = sat[prn].sig_level;
      }
      if(sat[prn].sig_level > max_sig_level) {
         max_sig_level = sat[prn].sig_level;
      }
      if(reading_signals == 0) {
         log_signal(sat[prn].azimuth+0.5F, sat[prn].elevation+0.5F, sat[prn].sig_level, amu_mode);
      }
   }
#endif
}


void eeprom_status()
{
u08 flag;
u16 ee_status;

// printf("Packet 5F (EEPROM status):\n");

   flag = tsip_byte();
   if(flag == 0x11) {
      ee_status = tsip_word();
   }

   tsip_end(1);
   if(tsip_error) return;
}


void sat_list()
{
u08 dimension;
u08 count;
u08 i;
int prn;

// printf("Packet 6D (Satellite list):\n");

   dimension = count = tsip_byte();
   dimension &= 0x07;
   count >>= 4;

   pdop = tsip_single();
   if(pdop > 20.0) pdop = 20.0;

   hdop = tsip_single();
   if(hdop > 20.0) hdop = 20.0;

   vdop = tsip_single();
   if(vdop > 20.0) vdop = 20.0;

   tdop = tsip_single();
   if(tdop > 20.0) tdop = 20.0;

   for(i=1; i<=32; i++) {  // reset current tracking flags
      sat[i].tracking = 0;
   }

   for(i=0; i<count; i++) {
      prn = tsip_byte();
      if(prn & 0x80) {  // prn tracked,  but not used
         prn |= 0xFFFFFF00;
      }
      if(prn > 32) prn = 0;  // put any bogus data in unused entry in array
      else if(prn < (-32)) prn = 0;

      if(prn < 0) {
         sat[0-prn].tracking = prn;
      }
      else {  // prn is used in solution
         sat[prn].tracking = prn;
      }
   }
   tsip_end(1);
   if(tsip_error) return;
}



void show_filter_status()
{
int row;
int rows_avail;
int show_dops;
int show_filters;

   // This routine draws the filter settings,  dilution of precision,  
   // and elevation/signal level masks
   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;
   if(all_adevs && (SCREEN_WIDTH < 1280)) return;

   row = INFO_ROW;
   rows_avail = view_row - row + 1;

   if((all_adevs == 0) || (SCREEN_WIDTH >= 1280)) {
      if(rows_avail > (1+1+4+1)) {
         ++row;
         --rows_avail;
      }
      if(pps_enabled) {
         if(pps_rate & 0x80) {
            if(pps_polarity) sprintf(out, "PP2S: ON %c ", DOWN_ARROW);  //falling
            else             sprintf(out, "PP2S: ON %c ", UP_ARROW);    //rising
         }
         else {
            if(pps_polarity) sprintf(out, "PPS: ON %c ", DOWN_ARROW);  //falling
            else             sprintf(out, "PPS: ON %c ", UP_ARROW);    //rising
         }
         vidstr(row, INFO_COL, GREEN, out);
      }
      else {
         sprintf(out, "PPS: OFF ");
         vidstr(row, INFO_COL, YELLOW, out);
      }
      ++row;
      --rows_avail;
   }

   show_dops = 0;
   if(plot_dops || doing_survey || ((rcvr_mode != 7) && (rcvr_mode != 1) && have_rcvr_mode)) {
      if(rows_avail > 5) {
         ++row;
         --rows_avail;
      }
      if(rows_avail >= 4) {
         show_dops = row;
         rows_avail -= 4;
         row += 4;
      }
   }

   if(rows_avail > 7) show_filters = row+1;
   else if(rows_avail >= 4) show_filters = row;
   else show_filters = 0;

#ifdef VARIABLE_FONT
   if(show_dops) {
      sprintf(out, "PDOP: %5.2f  ", pdop);
      vidstr(show_dops+0, FILTER_COL, DOP_COLOR, out);
      sprintf(out, "HDOP: %5.2f  ", hdop);
      vidstr(show_dops+1, FILTER_COL, DOP_COLOR, out);
      sprintf(out, "VDOP: %5.2f  ", vdop);
      vidstr(show_dops+2, FILTER_COL, DOP_COLOR, out);
      sprintf(out, "TDOP: %5.2f  ", tdop);
      vidstr(show_dops+3, FILTER_COL, DOP_COLOR, out);
   }
   if(show_filters) {
      sprintf(out, "PV: %s      ", pv_filter?"ON ":"OFF");
      vidstr(show_filters+0, FILTER_COL, pv_filter?WHITE:YELLOW, out);
      sprintf(out, "STATIC: %s", static_filter?"ON ":"OFF");
      vidstr(show_filters+1, FILTER_COL, static_filter?WHITE:YELLOW, out);
      sprintf(out, "ALTITUDE: %s", alt_filter?"ON ":"OFF"); 
      vidstr(show_filters+2, FILTER_COL, alt_filter?WHITE:YELLOW, out);
      if(ebolt || saw_kalman_on) {
         sprintf(out, "KALMAN: %s", kalman_filter?"ON ":"OFF"); 
         vidstr(show_filters+3, FILTER_COL, kalman_filter?WHITE:YELLOW, out);
      }
      else {
         sprintf(out, "KALMAN: %s", kalman_filter?"ON ":"N/A"); 
         vidstr(show_filters+3, FILTER_COL, kalman_filter?YELLOW:GREY, out);
      }
      rows_avail -= 4;
      show_filters += 4;
   }
#endif  // VARIABLE_FONT

#ifdef FIXED_FONT
   if(show_dops) {
      sprintf(out, "PDOP: %5.2f  ", pdop);
      vidstr(show_dops+0, FILTER_COL, DOP_COLOR, out);
      sprintf(out, "HDOP: %5.2f  ", hdop);
      vidstr(show_dops+1, FILTER_COL, DOP_COLOR, out);
      sprintf(out, "VDOP: %5.2f  ", vdop);
      vidstr(show_dops+2, FILTER_COL, DOP_COLOR, out);
      sprintf(out, "TDOP: %5.2f  ", tdop);
      vidstr(show_dops+3, FILTER_COL, DOP_COLOR, out);
   }

   if(show_filters) {
      sprintf(out, "PV:      %s", pv_filter?"ON ":"OFF");
      vidstr(show_filters+0, FILTER_COL, pv_filter?WHITE:YELLOW, out);
      sprintf(out, "STATIC:  %s", static_filter?"ON ":"OFF");
      vidstr(show_filters+1, FILTER_COL, static_filter?WHITE:YELLOW, out);
      sprintf(out, "ALTITUDE:%s", alt_filter?"ON ":"OFF"); 
      vidstr(show_filters+2, FILTER_COL, alt_filter?WHITE:YELLOW, out);
      if(ebolt || saw_kalman_on) {
         sprintf(out, "KALMAN:  %s", kalman_filter?"ON ":"OFF"); 
         vidstr(show_filters+3, FILTER_COL, kalman_filter?WHITE:YELLOW, out);
      }
      else {
         sprintf(out, "KALMAN:  %s", kalman_filter?"ON ":"N/A"); 
         vidstr(show_filters+3, FILTER_COL, kalman_filter?YELLOW:GREY, out);
      }
      rows_avail -= 4;
      show_filters += 4;
   }
#endif  // FIXED_FONT

   if(rows_avail > 4) { ++show_filters; --rows_avail; }
   if((rows_avail >= 2) && (text_mode || (SCREEN_HEIGHT > 480))) {
      sprintf(out, "EL:  %6.2f%c", el_mask, DEGREES);
      vidstr(show_filters+0, FILTER_COL, WHITE, out);
      if(res_t == 2) sprintf(out, "dBc: %6.2f", amu_mask);
      else           sprintf(out, "AMU: %6.2f", amu_mask);
      vidstr(show_filters+1, FILTER_COL, WHITE, out);
      rows_avail -= 2;
   }
}


void filter_config()
{
// printf("Packet 70 (Filter config):\n");

   pv_filter = tsip_byte();
   static_filter = tsip_byte();
   alt_filter = tsip_byte();
   kalman_filter = tsip_byte();
   tsip_end(1);
   if(tsip_error) return;

   saw_version |= 0x80;
if(just_read) return;

   saw_kalman_on |= kalman_filter;
   show_filter_status();
}


void ecef_fix()
{
double clock_bias;
double fix_x,fix_y,fix_z;
float time_of_fix;

// printf("Packet 83 (XYZ ECEF):\n");

   fix_x = tsip_double();
   fix_y = tsip_double();
   fix_z = tsip_double();
   clock_bias = tsip_double();
   time_of_fix = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
}


void lla_fix()
{
double lat, lon, alt;
double clock_bias;
float time_of_fix;

// printf("Packet 84 (LLA fix):\n");

   lat = tsip_double();
   lon = tsip_double();
   alt = tsip_double();
   #ifdef PRECISE_STUFF
      precise_check();
   #endif
   clock_bias = tsip_double();
// sprintf(plot_title, "dlla:%g %g %g bias=%g", lat*RAD_TO_DEG,lon*RAD_TO_DEG, alt, clock_bias);
   time_of_fix = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
// show_lla();
}

void datums()
{
int index;
double dx;
double dy;
double dz;
double a_axis;
double ecc;

// printf("Packet 8F.15 (Datums):\n");

   index = tsip_word();
   dx = tsip_double();
   dy = tsip_double();
   dz = tsip_double();
   a_axis = tsip_double();
   ecc = tsip_double();
   tsip_end(1);
   if(tsip_error) return;
}



void fix_manuf_params()
{
   if(luxor) return;
   send_msg_start(0x8E);
   send_byte(0x41);
   send_word(0x1234);           //prefix
   send_dword(0x56789ABCL);     // sn
   send_byte(10);               // yr
   send_byte(1);    // mo
   send_byte(2);    //day
   send_byte(3);    // hr
   send_single(0.0F);    // build offset
   send_word(0);    // test code
   send_msg_end();

   save_segment(0xFF);
}


void show_serial_info()
{

   if(luxor) {
      if(usb_port == 9999)     sprintf(out, "Dev: %s", com_dev); 
      else if(usb_port == 999) sprintf(out, "Dev: %s", com_dev); 
      else if(usb_port)        sprintf(out, "USB: %d", usb_port);
      else if(com_port)        sprintf(out, "COM: %d", com_port);
#ifdef TCP_IP 
      else         sprintf(out," IP: %s", IP_addr); // TCP, no room for sernum
#else
      else         sprintf(out," COM: none");
#endif
      if(strlen(out) > 16) strcpy(&out[16-3],"...");   // don't hit 'Power' label
      vidstr(VER_ROW+5, VER_COL, WHITE, out);

      sprintf(out, "SER: %u.%04lu  ", sn_prefix, (unsigned long) serial_num);
   }
   else {
      if(usb_port == 9999)     sprintf(out, "Dev: %s", com_dev); // user specified device
      else if(usb_port == 999) sprintf(out, "Dev: %s", com_dev); // symlink to /dev/heather
      else if(usb_port >= 10)  sprintf(out, "Ser: %2u.%-8lu USB:%d",  sn_prefix, (unsigned long) serial_num, usb_port);
      else if(usb_port)        sprintf(out, "Ser: %2u.%-8lu  USB:%d", sn_prefix, (unsigned long) serial_num, usb_port);
      else if(com_port >= 10)  sprintf(out, "Ser: %2u.%-8lu COM:%d",  sn_prefix, (unsigned long) serial_num, com_port);
      else if(com_port)        sprintf(out, "Ser: %2u.%-8lu  COM:%d", sn_prefix, (unsigned long) serial_num, com_port);
#ifdef TCP_IP 
      else                    sprintf(out," IP: %s", IP_addr); // TCP, no room for sernum
#else
      else                    sprintf(out, "Ser: %2u.%-8lu  COM:none", sn_prefix, (unsigned long) serial_num);
#endif
      if (strlen(out) > 27) strcpy(&out[27-3],"...");   // don't hit 'Power' label
   }
   vidstr(VER_ROW+4, VER_COL, WHITE, out);
}

void manuf_params()
{
u16 test_code;
int sum;

// printf("Packet 8F.41 (Manufacturing Params):\n");

   sn_prefix = tsip_word();
   serial_num = tsip_dword();
   build_year = sum = tsip_byte();
   if(build_year > 80) build_year += 1900;
   else                build_year += 2000;
   build_month = tsip_byte();
   build_day = tsip_byte();
   build_hour = tsip_byte();
   build_offset = tsip_single();
   test_code = tsip_word();
   tsip_end(1);
   if(tsip_error) return;

   sum += sn_prefix + serial_num + test_code + build_month + build_day + build_hour;  // check for zeroed build params

   if((sum == 0) || ((build_month <= 12) &&
       (build_month != 0)  &&
       (build_day <= 31)  &&
       (build_day != 0)  &&
       (build_year >= 1980) &&
       (build_year <= 2080)  &&
       (build_hour <= 24)))
   {
      have_info |= MANUF_PARAMS;

      if(text_mode && first_key) return;
      if(zoom_screen) return;
      if(luxor) return;
      if(just_read) return;

      sprintf(out, "Mfg: %02d:00  %02d %s %04d", 
         build_hour, build_day, months[build_month], build_year);
      vidstr(VER_ROW+3, VER_COL, WHITE, out);
   }

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;
   if(just_read) return;

   show_serial_info();
}

void prodn_params()
{
u16 rsvd2;
u16 rsvd1;

// printf("Packet 8F.42 (Production Params):\n");

   prodn_options = tsip_byte();
   prodn_extn = tsip_byte();
   case_prefix = tsip_word();
   case_sn = tsip_dword();
   prodn_num = tsip_dword();
   rsvd1 = tsip_word();
   machine_id = tsip_word();
   rsvd2 = tsip_word();
   tsip_end(1);
   if(tsip_error) return;

   have_info |= PRODN_PARAMS;
}


void pps_settings()
{
u08 pps_rsvd;
float bias_threshold;

// printf("Packet 8F.4A (PPS settings):\n");

   pps_enabled = tsip_byte();
   pps_rsvd = tsip_byte();
   pps_polarity = tsip_byte();
   cable_delay = tsip_double();
   bias_threshold = tsip_single();
   tsip_end(1);
   if(tsip_error) return;

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;
if(just_read) return;

   saw_version |= 0x40;
   show_filter_status();

   if(1 || ((cable_delay >= 0.0) && (cable_delay < 10000.0))) {
      sprintf(out, "Dly:%11.6f ns", cable_delay/1.0E-9);
      vidstr(VAL_ROW+5, VAL_COL, WHITE, out);
   }
}


void dac_values()
{
u32 dac_value;
float dac_voltage;
u08 dac_res;
u08 dac_format;
float dac_min, dac_max;

// printf("Packet 8F.A0 (DAC values):\n");

   dac_value = tsip_dword();
   dac_voltage = tsip_single();
   dac_res = tsip_byte();
   dac_format = tsip_byte();
   dac_min = tsip_single();
   dac_max = tsip_single();
   tsip_end(1);
   if(tsip_error) return;
}


void osc_sense()
{  // not avilable on ThunderBolt-E or early ThunderBolts
// printf("Packet 8F.A1 (10 MHz sense):\n");

   osc_polarity = tsip_byte();
   tsip_end(1);
   if(tsip_error) return;
}


void get_timing_mode()
{
// printf("Packet 8F.A2 (Timing mode):\n");

   timing_mode = tsip_byte();
   tsip_end(1);
   if(tsip_error) return;
}


void packet_mask()
{
u16 mask1;
u16 mask2;

// printf("Packet 8F.A5 (Packet mask):\n");

   mask1 = tsip_word();
   mask2 = tsip_word();
   tsip_end(1);
   if(tsip_error) return;
}


void sat_solutions()
{   //not available on ThunderBolt-E
u08 format;
u32 time_of_week;
float clock_bias;
float clock_bias_rate;
float sat_bias;
u08 prn;
u08 i;

// printf("Packet 8F.A7 (Satellite solutions):\n");

   format = tsip_byte();
   time_of_week = tsip_dword();

   if(format == 0) {     // floating point
      clock_bias = tsip_single();
      clock_bias_rate = tsip_single();
   }
   else if(format == 1) {   // integer values
      clock_bias = (float) (int) tsip_word();
      clock_bias *= 100.0e-12F;
      clock_bias_rate = (float) (int) tsip_word();
      clock_bias_rate *= 1.0e-12F;
   }
   else {
      tsip_end(1);
      if(tsip_error) return;
      return;
   }

   for(i=1; i<=32; i++) {  // reset current bias flags
      sat[i].last_bias_msg = 0;
   }

   for(i=0; i<8; i++) {  // get bias info from all satellites
      prn = tsip_byte();
      if(prn > 32) prn = 0;  // put any bogus data in unused entry in array
      if(format == 0) {
         sat_bias = tsip_single();
      }
      else {
         sat_bias = (float) (int) tsip_word();
         sat_bias *= 100.0e-12F;
      }

      sat[prn].sat_bias = sat_bias;
      sat[prn].time_of_fix = (float) time_of_week;
      sat[prn].last_bias_msg = 1;
   }
   tsip_end(1);
   if(tsip_error) return;
}


void fmt_fp(int v1,int v2,int v3,int v4)
{
unsigned char v[4];

   v[3] = v1;
   v[2] = v2;
   v[1] = v3;
   v[0] = v4;
   sprintf(plot_title, "%02X:%02X:%02X:%02X -> %f", v1,v2,v3,v4, *((float *) (void *) &v));
}

void discipline_params()
{
u08 type;
float v1,v2,v3;
float v4,v5,v6,v7;
int osc_ok;

// printf("Packet 8F.A8 (Discipline params):\n");

   type = tsip_byte();

   if(type == 0) {
      v1 = tsip_single();
      v2 = tsip_single();
      if(saw_ntpx) {
         v3 = tsip_single();
         v4 = tsip_single();
         v5 = tsip_single();
//sprintf(plot_title, "v: %f %f %f %f %f      ", v1,v2,v3,v4,v5);
      } 
      else if(try_nortel & 0x01) {
         v3 = tsip_single();
         v4 = tsip_single();
         v5 = tsip_single();
         v6 = tsip_single();
         v7 = tsip_single();
      }
      tsip_end(1);
      if(tsip_error) {
         try_nortel ^= 0x01;
         request_discipline_params(0x00);
         return;
      }

      time_constant = v1;
      damping_factor = v2;
      if(saw_ntpx) {
         osc_gain = v3;
         min_volts = v4;
         max_volts = v5;
      }
      else if(try_nortel & 0x01) {
         osc_gain = v3;
         min_volts = v4;
         max_volts = v5;
         jam_sync = v6;
         max_freq_offset = v7;
         saw_nortel |= 0x01;
         if(user_set_temp_filter == 0) undo_fw_temp_filter = 0;
      }
      have_osc_params |= 0x01;
   }
   else if(type == 1) {
      v1 = tsip_single();
      v2 = tsip_single();
      v3 = tsip_single();
      if(try_nortel & 0x02) {
         v4 = tsip_single();
         v5 = tsip_single();
      }
      tsip_end(1);
      if(tsip_error) {
         try_nortel ^= 0x02;
         request_discipline_params(0x01);
         return;
      }
      if(pause_data) return;   // in case reading log file,  we don't want to change the OSC_GAIN
                               // since the user may be calculating osc parameters
      gain_color = WHITE;
      osc_gain = v1;
      min_volts = v2;
      max_volts = v3;
      if(try_nortel & 0x02) {
         jam_sync = v4;
         max_freq_offset = v5;
         saw_nortel |= 0x02;
         if(user_set_temp_filter == 0) undo_fw_temp_filter = 0;
      }
      have_osc_params |= 0x02;
   }
   else if(saw_ntpx) {  // packets 2,3,4 have no data
      tsip_end(1);
      if(tsip_error) return;
   }
   else if(type == 2) {
      v1 = tsip_single();
      v2 = tsip_single();
      tsip_end(1);
      if(tsip_error) return;

      jam_sync = v1;
      max_freq_offset = v2;
      have_osc_params |= 0x04;
   }
   else if(type == 3) {
      v1 = tsip_single();
      tsip_end(1);
      if(tsip_error) return;

      initial_voltage = v1;
      have_osc_params |= 0x08;
   }
   else if(type == 4) {     // undocumented - allowable dac range?
      v1 = tsip_single();
      v2 = tsip_single();
      tsip_end(1);
      if(tsip_error) return;
      min_dac_v = v1;
      max_dac_v = v2;
      have_osc_params |= 0x10;
   }
   else {
      tsip_end(1);
      if(tsip_error) return;
   }

   if((have_osc_params & 0x1F) == 0x1F) {  // !!!!! 0x0F: we have all osc params available
      osc_ok = 1;
   }
   else if(saw_ntpx && ((have_osc_params & 0x03) == 0x03)) {
      osc_ok = 1;
   }
   else osc_ok = 0;

   if(user_set_osc && osc_ok) {  // set osc params from command line values
      user_time_constant = time_constant;           // get current values
      user_damping_factor = damping_factor;
      user_osc_gain = osc_gain;
      user_min_volts = min_volts;
      user_max_volts = max_volts;
      user_min_range = min_dac_v;
      user_max_range = max_dac_v;
      user_jam_sync = jam_sync;
      user_max_freq_offset = max_freq_offset;
      user_initial_voltage = initial_voltage;

      // update current values with user set values from command line
      if(user_set_osc & 0x01) user_time_constant = cmd_tc;
      if(user_set_osc & 0x02) user_damping_factor = cmd_damp;
      if(user_set_osc & 0x04) user_osc_gain = cmd_gain;
      if(user_set_osc & 0x08) user_initial_voltage = cmd_dac;
      if(user_set_osc & 0x10) user_min_volts = cmd_minv;
      if(user_set_osc & 0x20) user_max_volts = cmd_maxv;
      user_set_osc = 0;

      set_discipline_params(0);
   }
}

void survey_params()
{
u08 survey_flag;
u32 rsvd;

// printf("Packet 8F.A9 (Survey params):\n");

   survey_flag = tsip_byte();
   survey_save = tsip_byte();
   survey_length = tsip_dword();
   rsvd = tsip_dword();
   tsip_end(1);
   if(tsip_error) return;
}

unsigned long last_pl;

void show_time_info()
{
int color;
u08 alarm_state;
long sec;

   if((text_mode && first_key) || zoom_screen || luxor) { // screen in use for help/edit info
      time_set_char = ' ';
      return;
   }

   if(alarm_time || alarm_date || egg_timer) alarm_state = ALARM_CHAR;
   else if(dump_time || dump_date || dump_timer || log_time || log_date || log_timer) {
      if(single_dump || single_log) alarm_state = '!';         //!!!!! need separate flags for screen and log dumps
      else                          alarm_state = DUMP_CHAR;
   }
   else if(cuckoo) {
      if(singing_clock) alarm_state = SONG_CHAR;
      else alarm_state = CHIME_CHAR;
   }
   else alarm_state = ' ';

   if(time_set_char != ' ') {
      sprintf(out, "Time synced %c  ", alarm_state);
      vidstr(TIME_ROW+0, TIME_COL, GREEN, out);
   }
   else if(time_flags & 0x04) {
      sprintf(out, "NO time avail %c", alarm_state);
      vidstr(TIME_ROW+0, TIME_COL, RED, out);
      time_color = RED;
   }
   else if(time_flags & 0x08) {
      sprintf(out, "NO UTC offset %c", alarm_state);
      vidstr(TIME_ROW+0, TIME_COL, RED, out);
      time_color = YELLOW;
   }
   else if(time_flags & 0x10) {
      sprintf(out, "USER set time %c", alarm_state);
      vidstr(TIME_ROW+0, TIME_COL, YELLOW, out);
      time_color = YELLOW;
   }
   else if(time_flags & 0x01) { 
      sprintf(out, "UTC time OK %c  ", alarm_state);
      vidstr(TIME_ROW+0, TIME_COL, GREEN,  out);
      if(dst_ofs)            time_color = DST_TIME_COLOR;
      else if(time_zone_set) time_color = DST_TIME_COLOR;  // !!! std_time_color is rather dim for the big clock
      else                   time_color = WHITE;
   }
   else {
      sprintf(out, "GPS time OK %c  ", alarm_state);
      vidstr(TIME_ROW+0, TIME_COL, GREEN,  out);
      if(dst_ofs)            time_color = DST_TIME_COLOR;
      else if(time_zone_set) time_color = DST_TIME_COLOR;  // !!! std_time_color is rather dim for the big clock
      else                   time_color = WHITE;
   }

   if(time_color != last_time_color) {  // redraw big clock if time status has changed
      last_time_color = time_color;
      reset_vstring();
   }

   if(seconds > 59) write_log_leapsecond();
   else if((seconds == 0) && (last_second == 0)) write_log_leapsecond();
   last_second = seconds;

   if((last_utc_offset != 0x8000) && (utc_offset != last_utc_offset)) {
      write_log_utc(utc_offset);
   }
   last_utc_offset = utc_offset;


   color = WHITE;
   if(sound_alarm && (ticker & 0x01)) color = RED;

   if(seconds_time || fraction_time) {
      sec  = (long) pri_hours * 3600L;
      sec += (long) pri_minutes * 60L;
      sec += (long) pri_seconds;
      if(fraction_time) {
         sec *= 1000L;
         sec /= 864L;
         sprintf(out, "%s: .%05ld", 
            time_zone_set?tz_string:(time_flags&0x01)?"UTC":"GPS", sec);
      }
      else {
         sprintf(out, "%s:  %05ld", 
            time_zone_set?tz_string:(time_flags&0x01)?"UTC":"GPS", sec);
      }
      if(dst_ofs)            vidstr(TIME_ROW+2,TIME_COL, DST_TIME_COLOR, out);
      else if(time_zone_set) vidstr(TIME_ROW+2,TIME_COL, STD_TIME_COLOR, out);
      else                   vidstr(TIME_ROW+2,TIME_COL, WHITE, out);
      strcpy(out, fmt_date(0));
      vidstr(TIME_ROW+1,TIME_COL, color, out);
   }
   else {
      sprintf(out, "%02d:%02d:%02d %s", pri_hours,pri_minutes,pri_seconds, 
         time_zone_set?tz_string:(time_flags&0x01)?"UTC":"GPS");
      if(dst_ofs)            vidstr(TIME_ROW+1,TIME_COL, DST_TIME_COLOR, out);
      else if(time_zone_set) vidstr(TIME_ROW+1,TIME_COL, STD_TIME_COLOR, out);
      else                   vidstr(TIME_ROW+1,TIME_COL, WHITE, out);
      strcpy(out, fmt_date(0));
      vidstr(TIME_ROW+2,TIME_COL, color, out);
   }
   

   if(rolled) sprintf(out, "Week: %5uro", (unsigned) gps_week);
   else       sprintf(out, "Week: %5u  ", (unsigned) gps_week);
//sprintf(out, "%5lu", pl_counter-last_pl);
//last_pl = pl_counter;
   vidstr(TIME_ROW+3,TIME_COL, color, out);
   sprintf(out, "TOW:%7lu  ", (unsigned long) tow);
   vidstr(TIME_ROW+4,TIME_COL, color, out);
   sprintf(out, "UTC ofs:%3d", utc_offset);
   vidstr(TIME_ROW+5,TIME_COL, color, out);

   time_set_char = ' ';
   return;
}


void primary_misc()
{
   if(1 || osc_params || plot_azel || plot_watch || (log_db && log_file) || need_posns) {
      if(need_posns || (log_db && log_file) || (pri_seconds == SUN_SECOND))  {
         sun_posn();   // calculate the sun's position
      }
      if(need_posns || (log_db && log_file) || (pri_seconds == MOON_SECOND)) {
         moon_posn();  // calculate the moon's position
      }
      if(need_posns > 0) --need_posns;
   }

   have_time = 1;
   if(have_year != year) {    // it's the first valid year we have seen or year has changed
      have_year = year;
      init_dsm();             // tweek month tables for possible leap year
      calc_dst_times(dst_list[dst_area]);  // find daylight savings change times
   }                                       // and recalculate the seasons, etc

   ticker ^= 1;               // used to flash the alarm on the screen
   adjust_tz();               // tweak pri_ time for time zone and daylight savings time
//sun_posn();

// SetDtrLine(1);
   set_cpu_clock();           // set system clock to receiver time

   #ifdef GREET_STUFF
      if(new_moon_info || (pri_day != last_day)) {   // calculate new moon info for the month
         if(new_moon_info || (pri_seconds == MOON_STUFF)) {
            calc_moons(pri_year, pri_month);
            last_day = pri_day;
            new_moon_info = 0;
         }
      }
   #endif

   check_end_times();         // exit program at preset time
   silly_clocks();            // do alarm clock and cuckoo clock
   show_satinfo();            // show satellite info
   draw_maps();               // draw maps and analog watch

   if(time_flags != last_time_flags) {  // redo big clock if time settings have changed
      sync_log_file();        // time reference changed,  note it in the log file
      reset_vstring();
      last_time_flags = time_flags;
   }

   if(time_flags & 0x01) {  // we are in UTC mode
      if(set_gps_mode) set_timing_mode(0x00);
      set_utc_mode = set_gps_mode = 0;
   }
   else { // we are in GPS mode
      if(set_utc_mode) set_timing_mode(0x03);
      set_utc_mode = set_gps_mode = 0;
   }

   show_time_info();          // draw primary timing data
   if(configed_mode == 5) {   // secondary timing not available in DGPS mode
      refresh_page();
   }
// SetDtrLine(0);
}

void primary_timing()
{
int i;
double jd;

// printf("Packet 8F.AB (Primary timing):\n");

   pri_tow = tsip_dword();
   gps_week = tsip_word();
   utc_offset = tsip_word();
   time_flags = tsip_byte();
   pri_seconds = tsip_byte();
   pri_minutes = tsip_byte();
   pri_hours = tsip_byte();
   pri_day = tsip_byte();
   pri_month = tsip_byte();
   pri_year = tsip_word();
   pri_frac = 0.0;
   rolled = 0;
   tsip_end(1);

   if(pri_seconds == 60) leap_time = 1;
   else                  leap_time = 0;

   if(force_day) {
      pri_day = force_day;
      pri_month = force_month;
      pri_year = force_year;
   }

   if(user_set_rollover) ;               // user forced a rollover offset
//else if(tsip_error) ;
   else if(pri_year < ROLLOVER_YEAR) {   // GPS year looks bogus
      if((time_flags & 0x08) == 0) {     // and GPS time is valid
         rollover = 1024.0 * 7.0 * 24.0 * 60.0 * 60.0;  // rollover one 1024 week epoch
//sprintf(debug_text, "rollover: year:%d/%02d/%02d  %02d:%02d:%02d  roy:%d  err:%04X", 
//pri_year,pri_month,pri_day, pri_hours,pri_minutes,pri_seconds, ROLLOVER_YEAR, tsip_error);
      }
   }

   if(rollover || user_set_rollover) {  // adjust GPS receiver time by xxx seconds
      jd = ((double) pri_hours * 60.0 * 60.0) + ((double) pri_minutes * 60.0) + (double) pri_seconds;  // time in seconds
jd += 0.50;   // !!! round jtime 
      jd /= (24.0 * 60.0 * 60.0);       // convert seconds to days
      jd += jdate(pri_year, pri_month, pri_day);
      gregorian(jd + rollover/(24.0 * 60.0 * 60.0));
      pri_year = g_year;
      pri_month = g_month;
      pri_day = g_day;
      pri_hours = g_hours;
      pri_minutes = g_minutes;
      pri_seconds = g_seconds;
      pri_frac = g_frac;
      rolled = 1;
   }

   if(murray) {
      request_primary_timing();
   }
   if(log_db) request_sig_levels();

   if(user_pps_len) {  // send string of user specified bytes each time a timing message is received
      for(i=0; i<user_pps_len; i++) sendout(user_pps_cmd[i]);
   }
   if(murray) {
      if(seconds == pri_seconds) return;
   }

   if(tsip_error) return;
if(just_read) return;

   // filter bogus time values
   if(pri_tow > (60L*60L*24L*7L+1L)) { write_log_error(0x02, pri_tow);     return; } 
   if(pri_seconds > 61)              { write_log_error(0x03, pri_seconds); return; } 
   if(pri_minutes > 60)              { write_log_error(0x04, pri_minutes); return; } 
   if(pri_hours > 24)                { write_log_error(0x05, pri_hours); return; }   // accomodate weird leap seconds
   if(pri_day == 0)                  { write_log_error(0x06, pri_day);   return; } 
   if(pri_day > 31)                  { write_log_error(0x07, pri_day);   return; } 
   if(pri_month == 0)                { write_log_error(0x08, pri_month); return; } 
   if(pri_month > 12)                { write_log_error(0x09, pri_month); return; } 
   if(pri_year < 2009)               { write_log_error(0x00, pri_year);  return; } 
   if(pri_year > 2100)               { write_log_error(0x0B, pri_year);  return; }

   // the time message seems to have valid time
   seconds = pri_seconds;     // save GPS/UTC time and date in global variables
   minutes = pri_minutes;
   hours = pri_hours;
   day = pri_day;
   month = pri_month;
   year = pri_year;
   tow = this_tow = pri_tow;  

   primary_misc();

   if(leap_time && leap_dump) {  // do screen dump if leap-second seen
      refresh_page();
      leap_time = 0;
      dump_screen(0, 0, "LEAP_SEC");
   }
}


void show_survey_info()
{
int color;

   if(luxor) return;

   if(minor_alarms & 0x0020) {   // self survey is active
      vidstr(SURVEY_ROW+0+eofs, SURVEY_COL, RED,    "Self Survey:  ");
      color = YELLOW;
   }
   else if(precision_survey) {
      vidstr(SURVEY_ROW+0+eofs, SURVEY_COL, RED,    "Median Survey:");
      color = YELLOW;
   }
   else {  // not in survey mode,  grey out this info on the screen
      if(res_t || res_t_init) {  // show survey info
         color = GREY;
         vidstr(SURVEY_ROW+0+eofs, SURVEY_COL, color,  "Survey data:  ");
      }
      else {   // show osc info
        sprintf(out, "TC:   %.1f sec", time_constant);
        vidstr(SURVEY_ROW+0+eofs, SURVEY_COL, WHITE, out);
        sprintf(out, "DAMP: %.3f", damping_factor);
        vidstr(SURVEY_ROW+1+eofs, SURVEY_COL, WHITE, out);
        if(osc_gain < 0.0F)       sprintf(out, "GAIN:%.3f Hz/V ", osc_gain);
        else if(osc_gain > 10.0F) sprintf(out, "GAIN:%.3f Hz/V ", osc_gain);
        else                      sprintf(out, "GAIN: %.3f Hz/V ", osc_gain);
        vidstr(SURVEY_ROW+2+eofs, SURVEY_COL, gain_color, out);
        sprintf(out, "INIT: %.3f V", initial_voltage);
        if(saw_ntpx) vidstr(SURVEY_ROW+3+eofs, SURVEY_COL, GREY,  out);
        else         vidstr(SURVEY_ROW+3+eofs, SURVEY_COL, WHITE, out);
        return;
      }
   }

   if((survey_length >= 0) && (survey_length <= 100000L)) {
      if(precision_survey) sprintf(out, "Samples:%5lu", (unsigned long) precision_samples);
      else sprintf(out, "Samples:%5ld", survey_length);
      vidstr(SURVEY_ROW+1+eofs, SURVEY_COL, color, out);
   }

   if((survey_progress >= 0) && (survey_progress <= 100)) {
      if(precision_survey) sprintf(out, "Progress:%3ld%%", (survey_minutes*99L)/((long)PRECISE_SURVEY_HOURS*60L)+1L);
      else                 sprintf(out, "Progress:%3d%%", survey_progress);
      vidstr(SURVEY_ROW+2+eofs, SURVEY_COL, color, out);
   }

   if(precision_survey || check_precise_posn || survey_done) {
   }
   else {
      if(survey_save) vidstr(SURVEY_ROW+3+eofs, SURVEY_COL, color, "Save position");
      else            vidstr(SURVEY_ROW+3+eofs, SURVEY_COL, color, "Dont save pos");
   }
}

void show_minor_alarms()
{
int bad_mask;
char s[80];

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;

   // minor alarm info
   if(minor_alarms & 0x0400)  vidstr(MINOR_ROW+0, MINOR_COL, RED,        "EEPROM BAD   ");
   else                       vidstr(MINOR_ROW+0, MINOR_COL, GREEN,      "EEPROM  OK   ");

   if     (minor_alarms & 0x0002)  vidstr(MINOR_ROW+1, MINOR_COL, YELLOW,"Antenna open  ");
   else if(minor_alarms & 0x0004)  vidstr(MINOR_ROW+1, MINOR_COL, RED,   "Antenna short ");
   else                            vidstr(MINOR_ROW+1, MINOR_COL, GREEN, "Antenna OK    ");

   if(minor_alarms & 0x0800)  vidstr(MINOR_ROW+2, MINOR_COL, YELLOW,     "No almanac   ");
   else                       vidstr(MINOR_ROW+2, MINOR_COL, GREEN,      "Almanac OK   ");
   if(minor_alarms & 0x0010)  {
      if(res_t || res_t_init) vidstr(MINOR_ROW+3, MINOR_COL, RED,        "Unk alarm 0x10");
      else if(osc_control_on) vidstr(MINOR_ROW+3, MINOR_COL, OSC_PID_COLOR, "Ext osc ctrl  ");
      else                    vidstr(MINOR_ROW+3, MINOR_COL, RED,        "Undisciplined ");
   }
   else if(res_t || res_t_init) {
                              vidstr(MINOR_ROW+3, MINOR_COL, GREEN,      "              ");
   }
   else                       vidstr(MINOR_ROW+3, MINOR_COL, GREEN,      "Discipline OK ");
   if(minor_alarms & 0x0200)  vidstr(MINOR_ROW+4, MINOR_COL, RED,        "Saved posn BAD");
   else                       vidstr(MINOR_ROW+4, MINOR_COL, GREEN,      "Saved posn OK ");
   if(minor_alarms & 0x0008)  vidstr(MINOR_ROW+5, MINOR_COL, RED,        "No sats usable");
   else                       vidstr(MINOR_ROW+5, MINOR_COL, GREEN,      "Tracking sats ");
   if(minor_alarms & 0x0040)  vidstr(MINOR_ROW+6, MINOR_COL, RED,        "No saved posn ");
   else                       vidstr(MINOR_ROW+6, MINOR_COL, GREEN,      "Position saved");
         
   if(leap_days >= 365)      sprintf(s, "LEAP: PENDING!");
   else if(leap_days >= 100) sprintf(s, "LEAP: %3u days", leap_days);
   else if(leap_days >= 10)  sprintf(s, "LEAP: %2u days ", leap_days);
   else if(leap_days >= 2)   sprintf(s, "LEAP: %1u days  ", leap_days);
   else if(leap_days >= 1)   sprintf(s, "LEAP: %1u day   ", leap_days);
   else                      sprintf(s, "LEAP: PENDING!");
   if(minor_alarms & 0x0080)  vidstr(MINOR_ROW+7, MINOR_COL, YELLOW,     s);
   else                       vidstr(MINOR_ROW+7, MINOR_COL, GREEN,      "No leap second");
   if(minor_alarms & 0x0100)  vidstr(MINOR_ROW+8, MINOR_COL, RED,        "Cal mode set ");
   else                       vidstr(MINOR_ROW+8, MINOR_COL, GREEN,      "Normal op mode");

   if(res_t) {
      if(minor_alarms & 0x0001)  vidstr(MINOR_ROW+9, MINOR_COL, RED,     "Unk alarm 0x01");
      else                       vidstr(MINOR_ROW+9, MINOR_COL, GREEN,   "              ");
   }
   else {
      if(minor_alarms & 0x0001)  vidstr(MINOR_ROW+9, MINOR_COL, RED,     "OSC age alarm ");
      else                       vidstr(MINOR_ROW+9, MINOR_COL, GREEN,   "Normal OSC age");
   }

   if((SCREEN_HEIGHT >= 768) || (small_font && (SCREEN_HEIGHT > 600))) { // windows uses small font,  so this fits in 800x600 mode
      if(res_t) {
         if(pps_rate & 0x80) {
            if(minor_alarms & 0x1000)  vidstr(MINOR_ROW+10, MINOR_COL, GREEN,      "PP2S: skipped  ");
            else                       vidstr(MINOR_ROW+10, MINOR_COL, GREEN,      "PP2S: generated");
         }
         else {
            if(minor_alarms & 0x1000)  vidstr(MINOR_ROW+10, MINOR_COL, YELLOW,     "PPS: skipped   ");
            else                       vidstr(MINOR_ROW+10, MINOR_COL, GREEN,      "PPS: generated ");
         }
         bad_mask = 0xE000;
      }
      else bad_mask = 0xF000;

      if(minor_alarms & bad_mask)  {
         sprintf(out, "Alarm?: %04X  ",  minor_alarms&0xF000);
         vidstr(MINOR_ROW+10, MINOR_COL, RED,   out);
      }
      else {
///!!!!  vidstr(MINOR_ROW+10, MINOR_COL, WHITE,   "              ");
      }
   }
}

void show_alarm_info()
{
int color;

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;

   // receiver mode and position
   if     (rcvr_mode == 0) vidstr(POSN_ROW+0+eofs,POSN_COL, YELLOW, "2D/3D positioning        ");
   else if(rcvr_mode == 1) vidstr(POSN_ROW+0+eofs,POSN_COL, YELLOW, "Single satellite         ");
   else if(rcvr_mode == 3) vidstr(POSN_ROW+0+eofs,POSN_COL, YELLOW, "2D positioning           ");
   else if(rcvr_mode == 4) vidstr(POSN_ROW+0+eofs,POSN_COL, YELLOW, "3D positioning           ");
   else if(rcvr_mode == 5) vidstr(POSN_ROW+0+eofs,POSN_COL, YELLOW, "DGPS reference           ");
   else if(rcvr_mode == 6) vidstr(POSN_ROW+0+eofs,POSN_COL, YELLOW, "2D clock hold            ");
   else if(rcvr_mode == 7) vidstr(POSN_ROW+0+eofs,POSN_COL, GREEN,  "Overdetermined clock");
   else {
      sprintf(out, "Receiver mode ?%02X?  ", rcvr_mode);
      vidstr(POSN_ROW+0+eofs,POSN_COL, RED, out);
   }
   if(rcvr_mode == 7) fix_mode = 0;
   else               fix_mode = 1;

   show_lla();           // lat/lon/alt info
   show_survey_info();   // self survey info

   // Oscillator disciplining info
   if(res_t) vidstr(DIS_ROW+0+eofs, DIS_COL, WHITE, "Operation mode: ");
   else      vidstr(DIS_ROW+0+eofs, DIS_COL, WHITE, "Discipline mode:");
   if     (discipline_mode == 0) vidstr(DIS_ROW+1+eofs, DIS_COL, GREEN,  "Normal          ");
   else if(discipline_mode == 1) vidstr(DIS_ROW+1+eofs, DIS_COL, YELLOW, "Power-up        ");
   else if(discipline_mode == 2) vidstr(DIS_ROW+1+eofs, DIS_COL, RED,    "Auto holdover   ");  // this could be a YELLOW alert
   else if(discipline_mode == 3) vidstr(DIS_ROW+1+eofs, DIS_COL, YELLOW, "Manual holdover ");
   else if(discipline_mode == 4) vidstr(DIS_ROW+1+eofs, DIS_COL, YELLOW, "Recovery        ");
   else if(discipline_mode == 5) vidstr(DIS_ROW+1+eofs, DIS_COL, YELLOW, "Fast recovery   ");
   else if(discipline_mode == 6) {
      if(osc_control_on) vidstr(DIS_ROW+1+eofs, DIS_COL, OSC_PID_COLOR,  "External        ");
      else               vidstr(DIS_ROW+1+eofs, DIS_COL, RED,            "Disabled        ");
   }
   else {
      if(res_t) sprintf(out, "Operation ?%02X?  ", discipline_mode);
      else      sprintf(out, "Discipline ?%02X? ", discipline_mode);
      vidstr(DIS_ROW+1+eofs, DIS_COL, YELLOW, out);
   }

   sprintf(out, "Holdover: %lu secs            ", (unsigned long) holdover);
   out[20] = 0;
   if((discipline_mode == 2) || (discipline_mode == 3)) {
      color = RED;
      holdover_seen = 1;
   }
   else if(holdover_seen) color = YELLOW;
   else color = GREEN;
   vidstr(DIS_ROW+2+eofs, DIS_COL, color, out);
   if     (gps_status == 0x00) vidstr(DIS_ROW+3+eofs, DIS_COL, GREEN,  "Doing fixes     ");
   else if(gps_status == 0x01) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "No GPS time     ");
   else if(gps_status == 0x03) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "PDOP too high   ");
   else if(gps_status == 0x08) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "No usable sats  ");
   else if(gps_status == 0x09) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "1 usable sat    ");
   else if(gps_status == 0x0A) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "2 usable sats   ");
   else if(gps_status == 0x0B) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "3 usable sats   ");
   else if(gps_status == 0x0C) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "sat unusable    ");
   else if(gps_status == 0x10) vidstr(DIS_ROW+3+eofs, DIS_COL, RED,    "TRAIM rejected  ");
   else {
      sprintf(out, "GPS status:?%02X? ", gps_status);
      vidstr(DIS_ROW+3+eofs, DIS_COL, YELLOW, out);
   }
}

void show_param_values()
{
u08 c;
float val;

   if(text_mode && first_key) return;
   if(zoom_screen) return;
   if(luxor) return;

   if((all_adevs == 0) || ((TEXT_HEIGHT <= 12) && (SCREEN_WIDTH >= 1280))) {
      show_alarm_info();
      show_minor_alarms();
   }
   else if(all_adevs) {
      if(SCREEN_WIDTH >= 1280) show_minor_alarms();
      if(all_adev_row >= (ALL_ROW+5)) show_alarm_info();
   }

   if(CRIT_ROW) vidstr(CRIT_ROW-1, CRIT_COL, WHITE, "Status:");
#ifdef VARIABLE_FONT
   if(critical_alarms & 0x0001)  vidstr(CRIT_ROW+0, CRIT_COL, RED,   "ROM: BAD");
   else                          vidstr(CRIT_ROW+0, CRIT_COL, GREEN, "ROM: OK ");
   if(critical_alarms & 0x0002)  vidstr(CRIT_ROW+1, CRIT_COL, RED,   "RAM: BAD");
   else                          vidstr(CRIT_ROW+1, CRIT_COL, GREEN, "RAM: OK ");
   if(critical_alarms & 0x0010)  vidstr(CRIT_ROW+2, CRIT_COL, RED,   "OSC: BAD");
   else                          vidstr(CRIT_ROW+2, CRIT_COL, GREEN, "OSC: OK ");
   if(critical_alarms & 0x0008)  vidstr(CRIT_ROW+3, CRIT_COL, RED,   "FPGA: BAD");
   else                          vidstr(CRIT_ROW+3, CRIT_COL, GREEN, "FPGA: OK ");
   if(critical_alarms & 0x0004)  vidstr(CRIT_ROW+4, CRIT_COL, RED,   "Power: BAD");
   else                          vidstr(CRIT_ROW+4, CRIT_COL, GREEN, "Power: OK ");
#endif  // VARIABLE_FONT
#ifdef FIXED_FONT
   if(critical_alarms & 0x0001)  vidstr(CRIT_ROW+0, CRIT_COL, RED,   "ROM:   BAD");
   else                          vidstr(CRIT_ROW+0, CRIT_COL, GREEN, "ROM:    OK");
   if(critical_alarms & 0x0002)  vidstr(CRIT_ROW+1, CRIT_COL, RED,   "RAM:   BAD");
   else                          vidstr(CRIT_ROW+1, CRIT_COL, GREEN, "RAM:    OK");
   if(critical_alarms & 0x0010)  vidstr(CRIT_ROW+2, CRIT_COL, RED,   "OSC:   BAD");
   else                          vidstr(CRIT_ROW+2, CRIT_COL, GREEN, "OSC:    OK");
   if(critical_alarms & 0x0008)  vidstr(CRIT_ROW+3, CRIT_COL, RED,   "FPGA:  BAD");
   else                          vidstr(CRIT_ROW+3, CRIT_COL, GREEN, "FPGA:   OK");
   if(critical_alarms & 0x0004)  vidstr(CRIT_ROW+4, CRIT_COL, RED,   "Power: BAD");
   else                          vidstr(CRIT_ROW+4, CRIT_COL, GREEN, "Power:  OK");
#endif  // FIXED_FONT


   if(res_t && unit_name[0]) vidstr(VAL_ROW+0, VAL_COL, GREEN,  unit_name); 
   else if(res_t)            vidstr(VAL_ROW+0, VAL_COL, GREEN,  "Resolution-T    "); 
   else if(discipline == 0)  vidstr(VAL_ROW+0, VAL_COL, GREEN,  "Phase locked    ");
   else if(discipline == 1)  vidstr(VAL_ROW+0, VAL_COL, YELLOW, "Warming up      ");
   else if(discipline == 2)  vidstr(VAL_ROW+0, VAL_COL, YELLOW, "Freq locking    ");
   else if(discipline == 3)  vidstr(VAL_ROW+0, VAL_COL, YELLOW, "Placing PPS     ");
   else if(discipline == 4)  vidstr(VAL_ROW+0, VAL_COL, YELLOW, "Filter init     ");
   else if(discipline == 5)  vidstr(VAL_ROW+0, VAL_COL, YELLOW, "OCXO comp       ");
   else if(discipline == 6) {
      if(osc_control_on) vidstr(VAL_ROW+0, VAL_COL, OSC_PID_COLOR, "Discipline EXTERNAL  ");
      else               vidstr(VAL_ROW+0, VAL_COL, RED,           "Discipline OFF       ");
   }
   else if(discipline == 8) vidstr(VAL_ROW+0, VAL_COL, YELLOW, "Recovery mode   ");
   else {
      sprintf(out, "Discipline: %02X", discipline);
      vidstr(VAL_ROW+0, VAL_COL, RED, out);
   }

   if(res_t) sprintf(out, "Corr:%10.6f ns  ", dac_voltage);  // pps_quant);
   else      sprintf(out, "DAC:%11.6f V   ", dac_voltage);
   if     (critical_alarms & 0x0010) vidstr(VAL_ROW+2, VAL_COL, RED,    out);
   else if(minor_alarms & 0x0001)    vidstr(VAL_ROW+2, VAL_COL, YELLOW, out);
   else                              vidstr(VAL_ROW+2, VAL_COL, WHITE,  out);

   if((temperature > (-100.0)) && (temperature < 100.0)) {
      sprintf(out, "Temp: %s%c   ", fmt_temp(temperature), temp_dir);
      if((temperature < 0.0F) || (temperature >= 60.0F))  vidstr(VAL_ROW+2, VAL_COL, RED, out);
      else if((temperature < 10.0F) || (temperature >= 50.0F)) vidstr(VAL_ROW+2, VAL_COL, YELLOW, out);
      else vidstr(VAL_ROW+1, VAL_COL, WHITE, out);
   }
   else {
      sprintf(out, "Temp: %s%c   ", fmt_temp(temperature), temp_dir);
      vidstr(VAL_ROW+1, VAL_COL, RED, out);
   }


   if(luxor) {
      sprintf(out, "PPS%c%11.6f V     ", pps_polarity?DOWN_ARROW:UP_ARROW, (float) pps_offset);
   }
   else if(res_t) {
      sprintf(out, "Bias:%10.6f us    ", (float) (pps_offset/1000.0));
   }
   else {
      sprintf(out, "PPS%c%11.6f ns    ", pps_polarity?DOWN_ARROW:UP_ARROW, (float) pps_offset);
   }
   if(pps_enabled) vidstr(VAL_ROW+3, VAL_COL, WHITE, out);
   else            vidstr(VAL_ROW+3, VAL_COL, YELLOW, out);


   if(ebolt || res_t)    c = ':';
   else if(osc_polarity) c = DOWN_ARROW;
   else                  c = UP_ARROW;
// sprintf(out, "Osc%c%11.6f%s   ", c, (float) osc_offset, ppb_string);
   if(luxor) {
      val = (float) osc_offset;
      if((val >= 10000.0F) || (val <= (-1000.0F))) {
         sprintf(out, "Osc%c%11.4f%s   ", c, val, "V  ");
      }
      else if((val >= 1000.0F) || (val <= (-100.0F))) {
         sprintf(out, "Osc%c%11.5f%s   ", c, val, "V  ");
      }
      else {
         sprintf(out, "Osc%c%11.6f%s   ", c, val, "V  ");
      }
   }
   else if(res_t) {
      val = (float) osc_offset;
      if(show_euro_ppt) ppt_string = "e-9 ";
      else              ppt_string = " ppb";
      if((val >= 10000.0F) || (val <= (-1000.0F))) {
         sprintf(out, "Rate%c%10.4f%s   ", c, val, ppt_string);
      }
      else if((val >= 1000.0F) || (val <= (-100.0F))) {
         sprintf(out, "Rate%c%10.5f%s   ", c, val, ppt_string);
      }
      else {
         sprintf(out, "Rate%c%10.6f%s   ", c, val, ppt_string);
      }
   }
   else {
      val = (float) osc_offset * 1000.0F;
      if((val >= 10000.0F) || (val <= (-1000.0F))) {
         sprintf(out, "Osc%c%11.4f%s   ", c, val, ppt_string);
      }
      else if((val >= 1000.0F) || (val <= (-100.0F))) {
         sprintf(out, "Osc%c%11.5f%s   ", c, val, ppt_string);
      }
      else {
         sprintf(out, "Osc%c%11.6f%s   ", c, val, ppt_string);
      }
   }
   vidstr(VAL_ROW+4, VAL_COL, WHITE, out);
}

void update_plot_data()
{
   // add the latest data to the plot queue and update the screen
   if(have_time && (pause_data == 0)) {
      if(continuous_scroll) update_plot(2);
      else if((all_adevs == 0) || mixed_adevs) update_plot(1);
      else if(all_adevs) update_plot(1);
      else update_plot(0);

      if(first_sample) {
         if(discipline_mode == 6) osc_discipline = 0;
         else                     osc_discipline = 1;

         if(discipline_mode == 3) user_holdover = 1;
         else                     user_holdover = 0;

         if((all_adevs == 0) || mixed_adevs) draw_plot(1);

         first_sample = 0;
      }
   }
   else {
      refresh_page();
   }
}

float last_xt;
float x_temp;


void secondary_timing()
{
u08 spare1, spare2;
u32 dac_value;
u08 spare3[8];
int i;
int color;
u08 spare_data;
u08 survey_err;
float val;
double x_pps;
double x_osc;
long   x_val;
float  x_dac;
double x_lat;
double x_lon;
double x_alt;

// printf("Packet 8F.AC (Secondary timing):\n");

   color = 0;
   if(luxor) {
      x_pps = pps_offset;
      x_osc = osc_offset;
      x_val = 0;
      x_dac = dac_voltage;
      last_xt = x_temp;
      x_temp = temperature;
      goto lux_mode;
   }

   rcvr_mode = tsip_byte();
   discipline_mode = tsip_byte();
   survey_progress = tsip_byte();
   holdover = tsip_dword();
   critical_alarms = tsip_word();
   minor_alarms = tsip_word();
   gps_status = tsip_byte();
   discipline = tsip_byte();
   spare1 = tsip_byte();
   spare2 = tsip_byte();
   x_pps = (double) tsip_single();
   x_osc = (double) tsip_single();
   x_val = tsip_dword();
   x_dac = tsip_single();
//   last_temp_val = temperature;
last_xt = x_temp;
   x_temp= tsip_single();
if(last_xt == 0.0F) last_xt = x_temp;
//   if(last_temp_val == 0.0F) last_temp_val = temperature;
   x_lat = tsip_double();
   x_lon = tsip_double();
   x_alt = tsip_double();

   pps_quant = tsip_single();  // res_t
   if(res_t) x_dac = pps_quant;

   spare_data = 0;  // flag set if any non-zero spare data fields 
   for(i=0; i<4; i++) {
      spare3[i] = tsip_byte();
      if(spare3[i]) ++spare_data;
   }

   tsip_end(1);
   if(murray) request_secondary_timing();

if(just_read) return;
if(tsip_error) return;

   lux_mode:
   pps_offset = x_pps;
   osc_offset = x_osc;
   dac_value = x_val;
   dac_voltage = x_dac;
   last_temp_val = temperature;
// temperature = x_temp;
if(undo_fw_temp_filter && (luxor == 0)) {
   temperature = (SENSOR_TC*x_temp) - ((SENSOR_TC-1.0F)*last_xt);  // unaverage the firmware reported temperature
   if((temperature < -100.0) || (temperature > 100.0F)) temperature = x_temp;  // filter problem
}
else {
   temperature = x_temp;
}
   if(last_temp_val == 0.0F) last_temp_val = temperature;
   if(luxor == 0) {
      lat = x_lat;
      lon = x_lon;
      alt = x_alt;
   }

   if(plot[TEMP].plot_center == NEED_CENTER) plot[TEMP].plot_center = scale_temp(temperature);
   if(plot[TC2].plot_center == NEED_CENTER) plot[TC2].plot_center = scale_temp(tc2);
   if(plot[BATTV].plot_center  == NEED_CENTER) plot[BATTV].plot_center  = dac_voltage;
   if(luxor && (plot[LUX1].plot_center == NEED_CENTER)) plot[LUX1].plot_center = (float) (pps_offset * lux_scale);
   if(luxor && (plot[LUX2].plot_center == NEED_CENTER)) plot[LUX2].plot_center = (float) (pps_offset * lum_scale);

   if(survey_progress == 100) surveying = 0;
   if(doing_survey != last_survey) {  // self survey changed
      redraw_screen();
   }
   last_survey = doing_survey;

   #ifdef PRECISE_STUFF
      precise_check();
   #endif

   if(crude_temp) {   // simulate the crude temperature sensor
      val = temperature - (float) (int) temperature;
      val -= 0.75F;
      if((val >= 0.02) || (val < (-0.02))) {  // allow some noise around the switch point
         temperature = ((float) (int) temperature) + 0.75F;
      }
   }

   if(tsip_error) {  // don't pollute log with potentially bad data
      pps_offset = last_pps_offset;
      osc_offset = last_osc_offset;
      dac_voltage = last_dac_voltage;
      temperature = last_temp_val;
   }
   else {  // filter out bogus values
      if(res_t == 0) {
         #ifdef __386__
            if(ABS(dac_voltage) <= 1.0E-4F) dac_voltage = 0.0F;
            if(ABS(temperature) <= 1.0E-4F) temperature = 0.0F;
         #endif
         if(luxor == 0) {
            if(dac_voltage == 0.0F) dac_voltage = last_dac_voltage;
            if(temperature == 0.0F) temperature = last_temp_val;
            if(pps_offset == 0.0F)  pps_offset = last_pps_offset;
            if(osc_offset == 0.0F)  osc_offset = last_osc_offset;
            if((dac_voltage < (-10.0F)) || (dac_voltage > 10.0F))  dac_voltage = last_dac_voltage;
            if((temperature < (-55.0F)) || (temperature > 100.0F)) temperature = last_temp_val;
         }
      }

//    if((pps_offset < (-100.0)) || (pps_offset > 100.0))  pps_offset = last_pps_offset;
//    if((osc_offset < (-100.0)) || (osc_offset > 100.0))  osc_offset = last_osc_offset;
      have_rcvr_mode = 1;

      #ifdef PRECISE_STUFF
         update_precise_survey();
         if(rcvr_mode != last_rcvr_mode) plot_lla_axes();
         last_rcvr_mode = rcvr_mode;
      #endif
   }

   if(saw_ntpx && (initial_voltage == 0.0) && ((user_set_osc & 0x08) == 0x00)) {
      initial_voltage = dac_voltage;  // set initial dac voltage to the current dac value
   }

   if(have_time && (have_osc == 0)) {  // initialize the value to the current PPS offset
      have_osc = 1;
      osc_integral = (((double) pps_offset) * 1.0E-9);
   }
   osc_integral += (osc_offset * 1.0E-9);


   filter_spikes();    // filter out false temperature sensor spikes
   #ifdef TEMP_CONTROL
      control_temp();
   #else
      temp_dir = ' ';
   #endif

   #ifdef OSC_CONTROL
      control_osc();
   #endif

   survey_err = 0;
   if(survey_progress > 100) {
      survey_progress = 100;
      survey_err = 1;
   }

#ifdef ADEV_STUFF
    if((adev_period > 0.0F) && (pause_data == 0)) {
      if(++adev_time >= (int) (adev_period+0.5F)) {  // add this data point to adev data queue
         add_adev_point(osc_offset, pps_offset);   
//       add_adev_point(osc_integral*1.0E9/100.0, pps_offset);   
         adev_time = 0;
      }
   }
#endif // ADEV_STUFF

   if(reading_log == 0) time_check(0, 1, hours,minutes,seconds);  // check for skips in the time
   if(++log_file_time >= log_interval) {
      write_log_readings(log_file, -1L);
      log_file_time = 0;
   }

   if(tsip_error) return;
   if(survey_err) return;

   last_pps_offset = pps_offset;
   last_osc_offset = osc_offset;
   last_dac_voltage = dac_voltage;
   last_temperature = temperature;

   // round these to multiples of the graph scale factor
   last_temperature *= plot[TEMP].ref_scale;
   last_temperature = (long) ((last_temperature / plot[TEMP].scale_factor)) * plot[TEMP].scale_factor;
   last_temperature /= plot[TEMP].ref_scale;

   last_dac_voltage *= plot[DAC].ref_scale; 
   last_dac_voltage = (long) ((last_dac_voltage / plot[DAC].scale_factor)) * plot[DAC].scale_factor;
   last_dac_voltage /= plot[DAC].ref_scale; 

   if(have_alarms == 0) {
      have_alarms = 1;
      last_critical = critical_alarms;
      last_minor = minor_alarms;
   }

#ifdef ADEV_STUFF
   if(pause_data == 0) {  // redraw adev curves and tables every 10 seconds
      update_adev_display(ATYPE);  
   }
#endif // ADEV_STUFF

   show_param_values();   // update alarm and data value displays
   write_log_changes();   // write important state changes to log file
   update_plot_data();    // add latest info to the plot queue and update the screen
}


void ae_packet()
{
u08 subcode;      // packet subcode
u16 zero;         // ???
u08 leds;         // led status
u08 ffom;         // frequency figure of merit
u08 tfom;         // time figure of merit
u08 hold;         // holdover state
u08 pll;          // pll state
u08 dis;          // disciplining mode
u08 flash;        // firmware code
u08 b1,b2;        // ???
u08 log_count;    // number of events in the log
u16 op_status;    // operation status
u16 hw_status;    // hardware status
float pps_val;    // related to pps error (in ns)
float osc_val;    // related to osc error (in ppb)
int i;
unsigned char buf[32];

   // Unknown packet sent by Nortel receiver.  Also mentioned as being
   // sent by the Palisade,  but in a different format.

// for(i=0; i<9+8; i++) tsip_byte();
   subcode = tsip_byte();
   if(subcode == 0x01) {
      zero  = tsip_word();
      leds  = tsip_byte();
      ffom  = tsip_byte();
      tfom  = tsip_byte();
      hold  = tsip_byte();

      if(try_ntpx == 0) {
         pll   = tsip_byte();
         dis   = tsip_byte();
         flash = tsip_byte();

         b1 = tsip_byte();    // 0
         b2 = tsip_byte();    // 1
         log_count = tsip_byte();  // error count
         op_status = tsip_word(); 
         hw_status = tsip_word(); 

         pps_val = tsip_single();  // PPS val (ns)
         osc_val = tsip_single();  // OSC val (ppb)
      }
//    sprintf(plot_title, "led:%02X  ffom:%02X tfom:%02X  ho:%02X  pll:%02X  dis:%02X  flash:%02X  b:%02X,%02X  log:%02X  op:%04X hw:%04X  %12g %12g", 
//      leds, ffom,tfom,  hold,pll,dis,flash, b1,b2, log_count, op_status,hw_status, pps_val,osc_val);
   }
   else if(1) {
//    plot_title[0] = 0;
      for(i=0; i<9+8+8; i++) {
         buf[i] = tsip_byte();
//       sprintf(out, "%02X ", (unsigned) buf[i]);
//       strcat(plot_title, out);
      }
   }

   tsip_end(1);
   if(try_ntpx && (tsip_error == 0) && (zero == 0x0001)) {
      saw_ntpx = 1;
      if(user_set_temp_filter == 0) undo_fw_temp_filter = 0;
   }
   if(tsip_error && (zero == 0x0001)) { // error seen, maybe it's an NTPX gpsdo?
      try_ntpx ^= 1;
      if(try_ntpx == 0) saw_ntpx = 0;
   }
//sprintf(plot_title, "ntpx: %d  zero:%04X  saw_ntpx=%d  notel=%d  oscp=%04X", 
//try_ntpx, zero, saw_ntpx, saw_nortel, have_osc_params);
}


// unit_status bit definitions
#define RESET_BIT      0x80000000L
#define CAL_MODE_BIT   0x40000000L
#define ZEROING_BIT    0x20000000L
#define WDT_BIT        0x10000000L
#define RUN_TIMEOUT    0x08000000L
#define CONFIG_ERR     0x04000000L
#define CAL_CRC_ERR    0x02000000L
#define COM_ERR_BIT    0x01000000L

#define AUXV_HVC_BIT   0x00800000L
#define AUXV_LVC_BIT   0x00400000L
#define LOAD_WATTS_BIT 0x00200000L
#define BATT_WATTS_BIT 0x00100000L

#define LUX2_OVFL_BIT  0x00080000L
#define LUX2_CHIP_BIT  0x00040000L
#define LUX1_OVFL_BIT  0x00020000L
#define LUX1_CHIP_BIT  0x00010000L

#define TEMP2_BAD_BIT  0x00008000L
#define TEMP2_OVT_BIT  0x00004000L
#define TEMP2_MASK     0xFFFFCFFFL
#define TEMP2_IR       0x00001000L
#define TEMP2_TC       0x00002000L
#define TEMP2_AT       0x00003000L

#define TEMP1_BAD_BIT  0x00000800L
#define TEMP1_OVT_BIT  0x00000400L
#define TEMP1_MASK     0xFFFFFCFFL
#define TEMP1_IR       0x00000100L
#define TEMP1_TC       0x00000200L
#define TEMP1_AT       0x00000300L

#define LOAD_HVC_BIT   0x00000080L
#define LOAD_LVC_BIT   0x00000040L
#define LOAD_OVC_BIT   0x00000020L
#define CFG_CRC_ERR    0x00000010L

#define BATT_HVC_BIT   0x00000008L
#define BATT_LVC_BIT   0x00000004L
#define BATT_OVC_BIT   0x00000002L
#define BATTERY_ON     0x00000001L

#define FAULT_BITS    (BATT_OVC_BIT | BATT_LVC_BIT | BATT_HVC_BIT | BATT_WATTS_BIT | LOAD_OVC_BIT | LOAD_HVC_BIT | LOAD_LVC_BIT | LOAD_WATTS_BIT | AUXV_HVC_BIT | AUXV_LVC_BIT | TEMP1_OVT_BIT | TEMP1_BAD_BIT | TEMP2_OVT_BIT | TEMP2_BAD_BIT | WDT_BIT | COM_ERR_BIT | RUN_TIMEOUT | CONFIG_ERR | CAL_CRC_ERR | CFG_CRC_ERR)


u08 luxor_fault()
{
int row, col;
int color;

   if(1 && (unit_status & RESET_BIT)) {
      have_time = 0;
      sound_alarm = 0;
//    fault_seen = 0;
   }

   if((unit_status & FAULT_BITS) == 0) {
      fault_seen = 0;
      if(unit_status & RESET_BIT) ;
      else if(unit_status & CAL_MODE_BIT) ;
      else if(unit_status & ZEROING_BIT) ;
      else if(prot_menu || show_prots) ;
      else {
         return 0;
      }
   }
   else if((unit_status & FAULT_BITS) && (fault_seen == 0)) {
      if(unit_status & RESET_BIT) ;
      else if(unit_status & ZEROING_BIT) ;
      else {
         fault_seen = 1;
         if((unit_status & FAULT_BITS) == COM_ERR_BIT) ;
         else if((unit_status & FAULT_BITS) == WDT_BIT) ;
         else if((unit_status & FAULT_BITS) == (WDT_BIT | COM_ERR_BIT)) ;
         else if(have_time) sound_alarm = 1;
      }
   }

   erase_watch();
   row = (aclock_y - ACLOCK_SIZE/2 + (TEXT_HEIGHT-1)) / TEXT_HEIGHT;
   col = (aclock_x - ACLOCK_SIZE/2 + (TEXT_WIDTH-1)) / TEXT_WIDTH;
   if(aclock_y < PLOT_ROW) {
      col -= 5;
      if(row) --row;
   }

   if(prot_menu || show_prots) {
      if(unit_status & FAULT_BITS) color = RED;
      else                         color = WHITE;
      vidstr(row++, col, color, "Protections:");

      if(unit_status & BATT_LVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "Batt LVC: %8.3f V", batt_lvc);
      vidstr(row++, col, color, out);

      if(unit_status & BATT_HVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "Batt HVC: %8.3f V", batt_hvc);
      vidstr(row++, col, color, out);

      if(unit_status & BATT_OVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "Batt OVC: %8.3f A", batt_ovc);
      vidstr(row++, col, color, out);

      if(unit_status & BATT_WATTS_BIT) color = RED;
      else                             color = WHITE;
      sprintf(out, "Batt OVW: %8.3f W", batt_watts);
      vidstr(row++, col, color, out);

      if(unit_status & LOAD_LVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "LED LVC:  %8.3f V", load_lvc);
      vidstr(row++, col, color, out);

      if(unit_status & LOAD_HVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "LED HVC:  %8.3f V", load_hvc);
      vidstr(row++, col, color, out);

      if(unit_status & LOAD_OVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "LED OVC:  %8.3f A", load_ovc);
      vidstr(row++, col, color, out);

      if(unit_status & LOAD_WATTS_BIT) color = RED;
      else                             color = WHITE;
      sprintf(out, "LED OVW:  %8.3f W", load_watts);
      vidstr(row++, col, color, out);

      if(unit_status & AUXV_LVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "AUXV LVC: %8.3f V", auxv_lvc);
      vidstr(row++, col, color, out);

      if(unit_status & AUXV_HVC_BIT) color = RED;
      else                           color = WHITE;
      sprintf(out, "AUXV HVC: %8.3f V", auxv_hvc);
      vidstr(row++, col, color, out);


      if(unit_status & TEMP1_OVT_BIT) color = RED;
      else                            color = WHITE;
      sprintf(out, "TEMP1:    %8.3f%c%c", tc1_ovt, DEGREES, DEG_SCALE);
      vidstr(row++, col, color, out);

      if(unit_status & TEMP2_OVT_BIT) color = RED;
      else                            color = WHITE;
      sprintf(out, "TEMP2:    %8.3f%c%c", tc2_ovt, DEGREES, DEG_SCALE);
      vidstr(row++, col, color, out);

      if(unit_status & WDT_BIT) color = RED;
      else                      color = WHITE;
      sprintf(out, "Timeout:  %8.3f S", msg_timeout);
      vidstr(row++, col, color, out);
   }
   else {
      vidstr(row++, col, RED, "Abnormal status:");
      if(unit_status & RESET_BIT)      vidstr(row++, col, RED, "Unit reset"); 
      if(unit_status & CAL_MODE_BIT)   vidstr(row++, col, RED, "Cal mode"); 
      if(unit_status & CAL_CRC_ERR)    vidstr(row++, col, RED, "Cal memory bad"); 
      if(unit_status & CFG_CRC_ERR)    vidstr(row++, col, RED, "Config memory bad"); 
      if(unit_status & CONFIG_ERR)     vidstr(row++, col, RED, "Config changed"); 
      if(unit_status & ZEROING_BIT) {
         vidstr(row++, col, RED, "Zeroing sensors"); 
      }
      else {
         if(unit_status & BATT_OVC_BIT)   vidstr(row++, col, RED, "Battery over current");
         if(unit_status & BATT_WATTS_BIT) vidstr(row++, col, RED, "Battery over watts");
         if(unit_status & LOAD_OVC_BIT)   vidstr(row++, col, RED, "LED over current");
         if(unit_status & LOAD_WATTS_BIT) vidstr(row++, col, RED, "LED over watts");
      }
      if(unit_status & BATT_LVC_BIT)   vidstr(row++, col, RED, "Battery low voltage");
      if(unit_status & BATT_HVC_BIT)   vidstr(row++, col, RED, "Battery high voltage");
      if(unit_status & LOAD_LVC_BIT)   vidstr(row++, col, RED, "LED low voltage");
      if(unit_status & LOAD_HVC_BIT)   vidstr(row++, col, RED, "LED high voltage");
      if(unit_status & AUXV_LVC_BIT)   vidstr(row++, col, RED, "AUXV low voltage");
      if(unit_status & AUXV_HVC_BIT)   vidstr(row++, col, RED, "AUXV high voltage");
      if(unit_status & TEMP1_OVT_BIT)  vidstr(row++, col, RED, "Temp1 over-temp");
      if(unit_status & TEMP2_OVT_BIT)  vidstr(row++, col, RED, "Temp2 over-temp");
      if(unit_status & TEMP1_BAD_BIT)  vidstr(row++, col, RED, "Temp1 sensor fault");
      if(unit_status & TEMP2_BAD_BIT)  vidstr(row++, col, RED, "Temp2 sensor fault");
      if(unit_status & LUX1_OVFL_BIT)  vidstr(row++, col, RED, "Lux overflow");
      if(unit_status & LUX2_OVFL_BIT)  vidstr(row++, col, RED, "Lumens overflow");
      if(unit_status & COM_ERR_BIT)    vidstr(row++, col, RED, "Serial data error");
      if(unit_status & WDT_BIT)        vidstr(row++, col, RED, "Message timeout");
      if(unit_status & RUN_TIMEOUT)    vidstr(row++, col, RED, "Timer shutdown");
   }

   return 1;
}

struct CCT_TABLE {
   float ratio;
   float k;
} cctt[] = {
   { 0.000F, 200000.0F},
   { 0.440F, 63675.0F},     // 390 nm UV !!!!!
   { 0.823F, 20000.0F}, // dummy
   { 0.858F, 15000.0F}, // Chinese 3W
   { 0.894F, 13000.0F}, // Chinese 3W
   { 1.013F, 10000.0F}, // Chinese 3W
   { 1.156F, 8000.0F},  // Chinese 3W
   { 1.360F, 6500.0F},  // XML T6 UF2100
   { 1.550F, 5700.0F},  // luminus
   { 1.770F, 5200.0F},  // Bridgelux C8000
   { 1.890F, 4950.0F},  // SkyRayKing NW on high
   { 2.295F, 4250.0F},  // Nichia 219
   { 2.482F, 4000.0F},  // Philips capsule
   { 3.023F, 3350.0F},  // Bridgelux
   { 3.367F, 3050.0F},  // LSG MR16l
   { 3.458F, 3000.0F},  // philips/lsg/syl PAR20/Syl PAR16
   { 3.752F, 2850.0F},  // Bridgelux W0804
   { 4.077F, 2700.0F},  // LSG PAR30  SYL PAR16
   { 4.500F, 2500.0F}   // dummy value !!!!!
};

#define NUM_CCT (sizeof(cctt) / sizeof(struct CCT_TABLE))

float cie_x, cie_y, cie_z;
float cie_sum;

void calc_cie(float red_uw, float green_uw,  float blue_uw)
{
   if(tcs_color) {  // TCS3414
      cie_x = (-0.14282F*red_uw) + (1.54924F*green_uw) + (-0.95641F*blue_uw); // TCS3414
      cie_y = (-0.32466F*red_uw) + (1.57837F*green_uw) + (-0.73191F*blue_uw);
      cie_z = (-0.68202F*red_uw) + (0.77073F*green_uw) + (+0.56332F*blue_uw);
   }
   else {           // TCS3210
      cie_x = (0.4287F*red_uw) + (0.4489F*green_uw)  + (0.0493F*blue_uw);
      cie_y = (0.1450F*red_uw) + (0.9623F*green_uw)  + (-0.1167F*blue_uw);
      cie_z = (0.0539F*red_uw) + (-0.4059F*green_uw) + (1.4191F*blue_uw);
   }
   cie_sum = cie_x + cie_y + cie_z;
}

float calc_cct(int type, int undo_scale, float red, float green, float blue)
{
int i;
float val;
float dif;
float pct;
float red_uw, green_uw, blue_uw;
float ccx, ccy, ccz;
float n;
float cct;

   if(undo_scale) {        // red, green and blue came from get_plot_q() values
      if(show_color_uw) {  // we need to undo the scale factor that was applied to those values 
         red *= RED_SENS;    // blue
         green *= GREEN_SENS; // green
         blue *= BLUE_SENS;    // red
      }
      else if(show_color_pct) {
         // !!!!!!! we cant properly undo those values
         red_uw = red * (red + green + blue);
         green_uw = green * (red + green + blue);
         blue_uw = blue * (red + green + blue);
         red = red_uw;
         green = green_uw;
         blue = blue_uw;
      }
   }
if(0 && cct_dbg) sprintf(plot_title, "ty=%d r=%f g=%f b=%f", type, red, green, blue);

   if(type == 0) {
      if(blue == 0.0F) return 0.0F;
      val = (red / blue) * cct_cal;
val = rb_m * val + rb_b;

      for(i=0; i<NUM_CCT; i++) {
         if(val < cctt[i].ratio) {
            if(i == 0) return 99999.999F;

            dif = cctt[i].ratio - cctt[i-1].ratio;
            if(dif == 0.0F) return 0.0F;
            pct = (val - cctt[i-1].ratio) / dif;

            dif = cctt[i].k - cctt[i-1].k;
// sprintf(plot_title, "red=%f  rob=%f  val=%f  hz=%f  i=%d  pct=%f  dif=%f", red, r_over_b, val, red_hz/blue_hz, i, pct, dif);
            dif *= pct;
            return cctt[i-1].k + dif;
         }
      }
   }
   else {
      red_uw = red / RED_SENS;
      green_uw = green / GREEN_SENS;
      blue_uw = blue / BLUE_SENS;

      calc_cie(red_uw, green_uw, blue_uw);
      if(cie_sum) {
         ccx = cie_x / cie_sum;
         ccy = cie_y / cie_sum;
         ccz = cie_z / cie_sum;
         if(type == 1) {
            n = (ccx - 0.3320F) / (ccy - 0.1858F);
            cct = (-449.0F*n*n*n) + (3525.0F*n*n) - (6823.3F*n) + 5520.33F;
            if((cct < 0.0F) || (cct > 100000.0F)) cct = 0.0F;
            cct /= cct1_cal;  // apply bogus correction factor
            return cct;
         }
         else if(type == 2) {
            n = (ccx - 0.3366F) / (ccy - 0.1735F);
            cct = (float) ((-949.86315F) + 6253.80338F*exp(-n/0.91259F) + 28.70599F*exp(-n/0.20039) + 0.00004F*exp(-n/0.07125F));
            if((cct < 0.0F) || (cct > 100000.0F)) cct = 0.0F;
            cct /= cct2_cal;  // apply bogus correction factor
            return cct;
         }
      }
      else return 0.0F;
   }

   return 1.0F;
}


#define H 6.626068E-34
#define C 299792458.0
#define K 1.3806503E-23

double plank(double t, double y)
{
double f;

// This routine used Plank's equation to calculate the energy at wavelength
// y (in namometers) of a black body at temperature t (in degrees K)

   y *= 1.0E-9;     // convert wavelenth to meters
   f = (2.0*PI*H*C*C) /
       ((y*y*y*y*y) * (exp((H*C) / (K*y*t)) - 1.0));
   f /= 1.0E6;      // normalize to standard units
//printf("T=%f  y=%g  f=%g\n", t,y,f);
   return f;

}


float calc_cri(float cct)
{
double bb_r,bb_g,bb_b,d,sum;  // black body values
double R,G,B;                 // sensor values
double y;
double err;

   d = 0.0;

   R = red_uw;
   G = green_uw;
   B = blue_uw;
   sum = R + G + B;
   if(sum == 0.0) return 0.0F;

   R /= (float) sum;
   G /= (float) sum;
   B /= (float) sum;

   // calculate the black body energy emitted over the color sensor bands
   if(cri_flag) {
      bb_r = plank(cct, 621.0);  // 640
      bb_g = plank(cct, 500.0);  // 524
      bb_b = plank(cct, 490.0);  // 470
   }
   else if(1) {
      bb_b  = plank(cct, 420.0) * 0.30;
      bb_b += plank(cct, 430.0) * 0.40;
      bb_b += plank(cct, 440.0) * 0.42;
      bb_b += plank(cct, 450.0) * 0.45;
      bb_b += plank(cct, 460.0) * 0.48;
      bb_b += plank(cct, 470.0) * 0.46;
      bb_b += plank(cct, 480.0) * 0.44;
      bb_b += plank(cct, 490.0) * 0.40;
      bb_b += plank(cct, 500.0) * 0.35;
      bb_b += plank(cct, 510.0) * 0.30;
      bb_b += plank(cct, 520.0) * 0.25;
      bb_b += plank(cct, 530.0) * 0.15;
      bb_b += plank(cct, 540.0) * 0.14;
      bb_b += plank(cct, 550.0) * 0.13;
      bb_b += plank(cct, 560.0) * 0.08;
      bb_b /= 15.0;

      bb_g  = plank(cct, 420.0) * 0.05;
      bb_g += plank(cct, 420.0) * 0.06;
      bb_g += plank(cct, 440.0) * 0.07;
      bb_g += plank(cct, 450.0) * 0.08;
      bb_g += plank(cct, 460.0) * 0.10;
      bb_g += plank(cct, 470.0) * 0.18;
      bb_g += plank(cct, 480.0) * 0.20;
      bb_g += plank(cct, 490.0) * 0.23;
      bb_g += plank(cct, 500.0) * 0.28;
      bb_g += plank(cct, 510.0) * 0.32;
      bb_g += plank(cct, 520.0) * 0.38;
      bb_g += plank(cct, 530.0) * 0.50;
      bb_g += plank(cct, 540.0) * 0.55;
      bb_g += plank(cct, 550.0) * 0.54;
      bb_g += plank(cct, 560.0) * 0.50;
      bb_g += plank(cct, 570.0) * 0.40;
      bb_g += plank(cct, 580.0) * 0.39;
      bb_g += plank(cct, 590.0) * 0.20;
      bb_g += plank(cct, 600.0) * 0.15;
      bb_g += plank(cct, 610.0) * 0.06;
      bb_g /= 20.0;

      bb_r  = plank(cct, 510.0) * 0.03;
      bb_r += plank(cct, 520.0) * 0.05;
      bb_r += plank(cct, 530.0) * 0.08;
      bb_r += plank(cct, 540.0) * 0.10;
      bb_r += plank(cct, 550.0) * 0.17;
      bb_r += plank(cct, 560.0) * 0.17;
      bb_r += plank(cct, 570.0) * 0.20;
      bb_r += plank(cct, 580.0) * 0.40;
      bb_r += plank(cct, 590.0) * 0.50;
      bb_r += plank(cct, 600.0) * 0.60;
      bb_r += plank(cct, 610.0) * 0.65;
      bb_r += plank(cct, 620.0) * 0.70;
      bb_r += plank(cct, 630.0) * 0.73;
      bb_r += plank(cct, 640.0) * 0.80;
      bb_r += plank(cct, 650.0) * 0.82;
      bb_r += plank(cct, 660.0) * 0.85;
      bb_r += plank(cct, 670.0) * 0.85;
      bb_r += plank(cct, 680.0) * 0.90;
      bb_r += plank(cct, 690.0) * 0.93;
      bb_r += plank(cct, 700.0) * 0.95;
      bb_r /= 20.0;    
   }
   else {
      bb_r = bb_g = bb_b = 0.0;
      for(y=400.0; y<=520.0; y+=10.0) {
         bb_b += plank(cct, y);
         d += 1.0;
      }
      bb_b /= d;

      for(y=480.0; y<=600.0; y+=10.0) {
         bb_g += plank(cct, y);
         d += 1.0;
      }
      bb_g /= d;

      for(y=550.0; y<=770.0; y+=10.0) {
         bb_r += plank(cct, y);
         d += 1.0;
      }
      bb_r /= d;
   }
   sum = bb_r + bb_g + bb_b;  // normalize black body energy to 0 .. 1
   bb_r /= sum;
   bb_g /= sum;
   bb_b /= sum;


   err = sqrt((((R-bb_r)*(R-bb_r)) + ((G-bb_g)*(G-bb_g)) + ((B-bb_b)*(B-bb_b)))/3.0);
   err = (1.0-err) * (1.0-err);

   return (float)err*100.0F;
}


#define SAT_COLOR_HZ 700000.0F      // color sensor saturation threshold
#define MAX_COLOR_HZ 500000.0F      // color sensor saturation warning threshold
#define MIN_COLOR_HZ 100.0F         // color sensor too low threshold
#define RED_OVFL   0x01
#define GREEN_OVFL 0x02
#define BLUE_OVFL  0x04
#define WHITE_OVFL 0x08
#define RED_LOW    0x10
#define GREEN_LOW  0x20
#define BLUE_LOW   0x40
#define WHITE_LOW  0x80
#define RED_SAT    0x100
#define GREEN_SAT  0x200
#define BLUE_SAT   0x400
#define WHITE_SAT  0x800

u08 last_cal_mode;


void measure_ir()
{
   // this routine measures the battery internal resistance by checking
   // how the battery voltage changes when loaded and unloaded

   if(calc_ir >= IR_TIME) {        // turn on load
      set_batt_pwm(0xFFFF);
      --calc_ir;
      sprintf(plot_title, "Calculating battery internal resistance: %2d", calc_ir);
   }
   else if(calc_ir == 3) {   // get loaded readings
      ir_v = batt_v;
      ir_i = batt_i;
      --calc_ir;
      set_batt_pwm(0);
      sprintf(plot_title, "Calculating battery internal resistance: %2d", calc_ir);
   }
   else if(calc_ir) {
      --calc_ir;
      if(calc_ir) {     // get unloaded readings
         sprintf(plot_title, "Calculating battery internal resistance: %2d", calc_ir);
      }
      else {
         ir_v = fabs(batt_v-ir_v);
         if(ir_i) {
            ir_v /= ir_i;
            sprintf(plot_title, "Battery internal resistance: %.2f milliohms at %.3f amps", ir_v*1000.0F, ir_i);
         }
         else {
            sprintf(plot_title, "No load detected on the battery");
         }
      }
   }
}



#define TERM_TIME 60  // seconds
int term_timer;       // times amount of time that the charge current is less than the shutoff threshold

void constant_load()
{
float delta;
u16 pwm;

   if(cc_mode == 0) return;
   if(cc_state < 5) ++cc_state;
   if(sweep_rate <= 0) {
      sweep_rate = sweep_tick = 1;
   }

   if(cc_state == 1) {  // starting up
      if(cc_mode == PWM_SWEEP) {
         cc_pwm = sweep_val = sweep_start;
         goto charged;
      }
      else if((cc_mode == CC_LIPO) && (led_v < unsafe_v)) {  // potentially unsafe cell - don't charge
         goto stop_charge;
      }
      term_timer = TERM_TIME;
      if(sweep_stop) cc_pwm = 0.0F;
      else           cc_pwm = PWM_STEP;
   }
   else if(cc_mode == PWM_SWEEP) {   // sweeping PWM value between limits
      if(sweep_start > sweep_end) {  // down sweep
         if(--sweep_tick <= 0) {
            sweep_tick = sweep_rate;
            sweep_val -= PWM_STEP;
            if(sweep_val < 0.0F) end_sweep();
         }
         if(sweep_val < sweep_end) {
            end_sweep();
         }
      }
      else {                         // up sweep;
         if(--sweep_tick <= 0) {
            sweep_tick = sweep_rate;
            sweep_val += PWM_STEP;
            if(sweep_val > 1.0F) end_sweep();
         }
         if(sweep_val > sweep_end) {
            end_sweep();
         }
      }
      cc_pwm = sweep_val;
      goto charged;
   }
   else {
      if((cc_mode == CC_LIPO) && (led_v > (lipo_volts-0.05F))) {  // constant V mode
//       if(led_v > (lipo_volts+0.05F)) goto stop_charge;
         if(led_v > (lipo_volts+0.10F)) goto stop_charge;
         if(led_i < (cc_val/20.0F)) {  // constant I mode - charge done at charge_rate/20
            if(--term_timer < 0) {
               stop_charge:
               end_sweep();
               cc_pwm = 0.0F;
               goto charged;
            }
         }
         else term_timer = TERM_TIME;

         if(led_i < cc_val) {
            if((led_v > lipo_volts) && cc_pwm) {
               cc_pwm -= PWM_STEP;
               if(cc_pwm < PWM_STEP) cc_pwm = PWM_STEP;
            }
            goto charged;
         }
      }

      if((cc_mode == CC_VOLTS) && (led_v > 0.050F)) {  // must have at least 50mv load voltage
         if(sweep_stop) {
            if(led_v > sweep_stop) {
               end_sweep();
               cc_pwm = 0.0F;
            }
            else if(--sweep_tick <= 0) {
               sweep_tick = sweep_rate;
               cc_pwm += PWM_STEP;
               if(cc_pwm > 1.0F) {
                  end_sweep();
                  cc_pwm = 0.0F;
               }
            }
         }
         else {
            delta = (cc_val - led_v);
            delta /= led_v;
            if(delta < 0.0F) delta *= 0.50F;
            else             delta *= 0.20F;
            cc_pwm += (delta * cc_pwm);
         }
      }
      else if((cc_mode == CC_WATTS) && (led_w > 0.050F)) {  // must have at least 50mw load power
         if(sweep_stop) {
            if(led_w > sweep_stop) {
               end_sweep();
               cc_pwm = 0.0F;
            }
            else if(--sweep_tick <= 0) {
               sweep_tick = sweep_rate;
               cc_pwm += PWM_STEP;
               if(cc_pwm > 1.0F) {
                  end_sweep();
                  cc_pwm = 0.0F;
               }
            }
         }
         else {
            delta = (cc_val - led_w);
            delta /= led_w;
            if(delta < 0.0F) delta *= 0.25F;  // power is a squared function, reduce gain
            else             delta *= 0.04F;
            cc_pwm += (delta * cc_pwm);
         }
      }
      else if((cc_mode > 1) && (led_i > 0.050F)) {  // must have at least 50mA load current
         if(sweep_stop) {
            if(led_i > sweep_stop) {
               end_sweep();
               cc_pwm = 0.0F;
            }
            else if(--sweep_tick <= 0) {
               sweep_tick = sweep_rate;
               cc_pwm += PWM_STEP;
               if(cc_pwm > 1.0F) {
                  end_sweep();
                  cc_pwm = 0.0F;
               }
            }
         }
         else {
            delta = (cc_val - led_i);
            delta /= led_i;
            if(delta < 0.0F) delta *= 0.50F;
            else             delta *= 0.20F;
            cc_pwm += (delta * cc_pwm);
         }
      }
      else {
         if(sweep_stop) {
            if(--sweep_tick <= 0) {
               sweep_tick = sweep_rate;
               cc_pwm += PWM_STEP;
               if(cc_pwm > 1.0F) {
                  end_sweep();
                  cc_pwm = 0.0F;
               }
            }
         }
         else {
            cc_pwm += PWM_STEP;
         }
      }
   }

   charged:
   if(cc_pwm > 1.0)        cc_pwm = 1.0F;
   else if(cc_pwm <= 0.0F) cc_pwm = 0.0F;

   pwm = (u16) (cc_pwm * 65535.0F);
   set_batt_pwm(pwm);

   if(cc_mode == CC_LIPO) {
      sprintf(plot_title, " LiPo Charge %.3fA to %.3fV: led_i=%.3fA  pwm=%f %04X %04X", cc_val,lipo_volts, led_i, cc_pwm,pwm,pwm>>6);
   }
   else if(cc_mode == CC_AMPS) {
      sprintf(plot_title, " CC Load %.3fA: led_i=%.3fA  pwm=%f %04X %04X", cc_val, led_i, cc_pwm,pwm,pwm>>6);
   }
   else if(cc_mode == CC_VOLTS) {
      sprintf(plot_title, " CV Load %.3fV: led_v=%.3fV  pwm=%f %04X %04X", cc_val, led_v, cc_pwm,pwm,pwm>>6);
   }
   else if(cc_mode == CC_WATTS) {
      sprintf(plot_title, " CW Load %.3fW: led_v=%.3fV  led_i=%.3fA  led_w=%.3fW  pwm=%f %04X %04X", cc_val, led_v, led_i, led_w, cc_pwm,pwm,pwm>>6);
   }
   else if(cc_mode == PWM_SWEEP) {
      sprintf(plot_title, " PWM sweep from %.3f to %.3f:  pwm=%f %04X %04X", sweep_start, sweep_end, cc_pwm,pwm,pwm>>6);
   }
}


u32 last_unit_status;

float ldbg1, ldbg2, ldbg3, ldbg4;

void luxor_packet()
{
u08 subcode;    // packet subcode
double val;
int i;
unsigned char buf[32];
int batt_volts, led_volts;
int batt_amps, led_amps;
int row;
int col;
int color;
int color_ovfl;
float color_sum;
float ccx, ccy, ccz;
float cct1, cct2, cct3, cct4;

   // Luxor power/light analyzer

   subcode = tsip_byte();
   if(subcode == 0x00) {        // get version info
      luxor_hw_ver = tsip_byte();
      luxor_hw_rev = tsip_byte();
      luxor_sn_prefix = sn_prefix = tsip_byte();
      luxor_serial_num = serial_num = tsip_word();

      batt_volts = tsip_word();
      batt_amps = (int) (s16) tsip_word();
      led_volts = tsip_word();
      led_amps = (int) (s16) tsip_word();
      tsip_end(1);

      have_info = (MANUF_PARAMS | PRODN_PARAMS | VERSION_INFO);

      if(text_mode && first_key) return;
      if(zoom_screen) return;

      if(cal_mode) color = RED;
      else         color = WHITE;

      sprintf(
         out, "BAT:%3dV  %c%dA", 
         batt_volts, (batt_amps<0)?PLUS_MINUS:'+', (batt_amps<0)?0-batt_amps:batt_amps
      );
      vidstr(VER_ROW+1, VER_COL, color, out);
      sprintf(
         out, "LED:%3dV  %c%dA", 
         led_volts,  (led_amps<0)?PLUS_MINUS:'+',  (led_amps<0)?0-led_amps:led_amps
      );
      vidstr(VER_ROW+2, VER_COL, color, out);
      sprintf(out, "VER: %d.%02d", luxor_hw_ver,luxor_hw_rev);
      vidstr(VER_ROW+3, VER_COL, color, out);
      show_serial_info();
      show_version_header();
   }
   else if(subcode == 0x01) {   // get readings
      if(luxor == 0) {
         luxor = 1;
         reset_luxor_wdt(0x01);
         config_luxor_plots();
         config_screen();
         redraw_screen();
         request_luxor_ver();
         set_luxor_time();
      }
      ++tow;
      time_color = DST_TIME_COLOR;

      unit_status = tsip_dword();
      batt_pwm = tsip_word();

      pri_seconds = seconds = tsip_byte();
      pri_minutes = minutes = tsip_byte();
      pri_hours = hours = tsip_byte();
      pri_day = day = tsip_byte();
      pri_month = month = tsip_byte();
      pri_year = year = tsip_byte() + 2000;

      tow = 0;
      tow += 365L*(long) (year-2012);
      tow += (long) dsm[month];
      tow += (long) day;            // t = day number of the year
      tow *= (24L*60L*60L);         // * secs per day
      tow += (60L*60L) * (long) hours;  // + secs per hour
      tow += (60L) * (long) minutes;    // + secs per minute
      tow += (long) seconds;            // + seconds

      batt_v = dac_voltage = tsip_single();
      batt_i = tsip_single(); 

      led_pos = tsip_single(); 
      led_neg = tsip_single(); 
      led_v = led_pos - led_neg;
      led_i = tsip_single(); 
      adc2 = tsip_single();

      tc1 = temperature = tsip_single(); 
      tc2 = tsip_single(); 

      pwm_hz = tsip_single();

      lux1 = tsip_single(); 
      lux1_time = tsip_byte();

      lux2 = tsip_single(); 
      lux2_time = tsip_byte();

      red_hz = tsip_single();
      blue_hz = tsip_single();
      white_hz = tsip_single();
      green_hz = tsip_single();
      r_over_b = tsip_single();

      cal_mode = tsip_byte();
      ldbg1 = tsip_single();
      ldbg2 = tsip_single();
      ldbg3 = tsip_single();
      ldbg4 = tsip_single();

      tsip_end(1);


      if(show_debug_info) {
         sprintf(plot_title, "dbg1=%f dbg2=%f dbg3=%f dbg4=%f", ldbg1,ldbg2,ldbg3,ldbg4);
      }

      reset_luxor_wdt(0);

      if(unit_status != last_unit_status) {  // make sure fault display gets erased/redrawn
         last_unit_status = unit_status;
         redraw_screen();
      }

      if(unit_status & FAULT_BITS) {
         end_sweep();
      }
      if(calc_ir) {     // battery internal resistance
         measure_ir();
      }
      constant_load();

      if(unit_status & RESET_BIT) {
         set_luxor_time();
         request_luxor_ver();
      }
      else if(cal_mode != last_cal_mode) request_luxor_ver();
      last_cal_mode = cal_mode;


      color_ovfl = 0;
      if(red_hz > SAT_COLOR_HZ)        color_ovfl |= RED_SAT;
      else if(red_hz > MAX_COLOR_HZ)   color_ovfl |= RED_OVFL;
      else if(red_hz < MIN_COLOR_HZ)   color_ovfl |= RED_LOW;

      if(green_hz > SAT_COLOR_HZ)      color_ovfl |= GREEN_SAT;
      else if(green_hz > MAX_COLOR_HZ) color_ovfl |= GREEN_OVFL;
      else if(green_hz < MIN_COLOR_HZ) color_ovfl |= GREEN_LOW;

      if(blue_hz > SAT_COLOR_HZ)       color_ovfl |= BLUE_SAT;
      else if(blue_hz > MAX_COLOR_HZ)  color_ovfl |= BLUE_OVFL;
      else if(blue_hz < MIN_COLOR_HZ)  color_ovfl |= BLUE_LOW;

      if(white_hz > SAT_COLOR_HZ)      color_ovfl |= WHITE_SAT;
      else if(white_hz > MAX_COLOR_HZ) color_ovfl |= WHITE_OVFL;
      else if(white_hz < MIN_COLOR_HZ) color_ovfl |= WHITE_LOW;

      cct  = calc_cct(0, 0, red_hz, green_hz, blue_hz);
      cct1 = calc_cct(1, 0, red_hz, green_hz, blue_hz);
      cct2 = calc_cct(2, 0, red_hz, green_hz, blue_hz);

      cct3 = (cct + cct1 + cct2) / 3.0F;
      cct4 = sqrt((cct*cct + cct1*cct1 + cct2*cct2) / 3.0F);
cct3 = cct4;

      red_uw = red_hz / RED_SENS;
      green_uw = green_hz / GREEN_SENS;
      blue_uw = blue_hz / BLUE_SENS;
      white_uw = white_hz / WHITE_SENS;
if(alt_lux1) lux1 = green_uw * alt_lux1;

      calc_cie(red_uw, green_uw, blue_uw);

      if(cie_sum) {
         ccx = cie_x / cie_sum;
         ccy = cie_y / cie_sum;
         ccz = cie_z / cie_sum;
      }
      else {
         ccx = ccy = ccz = 0.0F;
         cct = cct1 = cct2 = 0.0F;
      }



      pps_offset = (double) lux1; 
      osc_offset = (double) batt_i; 

      primary_misc();
      secondary_timing();

      batt_w = (batt_v*batt_i);
      led_w = (led_v*led_i);



      if(text_mode && first_key) return;
      if(zoom_screen) return;

      if(1 && (SCREEN_HEIGHT > 600)) row = 1;
      else                           row = 0;
      col = 30;

      if(cal_mode) unit_status |= CAL_MODE_BIT;
      sprintf(out, "Status: %08lX", (unsigned long) unit_status);
      if(unit_status & FAULT_BITS)      color = RED;
      else if(unit_status & BATTERY_ON) color = WHITE;
      else                              color = YELLOW;
      vidstr(row++, col, color, out);
      ++row;


      color_sum = (red_uw + green_uw + blue_uw) / 100.0F;
      if(color_sum == 0.0F) {
         sprintf(out, "Red:    none       ");
         vidstr(row++, col, GREY, out);
         sprintf(out, "Green:  none       ");
         vidstr(row++, col, GREY, out);
         sprintf(out, "Blue:   none       ");
         vidstr(row++, col, GREY, out);
         sprintf(out, "White:  none       ");
         vidstr(row++, col, GREY, out);
      }
      else if(show_color_hz) {
         sprintf(out, "Red:    %8.0f Hz", red_hz);
         if(color_ovfl & RED_OVFL)     color = YELLOW;
         else if(color_ovfl & RED_SAT) color = RED;
         else if(color_ovfl & RED_LOW) color = BLUE;
         else                          color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "Green:  %8.0f Hz", green_hz);
         if(color_ovfl & GREEN_OVFL)     color = YELLOW;
         else if(color_ovfl & GREEN_SAT) color = RED;
         else if(color_ovfl & GREEN_LOW) color = BLUE;
         else                            color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "Blue:   %8.0f Hz", blue_hz);
         if(color_ovfl & BLUE_OVFL)     color = YELLOW;
         else if(color_ovfl & BLUE_SAT) color = RED;
         else if(color_ovfl & BLUE_LOW) color = BLUE;
         else                           color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "White:  %8.0f Hz", white_hz);
         if(color_ovfl & WHITE_OVFL)     color = YELLOW;
         else if(color_ovfl & WHITE_SAT) color = RED;
         else if(color_ovfl & WHITE_LOW) color = BLUE;
         else                            color = WHITE;
         vidstr(row++, col, color, out);
      }
      else if(show_color_pct) {
         sprintf(out, "Red:    %8.3f %%", red_uw/color_sum);
         if(color_ovfl & RED_OVFL)     color = YELLOW;
         else if(color_ovfl & RED_SAT) color = RED; 
         else if(color_ovfl & RED_LOW) color = BLUE;
         else                          color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "Green:  %8.3f %%", green_uw/color_sum);
         if(color_ovfl & GREEN_OVFL)     color = YELLOW;
         else if(color_ovfl & GREEN_SAT) color = RED;
         else if(color_ovfl & GREEN_LOW) color = BLUE;
         else                            color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "Blue:   %8.3f %%", blue_uw/color_sum);
         if(color_ovfl & BLUE_OVFL)     color = YELLOW;
         else if(color_ovfl & BLUE_SAT) color = RED;
         else if(color_ovfl & BLUE_LOW) color = BLUE;
         else                           color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "White:  %8.3f %%", white_uw/color_sum);
         if(color_ovfl & WHITE_OVFL)     color = YELLOW;
         else if(color_ovfl & WHITE_SAT) color = RED;
         else if(color_ovfl & WHITE_LOW) color = BLUE;
         else                            color = WHITE;
         vidstr(row++, col, color, out);
      }
      else if(show_color_uw) {
         sprintf(out, "Red:   %9.3f uW/cm^2", red_hz/RED_SENS);
         if(color_ovfl & RED_OVFL)     color = YELLOW;
         else if(color_ovfl & RED_SAT) color = RED;
         else if(color_ovfl & RED_LOW) color = BLUE;
         else                          color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "Green: %9.3f uW/cm^2", green_hz/GREEN_SENS);
         if(color_ovfl & GREEN_OVFL)     color = YELLOW;
         else if(color_ovfl & GREEN_SAT) color = RED;
         else if(color_ovfl & GREEN_LOW) color = BLUE;
         else                            color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "Blue:  %9.3f uW/cm^2", blue_hz/BLUE_SENS);
         if(color_ovfl & BLUE_OVFL)     color = YELLOW;
         else if(color_ovfl & BLUE_SAT) color = RED;
         else if(color_ovfl & BLUE_LOW) color = BLUE;
         else                           color = WHITE;
         vidstr(row++, col, color, out);

         sprintf(out, "White: %9.3f uW/cm^2", white_hz/WHITE_SENS);
         if(color_ovfl & WHITE_OVFL)     color = YELLOW;
         else if(color_ovfl & WHITE_SAT) color = RED;
         else if(color_ovfl & WHITE_LOW) color = BLUE;
         else                            color = WHITE;
         vidstr(row++, col, color, out);
      }

      if(color_sum == 0.0F)                        color = GREY;
      else if(color_ovfl & (RED_SAT | BLUE_SAT))   color = RED;
      else if(color_ovfl & (RED_OVFL | BLUE_OVFL)) color = YELLOW;
      else if(color_ovfl & (RED_LOW | BLUE_LOW))   color = BLUE;
      else                                         color = WHITE;
      if(1) sprintf(out, "R/B:   %9.3f   ", r_over_b);
//    if(blue_hz) sprintf(out, "R/B:   %9.3f   ", red_hz/blue_hz);
      else        sprintf(out, "R/B:               ");
      vidstr(row++, col, color, out);
      sprintf(out, "CCT:   %9.3f %cK  ", cct, DEGREES);
      vidstr(row++, col, color, out);

      ++row;
      if(color_sum == 0.0F)                                     color = GREY;
      else if(color_ovfl & (RED_SAT | GREEN_SAT | BLUE_SAT))    color = RED;
      else if(color_ovfl & (RED_OVFL | GREEN_OVFL | BLUE_OVFL)) color = YELLOW;
      else if(color_ovfl & (RED_LOW | GREEN_LOW | BLUE_LOW))    color = BLUE;
      else                                                      color = WHITE;
//    sprintf(out, "ciex: %.4f  ", cie_x);
//    vidstr(row++, col, color, out); 
//    sprintf(out, "ciey: %.4f  ", cie_y);
//    vidstr(row++, col, color, out); 
//    sprintf(out, "ciez: %.4f  ", cie_z);
//    vidstr(row++, col, color, out); 
      sprintf(out, "ciex: %.4f  ", ccx);
      vidstr(row++, col, color, out); 
      sprintf(out, "ciey: %.4f  ", ccy);
      vidstr(row++, col, color, out); 
      sprintf(out, "ciez: %.4f  ", ccz);
      vidstr(row++, col, color, out); 
      ++row;

      sprintf(out, "cct1: %.3f %cK  ", cct1, DEGREES);
      vidstr(row++, col, color, out); 
      sprintf(out, "cct2: %.3f %cK  ", cct2, DEGREES);
      vidstr(row++, col, color, out); 
      sprintf(out, "cct3: %.3f %cK  ", cct3, DEGREES);
      vidstr(row++, col, color, out); 
//    sprintf(out, "cct4: %.3f %cK  ", cct4, DEGREES);
//    vidstr(row++, col, color, out); 
      sprintf(out, "bogoCRI:%6.2f  ", calc_cri(cct));
      vidstr(row++, col, color, out); 


      col = 0;
      if(1 && (SCREEN_HEIGHT > 600)) row = 1;
      else                           row = 0;

      if(unit_status & (BATT_HVC_BIT | BATT_LVC_BIT)) color = RED;
//    else if((batt_v > 0.003F) && (batt_v < 0.300F)) color = BLUE;
      else if(unit_status & BATTERY_ON)               color = WHITE;
      else                                            color = YELLOW;
      sprintf(out, "Batt V: %8.3f V", batt_v);
      vidstr(row++, col, color, out);

      if(unit_status & BATT_OVC_BIT)    color = RED;
      else if(unit_status & BATTERY_ON) color = WHITE;
      else                              color = YELLOW;
      sprintf(out, "Batt I: %8.3f A", batt_i);
      vidstr(row++, col, color, out);

      if(unit_status & BATTERY_ON) {
         if(batt_pwm != 0xFFFF) color = GREY;
         else                   color = WHITE;
      }
      else color = YELLOW;
      sprintf(out, "Batt W: %8.3f W", batt_w);
      vidstr(row++, col, color, out);


      if(plot[AUXV].show_plot) {
         if(unit_status & AUXV_HVC_BIT)      color = RED;
         else if(unit_status & AUXV_LVC_BIT) color = RED;
         else                                color = WHITE;
         sprintf(out, "Aux V:  %8.3f V", adc2);
         vidstr(row++, col, color, out);
      }
      else if(SCREEN_HEIGHT >= 600) ++row;

      if(unit_status & (LOAD_HVC_BIT | LOAD_LVC_BIT))   color = RED;
//    else if((led_pos > 0.003F) && (led_pos < 0.300F)) color = BLUE;
//    else if((led_neg > 0.003F) && (led_neg < 0.300F)) color = BLUE;
      else if(unit_status & BATTERY_ON)                 color = WHITE;
      else                                              color = YELLOW;
      sprintf(out, "Led +:  %8.3f V", led_pos);
      vidstr(row++, col, color, out);
      sprintf(out, "Led -:  %8.3f V", led_neg);
      vidstr(row++, col, color, out);
      sprintf(out, "Led Vf: %8.3f V", fabs(led_v));
      vidstr(row++, col, color, out);

      if(unit_status & LOAD_OVC_BIT)    color = RED;
      else if(unit_status & BATTERY_ON) color = WHITE;
      else                              color = YELLOW;
      sprintf(out, "Led I:  %8.3f A", led_i);
      vidstr(row++, col, color, out);

      sprintf(out, "Led W:  %8.3f W", led_w);
      if(unit_status & BATTERY_ON) color = WHITE;
      else                         color = YELLOW;
      vidstr(row++, col, color, out);

      sprintf(out, "Eff:             ");
      if(batt_w) {
         val = fabs(led_w/batt_w*100.0);  // !!!!! fabs?
         if(batt_pwm != 0xFFFF) color = GREY;
         if(val < 120.0) sprintf(out, "Eff:    %8.3f %%", val);
         else            sprintf(out, "Eff:         ??? %%");
      }
      vidstr(row++, col, color, out);


      if(SCREEN_HEIGHT >= 600) ++row;
      if((unit_status & (TEMP1_IR | TEMP1_TC | TEMP1_AT)) == 0) {   // no chip seen
         color = GREY;
         sprintf(out, "Temp1:      NONE    ");
      }
      else {                            // thermocouple chip installed
         if(unit_status & TEMP1_OVT_BIT)      color = RED;     // over temp
         else if(unit_status & TEMP1_BAD_BIT) color = YELLOW;  // no thermocouple seen
         else                                 color = WHITE;
         sprintf(out, "Temp1:  %s", fmt_temp(tc1));
      }
      vidstr(row++, col, color, out);


      if((unit_status & (TEMP2_IR | TEMP2_TC | TEMP2_AT)) == 0) {   // no chip seen
         color = GREY;
         sprintf(out, "Temp2:      NONE    ");
      }
      else {
         if(unit_status & TEMP2_OVT_BIT)      color = RED;     // over temp
         else if(unit_status & TEMP2_BAD_BIT) color = YELLOW;  // no thermocouple seen
         else                                 color = WHITE;
         sprintf(out, "Temp2:  %s", fmt_temp(tc2));
      }
      vidstr(row++, col, color, out);




      if(SCREEN_HEIGHT >= 600) ++row;
      if(unit_status & LUX1_CHIP_BIT) {
//val = ((white_hz/243.56F) + ((red_hz+green_hz+blue_hz)/229.8F)) * (1.10F/2.0F);
         if(show_fc) sprintf(out, "Lux:    %8.3f fc  ", lux1*lux_scale);
         else        sprintf(out, "Lux:    %8.3f lux ", lux1*lux_scale);
         if(unit_status & LUX1_OVFL_BIT) color = RED;   
         else                            color = WHITE;
      }
      else {
         color = GREY;
         sprintf(out, "Lux:        NONE");
      }
      vidstr(row++, col, color, out);

      if(unit_status & LUX2_CHIP_BIT) {
         if(show_cp) sprintf(out, "Lum:    %8.3f cp  ", lux2*lum_scale);
         else        sprintf(out, "Lum:    %8.3f lum ", lux2*lum_scale);
         if(unit_status & LUX2_OVFL_BIT) color = RED;   
         else                            color = WHITE;
      }
      else {
         color = GREY;
         sprintf(out, "Lum:        NONE");
      }
      vidstr(row++, col, color, out);

      color = WHITE;
      sprintf(out, "PWM:    %8.3f Hz  ", pwm_hz);
      vidstr(row++, col, color, out);
   }
   else if(subcode == 0x07) {
      get_luxor_config();
   }
   else if(subcode == 0x10) {
      get_luxor_cal();
   }
   else if(1) {
      plot_title[0] = 0;
      for(i=0; i<9+8+8; i++) {
         buf[i] = tsip_byte();
         sprintf(out, "%02X ", (unsigned) buf[i]);
         strcat(plot_title, out);
      }
      tsip_end(1);
   }
   else {
      tsip_end(1);
   }

}


void rcvr_config()
{
u08 rcvr_mode;
u08 rsvd1;
u08 rsvd2;
u08 rsvd3;
u08 rsvd4[17];
u08 i;

// printf("Packet BB (Receiver config):\n");

   subcode = tsip_byte();
   rcvr_mode = tsip_byte();
   rsvd1 = tsip_byte();
   dynamics_code = tsip_byte();
   rsvd2 = tsip_byte();
   el_mask = tsip_single();
   amu_mask = tsip_single();
   pdop_mask = tsip_single();
   pdop_switch = tsip_single();
   rsvd3 = tsip_byte();
   foliage_mode = tsip_byte();
   for(i=23; i<=39; i++) rsvd4[i-23] = tsip_byte();
   tsip_end(1);

   el_mask = (float) (int) ((el_mask*RAD_TO_DEG) + 0.50F);
   if(tsip_error) return;
}


void request_misc_msg()
{
   // This routine requests various minor status messages
   // It requests a different message each time it is called.
   if(first_request) {
      request_rcvr_info();
      first_request = 0;
   }

   ++req_num;

   if(req_num == 1)       request_io_options();
   else if(req_num == 2)  request_alm_health();
   else if(req_num == 3)  request_manuf_params();
   else if(req_num == 4)  request_last_posn();
   else if(req_num == 5)  request_version();
   else if(req_num == 6) {
      if(log_db == 0) request_sig_levels();
   }
   else if(req_num == 7)  request_eph_status(0x00);
   else if(req_num == 8)  request_sat_status(0x00);
   else if(req_num == 9)  request_eeprom_status();
   else if(req_num == 10) request_sat_list();
   else if(req_num == 11) request_filter_config();
   else if(req_num == 12) request_prodn_params();
   else if(req_num == 13) request_pps();
   else if(req_num == 14) request_dac_voltage();
   else if(req_num == 15) request_osc_sense();
   else if(req_num == 16) request_timing_mode();
   else if(req_num == 17) request_packet_mask();
   else if(req_num == 18) request_survey_params();
   else if(req_num == 19) request_last_raw(0x00);
   else if(req_num == 20) request_all_dis_params();
   else if(req_num == 21) request_sat_health(); 
   else if(req_num == 22) request_rcvr_config(); 
   else if(req_num == 23) request_datum(); 
   else if(req_num == 24) request_pps_mode();
   else if(req_num == 25) request_utc_info();
#define  LAST_REQUEST 26
   else if(req_num == LAST_REQUEST) {
      if(saw_version == 0) {   // no response to message requests
         res_t_init ^= 1;      // try different parity
         init_com();
         redraw_screen();
      }
   }
   else req_num = 0;

   #ifdef SAT_TRAILS
      // here we try to get position info for untracked sats,  but tbolts
      // don't seem to want to give up the goods on untracked sats... but
      // we ask anyway
      if(++status_prn > 32) status_prn = 1;
      request_sat_status(status_prn);
   #endif
}

void timing_msg()
{
   subcode = tsip_byte();

   if     (subcode == 0x15) datums();
   else if(subcode == 0x41) manuf_params();
   else if(subcode == 0x42) prodn_params();
   else if(subcode == 0x4A) pps_settings();
   else if(subcode == 0x4E) get_pps_mode();
   else if(subcode == 0xA0) dac_values();
   else if(subcode == 0xA1) osc_sense();
   else if(subcode == 0xA2) get_timing_mode();
   else if(subcode == 0xA5) packet_mask();
   else if(subcode == 0xA7) sat_solutions();   // not on ThunderBolt-E
   else if(subcode == 0xA8) discipline_params();
   else if(subcode == 0xA9) survey_params();
   else if(subcode == 0xAB) {
      primary_timing();
      // every time we see the 8F.AB message, 
      // ... we also request a different minor message
      request_misc_msg();  
   }
   else if(subcode == 0xAC) secondary_timing();
   else if(subcode == 0xAE) ae_packet();
   else                     unknown_msg(0x8F00 | subcode);
}


void unknown_msg(u16 msg_id)
{
   if(msg_id == 0x13) {
      msg_id = get_next_tsip();
      if(log_comments && log_stream && log_file) {
         fprintf(log_file, "#!! Message rejected: %02X\n      ", msg_id);
         kol = (-1);
      }
   }
   else {
      if(log_comments && log_stream && log_file) {
         fprintf(log_file, "#!! Unknown message: id %02X:\n      ", msg_id);
         kol = (-1);
      }
   }

   tsip_rptr = tsip_wptr = 0;  // flush the tsip buffer
}


void request_rcvr_info()
{
   request_version();
   request_luxor_ver();
   if(luxor_time_set == 0) set_luxor_time();

   request_utc_info();
   request_manuf_params();
   request_prodn_params();

   request_fw_ver();      // !!! testing ThunderBolt-E messages
   request_hw_ver();

   request_pps();
   request_timing_mode();

   request_filter_config();
   request_rcvr_config();
   request_survey_params();

   request_all_dis_params();

   request_sat_list();
}


void abort_wakeup()
{
   // see if user says to stop the wakeup loop
#ifdef WINDOWS
   SAL_serve_message_queue();
   Sleep(0);
#endif
#ifdef USE_X11
   get_x11_event();
#endif
   if(KBHIT()) {
      if(GETCH() == 0x1B) {
         error_exit(666, "Wakeup aborted");
      }
   }
}

void wakeup_nortel()
{
int row, col;
unsigned c;

   // try to wake up the Nortel NTGxxxx unit
   try_nortel = 0;
   saw_nortel = 0;
   if(nortel != 1) return;  

   try_nortel = 0xFF;
   wakeup_tsip_msg = 0;
   waking = 1;

   col = 0;
   row = 1;
   while(wakeup_tsip_msg == 0) {
      vidstr(row,col, RED, "*");
      refresh_page();
      ++col;

      SetDtrLine(1);
      SendBreak();

      request_sig_levels();        // 0x27
      request_rcvr_health();       // 0x26
      request_sat_list();          // 0x24
      request_sat_status(0x00);    // 0x3C
      request_0x21();              // 0x21
      request_io_options();        // 0x35
      request_hw_ver();            // 1C 03
      request_unk_ver();           // 1C 02
      request_version();           // 1F
      request_rcvr_config();       // BB 00
      request_filter_config();     // 70
      twiddle_health(0x03, 0x00);  // 39 03 00
      request_c2();                // C2
      request_7A_00();             // 7A 00
      request_datum();             // 8E 15
      Sleep(500);

      if(1 && process_com) {
         loopy:
         abort_wakeup();
         if(SERIAL_DATA_AVAILABLE()) {
            while(SERIAL_DATA_AVAILABLE()) {
               c = get_serial_char();
               while(c == DLE) {
                  if(SERIAL_DATA_AVAILABLE() == 0) {
                     Sleep(100);
                  }
                  if(SERIAL_DATA_AVAILABLE() == 0) {
                     goto loopy;
                  }
                  c = get_serial_char();
                  if(c == ETX) goto etx_seen;
                  abort_wakeup();
               }
               abort_wakeup();
            }
            Sleep(100);
            goto loopy;
         }
         abort_wakeup();
         continue;
      }

      etx_seen:
      get_pending_gps();
      abort_wakeup();
   }

   waking = 0;
// set_pps_mode(0x02);  // 1pps mode
// request_pps_mode();
}


void init_messages()
{
int i;

   wakeup_nortel();
   if(luxor) {
      request_luxor_ver();
      if(luxor_time_set == 0) set_luxor_time();
   }

//fix_manuf_params();
   set_rcvr_config(7);

   set_packet_mask(0x0055, 0x0000);  // broadcast primary and supplemntal timing packets
                                     // also broadcast satellite solutions, gps system data,  and ephemeris data
// set_packet_mask(0x0065, 0x0000);  // integer
// set_io_options(0x13, 0x03, 0x01, 0x09);  // ECEF+LLA+DBL PRECISION, ECEF+ENU vel,  UTC, PACKET 5A
// set_io_options(0x13, 0x03, 0x01, 0x00);  // ECEF+LLA+DBL PRECISION, ECEF+ENU vel,  UTC, no PACKET 5A, AMU
   set_io_options(0x13, 0x03, 0x01, 0x08);  // ECEF+LLA+DBL PRECISION, ECEF+ENU vel,  UTC, no PACKET 5A, dBc

   if(user_set_delay || set_pps_polarity) {   // set cable delay and pps values
      set_pps(user_pps_enable, user_pps_polarity,  delay_value,  300.0, 0);
   }
   request_pps_mode();


   if(set_osc_polarity) {
      set_osc_sense(user_osc_polarity, 0);
   }

   set_filter_config(user_pv, user_static, user_alt, user_kalman, 0);

   request_rcvr_info();      // get various receiver status messages
   request_rcvr_health();

   request_sat_list();       // get satellite info
   request_last_raw(0x00);
   request_sat_status(0x00);
   request_eph_status(0x00);

   if(log_db == 0) {
      request_sig_levels();  // get signal quality info
   }

   if(do_survey && (user_precision_survey == 0)) {
      set_survey_params(1, 1, do_survey);
      request_survey_params();
      start_self_survey(0x00);
   }


   if(user_init_len) {  // send string of user specified bytes after the standard init commands
      for(i=0; i<user_init_len; i++) sendout(user_init_cmd[i]);
   }

   request_primary_timing();    // get time of day
   request_secondary_timing();
   request_all_dis_params();
}



void parse_tsip_message()
{
   msg_fault = 0x00;
   tsip_rptr = 0;
   msg_id = get_next_tsip();

   subcode = 0x00;
   first_msg = 0;
   last_msg = msg_id;
   ++wakeup_tsip_msg; // we have seen a TSIP message
   tsip_error = 0;    // this flag gets set if we see a start or ETX when we wanted normal data
   ++packet_count;
   if(packet_count == 1L) {
      redraw_screen();     // get rid of any "no serial..." message
   }

   msg_id &= 0xFF;
   if     (msg_id == 0x13) unknown_msg(0x13);
   else if(msg_id == 0x1C) ebolt_version();
   else if(msg_id == 0x41) msg_41();            // ntpx
   else if(msg_id == 0x42) single_ecef_fix();
   else if(msg_id == 0x43) velocity_fix();
   else if(msg_id == 0x45) version_info();
   else if(msg_id == 0x46) ebolt_health1();
   else if(msg_id == 0x47) sig_levels();
   else if(msg_id == 0x49) get_alm_health();
   else if(msg_id == 0x4A) single_lla_fix(); 
   else if(msg_id == 0x4B) ebolt_health2();
   else if(msg_id == 0x55) io_options();
   else if(msg_id == 0x56) enu_velocity_fix();
   else if(msg_id == 0x57) last_fix_info();
   else if(msg_id == 0x58) packet_58();
   else if(msg_id == 0x59) sat_health();
   else if(msg_id == 0x5A) raw_data();
   else if(msg_id == 0x5B) eph_status();
   else if(msg_id == 0x5C) sat_tracking(0x5C);
   else if(msg_id == 0x5D) sat_tracking(0x5D);
   else if(msg_id == 0x5F) eeprom_status();
   else if(msg_id == 0x6D) sat_list();
   else if(msg_id == 0x70) filter_config();
   else if(msg_id == 0x83) ecef_fix();
   else if(msg_id == 0x84) lla_fix();
   else if(msg_id == 0x8F) timing_msg();
   else if(msg_id == 0xBB) rcvr_config();
   else if(msg_id == LUXOR_ID) luxor_packet();
   else                        unknown_msg(msg_id);

   if(com_error) {    // we had a com timeout so were skipping serial reads
      com_error = 0;  // we can stop searching since data is now comming in
   }
}

#ifdef FFT_STUFF

#define MAX(x, y) ((x > y)? x:y)

/* function prototypes for dft and inverse dft functions */
void fft(COMPLEX BIGUN *,int);
void rfft(float BIGUN *,COMPLEX BIGUN *,int);
int  logg2(long);


/**************************************************************************

fft - In-place radix 2 decimation in time FFT

Requires pointer to complex array, x and power of 2 size of FFT, m
(size of FFT = 2**m).  Places FFT output on top of input COMPLEX array.

void fft(COMPLEX *x, int m)

*************************************************************************/

void fft(COMPLEX BIGUN *x, int m)
{
static int mstore = 0;       /* stores m for future reference */
static int n = 1;            /* length of fft stored for future */

COMPLEX u,temp,tm;
COMPLEX BIGUN *xi, BIGUN *xip, BIGUN *xj, BIGUN *wptr;

int i,j,k,l,le,windex;

double arg,w_real,w_imag,wrecur_real,wrecur_imag,wtemp_real;

    if(m != mstore) {  // fft size changed,  redo w array
        /* free previously allocated storage and set new m */
        mstore = m;
        if(m == 0) return;       /* if m=0 then done */

        /* n = 2**m = fft length */
        n = 1 << m;
        le = n/2;

        /* calculate the w values recursively */
        arg = 4.0*atan(1.0)/le;         /* PI/le calculation */
        wrecur_real = w_real = cos(arg);
        wrecur_imag = w_imag = -sin(arg);
        xj = w;
        for(j=1; j<le; j++) {
            xj->real = (float) wrecur_real;
            xj->imag = (float) wrecur_imag;
            xj++;
            wtemp_real = wrecur_real*w_real - wrecur_imag*w_imag;
            wrecur_imag = wrecur_real*w_imag + wrecur_imag*w_real;
            wrecur_real = wtemp_real;
        }
    }

    /* start fft */
    le = n;
    windex = 1;
    for(l=0; l<m; l++) {
       le = le/2;

       /* first iteration with no multiplies */
       for(i=0; i<n; i=i+2*le) {
           xi = x + i;
           xip = xi + le;
           temp.real = xi->real + xip->real;
           temp.imag = xi->imag + xip->imag;
           xip->real = xi->real - xip->real;
           xip->imag = xi->imag - xip->imag;
           *xi = temp;
       }

       /* remaining iterations use stored w */
       wptr = w + windex - 1;
       for(j=1; j<le; j++) {
          u = *wptr;
          for(i=j; i<n; i=i+2*le) {
             xi = x + i;
             xip = xi + le;
             temp.real = xi->real + xip->real;
             temp.imag = xi->imag + xip->imag;
             tm.real = xi->real - xip->real;
             tm.imag = xi->imag - xip->imag;
             xip->real = tm.real*u.real - tm.imag*u.imag;
             xip->imag = tm.real*u.imag + tm.imag*u.real;
             *xi = temp;
          }
          wptr = wptr + windex;
       }
       windex = 2*windex;
    }

    /* rearrange data by bit reversing */
    j = 0;
    for(i=1; i<(n-1); i++) {
        k = n/2;
        while(k <= j) {
           j = j - k;
           k = k/2;
        }
        j = j + k;
        if(i < j) {
           xi = x + i;
           xj = x + j;
           temp = *xj;
           *xj = *xi;
           *xi = temp;
        }
    }
}

/************************************************************

rfft - trig recombination real input FFT

Requires real array pointed to by x, pointer to complex
output array, y and the size of real FFT in power of
2 notation, m (size of input array and FFT, N = 2**m).
On completion, the COMPLEX array pointed to by y
contains the lower N/2 + 1 elements of the spectrum.

void rfft(float *x, COMPLEX *y, int m)

***************************************************************/

void rfft(float BIGUN *x, COMPLEX BIGUN *y, int m)
{
static    int      mstore = 0;
int       p,num,k;
float     Realsum, Realdif, Imagsum, Imagdif;
double    factor, arg;
COMPLEX   BIGUN *ck, BIGUN *xk, BIGUN *xnk, BIGUN *cx;

   /* First call the fft routine using the x array but with
      half the size of the real fft */

    p = m - 1;
    cx = (COMPLEX BIGUN *) x;
    fft(cx, p);

    /* Next create the coefficients for recombination, if required */
    num = (1 << p);    /* num is half the real sequence length.  */

    if(m != mstore) { // fft size changed,  redo cf array
       mstore = m;  

       factor = 4.0*atan(1.0)/num;
       for (k = 1; k < num; k++){
         arg = factor*k;
         cf[k-1].real = (float)cos(arg);
         cf[k-1].imag = (float)sin(arg);
       }
    }

    /* DC component, no multiplies */
    y[0].real = cx[0].real + cx[0].imag;
    y[0].imag = 0.0;

    /* other frequencies by trig recombination */
    ck = cf;
    xk = cx + 1;
    xnk = cx + num - 1;
    for (k = 1; k < num; k++){
      Realsum = ( xk->real + xnk->real ) / 2;
      Imagsum = ( xk->imag + xnk->imag ) / 2;
      Realdif = ( xk->real - xnk->real ) / 2;
      Imagdif = ( xk->imag - xnk->imag ) / 2;

      y[k].real = Realsum + ck->real * Imagsum
                          - ck->imag * Realdif ;

      y[k].imag = Imagdif - ck->imag * Imagsum
                          - ck->real * Realdif ;
      ck++;
      xk++;
      xnk--;
    }
}

/**************************************************************************

logg2 - base 2 logarithm

Returns base 2 log such that i = 2**ans where ans = logg2(i).
if logg2(i) is between two values, the larger is returned.

int logg2(unsigned int x)

*************************************************************************/

int logg2(long x)
{
    unsigned long mask,i;

    if(x == 0) return(-1L);     /* zero is an error, return -1 */
    x--;                        /* get the max index, x-1 */

    for(mask=1,i=0; ; mask*=2,i++) {
        if(x == 0) return(i);   /* return logg2 if all zero */
        x = x & (~mask);        /* AND off a bit */
    }
}




long process_signal(long length, int id)
{
long i;
long last_i;
long j;
int k;
struct PLOT_Q q;
float show_time;
float a;
float tempflt;
float fft_max, fft_min;

   plot_column = 0;

   j = 0;
   i = plot_q_col0;
   fft_queue_0 = i;
   while(i != plot_q_in) {  // copy queue data to FFT buffers
      if(filter_count) q = filter_plot_q(i);
      else             q = get_plot_q(i);

      tsignal[j] = q.data[id];  // * window[j];
      if(++j >= length) {
         break;  // buffer is full
      }

      i = next_q_point(i, 0);
      if(i < 0) {
         break;
      }
   }

   if(j <= 0) {
      fft_length = 0;
      goto done;
   }

   length = (1 << logg2(j));  // adjust fft length for short data
   if(length > j) length /= 2;
   if(length > max_fft_len) length = max_fft_len;

   fft_scale = 1;
   fft_length = length;
   if(fft_length < 2) goto done;  //fft_scale = 1;
   else               fft_scale = ((view_interval * (long)SCREEN_WIDTH) / (fft_length/2L));
   if(fft_scale < 1)  fft_scale = 1;

   show_time = ((float) (fft_length)) * ((float) view_interval);  // seconds per screen
   show_time /= (float) plot_mag;
   if(show_time < (2.0F*3600.0F)) sprintf(out, "%.1f min", show_time/60.0F);
   else                           sprintf(out, "%.1f hrs", show_time/3600.0F);
   if(title_type != USER) {
      sprintf(plot_title, "%ld point FFT of %s of%s%s data.", 
          fft_length, out, show_live_fft?" live ":" ", plot[id].plot_id);
      title_type = OTHER;
   }

   a = (float) fft_length * (float) fft_length;
   rfft(&tsignal[0], fft_out, logg2(fft_length));

   fft_max = (-1.0E30F);
   fft_min = (1.0E30F);
   for(j=1; j<fft_length/2; j++) {
      tempflt  = fft_out[j].real * fft_out[j].real;
      tempflt += fft_out[j].imag * fft_out[j].imag;
      if(tempflt > fft_max) fft_max = tempflt;
      if(tempflt < fft_min) fft_min = tempflt;
   }
   if(fft_max == 0.0F) fft_max = 1.0F;

   plot_column = 0;
   j = 0;
   i = last_i = plot_q_col0;

   // place fft results into the plot queue FFT plot data
   while(i != plot_q_in) {  
      for(k=0; k<fft_scale; k++) { // expand plot horizontally so that it is easier to read
         q = get_plot_q(i);

         if(j >= fft_length/2) q.data[FFT] = 0.0F;  // fill out queue with 0's
         else if(j == 0)       q.data[FFT] = 0.0F;  // drop the DC value because it messes up scaling
         else {   // insert FFT results into plot queue data
            tempflt  = fft_out[j].real * fft_out[j].real;
            tempflt += fft_out[j].imag * fft_out[j].imag;
            if(fft_db) {  // calc FFT in dB
              tempflt /= a;
              tempflt = (float) (10.0 * log10(MAX(tempflt, 1.e-16))) ;
            }
            else {
               tempflt /= fft_max;
            }
            q.data[FFT] = tempflt;
            last_i = i;
         }
         if(j == 1) mark_q_entry[1] = i;

         put_plot_q(i, q);
         if(++i == plot_q_in) goto done;
         while(i >= plot_q_size) i -= plot_q_size;
      }
      j++;
if((j >= fft_length/2) && (j >= SCREEN_WIDTH*2)) break;
   }

   done:
   mark_q_entry[2] = last_i;
   return j;
}

void set_fft_scale()
{
   if(fft_db) {
      plot[FFT].user_scale = 0;
      plot[FFT].scale_factor = 1.0F;
      plot[FFT].plot_center = 0.0F;
      plot[FFT].float_center = 1;
   }
   else {
      plot[FFT].scale_factor = 1.0F / ((float) PLOT_HEIGHT/(float)(VERT_MAJOR*2));
      plot[FFT].user_scale = 1;
      plot[FFT].plot_center = 0.0F;
      plot[FFT].float_center = 0;
   }
}

long calc_fft(int id)
{
long length, m;
long points;

   if(id == FFT) {
     edit_error("Cannot calculate the FFT of the FFT plot!");
     return 0;
   }

   length = max_fft_len;
   m = logg2(length);
   if((1<<m) != length){  /* Check for power of 2 input size */
     edit_error("FFT size must be power of 2.");
     return 0;
   }

   fps = ((1.0F/view_interval)/2.0F) / (float) (length/2);
   points = process_signal(length, id);

   // set scale factors and enable the FFT plot
   if(show_live_fft == 0) {
      set_fft_scale();
      plot[FFT].show_stat = 1;
      if(plot[FFT].show_plot == 0) toggle_plot(FFT);
   }

   return points;
}

#endif // FFT_STUFF

