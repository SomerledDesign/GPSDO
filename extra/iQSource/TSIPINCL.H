/*
 ***************************************************************************
 *	Trimble part number:  40536
 ***************************************************************************
 *
 * Trimble Navigation, Ltd.
 * OEM Products Development Group
 * P.O. Box 3642
 * 645 North Mary Avenue
 * Sunnyvale, California 94088-3642
 *
 * Corporate Headquarter:
 *    Telephone:  (408) 481-8000
 *    Fax:        (408) 481-6005
 *
 * Technical Support Center:
 *    Telephone:  (800) 767-4822	(U.S. and Canada)
 *                (408) 481-6940    (outside U.S. and Canada)
 *    Fax:        (408) 481-6020
 *    BBS:        (408) 481-7800
 *    e-mail:     trimble_support@trimble.com
 *
 * *************************************************************************
 *
 * The following modules require TSIPINCL.H:
 *
 *    TSIPCHAT.C:  main program for communicating with TSIP devices
 *    TSIP_UTL.C:  user interface funtions
 *    TSIP_CMD.C:  command generator
 *    TSIP_RPT.C:  report interpreter
 *    TSIP_ALM.C:  grabs almanacs from, and stuffs them into, receiver
 *    T_SERIAL.C:  serial buffering routines
 *
 * This source code is supplied without warranty and is intended as sample
 * source code for exercising the TSIP interface.  We do appreciate comments
 * and try to support the software as much as possible.
 *
 * Developers of new applications are encouraged to use the functions in
 * T_SERIAL.C and T_FORMAT.C.
 *
 * *************************************************************************
 *
 */

#define TSIPCHAT_VERNUM "1.50"
#define TSIPCHAT_PARTNUM "47583"
#define TSIPCHAT_SOFTNUM "1.03  13 May 2002"

#define DIAG_MENU    -3
#define REPEAT_MENU  -2
#define ALL_MENU     -1
#define x79_MENU     0x79
#define x8E_MENU     0x8E

#define BANNER_TEXT	WHITE
#define BANNER_BACKGROUND	BLUE


#define ABLE_TEXT_LEN			2
#define BAUD_TEXT_LEN    		10
#define DATABIT_TEXT_LEN 		4
#define DGPS_MODE_TEXT_LEN		5
#define DYN_TEXT_LEN				5
#define PARITY_TEXT_LEN  		3
#define PROTOCOLS_TEXT_LEN		5
#define POS_FIX_TEXT_LEN		5
#define RCVR_PORT_TEXT_LEN		3
#define REQ_SET_TEXT_LEN   	2
#define STOPBIT_TEXT_LEN 		2
#define TOGGLE_TEXT_LEN 		2
#define TRACKMODE_TEXT_LEN		3
#define MAX_INPUT_MODE     2
#define MAX_OUTPUT_MODE    6

#define NMEA_MAX_MSG     		9

#define TAIP	0x01
#define TSIP	0x02
#define NMEA	0x04
#define RTCM	0x08

/* data base for keyboard command help screen */
typedef struct {
	char kbch;              /* ASCII code for keystroke */
	unsigned short cmdcode;       /* TSIP command code */
	unsigned short replycode;       /* TSIP command code */
	char cmdtext[18];       /* description of TSIP command */
   void (*cmdfn)(TSIPPKT *cmdptr);
} KB_CMD;

#define MENUWIN 		2
#define CMDWIN       1
#define AUTOWIN      0

#define TSIPFILE     1
#define AUTOFILE     2

#define reply_code(rpt) (((rpt)->code==0x8F)?(*(rpt)->buf+0x100):((rpt)->code))

/**/
/************************** TSIPCHAT.C **********************************/
/* called from main() in TSIPCHAT.C and TSIP_UTL.C */
unsigned char read_rpts_wait_for_kbhit
	(void);
/* in TSIP_CMD.C */
void proc_kbd
	(TSIPPKT *cmd,
	unsigned char kch,
	short *reply);
short menu_cmd_prompt
	(short code,
	KB_CMD *kb_cmd);
void match_port (
	unsigned char in_baud,
   unsigned char data_bits,
   unsigned char parity_code,
   unsigned char stop_bits);
void change_PC_serial_settings (
   short baud_code,  	  // baud = (75 << baud_code)
	short databits,        // 7 or 8 data bits
   short parity_code,     // none, odd, even
	short stopbits);       // 1 or 2 stopbits
/* in TSIP_RPT.C */
void rpt_packet
   (TSIPPKT *rpt, char *obuf);
short print_msg_table_header
	(unsigned char rptcode, char *HdrStr, unsigned char force);
/************************** TSIP_ALM.C **********************************/
/* functions called from TSIP_CMD.C */
short almgetb
	(void);
short almputb
	(void);
/************************** TSIP_UTL.C **********************************/
/* Utility functions for console display */
short cmd_esc
	(void);
void set_cmd_esc
	(short x);
/* put carriage return & linefeed */
void show_crlf
	(void);
/* ask user for verification of choice */
short ask_verify
	(void);
/* without introducing new-line/clear window to end of line */
short ask_verify_nocmdcrlf
   (void);
/* prompt user to input a double */
double ask_dbl
	(char *prompt);
/* prompt user to input an integer */
short ask_byte
	(char *prompt);
/* prompt user to input an unsigned long */
unsigned long ask_long
	(char *prompt);
/* ask for hex byte string, returns number of bytes read */
unsigned char ask_hex_string (
  	char *prompt,
	unsigned char *h,
	unsigned char maxchar);
unsigned char ask_char_string
   (char *prompt,
	char *h);
/* prompt user to pick among a finite number of choices */
short pick_one
   (char *prompt,
	char *code_txt[],
	short nopts);

/* DOS functions to set time */
void request_PC_time_set
	(void);
void GPS_time_from_PC
	(double *time);
short GPS_time_to_PC
	(double time);

/* BORLAND window functions */
void switch_window
	(short window_id);
void clr_cmd_window
	(short mode);
void start_menu_window
	(void);
void end_menu_window
	(void);
void new_cmd_window
	(void);
short which_window
	(void);
void initialize_screen
	(void);
void reset_screen
	(void);

/* file storage control */
void open_file_storage
	(FILE **stream, char *filename);
void close_file_storage
	(FILE **stream, char *filename);

/* serial port control */
#define NO_PARITY       0x00
#define ODD_PARITY      0x08
#define EVEN_PARITY     0x18
#define STOPBITS_2		1
#define STOPBITS_1		0
#define DATABITS_8		3
#define DATABITS_7		2
#define BAUD_38400  		9
#define BAUD_19200  		8
#define BAUD_9600			7
#define BAUD_4800			6
#define BAUD_2400			5
#define BAUD_1200			4
#define BAUD_600			3
#define BAUD_300			2
typedef struct
{
   short port;            // 1 = COM1, 2 = COM2
	short baud_code;  	  // baud = (75 << baud_code)
	short databits;        // 7 or 8 data bits
	short stopbits;        // 1 or 2 stopbits
	short parity_code;     // none, odd, even
} PORT_DEF;

short set_buf_serial_port
	(PORT_DEF *pdef);
/************************* T_SERIAL.C *********************************/
void  initsio
	(PORT_DEF *pdef);
short   get_char (        // returns -1 for no char waiting, 0-FF otherwise
	short port);           // 1 or 2
short   put_char(         // returns 0 for sucess, 1 for failure
	short port,            // 1 or 2
	unsigned char x);    // byte to be transmitted
void  closeserial(      // closes all serial buffers
	void);
void sendBreak(short port, unsigned short msecs);

