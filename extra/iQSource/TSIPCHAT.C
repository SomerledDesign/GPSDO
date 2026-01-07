/*
 ***************************************************************************
 *	Trimble part number:  40536
 * *************************************************************************
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
 *		ftp://ftp.trimble.com/pub/sct/embedded/bin
 *
 * *************************************************************************
 *
 * TSIPCHAT.C contains the main() entry function to the TSIPCHAT program.
 * The main() function serves as a model for programs that interface with
 * TSIP-based receivers.  The files required for compilation include:
 *
 *		T_PARSER.H 	-	parser prototypes
 *		T_PARSER.C	-	parses TSIP packets into meaningful data
 *		T_FORMAT.H	-  prototypes for TSIP command generators
 *		T_FORMAT.C	- 	generates TSIP command strings and sends them
 *		T_STRUCT.H	- 	declarations of general TSIP data strustures
 *    TSIPINCL.H  -  prototypes for commands, reports, serial I/O, and utilities
 *    TSIPCHAT.C  -  main program
 *    TSIP_UTL.C  -  user interface functions
 *    TSIP_CMD.C  -  gets input from user and generates commands
 *    TSIP_RPT.C  -  outputs data contained in TSIP packets
 *    TSIP_ALM.C  -  receiver almanacs
 *    T_SERIAL.C  -  serail buffer routines
 *
 * Portability:
 * The TSIPCHAT code is very restrictive and requires a Borland Compiler.
 *
 * *************************************************************************
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <dos.h>		/* for ctrlbrk */
#include <math.h>
#include <signal.h>

#include "t_struct.h"
#include "t_format.h"
#include "t_parser.h"
#include "tsipincl.h"

static short
	new_repeat_report,
	repeat_report_code,  /* report to be repeat-requested */
	nprintchar,				/* character count of ASCII line print */
	tsipfiletype,			/* other choice = AUTOFILE */
	reply [0x200],			/* indexed by rpt.code; >0 if requested by cmd */
	serial_port_hold,
   pc_baud_rate,
   pc_data_bits,
   pc_stop_bits,
   pc_parity,
   pc_change_com;

/* file for recording report data */
static FILE
	*tsipstream = NULL;

/* file name for same */
#define OUTBUFSIZE (25*80)
static char
	tsipfilename[80],
   outbuf[OUTBUFSIZE];
PORT_DEF
	pdef;

void display_panel (char *obuf)
{
	char
   	*obufptr,
      *obufstart;
   obufptr=obuf;
   /* strip leading \n */
   if (*obuf == '\n') obufptr++;
   while (obufptr && *obufptr)
   {
      /* line feed, clear line, & print */
	   cputs ("\r\n");
		clreol();
   	obufstart = obufptr;
      /* look for next \n */
		obufptr = strchr (obufstart, '\n');
      /* if \n exists, create substring */
      if (obufptr)
      {
      	*obufptr = '\0';
      	obufptr++;
      }
		cputs (obufstart);
   }
}

/* serial port interface 'primitives' required by TSIP_IFC.C */
short getb (void)
{
	short this_byte;

	this_byte = get_char (pdef.port);
	if (this_byte != -1)
   {
		if (tsipstream != NULL) fputc (this_byte, tsipstream);
   }
	return this_byte;
}

short sendb (unsigned char outbyte)
{
	return put_char(pdef.port, outbyte);
}

/*
 * three special functions of TSIPCHAT:
 * repeat reports;
 * print non-TSIP characters;
 * hourly file opener.
*/

static void rawprint (short newbyte)
{
	short
		curr_window,
		newlinechar,
		newchar;

	switch (newbyte)
	{
	case '\r': case '\n':
		newlinechar = TRUE;
		newchar = -1;
		break;
	case '$': case '>':
	/* NMEA, TAIP starting characters */
		newlinechar = TRUE;
		newchar = newbyte;
		nprintchar++;
		break;
	default:
		newlinechar = FALSE;
		if (newbyte < 0x20 || newbyte > 0xFF) newchar = ((newchar&0x3F)|0x40);
		else newchar = newbyte;
		nprintchar++;
		break;
	}

	/* Save to reset screen at exit. */
	curr_window = which_window();
	switch_window (AUTOWIN);
	if (newlinechar || nprintchar > 75)
	{
		if (nprintchar) show_crlf();
		nprintchar = 0;
	}
	if (newchar > 0) {
		cprintf ("%c", (char)newchar);
	}
	switch_window (curr_window);
}

static void open_auto_file (double current_time)
{
	static double
		file_start_time = -4000.; /* allows file to open before first fix. */
	short
   	errcode,
		week_num,
		hour_of_week;

	if (tsipfiletype != AUTOFILE) return;
	if (current_time > file_start_time + 3600.) {
		/* open up command window */
		new_cmd_window ();

		file_start_time = current_time - fmod(current_time, 3600.);
      if (tsipstream)
      {
			errcode = fclose (tsipstream);
		   cprintf (errcode ? "File close error, '%s'" : "Closing '%s'.",
         	tsipfilename);
         if (errcode) return;
      }
		week_num = (short) (current_time / WEEK);
		hour_of_week = (short)((current_time - week_num * WEEK) / 3600.);
		sprintf (tsipfilename, "T%03d-%03d.TSP", week_num%1000, hour_of_week);

		tsipstream = fopen (tsipfilename, "wb");
		/* file open failed; loop and ask for new file name. */
		cprintf ((tsipstream==NULL) ? "Could not open '%s'." : "Opened '%s'",
        	tsipfilename);
		show_crlf ();
		/* return to auto-report mode */
		switch_window (AUTOWIN);
	}
}

static void display_tsip_rpt (TSIPPKT *rpt)
{
	short
		ireply;
	float
   	time_of_week;
   short
   	week_num;
   float
   	UTC_offset;
   char
   	*obufptr;

   memset (outbuf, '\0', sizeof (outbuf));
   obufptr = outbuf;

	/* end of packet received, prepare for display */
	ireply = reply_code (rpt);
	if (reply [ireply])
	{
		/*
		** if this report has been requested, print in command window,
		** and decrement the reply request.  There may be 32 requests,
		** one for each SV: e.g., cmd_0x3B.
		*/
      if (repeat_report_code == 0x120) new_repeat_report = TRUE;
		if (ireply==repeat_report_code && new_repeat_report)
      {
			new_cmd_window ();
			/* the following will re-print the header if necessary */
			obufptr += print_msg_table_header (repeat_report_code, obufptr, TRUE);
			new_repeat_report = FALSE;
      }
		else
		{
			switch_window (CMDWIN);
      }
      reply [ireply]--;
   }
	else
	{
		switch_window (AUTOWIN);
   }

	rpt_packet (rpt, obufptr);

   display_panel (outbuf);

	/* refresh repeat code for special display */
   reply [repeat_report_code] = 1;

   /* reset non-TSIP character printer */
   nprintchar = 0;

   /* prevent printing this packet again */
   rpt->status = TSIP_PARSED_EMPTY;

   if (rpt->code == 0x41)
   {
		/* unload rptbuf */
		if (rpt_0x41 (rpt, &time_of_week, &UTC_offset, &week_num)) return;

		/* Check to see if time to open an hourly storage file. */
		open_auto_file((double)time_of_week + (double)week_num*604800.);
   }

}

static void timekeeper (void)
{
	clock_t
		now_clock;
	static clock_t
		last_repeat_clock;
   static TSIPPKT
   	cmd;

 	now_clock = clock();
 	if (now_clock < last_repeat_clock + 2*CLK_TCK) return;

	if (!repeat_report_code) return;

	reply [repeat_report_code] = 1;
	switch (repeat_report_code)
	{
	case 0x41:
		cmd_0x21(&cmd);
		break;
	case 0x47:
		cmd_0x27(&cmd);
		break;
	case 0x4D:
		cmd_0x2D(&cmd);
		break;
	case 0x5A:
		cmd_0x3A(&cmd, 0);
		break;
 	case 0x5C:
		cmd_0x3C(&cmd, 0);
		break;
	case 0x85:
		cmd_0x65(&cmd, 0);
		break;
   case 0x120:
 		last_repeat_clock = now_clock;
   	return;
	default:
		return;
	}
	send_cmd(&cmd, sendb);
   new_repeat_report = TRUE;
 	last_repeat_clock = now_clock;
}

/*
 * The following routine is used in main and any routines requiring
 * user keyboard input.
 * By using this routine, the incoming serial stream is serviced and output on
 * the screen but can be pre-empted by processing of user keystrokes
 * while inputting data.
 */
unsigned char read_rpts_wait_for_kbhit (void)
{
	static TSIPPKT
		rpt;		      /* structure for current incoming TSIP report  */
	short
   	newbyte;
	short
		curr_window;   /* if in dual window configuration, current window */

	/* Current screen state so we are able to reset screen at exit. */
	curr_window = which_window();

	/* do parsing until a kbhit is detected */
	while (!kbhit ()) {
		if (serial_port_hold)
		{
			/* suppress output if the serial port parmeters are being changed */
			continue;
		}

		newbyte = getb();
		tsip_input_proc (&rpt, newbyte);
		if (rpt.status == TSIP_PARSED_FULL)
		{
      	display_tsip_rpt (&rpt);
			/* return to active window if necessary */
			switch_window (curr_window);
		}
		else if (rpt.status == TSIP_PARSED_EMPTY && newbyte>=0)
		{
			/* non-TSIP character printer */
			rawprint (newbyte);
		}

		/* repeat command alarm clock control every two seconds */
      timekeeper();
	}
	repeat_report_code = 0;
	return (getch ());
}  

void change_PC_serial_settings (short baud_code, short databits, short parity_code,
 short stopbits)
{
   pc_baud_rate = baud_code;
   pc_data_bits = databits;
   pc_parity    = parity_code;
   pc_stop_bits = stopbits;

   pc_change_com = TRUE;
}

static short closechat (void)
{
	closeserial ();
	reset_screen ();
	return 0;
}

static void ctrlchandler (short sig)
{
	closechat ();
	exit (sig);
}

static void do_command (unsigned char kbch)
{
	short
		irpt;
	KB_CMD
		kb_cmd;
   TSIPPKT
   	cmd;

	repeat_report_code = 0;

	/* zero out all previous report requests */
	for (irpt=0; irpt < 0x200; irpt++) reply [irpt] = 0;

	/* open up command window */
	new_cmd_window ();

	/* 0x06, 0x07, 0x0C, 0x0D do not generate TSIP commands; */
	/* service them separately. */
	switch (kbch) {
   case 'V':	/* show tsipchat version number and part number */
   	cprintf("TSIPCHAT part number: %s", TSIPCHAT_PARTNUM);
      show_crlf();
      cprintf("TSIPCHAT version:     %s", TSIPCHAT_SOFTNUM);
		break;
	case 0x06:
		/* '^F' - continuous binary file storage control */
		if (tsipstream == NULL)
		{
			tsipfiletype = TSIPFILE;
			open_file_storage (&tsipstream, tsipfilename);
		}
		else
		{
			close_file_storage (&tsipstream, tsipfilename);
		}
		break;

	case 0x07:
		/* '^G' - continuous binary file storage control */
		if (tsipfiletype == TSIPFILE && tsipstream != NULL)
      {
			close_file_storage (&tsipstream, tsipfilename);
		}
		tsipfiletype = AUTOFILE;
		cmd_0x21 (&cmd);
   	send_cmd (&cmd, sendb);
		break;

	case 0x09:
		/* '^I' - change serial port parameters.
		/* When changing serial port settings, suppress TSIP parsing. */
	   serial_port_hold = TRUE;
		if (!set_buf_serial_port (&pdef))
      {
      	initsio (&pdef);
      }
		serial_port_hold = FALSE;
		break;

	case 0x0D:  /* <CR> - just blanks out command window */
		break;

	case 0x17:  /* '^W' - setting continuous report command */
		menu_cmd_prompt (REPEAT_MENU, &kb_cmd);
		if (kb_cmd.kbch != 0x1B)
      {
			repeat_report_code = kb_cmd.replycode;
	      if (repeat_report_code == 0x120)
   	   {
      		cmd_0x35s (&cmd, 0x20, 0, 0, 0);
            send_cmd (&cmd, sendb);
         }
		}
		break;

	case '?':   /* '?' - Keystroke Command List */
		kbch = menu_cmd_prompt (ALL_MENU, &kb_cmd);
		if (kb_cmd.kbch != 0x1B) {
			switch_window (AUTOWIN);
			do_command (kb_cmd.kbch);		/* recursive call */
		}
		break;

	case '!':
		/* Creates a file GPSALM.DAT that contains all information */
		/* required to do a warm start. */
		cprintf ("Transfer GPSALM.DAT from rcvr to PC?");
		clreol ();
		if (!ask_verify_nocmdcrlf ()) break;
		if (!almgetb ()) {
			show_crlf();
			cprintf ("Storage aborted");
		}
		break;

	case '@':
		/* Load a file GPSALM.DAT that contains all information */
		/* required to do a warm start. */
		cprintf ("Transfer GPSALM.DAT from PC to rcvr?");
		clreol ();
		if (!ask_verify_nocmdcrlf ()) break;
		if (!almputb ()) {
			show_crlf();
			cprintf ("Loading aborted");
		}
	   break;

	/* case '~':     */
		/* send a stinger break sequence */
	 /*	cprintf ("Send Break Sequence to rcvr?");
		clreol ();
		if (!ask_verify ()) break;
      pdef.baud_code = BAUD_9600;
      pdef.databits = DATABITS_8;
      pdef.parity_code = NO_PARITY;
      pdef.stopbits = STOPBITS_1;
		initsio (&pdef);
  		sendBreak (pdef.port, 600);
	   break;    */

	case 0x1B:
		/* open up command window */
		highvideo ();
		show_crlf();
		show_crlf();
		cprintf (
"******** Press ESC to exit program; or press any other key to continue *********");
		show_crlf();
		show_crlf();
		normvideo ();
		break;

	case '%':	/* unsigned char string */
		{
			unsigned char cmdbuflen, cmdbuf[21];

			cmdbuflen = ask_hex_string (
         	"TSIP command string (ID, then 0-19 data bytes in Hex): ",
         	cmdbuf, 21);
         if (!cmd_esc())
         {
				cmd_0xxx (&cmd, cmdbuf[0], &cmdbuf[1], cmdbuflen-1);
   	   	send_cmd (&cmd, sendb);
         }
		}
		break;

 /*	case '|':  */	/* unsigned char string */
 /*		{
			char cmdbuflen, cmdbuf[60], i;

			cmdbuflen = ask_char_string ("command characters: ", cmdbuf);
			for (i = 0; i < cmdbuflen; i++) sendb (cmdbuf[i]);
		}
		break;  */

	default: /* normal TSIP commands */
		proc_kbd (&cmd, kbch, reply);
		if (cmd.code)
      {
      	send_cmd (&cmd, sendb);
      }
      if (pc_change_com)
      {
         sleep(1);
         pc_change_com    = FALSE;
         serial_port_hold = TRUE;

         pdef.baud_code   = pc_baud_rate;
         pdef.databits    = pc_data_bits;
         pdef.parity_code = pc_parity;
         pdef.stopbits    = pc_stop_bits;
         initsio (&pdef);

         serial_port_hold = FALSE;
      }
		break;
	}
	/* return to auto-report mode */
	switch_window (AUTOWIN);
}

static short ParseCommandLine (short argc, char *argv[])
{
	short
		iarg, retval;
	char
		argflag, *argptr;

	retval = TRUE;
	/* provisions for command line arguments starting with '-' or '/' */
	for (iarg = 0; iarg < argc; iarg++) {
		argflag = argv[iarg][0];
		if (argflag != '-' && argflag != '/') continue;
      argptr = &argv[iarg][2];
      switch (argv[iarg][1])
      {
      case 'c': case 'C':
			pdef.port = *argptr - '0';
			/* returns TRUE if serial port failure */
         if (pdef.port < 0 || pdef.port > 2) return TRUE;
	      pdef.baud_code = BAUD_9600;
   	   pdef.databits = DATABITS_8;
      	pdef.parity_code = ODD_PARITY;  // jah
	      pdef.stopbits = STOPBITS_1;
			initsio (&pdef);
         retval = FALSE;
         break;
      case 'f': case 'F':
			if (*argptr == '\0')
			{
				tsipfiletype = AUTOFILE;
			}
			else
			{
				strcpy (tsipfilename, argptr);
				open_file_storage (&tsipstream, tsipfilename);
			}
      }
	}
	return retval;
}

/**/
/* ************************************************************** */
/* ****************  main routine for tsiptalk ****************** */
/* ************************************************************** */

void main (short argc, char *argv[])
{
	short
   	i;
	unsigned char
		last_kbch,
		kbch;

   pc_change_com = FALSE;
	new_repeat_report = FALSE;
	repeat_report_code = 0;
	nprintchar = 0;
	tsipfiletype = TSIPFILE;
	for (i=0; i<0x200; i++) reply[i] =0;
	serial_port_hold = FALSE;
	tsipstream = NULL;

	if (ParseCommandLine(argc, argv))
	{
		show_crlf();show_crlf();
		printf ("\nSyntax error. Correct Syntax:");
		printf ("\nTSIPCHAT -c<n> -f<filename>");
		printf ("\nComm Port must be specified by command line argument");
		printf ("\n-c1 for COM1, -c2 for COM2, -c0 for SPDRIVE");
		printf ("\nBinary output file name optional: -f<filename>");
		printf ("\nIf no filename specified, output is divided into hourly files.\n");
		exit(0);
	}

	/* clear screen and start at the bottom */
	initialize_screen ();

	/* initialize two screen setup */
	switch_window (CMDWIN);
	highvideo ();
	cprintf (
		"   TSIPCHAT %s ( for Lassen SQ ), TSIP Receiver Control Interface Software",
		TSIPCHAT_VERNUM);
	show_crlf ();
	cprintf (
		"              (c) Copyright 1993-2002 Trimble Navigation, Ltd.");
	show_crlf ();
	cprintf (
		"               Press '?' to access the Keystroke Command List");
	normvideo ();

	switch_window (AUTOWIN);

	signal (SIGINT, ctrlchandler);

	kbch = last_kbch = 0;

	/* MAIN LOOP:  read bytes from buffered serial port input; */
	/* if kbhit, do corresponding command */
	/* double ESC to quit program */

	for (;;)
	{
		kbch = read_rpts_wait_for_kbhit ();
		if (kbch==0x1B && last_kbch==0x1B) break;
		do_command (kbch);
		last_kbch = kbch;
   }

	closechat ();
}

