// ------------------------------------------------------------------
//
// --- Tbolt2Lcd
//     Monitor for Trimble Thunderbolt GPSDO (Tbolt)
//     by Götz Romahn 24-Jul-2013, for private use only (GWR)
//     goetz@g-romahn.de
//
// --- This package was compiled with WinAVR2010. Programming the device with avrdude
//     is provided in make file. You may need to adapt this to your programmer. 
//     I use the simple LPT - 4 resistor version, that is compatible with STK200.
//     (google for "pony simple parallel programmer schematic")
//
// --- based on: tsip2gps
//     TSIP GPS to HD44780 LCD decoder                            ---
//     device ATmega8515 @ XTAL f = 12.000 MHz                    ---
//     fuses: C9EF (wd off) or 99EF (wd on)                       ---
//
// --- still using old fashioned ATmega8515 since it is cheap, available, 
//     8K flash is enough and I am too lazy to migrate to another CPU (GWR)
//
// This monitor provides information about Tbolts health. It does to Tbolt listen only.
// It is assumed, that Tbolt has been set up properly with TboltMonitor and/or LadyHeather(LH).
// Therefore no position or self survey data are shown. You should know where you are and
// precision survey should have been completed ( see LH for this ). Also I could not see
// any use for displaying ADC or Temperature data because you need them over time. For this 
// LadyHeather, that can be connected in parallel by using an y-cable, is a powerfull tool.
//
// For decoding Super Packets 0x8f-ab and 0x8f-ac are used ( see description in manual);
// to obtain count of fixed satellites we also use packet 0x6d. This is output also from
// Tbolt after powering up ( may be because set up so by TboltMonitor and/or LadyHeather).
//
// This monitor may be compiled to two differnt versions:
// 1st: by defining "TOW" GPS Seconds of Week and Week Number are used for decoding time and date.
// Btw  10bit week rollover does not seem to be a problem. Tbolt transmits correct week 
// ( 1750 at time of writing) as is also shown by TboltMonitor or LH.
//
// UTC offset is included automatically and MEZ (CET) and ME(S)Z ( CEST/CEDT) are shown, when
// connecting pin 21 (Port PC0) to ground insteat UTC when left open. DST is determined automatically
// following European rules. Overseas people please help yourself or comment out that code before
// compiling. Alternate time zones eg. Pacific Time may easily be edited in.
//
// 2nd: by commenting out "#define TOW" at compile time tbolts time and date info from bytes 10 to 16
// is used and you can set up tbolt to use GPS or UTC time eg. with TboltMonitor.
//
// No further user interaction is required.
//
// 1st line of LCD 			hh:mm:ssT Sats:# (T:time zone U/M/S)
//	if no sats received:	hh:mm:ssTDDMonYY
//
// 2nd line of LCD cycles through various status messages:
//		>Decoding Status			-- (only shown if bad) decoded	
//		>Disciplining Mode			-- decoded
//		>Disciplining Activity		-- decoded
//		>Minor Alarms				-- (only if happens) decoded
//		>Critical Alarm				-- (only if happens)  not cycling, bitfield only hexadecimal output. 
//										Since we are in trouble we may use other tools anyway.
//
//		Receiver Mode is not shown. When properly set up for timing, it stays "OverDetermined"
//
// ------------------------------------------------------------------

// CPU clock frequency
#define F_CPU 12000000UL	


#include <inttypes.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <util/delay.h>
#include "lcd.h"

#define SEC_HOUR 3600
#define SEC_DAY 86400
#define SEC_MIN 60
#define SEC_MEZ 3600		// central european time zone MEZ or CET UTC+1 hour
#define SEC_MESZ 3600		// DST daylight saving time MEZ+1 hour

#define pinMEZ		PC0		// define Pin for UTC vs ME(S)Z selection

#define TOW 		// uncomment this to use GPS_timeofweek and GPS_weeks for date-info
// if defined, only UTC or MEZ or MESZ are available independent of tbolts time settings
// if commented, you prefer date and time in GPS vs UTC depending on tbolts settings

//                               12345678901234561234567890123456
char lcdScreen[33];

volatile int 		systime = 0;					// wrapped by time()
volatile int 		lastgpspkt = 0;
volatile char 		key = 0;

char gpstime[33];

PGM_P gpshealth;
uint16_t minorwert = 0;
uint8_t minorbit = 0;
uint8_t satcount = 0;
volatile uint8_t newsec=0;

int time(void) 
{
	cli();
	int t = systime;
	sei();
	return t;
}

// ------------------------------------------------------------------

#define DLE 0x10
#define ETX 0x03

// ------------------------------------------------------------------
// get count of satellites used for fixes
uint8_t tsipSATELLITE[4];

char tsipDecodeSATELLITE(void)
{
	if (tsipSATELLITE[0] != 0x6d)
		return 0;

	satcount = tsipSATELLITE[1]/16;
	
	tsipSATELLITE[0] = 0;
	return 1;
}


// ------------------------------------------------------------------
// decode 0x8F-ac status packet
// Report Packet 0x8F-ac data descriptions

uint8_t tsipSTATUS[14];		// Bytes 0 - 13 only

/* Mode not used: receiver mode is a configuration option. 
// Mode does not change without user intervention;
// rx comes up overdet. if it has stored position
// receiver-mode Byte 1
const char decodingrxmode0[]  PROGMEM = "Automat. (2D/3D)";
const char decodingrxmode1[]  PROGMEM = "Singl Sat (Time)";
const char decodingrxmode3[]  PROGMEM = "Horizontal  (2D)";
const char decodingrxmode4[]  PROGMEM = "Full Posit. (3D)";
const char decodingrxmode5[]  PROGMEM = "DGPS Reference  ";
const char decodingrxmode6[]  PROGMEM = "Clock Hold (2D) ";
const char decodingrxmode7[]  PROGMEM = "Overdetrmd Clock";
*/

//decoding Disciplining Mode Byte 2
const char disciplinmode0[]   PROGMEM = "Normal Discipl. ";
const char disciplinmode1[]   PROGMEM = "Power up        ";
const char disciplinmode2[]   PROGMEM = "Auto Holdover   ";
const char disciplinmode3[]   PROGMEM = "Manual Holdover ";
const char disciplinmode4[]   PROGMEM = "Recover Discipl.";
const char disciplinmode5[]   PROGMEM = "??Mode not used?";
const char disciplinmode6[]   PROGMEM = "Disabled Discipl";
const char disciplinmodeu[]   PROGMEM = "Unknwn Disc Mode";	// should never happen

//decoding Status Byte 12
const char decodingstatus0[]  PROGMEM = "Doing fixes     ";
const char decodingstatus1[]  PROGMEM = "No GPS Time yet ";
const char decodingstatus2[]  PROGMEM = "??Status??      ";
const char decodingstatus3[]  PROGMEM = "PDOP is too high";
const char decodingstatus8[]  PROGMEM = "No usable Sats. ";
const char decodingstatus9[]  PROGMEM = "1 usable Sat    ";
const char decodingstatus10[] PROGMEM = "2 usable Sats.  ";
const char decodingstatus11[] PROGMEM = "3 usable sats.  ";
const char decodingstatus12[] PROGMEM = "Sat. is unusable";
const char decodingstatus16[] PROGMEM = "TRAIM rejct. fix";
const char decodingstatusu[]  PROGMEM = "Unknown Status  ";	// should never happen

//decoding Disciplining Activity Byte 13 
const char decodingactivity0[]  PROGMEM = "Phase locking   ";
const char decodingactivity1[]  PROGMEM = "Oscillat warm up";
const char decodingactivity2[]  PROGMEM = "Frquency locking";
const char decodingactivity3[]  PROGMEM = "Placing PPS     ";
const char decodingactivity4[]  PROGMEM = "Init Loop Filter";
const char decodingactivity5[]  PROGMEM = "Compensatg. OCXO";
const char decodingactivity6[]  PROGMEM = "Discipl Inactive";
const char decodingactivity7[]  PROGMEM = "  ??            ";
const char decodingactivity8[]  PROGMEM = "Recovery loop   ";
const char decodingactivity9[]  PROGMEM = "Calibr > Voltage";
const char decodingactivityu[]  PROGMEM = "Unknown activity";	// should never happen

//decoding Bits of Minor Alarms Bytes 10/11 
const char decodingmalarm0[]  PROGMEM = "DAC near rail   ";
const char decodingmalarm1[]  PROGMEM = "Antenna open    ";
const char decodingmalarm2[]  PROGMEM = "Antenna shorted ";
const char decodingmalarm3[]  PROGMEM = "Not trackg sats.";
const char decodingmalarm4[]  PROGMEM = "Not discpl. Osc.";
const char decodingmalarm5[]  PROGMEM = "Survey progress ";
const char decodingmalarm6[]  PROGMEM = "No stored Posit.";
const char decodingmalarm7[]  PROGMEM = "Leap sec pending";
const char decodingmalarm8[]  PROGMEM = "In test mode    ";
const char decodingmalarm9[]  PROGMEM = "Position is ??  ";
const char decodingmalarm10[]  PROGMEM = "EEPROM invalid  ";
const char decodingmalarm11[]  PROGMEM = "Almanach incompl";
const char decodingmalarm12[]  PROGMEM = "PPS not generatd";	// message not generated by tbolt
const char decodingmalarmu[]   PROGMEM = "Unknwn Min Alarm";	// should never happen

// Alarm
const char criticalalarm[]	PROGMEM = "Crit. Alarm 0x  ";	// Byte 9

char tsipDecodeSTATUS(void)
{
	if (tsipSTATUS[0] != 0xac)
		return 0;

	gpshealth = 0;

//	tsipSTATUS[9] = 0x1a;			// for testing of crit alarm message only
	
	if (!tsipSTATUS[12]) {			// if good (==0) GPS Decoding Status show Mode
									// else if bad override with Status.....

/* Mode not used: receiver mode is a configuration option. 
// Mode does not change without user intervention
		switch (tsipSTATUS[1]) {
			case  0: gpshealth = decodingrxmode0;  break;		 
			case  1: gpshealth = decodingrxmode1;  break;
			case  3: gpshealth = decodingrxmode3;  break;
			case  4: gpshealth = decodingrxmode4;  break;
			case  5: gpshealth = decodingrxmode5;  break;
			case  6: gpshealth = decodingrxmode6;  break;
			case  7: gpshealth = decodingrxmode7;  break;
		}
*/

		switch (tsipSTATUS[2]) {		// Disciplining Mode
			case  0: gpshealth = disciplinmode0;  break;		 
			case  1: gpshealth = disciplinmode1;  break;
			case  2: gpshealth = disciplinmode2;  break;
			case  3: gpshealth = disciplinmode3;  break;
			case  4: gpshealth = disciplinmode4;  break;
			case  5: gpshealth = disciplinmode5;  break;
			case  6: gpshealth = disciplinmode6;  break;
			default: gpshealth = disciplinmodeu;  break;
		}

	} else {

		switch (tsipSTATUS[12]) {		// ....no good GPS Decoding Status
			case  0: gpshealth = decodingstatus0;  break;	// case 0 never displayed since good
			case  1: gpshealth = decodingstatus1;  break;
			case  2: gpshealth = decodingstatus2;  break;
			case  3: gpshealth = decodingstatus3;  break;
			case  8: gpshealth = decodingstatus8;  break;
			case  9: gpshealth = decodingstatus9;  break;
			case 10: gpshealth = decodingstatus10; break;
			case 11: gpshealth = decodingstatus11; break;
			case 12: gpshealth = decodingstatus12; break;
			case 16: gpshealth = decodingstatus16; break;
			default: gpshealth = decodingstatusu;  break;
		}
	}

// alternate through 2nd LCD line every 8s
// default Disciplining Mode/Status for 3s ( if min alarm ) or 5s

	if ( ( (time()&0x07) >= 0) && ( (time()&0x07) <= 2) ) {	// Disciplining Activity for 3s 

		switch (tsipSTATUS[13]) {	// ... then show Disciplining 
			case  0: gpshealth = decodingactivity0;  break;		 
			case  1: gpshealth = decodingactivity1;  break;
			case  2: gpshealth = decodingactivity2;  break;
			case  3: gpshealth = decodingactivity3;  break;
			case  4: gpshealth = decodingactivity4;  break;
			case  5: gpshealth = decodingactivity5;  break;
			case  6: gpshealth = decodingactivity6;  break;
			case  7: gpshealth = decodingactivity7;  break;
			case  8: gpshealth = decodingactivity8;  break;
			case  9: gpshealth = decodingactivity9;  break;
			default: gpshealth = decodingactivityu;  break;
		}
	}

		minorwert = tsipSTATUS[10]*256 + tsipSTATUS[11];	
	if ( minorwert && ( (time()&0x07) >= 6)  ) {			// Minor Alarm for 2s

		minorbit++;
		while (!(minorwert & (1<<minorbit))) { minorbit++; } 
		switch (minorbit) {	// ... then show Disciplining Activity
			case  0: gpshealth = decodingmalarm0;  break;		 
			case  1: gpshealth = decodingmalarm1;  break;
			case  2: gpshealth = decodingmalarm2;  break;
			case  3: gpshealth = decodingmalarm3;  break;
			case  4: gpshealth = decodingmalarm4;  break;
			case  5: gpshealth = decodingmalarm5;  break;
			case  6: gpshealth = decodingmalarm6;  break;
			case  7: gpshealth = decodingmalarm7;  break;
			case  8: gpshealth = decodingmalarm8;  break;
			case  9: gpshealth = decodingmalarm9;  break;
			case  10: gpshealth = decodingmalarm10;  break;
			case  11: gpshealth = decodingmalarm11;  break;
			case  12: gpshealth = decodingmalarm12;  break;
			default: gpshealth = decodingmalarmu;  break;
		}

		if ( minorbit >12 ) minorbit =0;
	}

	if (tsipSTATUS[8] || tsipSTATUS[9]) gpshealth = criticalalarm;		// supercedes any other message
	tsipSTATUS[0] = 0;			// ready to receive new status packet
	return 1;
}

// ------------------------------------------------------------------
// ------------------------------------------------------------------
// decode 0x8F-ab timing packet

//uint8_t tsipGPSTIME[19];
uint8_t tsipGPSTIME[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// tbolt message packet format for Primary Timing Packet (0x8f-ab).
typedef
	struct
	{
    uint8_t subcode;
    uint32_t timeOfWeek;
    uint16_t weekNumber;
    int16_t	 utcOffset;
    uint8_t timingFlag;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint16_t year;
	} gps_time_t;

gps_time_t* gps_time;

//! Byte swap unsigned short. Make big endian to little endian
uint16_t swap_uint16( uint16_t val ) 
{
    return (val << 8) | (val >> 8 );
}

//! Byte swap unsigned int. Make big endian to little endian
uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}


// ------------------------------------------------------------------
#ifdef TOW		// if defined use GPS_timeofweek and GPS_weeks for date and time info
// Subroutines to calculate date from GPStow and GPSweek
//
// Return Modified Julian Day given calendar year,
// month (1-12), and day (1-31).
// - Valid for Gregorian dates from 17-Nov-1858.
// - Adapted from sci.astro FAQ.
//
long DateToMjd (long Year, long Month, long Day)
{
    return
        367 * Year
        - 7 * (Year + (Month + 9) / 12) / 4
        - 3 * ((Year + (Month - 9) / 7) / 100 + 1) / 4
        + 275 * Month / 9
        + Day
        + 1721028
        - 2400000;
}

// Convert Modified Julian Day to calendar date.
// - Assumes Gregorian calendar.
// - Adapted from Fliegel/van Flandern ACM 11/#10 p 657 Oct 1968.
void MjdToDate (long Mjd, long *Year, long *Month, long *Day)
{
    long J, C, Y, M;

    J = Mjd + 2400001 + 68569;
    C = 4 * J / 146097;
    J = J - (146097 * C + 3) / 4;
    Y = 4000 * (J + 1) / 1461001;
    J = J - 1461 * Y / 4 + 31;
    M = 80 * J / 2447;
    *Day = J - 2447 * M / 80;
    J = M / 11;
    *Month = M + 2 - (12 * J);
    *Year = 100 * (C - 49) + Y + J;
}

// Convert GPS Week and Seconds to Modified Julian Day.
// - Ignores UTC leap seconds.
long GpsToMjd (long GpsCycle, long GpsWeek, long GpsSeconds)
{
    long GpsDays;

    GpsDays = ((GpsCycle * 1024) + GpsWeek) * 7 + (GpsSeconds / SEC_DAY);
    return DateToMjd(1980, 1, 6) + GpsDays;
}

// ------------------------------------------------------------------

int8_t dow(int16_t y, int8_t m, int8_t d)	// compute day of week day == 0 >> sunday
{
    static int8_t t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}
#endif	// TOW

// ------------------------------------------------------------------
long	dst = 0;					// offset daylight saving time  
long	mez = 0;					// offset MEZ time  
const char months[] PROGMEM = "???JanFebMarAprMayJunJulAugSepOctNovDec";

char tsipDecodeGPSTIME(void)
{
gps_time = (gps_time_t*) tsipGPSTIME;

	if ( (gps_time->subcode) != 0xab)
		return 0;

//	ups!!--tbolt is big_byte-endian, AVR GCC little_byte-endian
	gps_time->year = swap_uint16(gps_time->year);

char	timezonechar ='G';
		if (gps_time->timingFlag&0x01) timezonechar ='U';	// in case we rely on tbolts timezone 

// ------------------------------------------------------------------
// ------------------------------------------------------------------
#ifdef TOW		// if defined use GPS_timeofweek and GPS_weeks for date and time info

	gps_time->utcOffset = swap_uint16(gps_time->utcOffset);
	gps_time->weekNumber = swap_uint16(gps_time->weekNumber);	// week# from tbolt is >1024!!
	gps_time->timeOfWeek = swap_uint32(gps_time->timeOfWeek);

//	sprintf(gpstime,"%lu     ",gps_time->timeOfWeek);	//debug
//	sprintf(gpstime,"%u      ",gps_time->weekNumber);	//debug

// get calendar date from GPS timeofWeek and weekNumber
// code is from www.leapsecond.com/tools/gpsdate.c
long	Year, Month, Day;
long	Mjd;			// current Modified Julian Day
long	GpsWeek, GpsSeconds, DaySeconds;

	// GpsSeconds is negativ from Sunday 0:0 hour 0 secs. until utcoffset, with UTC therefore:
	GpsWeek = (long)gps_time->weekNumber-1;	// 1 week back and corresponding # of sec added
	// to prevent GpsSeconds underflow early on Sunday if UTC selected
	// this also helps handling negative time zone offsets to UTC e.g. in the US
	GpsSeconds = gps_time->timeOfWeek+604800-(long)(gps_time->utcOffset) +mez +dst;
    Mjd = GpsToMjd(0, GpsWeek, GpsSeconds);	// GpsCycle set to 0, see week# above
    MjdToDate(Mjd, &Year, &Month, &Day);


	if ((PINC& (1<< pinMEZ))) {mez = 0; dst = 0; timezonechar ='U';}	// if set show UTC
	if (!(PINC& (1<< pinMEZ))) {										// if clear show ME(S)Z
// ------------------------------------------------------------------
// compute MEZ and begin and end of daylight saving time (DST == MESZ)
// dst begins last Sunday in March and ends last Sunday in October
// European rule is: begin of DST is last Sunday in March, end of DST is last Sunday of October
// should be not too difficult to implement other rules
		mez = SEC_MEZ;
long	lastSundayMarch = (long)(31 - dow(gps_time->year, 3, 31));		// DST begins
long	lastSundayOctober = (long)(31 - dow(gps_time->year, 10, 31));	// DST ends 
long	SummerMjd = DateToMjd (Year, 3, lastSundayMarch);		// Modified Julian Day, begin of DST
long	WinterMjd = DateToMjd (Year, 10, lastSundayOctober);	// Modified Julian Day, end of DST
		if (Mjd >= SummerMjd) {dst = SEC_MESZ; timezonechar ='S';}
		if (Mjd >= WinterMjd) {dst = 0; timezonechar ='M';}
// thats all with daylight saving time
// ------------------------------------------------------------------
	} 

//	overwrite correspondig data in tsip_packet
	gps_time->year = (uint16_t)Year;
	gps_time->month = (uint8_t)Month;
	gps_time->day = (uint8_t)Day;

// get time of day from GPS timeofWeek 
	DaySeconds = GpsSeconds%SEC_DAY;
//	sprintf(gpstime,"%lu     ",DaySeconds);	//debug

//	overwrite correspondig data in tsip_packet
	gps_time->hours = (uint8_t)(DaySeconds/SEC_HOUR);
	gps_time->minutes = (uint8_t)((DaySeconds-(long)gps_time->hours*SEC_HOUR)/60);
	gps_time->seconds = (uint8_t)((DaySeconds-(long)(gps_time->hours*SEC_HOUR)-(long)(gps_time->minutes*60)));

#endif	// TOW

// ------------------------------------------------------------------
// ------------------------------------------------------------------

	sprintf(gpstime,"%02u:%02u:%02u%1s ",gps_time->hours,gps_time->minutes,gps_time->seconds,&timezonechar);

	if(!satcount && !(gps_time->timingFlag&0x04)) {		// show date....
		sprintf(gpstime+9,"%02u   %02u",gps_time->day,gps_time->year-2000);
		strncpy_P(gpstime+11, months+(3*gps_time->month), 3);
	} else {												// ... or count of rxd sats
		sprintf(gpstime+9," Sats:%1u",satcount);
	}	

	satcount = 0;			// assume no satcount available
	tsipGPSTIME[0] = 0;
	return 1;
}

// ------------------------------------------------------------------

#define keyNO		PA7
#define keyYES		PA0
#define keyLEFT		PA6
#define keyRIGHT	PA4

void hwinit(void)
{
//	sbi(ACSR, ACD);		// analog comparator poweroff
//	ACSR |= (1<<ACD);	// analog comparator poweroff
	UBRRH = 0;			// set UART baud rate to 9600 @ 12.000MHz
	UBRRL = 77;			// set UART baud rate to 9600 @ 12.000MHz
	UCSRB = 0xb8;		// enable RX/TX, enable RX int, enable UDR empty interrupt
	TCCR1A = 0;			// normal mode of operation (0 by default, but just in case)
	TCCR1B = 0x04;		// prescale Timer1 clk/256
	TCCR0 = 0x05;		// prescale Timer0 clk/1024
	TIMSK = 0x82;		// enable overflow interrupts for both timers
	DDRC = 0;			// configure portc as inputs
	PORTC = 0xff;		// also enable the pullup resistor
}

// ------------------------------------------------------------------


// ------------------------------------------------------------------


int main(void)
{
	_delay_ms(100);
	hwinit();
	_delay_ms(100);
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts_p(PSTR("Tbolt2LCD (GWR) "));	// greeting

	_delay_ms(2000);
	
	sei();			// now, that all is settled, we enable interrupts

	while (1)
	{
		wdt_reset();
		
// no packet received
		if ((time() > (lastgpspkt + 2)) && newsec) {		// do it only once per second
			lcd_clrscr();
			lcd_puts_p(PSTR("Tbolt Connected?"));
			lcd_gotoxy(0, 1);
			lcd_puts_p(PSTR("No packet      s"));
			itoa(time() - lastgpspkt, lcdScreen, 10);
			lcd_gotoxy(10, 1);
			lcd_puts(lcdScreen);
			satcount=0;		
			newsec=0;		
		}
		
		if (tsipDecodeSTATUS() && (gpshealth)) {			
			lcd_gotoxy(0, 1);
			lcd_puts_p(gpshealth);
			if (tsipSTATUS[9]) {		// critical alarm, report reason in hex
				itoa(tsipSTATUS[9], lcdScreen, 16);
				lcd_gotoxy(14, 1);
				lcd_puts(lcdScreen);
			}
		}

		if	(tsipDecodeSATELLITE()) {		// get count of satellites if possible
		}

/*
		if	(tsipDecodeSATLEVEL()) {		// gcount of satellites tracked or track attempted
		}
*/

		if	(tsipDecodeGPSTIME()) {
			lcd_gotoxy(0, 0);
			lcd_puts(gpstime);
		}
	}
}

// ------------------------------------------------------------------
// --- INTERRUPTS ---------------------------------------------------
// ------------------------------------------------------------------


// Timer0 overflow
// prescaler = clk/1024
// CK/1024 @ 12.000MHz = 11700Hz, so to overflow every 5ms
// timer0 must start counting at 255-60
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0xff-60;
/* not used here	
	if (bit_is_clear(PINA, keyYES)) {
		key = 'Y';
	} else
	if (bit_is_clear(PINA, keyNO)) {
		key = 'N';
	} else
	if (bit_is_clear(PINA, keyLEFT)) {
		key = 'L';
	} else
	if (bit_is_clear(PINA, keyRIGHT)) {
		key = 'R';
	} else
*/
	key = 0;
}

// Timer1 overflow interrupt
// CK/256 @ 12.000MHz = 46875 Hz, so to overflow every 1s,
// timer1 must start counting at 65535-46875
ISR(TIMER1_OVF_vect)
{
	TCNT1 = (0xffff-46875);
	
	systime++;
	newsec=1;	
}

// INT0
ISR(INT0_vect)
{
}

#define rxBufSize 69
uint8_t rxBuffer[rxBufSize];

// UART Rx interrupt
ISR(USART_RX_vect)
{
	static uint8_t stuff = 0;
	static int8_t rxBufLen = -1;

	unsigned char a;
//	a = inb(UCSRA);		// check error flags
	a = UCSRA;		// check error flags
	if (a & (_BV(FE)|_BV(DOR)|_BV(PE))) {
		rxBufLen = -1;
	}
	
//	a = inb(UDR);
	a = UDR;
	
	if (rxBufLen == -1) {	// if we want a new packet, first byte must be DLE
		if (a == DLE) {
			rxBufLen = 0;
			stuff = 0;
		}
		return;
	}
	
	if ((stuff)&&(a == ETX)) {	// if DLE ETX sequence, exit
		lastgpspkt = systime;	// IN INTERRUPT, DO NOT USE time() since that will SEI

		if ((rxBuffer[0] == 0x8f)) {		
			if ((rxBuffer[1] == 0xac)&&(rxBufLen == 69)&&(tsipSTATUS[0] != 0xac)) {	// GPS status
			memcpy(tsipSTATUS, rxBuffer+1,14);
			} 
			if ((rxBuffer[1] == 0xab)&&(rxBufLen == 18)&&(tsipGPSTIME[0] != 0xab)) {	// GPS time
			memcpy(tsipGPSTIME, rxBuffer+1, 18);
			} 
			if ((rxBuffer[1] == 0xa7)&&(rxBufLen == 55)&&(tsipGPSTIME[0] != 0xa7)) {	// GPS report here not used
			}
		}
		if ((rxBuffer[0] == 0x6d)&&(rxBufLen >= 3)&&(tsipSATELLITE[0] != 0x6d)) {	// GPS satellite selection list
			memcpy(tsipSATELLITE, rxBuffer,3);
		}

	rxBufLen = -1;
	return;
	} else {
	
	if ((!stuff)&&(a == DLE)) {	// if DLE in the middle, set STUFF and exit
	stuff = 1;
	return;
	}
	
		stuff = 0;
	
		if (rxBufLen < rxBufSize) {
		rxBuffer[rxBufLen++] = a;
		}
		return;
	}
	return;
}

// UDR empty interrupt
ISR(USART_UDRE_vect)
{
}
