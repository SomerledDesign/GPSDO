// ------------------------------------------------------------------
// --- TSIP GPS to HD44780 LCD decoder                            ---
// ---                                26.jun.2004, Matej Kogovsek ---
// ---  device ATmega8515 @ XTAL f = 12.000 MHz                   ---
// --- fuses: C9EF (wd off) or 99EF (wd on)                       ---
// ------------------------------------------------------------------

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lcd.h"

//                               12345678901234561234567890123456
unsigned char lcdScreen[33];

volatile int systime = 0;					// wrapped by time()
volatile int lastgpspkt = 0;
volatile char key = 0;

int gpsvel;
char gpsdir[3];

float gpsposlat = 0.0;
float gpsposlng = 0.0;

unsigned char gpstime[17];

PGM_P gpshealth;

struct s_place {
	float lat1;
	float lon1;
	float lat2;
	float lon2;
	char name[16];
};

#define plcsize (sizeof(struct s_place))

// ------------------------------------------------------------------

void comsendchar(char a)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	outb(UDR, a);
}

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

float extractFloat(char* p)
{
	float r;
	char* x;
	x = (char*)&r;
	x[0] = p[3];
	x[1] = p[2];
	x[2] = p[1];
	x[3] = p[0];
	
	return r;
}

void tsipSetIO(void)
{
	comsendchar(DLE);
	comsendchar(0x35);	// set io options
	
	comsendchar(0x02);	// 1 = XYZ ECEF position, 2 = LLA position
	comsendchar(0x02);	// 1 = XYZ ECEF velocity, 2 = ENU velocity
	comsendchar(0x01);  // UTC time
	comsendchar(0x00);  // no auxiliary measurements
	
	comsendchar(DLE);
	comsendchar(ETX);
}

unsigned char tsipSPPFLLA[21];

char tsipDecodeSPPFLLA(void)
{
	if (tsipSPPFLLA[0] != 0x4a)
		return 0;
	
	gpsposlat = 180.0 / M_PI * extractFloat(tsipSPPFLLA+1);
	gpsposlng = 180.0 / M_PI * extractFloat(tsipSPPFLLA+1+4);
	
	tsipSPPFLLA[0] = 0;
	return 1;
}

unsigned char tsipSPVFENU[21];

char tsipDecodeSPVFENU(void)
{
	if (tsipSPVFENU[0] != 0x56)
		return 0;
		
	float e = extractFloat(tsipSPVFENU+1);
	float n = extractFloat(tsipSPVFENU+1+4);
	float u = extractFloat(tsipSPVFENU+1+4+4);

	float fv = sqrt((e*e)+(n*n)+(u*u)) * 3.6;
	
	gpsvel = fv;		// store velocity in global
	
	if (abs(n * 2.4) > abs(e)) {
		if (n > 0) {
			gpsdir[0] = 'N';
		} else {
			gpsdir[0] = 'S';
		}
	} else {
		gpsdir[0] = ' ';
	}
		
	if (abs(e * 2.4) > abs(n)) {
		if (e > 0) {
			gpsdir[1] = 'E';
		} else {
			gpsdir[1] = 'W';
		}
	} else {
		gpsdir[1] = ' ';
	}
	
	gpsdir[2] = 0;
		
	tsipSPVFENU[0] = 0;
	return 1;
}

unsigned char tsipHOR[3];

const char gpshor0[]  PROGMEM = "Doing position fixes            ";
const char gpshor1[]  PROGMEM = "Don't have GPS time yet         ";
const char gpshor2[]  PROGMEM = "Need initialization             ";
const char gpshor3[]  PROGMEM = "PDOP is too high                ";
const char gpshor8[]  PROGMEM = "No usable sattelites            ";
const char gpshor9[]  PROGMEM = "Only 1 usable sattelite         ";
const char gpshor10[] PROGMEM = "Only 2 usable sattelites        ";
const char gpshor11[] PROGMEM = "Only 3 usable sattelites        ";
const char gpshor12[] PROGMEM = "The chosen sattelite is unusable";

char tsipDecodeHOR(void)
{
	if (tsipHOR[0] != 0x46)
		return 0;
		
	gpshealth = 0;
	
	switch (tsipHOR[1]) {
		case 0: break;		// we don't want this message, leave gpshealth at 0
		case  1: gpshealth = gpshor1; tsipSetIO(); break;
		case  2: gpshealth = gpshor2;  break;
		case  3: gpshealth = gpshor3;  break;
		case  8: gpshealth = gpshor8;  break;
		case  9: gpshealth = gpshor9;  break;
		case 10: gpshealth = gpshor10; break;
		case 11: gpshealth = gpshor11; break;
		case 12: gpshealth = gpshor12; break;
	}
	
	tsipHOR[0] = 0;
	return 1;
}

void tmtoa(char val, char* buf)
{
	if (val < 60) {
		if (val < 10) {
			buf[0] = '0';
			buf++;
		}
		itoa(val, buf, 10);
	} else {
		buf = "??";
	}
}

unsigned char tsipGPSTIME[11];
const char weekdays[] PROGMEM = "SunMonTueWedThuFriSat???";

char tsipDecodeGPSTIME(void)
{
	if (tsipGPSTIME[0] != 0x41)
		return 0;
		
	float gpst = extractFloat(tsipGPSTIME+1);		// GPS time in seconds
	float utco = extractFloat(tsipGPSTIME+1+4+2);	// GPS UTC offset (UTC = GPS - offset)
	float cet = gpst - utco + 3600.0;				// I want CET (UTC+1)

	if (cet >= 604800.0) cet -= 604800.0;			// mend possible overflow when offseting CET from UTC
//	float cet = 300275.0;
		
	uint32_t cets = cet;			// 300275 = Wednesday 11:24:35 (test)
	uint16_t cetm = cets / 60;		// 5004
	uint8_t ceth = cetm / 60;		// 83
	uint8_t cetd = ceth / 24;		// 3
	cets -= cetm * 60;				// 35
	cetm -= ceth * 60;				// 24
	ceth -= cetd * 24;				// 11
	
	// 1234567890123456
	// Wed     17:34:22
	
	if (cetd > 6) cetd = 7;		// if invalid weekday, set to point to ???
	
	strncpy_P(gpstime, weekdays+(3*cetd), 3);
	strncpy_P(gpstime+3, PSTR("     "), 5);
	
	tmtoa(ceth, gpstime+8);
	tmtoa(cetm, gpstime+8+3);
	tmtoa(cets, gpstime+8+3+3);
	gpstime[10] = ':';
	gpstime[13] = ':';
		
	tsipGPSTIME[0] = 0;
	return 1;
}

// ------------------------------------------------------------------

#define keyNO		PA7
#define keyYES		PA5
#define keyLEFT		PA6
#define keyRIGHT	PA4

void hwinit(void)
{
	sbi(ACSR, ACD);		// analog comparator poweroff
	
	outw(UBRRH, 0);		// set UART baud rate to 9600 @ 12.000MHz
	outw(UBRRL, 77);	// set UART baud rate to 9600 @ 12.000MHz
	outb(UCSRB, 0xb8);	// enable RX/TX, enable RX int, enable UDR empty interrupt
	
	outb(TCCR1A, 0);	// normal mode of operation (0 by default, but just in case)
	outb(TCCR1B, 0x04);	// prescale Timer1 clk/256
	outb(TCCR0, 0x05);	// prescale Timer0 clk/1024
	outb(TIMSK, 0x82);	// enable overflow interrupts for both timers
	
	outb(DDRA, 0);		// configure porta as inputs
	outb(PORTA, 0xff);	// also enable the pullup resistor
}

void delayms(unsigned short d)
{
	if (d == 0) return;
	
	while(d--) {
		asm volatile(
		"ldi r24,12"		"\n\t"
		"dly_outer:"		"\n\t"
		"ldi r25,250"		"\n\t"
		"dly_inner:"		"\n\t"
		"nop"				"\n\t"
		"dec r25"			"\n\t"
		"brne dly_inner"	"\n\t"
		"dec r24"			"\n\t"
		"brne dly_outer"	"\n\t"
		:
		:
		:"r24","r25");
	}
}

// ------------------------------------------------------------------

void PrintVel(void)
{
	char sv[8];
	itoa(gpsvel, sv, 10);
	char svl = strlen(sv);
	strcpy_P(lcdScreen,    PSTR("Velocity:   km/h"));
	strncpy(lcdScreen+9+3-svl, sv, svl);
	strcpy_P(lcdScreen+16, PSTR("Direction:      "));
	lcdScreen[30] = gpsdir[0];
	lcdScreen[31] = gpsdir[1];
}

void PrintPos(void)
{
    strcpy_P(lcdScreen, PSTR("Lat:"));
	dtostrf(gpsposlat, 12, 5, lcdScreen+4);
	strcpy_P(lcdScreen+16, PSTR("Lon:"));
	dtostrf(gpsposlng, 12, 5, lcdScreen+16+4);
}

void lcdPrint(void) {
	int i;
	
	for (i = 0; i < 32; i++) {
		if (lcdScreen[i] == 0) lcdScreen[i] = 0x20;
	}
	
	lcdScreen[32] = 0;
	lcd_puts(lcdScreen);
}

#define deglatm	111000		// 1 degree latitude is approx 111km
#define deglonm cos(gpsposlat*M_PI/180.0)*deglatm	// 1 degree longitude is dependent on latitude with cos(lat) * length of lat deg

char FindPlace(void)
{
	int i;
	struct s_place temp;

	for (i = 0; i < E2END; i += plcsize) {
		eeprom_read_block(&temp, (char*)i, plcsize);
		
		if (temp.name[0] == 0xff) break;
		
		// ugly code copy paste but...
		if ((temp.lat1 <= gpsposlat)&&(temp.lon1 <= gpsposlng)&&(temp.lat2 >= gpsposlat)&&(temp.lon2 >= gpsposlng)) {
			strncpy_P(lcdScreen, PSTR("Welcome to:     "), 16);
			strncpy(lcdScreen+16, temp.name, 16);
			return 1;
		}
	}
	
	return 0;
}

// ------------------------------------------------------------------

char eeWritePlace(void)
{
	struct s_place newplc;
	newplc.lat1 = gpsposlat-0.001;
	newplc.lat2 = gpsposlat+0.001;
	newplc.lon1 = gpsposlng-0.001;
	newplc.lon2 = gpsposlng+0.001;
	
	int i;
	int freeadr;
	
	for (freeadr = 0; freeadr < E2END; freeadr += plcsize) {
		
		for(i = 0; i < plcsize; i++) {
			if (eeprom_read_byte((char*)(freeadr+i)) != 0xff) break;
		}
		
		if (i >= plcsize) break;	// found an empty space
	}
	
	if (freeadr >= E2END) {
		strncpy(lcdScreen, PSTR("EE full! Sorry! "), 16);
		return 1;
	}

	strncpy_P(lcdScreen, PSTR("Place name:     "), 16);
	strncpy_P(lcdScreen+16, PSTR("A               "), 16);
	lcdPrint();
	
	for (i = 0; i < 16; i++) {
		while (key == 'Y') {}
		while (key != 'Y') {
			if (key == 'R') lcdScreen[16+i]++;
			if (key == 'L') lcdScreen[16+i]--;
			if (key == 'N') return 0;
			key = 0;
			
			if (lcdScreen[16+i] > 'z') lcdScreen[16+i] = 0x20;
			if (lcdScreen[16+i] < 0x20) lcdScreen[16+i] = 'z';
			lcdPrint();
			delayms(10);
		}
		lcdScreen[16+1+i] = lcdScreen[16+i];
	}
	lcdScreen[32] = 0;	// although done in several places, just to be sure
	
	// save to eeprom
	memcpy(newplc.name, lcdScreen+16, 16);
	eeprom_write_block(&newplc, (char*)freeadr, plcsize); 
	
	strncpy_P(lcdScreen, PSTR("Place saved!    "), 16);
	
	return 1;
}

// ------------------------------------------------------------------

#define prioEnterPlace 1
#define prioNOGPS	2
#define prioHOR 	3
#define prioGPSTIME 4
#define prioFindPlace 5
#define prioSPVFENU 6
#define prioSPPFLLA 7

#define prioNONE	10

int main(void)
{
	hwinit();
	sei();
	delayms(100);
	lcd_init(LCD_DISP_ON);
	
	int t_rp = -100;		// time of reset priority
	int t_pt = -100;		// time of print time (CET)

	char prio = prioNONE;

	while (1)
	{
		wdt_reset();
		
		if (time() > t_rp) {
			prio = prioNONE;
		}
		
		if ((key == 'Y') && eeWritePlace()) {
			prio = prioEnterPlace;
			t_rp = time() + 3;
			
			lcdPrint();
		}
		
		if ((time() > (lastgpspkt + 30))&&(prio >= prioNOGPS)) {
			prio = prioNOGPS;
			t_rp = time() + 3;
		
			strncpy_P(lcdScreen, PSTR("No packet from  GPS for      sec"), 32);
			itoa(time() - lastgpspkt, lcdScreen+24, 10);
			lcdPrint();
		}
		
		if (tsipDecodeHOR() && (gpshealth) && (prio >= prioHOR)) {
			prio = prioHOR;
			t_rp = time() + 3;
			
			strncpy_P(lcdScreen, gpshealth, 32);
			lcdPrint();
		}
		
		if (tsipDecodeGPSTIME() && (prio >= prioGPSTIME) && (time() > t_pt)) {
			prio = prioGPSTIME;
			t_rp = time() + 3;
			
			t_pt = time() + 60;
			strncpy(lcdScreen, gpstime, 16);
			lcdPrint();
		}
		
		if (tsipDecodeSPVFENU() && (gpsvel > 5) && (gpsvel < 300) && (prio >= prioSPVFENU)) {
			prio = prioSPVFENU;
			t_rp = time() + 5;
			
			PrintVel();
			lcdPrint();
		}
		
		if (tsipDecodeSPPFLLA() && (prio >= prioSPPFLLA)) {
			prio = prioSPPFLLA;
			t_rp = time() + 5;
			
			PrintPos();
			lcdPrint();
		}
		
		if (FindPlace() && (prio >= prioFindPlace)) {
			prio = prioFindPlace;
			t_rp = time() + 3;
			
			lcdPrint();
		}
	}
}

// ------------------------------------------------------------------
// --- INTERRUPTS ---------------------------------------------------
// ------------------------------------------------------------------


// Timer0 overflow
// prescaler = clk/1024
// CK/1024 @ 12.000MHz = 11700Hz, so to overflow every 1ms
// timer0 must start counting at 255-12
SIGNAL(SIG_OVERFLOW0)
{
	outb(TCNT0, 0xff-12);
	
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
	key = 0;
}

// Timer1 overflow interrupt
// CK/256 @ 12.000MHz = 46875 Hz, so to overflow every 1s,
// timer1 must start counting at 65535-46875
SIGNAL(SIG_OVERFLOW1)
{
	outw(TCNT1, 0xffff-46875);
	
	systime++;
	
	// should reinit display and GPS parameters here every 30secs or so
}

// INT0
SIGNAL(SIG_INTERRUPT0)
{
}

#define rxBufSize 32
char rxBuffer[rxBufSize];

// UART Rx interrupt
SIGNAL(SIG_UART_RECV)
{
	static char stuff = 0;
	static signed char rxBufLen = -1;

	unsigned char a;
	a = inb(UCSRA);		// check error flags
	if (a & (_BV(FE)|_BV(DOR)|_BV(PE))) {
		rxBufLen = -1;
	}
	
	a = inb(UDR);
	
	if (rxBufLen == -1) {	// if we want a new packet, first byte must be DLE
		if (a == DLE) rxBufLen = 0;
		return;
	}
	
	if ((stuff)&&(a == ETX)) {	// if DLE ETX sequence, exit
		if ((rxBuffer[0] == 0x46)&&(rxBufLen == 3)&&(tsipHOR[0] != 0x46)) {		// health of receiver
			memcpy(tsipHOR, rxBuffer, 3);
		} else
		if ((rxBuffer[0] == 0x4a)&&(rxBufLen == 21)&&(tsipSPPFLLA[0] != 0x4a)) {	// SP pos fix LLA
			memcpy(tsipSPPFLLA, rxBuffer, 21);
		} else
		if ((rxBuffer[0] == 0x56)&&(rxBufLen == 21)&&(tsipSPVFENU[0] != 0x56)) {	// SP vel fix ENU
			memcpy(tsipSPVFENU, rxBuffer, 21);
		} else
		if ((rxBuffer[0] == 0x41)&&(rxBufLen == 11)&&(tsipGPSTIME[0] != 0x41)) {	// GPS time
			memcpy(tsipGPSTIME, rxBuffer, 11);
		} else {
			lastgpspkt = systime;	// IN INTERRUPT, DO NOT USE time() since that will SEI
		}
		rxBufLen = -1;
		return;
	}
	
	if ((!stuff)&&(a == DLE)) {	// if DLE in the middle, set STUFF and exit
		stuff = 1;
		return;
	}
	
	stuff = 0;
	
	if (rxBufLen < rxBufSize) {
		rxBuffer[rxBufLen++] = a;
	}
}

// UDR empty interrupt
SIGNAL(SIG_UART_DATA)
{
}
