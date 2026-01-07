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
 *		ftp://ftp.trimble.com/pub/sct/embedded/bin
 * *************************************************************************
 *
 * TSIP_ALM.C contains two principal functions, almgetb() and almputb() that
 * get binary 'system data' from the receiver (almanac, health, ionospheric
 * parameters) and load it back into the receiver respectively. Each function
 * issues a sequence of more than 30 commands, and control is not passed back
 * to the main loop until the sequence is finished or aborted.  Reports are
 * intercepted in this function, so they do not pass through the TSIP_RPT.C
 * functions.  The binary data file is named GPSALM.DAT and includes health,
 * ionospheric, UTC, and satellite almanacs -- basically reloading RAM to
 * do quick satellite acquistion, or "warm start", after power to the
 * receiver has been discontinued.
 *
 * There is currently no protection such as checksums against damage to
 * the files.  It is possible for the receiver to "hang" if bad almanac
 * data is uploaded, in which case RAM must be erased by removing power
 * or through a cold start command.  In a system application using these
 * functions, we suggest checksums for data integrity.
 */

#include <conio.h>
#include <stdio.h>

#include "t_struct.h"
#include "t_format.h"
#include "t_parser.h"
#include "tsipincl.h"

static FILE	*almfile;

#define ACK 1
#define DATAOUT 2
#define ALM 2
#define ALH 3
#define ION 4
#define UTC 5
#define EPH 6

TSIPPKT cmd;
short getb (void);
short sendb (unsigned char outbyte);

static void wait_for_report (TSIPPKT *rpt, unsigned char rpt_code)
{
	for (;;) {
		tsip_input_proc (rpt, getb());
		if (rpt->status==TSIP_PARSED_FULL && rpt->code==rpt_code)
		{
			return;
		}
		if (kbhit ()) {
			set_cmd_esc (TRUE);
			return;
		}
	}
}


static void wait_for_58 (TSIPPKT *rpt, unsigned char parm1, unsigned char parm2)
{
	for (;;) {
		tsip_input_proc (rpt, getb());
		if (rpt->status==TSIP_PARSED_FULL &&
			rpt->code==0x58 && rpt->buf[1]==parm1 && rpt->buf[2]==parm2)
		{
			return;
		}
		if (kbhit ()) {
			set_cmd_esc (TRUE);
			return;
		}
	}
}

/**/
static short get_and_store_health (TSIPPKT *rpt)
{
	short
		len;
	unsigned char
		*loadbuf;

	cmd_0x38q (&cmd, 3, 0);
   send_cmd(&cmd, sendb);
	cprintf("Almanac health page, t_oa, wn_oa requested...");
	wait_for_58 (rpt, ALH, 0);
	if (cmd_esc()) {
		return FALSE;
	}
	if ((rpt->buf[0] != 2)) {
		cprintf("Data not available!");
		return FALSE;
	}
	len = rpt->buf[3];
	cprintf ("received, length = %d", len);
	show_crlf ();
	if (rpt->len != (len+4)) {
		cprintf("Length error!");
		return FALSE;
	}

	loadbuf = &rpt->buf[1];
	loadbuf[0] = 0x82;
	loadbuf[1] = 3;
	loadbuf[len+3] = 0x83;
	fwrite (loadbuf, 1, len + 4, almfile);
	return TRUE;
}

static short get_and_store_alm (TSIPPKT *rpt, unsigned char sv)
{
	short
		len;
	unsigned char
		*loadbuf;

	cmd_0x38q (&cmd, 2, sv);
   send_cmd(&cmd, sendb);
	cprintf ("SV %d almanac requested...", sv);
	wait_for_58 (rpt, ALM, sv);
	if (cmd_esc()) {
		return FALSE;
	}
	if ((rpt->buf[0] != 2) || (rpt->buf[1] != 2) || (rpt->buf[2] != sv)) {
		cprintf("Data not available!");
		return FALSE;
	}
	len = rpt->buf[3];
	cprintf ("received, length = %d", len);
	show_crlf ();
	if (rpt->len != (len+4)) {
		cprintf("Length error!");
		return FALSE;
	}

	loadbuf = &rpt->buf[0];
	loadbuf [0] = 0x82;
	loadbuf [len+4] = 0x83;
	fwrite (loadbuf, 1, len+5, almfile);
	return TRUE;
}

static short get_and_store_iono (TSIPPKT *rpt)
{
	short
		len;
	unsigned char
		*loadbuf;

	cmd_0x38q (&cmd, 4, 0);
   send_cmd(&cmd, sendb);
	cprintf("Ionospheric data requested...");
	wait_for_58 (rpt, ION, 0);
	if (cmd_esc()) {
		return FALSE;
	}
	if (rpt->buf[0] != 2) {
		cprintf("Data not available!");
		return FALSE;
	}
	len = rpt->buf[3];
	cprintf ("received, length = %d", len);
	show_crlf ();
	if (rpt->len != (len+4)) {
		cprintf("Length error!");
		return FALSE;
	}

	loadbuf = &rpt->buf[1];
	loadbuf [0] = 0x82;
	loadbuf [1] = 4;
	loadbuf [len+3] = 0x83;
	fwrite (loadbuf, 1, len+4, almfile);
	return TRUE;
}

static short get_and_store_utc(TSIPPKT *rpt)
{
	short
		len;
	unsigned char
		*loadbuf;


	cmd_0x38q (&cmd, 5, 0);
   send_cmd(&cmd, sendb);
	cprintf("UTC time data requested...");
	wait_for_58 (rpt, UTC, 0);
	if (cmd_esc()) {
		return FALSE;
	}
	if (rpt->buf[0] != 2) {
		cprintf("Data not available!");
		return FALSE;
	}
	len = rpt->buf[3];
	cprintf ("received, %d bytes", len);
	show_crlf ();
	if (rpt->len != (len+4)) {
		cprintf("Length error!");
		return FALSE;
	}

	loadbuf = &rpt->buf[1];
	loadbuf [0] = 0x82;
	loadbuf [1] = 5;
	loadbuf [len+3] = 0x83;
	fwrite (loadbuf, 1, len+4, almfile);
	return TRUE;
}

static short fetchall (void)
{
	unsigned char
		sv;
	static TSIPPKT
		rpt;

	/* following two bytes used to be version number */
	fputc (0, almfile);
	fputc (0, almfile);

	if (!get_and_store_health (&rpt)) {
		return FALSE;
	}
	for (sv=1; sv<=32; sv++) {
		if (!get_and_store_alm (&rpt, sv)) {
			return FALSE;
		}
	}
	if (!get_and_store_iono(&rpt)) {
		return FALSE;
	}
	if (!get_and_store_utc(&rpt)) {
		return FALSE;
	}
	return TRUE;
}

short almgetb (void)
{
	static TSIPPKT
		rpt;
	short 	errcode;
	unsigned char
		pos_code, vel_code, time_code, aux_code;

	almfile = fopen("GPSALM.DAT", "wb");
	if (almfile == NULL) {
	  	show_crlf ();
		cprintf("Couldn't open almanac data file!");
		return FALSE;
	}
   show_crlf ();
	cprintf("Almanac data file opened");
	show_crlf ();
	cprintf ("Hit <CR> to abort binary acquisition process");
	show_crlf ();
	cmd_0x35q(&cmd);
   send_cmd(&cmd, sendb);
	wait_for_report (&rpt, 0x55);
	if (cmd_esc()) {
		fclose (almfile);
		return FALSE;
	}
	if (rpt_0x55 (&rpt, &pos_code, &vel_code, &time_code, &aux_code)) {
		fclose (almfile);
		return FALSE;
	}
	cmd_0x35s (&cmd, 0, 0, 0, 0);
   send_cmd(&cmd, sendb);
	errcode = fetchall ();
	cmd_0x35s (&cmd, pos_code, vel_code, time_code, aux_code);
   send_cmd(&cmd, sendb);
	cprintf ("System data load into GPSALM.DAT ended.");
	fclose (almfile);
	return errcode;
}

/**/
/* read from file; load TSIP into receiver; listen for affirmation */
static short read_and_load_data (TSIPPKT *rpt)
{
	short bufch, blklen, svch;
	unsigned char inbuff[265];

	/*  read data block from file  */
	do {
		if (kbhit ()) {
         if (getch () == 0x0D) {
            return FALSE;
         }
      }
		bufch = fgetc(almfile);
		if (bufch == EOF) {
         return FALSE;
      }
	} while (bufch != 0x82);

	inbuff[0] = 2;			/*  'LOAD' operation code  */
	bufch = fgetc(almfile);
	if (bufch == EOF) {
      return FALSE;
   }
	inbuff[1] = bufch;

	switch (inbuff[1]) {
	case 1:
		svch = fgetc(almfile);
		if (svch < 1 || svch > 32) {
         return FALSE;
      }
		inbuff[2] = svch;
		cprintf ("Almanac raw for SV %d   ", svch);
		break;

	case 2:
		svch = fgetc(almfile);
		if (svch < 1 || svch > 32) {
         return FALSE;
	  }
		inbuff[2] = svch;
		cprintf ("Almanac data for SV %d   ", svch);
		break;

	case 3:
		cprintf("Almanac health page, t_oa, wn_oa   ");
		inbuff[2] = 0;
		break;

	case 4:
		cprintf("Ionosphere data   ");
		inbuff[2] = 0;
		break;

	case 5:
		cprintf("UTC time correction data   ");
		inbuff[2] = 0;
		break;

	default:
		cprintf("Unknown data block type!   ");
		return FALSE;
	}

	bufch = fgetc(almfile);
	if (bufch == EOF || bufch < 0 || bufch > 256) {
		return FALSE;
	}
	inbuff[3] = bufch;
	for (blklen = 4; blklen<inbuff[3]+4; blklen++) {
		bufch = fgetc(almfile);
		if (bufch == EOF) {
			return FALSE;
		}
		inbuff[blklen] = bufch;
	}
	bufch = fgetc(almfile);
	if (bufch == EOF) {
		return FALSE;
	}
	if (bufch != 0x83) {
		cprintf("End of block format error!");
		return FALSE;
	}

	/*  send data block to GPS set  */
	cmd_0x38s (&cmd, inbuff[1], inbuff[2], inbuff[3], &inbuff[4]);
   send_cmd(&cmd, sendb);

	wait_for_58 (rpt, inbuff[1], inbuff[2]);
	if (cmd_esc()) {
		return FALSE;
	}
	cprintf(rpt->buf[0]==ACK?"Data block acknowledged":"Data block rejected");
	show_crlf ();
	return TRUE;
}

short almputb (void)
{
	static TSIPPKT
		rpt;
	unsigned char
		pos_code, vel_code, time_code, aux_code;

	if ((almfile = fopen("GPSALM.DAT", "rb")) == NULL) {
		show_crlf ();
		cprintf("Couldn't open almanac data file!");
		return FALSE;
	}
	show_crlf ();
	cprintf("Almanac data file opened");
	show_crlf ();
	cprintf ("Hit <CR> to abort binary load process");
	show_crlf ();
	cmd_0x35q (&cmd);
   send_cmd(&cmd, sendb);
	wait_for_report (&rpt, 0x55);
	if (cmd_esc()) {
		return FALSE;
	}
	if (rpt_0x55 (&rpt, &pos_code, &vel_code, &time_code, &aux_code)) {
		return FALSE;
	}
	/* silence the output */
	cmd_0x35s (&cmd, 0, 0, 0, 0);
   send_cmd(&cmd, sendb);
	do {
	  if (kbhit () && (getch () == 0x0D)) {
         break;
      }
   } while (read_and_load_data (&rpt));
	cprintf ("System data load function ended");
	fclose (almfile);
	cmd_0x35s (&cmd, pos_code, vel_code, time_code, aux_code);
   send_cmd(&cmd, sendb);
	return TRUE;
}
