#define EXTERN extern
#include "heather.ch"

//  Thunderbolt TSIP monitor
//
//  Copyright (C) 2008,2009 Mark S. Sims - all rights reserved
//  Win32 port by John Miles, KE5FX (jmiles@pop.net)
//
//
//  This file contains most of the user interface stuff.
//  Abandon all hope, ye mortals who dain to understand it...
//  It makes my noggin throb,  and I wrote it...
//

int last_was_mark;
u08 aa_val;
u08 all_plots;
extern char *dst_list[];
extern float k6, k7, k8, integrator;
extern double osc_k6, osc_k7, osc_k8, osc_integrator;

#define GRAPH_LLA 1     // if 1,  make graphs 1,2,3 lat/lon/alt if rcvr is in 3D mode

// text editing stuff
u08 first_edit;
u08 insert_mode;
u08 edit_cursor;
u08 no_auto_erase;
u08 dos_text_mode;
int e_row;
char mode_string[SLEN+1];     // the last driver mode change string used

int getting_plot;
int amu_flag = 0x08;

float scale_step;
float center_step;

void set_steps(void);

// extended codes for identifiing edit strings
#define DRVR_MODE      0x0100   // driver mode change
#define PC_CMD         0x0101   // load protection overcurrent
#define PH_CMD         0x0102   // battery HVC
#define PL_CMD         0x0103   // battery LVC
#define PM_CMD         0x0104   // message watchdog timeout
#define PO_CMD         0x0105   // battery overcurrent
#define PP_CMD         0x0106   // load overwatts
#define PR_CMD         0x0107   // protection fault reset
#define PS_CMD         0x0108   // temp2 overtemp
#define PT_CMD         0x0109   // temp1 overtemp
#define PU_CMD         0x010A   // load undervoltage
#define PV_CMD         0x010B   // load overvoltage
#define PX_CMD         0x010C   // auxv overvoltage
#define PW_CMD         0x010D   // battery overwatts
#define PZ_CMD         0x010E   // auxv undervoltage
#define WC_CMD         0x010F   // write config data to file
#define S_CMD          0x0110   // lat, lon, alt

#define AMPL_CMD       0x0120   // lux sensitivity
#define AMPU_CMD       0x0121   // lumen sensitivity
#define AMPE_CMD       0x0122   // IR1 emissivity
#define AMPI_CMD       0x0123   // IR2 emissivity
#define AMPS_CMD       0x0124   // serial number
#define AMPV_CMD       0x0125   // reference voltage
                            
#define BC_CMD         0x0130   // constant current load mode
#define BF_CMD         0x0131   // 3.60V LiFePO4 charge mode
#define BH_CMD         0x0132   // high voltage lipo charge mode
#define BL_CMD         0x0133   // 4.20V lipo charge mode
#define BP_CMD         0x0134   // battery PWM resolution (8/9/10 bit)
#define BR_CMD         0x0135   // pwm sweep rate
#define BS_CMD         0x0136   // pwm sweep
#define BV_CMD         0x0137   // constant load voltage mode
#define BW_CMD         0x0138   // constant load wattage mode

#define CAL_CMD        0x0140   // calibration constants


//
//  Keyboard processor
//

void key_wait(char *s)
{
// debug routine - display message and wait for key
strcpy(plot_title, s);
title_type = OTHER;
show_title();
refresh_page();
BEEP();
   while(1) {
      #ifdef WINDOWS
         SAL_serve_message_queue();
         Sleep(0);
      #endif
      #ifdef USE_X11
         get_x11_event();
      #endif
      if(KBHIT()) break;
   }
   GETCH();
BEEP();
}

FILE *topen(char *f, char *m)
{
char c;

   // open a file,  trim leading whitespace
   while(*f) {
      c = *f;
      if((c == ' ') || (c == '\t')) ++f;
      else break;
   }

printf("topen(%s, %s)\n", f,m);  //zork
   return fopen(f, m);
}

void kbd_help()
{
char *s, *ems_info;
COORD help_row, help_col;
COORD row, col;
COORD help_row_1;

   // this routine displays help info about the keyboard commands 
   // until a key is pressed

   request_version(); // so the "Press space for help" message gets updated quickly
   plot_version = 1;  // once asked for help,  switch help message to version 
                      // display since the user should now know that help exists
   if(1 || (process_com == 0)) {
      osc_params = 0;
      erase_screen();
      redraw_screen();
   }

   // !!! kludge: for undersized screens
   if(screen_type == 't') {   // text mode
      no_x_margin = no_y_margin = 1;
   }
   else if(SCREEN_HEIGHT <= 600) {  // small graphics screens
      text_mode = 2;  // say we are in text mode while help is displayed
      no_x_margin = no_y_margin = 1;
   }

   if(text_mode) {   // full screen help mode
      if(SCREEN_WIDTH >= 800) {  // there is room for a margin
         help_row = 3;
         help_col = 3;
      }
      else {         // no margin space available
         help_row = 0;
         help_col = HELP_COL;
      }
      erase_screen();
   }
   else {            // help is in the plot area
      help_row = HELP_ROW;
      help_col = HELP_COL+3;
      #ifdef DOS
        erase_help();
      #endif
   }

   row = help_row;
   col = help_col + 0;

   if(text_mode && ems_ok) s = "";
   else s = "Control ";
   if(ems_ok) ems_info = " - EMS";
   else       ems_info = "";
   if(TEXT_COLS <= 100) {
      if(luxor) sprintf(out, "Luxor Power/LED Analyzer %sProgram", s);
      else      sprintf(out, "Lady Heather's Disciplined Oscillator %sProgram", s);
      vidstr(row,col,  HELP_COLOR, out);
      ++row;

      sprintf(out, "Rev %s - %s %s%s", VERSION, date_string, __TIME__, ems_info);
      vidstr(row,col,  HELP_COLOR, out);
      ++row;

      vidstr(row,col,  HELP_COLOR, "Press any key to continue...");
      ++row;
      ++row;
   }
   else {
      if(luxor) sprintf(out, "Luxor Power/LED Analyzer %sProgram.  Rev %s - %s %s%s", s, VERSION, date_string, __TIME__, ems_info);
      else      sprintf(out, "Lady Heather's Disciplined Oscillator %sProgram.  Rev %s - %s %s%s", s, VERSION, date_string, __TIME__, ems_info);
      vidstr(row,col,  HELP_COLOR, out);
      ++row;

      vidstr(row,col,  HELP_COLOR, "Press any key to continue...");
      ++row;
      ++row;
   }
   help_row = row;

   if(script_file) {  // error was in a script file,  abandon script
      sprintf(out, "Unknown command seen in script file: %s line %d, col %d: %c", 
         script_name, script_line, script_col, script_err);
      vidstr(row, col,  HELP_COLOR, out);
      close_script(1);
      goto help_exit;
   }

   #ifdef ADEV_STUFF
      if(luxor == 0) {
         s = "a - select Adev type to display";
         vidstr(row++, col,  HELP_COLOR, s);
      }
   #endif

   if(luxor) {
      s = "b - Battery capacity/resistance";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   s = "c - Clear queues or reset data";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor == 0) {
      s = "d - set osc Disciplining / DAC voltage";
      vidstr(row++, col,  HELP_COLOR, s);

      s = "e - save current config to EEPROM";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   if(luxor) s = "f - change display Filter";
   else      s = "f - toggle Filter or signal/elev masks";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "g - modify Graph or screen display";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor == 0) {
      s = "h - toggle manual Holdover mode";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   s = "i - set the plot queue update Interval";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor == 0) {
      if(timing_mode & 0x02) s = "j - Jam sync PPS to UTC time";
      else                   s = "j - Jam sync PPS to GPS time";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   s = "l - data Logging";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor) {
      s = "m - change LED driver Mode";
      vidstr(row++, col,  HELP_COLOR, s);

      s = "p - set Protection values";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   s = "r - Read in a file";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor) s = "s - enter position (lat lon alt)";
   else      s = "s - Survey/enter position/show fixes";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "t - Time and temperature control";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor) {
      if(pause_data) s = "u - resume plot queue Updates";
      else           s = "u - pause plot queue Updates";
      vidstr(row++, col,  HELP_COLOR, s);

      s = "v - set View time span of plot window";
      vidstr(row++, col,  HELP_COLOR, s);
   }
   else {
      if(pause_data) s = "u - resume plot/adev queue Updates";
      else           s = "u - pause plot/adev queue Updates";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   #ifdef DOS    
      help_row_1 = row;
      row = help_row;
      col = help_col + 40;
   #else
      help_row_1 = row;
      row = help_row;
      col = help_col + 40;
   #endif


   if(luxor) {
      s = "w - Write data, screen, delete file";
      vidstr(row++, col,  HELP_COLOR, s);
   }
   else {
      s = "v - set View time span of plot window";
      vidstr(row++, col,  HELP_COLOR, s);

      s = "w - Write data, screen, delete file";
      vidstr(row++, col,  HELP_COLOR, s);
   }

   sprintf(out, "x - view graphs at 1 hr/div");
   vidstr(row++, col,  HELP_COLOR, out);

   if(day_size) sprintf(out, "y - view graphs at %d hr/screen", day_size);
   else         sprintf(out, "y - view graphs at %d hr/screen", 24);
   vidstr(row++, col,  HELP_COLOR, out);

   if(luxor) s = "z - Zoom fullscreen clocks";
   else      s = "z - Zoom fullscreen clocks and maps";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "-+  lower/raise last selected graph";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "{}  shrink/grow last selected graph";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "! - do a Warm, Cold, or Hard reset";
   vidstr(row++, col,  HELP_COLOR, s);

   if(luxor) s = "& - change calibration parameters";
   else      s = "& - change oscillator/signal parameters";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "/ - startup (command line) only options";
   vidstr(row++, col,  HELP_COLOR, s);

   #ifdef GIF_FILES
      if(luxor) s = "\\ - dump screen to LUXOR.GIF";
      else      s = "\\ - dump screen to TBOLT.GIF";
   #else
      if(luxor) s = "\\ - dump screen to LUXOR.BMP";
      else      s = "\\ - dump screen to TBOLT.BMP";
   #endif
   vidstr(row++, col,  HELP_COLOR, s);

   s = "$ - change screen resolution";
   vidstr(row++, col,  HELP_COLOR, s);

   #ifdef WINDOWS
      s = "F11 - toggle fullscreen mode";
      vidstr(row++, col,  HELP_COLOR, s);

      s = "? - display command line help";
      vidstr(row++, col,  HELP_COLOR, s);
   #endif

   if(text_mode) {  // full screen help
      col = help_col;
      row = help_row_1 + 1;
      help_row_1 = row;
   }
   else {           // help in the plot area
      row = help_row;
      col = help_col + 80;
   }

   s = "HOME - scroll plot to beginning of data";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "END - scroll plot to end of data";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "LEFT - scroll plot forward one division";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "RIGHT - scroll plot back one division";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "PG UP - scroll plot forward one screen";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "PG DN - scroll plot back one screen";
   vidstr(row++, col,  HELP_COLOR, s);

   if(text_mode && (SCREEN_HEIGHT < 600)) {
      row = help_row_1;
      col = help_col + 40;
   }

   s = "UP - scroll plot forward one hour";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "DOWN - scroll plot back one hour";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "<>  scroll plot one day";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "[]  scroll plot one pixel";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "% - scroll to next error event";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "DEL - return plotting back to normal";
   vidstr(row++, col,  HELP_COLOR, s);

   s = "0..9,=,+,- set or move to plot markers";
   vidstr(row++, col,  HELP_COLOR, s);

   help_exit:
   refresh_page();
}


void second_key(int c)
{
   // process second  keystroke of a two key command
   if(c == first_key) {  // the user confirmed a dangerous single char command
      if(c != '?') BEEP();
   }
   else {  // single char command not confirmed
      if(script_file) {
         erase_plot(1);
         sprintf(out, "Selection '%c' for command '%c' not recognized", c, first_key);
         edit_error(out);
      }
      if(text_mode) redraw_screen();
   }

   first_key = 0;  // clear message and resume graphing
   if(screen_type == 't') {
      no_x_margin = no_y_margin = 0;
   }
   else if(SCREEN_HEIGHT <= 600) { // !!! kludge: for undersized screen
      text_mode = 0;
      no_x_margin = no_y_margin = 0;
      redraw_screen();
   }

   if(text_mode) {
      redraw_screen();
   }
   else {
     erase_help();
     draw_plot(1);
   }
}


int are_you_sure(int c)
{
char *s1;
char *s2;
char *s3;
char *s4;
char *s5;
char *s6;
u08 two_char;
char key[6];
COORD row, col;
int i;

   // This routine supports the two character keyboard commands.
   // It either prompts for the second character of the command or 
   // asks for confirmation on single character commands that do 
   // something semi-dangerous.

   s1 = s2 = s3 = s4 = s5 = s6 = 0;
   two_char = 0;
   if(c != '&') {   // command is not the osc parameter command
      if(osc_params) {      // we are showing the osc parameters
         redraw_screen();
         if(process_com) {
//----      osc_params = 0;    // disable the osc param display
         }
      }
   }
   else {
      show_satinfo();
   }

   if(first_key) {   // this is the second keystroke of a two char command
      second_key(c);
      return c;
   }

   // This is the first keystroke of a command.
   // Either the user wants to do something dangerous... so ask the annoying question
   // or else prompt for the second keystroke of the two character commands.

   first_key = c;    // first_key is first char of the command we are doing
   if(first_key != 'p') prot_menu = 0;
   erase_help();     // erase any old help info
   refresh_page();

   if(c == '?') {    // the user wants some help
      kbd_help();    // show the help
      return 0;
   }

   row = EDIT_ROW;
   col = EDIT_COL;
   if(text_mode) {
      erase_screen();
      if(osc_params) {  
         show_osc_params(row+8, col);
      }
   }

   if(c == ESC_CHAR) {
      s1 = "This will exit the program";
   }
#ifdef ADEV_STUFF
   else if(c == 'a') {
      s1 = "Display adev type:  A)dev  H)dev  M)dev  T)dev    all O)sc  all P)ps";
      two_char = 1;
   }
#endif
   else if(luxor && (c == 'b')) {
      s1 = "Battery:  I)nternal resistance measurement   P)WM resolution";
      s2 = "Constant: V)oltage  C)urrent     W)atts      S)weep pwm   R)ate";
      s3 = "Charge:   L)iPo     F)LiFePO4    H)igh voltage LiPo";
      two_char = 1;
   }
   else if(c == 'c') {
      if(luxor) {
         s1 = "Clear plot queue";
      }
      else {
         s1 = "Clear A)dev queue only   B)oth plot and adev queues   P)lot queue only";
         s2 = "      L)LA fix data   S)ignal level data   R)eload adevs from plot window";
         two_char = 1;
      }
   }
   else if(c == 'd') {
      s1 = "Oscillator discipline:  E)nable  D)isable    S)et DAC voltage";
      two_char = 1;
   }
   else if(c == 'e') {
      s1 = "This will save the current configuration into EEPROM";
   }
   else if(c == 'f') {
      if(luxor) {
         s1 = "Enter filter to change: D)isplay";
      }
      else {
         s1 = "Enter filter to change: P)v  S)tatic  A)ltitude  K)alman     D)isplay";
         if(res_t == 2) {
            s2 = "                        signal L)evel (in dBc)   E)levation mask (degrees)";
            s3 = "                        J)amming mode";
         }
         else {
            s2 = "                        signal L)evel (in amu)   E)levation mask (degrees)";
            s3 = "                        F)oliage mode    M)ovement   X)PDOP mask/switch";
         }
         two_char = 1;
      }
   }
   else if(c == 'g') {
      if(luxor) {
         s1 = "Display: C)apacity D)BATTv   O)BATTi   F)FT      T)emperature";
         s2 = "         P)lux     I)BATTw   J)LEDw    K)eff     L)CCT";
         s3 = "         1)lumens  2)LEDv    3)LEDi    4)PWM     5)TEMP2";
         s4 = "         6)BLUE    7)GREEN   8)RED     9)WHITE   0)AUXv";
         s6 = "         R)edraw   S)ound    W)atch    B)oth     G)raph title   A)prots";
         s5 = "         E)rrors   U)pdates  /)change statistic";
      }
      else if(res_t) {
         s1 = "Display: A)dev B)oth map & adev tables C)ount D)corr E)rrors F)FT  G)raph title";
         s2 = "         H)oldover  L)ocation  M)ap,no adev tables  O)rate  P)bias  R)edraw  S)ound";
         s3 = "         T)emperature  U)pdates  W)atch  X)dops  Z)clock  /)change statistic";
      }
      else {
         s1 = "Display: A)dev B)oth map & adev tables C)ount D)ac E)rrors F)FT  G)raph title";
         s2 = "         H)oldover  L)ocation  M)ap,no adev tables  O)sc  P)ps  R)edraw  S)ound";
         s3 = "         T)emperature  U)pdates  W)atch  X)dops  Z)clock  /)change statistic";
      }
      two_char = 1;
   }
   else if(c == 'h') {
      if(user_holdover)  s1 = "This will exit user Holdover mode";
      else               s1 = "This will enter user Holdover mode";
   }
   else if(c == 'j') {
      if(timing_mode & 0x02)   s1 = "This will Jam sync the PPS output to UTC time";
      else                     s1 = "This will Jam sync the PPS output to GPS time";
   }
   else if(c == 'l') {
      if(log_file) s1 = "S)top logging data to file";
      else         s1 = "Log:  A)ppend to file   W)rite to file   D)elete file   I)nterval";
      if(log_db)   s2 = "      stop C)onstellation data in log file";
      else         s2 = "      add C)onstellation data to log file";
      two_char = 1;
   }
   else if(luxor && (c == 'p')) {
      s1 = "Battery:     H)igh voltage cutoff  L)ow voltage cutoff   W)atts   C)over current";
      s2 = "LED:         V)over voltage        U)nder voltage        P)ower   O)ver current";
      s3 = "AUXV:        X)over voltage        Z)under voltage";
      s4 = "Temperature: T)emp1 overtemp       S)temp2 overtemp";
      s5 = "Misc:        M)sg timeout          R)eset protection faults";
      prot_menu = 1;
      two_char = 1;
   }
   else if(c == 's') {
      #ifdef PRECISE_STUFF
         if(check_precise_posn)     s1 = "Enter L to abort the precise lat/lon/altitude save (ESC to ignore)";
         else if(precision_survey)  s1 = "Enter P to abort the Precison survey (ESC to ignore)";
         else if(doing_survey)      s1 = "Enter S to abort the Standard survey (ESC to ignore)";
         else if(show_fixes)        s1 = "Enter F to return to overdetermined clock mode (ESC to ignore)";
         else {
            s1 = "S)tandard survey     P)recision 48 hour survey  or";
            s2 = "enter L)at/lon/alt   do 2D/3d F)ixes   3)D fixes only";
            s3 = "O)ne sat mode   0)..7) set receiver mode   A)ntenna survey";
         }
      #else
         s1 = "S)tandard survey    (ESC to ignore)";
         s2 = "enter L)at/lon/alt   do 2D/3d F)ixes   3)D fixes only";
         s3 = "O)ne sat mode   0)..7) set receiver mode";
      #endif
      if(luxor == 0) two_char = 1;
   }
   else if(c == 't') {
      if(luxor) {
         s1  = "A)larm time   cH)ime clock";
         #ifdef TEMP_CONTROL
            s2 = "eX)it time    time Z)one      T)emperature control";
         #else
            s2 = "eX)it time    time Z)one";
         #endif
         s3  = "screen D)ump time    L)og dump time";
      }
      else {
         s1  = "A)larm time   cH)ime clock    use G)PS time   use U)TC time";
         #ifdef TEMP_CONTROL
            s2 = "eX)it time    time Z)one      S)et system time    T)emperature control";
         #else
            s2 = "eX)it time    time Z)one      S)et system time";
         #endif
         s3  = "screen D)ump time    L)og dump time";
      }
      two_char = 1;
   }
   else if(c == 'u') {
      if(pause_data) s1 = "This will resume plot/adev queue Updates";
      else           s1 = "This will pause plot/adev queue Updates";
   }
   else if(c == 'w')  {
      if(filter_log) s1 = "Write to file:  A)ll queue data   P)lot area    D)elete file   unF)iltered data";
      else           s1 = "Write to file:  A)ll queue data   P)lot area    D)elete file   F)iltered data";
      if(luxor) {
         s2 = "                S)creen dump      R)everse video screen dump   L)og";
         s4 = "                C)onfig data      &)calibration data";
      }
      else {
         s2 = "                S)creen dump      R)everse video screen dump   L)og  aZ)el data";
      }
         s3 = "                G)raph area dump  I)nverse video graph area dump";
      two_char = 1;
   }
   else if(c == '&') {
      if(luxor) {
         s1 = "Light sens:  L)ux  U)lumens";
         s2 = "IR sensor:   E)IR1 emissivity   I)IR2 emissivity";
         s3 = "Mode:        C)alibration mode";
      }
      else if(res_t) {
         s1 = "Tune:        A)utotune elevation and signal level masks";
         s2 = "PPS output:  1)PPS mode   2)PP2S mode   toggle P)ps polarity   PP(S) enable";
         s3 = "Signals:     C)able delay";           
      }
      else {
         s1 = "EFC voltage:  I)initial  mi(N)  ma(X)   or   A)utotune osc params";
         s2 = "Oscillator:   D)amping   max F)req   G)ain   J)am thresh   T)ime const";
         s3 = "Signals:      C)able delay   toggle O)sc or P)ps polarity  toggle PP(S)";
      }
      two_char = 1;
   }
   else if(c == '!') {
      if(luxor) s1 = "W)arm reset   C)old reset   H)ard reset to factory settings";
      else      s1 = "W)arm reset   C)old reset   H)ard reset to factory settings   send B)reak";
      two_char = 1;
   }
   else if(c == '$') {
      s1 = "Select screen size:  T)ext   U)ndersized   or ";
      s2 = "   S)mall  M)edium  N)etbook  L)arge  V)ery large";
      s3 = "   eX)tra large  H)uge  Z)humongous";
      two_char = 1;
   }

   // display the command menu options
   i = 0;
   if(s1) vidstr(row+0, col, PROMPT_COLOR, s1);
   if(s2) vidstr(row+1, col, PROMPT_COLOR, s2);
   if(s3) vidstr(row+2, col, PROMPT_COLOR, s3);
   if(s4) { vidstr(row+3, col, PROMPT_COLOR, s4); i = 1; }
   if(s5) { vidstr(row+4, col, PROMPT_COLOR, s5); i = 2; }
   if(s6) { vidstr(row+5, col, PROMPT_COLOR, s6); i = 3; }

   if(two_char == 0) {     // it is a single character keyboard command
      if(c == ESC_CHAR) {  // user wants to exit
         sprintf(out, "Press 'y' if you are sure...");
      }
      else {
         key[0] = first_key;
         key[1] = 0;
         sprintf(out, "Press '%s' again if you are sure...", key);
      }
      vidstr(row+3+i, col, PROMPT_COLOR, out);
   }

   vidstr(row+4+i, col, PROMPT_COLOR, "Press any other key to ignore...");
   refresh_page();

   return 0;
}

u08 edit_string(int c)
{
int row, col;
int attr;
char s[2];

   // perform an edit operation on the text string that we are building

   edit_ptr = strlen(edit_buffer);

   if(c == INS_CHAR) { // toggle insert mode
      insert_mode ^=1;
      first_edit = 0;
   }
   else if(c == LEFT_CHAR) {   // move cursor left
      if(edit_cursor) --edit_cursor;
      else BEEP();
      first_edit = 0;
   }
   else if(c == RIGHT_CHAR) {  // move cursor right
      if(++edit_cursor >= edit_ptr) {  // if past end of string, append blanks
         c = ' ';
         goto add_char;
      }
      first_edit = 0;
   }
   else if(c == END_CHAR) {  // move end-of-line
      edit_cursor = edit_ptr;
      first_edit = 0;
   }
   else if(c == HOME_CHAR) {  // move to start of line
      edit_cursor = 0;
      first_edit = 0;
   }
   else if(c == DOWN_CHAR) {  // delete to end-of-line
      edit_buffer[edit_cursor] = 0;
      first_edit = 0;
   }
   else if(c == UP_CHAR) {  // delete to start-of-line
      strcpy(out, &edit_buffer[edit_cursor+1]);
      strcpy(edit_buffer, out);
      edit_cursor = edit_ptr = 0;  // strlen(edit_buffer);
      first_edit = 0;
   }
   else if(c == DEL_CHAR) {  // delete char at cursor
      delete_char:
      if(edit_buffer[edit_cursor]) {
         strcpy(out, edit_buffer);
         strcpy(&edit_buffer[edit_cursor], &out[edit_cursor+1]);
         edit_ptr = strlen(edit_buffer);
      }
      else if(edit_cursor) {
         --edit_cursor;
         goto delete_char;
      }
      else BEEP();
      first_edit = 0;
   }
   else if(c == 0x08) { // back up and delete a char
      if(edit_cursor) {
         --edit_cursor;
         goto delete_char;
      }
      else BEEP();
   }
   else if(c >= 0x0100) {  // ignore unused cursor and function keys
   }
   else if(c == ESC_CHAR) {  // erase edit buffer
      if(edit_ptr) {  // if something is in the buffer,  erase the buffer
         edit_ptr = edit_cursor = c = 0;
         edit_buffer[edit_ptr] = 0;
      }
      else {  // ESC with nothing in the buffer,  abandon the edit
         first_edit = 0;
         no_auto_erase = 0;
         if(luxor && (prot_menu || show_prots)) {
            prot_menu = 0;
            redraw_screen();
         }
         return ESC_CHAR;
      }
   }
   else if(c == 0x0D) {  // end of edit
      script_pause = 0;
      first_edit = 0;
   }
   else if(c) {  // normal text char - insert it into the buffer
      if(first_edit && (no_auto_erase == 0)) {  // first char typed erases old buffer contents
         edit_ptr = 0;
         edit_buffer[edit_ptr++] = c;
         edit_buffer[edit_ptr] = 0;
         edit_cursor = edit_ptr;
      }
      else if(insert_mode) {
         if(edit_ptr >= (SLEN-1)) {  // gone too far
            edit_ptr = (SLEN-1);
            edit_buffer[edit_ptr] = 0;
            BEEP();
         }
         else if(edit_ptr >= (TEXT_COLS-3)) {  // gone too far
            edit_ptr = (TEXT_COLS-3);
            edit_buffer[edit_ptr] = 0;
            BEEP();
         }
         else {
            strcpy(out, &edit_buffer[edit_cursor]);
            edit_buffer[edit_cursor] = c;
            strcpy(&edit_buffer[edit_cursor+1], out);
            ++edit_cursor;
            edit_ptr = strlen(edit_buffer);
         }
      }
      else {  // overwrite mode
         add_char:
         if(edit_cursor >= edit_ptr) {  // append char to end of string
            if(edit_ptr >= (SLEN-1)) {  // gone too far
               edit_ptr = (SLEN-1);
               edit_buffer[edit_ptr] = 0;
               edit_cursor = edit_ptr;
               BEEP();
            }
            else if(edit_ptr >= (TEXT_COLS-3)) {  // gone too far
               edit_ptr = (TEXT_COLS-3);
               edit_buffer[edit_ptr] = 0;
               edit_cursor = edit_ptr;
               BEEP();
            }
            else {
               edit_buffer[edit_ptr] = c;
               edit_buffer[++edit_ptr] = 0;
               edit_cursor = edit_ptr;
               edit_ptr = strlen(edit_buffer);
            }
         }
         else {  // replace char in the string at the cursor
            edit_buffer[edit_cursor++] = c;
         }
      }

      c = 0;
      first_edit = 0;
   }

   if(first_edit == 0) no_auto_erase = 0;

   dos_text_mode = 0;
   attr = WHITE;
   #ifdef DOS
      dos_text_mode = text_mode;
   #endif

   col = TEXT_COLS-SLEN-2;
   if(col < 0) col = 0;
   vidstr(e_row, EDIT_COL, WHITE, &blanks[col]);

   // kludgy,  but no-brainer way to erase old edit cursor
   col = (EDIT_COL+1+edit_cursor) * TEXT_WIDTH;
   row = e_row * TEXT_HEIGHT;
   if(row < PLOT_TEXT_ROW) {  // undo Windows margin offsets
      if(no_x_margin == 0) col += TEXT_X_MARGIN;
      if(no_y_margin == 0) row += TEXT_Y_MARGIN;
   }
   if(dos_text_mode == 0) {
      line(0,row+TEXT_HEIGHT, SCREEN_WIDTH-1,row+TEXT_HEIGHT, BLACK);
      line(0,row+TEXT_HEIGHT+2, SCREEN_WIDTH-1,row+TEXT_HEIGHT+2, BLACK);
   }

   sprintf(out, ">%s", edit_buffer);
   vidstr(e_row, EDIT_COL, WHITE, out);
   if(c != 0x0D) {  // draw the edit cursor under the char
      if(dos_text_mode) {
         if(insert_mode) attr = CYAN<<4;
         else            attr = WHITE<<4;
         s[0] = edit_buffer[edit_cursor];
         if(s[0] == 0) s[0] = ' ';
         s[1] = 0;
         blank_underscore = 0;
         vidstr(row/TEXT_HEIGHT, col/TEXT_WIDTH, attr, s);
         blank_underscore = 1;
      }
      else {
         line(col,row+TEXT_HEIGHT, col+TEXT_WIDTH-1,row+TEXT_HEIGHT, PROMPT_COLOR);
         if(insert_mode) line(col,row+TEXT_HEIGHT+2, col+TEXT_WIDTH-1,row+TEXT_HEIGHT+2, PROMPT_COLOR);
      }
   }

   if(0 && script_file && (script_pause == 0)) ;  // this makes script go faster,  but you can't see what is happening
   else refresh_page();

   return c;
}




#define BLANK_LINES_OK ((getting_string != ':') && (getting_string != '/') && (getting_string != '*') && (getting_string != '~') && (getting_string != '!') && (getting_string != '('))

int blank_lines_ok(int c)
{
   if(c == ':') return 0;
   if(c == '/') return 0;
   if(c == '*') return 0;
   if(c == '~') return 0;
   if(c == '!') return 0;
   if(c == '(') return 0;
   if((c >= 'A') && (c <= 'Z')) return 0;
   if(c == 0x0100) return 0;

   return 1;
}

int start_edit(int c, char *prompt)
{
int i, col;
int row;

   //
   // Start building the text string for command parameter *c* 
   //
   // Note that blank lines are allowed as input and are processed only 
   // if *c* is an upper case character (A-Z), '*', ':', '~', '!', '(',  or '/'.
   // Search for BLANK_LINES_OK to find where to add more "blank ok" lines
   //
   insert_mode = 0;
   if(script_file) edit_buffer[0] = 0;
   edit_cursor = strlen(edit_buffer);   // user can prime the buffer with data
   getting_string = c;
   if(c < 0x0100) first_key = tolower(c);
   else           first_key = c;

   if(text_mode) erase_screen();
   else          erase_help();

   // display prompt string for the command
   vidstr(EDIT_ROW, EDIT_COL, PROMPT_COLOR, prompt);

   // special cases for multiple line prompts
   e_row = EDIT_ROW+2;
   row = EDIT_ROW+1;
   if(c == 'g') {  // display color palette selections
      col = EDIT_COL + strlen(prompt);
      for(i=1; i<16; i++) {
         sprintf(out, " %2d", i);
         vidstr(EDIT_ROW, col+((i-1)*3), i, out);
      }
   }

   if(edit_info1) {
      vidstr(row, EDIT_COL, PROMPT_COLOR, edit_info1);
      ++row;
      ++e_row;
      edit_info1 = 0;
   }
   if(edit_info2) {
      vidstr(row, EDIT_COL, PROMPT_COLOR, edit_info2);
      ++row;
      ++e_row;
      edit_info2 = 0;
   }
   if(edit_info3) {
      vidstr(row, EDIT_COL, PROMPT_COLOR, edit_info3);
      ++row;
      ++e_row;
      edit_info3 = 0;
   }

   first_edit = 1;
   edit_string(0);  // (0) param just prints >_
   return 0;
}

int edit_error(char *s)
{
int x;
char out[256+1];
int row,col,width;

   if(reading_lla && zoom_lla) {
      row = TEXT_ROWS-4;
      col = TEXT_COLS/2;
      width = TEXT_COLS/2;
   }
   else {
      row = EDIT_ROW+3;
      col = EDIT_COL;
      width = 80;
   }

   // show an error message and wait for a key press
   vidstr(row+0, col, PROMPT_COLOR, &blanks[TEXT_COLS-width]);
   vidstr(row+1, col, PROMPT_COLOR, &blanks[TEXT_COLS-width]);

   if(script_file) {
      sprintf(out, "Error in script file %s: line %d, col %d: %s", 
         script_name, script_line, script_col, s);
      vidstr(row+0, col, PROMPT_COLOR, out);
      vidstr(row+1, col, PROMPT_COLOR, "Press any key to stop script....");
   }
   else {
      vidstr(row+0, col, PROMPT_COLOR, s);
      vidstr(row+1, col, PROMPT_COLOR, "Press any key to continue....");
   }

   refresh_page();

   //!!! just waiting for a key here would be bad news because
   //    gps data would not be processed and the queue can overflow
   wait_for_key();

   vidstr(row+1, col, PROMPT_COLOR, "                                ");
   refresh_page();

   if(KBHIT()) x = GETCH();
   else        x = 0;
   script_fault = 1;
   return x;  
}

int build_string(int c)
{
u32 val;

int not_upper;

   // we are building a text string from the keystrokes / script input
   c = edit_string(c);     // attempt to add char to the string
   if(getting_string < 0x0100) not_upper = !isupper(getting_string);
   else                        not_upper = 1;

   if(c == ESC_CHAR) {     // edit abandoned
      goto abandon_edit;
   }
// else if((c == 0x0D) && (edit_buffer[0] == 0) && !isupper(getting_string) && BLANK_LINES_OK) {
// else if((c == 0x0D) && (edit_buffer[0] == 0) && not_upper && BLANK_LINES_OK) {
   else if((c == 0x0D) && (edit_buffer[0] == 0) && blank_lines_ok(getting_string)) {
      // CR with no text in edit buffer
      abandon_edit:
      getting_string = 0;
      script_pause = 0;
      if(text_mode) redraw_screen();
      else if((PLOT_WIDTH/TEXT_WIDTH) <= 80) erase_plot(1);
   }
   else if(c == 0x0D) { // edit done, parameter available,  do the command
      quick_cmd:
      script_pause = 0;
      val = string_param();  // evaluate and act upon the text string
      getting_string = 0;
      if(val == 2) new_queue(0x03);
      else if((val == 1)) redraw_screen();
      else if((PLOT_WIDTH/TEXT_WIDTH) <= 80) erase_plot(1);
   }
   else if(getting_string == 'a') {  // !!! kludge to make parsing command easier !!!
      goto quick_cmd;  
   }
   else if(getting_string == 'Q') {  // !!! kludge to make parsing command easier !!!
      goto quick_cmd;  
   }
   else if(getting_string == '~') {  // !!! kludge to make parsing command easier !!!
      goto quick_cmd;  
   }
   else return 0;  // character was added to the edit string

   return sure_exit();
}


void edit_scale()
{
float val;
char *u;

   // get a plot scale factor
   if(plot[selected_plot].user_scale) val = 0.0F;
   else                               val = plot[selected_plot].scale_factor;

   if(selected_plot == TEMP) {
      if     (DEG_SCALE == 'F')  u = "milli degrees F";
      else if(DEG_SCALE == 'R')  u = "milli degrees R";
      else if(DEG_SCALE == 'K')  u = "milli degrees K";
      else if(DEG_SCALE == 'D')  u = "milli degrees D";
      else if(DEG_SCALE == 'N')  u = "milli degrees N";
      else if(DEG_SCALE == 'E')  u = "milli degrees E";
      else if(DEG_SCALE == 'O')  u = "milli degrees O";
      else                       u = "milli degrees C";
   }
   else u = plot[selected_plot].units;
   if(u[0] == ' ') ++u;

   sprintf(edit_buffer, "%.0f", val);

   sprintf(out, "Enter scale factor for %s graph (%s/div, 0=auto scale)", 
                 plot[selected_plot].plot_id, u);
   start_edit('d', out);
}

void edit_drift()
{
char *u;

   // set a plot drift rate removal factor

   if(selected_plot == TEMP) {
      if     (DEG_SCALE == 'F')  u = "degrees F";
      else if(DEG_SCALE == 'R')  u = "degrees R";
      else if(DEG_SCALE == 'K')  u = "degrees K";
      else if(DEG_SCALE == 'D')  u = "degrees D";
      else if(DEG_SCALE == 'N')  u = "degrees N";
      else if(DEG_SCALE == 'E')  u = "degrees E";
      else if(DEG_SCALE == 'O')  u = "degrees O";
      else                       u = "degrees C";
   }
   else u = plot[selected_plot].units;
   if(u[0] == ' ') ++u;
u = "units";

   sprintf(edit_buffer, "%g", plot[selected_plot].a1);

   sprintf(out, "Enter drift rate to remove from %s graph (%s/sec)", 
                 plot[selected_plot].plot_id, u);
   start_edit('=', out);
}

void edit_ref()
{
float val;
char *u;

   // get a plot center line reference value
   edit_buffer[0] = 0;
   val = plot[selected_plot].plot_center;
   if(plot[selected_plot].float_center) {
      sprintf(edit_buffer, "%.6f", val);
   }

   if(selected_plot == TEMP) {
      if     (DEG_SCALE == 'F')  u = "degrees F";
      else if(DEG_SCALE == 'R')  u = "degrees R";
      else if(DEG_SCALE == 'K')  u = "degrees K";
      else if(DEG_SCALE == 'D')  u = "degrees D";
      else if(DEG_SCALE == 'N')  u = "degrees N";
      else if(DEG_SCALE == 'E')  u = "degrees E";
      else if(DEG_SCALE == 'O')  u = "degrees O";
      else                       u = "degrees C";
   }
   else if(selected_plot == DAC) u = "V";
   else u = plot[selected_plot].units;
   if(u[0] == ' ') ++u;

   sprintf(out, "Enter center line reference for %s graph (in %s, <cr>=auto)", 
                 plot[selected_plot].plot_id, u);
   start_edit('C', out);
}


void edit_cal()
{
float m, b;
char *s;

   // get a plot center line reference value
   s = plot[selected_plot].plot_id;
   edit_buffer[0] = 0;

   if     (selected_plot == TEMP)  { m=temp1_m; b=temp1_b; }
   else if(selected_plot == TC2)   { m=temp2_m; b=temp2_b; }
   else if(selected_plot == BATTI) { m=batti_m; b=batti_b; }
   else if(selected_plot == LEDI)  { m=ledi_m;  b=ledi_b; }
   else if(selected_plot == BATTV) { m=vcal_m;  b=vcal_b; s="VCAL"; }
   else if(selected_plot == LUX1)  { m=lux1_m;  b=lux1_b; }
   else if(selected_plot == LUX2)  { m=lux2_m;  b=lux2_b; }
   else if(selected_plot == AUXV)  { m=adc2_m;  b=adc2_b; }
   else if(selected_plot == CCT)   { m=rb_m;    b=rb_b; }
   else {
      sprintf(out, "%s does not have a calibration adjustment!", s);
      edit_error(out);
      return;
   }

   if(cal_mode) {
//    sprintf(edit_buffer, "%f  %f", m,b);
      edit_buffer[0] = 0;
      sprintf(out, "Enter reading1 actual1 reading2 actual2 for %s (m=%f b=%f)", s, m,b);
   }
   else {
      sprintf(edit_buffer, "%f  %f", m,b);
      sprintf(out, "Enter m and b cal factors for %s (m=%f b=%f)", s, m,b);
   }
   start_edit(CAL_CMD, out);
}

void edit_cal_param()
{
float m, b;
float r1,a1, r2,a2;
int i;

   if(cal_mode) {
      r1 = 1.0F;
      a1 = 0.0F;
      r2 = 1.0F;
      a2 = 0.0F;
      i = sscanf(edit_buffer, "%f %f %f %f", &r1,&a1, &r2,&a2);
      if(i < 1) {
         edit_error("ERROR: No calibration numbers were given!");
         return;
      }
      if(i < 3) {
         r2 = r1;
         a2 = a1;
      }

      if(r2 == r1) {
         if(r1 == 0.0F) {
            edit_error("ERROR: reading1 and reading2 cannot both be zero!");
            return;
         }
         else {
            m = a1 / r1;
            b = 0.0F;
         }
      }
      else {
         m = (a2-a1) / (r2-r1);
         b = a2 - m*r2;
      }

      if(m == 0.0F) {
         edit_error("ERROR: calculated 'm' value cannot be 0.0!");
         return;
      }
      else {
         sprintf(plot_title, "%s cal: m=%.6f  b=%.6f", plot[selected_plot].plot_id, m,b);
      }
   }
   else {
      m = 1.0F;
      b = 0.0F;
      i = sscanf(edit_buffer, "%f %f", &m,&b);
      if(i < 1) {
         edit_error("ERROR: No calibration numbers were given!");
         return;
      }
   }

   if     (selected_plot == TEMP)  { temp1_m=m; temp1_b=b; }
   else if(selected_plot == TC2)   { temp2_m=m; temp2_b=b; }
   else if(selected_plot == BATTI) { batti_m=m; batti_b=b; }
   else if(selected_plot == BATTV) { vcal_m=m;  vcal_b=b; }
   else if(selected_plot == LEDI)  { ledi_m=m;  ledi_b=b; }
   else if(selected_plot == LUX1)  { lux1_m=m;  lux1_b=b; }
   else if(selected_plot == LUX2)  { lux2_m=m;  lux2_b=b; }
   else if(selected_plot == AUXV)  { adc2_m=m;  adc2_b=b; }
   else if(selected_plot == CCT)   { rb_m=m;    rb_b=b; }
   else return;
   set_luxor_cal();
}


void view_all()
{
float val;

   val = (float) plot_q_count;
   view_interval = 0;
   while(val > 0) {
      val -= PLOT_WIDTH;
      ++view_interval;
   }
// view_interval = (long) (((val+PLOT_WIDTH-1) / PLOT_WIDTH) + 0.5F);
   if(view_interval <= 1L) view_interval = 1L;
   user_view = view_interval;
   new_user_view = 1;
   do_review(END_CHAR);
}


int edit_user_view(char *s)
{
float val;

   // process the new plot view time setting
   val = 0.0F;
   strcpy(out, s);
   strupr(out);
   if(strstr(out, "A")) {   // view ALL data
      view_all_data = 1;
   }
   else if(strstr(out, "T")) {   // view ALL data, auto scroll
      view_all_data = 2;
   }
   else {                   // view a subset of the data
      view_all_data = 0;
      val = (float) atof(out);
      if(val < 0.0F) {
         val = 0.0F - val;
      }
      else if(val == 0.0F) {
         user_view = 0L;
         view_interval = 1L;
         return 0;
      }
   }

   if(strstr(out, "W")) {
      view_interval = (long) ((((val * 24.0F*3600.0F*7.0F) / (float) queue_interval) / PLOT_WIDTH) + 0.5F);
   }
   else if(strstr(out, "D")) {
      view_interval = (long) ((((val * 24.0F*3600.0F) / (float) queue_interval) / PLOT_WIDTH) + 0.5F);
   }
   else if(strstr(out, "H")) {
      view_interval = (long) ((((val * 3600.0F) / (float) queue_interval) / PLOT_WIDTH) + 0.5F);
   }
   else if(strstr(out, "M")) {
      view_interval = (long) ((((val * 60.0F) / (float) queue_interval) / PLOT_WIDTH) + 0.5F);
   }
   else if(strstr(out, "S")) {
      view_interval = (long) (((val / (float) queue_interval) / PLOT_WIDTH) + 0.5F);
   }
   else if(strstr(out, "T")) {
      view_all();
      return 0;
   }
   else if(strstr(out, "A")) {
      view_all();
      return 0;
   }
   else {  // interval set in minutes per division
      val /= (float) queue_interval;
      val *= 60.0F;                   // seconds/division
      val /= (float) HORIZ_MAJOR;
      view_interval = (long) val;
   }

   if(view_interval <= 1L) view_interval = 1L;
   user_view = view_interval;
   new_user_view = 1;

   return 0;
}


void edit_dt(char *arg,  int err_ok)
{
int aa,bb,cc;
u08 s1,s2;
int dd,ee,ff;
u08 s3,s4;
long val;
u08 timer_set;

   // parse the alarm/exit date and time string
   if(arg[0] == 0) {  // no string given,  clear the timer values
      alarm_wait = 0;
      if(getting_string == ':') {      // alarm/egg timer
         alarm_time = alarm_date = 0;
         egg_timer = egg_val = 0;
         repeat_egg = 0;
      }
      else if(getting_string == '/') { // exit time/timer
         end_time = end_date = 0;
         exit_timer = exit_val = 0;
      }
      else if(getting_string == '!') { // screen dump timer
         dump_time = dump_date = 0;
         dump_timer = dump_val = 0;
         repeat_dump = 0;
      }
      else if(getting_string == '(') { // log dump timer
         log_time = log_date = 0;
         log_timer = log_val = 0;
         repeat_log = 0;
      }
      return;
   }

   strupr(arg);
   if(getting_string == '!') {
      if(strstr(arg, "O")) single_dump = 1;  // dump the screen to one file
      else                 single_dump = 0;  // dump the screen multiple files
   }
   else if(getting_string == '(') {
      if(strstr(arg, "O")) single_log = 1;  // dump the log to one file
      else                 single_log = 0;  // dump the log multiple files
   }
   else {
      if(strstr(arg, "O")) single_alarm = 1;  // sound the alarm tone once
      else                 single_alarm = 0;  // sound the alarm until a key press
   }

   // see if a countdown timer has been set
   timer_set = 0;
   val = (long) atof(arg);
   if(strstr(arg, "S")) {      // timer is in seconds
      timer_set = 1;
   }
   else if(strstr(arg, "M")) { // timer is in minutes 
      val *= 60L;
      timer_set = 1;
   }
   else if(strstr(arg, "H")) { // timer is in hours 
      val *= 3600L;
      timer_set = 1;
   }
   else if(strstr(arg, "D")) { // timer is in days 
      val *= 3600L*24L;
      timer_set = 1;
   }

   if(strstr(arg, "W")) { // wait for alarm to trigger in script file
      alarm_wait = 1;
   }
   else {
      alarm_wait = 0;
   }

   if(timer_set) {  // a countdown timer has been set
      if(getting_string == ':') { // it is the egg timer
         egg_val = egg_timer = val;
         if(strstr(arg, "R")) repeat_egg = 1;
         else                 repeat_egg = 0;
      }
      else if(getting_string == '/') {  // it is the exit timer
         exit_val = exit_timer = val;
      }
      else if(getting_string == '!') {  // it is the screen dump timer
         dump_val = dump_timer = val;
         if(strstr(arg, "R")) repeat_dump = 1;
         else                 repeat_dump = 0;
      }
      else if(getting_string == '(') {  // it is the log dump timer
         log_val = log_timer = val;
         if(strstr(arg, "R")) repeat_log = 1;
         else                 repeat_log = 0;
      }
      return;
   }

   // setting a time or date value
   aa = bb = cc = dd = ee = ff = 0;
   s1 = s2 = s3 = s4 = 0;
   if(err_ok) {  // processing keyboard time string
      if(getting_string == '!') {
         dump_time = dump_date = 0;
         dump_hh = dump_mm = dump_ss = 0;
         dump_month = dump_day = dump_year = 0;
      }
      else if(getting_string == '(') {
         log_time = log_date = 0;
         log_hh = log_mm = log_ss = 0;
         log_month = log_day = log_year = 0;
      }
      else {
         alarm_time = alarm_date = 0;
         alarm_hh = alarm_mm = alarm_ss = 0;
         alarm_month = alarm_day = alarm_year = 0;

         end_time = end_date = 0;
         end_hh = end_mm = end_ss = 0;
         end_month = end_day = end_year = 0;
      }
   }
   sscanf(arg, "%d%c%d%c%d %d%c%d%c%d", &aa,&s1,&bb,&s2,&cc, &dd,&s3,&ee,&s4,&ff);

   if(s1 == ':') { // first field is a time
      if(s2 && (s2 != s1)) {
        if(err_ok) edit_error("Invalid time separator character");
      }
      else if(s3 && (s3 != '/')) {
        if(err_ok) edit_error("Invalid date separator character");
      }
      else if(getting_string == ':') {  // alarm time
         alarm_time = 1;
         alarm_hh = aa;
         alarm_mm = bb;
         alarm_ss = cc;
         if(s3 == '/') {  // second field is a date
            alarm_date = 1;
            alarm_month = dd;
            alarm_day = ee;
            if(ff < 100) ff += 2000;
            alarm_year = ff;
         }
      }
      else if(getting_string == '!') {  // screen dump time
         dump_time = 1;
         dump_hh = aa;
         dump_mm = bb;
         dump_ss = cc;
         if(s3 == '/') {  // second field is a date
            dump_date = 1;
            dump_month = dd;
            dump_day = ee;
            if(ff < 100) ff += 2000;
            dump_year = ff;
         }
      }
      else if(getting_string == '(') {  // log dump time
         log_time = 1;
         log_hh = aa;
         log_mm = bb;
         log_ss = cc;
         if(s3 == '/') {  // second field is a date
            log_date = 1;
            log_month = dd;
            log_day = ee;
            if(ff < 100) ff += 2000;
            log_year = ff;
         }
      }
      else { // exit time
         end_time = 1;
         end_hh = aa;
         end_mm = bb;
         end_ss = cc;
         if(s3 == '/') {  // second field is a date
            end_date = 1;
            end_month = dd;
            end_day = ee;
            if(ff < 100) ff += 2000;
            end_year = ff;
         }
      }
   }
   else if(s1 == '/') {  // first field is a date
      if(s2 && (s2 != s1))       edit_error("Invalid date separator character");
      else if(s3 && (s3 != ':')) edit_error("Invalid time separator character");
      else if(getting_string == ':') {  // alarm date
         alarm_date = 1;
         alarm_month = aa;
         alarm_day = bb;
         if(cc < 100) cc += 2000;
         alarm_year = cc;
         if(s3 == ':') {  // second field is a time
            alarm_time = 1;
            alarm_hh = dd;
            alarm_mm = ee;
            alarm_ss = ff;
         }
      }
      else if(getting_string == '!') {  // screen dump date
         dump_date = 1;
         dump_month = aa;
         dump_day = bb;
         if(cc < 100) cc += 2000;
         dump_year = cc;
         if(s3 == ':') {  // second field is a time
            dump_time = 1;
            dump_hh = dd;
            dump_mm = ee;
            dump_ss = ff;
         }
      }
      else if(getting_string == '(') {  // log dump date
         log_date = 1;
         log_month = aa;
         log_day = bb;
         if(cc < 100) cc += 2000;
         log_year = cc;
         if(s3 == ':') {  // second field is a time
            log_time = 1;
            log_hh = dd;
            log_mm = ee;
            log_ss = ff;
         }
      }
      else { // exit date
         end_date = 1;
         end_month = aa;
         end_day = bb;
         if(cc < 100) cc += 2000;
         end_year = cc;
         if(s3 == ':') {  // second field is a time
            end_time = 1;
            end_hh = dd;
            end_mm = ee;
            end_ss = ff;
         }
      }
   }
   else {
      if(err_ok) edit_error("No time or date specifier character seen");
   }
}

void edit_lla_cmd()
{
   // set lat/lon/altitude
   if(edit_buffer[0] == 0) return;

   precise_lat = precise_lon = precise_alt = 1.0E6;
   sscanf(edit_buffer, "%lf %lf %lf", &precise_lat, &precise_lon, &precise_alt);
   if((precise_lat < -90.0) || (precise_lat > 90.0))          edit_error("Bad latitude value");
   else if((precise_lon < -180.0) || (precise_lon > 180.0))   edit_error("Bad longitude value");
   else if((precise_alt< -1000.0) || (precise_alt > 10000.0)) edit_error("Bad altitude value");
   else { // save current position with high accuracy
      precise_lat /= RAD_TO_DEG;
      precise_lon /= RAD_TO_DEG;
      if(luxor) {
         set_lla((float)precise_lat, (float)precise_lon, (float)precise_alt);
      }
      else {
         #ifdef PRECISE_STUFF
            stop_precision_survey();   // stop any precision survey
            stop_self_survey();        // stop any self survey
            save_precise_posn(0);      // do single point surveys until we get close enough
         #else
            set_lla((float)precise_lat, (float)precise_lon, (float)precise_alt);
         #endif
      }
   }
}

void edit_option_switch()
{
int cmd_err;

   // process what is normally a command line option from the keyboard
   not_safe = 0;
   keyboard_cmd = 1;
   cmd_err = option_switch(edit_buffer);

   if(cmd_err) {
      sprintf(out, "Unknown command line option %c.  Type ? for command line help.", cmd_err);
      edit_error(out);
   }
   else if(not_safe == 1) {
      config_options();
   }
   else if(not_safe == 2) {
      sprintf(out, "Option cannot be set from keyboard: %s", edit_buffer);
      edit_error(out);
   }

   redraw_screen();
}

void set_osc_units()
{
   if(show_euro_ppt) {
      ppb_string = "e-9 "; 
      ppt_string = "e-12";
   }
   else {
      ppb_string = " ppb"; 
      ppt_string = " ppt";
   }
   plot[OSC].units = ppt_string;
}


void edit_option_value()
{
float val;
u08 c;

   // set a debug/test value
   val = (float) atof(&edit_buffer[1]);
   c = tolower(edit_buffer[0]);
   if(c == 'a') { 
      amu_flag ^= 0x08;
      set_io_options(0x13, 0x03, 0x01, amu_flag);  // ECEF+LLA+DBL PRECISION, ECEF+ENU vel,  UTC, no PACKET 5A, amu
//    clear_signals();
   }
#ifdef ADEV_STUFF
   else if(c == 'b') {  // adev bin scale
      bin_scale = (int) val;
      if(bin_scale <= 0) bin_scale = 5;
      reload_adev_info();
      force_adev_redraw();
   }
#endif
   else if(c == 'c') {  // sat count size
      if(edit_buffer[1]) small_sat_count = (int) val & 0x01;
      else               small_sat_count ^= 1;
      config_screen();
   }
#ifdef FFT_STUFF
   else if(c == 'd') {  // do FFT in dB
      if(edit_buffer[1]) fft_db = (int) val & 0x01;
      else               fft_db ^= 1;
      if(fft_db) plot[FFT].units = "dB";
      else       plot[FFT].units = "x ";
      set_fft_scale();
   }
#endif
   else if(c == 'e') {  // force Thunderbolt-E flag
      if(edit_buffer[1]) ebolt = (int) val & 0x01;
      else               ebolt ^= 1;
      max_sats = 8;     // used to format the sat_info data
      temp_sats = 8;
      eofs = 1;
      if(ebolt) {
         last_ebolt = 2;
         saw_ebolt();
      }
      config_screen();
   }
#ifdef ADEV_STUFF
   else if(c == 'f') {  // keep adevs fresh (by periodically forcing a recalc)
      if(edit_buffer[1]) keep_adevs_fresh = (int) val & 0x01;
      else               keep_adevs_fresh = 1;
   }
#endif
   else if(c == 'g') {  // plot grid background color
      if(edit_buffer[1]) plot_background = (int) val & 0x01;
      else               plot_background ^= 1;
   }
   else if(c == 'h') {  // erase lla plot every hour
      if(edit_buffer[1]) erase_every_hour = (int) val & 0x01;
      else               erase_every_hour ^= 1;
   }
   else if(c == 'i') {  // signal level displays
      zoom_screen = 0;
      if(edit_buffer[1])    plot_signals = (int) val;
      else if(plot_signals) plot_signals = 0;
      else                  plot_signals = 4;
      if     (strchr(edit_buffer, 'z')) zoom_screen = 0;
      else if(strchr(edit_buffer, 'Z')) zoom_screen = 0;
      else zoom_screen = 1;
      if(plot_watch || plot_azel) zoom_screen = 0;
      update_azel = 1;
      config_screen();
   }
   else if(c == 'j') {  // just read and log serial data
      if(edit_buffer[1]) log_stream = (int) val & 0x01;
      else               log_stream ^= 1;
//    if(edit_buffer[1]) just_read = (int) val & 0x01;
//    else               just_read ^= 1;
//    log_stream = just_read;
   }
   else if(c == 'k') {  // flag message faults as time skips
      if(edit_buffer[1]) flag_faults = (int) val & 0x01;
      else               flag_faults ^= 1;
   }
#ifdef FFT_STUFF
   else if(c == 'l') {  // live fft
      if(edit_buffer[1]) show_live_fft = (int) val & 0x01;
      else               show_live_fft ^= 1;
      live_fft = selected_plot;
      if(show_live_fft && (plot[FFT].show_plot == 0)) toggle_plot(FFT);
   }
#endif
   else if(c == 'm') {  // plot magnification factor (for less than one sec/pixel)
      plot_mag = (int) val;
      if(plot_mag <= 1) plot_mag = 1;
   }
   else if(c == 'p') {  // peak scale - dont let plot scale factors get smaller
      if(edit_buffer[1]) peak_scale = (int) val & 0x01;
      else               peak_scale ^= 1;
   }
   else if(c == 'q') {  // skip over subsmapled queue entries using the slow, direct method
      if(edit_buffer[1]) slow_q_skips = (int) val & 0x01;
      else               slow_q_skips ^= 1;
   }
#ifdef ADEV_STUFF
   else if(c == 'r') {  // reset adev bins and recalc adevs
      reload_adev_info();
   }
#endif
   else if(c == 's') {  // temperature spike filter 0=off  1=for temp pid  2=for pid and plot
      if(edit_buffer[1])  spike_mode = (int) val;
      else if(spike_mode) spike_mode = 0;
      else                spike_mode = 1;
   }
   else if(c == 't') {  // 12 or 24 hour big time time
      if(edit_buffer[1]) clock_12 = (int) val & 0x01;
      else               clock_12 ^= 1;
   }
   else if(c == 'u') {  // daylight savings time area
      if(edit_buffer[1]) dst_area = (int) val;
      else               dst_area = 0;
      calc_dst_times(dst_list[dst_area]);
   }
   else if(c == 'v') {  // ADEV base value mode 
      // (kludge used to increase dynamic range of single precision numbers)
      subtract_base_value = (u08) val;
      reset_queues(3);
   }
   else if(c == 'w') {  // watch face style
      watch_face = (u08) val;
      if(watch_face > 5) watch_face = 0;
   }
   else if(c == 'x') {
      if(edit_buffer[1]) set_rcvr_config((int) val);
      else               set_rcvr_config(7);
   }
   else if(c == 'y') {  // temp-dac dac scale factor
      if(edit_buffer[1]) d_scale = val;
      else if(plot[DAC].sum_yy && stat_count) {
         d_scale = sqrt(plot[TEMP].sum_yy/stat_count) / sqrt(plot[DAC].sum_yy/stat_count);
      }
      else d_scale = 0.0;
if(title_type != USER) {
   sprintf(plot_title, "DAC_scale=%f", d_scale);
   title_type = OTHER;
}
      redraw_screen();
   }
   else if(c == 'z') {  // auto centering
      if(edit_buffer[1]) auto_center = (int) val & 0x01;
      else               auto_center ^= 1;
   }
   else if((c == '/') || (c == '-') || (c == '$') || (c == '=') || isdigit(c)) {
      edit_option_switch();
   }
   else {
      // bugs_black_blood:
      sprintf(out, "Unknown debug parameter: %c", c);
      edit_error(out);
   }

   redraw_screen();
}


void dump_cal_file()
{
FILE *file;

   if(edit_buffer[0] == 0) {
      file = fopen("luxcal.scr", "w");  //zork
      if(file == 0) {
         sprintf(out, "ERROR: could not write file: luxcal.scr");
         edit_error(out);
         return;
      }
   }
   else {
//    strupr(edit_buffer);
      if(strstr(edit_buffer, ".") == 0) strcat(edit_buffer, ".scr");
      file = fopen(edit_buffer, "w");   // zork
      if(file == 0) {
         sprintf(out, "ERROR: could not write file: %s", edit_buffer);
         edit_error(out);
         return;
      }
   }

   fprintf(file, "&c0                     ;exit calibration mode\n");
   fprintf(file, "&s  %.4f   SERIAL     ;serial number\n", vref_b);
   fprintf(file, "&v  %.6f VREF       ;ADC reference voltage\n", vref_m);
   fprintf(file, "gd& %.6f %.6f   ;battery/led voltage calibration\n", vcal_m, vcal_b);
   fprintf(file, "go& %.6f %.6f   ;battery current calibration\n", batti_m, batti_b);
   fprintf(file, "g3& %.6f %.6f   ;led current calibration\n", ledi_m, ledi_b);
   fprintf(file, "gt& %.6f %.6f   ;temp sensor 1 calibration\n", temp1_m, temp1_b);
   fprintf(file, "g5& %.6f %.6f   ;temp sensor 2 calibration\n", temp2_m, temp2_b);
   fprintf(file, "gp& %.6f %.6f   ;lux sensor calibration\n", lux1_m, lux1_b);
   fprintf(file, "g1& %.6f %.6f   ;lumen sensor calibration\n", lux2_m, lux2_b);
   fprintf(file, "gl& %.6f %.6f   ;r/b color temperature calibration\n", rb_m, rb_b);
   fprintf(file, "g0& %.6f %.6f   ;aux ADC channel calibration\n", adc2_m, adc2_b);

   fclose(file);
}

int edit_write_cmd()
{
   // process a file write/delete command
   if(edit_buffer[0]) {
      if(dump_type == 's') {
         first_key = 0;
         prot_menu = 0;
         draw_plot(1);
         if(dump_screen(invert_video, top_line, edit_buffer) == 0) {
            first_key = ' ';
            edit_error("Could not write screen image file");
         }
      }
      else if(dump_type == 'd') {   //delete file
         if(unlink(edit_buffer)) {
            sprintf(out, "Could not delete file: %s", edit_buffer);
         }
         else {
            sprintf(out, "File %s deleted", edit_buffer);
         }
         edit_error(out);
      }
      else if(dump_type == 'c') {  // luxor cal .SCR file
         dump_cal_file();
      }
      else {
         dump_log(edit_buffer, dump_type);
      }
   }
   else {
      edit_error("Bad file name");
   }

   top_line = 0;
   return 0;
}

void edit_osc_param()
{
float val;

   // change an oscillator control parameter
   if(edit_buffer[0] == 0) return;
   val = (float) atof(edit_buffer);

   if(getting_string == '1') {  // time constant
      user_time_constant = val;
   }
   else if(getting_string == '2') {  // damping factor
      user_damping_factor = val;
   }
   else if(getting_string == '3') {  // osc gain
      user_osc_gain = val;
      if(process_com == 0) osc_gain = val;
if(luxor) set_luxor_sens((u08) val, (u08) val);
   }
   else if(getting_string == '4') {  // min volts / battery pwm level
      user_min_volts = val;
if(luxor) set_batt_pwm((u16) (val*65535.0F));
   }
   else if(getting_string == '5') {  // max volts / luxor driver mode change
      user_max_volts = val;
   }
   else if(getting_string == '6') {  // jam sync theshold
      user_jam_sync = val;
   }
   else if(getting_string == '7') {  // max freq offset
      user_max_freq_offset = val;
   }
   else if(getting_string == '8') {  // initial dac voltage
      user_initial_voltage = val;
      if(saw_ntpx) initial_voltage = val;
   }
   else if(getting_string == 't') {  // min EFC range volts
      user_min_range = val;
   }
   else if(getting_string == 'T') {  // max EFC range volts
      user_max_range = val;
   }
   else return;   // unknown osc param

   set_discipline_params(1);
   request_all_dis_params();
}


void edit_cable_delay()
{
float val;

   if(edit_buffer[0] == 0) return;

   val = (float) atof(edit_buffer);
   strupr(edit_buffer);
   if(strstr(edit_buffer, "F") || strstr(edit_buffer, "'")) {  // cable delay in feet
      val = val * (1.0F / (186254.0F * 5280.0F)) / 0.66F;  // 0.66 vp coax
   }
   else if(strstr(edit_buffer, "M")) { // cable delay in meters
      val *= 3.28084F;
      val = val * (1.0F / (186254.0F * 5280.0F)) / 0.66F;  // 0.66 vp coax
   }
   else {
      val /= 1.0E9;
   }

   delay_value = val;
   set_pps(user_pps_enable, pps_polarity,  delay_value,  300.0, 1);
   request_pps();
}


#ifdef TEMP_CONTROL

void clear_pid_display()
{
   if(pid_debug == 0) {
      debug_text[0] = 0;
      debug_text2[0] = 0;
      redraw_screen();
   }
}

u08 edit_pid_value(char *s, int kbd_cmd)
{
u08 c;

   strupr(s);
   if((s[0] == 'A') || (s[0] == 'B')) {    // KA command - bang-bang autotune
      // kb0 = abort autotune
      // kb1 = do full tuneup with all settling delays
      // kb2 = don't wait for temp to get near setpoint
      // kb3 = don't wait for pid to stabilize
      if(bang_bang == 0) OLD_P_GAIN = P_GAIN;
      bang_bang = 1;
      sscanf(&s[1], "%d", &bang_bang);
      if(kbd_cmd) enable_temp_control();
      do_temp_control = 1;

      if(bang_bang > 4) bang_bang = 1;
      else if(bang_bang == 0) {       // abort autotune
         P_GAIN = OLD_P_GAIN;
         calc_k_factors();
         if(kbd_cmd) clear_pid_display();
         if(kbd_cmd) show_pid_values();
      }
   }
   else if(s[0] == 'D') {  // KD command - derivitive time constant
      sscanf(&s[1], "%f", &D_TC);
      calc_k_factors();
   }
   else if(s[0] == 'F') {  // KF command - filter time constant
      sscanf(&s[1], "%f", &FILTER_TC);
      calc_k_factors();
   }
   else if(s[0] == 'H') {  // KH command - PID debug (help) display
      pid_debug = toggle_value(pid_debug);
      if(pid_debug) osc_pid_debug = 0;
      if(kbd_cmd) clear_pid_display();
   }
   else if(s[0] == 'I') {  // KI command - integral time constant
      sscanf(&s[1], "%f", &I_TC);
      calc_k_factors();
   }
   else if(s[0] == 'K') {  // KK command - all major PID values
      if(kbd_cmd) enable_temp_control();
      do_temp_control = 1;
      FILTER_OFFSET = 0.0F;
      sscanf(&s[1], "%f%c%f%c%f%c%f", &P_GAIN,&c, &D_TC,&c,  &FILTER_TC,&c, &I_TC);
      calc_k_factors();
   }
   else if(s[0] == 'L') {  // KL command - load distubance
      sscanf(&s[1], "%f", &k6);
      calc_k_factors();
   }
   else if(s[0] == 'M') {  // KM command - mark's values
      if(kbd_cmd) enable_temp_control();
      do_temp_control = 1;
      set_default_pid(1);
      if(kbd_cmd) show_pid_values();
   }
   else if(s[0] == 'O') {  // KO command - filter offset
      sscanf(&s[1], "%f", &FILTER_OFFSET);
      calc_k_factors();
   }
   else if(s[0] == 'P') {  // KP command - pid gain
      sscanf(&s[1], "%f", &P_GAIN);
      calc_k_factors();
   }
   else if(s[0] == 'R') {  // KR command - integrator reset
      sscanf(&s[1], "%f", &k8);
      calc_k_factors();
   }
   else if(s[0] == 'S') {  // KS command - scale factor (loop gain correction)
      sscanf(&s[1], "%f", &k7);
      calc_k_factors();
   }
   else if(s[0] == 'T') {  // KT command - pwm test
      sscanf(&s[1], "%f%c%f", &test_cool, &c, &test_heat);
      if(test_heat || test_cool) {
         if(kbd_cmd) enable_temp_control();
         do_temp_control = 1;
      }
      if(++test_marker > 9) test_marker = 1;
      mark_q_entry[test_marker] = plot_q_in;
   }
   else if(s[0] == 'W') {  // KW command - Warren's slow values
      if(kbd_cmd) enable_temp_control();
      do_temp_control = 1;
      set_default_pid(0);
      if(kbd_cmd) show_pid_values();
   }
   else if(s[0] == 'Z') {  // KZ command - reset PID
      integrator = 0.0F;
      if(kbd_cmd) enable_temp_control(); 
      do_temp_control = 1;
   }
   else if(s[0] == '9') {  // K9 command - autotune step size
      sscanf(&s[1], "%f", &KL_TUNE_STEP);
      calc_k_factors();
   }
   else if(s[0] == '0') {  // K0 command - make temperature crude
      crude_temp = toggle_value(crude_temp);
   }
   else return 1;

   return 0;
}

#endif // TEMP_CONTROL


#ifdef OSC_CONTROL

void clear_osc_pid_display()
{
   if(osc_pid_debug == 0) {
      debug_text[0] = 0;
      debug_text2[0] = 0;
      redraw_screen();
   }
}

u08 edit_osc_pid_value(char *s, int kbd_cmd)
{
u08 c;

   strupr(s);
   if((s[0] == 'A') || (s[0] == 'B')) {    // BA command - bang-bang autotune
   }
   else if(s[0] == 'C') {
      sscanf(&s[1], "%lf", &trick_scale);
      if(trick_scale == 0.0) {
         set_pps(user_pps_enable, pps_polarity,  delay_value,  300.0, 0);
      }
      else {
         first_trick = 1;
         trick_value = 0.0;
      }
   }
   else if(s[0] == 'D') {  // BD command - derivitive time constant
      sscanf(&s[1], "%lf", &OSC_D_TC);
      calc_osc_k_factors();
   }
   else if(s[0] == 'F') {  // BF command - filter time constant
      sscanf(&s[1], "%lf", &OSC_FILTER_TC);
      calc_osc_k_factors();
   }
   else if(s[0] == 'H') {  // BH command - PID debug (help) display
      osc_pid_debug = toggle_value(osc_pid_debug);
      if(osc_pid_debug) pid_debug = 0;
      if(kbd_cmd) clear_osc_pid_display();
   }
   else if(s[0] == 'I') {  // BI command - integral time constant
      sscanf(&s[1], "%lf", &OSC_I_TC);
      calc_osc_k_factors();
   }
   else if(s[0] == 'J') {  // BJ command - John's values
      set_default_osc_pid(2);
      if(kbd_cmd) enable_osc_control();
      if(kbd_cmd) show_osc_pid_values();
   }
   else if(s[0] == 'K') {  // BK command - all major PID values
      OSC_FILTER_OFFSET = 0.0F;
      sscanf(&s[1], "%lf%c%lf%c%lf%c%lf", &OSC_P_GAIN,&c, &OSC_D_TC,&c,  &OSC_FILTER_TC,&c, &OSC_I_TC);
      calc_osc_k_factors();
      if(kbd_cmd) enable_osc_control();
      if(kbd_cmd) show_osc_pid_values();
   }
   else if(s[0] == 'L') {  // BL command - load distubance
      sscanf(&s[1], "%lf", &osc_k6);
      calc_osc_k_factors();
   }
   else if(s[0] == 'M') {  // BM command - mark's values
      set_default_osc_pid(1);
      if(kbd_cmd) enable_osc_control();
      if(kbd_cmd) show_osc_pid_values();
   }
   else if(s[0] == 'O') {  // BO command - filter offset
      sscanf(&s[1], "%lf", &OSC_FILTER_OFFSET);
      calc_osc_k_factors();
   }
   else if(s[0] == 'P') {  // BP command - pid gain
      sscanf(&s[1], "%lf", &OSC_P_GAIN);
      calc_osc_k_factors();
   }
   else if(s[0] == 'R') {  // BR command - integrator reset
      sscanf(&s[1], "%lf", &osc_k8);
      calc_osc_k_factors();
   }
   else if(s[0] == 'S') {  // BS command - scale factor (loop gain correction)
      sscanf(&s[1], "%lf", &osc_k7);
      calc_osc_k_factors();
   }
   else if(s[0] == 'W') {  // BW command - Warren's slow values
      set_default_osc_pid(0);
      if(kbd_cmd) enable_osc_control();
      if(kbd_cmd) show_osc_pid_values();
   }
   else if(s[0] == 'Z') {  // BZ command - reset PID
      reset_osc_pid(kbd_cmd);
   }
   else if(s[0] == '0') {  // B0 command - turn off pid
      disable_osc_control();
   }
   else if(s[0] == '1') {  // B1 command - turn pid on
      enable_osc_control();
   }
   else if(s[0] == '9') {  // B9 command - prefilter depth
//    sscanf(&s[1], "%lf", &OSC_KL_TUNE_STEP);
//    sscanf(&s[1], "%d", &osc_prefilter);
//    if(osc_prefilter > PRE_Q_SIZE) osc_prefilter = PRE_Q_SIZE;
//    opq_in = opq_count = 0;
      sscanf(&s[1], "%d", &osc_postfilter);
      if(osc_postfilter > POST_Q_SIZE) osc_postfilter = POST_Q_SIZE;
      new_postfilter();
      calc_osc_k_factors();
   }
   else return 1;

   return 0;
}

#endif // OSC_CONTROL


int adjust_screen_options()
{
int stm;
int old_azel;

   stm = 0;   // set text mode
   old_azel = plot_azel;

// plot_signals = 0;
   if(screen_type == 't') {  // text mode
      plot_azel = 0;
      stm = 2;
   }
   else if(screen_type == 'z') ; // plot_azel = AZEL_OK;
   else if(screen_type == 'h') ; // plot_azel = AZEL_OK;
   else if(screen_type == 'x') ; // plot_azel = AZEL_OK;
   else if(screen_type == 'v') ; // plot_azel = AZEL_OK;
   else if(screen_type == 'l') ; // plot_azel = AZEL_OK;
   else if(screen_type == 'm') ; // plot_azel = 0;
   else if(screen_type == 'n') ; // plot_azel = 0;          // netbook
   else if(screen_type == 's') ; // plot_azel = 0;
   else if(screen_type == 'u') ; // plot_azel = 0;
   else if(screen_type == 'c') ; // plot_azel = 0;   //!!! custom screen
   else {
      screen_type = 'm';
      text_mode = stm;
      return 1;
   }
   if(plot_azel || plot_signals) update_azel = 1;
   text_mode = stm;

   if(plot_watch) {
      plot_azel = old_azel;
      plot_digital_clock = 0;
      if(plot_azel || plot_signals) update_azel = 1;
   }
   else if(user_set_clock_plot == 0) plot_digital_clock = plot_azel;
// shared_plot = 0;

   if(screen_type == 'm') {
      if((TEXT_HEIGHT <= 12) && (user_set_clock_plot == 0)) plot_digital_clock = 1;
   }

   if(ebolt) {  // adjust ebolt sat count for time clock display
      last_ebolt = 2;
      saw_ebolt();
   }
   return 0;
}

void change_screen_res()
{
int k;

   first_key = 0;
   prot_menu = 0;
   eofs = 1;

   adjust_screen_options();
   init_screen();

   // set where the first point in the graphs will be
   last_count_y = PLOT_ROW + (PLOT_HEIGHT - VERT_MINOR);
   for(k=0; k<NUM_PLOTS+DERIVED_PLOTS; k++) {
      plot[k].last_y = PLOT_ROW+PLOT_CENTER;
   }

   redraw_screen();
}

#ifdef WINDOWS
void go_windowed()
{
   initial_window_mode = VFX_WINDOW_MODE;
   change_screen_res();
   downsized = 1;
}

void go_fullscreen()
{
   initial_window_mode = VFX_TRY_FULLSCREEN;
   change_screen_res();
   downsized = 0;
}
#endif

void edit_screen_res()
{
int font_set;

   // change the screen size
   strupr(edit_buffer);
   if(strstr(edit_buffer, "N")) return;

   user_video_mode = (int) atof(edit_buffer);
   font_set = 0;
   if     (strstr(edit_buffer, ":")) font_set = 12;
   else if(strstr(edit_buffer, "S")) font_set = 12;
   else if(strstr(edit_buffer, "M")) font_set = 14;
   else if(strstr(edit_buffer, "L")) font_set = 16;
   else if(strstr(edit_buffer, "T")) font_set = 8;
   else                              font_set = 0;

   #ifdef WINDOWS
      if(font_set == 0) {
         if((strstr(edit_buffer, "Y") == 0) && (strstr(edit_buffer, "F") == 0)) return;
      }
      if(strstr(edit_buffer, "F")) initial_window_mode = VFX_TRY_FULLSCREEN;
      else                         initial_window_mode = VFX_WINDOW_MODE;
   #endif

   if((user_font_size == 0) && (SCREEN_HEIGHT < 600)) font_set = 12;
   user_font_size = font_set;

   change_screen_res();
}

void new_screen(u08 c)
{
char *s;

   // setup for a new screen size
   screen_type = c;   // $ command
   if(c == 'u') {
      strcpy(edit_buffer, "18");
      s="640x480";
   }
   else if (c == 's') {
      strcpy(edit_buffer, "258");
      s="800x600";
   }
   else if(c == 'm') {
      strcpy(edit_buffer, "260");
      s="1024x768";
   }
   else if(c == 'l') {
      strcpy(edit_buffer, "262");
      s="1280x1024";
   }
   else if(c == 'v') {
      strcpy(edit_buffer, "327");
      s="1400x1050";
   }
   else if(c == 'x') {
      strcpy(edit_buffer, "304");  // or mode 325
      s="1680x1050";
   }
   else if(c == 'h') {
      strcpy(edit_buffer, "319");
      s="1920x1080";
   }
   else if(c == 'z') {
      strcpy(edit_buffer, "338");
      s="2048x1530";
   }
   else if(c == 't') {
      s="640x480 text only";
      strcpy(edit_buffer, "2");
   }
   else if(c == 'n') {
      s="1000x540";
      strcpy(edit_buffer, "2");
   }
   else if(c == 'c') {
      s="custom screen size";
      strcpy(edit_buffer, "2");
   }
   else              {
      screen_type = 'm';
      strcpy(edit_buffer, "260");
      s="1024x768";
   }

   #ifdef DOS
      sprintf(out, "Enter VESA video mode for %s screen: (ESC ESC to abort):", s);
      no_auto_erase = 1;
   #else
      strcpy(edit_buffer, "Y");
      sprintf(out, "%s screen: Y)es  N)o  F)ull - T)iny  S)mall  M)edium  L)arge font:", s);
   #endif
   start_edit('$', out);
}



void update_check()
{
// if(strchr(edit_buffer, 'u') || strchr(edit_buffer, 'U')) {
   if(!strchr(edit_buffer, 'u') && !strchr(edit_buffer, 'U')) {
      pause_data = 0;    // release data pause
      new_queue(3);      // erase the data queue
      update_stop = 1;   // stop updating data at end of run
   }
}

void write_luxor_config()
{
FILE *file;

   if(!strchr(edit_buffer, '.')) strcat(edit_buffer, ".scr");

   file = fopen(edit_buffer, "w");  //zork
   if(file == 0) {
      sprintf(out, "ERROR: could not write file: %s", edit_buffer);
      edit_error(out);
      return;
   }

   fprintf(file, "PL %f  ;BATT low voltage\n", batt_lvc);
   fprintf(file, "PH %f  ;BATT high voltage\n", batt_hvc);
   fprintf(file, "PC %f  ;BATT overcurrent\n", batt_ovc);
   fprintf(file, "PW %f  ;BATT over-wattage\n", batt_watts);
   fprintf(file, "PU %f  ;LED low voltage\n", load_lvc);
   fprintf(file, "PV %f  ;LED high voltage\n", load_hvc);
   fprintf(file, "PO %f  ;LED overcurrent\n", load_ovc);
   fprintf(file, "PP %f  ;LED over-wattage\n", load_watts);
   fprintf(file, "PZ %f  ;AUX low voltage\n", auxv_lvc);
   fprintf(file, "PX %f  ;AUX high voltage\n", auxv_hvc);
   fprintf(file, "PT %f  ;TEMP1 overtemp\n", tc1_ovt);
   fprintf(file, "PS %f  ;TEMP2 overtemp\n", tc2_ovt);
   fprintf(file, "PM %f  ;Msg timeout\n", msg_timeout);
   fprintf(file, "&E %f  ;IR1 temp sensor emissivity\n", emis1);
   fprintf(file, "&I %f  ;IR2 temp sensor emissivity\n", emis2);
   fprintf(file, "BP %-2d   ;BATT pwm resolution\n", batt_pwm_res);
   fprintf(file, "BR %-2d   ;BATT pwm sweep rate\n", sweep_rate);
   fprintf(file, "&L %-3d  ;LUX sensor sensitivity\n", lux1_time);
   fprintf(file, "&U %-3d  ;LUMEN sensor sensitivity\n", lux2_time);
   fclose(file);
}

void set_cc_mode(int mode, float volts)
{
   if(cc_val) {
      cc_mode = mode;
      lipo_volts = volts;
      cc_state = 0;
      cc_pwm = 0.0F;
      update_check();
   }
   else {
      cc_mode = 0;
      lipo_volts = 0.0F;
      cc_state = 0;
      sweep_stop = 0.0F;
      update_stop = 0;
   }
   cc_pwm = 0.0F;
   set_batt_pwm(0x0000);
}


u08 string_param()
{
float val;
u08 c;
int i;

   // this routine evalates the string in edit_buffer
   // and sets the appropriate parameter value based upon 'getting_string'
   //
   // returns 2 if new queue setting
   // returns 1 if screen redraw needed
   //

   if(getting_string == 'a') {  // all_adevs display mode
      strupr(edit_buffer);
      if(edit_buffer[0] == 'A') mixed_adevs = 0;
      else if(edit_buffer[0] == 'G') mixed_adevs = 1;
      else if(edit_buffer[0] == 'R') mixed_adevs = 2;
      else if(edit_buffer[0] == 'N') mixed_adevs = 2;
      all_adevs = aa_val;
      config_screen();
      redraw_screen();
   }
#ifdef PRECISE_STUFF
   else if(getting_string == 'A') {  // abort precise survey
      if((tolower(edit_buffer[0]) == 'y') || (tolower(edit_buffer[0]) == 'n')) {
         check_precise_posn = 0;
         plot_lla = 0;
         stop_self_survey();        // stop any self survey
         if(tolower(edit_buffer[0]) == 'y') {
            abort_precise_survey();  // save current position using TSIP message
         }
         stop_precision_survey();
      }
   }
#endif
#ifdef OSC_CONTROL
   else if(getting_string == 'b') {  // osc control PID
      if(edit_osc_pid_value(&edit_buffer[0], 1)) {
         edit_error("Unknown osc PID command");
      }
   }
#endif
   else if(getting_string == 'c') {  // DAC control voltage
      if(edit_buffer[0] == 0) val = dac_voltage;
      else val = (float) atof(edit_buffer);
      if(val < (-5.0F)) val = (-5.0F);
      else if(val > 5.0F) val = 5.0F;
      set_discipline_mode(4);
      set_dac_voltage(val);
      osc_discipline = 0;
   }
   else if(getting_string == 'C') { // center line zero reference
      if(edit_buffer[0]) {
         val = (float) atof(edit_buffer);
         plot[selected_plot].plot_center = val;
         plot[selected_plot].float_center = 0;
      }
      else plot[selected_plot].float_center = 1;
      return 0;
   }
   else if(getting_string == 'd') {  // plot scale factor
      if(edit_buffer[0] == 0) val = 0.0F;
      else                    val = (float) atof(edit_buffer);
      if(val < 0.0F) val = 0.0F-val;
      if(strstr(edit_buffer, "-")) plot[selected_plot].invert_plot = (-1.0);
      else                         plot[selected_plot].invert_plot = 1.0;
      plot[selected_plot].user_scale = 1;
      if(val == 0.0F) plot[selected_plot].user_scale = 0;
      else            plot[selected_plot].scale_factor = val;
      set_steps();
      return 0;
   }
   else if(getting_string == 'e') {  // elevation angle
      if(edit_buffer[0]) {
         val = (float) atof(edit_buffer);
         if((val < 0.0F) || (val > 90.0F)) edit_error("Invalid elevation angle");
         else set_el_mask(val);
      }
      else {   // set recommended level
         set_el_level();
      }
      return 0;
   }
   else if(getting_string == 'f') {  // display filter
      if(strstr(edit_buffer, "-"))      plot[PPS].invert_plot = plot[TEMP].invert_plot = (-1.0);
      else if(strstr(edit_buffer, "+")) plot[PPS].invert_plot = plot[TEMP].invert_plot = (+1.0);
      if(edit_buffer[0]) {
         filter_count = (long) atof(edit_buffer);
         if(filter_count < 0) filter_count = 0 - filter_count;
      }
      else filter_count = 0;
      config_screen();
   }
   else if(getting_string == 'g') {       // set plot color
      if(edit_buffer[0]) {
         val = (float) (int) atof(edit_buffer);
         if((val >= 0.0F) && (val < 16.0F)) {
            plot[selected_plot].plot_color = (int) val;
         }
      }
   }
   else if(getting_string == 'h') {       // set chime interval
      strupr(edit_buffer);
      cuckoo_hours = singing_clock = 0;
      if(strstr(edit_buffer, "H")) cuckoo_hours  = 1;
      if(strstr(edit_buffer, "S")) singing_clock = 1;
      val = (float) atof(edit_buffer);
      if(val < 0.0F)  val = 0.0F - val;
      if(val > 60.0F) val = 4.0F;
      cuckoo = (u08) val;
   }
   else if(getting_string == 'H') {  // Graph title
      strcpy(plot_title, edit_buffer);
      if(plot_title[0]) title_type = USER;
      else              title_type = NONE;
      if(log_comments && log_file) fprintf(log_file, "#TITLE: %s\n", plot_title);
      return 1;
   }
   else if(getting_string == 'i') {       // set queue interval
      if(edit_buffer[0]) {
         val = (float) atof(edit_buffer);
         if(val < 1.0) {
            edit_error("Bad queue update interval");
         }
         else {   // !!!!!! luxor
            queue_interval = (long) (val+0.5F);
            plot[DAC].plot_center = last_dac_voltage = 1.0;
            last_temperature = 30.0F;
            plot[TEMP].plot_center = scale_temp(last_temperature);
            return 2;
         }
      }
   }
   else if(getting_string == 'j') {  // log interval
      val = (float) atof(edit_buffer);
      if(val < 0.0F) val = 0.0F - val;
      if(val == 0.0F) val = 1.0F;
      log_interval = (long) val;
      sync_log_file();
      return 1;
   }
#ifdef TEMP_CONTROL
   else if(getting_string == 'k') {  // temperature control PID
      if(edit_pid_value(&edit_buffer[0], 1)) {
         edit_error("Unknown temperature PID command");
      }
   }
#endif
   else if(getting_string == 'l') {  // enter precise lat/lon/alt
      edit_lla_cmd();
   }
#ifdef PRECISE_STUFF
   else if(getting_string == 'L') {  // abort lat/lon/alt position save search
      if((tolower(edit_buffer[0]) == 'y') || (tolower(edit_buffer[0]) == 'n')) {
         check_precise_posn = 0;
         plot_lla = 0;
         stop_self_survey();        // stop any self survey
         if(tolower(edit_buffer[0]) == 'y') {  
            save_precise_posn(1);  // save position using single precision numbers
         }
      }
   }
#endif
   else if(getting_string == 'm') {  // enter AMU mask
      if(edit_buffer[0]) {
         val = (float) atof(edit_buffer);
         if(val < 0.0F) edit_error("Invalid signal level mask");
         else set_amu_mask(val);
      }
      return 0;
   }
   else if(getting_string == 'n') {   // log file name
      if(edit_buffer[0] == 0) {
         edit_error("No file name given");
      }
      else {
         strcpy(log_name, edit_buffer);
         open_log_file(log_mode);
         log_written = 0;
         if(log_file == 0) edit_error("Could not open log file.");
      }
   }
   else if(getting_string == 'o') {  // fOliage or Jamming mode
      if(res_t == 2) {
         if     (tolower(edit_buffer[0]) == 'n') set_foliage_mode(0);
         else if(tolower(edit_buffer[0]) == 's') set_foliage_mode(1);
         else edit_error("Jamming mode must be S)A  N)o");
      }
      else {
         if     (tolower(edit_buffer[0]) == 'n') set_foliage_mode(0);
         else if(tolower(edit_buffer[0]) == 's') set_foliage_mode(1);
         else if(tolower(edit_buffer[0]) == 'a') set_foliage_mode(2);
         else edit_error("Foliage mode must be A)lways  S)ometimes  N)ever");
      }
      return 0;
   }
   else if(getting_string == 'p') {  // pdop mask
      if(edit_buffer[0]) {
         val = (float) atof(edit_buffer);
         if((val < 1.0F) || (val > 100.0F)) edit_error("PDOP make must be 1..100");
         else set_pdop_mask(val);
      }
      return 0;
   }
   else if(getting_string == 'Q') {
      strupr(edit_buffer);
      if     (edit_buffer[0] == 'A')  plot_signals = 1;
      else if(edit_buffer[0] == 'W')  plot_signals = 2;
      else if(edit_buffer[0] == 'E')  plot_signals = 3;
      else if(edit_buffer[0] == 'S')  plot_signals = 4;
      else if(edit_buffer[0] == 'D')  plot_signals = 5;
      else if(edit_buffer[0] == 'R')  clear_signals();
      else if(edit_buffer[0] == 'C')  clear_signals();
      else if(edit_buffer[0] == 0x0A) plot_signals = 0;
      else if(edit_buffer[0] == 0x0D) plot_signals = 0;
      else if(edit_buffer[0] == 0)    plot_signals = 0;
      if(plot_signals == 0) {
         zoom_screen = 0;
         zoom_lla = 0;
      }
      config_screen();
   }
   else if(getting_string == 'r') {   // read in a log file
      #ifdef DOS_MOUSE
         hide_mouse();
      #endif
      c = reload_log(edit_buffer, 0);
      #ifdef DOS_MOUSE
         update_mouse();
      #endif
      if(c == 0) { // adv, tim, log file
         plot_review(0L);
         #ifdef ADEV_STUFF
            force_adev_redraw();    // and make sure adev tables are showing
         #endif
         pause_data = user_pause_data^1;
      }
      else if(c == 3) {  // lla file
         plot_review(0L);
         pause_data = user_pause_data^1;
         return 0;
      }
      else if((c ==  1) || (c == 2)) return 0;   // bad file
   }
   else if(getting_string == 's') {  // do self survey
      if(edit_buffer[0]) {
         do_survey = (long) atof(edit_buffer);
         if(do_survey < 0L) {
            edit_error("Bad self survey size");
         }
         else {
            #ifdef PRECISE_STUFF
               stop_precision_survey();
            #endif
            set_survey_params(1, 1, (long) do_survey);
            request_survey_params();  //!!!
            start_self_survey(0x00);
         }
      }
   }
   else if(getting_string == 'u') {  // receiver dynamics
      if     (tolower(edit_buffer[0]) == 'a') set_rcvr_dynamics(3);
      else if(tolower(edit_buffer[0]) == 'f') set_rcvr_dynamics(4);
      else if(tolower(edit_buffer[0]) == 'l') set_rcvr_dynamics(1);
      else if(tolower(edit_buffer[0]) == 's') set_rcvr_dynamics(2);
      else edit_error("Movement dynamics must be:  A)ir  F)ixed  L)and  S)ea");
      return 0;
   }
   else if(getting_string == 'v') {  // set show interval
      if(edit_buffer[0]) {
         edit_user_view(&edit_buffer[0]);
      }
   }
   else if(getting_string == 'w') {  // Write queue data to log file
      edit_write_cmd();
      return 0;
   }
   else if(getting_string == 'x') {  // single sat mode
      if(edit_buffer[0] == 0) val = 0.0F;
      else val = (float) atof(edit_buffer);
      if(val < 0) val = 0.0F;
      else if(val > 32) val = 0.0F;
      single_sat = (u08) val;
      set_single_sat(single_sat);
      do_fixes(1);
   }
   else if(getting_string == 'Z') {  // set time zone
      set_time_zone(edit_buffer);
      calc_dst_times(dst_list[dst_area]);
   }
#ifdef PRECISE_STUFF
   else if(getting_string == '^') {  // do precision survey;
      if(edit_buffer[0] == 0) val = 48.0F;
      else val = (float) atof(edit_buffer);
      if((val < 1.0) || (val > 60.0))  edit_error("Value must be between 1 and 60.  48 is best.");
      else {
         do_survey = (long) val;
         start_precision_survey();
      }
   }
#endif
#ifdef TEMP_CONTROL
   else if(getting_string == '*') {  // set control temperature;
      if(edit_buffer[0] == 0) val = 0.0F;
      else val = (float) atof(edit_buffer);
      spike_delay = 0;
      if(val == 0.0) {
         disable_temp_control();
         desired_temp = 0.0;
      }
      else if((val < 10.0) || (val > 50.0)) {
         edit_error("Control temperature must be between 10 and 50 degrees C");
      }
      else {
         desired_temp = val;
         enable_temp_control();
      }
   }
#endif
   else if(getting_string == '$') {  // select a new screen resolution
      edit_screen_res();
   }
   else if(getting_string == '~') {  // select a plot statistic
      c = tolower(edit_buffer[0]);
      if(all_plots) {
         for(i=0; i<NUM_PLOTS+DERIVED_PLOTS; i++) {
            if     (c == 'a') plot[i].show_stat = AVG;
            else if(c == 'r') plot[i].show_stat = RMS;
            else if(c == 's') plot[i].show_stat = SDEV;
            else if(c == 'v') plot[i].show_stat = VAR;
            else if(c == 'n') plot[i].show_stat = SHOW_MIN;
            else if(c == 'x') plot[i].show_stat = SHOW_MAX;
            else if(c == 'p') plot[i].show_stat = SHOW_SPAN;
            else if(c == ESC_CHAR) ;
            else              plot[i].show_stat = 0;
         }
      }
      else {
         if     (c == 'a') plot[selected_plot].show_stat = AVG;
         else if(c == 'r') plot[selected_plot].show_stat = RMS;
         else if(c == 's') plot[selected_plot].show_stat = SDEV;
         else if(c == 'v') plot[selected_plot].show_stat = VAR;
         else if(c == 'n') plot[selected_plot].show_stat = SHOW_MIN;
         else if(c == 'x') plot[selected_plot].show_stat = SHOW_MAX;
         else if(c == 'p') plot[selected_plot].show_stat = SHOW_SPAN;
         else if(c == ESC_CHAR) ;
         else              plot[selected_plot].show_stat = 0;
      }
      plot_stat_info = 0;
      for(c=0; c<NUM_PLOTS+DERIVED_PLOTS; c++) {
         plot_stat_info |= plot[c].show_stat;
      }
   }
   else if(getting_string == ',') {  // enter debug value
      edit_option_value();
   }
   else if(getting_string == '-') {  // do command line option
      edit_option_switch();
   }
   else if(getting_string == '=') {  // remove drift rate from plot
      if(edit_buffer[0] == 0) val = 0.0F;
      else val = (float) atof(edit_buffer);
      plot[selected_plot].drift_rate = val;
   }
   else if(getting_string == '%') {  // az/el signal level data
      if(edit_buffer[0] == 0) {
         if(luxor) strcpy(edit_buffer, "luxor.sig");
         else      strcpy(edit_buffer, "tbolt.sig");
      }
      dump_signals(edit_buffer);
   }
   else if((getting_string == ':') || (getting_string == '/') || (getting_string == '!') || (getting_string == '(')) {  // set alarm or exit
      edit_dt(edit_buffer, 1);
   }
   else if(getting_string == 't') {  // efc range
      edit_osc_param();
   }
   else if(getting_string == 'T') {  // efc range
      edit_osc_param();
   }
   else if((getting_string >= '1') && (getting_string <= '8')) { // oscillator disciplinging param
      edit_osc_param();
   }
   else if(getting_string == '9') {  // cable delay
      edit_cable_delay();
   }
   else if(getting_string == DRVR_MODE) {
      strcpy(mode_string, edit_buffer);
      set_driver_mode();
   }
   else if(getting_string == PC_CMD) {
      if(edit_buffer[0]) batt_ovc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PH_CMD) {
      if(edit_buffer[0]) batt_hvc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PL_CMD) {
      if(edit_buffer[0]) batt_lvc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PM_CMD) {
      if(edit_buffer[0]) msg_timeout = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PO_CMD) {
      if(edit_buffer[0]) load_ovc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PP_CMD) {
      if(edit_buffer[0]) load_watts = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PR_CMD) {
      if(tolower(edit_buffer[0]) == 'r') reset_luxor_wdt(0x01);
   }
   else if(getting_string == PS_CMD) {
      if(edit_buffer[0]) tc2_ovt = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PT_CMD) {
      if(edit_buffer[0]) tc1_ovt = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PU_CMD) {
      if(edit_buffer[0]) load_lvc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PV_CMD) {
      if(edit_buffer[0]) load_hvc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PW_CMD) {
      if(edit_buffer[0]) batt_watts = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PX_CMD) {
      if(edit_buffer[0]) auxv_hvc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == PZ_CMD) {
      if(edit_buffer[0]) auxv_lvc = (float) atof(edit_buffer);
      set_luxor_config();
   }
   else if(getting_string == WC_CMD) {
      write_luxor_config();
   }
   else if(getting_string == S_CMD) {
      lat = lon = alt = 0.0;
      sscanf(edit_buffer, "%lf %lf %lf", &lat, &lon, &alt);
      lat /= RAD_TO_DEG;
      lon /= RAD_TO_DEG;
      precise_lat = lat;
      precise_lon = lon;
      precise_alt = alt;
   }
   else if(getting_string == BC_CMD) {  // constant current load
      if(edit_buffer[0]) cc_val = (float) atof(edit_buffer);
      strupr(edit_buffer);
      if(strstr(edit_buffer, "S")) sweep_stop = cc_val;
      else if(strstr(edit_buffer, "R")) sweep_stop = cc_val;
      unsafe_v = 0.0F;
      set_cc_mode(CC_AMPS, 0.00F);
   }
   else if(getting_string == BF_CMD) {  // lifepo4 battery charge mode
      if(edit_buffer[0]) cc_val = (float) atof(edit_buffer);
      unsafe_v = 2.0F;
      if(strstr(edit_buffer, "unsafe")) unsafe_v = 0.0F;
      if(led_v < unsafe_v) {
         edit_error("Battery voltage is too low to safely charge!");
      }
      else if(led_v > (3.60F-0.05F)) {
         edit_error("Battery appears to be fully charged!");
      }
      else {
         sweep_stop = 0.0F;
         set_cc_mode(CC_LIPO, 3.60F);
      }
   }
   else if(getting_string == BH_CMD) {  // high voltage lipo battery charge mode
      cc_val = 0.0F;
      lipo_volts = 0.0F;
      i = sscanf(edit_buffer, "%f %f", &cc_val, &lipo_volts);
      if(i != 2) {
         edit_error("ERROR: must specify charge curent and charge voltage!");
         return 0;
      }

      unsafe_v = lipo_volts * 0.60F;
      if(strstr(edit_buffer, "unsafe")) unsafe_v = 0.0F;
      if(led_v < unsafe_v) {
         edit_error("Battery voltage is too low to safely charge!");
      }
      else if(unsafe_v && (led_v > (lipo_volts-0.05F))) {
         edit_error("Battery appears to be fully charged!");
      }
      else {
         sweep_stop = 0.0F;
         set_cc_mode(CC_LIPO, lipo_volts);
      }
   }
   else if(getting_string == BL_CMD) {  // lipo battery charge mode
      if(edit_buffer[0]) cc_val = (float) atof(edit_buffer);
      unsafe_v = 2.50F;
      if(strstr(edit_buffer, "unsafe")) unsafe_v = 0.0F;
      if(led_v < unsafe_v) {
         edit_error("Battery voltage is too low to safely charge!");
      }
      else if(unsafe_v && (led_v > (4.20F-0.05F))) {
         edit_error("Battery appears to be fully charged!");
      }
      else {
         sweep_stop = 0.0F;
         set_cc_mode(CC_LIPO, 4.20F);
      }
   }
   else if(getting_string == BP_CMD) {  // PWM resolution
      if(strstr(edit_buffer, "8")) batt_pwm_res = 8;
      else if(strstr(edit_buffer, "9")) batt_pwm_res = 9;
      else batt_pwm_res = 10;
      set_luxor_config();
   }
   else if(getting_string == BR_CMD) {  // PWM sweep rate
      sweep_rate = 1;
      sscanf(edit_buffer, "%d", &sweep_rate);
   }
   else if(getting_string == BS_CMD) {  // PWM sweep
      sweep_start = sweep_end = 0.0F;
      sscanf(edit_buffer, "%f %f", &sweep_start, &sweep_end);
      if(sweep_start < 0.0F) sweep_start = 0.0F;
      if(sweep_start > 1.0F) sweep_start = 1.0F;
      if(sweep_end < 0.0F) sweep_end = 0.0F;
      if(sweep_end > 1.0F) sweep_end = 1.0F;
      cc_mode = PWM_SWEEP;
      update_check();
      sweep_stop = 0.0F;
      cc_state = 0;
      cc_pwm = sweep_start;
   }
   else if(getting_string == BV_CMD) {  // constant load volatge
      if(edit_buffer[0]) cc_val = (float) atof(edit_buffer);
      strupr(edit_buffer);
      if(strstr(edit_buffer, "S")) sweep_stop = cc_val;
      else if(strstr(edit_buffer, "R")) sweep_stop = cc_val;
      unsafe_v = 0.0F;
      set_cc_mode(CC_VOLTS, 0.00F);
   }
   else if(getting_string == BW_CMD) {  // constant load wattage
      if(edit_buffer[0]) cc_val = (float) atof(edit_buffer);
      strupr(edit_buffer);
      if(strstr(edit_buffer, "S")) sweep_stop = cc_val;
      else if(strstr(edit_buffer, "R")) sweep_stop = cc_val;
      unsafe_v = 0.0F;
      set_cc_mode(CC_WATTS, 0.00F);
   }
   else if(getting_string == AMPL_CMD) {
      strupr(edit_buffer);
      if     (strstr(edit_buffer, "L")) lux1_time = LOW_LUX;
      else if(strstr(edit_buffer, "M")) lux1_time = MED_LUX;
      else if(strstr(edit_buffer, "H")) lux1_time = HI_LUX;
      else {
         lux1_time = (u08) atof(edit_buffer);
         if(lux1_time < 1) lux1_time = 2;
         else if(lux1_time > MAX_LUX) lux1_time = MAX_LUX;
      }
      set_luxor_sens(lux1_time, lux2_time);
   }
   else if(getting_string == AMPU_CMD) {
      strupr(edit_buffer);
      if     (strstr(edit_buffer, "L")) lux2_time = LOW_LUX;
      else if(strstr(edit_buffer, "M")) lux2_time = MED_LUX;
      else if(strstr(edit_buffer, "H")) lux2_time = HI_LUX;
      else {
         lux2_time = (u08) atof(edit_buffer);
         if(lux2_time < 1) lux2_time = 2;
         else if(lux2_time > MAX_LUX) lux2_time = MAX_LUX;
      }
      set_luxor_sens(lux1_time, lux2_time);
   }
   else if(getting_string == AMPE_CMD) {
      emis1 = (float) atof(edit_buffer);
      if(emis1 < 0.1F) emis1 = 0.1F;
      else if(emis1 > 1.0F) emis1 = 1.0F;
      set_emissivity(emis1, emis2);
   }
   else if(getting_string == AMPI_CMD) {
      emis2 = (float) atof(edit_buffer);
      if(emis2 < 0.1F) emis2 = 0.1F;
      else if(emis2 > 1.0F) emis2 = 1.0F;
      set_emissivity(emis1, emis2);
   }
   else if(getting_string == AMPS_CMD) {
      strupr(edit_buffer);
      if(strstr(edit_buffer, "SERIAL")) {
         vref_b = (float) atof(edit_buffer);
         if(vref_b < 0.0F) vref_b = 0.0F;
         vref_b = vref_b * 10000.0F + 0.50F;
         vref_b = ((float) (int) vref_b) / 10000.0F;
         set_luxor_cal();
      }
      else {
         edit_error("You did not say the magic word!");
      }
   }
   else if(getting_string == AMPV_CMD) {
      strupr(edit_buffer);
      if(strstr(edit_buffer, "VREF")) {
         vref_m = (float) atof(edit_buffer);
         if(vref_m < 1.00F) vref_m = 5.0F;
         else if(vref_m > 6.50F) vref_m = 6.144F;
         set_luxor_cal();
      }
      else {
         edit_error("You did not say the magic word!");
      }
   }
   else if(getting_string == CAL_CMD) {
      edit_cal_param();
   }
   else {
      if(getting_string >= 0x0100) sprintf(out, "Unknown edit string: 0x%04X", getting_string);
      else                         sprintf(out, "Unknown edit string: %c", getting_string);
      edit_error(out);
   }

   return 1;
}



void kbd_exit()
{
   // user told the program to exit
   break_flag = 1;
   erase_help();
   vidstr(EDIT_ROW+4, EDIT_COL, RED, "Exiting...");
   refresh_page();
}

int sure_exit()
{
   // normal keystroke processor exit
   if(first_key) {    // we were processing a two-character command
      first_key = 0;  // command sequence is done
      prot_menu = 0;
      draw_plot(1);   // replace command sub-menu with the normal plot
   }
   return 0;
}

int help_exit(int c, int reason)
{
   // There was an error in the keyboard command.
   // Exit the keystroke processor with a help message
   reason = 0;       // shut up compiler warning
   script_err = c;
   prot_menu = 0;

   // if reading from a script file,  CR, LF, SPACE, TAB do not bring up help menu
   if(script_file) {   // script file is active
      if((c == 0x0D) || (c == 0x0A)) {  // end-of line reached
         script_pause = 0;
         return sure_exit();
      }
      else if(c == ' ') return sure_exit();
      else if(c == '\t') return sure_exit();
      else c = '?';
   }
   else c = '?';

   if(are_you_sure(c) != c) return 0;
   else if(script_file) return 0;

   return sure_exit();
}

int cmd_error(int c)
{
   return are_you_sure(c);
}

u08 toggle_value(u08 x)
{
int c;

   // commands that normally toggle the parameter can be forced on or off
   // by following them with a 0,1,y,n when they are in script files
   // i.e.  gu  - toggles graph update mode
   //       gu1 - sets graph update mode
   //       gun - clears graph update mode
   if(script_file && (script_pause == 0)) {
      c = get_script();
      if     ((c == '1') || (c == 'y') || (c == 'Y')) return 1;
      else if((c == '0') || (c == 'n') || (c == 'N')) return 0;
   }

   return (x & 1) ^ 1;
}

void share_it()
{
if(0) {
   if(plot_azel == 0)   {
      plot_azel = AZEL_OK;
      shared_plot = 1;
   }
   else if(shared_plot) {
      plot_azel = 0;
      shared_plot = 0;
   }
   else shared_plot = 1;
   if(WIDE_SCREEN && (plot_watch == 0)) shared_plot = 0;  // no need to share plot on wide screens
   //shared_plot = 1;
}
   shared_plot = toggle_value(shared_plot);
   first_key = 0;
   prot_menu = 0;
   config_screen();
   redraw_screen();
}

void edit_plot(int id, int c)
{
char *s;
char *a;

   // process the plot control commands

   last_selected_plot = selected_plot;
   selected_plot = id;
   #ifdef FFT_STUFF
      if(selected_plot != FFT) live_fft = selected_plot;
   #endif
   getting_plot = c;
   first_key = '{';
   prot_menu = 0;
   set_steps();

   if(text_mode) erase_screen();
   else          erase_help();

   // display prompt string for the command
   if(plot[selected_plot].show_plot) s = "hide";
   else                              s = "show";
   if(auto_scale) a = "disable";
   else           a = "enable";
   sprintf(out, " %4s plot: A)utoscale %s all plots   X) toggle %s plot autoscale modes",
                 plot[selected_plot].plot_id, a, plot[selected_plot].plot_id);
   vidstr(EDIT_ROW+0, EDIT_COL, PROMPT_COLOR, out);

   #ifdef FFT_STUFF
      if(selected_plot == FFT) sprintf(out, "            C)olor   I)nvert   S)cale factor   trend L)ine");
      else if(luxor)           sprintf(out, "            C)olor   I)nvert   S)cale factor   trend L)ine   &)Cal");
      else                     sprintf(out, "            C)olor   F)FT   I)nvert   S)cale factor   trend L)ine");
   #else                 
      if(luxor) sprintf(out, "            C)olor   I)nvert   S)cale factor   trend L)ine   &)Cal");
      else      sprintf(out, "            C)olor   I)nvert   S)cale factor   trend L)ine");
   #endif
   vidstr(EDIT_ROW+1, EDIT_COL, PROMPT_COLOR, out);

   sprintf(out, "            Z)ero ref   /)statistics  =)remove drift   %c or <cr>=%s", c, s);
   vidstr(EDIT_ROW+2, EDIT_COL, PROMPT_COLOR, out);

   refresh_page();
}



void set_steps()
{
   scale_step = plot[selected_plot].scale_factor*0.01F;
   center_step = 0.0F;
   if(plot[selected_plot].ref_scale) {
      center_step = plot[selected_plot].scale_factor/(plot[selected_plot].ref_scale*10.0F);
   }
}

void move_plot_up()
{
   plot[selected_plot].user_scale = 1;
   plot[selected_plot].float_center = 0;
   plot[selected_plot].plot_center -= center_step;
}

void move_plot_down()
{
   plot[selected_plot].user_scale = 1;
   plot[selected_plot].float_center = 0;
   plot[selected_plot].plot_center += center_step;
}

void shrink_plot()
{
   plot[selected_plot].user_scale = 1;
   plot[selected_plot].float_center = 0;
   plot[selected_plot].scale_factor += scale_step;
}

void grow_plot()
{
   plot[selected_plot].user_scale = 1;
   plot[selected_plot].float_center = 0;
   plot[selected_plot].scale_factor -= scale_step;
}

void toggle_plot(int id)
{
int i;

   if((id < 0) || (id >= (NUM_PLOTS+DERIVED_PLOTS))) return;

   selected_plot = id;
   plot[selected_plot].show_plot = toggle_value(plot[selected_plot].show_plot);
   if((graph_lla == 0) && (selected_plot == THREE) && (luxor == 0)) {  //!!!! debug_plots
      if(plot[DAC].sum_yy && stat_count) {
          d_scale = sqrt(plot[TEMP].sum_yy/stat_count) / sqrt(plot[DAC].sum_yy/stat_count);
      }
      else d_scale = 0.0;
if(title_type != USER) {
   sprintf(plot_title, "DAC_scale=%f", d_scale);
   title_type = OTHER;
}
   }


   extra_plots = 0;  // this flag gets set if any extra plots are enabled
   for(i=FIRST_EXTRA_PLOT; i<NUM_PLOTS+DERIVED_PLOTS; i++) {  
      extra_plots |= plot[i].show_plot;
   }

   if(extra_plots) {  // turn off adevs if any extra plot is on
      plot_adev_data = 0;
      redraw_screen();
   }
   if(luxor && (id == AUXV)) redraw_screen();
}

int change_plot_param(int c)
{
    // this routine acts upon the plot control command
    if(c < 0x0100) c = tolower(c);

    if((c == 0x0D) || (c == getting_plot)) {  // toggle plot
       if(selected_plot == FFT) plot[selected_plot].show_plot = 1;
       toggle_plot(selected_plot);
    }
    else if(c == 'a') {  // autoscale (all plots)
       auto_scale = toggle_value(auto_scale);
       auto_center = auto_scale;
    }
    else if(c == 'c') {  // graph color
       getting_plot = 0;
       edit_buffer[0] = 0;
       sprintf(out, "Enter color for %s graph (0-15):", plot[selected_plot].plot_id);
       start_edit('g', out);
       return 1;
    }
#ifdef FFT_STUFF
    else if(c == 'f') {
       calc_fft(selected_plot);
    }
#endif
    else if(c == 'g') {  // g acts like an ignore
    }
    else if(c == 'i') {  // invert plot
       plot[selected_plot].invert_plot *= (-1.0F);
    }
    else if(c == 'l') {  // trend line
       plot[selected_plot].show_trend = toggle_value(plot[selected_plot].show_trend);
       if(plot[selected_plot].show_trend && (title_type != USER)) {
          sprintf(plot_title, "%s trend line: %s = (%g*t) + %g   avg_delta=%g", 
                              plot[selected_plot].plot_id,
                              plot[selected_plot].plot_id,
                              plot[selected_plot].a1,
                              plot[selected_plot].a0,
                              (plot[selected_plot].sum_change/plot[selected_plot].stat_count)/view_interval
          );
          title_type = OTHER;
       }
    }
    else if(c == '/') {
       getting_plot = 0;
       all_plots = 0;
       edit_buffer[0] = 0;
       edit_info1 =    "                            mi)N   ma)X   s)Pan";
       start_edit('~', "Enter statistic to display: A)vg   R)ms   S)td dev   V)ar   <cr>=hide");
       return 1;
    }
    else if((c == 'm') || (c == 's') || (c == 'f')) {  // modify scale factor
       getting_plot = 0;
       edit_scale();
       return 1;
    }
    else if(c == 'x') {  // toggle scale modes
       plot[selected_plot].user_scale = toggle_value(plot[selected_plot].user_scale);
       plot[selected_plot].float_center = toggle_value(plot[selected_plot].float_center);
    }
    else if((c == 'z') || (c == 'r')) {  // zero reference line
       getting_plot = 0;
       edit_ref();
       return 1;
    }
    else if(c == '+') {  // move graph up
       move_plot_up();
    }
    else if(c == '-') {  // move graph down
       move_plot_down();
    }
    else if(c == '{') {  // make plot smaller
       shrink_plot();
    }
    else if(c == '}') {  // make plot bigger
       grow_plot();
    }
    else if(c == '=') {  // remove dift rate
       getting_plot = 0;
       edit_drift();
       return 1;
    }
//  else if((c == '&') && luxor && cal_mode) {
    else if((c == '&') && luxor) {
       getting_plot = 0;
       edit_cal();
       return 1;
    }
    else if(c == ESC_CHAR) {
    }
    else {
       getting_plot = 0;
       sprintf(out, "Invalid plot command: %c", c);
       edit_error(out);
    }

    refresh_page();
    getting_plot = 0;
    return 0;
}


void kbd_marker(int c)
{
long val;

   // set a plot marker from the keyboard
   last_was_mark = c;
   c -= '0';
   if(mark_q_entry[c]) {  // marker was set,  go to it
      goto_mark(c);
   }
   else {  // mark current spot if it is not already marked
      for(val=1; val<MAX_MARKER; val++) {
         if(mark_q_entry[val] == last_mouse_q) {  // place is already marked
            BEEP();
            return;
         }
      }
      mark_q_entry[c] = last_mouse_q;
      draw_plot(1);
   }
}

int set_next_marker()
{
int val;

   // mark current mouse column with the next available marker number
   for(val=1; val<MAX_MARKER; val++) {
      if(mark_q_entry[val] == last_mouse_q) {  // place is already marked
         mark_q_entry[val] = 0;
         draw_plot(1);
         return 1;
      }
   }
   for(val=1; val<MAX_MARKER; val++) {
      if(mark_q_entry[val] == 0) {
         last_was_mark = '0'+val;
         mark_q_entry[val] = last_mouse_q;  // last marker is mouse click marker
         draw_plot(1);
         return 1;
      }
   }

   BEEP();
   return 0;
}



void do_fixes(int mode)
{
   show_fixes = toggle_value(show_fixes);
   
   if(show_fixes && (mode >= 0) && (mode <= 7)) {  // 3d fix mode
      start_3d_fixes(mode);
      if(GRAPH_LLA && (graph_lla == 0)) {
         config_lla_plots();
      }
   }
   else {            // normal overdetermined clock mode
      set_rcvr_config(7);   
      plot_lla = 0;
      if(GRAPH_LLA && graph_lla) {
         config_normal_plots();
      }
   }
   request_rcvr_config();
   first_key = 0;
   prot_menu = 0;
   config_screen();
   redraw_screen();
}


void dump_image()
{
   dump_type = 's';
   #ifdef GIF_FILES
      if(luxor) strcpy(edit_buffer, "LUXOR.GIF");
      else      strcpy(edit_buffer, "TBOLT.GIF");
      if(top_line) start_edit('w', "Enter name of .GIF or .BMP file for GRAPH image (ESC ESC to abort):");
      else         start_edit('w', "Enter name of .GIF or .BMP file for SCREEN image (ESC ESC to abort):");
   #else
      if(luxor) strcpy(edit_buffer, "LUXOR.BMP");
      else      strcpy(edit_buffer, "TBOLT.BMP");
      if(top_line) start_edit('w', "Enter name of .BMP file for GRAPH image (ESC ESC to abort):");
      else         start_edit('w', "Enter name of .BMP file for SCREEN image (ESC ESC to abort):");
   #endif
}


int kbd_a_to_o(int c)
{
u32 val;

   // Process keyboard characters a..o
   if(c == 'a') {
      if(first_key == 'c') {  // CA command - clear adev queues
         if(luxor) return help_exit(c,99);
         new_queue(1);
      }
      else if(first_key == 'f') {  // FA command - toggle ALT filter
         if(luxor) return help_exit(c,99);
         alt_filter = toggle_value(alt_filter);
         set_filter_config(pv_filter, static_filter, alt_filter, kalman_filter, 1);
      }
      else if(first_key == 'l') {  // LA command - open log in append mode
         if(log_file) edit_error("Log file is already open.");
         else {
            log_mode = "a";
            strcpy(edit_buffer, log_name);
            start_edit('n', "Enter log file name to append data to: ");
            return 0;
         }
      }
      else if(first_key == 's') {  // SA command - antenna survey
         if(luxor) return help_exit(c,99);
         edit_buffer[0] = 0;
         start_edit('Q', "A)zimuth  W)eighted azimuth  E)levation  S)ignals  D)ata  C)lear  <cr>=off");
         return 0;
      }
      else if(first_key == 't') { // TA command - set alarm clock time
         if     (script_file) edit_buffer[0] = 0;
         else if(alarm_time && alarm_date) sprintf(edit_buffer, "%02d:%02d:%02d  %02d/%02d/%02d", alarm_hh,alarm_mm,alarm_ss, alarm_month,alarm_day,alarm_year); 
         else if(alarm_time) sprintf(edit_buffer, "%02d:%02d:%02d", alarm_hh,alarm_mm,alarm_ss);
         else if(alarm_date) sprintf(edit_buffer, "%02d/%02d/%02d", alarm_month,alarm_day,alarm_year);
         else if(egg_val) {
            if((egg_val >= (24L*3600L)) && ((egg_val % 24L*3600L) == 0)) sprintf(edit_buffer, "%ld d", egg_val/(24L*3600L));
            else if((egg_val >= (3600L)) && ((egg_val % 3600L) == 0)) sprintf(edit_buffer, "%ld h", egg_val/(3600L));
            else if((egg_val >= (60L)) && ((egg_val % 60L) == 0)) sprintf(edit_buffer, "%ld m", egg_val/(60L));
            else sprintf(edit_buffer, "%ld s", egg_val);
         }
         else edit_buffer[0] = 0;
         if(edit_buffer[0]) start_edit(':', "Enter alarm clock time (and optional date) or interval or <ESC CR> to reset:");
         else               start_edit(':', "Enter alarm clock time (and optional date) or interval or <CR> to reset:");
         return 0;
      }
      else if(first_key == 'w') {  // WA command - Output all data to a log file
         strcpy(edit_buffer, "DUMP.LOG");
         sprintf(out, "Enter name of log file to write ALL %squeue info to (ESC ESC to abort):",
                       filter_log?"filtered ":"");
         start_edit('w', out);
         dump_type = 'a';
         log_mode = "w";
         return 0;
      }
      else if(first_key == '&') {  // &A command - autotune osc params
         if(luxor) return help_exit(c,99);
         dac_dac = 1;
      }
      #ifdef ADEV_STUFF
         else if(first_key == 'a') {  // AA command - set adev type to ADEV
            if(luxor) return help_exit(c,99);
            ATYPE = OSC_ADEV;
            all_adevs = 0;
            force_adev_redraw();
            config_screen();
            redraw_screen();
         }
         else if(first_key == 'g') { 
            if(luxor) {  // GA command - toggle ADEV plot
               show_prots = toggle_value(show_prots);
            }
            else {  // GA command - toggle ADEV plot
               plot_adev_data = toggle_value(plot_adev_data);
               draw_plot(1);
            }
         }
         else if(luxor) {  // A commands
            return help_exit(c,1);
         }
         else if(are_you_sure(c) != c) return 0;
      #else
         else return help_exit(c,1);
      #endif
   }
   else if(c == 'b') {
      if(first_key == 'c') {  // CB command - clear both queues
//!!!!-  pause_data = 0;
         if(luxor) return help_exit(c,99);
         new_queue(3);
      }
      else if(first_key == 'g') {  // GB command - satellite map, shared with plot area
         share_it();
      }
      else if(first_key == '!') {    // !b command - send break command to the receiver
         SetDtrLine(1);
         SendBreak();
         redraw_screen();
      }
      else if(first_key == 0) {
         if(luxor) {
            if(are_you_sure(c) != c) return 0;
         }
         else {
            edit_buffer[0] = 0;
            start_edit('b',  "Enter osc PID command:  K)P_GAIN,D_TC,FIL_TC,I_TC   H)elp");
            return 0;
         }
      }
      else return help_exit(c,2);
   }
   else if(c == 'c') {
      if(luxor && (first_key == 'b')) {  // BC command - constant load current mode
         sprintf(edit_buffer, "%f", 0.1F);
         start_edit(BC_CMD, "Enter desired load current in amps.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'c') {  // CC command - clear both queues
//!!!!-  pause_data = 0;
         new_queue(3);
      }
      else if(first_key == 'g') { 
         if(luxor) {  // GC command - show battery capacity
            show_mah  = toggle_value(show_mah);
            debug_text[0] = 0;
            redraw_screen();
redraw_screen();
         }
         else {       // GC command - show sat counts
            plot_sat_count = toggle_value(plot_sat_count);
            draw_plot(1);
         }
      }
      else if(first_key == 'l') {  // LC command - toggle logging of sat constellation data
         if(luxor) return help_exit(c,99);
         log_db ^= 1;
      }
      else if(luxor && (first_key == 'p')) {  // PC command = load overcurrent
         sprintf(edit_buffer, "%f", batt_ovc);
         start_edit(PC_CMD, "Enter the battery overcurrent cutoff in amps.  (ESC ESC to abort):");
         return 0;
      }
      else if(luxor && (first_key == 'w')) {  // WC command = write config data
         sprintf(edit_buffer, "LUXCFG.SCR");
         start_edit(WC_CMD, "Enter config data script file to write (ESC ESC to abort)");
         return 0;
      }
      else if(first_key == '$') {  // $c command - custom screen
         new_screen(c);
         return 0;
      }
      else if(first_key == '&') { 
         if(luxor) { // &c command - toggle cal mode
            cal_mode = toggle_value(cal_mode);
            if(cal_mode) set_cal_mode(0x01);
            else         set_cal_mode(0x00);
            Sleep(100);
         }
         else {  // &c command - set cable delay
            osc_params = 0;
            redraw_screen();
            edit_buffer[0] = 0;
            edit_info1 = "Note: use NEGATIVE values to compensate for cable delay!";
            start_edit('9', "Enter cable delay in ns or use #feet or #meters (ESC ESC to abort):");
            return 0;
         }
      }
      else if(first_key == '!') {    // !c command - cold start reset
         request_cold_reset();
         redraw_screen();
      }
      else if(first_key == 0) {  // C command first char
         if(are_you_sure(c) != c) return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'd') {  
      if(first_key == 'd') { // DD command - disable osc discipline
         if(luxor) return help_exit(c,99);
         osc_discipline = 0;
         set_discipline_mode(4);
         redraw_screen();
      }
      else if(first_key == 'g') { // GD command - toggle DAC graph
         edit_plot(DAC, c);
         return 0;
      }
      else if(first_key == 'f') { // FD command - toggle display filter
         if(filter_count) strcpy(edit_buffer, "0");
         else             strcpy(edit_buffer, "10");
         start_edit('f', "Enter number of display points to average (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 'l') { // LD command - delete file
         strcpy(edit_buffer, log_name);
         goto delete_file;
      }
      else if(first_key == 't') { // TD command - set screen dump time
         if     (script_file) edit_buffer[0] = 0;
         else if(dump_time && dump_date) sprintf(edit_buffer, "%02d:%02d:%02d  %02d/%02d/%02d", dump_hh,dump_mm,dump_ss, dump_month,dump_day,dump_year); 
         else if(dump_time) sprintf(edit_buffer, "%02d:%02d:%02d", dump_hh,dump_mm,dump_ss);
         else if(dump_date) sprintf(edit_buffer, "%02d/%02d/%02d", dump_month,dump_day,dump_year);
         else if(dump_val) {
            if((dump_val >= (24L*3600L)) && ((dump_val % 24L*3600L) == 0)) sprintf(edit_buffer, "%ld d", dump_val/(24L*3600L));
            else if((dump_val >= (3600L)) && ((dump_val % 3600L) == 0)) sprintf(edit_buffer, "%ld h", dump_val/(3600L));
            else if((dump_val >= (60L)) && ((dump_val % 60L) == 0)) sprintf(edit_buffer, "%ld m", dump_val/(60L));
            else sprintf(edit_buffer, "%ld s", dump_val);
         }
         else edit_buffer[0] = 0;
         if(edit_buffer[0]) start_edit('!', "Enter screen dump time (and optional date) or interval or <ESC CR> to reset:");
         else               start_edit('!', "Enter screen dump time (and optional date) or interval or <CR> to reset:");
         return 0;
      }
      else if(first_key == 'w') { // WD command - delete file
         edit_buffer[0] = 0;
         delete_file:
         start_edit('w', "Enter name of file to delete (ESC ESC to abort):");
         dump_type = 'd';
         return 0;
      }
      else if(first_key == '&') { // &D command - change damping factor
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_damping_factor);
         start_edit('2', "Enter damping factor (ESC ESC to abort):");
         return 0;
      }
      else {   // D command - toggle oscillator disciplining
         if(luxor) return help_exit(c, 99);
         if(are_you_sure(c) != c) return 0;
         // next call to do_kbd() will process the discipline selection character
      }
   }
   else if(c == 'e') {  
      if(first_key == 'd') { // DE command - enable osc discipline
         if(luxor) return help_exit(c,99);
         osc_discipline = 1;
         set_discipline_mode(5);
         redraw_screen();
      }
      else if(first_key == 'e') { // EE command - save eeprom segments
         if(luxor) return help_exit(c,99);
         save_segment(0xFF);
      }
      else if(first_key == 'f') {  // FE command - elevation mask
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%.1f", el_mask);
         start_edit('e',  "Enter minimum acceptible satellite elevation (in degrees,  ESC CR=best)");
         return 0;
      }
      else if(first_key == 'g') {  // GE command - toggle error graph
         plot_skip_data = toggle_value(plot_skip_data);
         draw_plot(1);
      }
      else if(luxor && (first_key == '&')) { // &e command - IR emissivity
         sprintf(edit_buffer, "%f", emis1);
         start_edit(AMPE_CMD, "Enter IR1 sensor emissivity (0.1 .. 1.0)  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 0) {  // E command first char
         if(luxor) return help_exit(c,99);
         if(are_you_sure(c) != c) return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'f') {  // filter selection
      if(first_key == '&') { // &F command - max freq offset
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_max_freq_offset);
         sprintf(out, "Enter max freq offset in %s (ESC ESC to abort):", ppb_string);
         start_edit('7', out);
         return 0;
      }
      else if(luxor && (first_key == 'b')) {  // BF command - lifepo4 charge mode
         sprintf(edit_buffer, "%f", 0.1F);
         start_edit(BF_CMD, "Enter desired LiFePO4 charge current in amps.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'f') {  // FF command - set foliage filter
         if(luxor) return help_exit(c,99);
         if     (foliage_mode == 0) strcpy(edit_buffer, "N");
         else if(foliage_mode == 2) strcpy(edit_buffer, "A");
         else                       strcpy(edit_buffer, "S");
         start_edit('o', "Foliage:  A)lways   S)ometimes   N)ever");
         return 0;
      }
      #ifdef FFT_STUFF
         else if(first_key == 'g') {   // GF command - fft plot
            edit_plot(FFT, c);
            return 0;
         }
      #endif
      #ifdef PRECISE_STUFF
         else if(first_key == 's') {  // SF command - show fixes
            if(luxor) return help_exit(c,99);
            do_fixes(0); // 2D/3D mode
         }
      #endif
      else if(first_key == 'w') {  // WF command - write filtered data to log
         filter_log = toggle_value(filter_log);
      }
      else {  // F command - toggle filter
         if(are_you_sure(c) != c) return 0;
         // next call to do_kbd() will process the filter selection character
      }
   }
   else if(c == 'g') {  
      if(first_key == 'g') {  // GG command - graph title
         strcpy(edit_buffer, plot_title);
         start_edit('H', "Enter graph description (ESC <cr> to erase):");
         return 0;
      }
      else if(first_key == 't') {  // TG commmand - use GPS time
//       time_zone_set = 0;
         if(luxor) return help_exit(c,99);
         temp_utc_mode = 0;
         set_timing_mode(0x00);
         request_timing_mode();
      }
      else if(first_key == 'w') {  // WG command - plot image dump
         invert_video = 0;
         top_line = (MOUSE_ROW+2)*TEXT_HEIGHT;
         dump_image();
         return 0;
      }
      else if(first_key == '&') { // &G command - oscillator gain
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_osc_gain);
         start_edit('3', "Enter oscillator gain in Hz/v (ESC ESC to abort):");
         return 0;
      }
      else {  // G command - select graph/display option
         if(are_you_sure(c) != c) return 0;  // select a graph to toggle
         // next call to do_kbd() will process the graph selection character
      }
   }
   else if(c == 'h') {  // toggle manual holdover mode
      if(first_key == '&') { // &H command - change max allowale dac voltage
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_max_range);
         start_edit('T', "Enter maximum DAC voltage range value (ESC ESC to abort):"); 
         return 0;
      }
      else if(luxor && (first_key == 'b')) {  // BH command - high voltage lipo charge mode
         sprintf(edit_buffer, "%f %f", 0.1F, 4.30F);
         start_edit(BH_CMD, "Enter desired charge current in amps and voltage in volts.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'g') { // GH command - toggle HOLDOVER plot
         if(luxor) return help_exit(c,99);
         plot_holdover_data = toggle_value(plot_holdover_data);
         draw_plot(1);
      }
      else if(first_key == 'h') {  // HH command - toggle holdover mode
         if(luxor) return help_exit(c,99);
         user_holdover = toggle_value(user_holdover);
         if(user_holdover) set_discipline_mode(2);
         else              set_discipline_mode(3);
      }
      else if(luxor && (first_key == 'p')) {  // PH command = battery high voltage cutoff
         sprintf(edit_buffer, "%f", batt_hvc);
         start_edit(PH_CMD, "Enter the battery high voltage cutoff in volts.  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 't') {  // TH command - set chime mode
         if(cuckoo) sprintf(edit_buffer, "%d", cuckoo);
         else       sprintf(edit_buffer, "4");
         if(singing_clock) strcat(edit_buffer, "S");
         if(cuckoo_hours)  strcat(edit_buffer, "H");
         start_edit('h', "Chime/sing at # places per hour (#S=sing  #H=chime out hours):");
         return 0;
      }
      else if(first_key == '$') {  // $h command - huge screen
         new_screen(c);
         return 0;
      }
      else if(first_key == '!') {    // !h command - hard factory reset
         request_factory_reset();
         redraw_screen();
      }
      #ifdef ADEV_STUFF
         else if(first_key == 'a') {  // AH command - set adev type to HDEV
            if(luxor) return help_exit(c,99);
            ATYPE = OSC_HDEV;
            all_adevs = 0;
            force_adev_redraw();
            config_screen();
            redraw_screen();
         }
      #endif
      else if(first_key == 0) {  // H command first char - set holdover mode
         if(luxor) return help_exit(c, 99);
         if(are_you_sure(c) != c) return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'i') {  // set queue update interval
      if(first_key == '&') { 
         if(luxor) {         // &i command - IR2 emissivity
            sprintf(edit_buffer, "%f", emis2);
            start_edit(AMPI_CMD, "Enter IR2 sensor emissivity (0.1 .. 1.0)  (ESC ESC to abort):"); 
            return 0;
         }
         else {   // &i command - initial dac voltage
            sprintf(edit_buffer, "%f", user_initial_voltage);
            start_edit('8', "Enter initial DAC voltage (ESC ESC to abort):");
            return 0;
         }
      }
      else if(luxor && (first_key == 'b')) {  // BI command - calc internal resistance
         calc_ir = IR_TIME;
         pause_data = 0;
         redraw_screen();
      }
      else if(first_key == 'g') { // GI command - toggle BATTw graph
         edit_plot(ELEVEN, c);
         return 0;
      }
      else if(first_key == 'l') { // LI command - set log interval
         sprintf(edit_buffer, "%ld", log_interval);
         start_edit('j', "Enter log interval in seconds: ");
         return 0;
      }
      else if(first_key == 'm') { // MI command - invert pps and temperature scale factors
         if(luxor) return help_exit(c,99);
         if(plot[PPS].invert_plot < 1.0F) val = 1;
         else                             val = 0;
         val = toggle_value((u08) val);
         if(val) plot[PPS].invert_plot = (-1.0);
         else    plot[PPS].invert_plot = (1.0);

         if(plot[TEMP].invert_plot < 1.0F) val = 1;
         else                              val = 0;
         val = toggle_value((u08) val);
         if(val) plot[TEMP].invert_plot = (-1.0);
         else    plot[TEMP].invert_plot = (1.0);
      }
      else if(first_key == 'w') {  // WI command - inverted video plot image dump
         invert_video = 1;
         top_line = (MOUSE_ROW+2)*TEXT_HEIGHT;
         dump_image();
         return 0;
      }
      else if(first_key == 0) {
         edit_buffer[0] = 0;
         start_edit('i', "Enter the queue update interval in seconds: (ESC to abort):");
         return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'j') {
      if(first_key == '&') { // &J command - jam sync threshold
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_jam_sync);
         start_edit('6', "Enter jam sync threshold in ns (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'f') {  // FJ command - set jamming filter
         if(luxor) return help_exit(c,99);
         if     (foliage_mode == 0) strcpy(edit_buffer, "N");
         else if(foliage_mode == 2) strcpy(edit_buffer, "A");
         else                       strcpy(edit_buffer, "S");
         start_edit('o', "Jamming:  S)A   N)o");
         return 0;
      }
      else if(first_key == 'g') {  
         if(luxor) {               // GJ command - toggle LEDw plot
            edit_plot(TWELVE, c);
            return 0;
         }
         else {   // GJ command - toggle el mask in azel plot
            if(plot_azel == 0) plot_el_mask = 1;
            else               plot_el_mask = toggle_value(plot_el_mask);
            plot_azel = 1;
            update_azel = 1;
            goto do_azel;
         }
      }
      else if(first_key == 'j') {  // JJ command - jam sync
         if(luxor) return help_exit(c,99);
         set_discipline_mode(0);
         BEEP();
      }
      else if(first_key == 0) {   // J command first char - Jam sync
         if(luxor) return help_exit(c,99);
         if(are_you_sure(c) != c) return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'k') {  
      if(first_key == 'f') {  // FK command - toggle KALMAN filter
         if(luxor) return help_exit(c,99);
         kalman_filter = toggle_value(kalman_filter);
         set_filter_config(pv_filter, static_filter, alt_filter, kalman_filter, 1);
      }
      else if(first_key == 'g') {
         if(luxor) {               // GK command - toggle driver efficency plot
            edit_plot(THIRTEEN, c);
            return 0;
         }
         else {  // GK command - satellite constellation changes
            plot_const_changes = toggle_value(plot_const_changes);
            draw_plot(1);
         }
      }
      else if(first_key == 0) {
         edit_buffer[0] = 0;
         start_edit('k',  "Enter PID command:  T#msecs_fan,#msecs_heat  K)P_GAIN,D_TC,FIL_TC,I_TC   H)elp");
         return 0;
      }
      else return help_exit(c,3);
   }
   else if(c == 'l') { 
      if(first_key == '&') { 
         if(luxor) {  // &L command - lux sensor sensitivity
            sprintf(edit_buffer, "%.0f", (float) lux1_time);
            sprintf(out, "Lux sensor gain: L)ow=%d  M)edium=%d  H)high=%d  or enter gain (%d..%d) (ESC ESC to abort):", LOW_LUX,MED_LUX,HI_LUX, MIN_LUX,MAX_LUX); 
            start_edit(AMPL_CMD, out);
            return 0;
         }
         else {  // &L command - change min dac voltage
            sprintf(edit_buffer, "%f", user_min_range);
            start_edit('t', "Enter minimum DAC voltage range value (ESC ESC to abort):"); 
            return 0;
         }
      }
      else if(luxor && (first_key == 'b')) {  // BL command - lipo charge mode
         sprintf(edit_buffer, "%f", 0.1F);
         start_edit(BL_CMD, "Enter desired LIPO charge current in amps.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'c') {  // CL command - clear LLA fixes
         if(luxor) return help_exit(c,99);
         #ifdef BUFFER_LLA
            clear_lla_points();
            redraw_screen();
         #endif
      }
      else if(first_key == 'f') {  // FL command - signal level mask
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%.1f", amu_mask);
         if(res_t == 2) start_edit('m',  "Enter minimum acceptible signal level (in dBc)");
         else           start_edit('m',  "Enter minimum acceptible signal level (in AMU)");
         return 0;
      }
      else if(first_key == 'g') {
         if(luxor) {  // GL command - color temperature
            edit_plot(FOURTEEN, c);
            return 0;
         }
         else {  // GL command - hide locations
            plot_loc = toggle_value(plot_loc);
            redraw_screen();
         }
      }
      else if(luxor && (first_key == 'p')) {  // PL command = low voltage cutoff
         sprintf(edit_buffer, "%f", batt_lvc);
         start_edit(PL_CMD, "Enter the battery low voltage cutoff in volts.  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 's') {  // SL command - set lat/lon/alt
         if(luxor) return help_exit(c,99);
         if(check_precise_posn) {
            strcpy(edit_buffer, "Y");
            start_edit('L', "Lat/lon/alt search aborted! Save low resolution position? Y)es N)o");
         }
         else {
            sprintf(edit_buffer, "%.8lf %.8lf %.3lf", precise_lat*RAD_TO_DEG, precise_lon*RAD_TO_DEG, precise_alt);
            start_edit('l', "Enter precise lat lon alt (-=S,W +=N,E  alt in meters)  (ESC ESC to abort):");
         }
         return 0;
      }
      else if(first_key == 't') { // TL command - set log dump time
         if     (script_file) edit_buffer[0] = 0;
         else if(log_time && log_date) sprintf(edit_buffer, "%02d:%02d:%02d  %02d/%02d/%02d", log_hh,log_mm,log_ss, log_month,log_day,log_year); 
         else if(log_time) sprintf(edit_buffer, "%02d:%02d:%02d", log_hh,log_mm,log_ss);
         else if(log_date) sprintf(edit_buffer, "%02d/%02d/%02d", log_month,log_day,log_year);
         else if(log_val) {
            if((log_val >= (24L*3600L)) && ((log_val % 24L*3600L) == 0)) sprintf(edit_buffer, "%ld d", log_val/(24L*3600L));
            else if((log_val >= (3600L)) && ((log_val % 3600L) == 0)) sprintf(edit_buffer, "%ld h", log_val/(3600L));
            else if((log_val >= (60L)) && ((log_val % 60L) == 0)) sprintf(edit_buffer, "%ld m", log_val/(60L));
            else sprintf(edit_buffer, "%ld s", log_val);
         }
         else edit_buffer[0] = 0;
         if(edit_buffer[0]) start_edit('(', "Enter log dump time (and optional date) or interval or <ESC CR> to reset:");
         else               start_edit('(', "Enter log dump time (and optional date) or interval or <CR> to reset:");
         return 0;
      }
      else if(first_key == 'w') {  // WL command - write log
         first_key = 0;
         c = 'l';
         goto log_cmd;
      }
      else if(first_key == '$') {  // $l command - large screen
         new_screen(c);
         return 0;
      }
      else {    // L command - log stuff
         log_cmd:
         if(are_you_sure(c) != c) return 0;
         // the next keystroke will select the data to write
      }
   }
   else if(c == 'm') {  // toggle auto scaling of graphs
      if(luxor && (first_key == '&')) { // &m command - set medium sensitivity
         set_luxor_sens(69, 69);
      }
      else if(first_key == 'f') {  // FM command - movement dynamics
         if     (dynamics_code == 1) strcpy(edit_buffer, "L");
         else if(dynamics_code == 2) strcpy(edit_buffer, "S");
         else if(dynamics_code == 3) strcpy(edit_buffer, "A");
         else                        strcpy(edit_buffer, "F");
         start_edit('u',  "Receiver movement:  A)ir  F)ixed  L)and  S)ea");
         return 0;
      }
      else if(first_key == 'g') {  // GM command - plot satellite map
         if(luxor) return help_exit(c,99);
         plot_azel = toggle_value(plot_azel);
         do_azel:
         if(AZEL_OK == 0) plot_azel = AZEL_OK;
//       if((WIDE_SCREEN == 0) && ((shared_plot == 0) || all_adevs)) {
//          if(plot_signals) plot_watch = 0;  //!!!!!
//          if(plot_azel || plot_signals) plot_watch = 0;
////        else          plot_watch = 1;
//       }
         if(plot_azel || plot_signals) update_azel = 1;
         config_screen();
         redraw_screen();
      }
      #ifdef ADEV_STUFF
         else if(first_key == 'a') {  // AM command - set adev type to MDEV
            if(luxor) return help_exit(c,99);
            ATYPE = OSC_MDEV;
            all_adevs = 0;
            force_adev_redraw();
            config_screen();
            redraw_screen();
         }
      #endif
      else if(luxor && (first_key == 'p')) {  // PM command = message watchdog timer
         sprintf(edit_buffer, "%.3f", msg_timeout);
         start_edit(PM_CMD, "Enter the Message watchdog timeout in seconds (0=disable).  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == '$') {  // $m command - medium screen
         new_screen(c);
         return 0;
      }
      else if(luxor) {  // m command - battery pwm control (for now)
         strcpy(edit_buffer, mode_string);
         if(!isdigit(edit_buffer[1]) || (edit_buffer[0] == '.') || (edit_buffer[0] == 0)) {
            if(((edit_buffer[0] == '0') || (edit_buffer[0] == '.') || (edit_buffer[0] == 0)) && (batt_pwm == 0)) strcpy(edit_buffer, "1");
            else if(((edit_buffer[0] == '1') || (edit_buffer[0] == '.') || (edit_buffer[0] == 0)) && (batt_pwm != 0)) strcpy(edit_buffer, "0");
         }
         edit_info1 = "or enter * for double 100 msec mode change pulses";
         if(edit_buffer[0]) start_edit(DRVR_MODE, "Enter driver mode sequence: 0=OFF 1=ON  or  OFFmsecs [ONmsecs...]  (ESC ESC to abort):");
         else               start_edit(DRVR_MODE, "Enter driver mode sequence: 0=OFF 1=ON  or  OFFmsecs [ONmsecs...]  (ESC to abort):");
         return 0;
      }
      else return help_exit(c,4);
   }
   else if(c == 'n') {
      if(first_key == '&') { // &N command - change min voltage
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_min_volts);
         start_edit('4', "Enter minimum EFC control voltage (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == '$') {  // $n command - custom screen
         new_screen(c);
         return 0;
      }
      else return help_exit(c,5);
   }
   else if(c == 'o') {
      if(first_key == 'g') {  // GO command - toggle graph osc ppb data
         edit_plot(OSC, c);
         return 0;
      }
      #ifdef ADEV_STUFF
         else if(first_key == 'a') {  // AO command - graph all OSC adev types
            if(luxor) return help_exit(c,99);
            aa_val = 1;
            strcpy(edit_buffer, "G");
            start_edit('a', "Display:  A)devs only   G)raphs and all adevs   graphs and R)egular adevs");
            return 0;
         }
      #endif
      else if(luxor && (first_key == 'p')) {  // PO command = battery overcurrent
         sprintf(edit_buffer, "%f", load_ovc);
         start_edit(PO_CMD, "Enter the load overcurrent threshold in amps.  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 's') { // SO command - single sat mode
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%d", single_sat);
         start_edit('x', "Enter PRN of sat for single sat mode (0=highest sat)");
         return 0;
      }
      else if(first_key == '&') { // &O command - toggle osc polarity
         if(luxor) return help_exit(c,99);
         user_osc_polarity = toggle_value(user_osc_polarity);
         set_osc_sense(user_osc_polarity, 1);
      }
      else if(first_key == 0) {  // O command
//       if(luxor) return help_exit(c,99);
         strcpy(edit_buffer, "");
         start_edit(',',  "Enter option value (ESC ESC to abort):");
         return 0;
      }
      else return help_exit(c,6);
   }
   else {  // help mode
      return help_exit(c,7);
   }

   return sure_exit();
}

int kbd_other(int c)
{
long val;
int i;

   // process keyboard characters that are not a..o or cursor movement
   if(c == 'p') { 
      if(luxor && (first_key == 'b')) {  // BP command - PWM resolution
         sprintf(edit_buffer, "%d", batt_pwm_res);
         start_edit(BP_CMD, "Enter PWM resolution in bits (8/9/10).  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'c') {  // CP command - clear plot queue
//!!!!-  pause_data = 0;
         new_queue(2);
      }
      else if(first_key == 'f') {  // FP command - toggle PV filter
         if(luxor) return help_exit(c,99);
         pv_filter = toggle_value(pv_filter);
         set_filter_config(pv_filter, static_filter, alt_filter, kalman_filter, 1);
      }
      #ifdef ADEV_STUFF
         else if(first_key == 'a') {  // AP command - graph all PPS adev types
            if(luxor) return help_exit(c,99);
            aa_val = 2;
            strcpy(edit_buffer, "G");
            start_edit('a', "Display  A)devs only   G)raphs and all adevs   graphs and R)egular adevs");
            return 0;
         }
      #endif
      else if(first_key == 'g') {  // GP command toggle PPS plot
         edit_plot(PPS, c);
         return 0;
      }
      else if(luxor && (first_key == 'p')) {  // PW command = load high voltage cutoff
         sprintf(edit_buffer, "%f", load_watts);
         start_edit(PP_CMD, "Enter the LED power cutoff in watts.  (ESC ESC to abort):");
         return 0;
      }
      #ifdef PRECISE_STUFF
         else if(first_key == 's') { // SP command - precison survey
            if(luxor) return help_exit(c,99);
            redraw_screen();
            if(precision_survey) {   // abort precision survey
               strcpy(edit_buffer, "Y");
               start_edit('A', "Precise survey aborted! Save current position? Y)es N)o");
               return 0;
            }
            else {  // start precison survey
               strcpy(edit_buffer, "48");
               start_edit('^', "Enter number of hours to do survey for (1-60,  ESC ESC to abort) : ");
               return 0;
            }
         }
      #endif
      else if(first_key == 'w') {  // WP command - Write plot area data to a log file
         strcpy(edit_buffer, "DUMP.LOG");
         sprintf(out, "Enter name of log file to write %sPLOT area info to (ESC ESC to abort):",
                       filter_log?"filtered ":"");
         start_edit('w', out);
         log_mode = "w";
         dump_type = 'p';
         return 0;
      }
      else if(first_key == '&') {  // &P command - toggle PPS polarity
         if(luxor) return help_exit(c,99);
         pps_polarity = toggle_value(pps_polarity);
         user_pps_enable = 1;
         set_pps(user_pps_enable, pps_polarity,  delay_value,  300.0, 1);
      }
      else if(luxor && (first_key == 0)) { // P command - luxor protection values
         if(are_you_sure(c) != c) return 0; 
         // next call to do_kbd() will process the selection character
      }
      else return help_exit(c,8);
   }
   else if(c == 'r') { 
      if(first_key == 'g') { // GR command - redraw screen
         first_key = 0;
         if(luxor == 0) {
            debug_text[0] = 0;
            debug_text2[0] = 0;
         }
         reset_marks();
         osc_params = 0;
         redraw_screen();
         if(murray) {
            request_primary_timing();
            request_secondary_timing();
         }
      }
#ifdef ADEV_STUFF
      else if(first_key == 'c') {  // CR command - reload adev queue from screen data
         if(luxor) return help_exit(c,99);
         reload_adev_queue();
      }
#endif
      else if(luxor && (first_key == 'p')) {  // PR command = reset protection fault
         strcpy(edit_buffer, "r");
         start_edit(PR_CMD, "Enter R to reset the protection fault flags.  (ESC ESC to abort):");
         return 0;
      }
      else if(luxor && (first_key == 'b')) {  // BR command - sweep PWM rate
         sprintf(edit_buffer, "%d", sweep_rate);
         start_edit(BR_CMD, "Enter PWM sweep rate in seconds per step.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'w') {  // WR command - inverted video screen dump
         invert_video = 1;
         top_line = 0;
         dump_image();
         return 0;
      }
      else if(first_key == 0) {  // R command read in a log file
         edit_buffer[0] = 0;
         if(luxor) {
            start_edit('r', "Enter name of .LOG .CAL .CFG .WAV or .SCRipt file to read (ESC to abort):");
         }
         else {
            start_edit('r', "Enter name of .LOG .ADV .LLA .SIG .CAL .CFG .WAV .TIM or .SCRipt file to read (ESC to abort):");
         }
         return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 's') { 
      if(luxor && (first_key == 'b')) {  // BS command - sweep PWM value
         sprintf(edit_buffer, "%f %f", 0.0F, 1.0F);
         start_edit(BS_CMD, "Enter PWM sweep starting and ending PWM values.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'c') {  // CS command - clear signal level data
         if(luxor) return help_exit(c,99);
         #ifdef SIG_LEVELS
            clear_signals();
            redraw_screen();
         #endif
      }
      else if(first_key == 'd') { // DS command - disable osc discipline and set DAC voltage
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", dac_voltage);
         start_edit('c', "Enter DAC control voltage (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 'f') {  // FS command - toggle STATIC filter
         if(luxor) return help_exit(c,99);
         static_filter = toggle_value(static_filter);
         set_filter_config(pv_filter, static_filter, alt_filter, kalman_filter, 1);
      }
      else if(first_key == 'g') { // GS command - toggle sound
         beep_on = toggle_value(beep_on);
         BEEP();
         draw_plot(1);
      }
      else if(first_key == 'l') {  // LS command - stop logging
         if(log_file) close_log_file();
         else edit_error("Log file is not open.");
      }
      else if(first_key == 's') {  // SS command - standard survey
         if(luxor) return help_exit(c,99);
         if(doing_survey) {         // survey in progress,  stop self survey
            stop_self_survey();     // stop any self survey
            redraw_screen();
         }
         else {
            if(do_survey) sprintf(edit_buffer, "%ld", do_survey);
            else          sprintf(edit_buffer, "%ld", SURVEY_SIZE);
            start_edit('s', "Enter number of samples for standard self survey (ESC ESC to abort):");
            return 0;
         }
      }
      else if(luxor && (first_key == 'p')) {  // PS command - temp2 over temperature
         sprintf(edit_buffer, "%f", tc2_ovt);
         start_edit(PS_CMD, "Enter temp sensor 2 over-temperature cutoff (degrees C).  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 't') {  // TS command - set system time to receiver time
         set_system_time = toggle_value(set_system_time);
         if(set_system_time) need_time_set();
      }
      else if(first_key == 'w') {  // WS command - Dump screen to .GIF/.BMP file
         invert_video = 0;
         top_line = 0;
         dump_image();
         return 0;
      }
      else if(first_key == '&') { 
         if(luxor) {   // &s command - set unit serial number
            sprintf(edit_buffer, "%.4f", vref_b);
            start_edit(AMPS_CMD, "Enter the unit serial number (#.####). (ESC ESC to abort):");
            return 0;
         }
         else {   // &s command - toggle PPS signal
            user_pps_enable = pps_enabled ^ 1;
            set_pps(user_pps_enable, pps_polarity,  delay_value,  300.0, 1);
         }
      }
      else if(first_key == '$') {  // $s command - small screen
         new_screen(c);
         return 0;
      }
      else if((first_key == 0) && luxor) {
         sprintf(edit_buffer, "%f %f %f", lat*RAD_TO_DEG, lon*RAD_TO_DEG, alt);
         start_edit(S_CMD, "Enter lat lon alt: (+ for N and E,  - for S and W,  alt in meters) (ESC ESC to abort)");
         return 0;
      }
      else {  // S command - survey menu
         if(are_you_sure(c) != c) return 0;  
         // next call to do_kbd() will process the selection character
      }
   }
   else if(c == 't') { 
      if(first_key == 'g') {   // GT command - temperature graph
         edit_plot(TEMP, c);
         return 0;
      }
      #ifdef ADEV_STUFF
        else if(first_key == 'a') {  // AT command - set adev type to TDEV
           if(luxor) return help_exit(c,99);
           ATYPE = OSC_TDEV;
           all_adevs = 0;
           force_adev_redraw();
           config_screen();
           redraw_screen();
        }
      #endif
      #ifdef TEMP_CONTROL
         else if(first_key == 't') {  // TT command - active temperature control
            sprintf(edit_buffer, "%.3f", desired_temp);
            sprintf(out, "Enter desired operating temperature in %cC: (0=OFF  ESC ESC to abort)", DEGREES);
            start_edit('*', out);
            return 0;
         }
      #endif
      else if(luxor && (first_key == 'p')) {  // PT command - temp1 over temperature
         sprintf(edit_buffer, "%f", tc1_ovt);
         start_edit(PT_CMD, "Enter temp sensor 1 over-temperature cutoff (degrees C).  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == '$') {  // $t command - text mode screen
         new_screen(c);
         return 0;
      }
      else if(first_key == '&') { // &T command - change time constant
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_time_constant);
         start_edit('1', "Enter oscillator time constant in seconds (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == '!') {    // !t command - reset TSIP parser
         tsip_sync = 0;
         tsip_wptr = 0;
         tsip_rptr = 0;
         init_messages();
         redraw_screen();
      }
      else { // T command - time menu, select UTC or GPS time etc.
         if(are_you_sure(c) != c) return 0; 
         // next call to do_kbd() will process the selection character
      }
   }
   else if(c == 'u') {  // Updates or UTC time
      if(first_key == 'g') {  // GU command - constant graph updates
         continuous_scroll = toggle_value(continuous_scroll);
         config_screen();
         redraw_screen();
      }
      else if(luxor && (first_key == 'p')) {  // PU command - led under voltage cutoff
         sprintf(edit_buffer, "%f", load_lvc);
         start_edit(PU_CMD, "Enter LED under-voltage cutoff (in volts).  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 'u') {  // UU command - toggle updates
         pause_data = toggle_value(pause_data);
         if(pause_data == 0) {
            end_review(0);
         }
         redraw_screen();
      }
      else if(first_key == 't') {   // TU command - time UTC
//       time_zone_set = 0;
         if(luxor) return help_exit(c,99);
         temp_utc_mode = 0;
         set_timing_mode(0x03);
         request_timing_mode();
      }
      else if(first_key == '$') {  // $u command - very small screen
         new_screen(c);
         return 0;
      }
      else if(first_key == '&') {  // &U command - lumen sensor sensitivity
         if(luxor) {  
            sprintf(edit_buffer, "%.0f", (float) lux2_time);
            sprintf(out, "Lumen sensor gain: L)ow=%d  M)edium=%d  H)high=%d  or enter gain (%d..%d) (ESC ESC to abort):", LOW_LUX,MED_LUX,HI_LUX, MIN_LUX,MAX_LUX); 
            start_edit(AMPU_CMD, out);
            return 0;
         }
         else return help_exit(c,99);
      }
      else if(first_key == 0) {  // U command first char - toggle updates
         if(are_you_sure(c) != c) return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'v') {  // set plot View time
      if(first_key == '$') {  // $v command - very large screen
         new_screen(c);
         return 0;
      }
      else if(luxor && (first_key == '&')) {  // &v command - reference voltage
         sprintf(edit_buffer, "%.4f", vref_m);
         start_edit(AMPV_CMD, "Enter the unit reference voltage (4.5 .. 6.5) (ESC ESC to abort):");
         return 0;
      }
      else if(luxor && (first_key == 'b')) {  // BV command - contsant load voltage mode
         sprintf(edit_buffer, "%f", 0.1F);
         start_edit(BV_CMD, "Enter desired load voltage in volts.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(luxor && (first_key == 'p')) {  // PV command = load high voltage cutoff
         sprintf(edit_buffer, "%f", load_hvc);
         start_edit(PV_CMD, "Enter the load high voltage cutoff in volts.  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 0) {   // v command - view time
         if(view_interval == 1) {
            val = PLOT_WIDTH / HORIZ_MAJOR;
            if(val) val = (((plot_q_count+59)/60)+val-1) / val;
            else    val = 20;
//          val /= HORIZ_MAJOR;
            if(val <= 0) val = 1;
            sprintf(edit_buffer, "%ld", val);
//          sprintf(edit_buffer, "20");
            edit_info1 = "or enter a time interval to display (like 20m, 3h, 2d)";
            start_edit('v', "Enter the plot view time in minutes/division: (A=all,  T=auto,  ESC ESC to abort):");
         }
         else {
            strcpy(edit_buffer, "0");
            edit_info1 = "or enter a time interval to display (like 20m, 3h, 2d)";
            start_edit('v', "Enter the plot view time in minutes/division: (0=normal,  A=all,  T=auto):");
         }
         return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == 'w') {  
      if(first_key == '!')  { // !W command - warm reset and self test
         request_warm_reset();
         redraw_screen();
      }
      else if(luxor && (first_key == 'b')) {  // BW command - contsant load wattage mode
         sprintf(edit_buffer, "%f", 0.1F);
         start_edit(BW_CMD, "Enter desired load power in watts.  (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == 'g') {  // GW command - draw watch
         plot_watch = toggle_value(plot_watch);
         if((WIDE_SCREEN == 0) && ((shared_plot == 0) || all_adevs)) {
//          if(plot_watch) plot_signals = 0;
//          if(plot_watch) plot_azel = plot_signals = 0;
////        else           plot_azel = AZEL_OK;
         }
         config_screen();
         redraw_screen();
      }
      else if(first_key == 'l') {  // LW command - open log in write mode
         if(log_file) edit_error("Log file is already open.");
         else {
            log_mode = "w";
            strcpy(edit_buffer, log_name);
            start_edit('n', "Enter log file name to write data to: ");
            return 0;
         }
      }
      else if(luxor && (first_key == 'p')) {  // PW command = battery power cutoff
         sprintf(edit_buffer, "%f", batt_watts);
         start_edit(PW_CMD, "Enter the battery power cutoff in watts.  (ESC ESC to abort):");
         return 0;
      }
      else {  // W command - write file menu
         if(are_you_sure(c) != c) return 0;
         // the next keystroke will select the data to write
      }
   }
   else if(c == 'x') {   // toggle view_interval between minutes and hours
      if(first_key == 'f') {  // FX command - PDOP mask/switch
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%.1f", pdop_mask);
         start_edit('p', "Enter PDOP mask value (switch 2D/3D mode at mask*0.75)");
         return 0;
      }
      else if(luxor && (first_key == 'p')) {  // PX command - auxv over voltage cutoff
         sprintf(edit_buffer, "%f", auxv_hvc);
         start_edit(PX_CMD, "Enter AUXV over-voltage cutoff (in volts).  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 't') { // TX command - set exit time
         if(end_time && end_date) sprintf(edit_buffer, "%02d:%02d:%02d  %02d/%02d/%02d", end_hh,end_mm,end_ss, end_month,end_day,end_year); 
         else if(end_time) sprintf(edit_buffer, "%02d:%02d:%02d", end_hh,end_mm,end_ss);
         else if(end_date) sprintf(edit_buffer, "%02d/%02d/%02d", end_month,end_day,end_year);
         else if(exit_val) {  // exit countdown timer set
            if((exit_val >= (24L*3600L)) && ((exit_val % 24L*3600L) == 0)) sprintf(edit_buffer, "%ld d", exit_val/(24L*3600L));
            else if((exit_val >= (3600L)) && ((exit_val % 3600L) == 0)) sprintf(edit_buffer, "%ld h", exit_val/(3600L));
            else if((exit_val >= (60L)) && ((exit_val % 60L) == 0)) sprintf(edit_buffer, "%ld m", exit_val/(60L));
            else sprintf(edit_buffer, "%ld s", exit_val);
         }
         else edit_buffer[0] = 0;
         if(edit_buffer[0]) start_edit('/', "Enter exit time (and optional date) or interval or <ESC CR> to reset:");
         else               start_edit('/', "Enter exit time (and optional date) or interval or <CR> to reset:");
         return 0;
      }
      else if(first_key == '&') { // &X command - change max voltage
         if(luxor) return help_exit(c,99);
         sprintf(edit_buffer, "%f", user_max_volts);
         start_edit('5', "Enter maximum EFC control voltage (ESC ESC to abort):"); 
         return 0;
      }
      else if(first_key == '$') {  // $x command - extra large screen
         new_screen(c);
         return 0;
      }
      else if(first_key == 'g') { // GX command - show dops
         if(luxor) return help_exit(c,99);
         plot_dops = toggle_value(plot_dops);
         if(plot_dops) request_sat_list();
         redraw_screen();
      }
      else if(first_key == 0) {  // X command - 1 hr/division
         new_view();
      }
      else return help_exit(c,99);
   }
   else if(c == 'y') {   // toggle view_interval and set plot area to 24 (or 12) divisions
      if(first_key == ESC_CHAR) {  // ESC y command - exit program
         kbd_exit();
         return 1;  // ESC = exit
      }
      else if(first_key == 0) {  // Y command - set day plot mode
         if(day_plot) { day_plot = 0; view_interval = 2L;}
         else {
            day_plot = day_size;
            if     (SCREEN_WIDTH > 1280) day_plot = 26;
            else if(SCREEN_WIDTH > 1024) day_plot = 26;
            else if(SCREEN_WIDTH > 800)  day_plot = 25;
            else                         day_plot = 26;
         }
         config_screen();
         new_view();
      }
      else return help_exit(c,99);
   }
   else if(c == 'z') {  // toggle floating graph zero for dac and temp
      if(first_key == 'g') {  // GZ command - show big time
         plot_digital_clock = toggle_value(plot_digital_clock);
         if(ebolt) {  // adjust ebolt sat count for time clock display
            last_ebolt = 2;
            saw_ebolt();
         }
         config_screen();
         redraw_screen();
      }
      else if(luxor && (first_key == 'p')) {  // PZ command = load high voltage cutoff
         sprintf(edit_buffer, "%f", auxv_lvc);
         start_edit(PZ_CMD, "Enter the AUXV low voltage cutoff in volts.  (ESC ESC to abort):");
         return 0;
      }
      else if(first_key == 't') {  // TZ command - select time zone
         if(time_zone_set) {
            if     (time_zone_seconds) sprintf(edit_buffer, "%d:%02d:%02d%s", time_zone_hours, IABS(time_zone_minutes), IABS(time_zone_seconds),std_string);
            else if(time_zone_minutes) sprintf(edit_buffer, "%d:%02d%s", time_zone_hours, IABS(time_zone_minutes), std_string);
            else                       sprintf(edit_buffer, "%d%s", time_zone_hours, std_string);
            if(dst_string[0]) {
               strcat(edit_buffer, "/");
               strcat(edit_buffer, dst_string);
            }
            start_edit('Z', "Enter time zone string (like -6:00CST/CDT)  ESC CR to reset  ESC ESC to abort:");
         }
         else {
            edit_buffer[0] = 0;
            start_edit('Z', "Enter time zone string (like -6:00CST/CDT)  ESC to abort:");
         }
         return 0;
      }
      else if(first_key == 'w') {  // WZ command - Output az/el signal level file
         if(luxor) return help_exit(c,99);
         strcpy(edit_buffer, "TBOLT.SIG");
         sprintf(out, "Enter name of file to write AZ/EL info to (ESC ESC to abort):");
         start_edit('%', out);
         return 0;
      }
      else if(first_key == '$') {  // $z command - Oprah sized screen
         new_screen(c);
         return 0;
      }
      else if(first_key == 0) {  // z command - zoom screen
         if(1 || plot_azel || plot_watch || plot_signals || plot_digital_clock) {
            zoom_screen ^= 1;
         }
         else zoom_screen = 0;
         if(zoom_screen == 0) zoom_lla = 0;
         first_key = 0;
         config_screen();
         redraw_screen();
      }
      else return help_exit(c,9);
   }
   else if(c == '}') {  // } command - grow plot
      if(first_key == 0) {
         grow_plot();
         draw_plot(1);
      }
      else return help_exit(c,99);
   }
   else if(c == '{') {  // } command - shrink plot
      if(first_key == 0) {
         shrink_plot();
         draw_plot(1);
      }
      else return help_exit(c,99);
   }
   else if(c == '+') {  // + command 
      if(first_key == 0) {
         if(last_was_mark) {  // clear numeric marker
            last_was_mark = 0;
            val = last_q_place;
            // center point on screen
            val -= ((((long)PLOT_WIDTH/2L)*view_interval)/(long)plot_mag);
            if(last_q_place < plot_q_out) val += plot_q_size;
            zoom_review(val, 1);
            draw_plot(1);
         }
         else {
            move_plot_up();
            draw_plot(1);
         }
      }
      else if(first_key == 'g') {  // g+ command - turn on all plots
         for(i=NUM_PLOTS+DERIVED_PLOTS-1; i>=0; i--) {
            if(plot[i].show_plot == 0) toggle_plot(i);
         }
         plot_adev_data = 1;
         plot_sat_count = 1;
      }
      else return help_exit(c,99);
   }
   else if(c == '-') {  // - command
      if(first_key == 0) {
         if(last_was_mark) {  // clear numeric marker
            mark_q_entry[last_was_mark-'0'] = 0;
            last_was_mark = 0;
            draw_plot(1);
         }
         else {
            move_plot_down();
            draw_plot(1);
         }
      }
      else if(first_key == 'g') {   // g- command - hide all plots
         for(i=NUM_PLOTS+DERIVED_PLOTS-1; i>=0; i--) {
            if(plot[i].show_plot) toggle_plot(i);
         }
         plot_adev_data = 0;
         plot_sat_count = 0;
      }
      else return help_exit(c,99);
   }
   else if(c == '=') { // = command - assign next unused marker
      if(first_key == 0) {
         if(set_next_marker()) return sure_exit();
      }
      else return help_exit(c,99);
   }
   else if(c == '!') {  // ! command - reset unit
      if(are_you_sure(c) != c) return 0;
      // the next keystroke will select the reset type
   }
   else if(c == '&') {  // & command - edit osc param
      if(luxor) {
         if(first_key == 'w') { // W& command - write luxor cal data script file
            strcpy(edit_buffer, "LUXCAL.SCR");
            start_edit('w', "Enter name of calibration data script file to write (ESC ESC to abort):");
            dump_type = 'c';
            return 0;
         }
         if(are_you_sure(c) != c) return 0; 
         else                     return sure_exit();
      }

      if(osc_params == 1) osc_params = 0; 
      else                osc_params = 1;   // replace sat info table with osc parameter display
      redraw_screen();
      if(are_you_sure(c) != c) {
         user_time_constant = time_constant; 
         user_damping_factor = damping_factor;
         user_osc_gain = osc_gain;
         user_min_volts = min_volts;
         user_max_volts = max_volts;
         user_min_range = min_dac_v;
         user_max_range = max_dac_v;
         user_jam_sync = jam_sync;
         user_max_freq_offset = max_freq_offset;
         user_initial_voltage = initial_voltage;
         if(process_com == 0) {
            show_satinfo();
         }
         return 0;
      }
      else if(process_com == 0) {
         show_satinfo();
      }
      else {
//----   osc_params = 0;
      }
      redraw_screen();
   }
   else if(c == '/') {  
      if(first_key == 'g') { // G/ command - set statistic for all plots
         all_plots = 1;
         edit_buffer[0] = 0;
         edit_info1 =    "                             mi)N   ma)X   sP)an";
         start_edit('~', "Enter statistic to display:  A)vg   R)ms   S)td dev   V)ar   <cr>=hide");
         return 0;
      }
      else if(first_key == 0) {
         no_auto_erase = 1;
#ifdef USE_X11
         strcpy(edit_buffer, "-");
#else
         strcpy(edit_buffer, "/");
#endif
         start_edit('-', "Enter command line option to process (ESC ESC) to abort:");
         return 0;
      }
      else return help_exit(c,99);
   }
   else if(c == '\\') {   // \ command - dump screen image
      if(first_key == 0) {
         if(luxor) dump_screen(invert_video, 0, "LUXOR");
         else      dump_screen(invert_video, 0, "TBOLT");
      }
      else return help_exit(c,99);
   }
   else if(c == '$') {   // $ command - set screen size
      if(are_you_sure(c) != c) return 0;
      // the next char will select the screen size
   }
   else if(c == '%') {   // % command - goto next holdover/error event
      if(first_key == 0) {
         val = 0;
         if(plot_skip_data)     val |= TIME_SKIP;
         if(plot_holdover_data) val |= HOLDOVER;
         if(plot_temp_spikes)   val |= TEMP_SPIKE;
         if(val == 0)           val |= (HOLDOVER | TIME_SKIP | TEMP_SPIKE);
         goto_event((int) val);
      }
      else return help_exit(c,99);
   }
   else if((c == ';') || (c == '#')) {   // ; command or # command - script file text comment to end of line
      if(script_file) skip_comment = 1;
      else return help_exit(c,10);
   }
   else if((c >= '0') && (c <= '9')) {
      if((first_key == '&') && (c == '1')) {  // &1 command - set 1pps mode
         if(luxor) return help_exit(c,99);
         set_pps_mode(0x02);
         request_pps_mode();
         if(res_t) save_segment(0xFF);
      }
      else if((first_key == '&') && (c == '2')) {  // &2 command - set 2pps mode
         if(luxor) return help_exit(c,99);
         set_pps_mode(0x82);
         request_pps_mode();
         if(res_t) save_segment(0xFF);
      }
      else if(first_key == 'g') {  // G1 .. G9 commands - select auxiliary plots
         if(c == '0') val = FIRST_EXTRA_PLOT + 10 - 1;
         else         val = FIRST_EXTRA_PLOT + (c-'0') - 1;
         if((val == 0) || (val >= NUM_PLOTS+DERIVED_PLOTS)) {
            sprintf(out, "Plot %c is not supported", c);
            edit_error(out);
         }
         else {
            edit_plot((int) val, c);
            return 0;
         }
      }
      #ifdef PRECISE_STUFF
         else if(first_key == 's') {
            if(luxor) return help_exit(c,99);
            if     (c == '2') do_fixes(3);     // S2 command - 2D fixes
            else if(c == '3') do_fixes(4);     // S3 command - 3D mode
            else if(c == '4') do_fixes(2);     // S4 command - undocumented mode 2
            else              do_fixes(c-'0'); // S# command - set receiver mode to #
         }
      #endif
      else return help_exit(c,99);
   }
   else if(c == '?') {
      keyboard_cmd = 1;
      command_help("", "", help_path);
      keyboard_cmd = 0;
   }
   else {  // help mode
      return help_exit(c,11);
   }

   return sure_exit();
}

int do_kbd(int c)
{
   // This routine processes a keystroke character.
   //
   // If variable "first_key" is set, this key stroke is the second keystroke
   // of the two character command that started with character "first_key".

   if(sound_alarm) {    // any keystroke turns off alarm clock
      sound_alarm = 0;  
      #ifdef DIGITAL_CLOCK
         reset_vstring();
      #endif
   }

   if(disable_kbd > 1) return 0;  // nothing gets by

   if(zoom_screen && (first_key == 0)) {  // any keystroke restores zoomed screen
      if((c != 'z') && (c != '\\')) {     // unless it is one of these keys
         zoom_screen = 0;
         zoom_lla = 0;
         config_screen();
         redraw_screen();
      }
   }

   if(disable_kbd) {         // most of the keyboard is disabled
      last_was_mark = 0;
      if((first_key == 0) && (c != ESC_CHAR)) return 0;
      if((c >= 0x0100) || (c == '[') || (c == ']')) {  // cursor movement keys, etc
         c = 0;
         do_review(c);       // stop review
         return sure_exit(); // prevents spurious scroll mode header
      }
   }

   if(getting_string) { // we are currently building a parameter value string
      last_was_mark = 0;
      return build_string(c);  // add the keystroke to the line
   }
   else if(getting_plot) {  // we are in the plot control sub-menu
      if(change_plot_param(c)) return 0;
   }
   else if((c >= 0x0100) || (c == '<') || (c == '>') || (c == '[') || (c == ']') || (c == '@')) {  
      // cursor movement keys, etc
      // @ command - zoom to marked queue entry (invoked from mouse click or keyboard)
      last_was_mark = 0;
      if((first_key == 0) && (text_mode == 0)) {
         if(c == '@') goto_mark(0);  // center plot on marked place 
         else         do_review(c);  // scrolling around in the plot data
      }
      else {
         if(c >= 0x0100) cmd_error(0);  //!!!!
         else            cmd_error(c);
      }
   }
   else if(c == ESC_CHAR) {  // ESC key exits program or aborts key sequence
      last_was_mark = 0;
      if(review_mode && (pause_data == 0)) {
         c = 0;
         do_review(c);  // stop review
      }
      else if(first_key == ESC_CHAR) {
         if(esc_esc_exit) {  // allow ESC ESC to end the program
            kbd_exit();
            return 1;
         }
      }
      else {
         if(are_you_sure(c) != c) return 0;
      }
   }
   else if((first_key == 0) && (c >= '0') && (c <= '9')) {  // plot markers
      kbd_marker(c);
   }
   else {  // normal keystroke command
      if(c < 0x0100) c = tolower(c);
      if((c != '-') && (c != '+')) last_was_mark = 0;

      // break up the keyboard processing big 'if' statement 
      // into two parts so the compiler heap does not overflow
      if((c >= 'a') && (c <= 'o')) c = kbd_a_to_o(c);
      else                         c = kbd_other(c);
      return c;
   }

   return sure_exit();
}

//
// 
//  Command line processor
//
//
void save_cmd_bytes(char *arg)
{
u16 val;
char c;
int i;
u08 saw_digit;

   val = 0x00;
   saw_digit = 0;
   for(i=1; i<=(int)strlen(arg); i++) {
      c = toupper(arg[i]);
      if((c >= '0') && (c <= '9')) {  // build hex value
         val = (val * 16) + (c-'0');
         saw_digit = 1;
         continue;
      }
      else if((c >= 'A') && (c <= 'F')) {  // build hex value
         val = (val * 16) + (c-'A'+10);
         saw_digit = 1;
         continue;
      }
      else if(saw_digit) {  // end of hex value
         if(arg[0] == '=') {  // add byte to list of bytes to send during tbolt init
            if(user_init_len < USER_CMD_LEN) {
               user_init_cmd[user_init_len++] = (u08) val;
            }
         }
         else if(arg[0] == '$') {  // add byte to list of bytes to send every second
            if(user_pps_len < USER_CMD_LEN) {
               user_pps_cmd[user_pps_len++] = (u08) val;
            }
         }

         val = 0x00;     // setup for next hex value
         saw_digit = 0;
      }

      if(c == ',') continue;   // values can be separated by spaces or commas
      else if(c == ' ') continue;
      else break;  // anything else ends the list of hex values
   }
}

u08 toggle_option(u08 val, u08 sw)
{
   if     ((sw == '1') || (sw == 'y')) return 1;
   else if((sw == '0') || (sw == 'n')) return 0;
   else return (val & 1) ^ 1;
}


void set_watch_name(char *s)
{
unsigned i, j;
int n;
char c;

   plot_watch = 1;
   config_screen();
   n = 0;
   j = 0;
   watch_name[j] = watch_name2[j] = 0;
   for(i=0; i<strlen(s); i++) {
      c = s[i];   
      if(c == 0) break;
      if(c == '/') {
         ++n;
         j = 0;
         continue;
      }

      if(c == '_') c = ' ';
      if(n == 0) {
         watch_name[j++] = c;
         watch_name[j] = 0;
         if(j >= (sizeof(watch_name)-1)) break;
      }
      else if(n == 1) {
         watch_name2[j++] = c;
         watch_name2[j] = 0;
         if(j >= (sizeof(watch_name2)-1)) break;
      }
   }
}


int cmd_a_to_o(char *arg) 
{
char c, d, e;
float scale_factor;
float val;
int i;

   d = e = 0;
   c = tolower(arg[1]);
   if(c) d = tolower(arg[2]);
   if(d) e = tolower(arg[3]);

#ifdef ADEV_STUFF
   if(c == 'a') {
      not_safe = 1;
//    not_safe = 2;
//    if(keyboard_cmd) return 0;
      if(arg[2] && arg[3]) {  // get adev queue size
         sscanf(&arg[3], "%ld", &adev_q_size);                           
      }
      else {     // default adev queue sizes
         #ifdef DOS
            #ifdef DOS_EXTENDER
               adev_q_size = (330000L);      // good for 100000 tau
            #else
               if(ems_ok) adev_q_size = (33000L);    // good for 10000 tau
               else       adev_q_size = (22000L);    // good for 5000-10000 tau
            #endif
         #else
            adev_q_size = (330000L);      // good for 100000 tau
         #endif
      }

      if(adev_q_size <= 0) {
          adev_q_size = 1L;
          adev_period = 0.0F;
      }
      if(adev_q_size >= 50000000L) adev_q_size = 50000000L;
      user_set_adev_size = 1;

      if(keyboard_cmd) {   // we are resizing the queue
         alloc_adev();
         reset_queues(0x01);
      }
   }
   else if(c == 'b') {    // set daylight savings time mode
#else 
   if(c == 'b') {         // set daylight savings time mode 
#endif
      if(d == 'r') {  // /br - set baud rate
         if((e == '=') || (e == ':')) {
            sscanf(&arg[4], "%d", &baud_rate);
            if(baud_rate <= 0) baud_rate = 38400;
         }
         else baud_rate = 38400;
      }
      else if(d == 's') {  // adjust times for the solar equation-of-time
         solar_time = toggle_option(solar_time, e);
         if(user_set_watch_name == 0) {
            if(solar_time) set_watch_name("Solar");
            else           watch_name[0] = 0;
            label_watch_face = 1;
         }
      }
      else if(((d == '=') || (d == ':')) && e) {  //  /B# or /B=#  or /B=nth,start_day,month,nth,end_day,month,hour
         if(strstr(&arg[3], ",")) {  // custom daylight savings time settings
            strcpy(custom_dst, &arg[3]);
            dst_area = 5;
            user_set_dst = 1;
            not_safe = 1;
            if(keyboard_cmd) calc_dst_times(dst_list[dst_area]);
         }
         else if((e >= '0') && (e <= '5')) {  // standard dst area set
            dst_area = e - '0';
            user_set_dst = 1;
            not_safe = 1;
            if(keyboard_cmd) calc_dst_times(dst_list[dst_area]);
         }
         else return c;
      }
      else if((d >= '0') && (d <= '5')) {  // standard dst area set
         dst_area = d - '0';
         user_set_dst = 1;
         not_safe = 1;
         if(keyboard_cmd) calc_dst_times(dst_list[dst_area]);
      }
      else return c;
   }
   else if(c == 'c') {    // cable delay
      ++user_set_delay;                  
      not_safe = 1;
      if(d == 'g') {       // cg - use green color channel for lux readings
         alt_lux1 = 0.0F;
         if((e == '=') || (e == ':')) {
            sscanf(&arg[4], "%f", &alt_lux1);
         }
      }
      else if(d == 'h') {  // /ch - set raw color readings mode to Hz
         show_color_hz = 1;
         show_color_uw = 0;
         show_color_pct= 0;
         config_luxor_plots();
      }
      else if(d == 'p') {  // /cp - set raw color readings mode in percent
         show_color_hz = 0;
         show_color_uw = 0;
         show_color_pct= 1;
         config_luxor_plots();
      }
      else if(d == 'r') {  // /cr - alternate CRI energy calcs
         cri_flag ^= 1;
      }
      else if(d == 't') {  // /ct - set cct scale factor
         if((e == '=') || (e == ':')) {
            sscanf(&arg[4], "%f", &cct_cal);
            if(cct_cal <= 0.0F) cct_cal = 1.0F;
         }
         else if(e == '1') {
            if((arg[4] == '=') || (arg[4] == ':')) {
               cct1_cal = (float) atof(&arg[5]);                           
               if(cct1_cal <= 0.0F) cct1_cal = 1.0F;
            }
            else cct_type = 1;
         }
         else if(e == '2') {
            if((arg[4] == '=') || (arg[4] == ':')) {
               cct2_cal = (float) atof(&arg[5]);                           
               if(cct2_cal <= 0.0F) cct2_cal = 1.0F;
            }
            else cct_type = 2;
         }
         else cct_type = 0;
         set_cct_id();
      }
      else if(d == 'u') {  // /cu - set raw color readings mode in uw/cm^2
         show_color_hz = 0;
         show_color_uw = 1;
         show_color_pct= 0;
         config_luxor_plots();
      }
      else {
         if(arg[2] && arg[3]) {
            val = (float) atof(&arg[3]);                           
            strupr(arg);
            if(strstr(&arg[3], "F") || strstr(&arg[3], "'")) {  // cable delay in feet
               val = val * (1.0F / (186254.0F * 5280.0F)) / 0.66F;  // 50 feet of 0.66 vp coax
            }
            else if(strstr(&arg[3], "M")) { // cable delay in meters
               val *= 3.28084F;
               val = val * (1.0F / (186254.0F * 5280.0F)) / 0.66F;  // 50 feet of 0.66 vp coax
            }
            else {
               val /= 1.0E9;
            }
            delay_value = (double) val;
         }
      }
   }
#ifdef GREET_STUFF
   else if(c == 'd') {   // dates (select calendar)
      if     (d == 'a') alt_calendar = AFGHAN;
      else if(d == 'b') alt_calendar = HAAB;        // Mayan 365 day cycle
      else if(d == 'c') alt_calendar = CHINESE;    
      else if(d == 'd') alt_calendar = DRUID;       // pseudo-Druid calendar
      else if(d == 'e') show_debug_info = toggle_option(show_debug_info, d);
else if(d == 'f') {
   tcs_color = toggle_option(tcs_color, d);
   if(tcs_color) {
      BLUE_SENS  = 1.0F; 
      GREEN_SENS = 1.0F; 
      RED_SENS   = 1.0F; 
      WHITE_SENS = ((RED_SENS+BLUE_SENS+GREEN_SENS)/3.0F);
   }
   else {
      BLUE_SENS  = 123.94F;    // 371.0F  // converts Hz to uW/cm^2
      GREEN_SENS = 144.80F;    // 386.0F
      RED_SENS   = 177.74F;    // 474.0F
      WHITE_SENS = ((RED_SENS+BLUE_SENS+GREEN_SENS)/3.0F);
   }
}
      else if(d == 'g') alt_calendar = GREGORIAN;
      else if(d == 'h') alt_calendar = HEBREW;
      else if(d == 'i') alt_calendar = ISLAMIC;
      else if(d == 'j') alt_calendar = JULIAN;
      else if(d == 'k') alt_calendar = KURDISH;
      else if(d == 'm') alt_calendar = MJD;
      else if(d == 'n') alt_calendar = INDIAN;
      else if(d == 'p') alt_calendar = PERSIAN;
      else if(d == 's') alt_calendar = ISO;
      else if(d == 't') alt_calendar = TZOLKIN;     // Mayan 260 day cycle
      else if(d == 'x') alt_calendar = AZTEC_HAAB;  // Aztec 365 day cycle
      else if(d == 'y') alt_calendar = MAYAN;       // Mayan long count
      else if(d == 'z') alt_calendar = AZTEC;       // Aztec 260 day cycle
      else if(isdigit(d)) {   // force date for calendar testing
         sscanf(&arg[2], "%d%c%d%c%d", &force_day,&c,&force_month,&c,&force_year);
         if(keyboard_cmd) {
            pri_year = force_year;
            pri_month = force_month;
            pri_day = force_day;
            new_moon_info = 1;
            calc_greetings();  // calculate seasonal holidays and insert into table
            show_greetings();  // display any current greeting
         }
      }
      else if(d == 0) alt_calendar = GREGORIAN;
      else return c;

      if((e == '=') || (e == ':')) {  // calendar epoch adjustments
         if(arg[4]) {
            if     (alt_calendar == CHINESE)    sscanf(&arg[4], "%ld", &chinese_epoch);
            else if(alt_calendar == DRUID)      sscanf(&arg[4], "%ld", &druid_epoch);
            else if(alt_calendar == MAYAN)      sscanf(&arg[4], "%ld", &mayan_correlation);
            else if(alt_calendar == HAAB)       sscanf(&arg[4], "%ld", &mayan_correlation);
            else if(alt_calendar == TZOLKIN)    sscanf(&arg[4], "%ld", &mayan_correlation);
            else if(alt_calendar == AZTEC)      sscanf(&arg[4], "%ld", &aztec_epoch);
            else if(alt_calendar == AZTEC_HAAB) sscanf(&arg[4], "%ld", &aztec_epoch);
            else {
               sscanf(&arg[4], "%lf", &rollover);
               user_set_rollover = 1;
            }
         }
      }
   }
#endif
   else if(c == 'e') {   // log errors
      log_errors = toggle_option(log_errors, d);                           
   }
#ifdef WINDOWS
   else if (c == 'f') {  
      if(d) {  // toggle filter
         for(i=3; d; i++) {
            if     (d == 'p') user_pv ^= 1;      // !!!!! toggle_option
            else if(d == 's') user_static ^= 1;
            else if(d == 'a') user_alt ^= 1;
            else if(d == 'k') user_kalman ^= 1;
            else return d;
            d = tolower(arg[i]);
            if(d) e = tolower(arg[i+1]);
            else  e = 0;
         }
      }
      else {   // start up in full screen mode
         not_safe = 1;
//       initial_window_mode = VFX_FULLSCREEN_MODE;
         initial_window_mode = VFX_TRY_FULLSCREEN;
      }
   }
#endif
#ifdef USE_X11
   else if (c == 'f') {  
      if(d) {  // toggle filter
         for(i=3; d; i++) {
            if     (d == 'p') user_pv ^= 1;      // !!!!! toggle_option
            else if(d == 's') user_static ^= 1;
            else if(d == 'a') user_alt ^= 1;
            else if(d == 'k') user_kalman ^= 1;
            else return d;
            d = tolower(arg[i]);
            if(d) e = tolower(arg[i+1]);
            else  e = 0;
         }
      }
   }
#endif
#ifdef DOS
   else if (c == 'f') {  // toggle ems memory enable
      if(d) {
         for(i=3; d; i++) {
            if     (d == 'p') user_pv ^= 1;       // !!!!! toggle_option
            else if(d == 's') user_static ^= 1;
            else if(d == 'a') user_alt ^= 1;
            else if(d == 'k') user_kalman ^= 1;
            else return d;
            d = tolower(arg[i]);
            if(d) e = tolower(arg[i+1]);
            else  e = 0;
         }
      }
      else {
         not_safe = 2;
         if(keyboard_cmd) return 0;
         if(ems_ok) ems_ok = 0;
         else ems_ok = 1;
      }
   }
#endif
   else if(c == 'g') {   // toggle Graph enables
      for(i=3; d; i++) {
         if     (d == 'a') { plot_adev_data = toggle_option(plot_adev_data, e); user_set_adev_plot = 1; }
         else if(d == 'b') { plot_azel = AZEL_OK;  shared_plot = 1; if(plot_azel) update_azel = 1; }
         else if(d == 'c') { plot_sat_count = toggle_option(plot_sat_count, e); }
         else if(d == 'd') { plot[DAC].show_plot = toggle_option(plot[DAC].show_plot, e); user_set_dac_plot = 1; }
         else if(d == 'e') { plot_skip_data = toggle_option(plot_skip_data, e); }
         else if(d == 'h') { plot_holdover_data = toggle_option(plot_holdover_data, e); }
         else if(d == 'j') { plot_el_mask = toggle_option(plot_el_mask, e); }
         else if(d == 'k') { plot_const_changes = toggle_option(plot_const_changes, e); }
         else if(d == 'l') { plot_loc = toggle_option(plot_loc, e); }
         else if(d == 'm') { plot_azel = AZEL_OK;  shared_plot = 0; if(plot_azel) update_azel = 1; }
         else if(d == 'n') { no_greetings = toggle_option(no_greetings, e); }
         else if(d == 'o') { plot[OSC].show_plot = toggle_option(plot[OSC].show_plot, e); user_set_osc_plot = 1; } 
         else if(d == 'p') { plot[PPS].show_plot = toggle_option(plot[PPS].show_plot, e); user_set_pps_plot = 1; } 
         else if(d == 'q') { if(plot_signals) plot_signals = 0; else plot_signals = 4; user_set_signals = 1; } 
         else if(d == 'r') { plot_stat_info = toggle_option(plot_stat_info, e); }
         else if(d == 's') { beep_on = toggle_option(beep_on, e); }
         else if(d == 't') { plot[TEMP].show_plot = toggle_option(plot[TEMP].show_plot, e); }
         else if(d == 'u') { continuous_scroll = toggle_option(continuous_scroll, e); }
         else if(d == 'w') { plot_watch = toggle_option(plot_watch, e); user_set_bigtime = 1; plot_digital_clock = 0; user_set_watch_plot = 1; }
         else if(d == 'x') { plot_dops = toggle_option(plot_dops, e); }
         else if(d == 'z') { plot_digital_clock = toggle_option(plot_digital_clock, e); user_set_bigtime = 1;  plot_watch = 0; user_set_clock_plot = 1; }
//       else if(d == '/') plot_stat_info = toggle_option(plot_stat_info, e);
         else if(d == ',') ;
         else if(d == '1') ;
         else if(d == '0') ;
         else if(d == 'y') ;
//       else if(d == 'n') ;
         else if(d == 0x0A) break;
         else if(d == 0x0D) break;
         else return d;
         d = tolower(arg[i]);
         if(d) e = tolower(arg[i+1]);
         else e = 0;
      }
   }
   else if(c == 'h') {
      if(((d == '=') || (d == ':')) && arg[3]) read_config_file(&arg[3], 0, 0);
   }
   else if(c == 'i') {   
      if((d == '0') || (d == 'o')) {  // do not process any received TSIP commands
         just_read = toggle_option(just_read, e);
      }
#ifdef USE_X11  // !!!! __linux__
      else if(d == 'd') {  // /id - set input device name
         com_port = 0;
         usb_port = 9999;
         process_com = 1;
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            strncpy(com_dev, &arg[4], sizeof(com_dev));  
         }
         else {
            strncpy(com_dev, "/dev/heather", sizeof(com_dev));  
         }
         if(com_running) {
            init_com();
         }
      }
#endif
#ifdef TCP_IP            // TCP: com_port 0 with process_com 1 means use TCP/IP connection rather than COM port 
      else if(d == 'p') {
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            com_port = usb_port = 0;
            process_com = 1;
            strncpy(IP_addr, &arg[4], sizeof(IP_addr));  
         }
         if(com_running && IP_addr[0]) {
            com_port = usb_port = 0;
            process_com = 1;
            init_com();
         }
      }
#endif 
      else if(d == 'r') {  // block TSIP commands that change the unit's state
         read_only = toggle_option(read_only, e);
      }
      else if(d == 's') {  // do not send data out the serial port
         no_send = toggle_option(no_send, e);
      }
      else {               // set plot queue update interval  
         if(arg[2] && arg[3]) {
            sscanf(&arg[3], "%ld", &queue_interval);                           
            if(queue_interval < 1) queue_interval = 0;
         }
         else {
            day_plot = 24;
            interval_set = 1;
         }
      }
   }
#ifdef ADEV_STUFF
   else if(c == 'j') {   // adev sample interval (not adev info display interval)
      if(d == 'p') {    // JPL wall clock mode
         jpl_clock = toggle_option(jpl_clock, e);
         if(jpl_clock) {
            zoom_screen = 1;
            alt_calendar = ISO;
         }
      }
      else {
         not_safe = 1;
         if(arg[2] && arg[3]) {
            sscanf(&arg[3], "%f", &adev_period);                           
            if(adev_period < 1.0F) adev_period = 0.0F;
         }
         else if(adev_period == 1.0F) adev_period = 10.0F;
         else adev_period = 1.0F;
         if(keyboard_cmd) {
            reset_queues(0x01);
         }
      }
   }
#endif
   else if(c == 'k') {  // disable keyboard commands
      if     (d == 'b') beep_on = toggle_option(beep_on, e);  // kb - disable beeper
      else if(d == 'c') no_eeprom_writes = toggle_option(no_eeprom_writes, e);  // kc - disable config eeprom writes
//    else if(d == 'c') com_error_exit = toggle_option(com_error_exit, e);  // kc - enable exit on com port error
      else if(d == 'e') esc_esc_exit = toggle_option(esc_esc_exit, e); // ke - allow ESC ESC to exit program
//    else if(d == 'k') kbd_flag = d; // kk - locks out kbd during mouse update
      else if(d == 'm') mouse_disabled = toggle_option(mouse_disabled, e);  // km - disable mouse
      else if(d == 't') enable_timer = toggle_option(enable_timer, e);
      else if(d) {
         #ifdef TEMP_CONTROL
            if(edit_pid_value(&arg[2], 0)) return c;
         #endif
      }
      else ++disable_kbd;
   }
   else if(c == 'l') {  // log write interval
      if(d == 'c') {       // /lc - toggle comments in the log flag
         log_comments = toggle_option(log_comments, e);
      }
      else if(d == 'd') {  // /ld - toggle constellation/signal level data flag
         log_db = toggle_option(log_db, e);
      }
      else if(luxor && (d == 'f')) {  // /lf - show lux in footcandles
         if((e == '=') || (e == ':')) sscanf(&arg[4], "%f", &lux_scale);
         else lux_scale = 1.0F / 10.76391F;
         show_lux = 0;
         show_fc = 1;
         config_luxor_plots();
         return 0;
      }
      else if(d == 'h') {  // /lh - toggle timestamp headers in the log
         log_header = toggle_option(log_header, e);
      }
      else if(d == 'o') {  // /lo command - read old format log files
         old_log_format = toggle_option(old_log_format, e);
      }
      else if(luxor && (d == 'p')) {  // /lp - show lumens in candlepower
         if((e == '=') || (e == ':')) sscanf(&arg[4], "%f", &lum_scale);
         else lum_scale = 1.0F/(4.0F*(float)PI);
         show_lumens = 0;
         show_cp = 1;
         config_luxor_plots();
         return 0;
      }
      else if(d == 's') {  // /ls - log file value separator
         if(csv_char == ',') csv_char = '\t';
         else                csv_char = ',';
      }
      else if((d == 'u') && (e == 'x')) {  // /lux - force luxor mode
         luxor = toggle_option(luxor, e);
      }
      else if(luxor && (d == 'u')) {  // /lu - show lumens in lumens
         if((e == '=') || (e == ':')) sscanf(&arg[4], "%f", &lum_scale);
         else lum_scale = 1.0F;
         show_lumens = 1;
         show_cp = 0;
         config_luxor_plots();
         return 0;
      }
      else if(luxor && (d == 'x')) {  // /lx - show lux in lux
         if((e == '=') || (e == ':')) sscanf(&arg[4], "%f", &lux_scale);
         else lux_scale = 1.0F;
         show_lux = 1;
         show_fc = 0;
         config_luxor_plots();
         return 0;
      }
      else {
         if(arg[2] && arg[3]) {
            sscanf(&arg[3], "%ld", &log_interval);                           
            if(log_interval < 1) log_interval = 0 - log_interval;
            log_file_time = log_interval+1;
         }
         user_set_log = 1;
      }
   }
   else if(c == 'm') {     // multiply or set default plot scale factors
      if(d == 'a') {
         auto_scale = toggle_option(auto_scale, e);  // turn off auto scaling
         auto_center = auto_scale;
      }
      else if(d == 'd') {  // /md  - set dac scale factor
         plot[DAC].user_scale = 1;
         scale_factor = plot[DAC].scale_factor * 2.0F;
         plot[DAC].invert_plot = 1.0;
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            sscanf(&arg[4], "%f", &scale_factor);                           
            if(scale_factor <= 0.0) scale_factor *= (-1.0);
            if(strstr(&arg[4], "-")) plot[DAC].invert_plot = (-1.0);
         }
         plot[DAC].scale_factor = scale_factor;
      }
      else if(d == 'i') {  // /mi - Invert PPS and termperature plot scale factors
         if(plot[PPS].invert_plot < 1.0F) plot[PPS].invert_plot = 1.0F;
         else                             plot[PPS].invert_plot = (-1.0F);
         if(plot[TEMP].invert_plot < 1.0F) plot[TEMP].invert_plot = 1.0F;
         else                              plot[TEMP].invert_plot = (-1.0F);
      }
      else if(d == 'p') {  // /mp - pps error scale factor
         plot[PPS].user_scale = 1;
         plot[PPS].invert_plot = 1.0;
         scale_factor = (float) plot[PPS].scale_factor * 2.0F;
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            sscanf(&arg[4], "%f", &scale_factor);                           
            if(scale_factor <= 0.0) scale_factor *= (-1.0);
            if(strstr(&arg[4], "-")) plot[PPS].invert_plot = (-1.0);
         }
         plot[PPS].scale_factor = (OFS_SIZE) scale_factor;
      }
      else if(d == 'o') {  // /mo - osc error scale factor
         plot[OSC].user_scale = 1;
         plot[OSC].invert_plot = 1.0;
         scale_factor = (float) plot[OSC].scale_factor * 2.0F;
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            sscanf(&arg[4], "%f", &scale_factor);                           
            if(scale_factor <= 0.0) scale_factor *= (-1.0);
            if(strstr(&arg[4], "-")) plot[OSC].invert_plot = (-1.0);
         }
         plot[OSC].scale_factor = (OFS_SIZE) scale_factor;
      }
      else if(d == 't') {  // /mt - temperature scale factor
         plot[TEMP].user_scale = 1;
         scale_factor = plot[TEMP].scale_factor * 2.0F;
         plot[TEMP].invert_plot = 1.0;
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            sscanf(&arg[4], "%f", &scale_factor);                           
            if(scale_factor <= 0.0) scale_factor *= (-1.0);
            if(strstr(&arg[4], "-")) plot[TEMP].invert_plot = (-1.0);
         }
         plot[TEMP].scale_factor = scale_factor;
      }
      else if((d >= '0') && (d <= '9')) {  // the extra plots
         if(d == '0') d = 10;
         else         d = d - '0' - 1;
         d += FIRST_EXTRA_PLOT;
         plot[d].user_scale = 1;
         scale_factor = plot[d].scale_factor * 2.0F;
         plot[d].invert_plot = 1.0;
         if(arg[4] && ((arg[3] == '=') || (arg[3] == ':'))) {
            sscanf(&arg[4], "%f", &scale_factor);                           
            if(scale_factor <= 0.0) scale_factor *= (-1.0);
            if(strstr(&arg[4], "-")) plot[TEMP].invert_plot = (-1.0);
         }
         plot[d].scale_factor = scale_factor;
      }
      else if(d) return c;
      else {   // multiply all scale plot factors
         scale_factor = 2.0;
         if(arg[2] && arg[3]) {  // /m=
            sscanf(&arg[3], "%f", &scale_factor);                           
         }
         
         plot[TEMP].user_scale    = plot[OSC].user_scale = plot[DAC].user_scale = plot[PPS].user_scale = 1;
         plot[OSC].scale_factor  *= scale_factor;
         plot[PPS].scale_factor  *= scale_factor;
         plot[DAC].scale_factor  *= scale_factor;
         plot[TEMP].scale_factor *= scale_factor;
      }
   }
   else if(c == 'n') {  // set end time
      if(d == 'a') {
        getting_string = ':';  //  /na=alarm time
        edit_dt(&arg[4], 0);
        getting_string = 0;
      }
      else if(d == 'd') {
        getting_string = '!';  //  /nd=screen dump interval
        edit_dt(&arg[4], 0);
        getting_string = 0;
      }
      else if(d == 'l') {
        getting_string = '(';  //  /nl=log dump interval
        edit_dt(&arg[4], 0);
        getting_string = 0;
      }
      else if(d == 't') {      // /nt - try to wake up Nortel NTGxxxx unit
         ++nortel;
      }
      else if(d == 'x') {
        getting_string = '/';  //  /nx=exit time
        edit_dt(&arg[4], 0);
        getting_string = 0;
      }
      else if(d) return c;
      else {
        getting_string = '/';  //  /n=exit time
        edit_dt(&arg[3], 0);
        getting_string = 0;
      }
   }
#ifdef ADEV_STUFF
   else if(c == 'o') {   // set adev type
      if     (d == 'a') { ATYPE = OSC_ADEV; all_adevs = 0; }
      else if(d == 'h') { ATYPE = OSC_HDEV; all_adevs = 0; } 
      else if(d == 'm') { ATYPE = OSC_MDEV; all_adevs = 0; } 
      else if(d == 't') { ATYPE = OSC_TDEV; all_adevs = 0; } 
      else if(d == 'o') all_adevs = 1;
      else if(d == 'p') all_adevs = 2;
      else return c;
   }
#endif
   else return c;

   return 0;
}

int cmd_other(char *arg)
{
char c, d, e;
float scale_factor;
int i;

   d = e = 0;
   c = tolower(arg[1]);
   if(c) d = tolower(arg[2]);
   if(d) e = tolower(arg[3]);

   if(c == 'p') {     // toggle signal PPS enable
      if(d == 'o'){  // /po=lat,lon,alt
         if(((e == '=') || (e == ':')) && arg[4]) {
            sscanf(&arg[4], "%lf%c%lf%c%lf", &lat,&d,&lon,&d,&alt);
            lat /= RAD_TO_DEG;
            lon /= RAD_TO_DEG;   // !!!! should range check these numbers
            precise_lat = lat;
            precise_lon = lon;
            precise_alt = alt;
         }
         else return 0;
      }
      else {
         not_safe = 1;
         ++set_pps_polarity;
         user_pps_enable = toggle_option(user_pps_enable, d);
      }
   }
   else if(c == 'q') {    
      if(d == 'f')  {  // set max fft size
#ifdef FFT_STUFF
//       not_safe = 2;
//       if(keyboard_cmd) return 0;
         not_safe = 1;
         if(e == '=')      max_fft_len = (long) atof(&arg[4]);
         else if(e == ':') max_fft_len = (long) atof(&arg[4]);
         else if(e)        max_fft_len = (long) atof(&arg[3]);
         else              max_fft_len = 4096;
         if(max_fft_len < 0) max_fft_len = 0 - max_fft_len;
         max_fft_len = (1 << logg2(max_fft_len));
         if(keyboard_cmd) {  // we are resizing the FFT queue
            alloc_fft();
         }
#endif
      }
      else {  // set plot queue size
//       not_safe = 2;
//       if(keyboard_cmd) return 0;
         not_safe = 1;
         if(arg[2] && arg[3]) {  // get plot queue size
            sscanf(&arg[3], "%ld", &plot_q_size);                           
            strupr(&arg[3]);
            if     (strstr(&arg[3], "W")) plot_q_size *= 3600L*24L*7L;
            else if(strstr(&arg[3], "D")) plot_q_size *= 3600L*24L;
            else if(strstr(&arg[3], "H")) plot_q_size *= 3600L;
            else if(strstr(&arg[3], "M")) plot_q_size *= 60L;
         }
         else {     // default plot queue sizes
            #ifdef DOS
               #ifdef DOS_EXTENDER
                  plot_q_size = 3600L*7L*24L; // 7 days 'o data
               #else
                  if(ems_ok) plot_q_size = 3600L*7L*24L; // 7 days 'o data
                  else       plot_q_size = 3600L*2L;     // wimpy 2 hours 'o data
               #endif
            #else
               plot_q_size = 3600L*24L*30L;   // boost plot queue to 30 days 'o data
            #endif
         }

         if(plot_q_size <= 10L) plot_q_size = 10L;
         if(plot_q_size >= (366L*24L*3600L)) plot_q_size = (366L*24L*3600L);  // 1 year max
         user_set_plot_size = 1;
         if(keyboard_cmd) {  // we are resizing the queue
            alloc_plot();
            reset_queues(0x02);
         }
      }
   }
   else if(c == 'r') {    // Read a log file into the plot and adev queues
      if(d == 'o') {      // /ro - set gps date/time rollover adjustment in seconds
         user_set_rollover = 1;
         if(((e == '=') || (e == ':')) && arg[4]) rollover = atof(&arg[4]);
         else                                     rollover = 1024.0 * 7.0 * 24.0 * 60.0 * 60.0;
      }
      else if(d == 't') {      // Resolution-T receiver... use 9600,ODD,1
         res_t_init = toggle_option(res_t_init, e);
      }
      else {
         if(arg[2] && arg[3]) {
            strcpy(read_log, &arg[3]);
         }
         else strcpy(read_log, log_name);
//       strupr(read_log);
      }
   }
   else if((c == 's') && (d == 's')) {   // force site position survey
      user_precision_survey = 0;
      do_survey = SURVEY_SIZE;
      if(arg[3] && arg[4]) sscanf(&arg[4], "%ld", &do_survey);                           
      if(do_survey < 1)  do_survey = 0;
   }
#ifdef PRECISE_STUFF
   else if((c == 's') && (d == 'p')) {   // force precision survey
      not_safe = 1;
      user_precision_survey = 1;
      do_survey = 0;
      if(arg[3]) sscanf(&arg[4], "%ld", &do_survey);                           
      if((do_survey < 1) || (do_survey > SURVEY_BIN_COUNT)) do_survey = 0;
   }
   else if((c == 's') && (d == 'f')) {   // force 3D fix mode
      show_fixes = toggle_option(show_fixes, e);
      if(show_fixes) user_precision_survey = 2;
      else           user_precision_survey = 0;
      do_survey = 0;
      user_precision_survey = 0;
   }
#endif
   else if(c == 't') {   // set Time reference (GPS/UTC) or temp reference (C/F)
      if(arg[3] && ((d == '=') || (d == ':') || (d == 'z'))) {  // t=zoneinfo or /tz=zoneinfo
         set_time_zone(&arg[3]);
         if(keyboard_cmd) calc_dst_times(dst_list[dst_area]);
         return 0;
      }
      else if((d == '+') || (d == '-') || isdigit(d)) {
         set_time_zone(&arg[2]);
         if(keyboard_cmd) calc_dst_times(dst_list[dst_area]);
         return 0;
      }
      else if(d == 'b') {  // set watch brand name
         if((e == '=') || (e == ':')) {
            if(arg[4]) set_watch_name(&arg[4]);
            else       watch_name[0] = 0;
            label_watch_face = 1;
            user_set_watch_name = 1;
         }
         else {
            label_watch_face = toggle_option(label_watch_face, e);
         }
         return 0;
      }
      else if(d == 'h') {  // /th[=#] - set chime mode
         strupr(arg);
         cuckoo_hours = singing_clock = 0;
         if(strstr(&arg[3], "H")) cuckoo_hours  = 1;
         if(strstr(&arg[3], "S")) singing_clock = 1;
         if(((e == '=') || (e == ':')) && (arg[4])) {
            scale_factor = (float) atof(&arg[4]);
            if(scale_factor < 0.0F) scale_factor = 0.0F - scale_factor;
            if(scale_factor > 60.0F) scale_factor = 4.0F;
            cuckoo = (u08) scale_factor;
         }
         return 0;
      }
      else if(d == 'j') {  // /tj - remove the smoothing the tbolt firmware does to the temperature sensor readings
         undo_fw_temp_filter = toggle_option(undo_fw_temp_filter, e);
         user_set_temp_filter = 1;
         return 0;
      }
      else if(d == 'p') {  // /tp - show time as fractions of the day
         fraction_time = toggle_option(fraction_time, e);
         seconds_time  = 0;
         return 0;
      }
      else if(d == 'q') {  // /tq - show time as seconds of the day
         seconds_time = toggle_option(seconds_time, e);
         fraction_time = 0;
         return 0;
      }
      else if(d == 's') {   // set system time
         set_system_time = toggle_option(set_system_time, e);
         if(set_system_time) need_time_set();
         force_utc_time = 1;
         set_time_daily = set_time_hourly = set_time_minutely = 0;
         set_time_anytime = 0L;
         if((e == 'h') || (e == 'd') || (e == 'a')) {  // hourly or daily or anytime millisecond is not 0
            if(set_system_time) {
               if     (e == 'd') set_time_daily = 1;
               else if(e == 'h') set_time_hourly = 1;
               else if(e == 'm') set_time_minutely = 1;
               else if(e == 'a') { // /tsa[=#msecs_drift_before_correcting
                  set_time_anytime = 1;
                  if(((arg[4] == '=') || (arg[4] == ':')) && arg[5]) {
                     sscanf(&arg[5], "%ld", &set_time_anytime);
                  }
               }
            }
         }
         else if(e == 'x') {
            time_sync_offset = 45L;
            if(((arg[4] == '=') || (arg[4] == ':')) && arg[5]) {
               sscanf(&arg[5], "%ld", &time_sync_offset);
            }
         }
         else if(e == 'o') ;  // set time once
         else if(strstr(arg, "g")) force_utc_time = 0;  // set to gps time
         else if(strstr(arg, "G")) force_utc_time = 0;  // set to gps time
         else if(e) return c;
         return 0;
      }
#ifdef TEMP_CONTROL
      else if(d == 't') {  // set control temperature
         do_temp_control = 1;
         if(((e == '=') || (e == ':')) && arg[4]) {
            desired_temp = (float) atof(&arg[4]);
            if(desired_temp == 0.0F) ;
            else if(desired_temp > 50.0F) desired_temp = 40.0F;
            else if(desired_temp < 10.0F) desired_temp = 20.0F;
         }
         if(keyboard_cmd) {
            if(desired_temp) enable_temp_control();
            else             disable_temp_control();
         }
         return 0;
      }
#endif
      else if(d == 'w') {  // /tw[=#] - Windows idle sleep time
         if(e == '=')      idle_sleep = (long) atof(&arg[4]);
         else if(e == ':') idle_sleep = (long) atof(&arg[4]);
         else if(e)        idle_sleep = (long) atof(&arg[3]);
         else              idle_sleep = DEFAULT_SLEEP;
         if(idle_sleep < 0) idle_sleep = 0 - idle_sleep;
         return 0;
      }
      else if(d == 'y') {   // round temperatures
         user_set_rounding = 1;
         if(e == '=')      round_temp = atoi(&arg[4]);
         else if(e == ':') round_temp = atoi(&arg[4]);
         else if(luxor)    round_temp = 3;
         else              round_temp = 3;
         return 0;
      }

      for(i=3; d; i++) {  // misc simple /t options
         if(d == 'a') {        // european date ordering
            show_euro_dates = toggle_option(show_euro_dates, e);
         }
         else if(d == 'c') {   // use degrees C
            DEG_SCALE = 'C';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'd') {   // use degrees Delisle
            DEG_SCALE = 'D';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'e') {   // use degrees Reaumur
            DEG_SCALE = 'E';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'f') {   // use degrees F
            DEG_SCALE = 'F';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'g') {   // use GPS time
            ++set_gps_mode;                  
            set_utc_mode = 0;
         }
         else if(d == 'k') {   // use degrees K
            DEG_SCALE = 'K';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'm') {   // use meters
            alt_scale = "m";
            LLA_SPAN = 15.0;
            ANGLE_SCALE = (2.74e-6*3.28); // degrees per meter
            angle_units = "m";
         }
         else if(d == 'n') {   // use degrees Newton
            DEG_SCALE = 'N';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'o') {   // use degrees Romer
            DEG_SCALE = 'O';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'r') {   // use degrees R
            DEG_SCALE = 'R';
            plot[TEMP].plot_center = NEED_CENTER;
            if(luxor) plot[TC2].plot_center = NEED_CENTER;
         }
         else if(d == 'u') {   // use UTC time
            ++set_utc_mode;                  
            set_gps_mode = 0;
         }
         else if(d == 'x') {   // use exponents on osc data
            show_euro_ppt = toggle_option(show_euro_ppt, e);
            set_osc_units();
         }
         else if(d == '*') {   // monitor power line freq
            monitor_pl = toggle_option(monitor_pl, e);
         }
         else if(d == '\'') {   // use feet
            alt_scale = "ft";
            LLA_SPAN = 50.0;        // lla plot scale in feet each side of center
            ANGLE_SCALE = 2.74e-6;  // degrees per foot
            angle_units = "ft";
         }
         else if(d == '"') {   // use d.m.s format for lat/lon
            dms = toggle_option(dms, e);
         }
         else if(d == ',') ;
         else if(d == '1') ;
         else if(d == '0') ;
         else if(d == 0x0A) break;
         else if(d == 0x0D) break;
         else return c;
         d = tolower(arg[i]);
         if(d) e = tolower(arg[i+1]);
         else e = 0;
      }
   }
   else if(c == 'u') {  // set osc disciplining params or toggle queue Update mode
      if(d == 'd') {   // damping
         user_set_osc |= 0x02;
         if(((e == '=') || (e == ':')) && arg[4]) cmd_damp = (float) atof(&arg[4]);
         else                     cmd_damp = 1.000F;
      }
      else if(d == 'g') {   // gain
         user_set_osc |= 0x04;
         if(((e == '=') || (e == ':')) && arg[4]) cmd_gain = (float) atof(&arg[4]);
         else                     cmd_gain = 1.400F;
      }
      else if(d == 'i') {   // initial dac volts
         user_set_osc |= 0x08;
         if(((e == '=') || (e == ':')) && arg[4]) cmd_dac = (float) atof(&arg[4]);
         else                     cmd_dac = 3.000F;
         initial_voltage = cmd_dac;
      }
      else if(d == 'n') {   // min dac volts
         user_set_osc |= 0x10;
         if(((e == '=') || (e == ':')) && arg[4]) cmd_minv = (float) atof(&arg[4]);
         else                     cmd_minv = 0.000F;
      }
      else if(d == 't') {   // time constant
         user_set_osc |= 0x01;
         if(((e == '=') || (e == ':')) && arg[4]) cmd_tc = (float) atof(&arg[4]);
         else                     cmd_tc = 500.0F;
      }
      else if(d == 'x') {   // max dac volts
         user_set_osc |= 0x20;
         if(((e == '=') || (e == ':')) && arg[4]) cmd_maxv = (float) atof(&arg[4]);
         else                     cmd_maxv = 5.000F;
      }
      else if(d == 0) {
         user_pause_data = toggle_option(user_pause_data, d);
         pause_data = user_pause_data;
      }
      else return c;
   }
   else if(c == 'v') {   // video screen size - Small,  Medium,  Large,  Xtra large, Huge
      not_safe = 1;
      screen_type = d;
      need_screen_init = 1;
      user_font_size = 0;

      if(arg[3] == ':') user_font_size = 12;
      if(arg[3] && arg[4]) {
         strupr(arg);
         if     (strstr(&arg[4], "S")) user_font_size = 12;
         else if(strstr(&arg[4], "N")) user_font_size = 12;
         else if(strstr(&arg[4], "M")) user_font_size = 14;
         else if(strstr(&arg[4], "L")) user_font_size = 16;
         else if(strstr(&arg[4], "T")) user_font_size = 8;
      }

      if(adjust_screen_options()) {
         screen_type = 'm';
         adjust_screen_options();
         return c;
      }

      if(arg[2] && arg[3] && arg[4]) {  // get video mode to use
         if(screen_type == 'c') {       // custom screen size
            custom_width = 1024;
            custom_height = 768;
            sscanf(&arg[4], "%d%c%d", &custom_width, &c, &custom_height);
         }
         else {                         // standard screen size
            sscanf(&arg[4], "%u", &user_video_mode);                     
            text_mode = 0;
            if(screen_type == 't') {
               text_mode = user_video_mode;
               if(text_mode == 0) text_mode = 2;
            }
         }
      }
   }
   else if(c == 'w') {   // name of log file to write
      not_safe = 1;
      if((d == 'w') || (d == 'l')) {  //  /ww=file or /wl=file
         log_mode = "w";
         if(e && arg[4]) strcpy(log_name, &arg[4]);
      }
      else if(d == 'a') { //  /wa=file
         log_mode = "a";
         if(e && arg[4]) strcpy(log_name, &arg[4]);
      }
      else if(arg[2] && arg[3]) { //  /w=file
         log_mode = "w";
         if(d) strcpy(log_name, &arg[3]);
      }
      user_set_log = 1;
   }
   else if(c == 'x') {    // set display filter count (was mouse disable)
      filter_count = 10;
      plot[PPS].invert_plot = plot[TEMP].invert_plot = 1.0;
      if(arg[2] && arg[3]) {  // set filter count
         if(strstr(&arg[3], "-")) plot[PPS].invert_plot = plot[TEMP].invert_plot = (-1.0); 
         sscanf(&arg[3], "%ld", &filter_count);                        
         if(filter_count < 0) filter_count = 0 - filter_count;
      }
   }
   else if(c == 'y') {
      not_safe = 1;
      if(arg[2] && arg[3]) {  // get show interval
         strncpy(user_view_string, &arg[3], 32);
         user_view = 0;
         set_view = 0;
      }
      else {     // set plot window for 12 or 24 hours 
         if(day_plot == 24) day_plot = 12; 
         else day_plot = 24; 
         day_size = day_plot;
         user_view = day_plot;
         new_user_view = 1;
         ++set_view;
      }
   }
   else if(c == 'z') {  // allow graphs to recenter each time the plot is redrawn
      if(d && ((arg[3] == '=') || (arg[3] == ':')) && arg[4]) {  // /zd=3 - set fixed center value for dac plot
         scale_factor = (float) atof(&arg[4]);
         if     (d == 'd') { plot[DAC].float_center  = 0;  plot[DAC].plot_center  = scale_factor; user_set_dac_float = 1; }
         else if(d == 'o') { plot[OSC].float_center  = 0;  plot[OSC].plot_center  = scale_factor/1000.0F; user_set_osc_float = 1; } 
         else if(d == 'p') { plot[PPS].float_center  = 0;  plot[PPS].plot_center  = scale_factor; user_set_pps_float = 1; } 
         else if(d == 't') { plot[TEMP].float_center = 0;  plot[TEMP].plot_center = scale_factor; } 
         else if((d >= '0') && (d <= '9')) { // !!!!!! luxor
            if(d == '0') d = 10;
            else         d = d - '0' - 1;
            d += FIRST_EXTRA_PLOT;
            plot[d].float_center = 0;
            plot[d].plot_center = scale_factor;
         }
         else return c;
      }
      else if(d) {  // /zd /zpt  - toggle graph floating reference mode
         for(i=3; d; i++) {
            if(d == 'a') {
               auto_scale = toggle_option(auto_scale, e);  // turn off auto scaling
               auto_center = auto_scale;
            }
            else if(d == 'd') plot[DAC].float_center  = toggle_option(plot[DAC].float_center, e);
            else if(d == 'o') plot[OSC].float_center  = toggle_option(plot[OSC].float_center, e); 
            else if(d == 'p') plot[PPS].float_center  = toggle_option(plot[PPS].float_center, e); 
            else if(d == 't') plot[TEMP].float_center = toggle_option(plot[TEMP].float_center, e); 
            else if(d == ',') ;
            else if(d == '1') ;
            else if(d == 'y') ;
            else if(d == '0') ;
            else if(d == 'n') ;
            else if(d == 0x0A) break;
            else if(d == 0x0D) break;
            else return c;
            d = tolower(arg[i]);
            if(d) e = tolower(arg[i+1]);
            else e = 0;
         }
      }
      else {  // just /z - toggle dac and temp floating reference mode
         plot[TEMP].float_center = toggle_option(plot[TEMP].float_center, d); 
         plot[DAC].float_center = toggle_option(plot[TEMP].float_center, d); 
      }
   }
   else if(c == '+') {  // positive PPS polarity
      not_safe = 1;
      ++set_pps_polarity;                  
      user_pps_polarity = 0;
      user_pps_enable = 1;
   }
   else if(c == '-') {  // negative PPS polarity
      not_safe = 1;
      ++set_pps_polarity;                  
      user_pps_polarity = 1;
      user_pps_enable = 1;
   }
   else if(c == '^') {  // toggle OSC signal polarity (referenced to the PPS signal)
      not_safe = 1;
      ++set_osc_polarity;                  
      user_osc_polarity = toggle_option(user_osc_polarity, d);
   }
   else if(c == '*') {
      ++murray;
   }
   else {   // not a command that we know about
      return c;
   }

   return 0;  // we did something useful
}

int option_switch(char *arg)  
{   
char c, d;

   // process a command line option parameter
   d = 0;
   c = tolower(arg[1]);
   if(c) d = tolower(arg[2]);

   if((arg[0] == '=') || (arg[0] == '$')) {  // it is a hex byte to send to the tbolt
      save_cmd_bytes(arg);
   }
   else if(c == '0') {  // toggle com port processing flag
      process_com = toggle_option(process_com, d);
      if(process_com == 0) com_port = 0;
   }
   else if(isdigit(c)) {  // com port number
      strupr(arg);
      if     (strstr(arg, "P")) lpt_port = atoi(&arg[1]);  // parallel port used for temp control
      else if(strstr(arg, "T")) lpt_port = atoi(&arg[1]);  // parallel port used for temp control 
      else if(strstr(arg, "U")) {  // linux ttyUSB#
         usb_port = atoi(&arg[1]); 
         com_port = 0;
      }
      else {
         com_port = atoi(&arg[1]);
         usb_port = 0;
      }
      process_com = 1;
      if(com_running) {
         init_com();
      }
   }
   // we break up the command line processing big 'if' statement 
   // into two parts so the DOS compiler heap does not overflow
   else if((c >= 'a') && (c <= 'o')) {   // first half of command line options
      return cmd_a_to_o(arg);           
   }
   else {                                // all the other command line options
      return cmd_other(arg);
   }

   return 0;  // we did something useful
}

