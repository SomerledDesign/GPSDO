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
 *
 *
 * TSIP_CMD.C carries the function help_screen() displays the Keystroke
 * Command List in the format (key packet Id description).  For example,
 * (t 0x21 show time) means the keystroke 't' must be pressed in order to
 * request the time the receiver carries whether it is from an upload from
 * the user/computer or from the GPS constellation.  The TSIP commands are
 * displayed in the Keystroke Command List in ascending hexadecimal order.
 *
 * proc_kbd() parses the keyboard inputs and
 * directs processing to the mid-level function specific to the keyboard
 * stroke.  The called function then queries for user parameters and passes
 * them to the appropriate command string generator cmd_0x?? in FORMAT.C.
 * The suffix convention for the command string generator follows:
 *
 *                   cmd_0x??q   -  query
 * 	               cmd_0x??s   -  set
 * 	               cmd_0x??c   -  clear/set to default
 * 	               cmd_0x??e   -  enable
 * 	               cmd_0x??d   -  disable
 *
 * In general, one command code corresponds to one keystroke.
 * *************************************************************************
 *
 */

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "t_struct.h"
#include "t_format.h"
#include "t_parser.h"
#include "tsipincl.h"
/*********************************************************************************************/
/*********************************************************************************************/

#define MAX_KB_CMDS 100

/* Generate Control-letter character */
#define CNTRLKEY ('A'-0x01)
#define cntrl(x) ((x)-CNTRLKEY)
extern char
	*dayname[],
	old_baudnum[]
   , *old_parity_text[]
	, *old_input_ch[]
	, *old_output_ch[]
	, *st_baud_text_app []
	, *able_text2[]
	, *databit_text_app []
	, *dgps_mode_text2[]
	, *dyn_text []
	, *flow_cntrl_text[]
	, *in_out_text[]
	, *parity_text []
	, *port_text []
	, *pos_fix_text[]
	, *protocols_text[]
	, *rcvr_port_text []
	, *req_set_text[]
	, *stopbit_text[]
	, *toggle_text[]
	, *trackmode_text3[]
	, *NMEA_list[];

static short
	  num_replies;

/* Utility to check on sv_prn values */
static short prn_valid (unsigned char sv_prn)
{
	if ((sv_prn > 0) && (sv_prn < 33)) {
	  return TRUE;
   }
	cprintf ("SV number must be between 1 and 32 inclusive");
	return FALSE;
}

/**/
/* ***************  USER-PROMPTING ROUTINES FOR COMMANDS ************** */

/* 0x1D */
static void set_osc_offset (TSIPPKT *pCmd)
{
	float
		offset;
	unsigned char
		op_code;
	static char
		*op_text[2] = {"clear", "set"};

	op_code = pick_one ("Enter operation: ", op_text, 2);
	if (cmd_esc ()) return;

	switch (op_code)
	{
	case 0:
		cmd_0x1Dc (pCmd);
		break;

   case 1:
		offset = ask_dbl ("Set osc offset to (relative to 1575.42 GHz): ");
		if (cmd_esc ()) return;
		cmd_0x1Ds (pCmd, offset);
   	break;
   }
}

/* 0x1E */
static void cold_start (TSIPPKT *pCmd)
{
	static char *reset_text [2] = {
		"Erase RAM, Restart",
		"Erase RAM, Set Lassen SQ to Factory Settings, Restart" };
	short			iResetCode ;

   iResetCode = pick_one ("Enter Reset Type: ", reset_text, 2);
   if (cmd_esc ()) return;
   cmd_0x1E (pCmd, iResetCode ? 0x46 : 0x4B);
}
/**/
/* 0x20 */
static void request_almanac (TSIPPKT *pCmd)
{
	unsigned char
		sv_prn;

	sv_prn = ask_byte ("Enter SV PRN number: ");
   if (!prn_valid (sv_prn)) {
   	set_cmd_esc (TRUE);
   }
	if (cmd_esc ()) return;
	cmd_0x20 (pCmd, sv_prn);
	return;
}

/* 0x22 */
static void set_nav_mode (TSIPPKT *pCmd)
{
	unsigned char
		nav_code;

	nav_code = pick_one ("Enter nav mode: ", pos_fix_text, POS_FIX_TEXT_LEN);
	if (cmd_esc ()) return;
	cmd_0x22 (pCmd, nav_code);
}

/* 0x23 */
static void set_initial_ECEF_position (TSIPPKT *pCmd)
{
	float
		pos_ECEF[3];

	pos_ECEF[0] = ask_dbl ("Enter ECEF x: ");	if (cmd_esc ()) return;
	pos_ECEF[1] = ask_dbl ("Enter ECEF y: ");	if (cmd_esc ()) return;
	pos_ECEF[2] = ask_dbl ("Enter ECEF z: ");	if (cmd_esc ()) return;

	cmd_0x23 (pCmd, pos_ECEF);
	return;
}

/* 0x2A */
static void set_altitude(TSIPPKT *pCmd)
{
	float
		alt;
	unsigned char
		op_code;
	static char
		*op_text[3] = {"query", "set alt", "disable"};

	op_code = pick_one ("Enter operation: ", op_text, 3);
	if (cmd_esc ()) return;

	switch (op_code)
	{
	case 0:
		cmd_0x2Aq(pCmd);
		break;
	case 1:
		alt = ask_dbl("Enter reference altitude: ");
		if (cmd_esc ()) break;
		cmd_0x2As (pCmd, alt) ;
		break;
	case 2:
		cmd_0x2Ad (pCmd);
		break;
	}

	return ;
}

/* 0x2B */
static void set_initial_lla_position (TSIPPKT *pCmd)
{
	float
		lat, lon, alt;

	lat = ask_dbl ("Enter lat (ø, negative for south): ");
	if (cmd_esc ()) return;
	lon = ask_dbl ("Enter lon (ø, negative for west): ");
	if (cmd_esc ()) return;
	alt = ask_dbl ("Enter alt (m): ");
	if (cmd_esc ()) return;

	lat *= D2R;
	lon *= D2R;
	cmd_0x2B (pCmd, lat, lon, alt);
	return;
}

static void set_nav_params (TSIPPKT *pCmd)
{
	unsigned char
		dyn_code, set_req;
	float
		elev_mask, snr, dop_mask, dop_switch;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x2Cq (pCmd);
      return;
   }

	dyn_code = pick_one ("Enter dynamics code: ", dyn_text, DYN_TEXT_LEN);
	if (cmd_esc ()) return;
	elev_mask = ask_dbl ("Enter elev angle mask, -1 for no change: ");
	if (cmd_esc ()) return;
	snr = ask_dbl ("Enter SNR mask, -1 for no change: ");
	if (cmd_esc ()) return;
	dop_mask = ask_dbl ("Enter DOP mask, -1 for no change: ");
	if (cmd_esc ()) return;
	dop_switch = ask_dbl ("Enter DOP switch, -1 for no change: ");
	/* Convert elevation mask to radians */
	elev_mask *= D2R;
	cmd_0x2Cs (pCmd, dyn_code, elev_mask, snr, dop_mask, dop_switch);
	return;
}
/* 0x2E */
static void set_time (TSIPPKT *pCmd)
{
	short
		week_num;
	double
		gpstime;
	float
		time_of_week;
	short	days, hours, minutes;
	float seconds;


	/* set time from PC */
	GPS_time_from_PC (&gpstime);
	if (cmd_esc ()) return;
	week_num = (short) (gpstime/604800.);
	time_of_week = (gpstime - 604800.*week_num);
	cprintf ("GPS week %3d", week_num);
	days = (short)(time_of_week / 86400.0);
	hours = (short)fmod(time_of_week / 3600., 24.);
	minutes =  (short) fmod(time_of_week/60., 60.);
	seconds = fmod(time_of_week, 60.);
	cprintf (" %s %02d:%02d:%05.2f   ", dayname[days], hours, minutes, seconds);
	show_crlf ();
	cmd_0x2E (pCmd, time_of_week, week_num);
	return;
}


/**/
/* 0x31 */
static void set_accurate_ECEF_position (TSIPPKT *pCmd)
{
	float
		pos_ECEF[3];

	cprintf ("CAUTION: Position should be accurate to 50 km");
	show_crlf ();
	pos_ECEF[0] = ask_dbl ("Enter ECEF x: ");
	if (cmd_esc ()) return;
	pos_ECEF[1] = ask_dbl ("Enter ECEF y: ");
	if (cmd_esc ()) return;
	pos_ECEF[2] = ask_dbl ("Enter ECEF z: ");
	if (cmd_esc ()) return;
	cmd_0x31 (pCmd, pos_ECEF);
	return;
}

/* 0x32 */
static void set_accurate_LLA_position (TSIPPKT *pCmd)
{
	float
		lat, lon, alt;

	cprintf ("CAUTION: Position should be accurate to 50 km");
	show_crlf ();
	lat = ask_dbl ("Enter lat (ø, negative for south): ");
	if (cmd_esc ()) return;
	lon = ask_dbl ("Enter lon (ø, negative for west): ");
	if (cmd_esc ()) return;
	alt = ask_dbl ("Enter alt (m): ");
	if (cmd_esc ()) return;
	/* Convert lat and lon to radians */
	lat *= D2R;
	lon *= D2R;
	cmd_0x32 (pCmd, lat, lon, alt);
	return;
}

/* 0x35 */
static void set_IO_options (TSIPPKT *pCmd)
{
	unsigned char
		hexnum, hexbyte[5];
	static char
		*yes_no_text[2] = {"yes", "no"},
		*toggle_text[2] = {"off", "on"},
		*alt_text[2] = {"WGS-84", "MSL   "},
		*prec_text[2] = {"single", "double"},
		*time_text[2] = {"GPS", "UTC"},
		*raw_text[2] = {"raw (unfiltered)", "Doppler-smoothed"},
		*signal_text[2] = {"AMU", "dBHz"};

	short
   	bit0, bit1, bit2, bit3, bit4, bit5,
		pos_code, vel_code, time_code, aux_code;

	unsigned char
   	req_set, do_8f20;

	req_set = pick_one("Command:  ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc()) return;
	if (req_set == 0)
	{
		cmd_0x35q(pCmd) ;
		return;
	}

   /* do_8f20 = pick_one("Output Enabled Superpackets?", yes_no_text, 2);
	if (cmd_esc()) return;
	if (do_8f20==0)
	{
		cmd_0x35s(pCmd, 0x20, 0, 0, 0);
      return;
	}  */

	if (pick_one("Enter full menu?", yes_no_text, 2))
	{
		if (cmd_esc ()) return;
		hexnum = ask_hex_string ("Default is 2 2 0 0: ", hexbyte, 4);
		if (hexnum != 4)
		{
			set_cmd_esc (TRUE);
		}
		else
		{
			pos_code = hexbyte[0];
			vel_code = hexbyte[1];
			time_code = hexbyte[2];
			aux_code = hexbyte[3];
		}
		if (cmd_esc ()) return;
	}
	else
	{ /* position code */
		bit0 = bit1 = bit2 = bit3 = bit4 = bit5 = 0;
		bit0 = pick_one ("ECEF position output: ", toggle_text, 2);
		if (cmd_esc ()) return;
		bit1 = pick_one ("LLA position output: ", toggle_text, 2);
		if (cmd_esc ()) return;
		if (bit1 == 1)
		{
			bit2 = pick_one ("altitude output: ", alt_text, 2);
			if (cmd_esc ()) return;
		}
		else
		{
			bit2 = 0;
		}
		bit3 = pick_one ("altitude input: ", alt_text, 2);
		if (cmd_esc ()) return;
		bit4 = pick_one ("output precision: ", prec_text, 2);
		if (cmd_esc ()) return;
		bit5 = pick_one ("Superpacket output: ", toggle_text, 2);
		if (cmd_esc ()) return;
		pos_code = bit0+(2*bit1)+(4*bit2)+(8*bit3)+(16*bit4)+(32*bit5);

		/* velocity code */
		bit0 = bit1 = bit2 = bit3 = bit4 = bit5 = 0;
		bit0  = pick_one ("ECEF velocity output: ", toggle_text, 2);
		if (cmd_esc ()) return;
		bit1  = pick_one ("ENU velocity output: ", toggle_text, 2);
		if (cmd_esc ()) return;
		vel_code = bit0 + (2 * bit1);

		/* time code */
		bit0 = bit1 = bit2 = bit3 = bit4 = bit5 = 0;
		bit0 = pick_one ("Time tags in: ", time_text, 2);
		if (cmd_esc ()) return;
#if 0
		bit1 = pick_one ("Fix computation time: ", latent_text, 2);
		if (cmd_esc ()) return;
		bit2 = pick_one ("Output time: ", query_text, 2);
		if (cmd_esc ()) return;
		bit3 = pick_one ("Synchronized measmts: ", toggle_text, 2);
		if (cmd_esc ()) return;
		bit4 = pick_one ("Min measmt propagate: ", toggle_text, 2);
		if (cmd_esc ()) return;
#endif
		time_code = bit0 + (2 * bit1) + (4 * bit2) + (8 * bit3) + (16 * bit4);

		/* auxiliary code */
		bit0 = bit1 = bit2 = bit3 = bit4 = bit5 = 0;
		bit0 = pick_one ("Pseudorange output: ", toggle_text, 2);
		if (cmd_esc ()) return;
		if (bit0 == 1) {
			bit1  = pick_one ("Pseudorange quality: ", raw_text, 2);
			if (cmd_esc ()) return;
		}
#if 0
		bit2 = pick_one ("Additional fix status: ", toggle_text, 2);
		if (cmd_esc ()) return;
#endif
		bit3 = pick_one ("Signal strength output units: ", signal_text, 2);
		if (cmd_esc ()) return;
		aux_code = bit0 + (2 * bit1) + (4 * bit2) + (8 * bit3);
	}
	cmd_0x35s (pCmd, pos_code, vel_code, time_code, aux_code);
}

/* 0x38 */
static void request_SV_system_data (TSIPPKT *pCmd)
{
	unsigned char
		type_of_data,
		sv_prn;
	static char
		*type_text[7] = {
      	"",
         "",
         "almanac",
         "health page, t_oa, wn_oa",
         "ionosphere",
         "UTC",
         "ephemeris"};

   /*
	* For loading, a data buffer must be supplied from somewhere
	* with the information to be loaded.  Because misloading of
	* data can cause the receiver to act erratic, the load
	* feature is not implemented here.
	* cmd_0x38s (pCmd, type_of_data, sv_prn, nbytes, databuf);
	*/
	type_of_data = pick_one ("Type of data: ", type_text, 7);
	if (cmd_esc ()) return;

	if ((type_of_data == 2) || (type_of_data == 6)) {
		sv_prn = ask_byte ("Enter SV number: ");
		if (!prn_valid(sv_prn)) set_cmd_esc (TRUE);
		if (cmd_esc ()) return;
	} else {
	  sv_prn = 0;
   }
	cmd_0x38q (pCmd, type_of_data, sv_prn);
}


/* 0x39 */
static void request_disable_or_health_override_list (TSIPPKT *pCmd)
{
	unsigned char
		op_code, sv_prn;
	static char
		*op_text[7] = {"", "enable SV", "disable SV", 
		"list enabled/disabled", "heed SV health",
		"ignore SV health", "list heed/ignore health"};

	op_code = pick_one ("Enter operation code: ", op_text, 7);
	if (cmd_esc ()) return;

	sv_prn = 0;
	if ((op_code != 3) && (op_code != 6)) {
		sv_prn = ask_byte ("Enter SV PRN number or 0 for all:  ");
      if (sv_prn && !prn_valid(sv_prn))
      {
			set_cmd_esc (TRUE);
		}
		if (cmd_esc ()) return;
      num_replies = 0;
	}
	cmd_0x39 (pCmd, op_code, sv_prn);
	return;
}

/* 0x3A */
static void request_raw_msmt_data (TSIPPKT *pCmd)
{
	unsigned char
		sv_prn;

	sv_prn = ask_byte ("Enter SV PRN number or 0 for all: ");
	if (sv_prn) if (!prn_valid (sv_prn)) set_cmd_esc (TRUE);
	if (cmd_esc ()) return;
	cmd_0x3A (pCmd, sv_prn);
	num_replies = (sv_prn)?1:8;
	return;
}

/* 0x3B */
static void request_eph_status (TSIPPKT *pCmd)
{
	unsigned char
		sv_prn;

	sv_prn = ask_byte ("Enter SV PRN number or 0 for all: ");
	if (sv_prn != 0) {
      if (!prn_valid (sv_prn)) {
         set_cmd_esc (TRUE);
      }
   }
	if (cmd_esc ()) return;
	cmd_0x3B (pCmd, sv_prn);
	num_replies = (sv_prn)?1:32;
	return;
}

/* 0x3C */
static void request_track_info (TSIPPKT *pCmd)
{
	unsigned char
		sv_prn;

	sv_prn = ask_byte ("Enter SV PRN number or 0 for all: ");
	if (sv_prn != 0) {
      if (!prn_valid (sv_prn)) {
         set_cmd_esc (TRUE);
      }
   }
	if (cmd_esc ()) return;
	cmd_0x3C (pCmd, sv_prn);
	num_replies = (sv_prn)?1:8;
	return;
}

/* 0x3D */
static short old_set_port_config (
   unsigned char *baud_out,
   unsigned char *baud_inp,
   unsigned char *char_code,
	unsigned char *stopbitcode,
   unsigned char *output_mode,
   unsigned char *input_mode)
{
	short
		i, j;
	char
		prompt[40];
	static char
		*stop_bit_text[3]       =  {"", "1", "2"};

	i = pick_one ("Enter XMT Baud Rate: ", st_baud_text_app, BAUD_TEXT_LEN);
	if (cmd_esc ()) return(0);
	*baud_out = old_baudnum[i];

	i = pick_one ("Enter RCV Baud Rate: ", st_baud_text_app, BAUD_TEXT_LEN);
	if (cmd_esc ()) return(0);
	*baud_inp = old_baudnum[i];

	i = pick_one ("Enter bits/char: ", databit_text_app, 4);
	if (cmd_esc ()) return(0);
	sprintf (prompt, "Enter parity: %s-", databit_text_app[i]);

	j = pick_one (prompt, old_parity_text, 5);
	if (cmd_esc ()) return(0);
	*char_code = i + (j << 2);

	sprintf (prompt, "Enter stop bits: %s-%s-", databit_text_app[i], old_parity_text[j]);
	i = pick_one (prompt, stop_bit_text, 3);
	if (cmd_esc ()) return(0);
	if (i == 1)             /* 0x07 */
		*stopbitcode = 0x07;
	else if (i == 2)        /* 2 stop bits code */
		*stopbitcode = 0x0F;

	i = pick_one ("Enter XMT language: ", old_output_ch, 6);
	if (cmd_esc ()) return(0);
	*output_mode = i;
	i = pick_one ("Enter RCV language: ", old_input_ch, 2);
	if (cmd_esc ()) return(0);
	*input_mode = i;

   return(1);
}

static void set_chan_A (TSIPPKT *pCmd)
{
   unsigned char
   	set_req;
   unsigned char
   	baud_out,
   	baud_inp,
   	char_code,
		stopbitcode,
   	output_mode,
   	input_mode;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x3Dq (pCmd);
      return;
   }

	if ( old_set_port_config (&baud_out, &baud_inp, &char_code,
   	&stopbitcode, &output_mode, &input_mode))
   {
   	cmd_0x3Ds (pCmd, baud_out, baud_inp, char_code,
      	stopbitcode, output_mode, input_mode);
   }
}

/**/
/* 0x62 */
static void set_dgps_mode (TSIPPKT *pCmd)
{
	unsigned char
		dgps_mode,
      set_req;
	static char
		*dgps_mode_text[3] = {"Manual GPS (DGPS off)",
		"Manual DGPS (DGPS Req'd)", "Auto DGPS/GPS"};

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x62q (pCmd);
      return;
   }

	dgps_mode = pick_one ("Enter DGPS mode: ", dgps_mode_text, 3);
	/* dgps_mode other than 0, 1, 2, or 3 results in query */
	if (cmd_esc ()) return;
	cmd_0x62s (pCmd, dgps_mode);
	return;
}

/* 0x65 */
static void request_DGPS_corrections (TSIPPKT *pCmd)
{
	unsigned char
		sv_prn;

	sv_prn = ask_byte ("Enter SV PRN number (0 for all): ");
	if (sv_prn) if (!prn_valid (sv_prn)) set_cmd_esc (TRUE);
	if (cmd_esc ()) return;
	cmd_0x65 (pCmd, sv_prn);
	num_replies = (sv_prn)?1:12;
	return;
}


/**/
/* 0x6E */
static void full_msmt_packet_control (TSIPPKT *pCmd)
{
	unsigned char
		mode,
      subcode,
		interval;

   subcode = 1; /* doesn't matter; receiver all assumees 1 */
	mode = pick_one("Full msmt packet control:  ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc()) return;
	if (mode == 0)
	{
		cmd_0x6Eq(pCmd, subcode);
		return;
	}
	mode = pick_one ("Full msmt packet output:  ", able_text2, ABLE_TEXT_LEN);
	if (cmd_esc()) return;
	if (mode == 0)
	{
		cmd_0x6Ed(pCmd, subcode);
		return;
	}
	interval = ask_byte ("Output interval:  ");
	if (cmd_esc()) return;

	cmd_0x6Es (pCmd, subcode, interval);
	return;
}

static void set_pos_filter_operation (TSIPPKT *pCmd)
{
	unsigned char
		mode,
		dyn_switch,
		static_switch,
		alt_switch,
		extra;

	mode = pick_one("Position filter operation:  ", req_set_text, REQ_SET_TEXT_LEN);

	if (mode == 0)
	{
		cmd_0x70q(pCmd);
		return;
	}

	extra = 0;

	dyn_switch = pick_one ("PV dynamic filter:  ", able_text2, ABLE_TEXT_LEN);
	if (cmd_esc()) return;

	/* If the dynamic filter is off, the static filter will not run, so
		don't confuse user by giving them the option to turn it on */
	if (dyn_switch == 1){
		static_switch = pick_one ("PV static filter:  ", able_text2, ABLE_TEXT_LEN);
		if (cmd_esc()) return;
	}
	alt_switch = pick_one ("Altitude filter:  ", able_text2, ABLE_TEXT_LEN);
	if (cmd_esc()) return;
	show_crlf();

	if (dyn_switch == 0)
   {	/* PV filter off */
		cprintf ("PV filter %s, Altitude filter %s",
			able_text2[dyn_switch], able_text2[alt_switch]);

	}
	else {
		cprintf ("PV dynamic filter %s, PV static filter %s, Altitude filter %s",
			able_text2[dyn_switch], able_text2[static_switch], able_text2[alt_switch]);
	}
	show_crlf();

	cmd_0x70s (pCmd, dyn_switch, static_switch, alt_switch, extra);
	return;
}

/* 0x71 */
static void set_pos_filter_parms (TSIPPKT *pCmd)
{
   /* mode is set to default at program onset; otherwise, mode
	  remembers the last setting (receiver setting at program
	  startup is not known)
   */
	unsigned char
		temp_pf;
	TSIP_POS_FILT_PARMS
		temp_params;
	static unsigned char
		pf;
	const TSIP_POS_FILT_PARMS
		default_params =  {
			.0625, 1, 1, 0, 6, .1, 100., 1.21, 1000000., 2};
	static TSIP_POS_FILT_PARMS
		current_params = {
			.0625, 1, 1, 0, 6, .1, 100., 1.21, 1000000., 2};
	short
		mode;
	static char
		*able_text[5] = {"DISABLE", "DISABLE STATIC ONLY",
			"ENABLE ", "RESET", "CHANGE"};

  	short  set_req;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x71q (pCmd);
      return;
   }

	mode = pick_one ("Position filter: ", able_text, 5);
	temp_params = current_params;
	temp_pf = pf;
	if (cmd_esc ()) return;
	switch (mode) {
	case 0:  /* do not change parameters */
		temp_pf = 0;
		break;

	case 1:  /* do not change parameters */
		temp_pf = 1;
		temp_params.chr5 = 0xFF;
		break;

	case 2:  /* do not change parameters */
		temp_pf = 1;
      temp_params.chr5 = 2;
		break;

	case 3:  /* go back to orig */
		temp_pf = 1;
		temp_params = default_params;
		break;

	case 4:
		temp_pf = 1;
		temp_params.flt1 = ask_dbl ("flt1: ");
		if (cmd_esc ()) return;
		temp_params.chr1 = ask_byte ("chr1: ");
		if (cmd_esc ()) return;
		temp_params.chr2 = ask_byte ("chr2: ");
		if (cmd_esc ()) return;
		temp_params.chr3 = ask_byte ("chr3: ");
		if (cmd_esc ()) return;
		temp_params.chr4 = ask_byte ("chr4: ");
		if (cmd_esc ()) return;
		temp_params.flt2 = ask_dbl ("flt2: ");
		if (cmd_esc ()) return;
		temp_params.flt3 = ask_dbl ("flt3: ");
		if (cmd_esc ()) return;
		temp_params.flt4 = ask_dbl ("flt4: ");
		if (cmd_esc ()) return;
		temp_params.flt5 = ask_dbl ("flt5: ");
		if (cmd_esc ()) return;
		temp_params.chr5 = ask_byte ("chr5 (255 = static filter disabled): ");
		if (cmd_esc ()) return;
	  break;
	}

	pf = temp_pf;
	current_params = temp_params;
	cmd_0x71s (pCmd, pf, &current_params);
}

/* 0x73 */
static void set_altitude_filter_parms (TSIPPKT *pCmd)
{
	float
		time_constant;
	static char
		*mode_text[3] = {"DISABLE", "CHANGE ", "CLEAR  "};
	short
		mode;

  	short  set_req;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x73q (pCmd);
      return;
   }

	mode = pick_one ("Altitude filter: ", mode_text, 3);
	if (cmd_esc ()) return;
	switch (mode) {
	case 0:
		cmd_0x73d (pCmd);
		break;

	case 1:
		time_constant = ask_dbl(
			"Enter altitude time constant (# fixes) (0=default): ");
		if (cmd_esc ()) return;
		cmd_0x73s (pCmd, time_constant);
		break;

	case 2:
		cmd_0x73c (pCmd);
		break;

	}
}

/* 0x77 */
static void set_DGPS_maxage (TSIPPKT *pCmd)
{
	short maxage;

  	short  set_req;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x77q (pCmd);
      return;
   }
   maxage = ask_byte ("Enter Maximum age for differential corrections: ");
	if (cmd_esc ()) return;
   cmd_0x77s (pCmd, maxage);
   return;
}

/* 0x7A */
static void set_NMEA_parameters(TSIPPKT *pCmd)
{

	static char
      prompt_text[15];
	short int
   	set_req, interval ;
	unsigned long
		nmeamask;
   short
   	i;

	set_req = pick_one("Operation:  ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc()) return;
	if (!set_req)
	{
		cmd_0x7A_0q(pCmd);
      return;
	}

	interval = ask_byte("NMEA interval ( 1 - 20 seconds ): ");
	if (cmd_esc()) return;
	for (nmeamask=0, i=0; i<NMEA_MAX_MSG; i++)
	{
     	if (NMEA_list[i][0] == '\0') continue;
		sprintf (prompt_text, "%s msg:  ", NMEA_list[i]);
		if (pick_one(prompt_text, toggle_text, 2)==1)
      {
        	nmeamask |= (1<<i);
      }
		if (cmd_esc()) return;
   }
	cmd_0x7A_0s(pCmd, interval, nmeamask);
}

/* 0x8E03 */
static void set_chan_B (TSIPPKT *pCmd)
{
	short
		set_req;
   unsigned char
   	baud_out,
   	baud_inp,
   	char_code,
		stopbitcode,
   	output_mode,
   	input_mode;


	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	if (!set_req)
	{
		cmd_0x8E03q (pCmd);
      return;
   }

	if ( old_set_port_config (&baud_out, &baud_inp, &char_code,
   	&stopbitcode, &output_mode, &input_mode))
   {
   	cmd_0x8E03s (pCmd, baud_out, baud_inp, char_code,
      	stopbitcode, output_mode, input_mode);
   }
}

/* 0x8E-15 */
static void set_datum (TSIPPKT *pCmd)
{
	short datum_index;

  	short  set_req;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	switch (set_req)
	{
	case 0:
		cmd_0x8E15q (pCmd);
		break;
	case 1:
		datum_index = ask_byte ("Enter Desired Datum index:  ");
		if (cmd_esc ()) return;
#if 0
		/* function does not work in v7.68 */
		datum_index = ask_byte ("Enter Desired Datum index (-1 for custom) :  ");
		if (cmd_esc ()) return;
		if (datum_index == -1)
		{
			double datum_coeffs[5];
			/* Get 5 double values */
			datum_coeffs[0] = ask_dbl("Enter value for DX :");
			datum_coeffs[1] = ask_dbl("Enter value for DY :");
			datum_coeffs[2] = ask_dbl("Enter value for DZ :");
			datum_coeffs[3] = ask_dbl("Enter value for A-axis :");
			datum_coeffs[4] = ask_dbl("Enter value for E-squared :");
			cmd_0x8E15s_2 (pCmd, datum_coeffs);
		}
		else
#endif
		{
			cmd_0x8E15s (pCmd, datum_index);
			return;
		}
	}
}

/* 0x8E19 */
static void set_UTM_status (TSIPPKT *pCmd)	/* obslete; use 8E-17 or -18 */
{
	short set_req;
   static char *status_string[] = {"Enable", "Disable", "Query  "};

   cprintf ("Before enabling UTM, set double/single precision with 0x35 command");
   show_crlf();
	set_req = pick_one ("Select UTM position state: ", status_string, 3);
	if (cmd_esc ()) return;
	switch (set_req) {
	case 0:
		cmd_0x8E19e (pCmd);
		break;

	case 1:
		cmd_0x8E19d (pCmd);
		break;

	case 2:		/* current UTM message enable/disable */
		cmd_0x8E19q (pCmd);
		break;

	default:
		break;
	}
}

/* 0x8E-20 */
static void superpacket_20_control (TSIPPKT *pCmd)
{
	unsigned char
		mode, cmdbuflen, cmdbuf[3];
	static char
		*superpacket_enable[3] = {"off", "on", "query"};


	mode = pick_one ("Superpacket output:  ", superpacket_enable, 3);
	if (mode > 1) {
		cmdbuflen = 1;
		cmdbuf[0] = 0x20;
	}
   else
   {
		cmdbuflen = 2;
		cmdbuf[0] = 0x20;
		cmdbuf[1] = mode;
      num_replies = 0;
	}
	cmd_0x8E (pCmd, cmdbuf, cmdbuflen);
}

/* 0x8E-23 */
static void superpacket_23_control (TSIPPKT *pCmd)
{
	unsigned char
		mode, cmdbuflen, cmdbuf[3];
	static char
		*superpacket_enable[3] = {"off", "on", "query"};


	mode = pick_one ("Superpacket output:  ", superpacket_enable, 3);
	if (mode > 1) {
		cmdbuflen = 1;
		cmdbuf[0] = 0x23;
	}
   else
   {
		cmdbuflen = 2;
		cmdbuf[0] = 0x23;
		cmdbuf[1] = mode;
      num_replies = 0;
	}
	cmd_0x8E (pCmd, cmdbuf, cmdbuflen);
}

/* 0x8E-24 */
static void set_LP_Shutdown (TSIPPKT *pCmd)
{
	short set_req;
   short shutdown_in, shutdown_len;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	switch (set_req)
	{
	case 0:
		cmd_0x8E24q (pCmd);
		break;
	case 1:
		shutdown_in  = ask_byte ("Seconds until graceful shutdown:  ");
		if (cmd_esc ()) return;
      shutdown_len = ask_byte ("Seconds to shutdown for        :  ");
		if (cmd_esc ()) return;
      cmd_0x8E24s (pCmd, shutdown_in, shutdown_len);
      break;
	}
}

/* 0x8E-25 */
static void set_LP_Modes (TSIPPKT *pCmd)
{
	short set_req;
   short mode_mask;
	static char
		*yes_no_text[2] = {"yes", "no"},
		*toggle_text[2] = {"off", "on"};
	short
   	bit0, bit1, bit2, bit3;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	switch (set_req)
	{
	case 0:
		cmd_0x8E25q (pCmd);
		break;
	case 1:
		if (pick_one("Enter full menu? ", yes_no_text, 2))
		{
			if (cmd_esc ()) return;
			mode_mask = ask_byte ("Enter Mode Mask (default is 0): ");
			if (cmd_esc ()) return;
		}
		else
		{ /* position code */
			bit0 = bit1 = bit2 = bit3= 0;
			bit0 = pick_one ("LPSTOP: ", toggle_text, 2);
			if (cmd_esc ()) return;
         bit2 = pick_one ("Scheduled Track: ", toggle_text, 2);
         if (cmd_esc ()) return;
			bit3 = pick_one ("Auto SV Data Collection: ", toggle_text, 2);
			if (cmd_esc ()) return;
			mode_mask = bit0 + (2 * bit1) + (4 * bit2) + (8 * bit3);
      }
      cmd_0x8E25s(pCmd,mode_mask);
      break;
	}
}

/* 0x8E-27 */
static void set_LP_Config (TSIPPKT *pCmd)
{
	short set_req, ST_awake_time;
   unsigned long ST_period;

	set_req = pick_one ("Command: ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc ()) return;
	switch (set_req)
	{
	case 0:
		cmd_0x8E27q (pCmd);
		break;
	case 1:
		ST_period     	 = ask_long ("ST Period                (seconds): ");
		if (cmd_esc ()) return;
      ST_awake_time   = ask_byte ("ST Time to Stay Awake    (seconds): ");
		if (cmd_esc ()) return;
      cmd_0x8E27s (pCmd, ST_period, ST_awake_time);
      break;
	}
}

#define MAX_HBS_TEXT 17
/* 0x8E40 */
static void set_TAIP_cfg (TSIPPKT *pCmd)	/* obsolete; use 8E-17 or -18 */
{
	unsigned char
   	temp,
   	Flags,
      HeartBeatSentence;
   short
      TopOfHourOffset,
      Frequency;
   char
   	VehicleID[5];
   char
   	*FlagsText[8] = {"ID","CS","EC","FR","CR","Unkn","Unkn","Unkn"},
      *HBSentenceText[MAX_HBS_TEXT] = {
      	"AL", "", "CP", "", "", "", "ID", "", "LN", "",
         "", "PV", "", "", "ST", "TM", "VR"};
   short
   	i;

	unsigned char req_set;
	req_set = pick_one("Command:  ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc()) return;
	if (req_set == 0)
	{
		cmd_0x8E40q(pCmd) ;
		return;
	}

   cprintf ("Sentence Flags:");
   show_crlf();
   Flags = 0;
   for (i=0; i<5; i++)
   {
		if (pick_one (FlagsText[i], toggle_text, 2))
      {
      	Flags |= (1<<i);
      }
     	if (cmd_esc ()) return;
	}
   cprintf ("Flags = %2X", Flags);
   show_crlf();
   HeartBeatSentence = pick_one ("Heartbeat Sentence:", HBSentenceText, MAX_HBS_TEXT);
  	if (cmd_esc ()) return;
   TopOfHourOffset = ask_byte ("Top of Hour Offset:");
  	if (cmd_esc ()) return;
   Frequency  = ask_byte ("Frequency:");
  	if (cmd_esc ()) return;
	do
   {
   	temp = ask_char_string ("Vehicle ID (4 chars): ", VehicleID);
   } while (temp && temp != 4);
   VehicleID[4] = 0;
  	if (cmd_esc ()) return;
   cprintf (VehicleID);
   show_crlf();
	cmd_0x8E40s(pCmd,
   	Flags,
      HeartBeatSentence,
      TopOfHourOffset,
      Frequency,
      VehicleID);
}

/**/

static void set_stinger_rcvr_config (TSIPPKT *pCmd)
{
	TSIP_RCVR_CFG
   	TsipBB;
   char
   	*subcode_text[4] = {"0 (preferred)", "", "", "3"};
	static char
		*dgps_mode_text[3] = {"Manual GPS (DGPS off)",
		"Manual DGPS (DGPS Req'd)", "Auto DGPS/GPS"};

	unsigned char req_set;


   TsipBB.bSubcode = pick_one("Subcode:  ", subcode_text, 4);
	if (cmd_esc()) return;

	req_set = pick_one("Command:  ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc()) return;
	if (req_set == 0)
	{
		cmd_0xBBq(pCmd, TsipBB.bSubcode) ;
		return;
	}


	TsipBB.operating_mode = pick_one ("Operating mode:  ", pos_fix_text, POS_FIX_TEXT_LEN);
	if (cmd_esc()) return;
	TsipBB.dgps_mode = pick_one ("DGPS mode:  ", dgps_mode_text, 3);
	if (cmd_esc()) return;
/* not changeable in v7.52 or v7.68
	TsipBB.trackmode = pick_one ("Tracking mode:  ", trackmode_text3, TRACKMODE_TEXT_LEN);
	if (cmd_esc()) return;
*/
	TsipBB.dyn_code = pick_one ("Dynamics code:   ", dyn_text, DYN_TEXT_LEN);
	if (cmd_esc()) return;
	TsipBB.elev_mask = ask_dbl ("Enter elev angle mask (deg, -1 = no change): ");
	if (cmd_esc()) return;
	TsipBB.cno_mask = ask_dbl ("Enter SNR mask (AMUs, -1 = no change):   ");
	if (cmd_esc()) return;
	TsipBB.dop_mask = ask_dbl ("Enter DOP mask (-1 = no change):       ");
	if (cmd_esc()) return;
	TsipBB.dop_switch = ask_dbl ("Enter DOP switch (-1 = no change):     ");
	if (cmd_esc()) return;
	TsipBB.dgps_age_limit = ask_byte ("Enter DGPS age limit (sec):     ");
	if (cmd_esc()) return;
	/* Convert elevation mask to radians. */
	TsipBB.elev_mask *= D2R;

	cmd_0xBBs(pCmd, &TsipBB) ;
}


/* 0xBC */
static void set_rcvr_serial_port_config (TSIPPKT *pCmd)
{
	unsigned char
		port_num,
		baud_rate,
		data_bits,
		parity,
		stop_bits,
		flow_control,
		protocols_in,
		protocols_out,
		reserved,
		temp,
		req_set;

   short pc_parity;

	req_set = pick_one("Command:  ", req_set_text, REQ_SET_TEXT_LEN);
	if (cmd_esc()) return;

	port_num = 0;

   /* Request */
	if (req_set == 0)
	{
		cmd_0xBCq (pCmd, port_num);
		return;
	}

   /* Set */
	cprintf ("Set RECEIVER Port Configuration");
   show_crlf();
	baud_rate = pick_one ("Baud rate: ", st_baud_text_app, BAUD_TEXT_LEN);
	if (cmd_esc()) return;
	data_bits = pick_one ("Data bits: ", databit_text_app, DATABIT_TEXT_LEN);
	if (cmd_esc()) return;
	parity = pick_one ("Parity: ", parity_text, PARITY_TEXT_LEN);
	if (cmd_esc()) return;
	stop_bits = pick_one ("Stop bits: ", stopbit_text, STOPBIT_TEXT_LEN);
	if (cmd_esc()) return;
	flow_control = 0;
	//temp = pick_one ("Protocol in:  ", protocols_text, PROTOCOLS_TEXT_LEN);
   cprintf ("Protocol in: Lassen SQ supports only TSIP for input."
            " Press RETURN to continue.");
	temp = read_rpts_wait_for_kbhit ();
	if (cmd_esc()) return;
	protocols_in = 1 << temp;
   show_crlf();
	temp = pick_one ("Protocol out:  ", protocols_text, PROTOCOLS_TEXT_LEN);
	if (cmd_esc()) return;
	protocols_out = 1 << temp;
	show_crlf();
   reserved = 0;

   cprintf ("Set receiver serial port?");
	if (!ask_verify ()) {
		set_cmd_esc (TRUE);
		return;
	}

   cprintf ("Change PC serial configuration to match?");
   if (ask_verify ()) {
      // modify parity parameters
      if (parity == 1)
         pc_parity = ODD_PARITY;
      else if (parity == 2)
         pc_parity = EVEN_PARITY;
      else
         pc_parity = NO_PARITY;
      change_PC_serial_settings (baud_rate, data_bits, pc_parity, stop_bits);
   }
   if (cmd_esc()) return;

	cmd_0xBCs (pCmd, port_num, baud_rate, baud_rate, data_bits, parity, stop_bits,
		flow_control, protocols_in, protocols_out, reserved);
}

/**/

#define NUM_ALL_CMDS 	60
#define NUM_8E_CMDS 		11
#define NUM_REPEAT_CMDS 10
static short get_menu (short code, KB_CMD **kb_cmd_list)
{
static KB_CMD kb_all_cmd[NUM_ALL_CMDS] = {
	{ 'V', 0x10, 0x00, "show tsipchat ver"},
	{0x17, 0x10, 0x00, "repeat command   "},
	{0x06, 0x10, 0x00, "log TSIP to file "},
	{0x07, 0x10, 0x00, "log TSIP hourly  "},
	{ '%', 0x10, 0x00, "TSIP cmd string  "},
	/*{ '|', 0x10, 0x00, "TAIP cmd string  "},     */
	{ '!', 0x10, 0x00, "download almanac "},
	{ '@', 0x10, 0x00, "upload almanac   "},
   /*{ '~', 0x10, 0x00, "send serial break"},  */
	{0x09, 0x10, 0x00, "set PC serial prt"},
	{ '=', 0x10, 0x00, "Superpkt 8Eh menu"},
 /*	{ 'F', 0x1D, 0x00, "set osc offset   ", set_osc_offset},    */
	{0x0B, 0x1E, 0x45, "clear battery RAM", cold_start},
	{ 'v', 0x1F, 0x45, "show S/W version ", cmd_0x1F},
 /*	{ 'A', 0x20, 0x40, "*show almanac    ", request_almanac},    */
	{ 't', 0x21, 0x41, "show time        ", cmd_0x21},
  /*	{ 'N', 0x22, 0x00, "*set 2D/3D mode  ", set_nav_mode},    */
	{ 'i', 0x23, 0x00, "input XYZ pos    ", set_initial_ECEF_position},
	{ 'M', 0x24, 0x6D, "show 2D/3D mode  ", cmd_0x24},
	{0x12, 0x25, 0x45, "reset receiver   ", cmd_0x25},
	{ 'h', 0x26, 0x46, "receiver health  ", cmd_0x26},
	{ 's', 0x27, 0x47, "show sig levels  ", cmd_0x27},
  /*	{ 'm', 0x28, 0x48, "GPS sys message  ", cmd_0x28},  */
  /*	{ 'a', 0x29, 0x49, "*show alm health ", cmd_0x29}, */
	{0x01, 0x2A, 0x4A, "altitude for 2-D ", set_altitude},
	{ 'I', 0x2B, 0x00, "input LLA pos    ", set_initial_lla_position},
  /*	{ 'P', 0x2C, 0x4C, "*set nav params  ", set_nav_params},    */
	{ 'o', 0x2D, 0x4D, "show osc offset  ", cmd_0x2D},
	{ 'T', 0x2E, 0x4E, "set time from PC ", set_time},
  /*	{ 'u', 0x2F, 0x4F, "*show UTC data   ", cmd_0x2F},    */
	{ 'b', 0x31, 0x00, "set acc ECEF pos ", set_accurate_ECEF_position},
	{ 'B', 0x32, 0x00, "set acc LLA pos  ", set_accurate_LLA_position},
	{ 'O', 0x35, 0x55, "set  I/O options ", set_IO_options},
	{ 'w', 0x37, 0x57, "show last fix    ", cmd_0x37},
	{ '$', 0x38, 0x58, "receive SV data  ", request_SV_system_data},
 /*	{ 'd', 0x39, 0x59, "enable/disable SV", request_disable_or_health_override_list},*/
 /*	{ '<', 0x3A, 0x5A, "*show raw meas   ", request_raw_msmt_data},  */
 /*	{ 'e', 0x3B, 0x5B, "*show eph status ", request_eph_status},  */
	{ '>', 0x3C, 0x5C, "show track status", request_track_info},
  /*	{0x15, 0x3D, 0x3D, "*set port 1      ", set_chan_A},    */
	{ 'D', 0x62, 0x82, "*set DGPS mode   ", set_dgps_mode},
	{ '/', 0x65, 0x85, "show DGPS info   ", request_DGPS_corrections},
 /*	{ 'c', 0x6E, 0x6E, "set raw msmt cntl", full_msmt_packet_control},  */
	{ 'l', 0x70, 0x70, "filter control   ", set_pos_filter_operation},
 /*	{ 'L', 0x71, 0x72, "*set pv fltr prms", set_pos_filter_parms}, */
  /*	{ 'H', 0x73, 0x74, "*set alt fltr prm", set_altitude_filter_parms},  */
 /*	{ 'J', 0x77, 0x78, "*set DGPS max age", set_DGPS_maxage},  */
	{ 'q', 0x7A, 0x7B, "NMEA output cntrl", set_NMEA_parameters},
	{ 'p', 0xBB, 0xBB, "rcvr configure   ", set_stinger_rcvr_config},
	{ 'U', 0xBC, 0xBC, "port configure   ", set_rcvr_serial_port_config},
	{'\0', 0x00, 0x00, "end record       "}
};

static KB_CMD kb_8e_cmd[NUM_8E_CMDS] = {
	{ 'd', 0x15, 0x100 + 0x15, "Datum Index      ", set_datum},
	{ 'f', 0x19, 0x100 + 0x19, "UTM Control      ", set_UTM_status},
	{ 'p', 0x20, 0x100 + 0x20, "Std PosVel spkt  ", superpacket_20_control},
	{ 's', 0x26, 0x100 + 0x26, "Save to NV Memory", cmd_0x8E26s},
	{'\0', 0x00, 0x00, "end record       "}
};

static KB_CMD kb_repeat_cmd[NUM_REPEAT_CMDS] = {
	{ 't', 0x21, 0x41, "show time        "},
	{ 'o', 0x2D, 0x4D, "show osc offset  "},
	{ 's', 0x27, 0x47, "show sig levels  "},
	{ '>', 0x3C, 0x5C, "show track status"},
	{ '/', 0x65, 0x85, "show DGPS info   "},
	{ '=',0x120,0x120, "Pos/Vel fixes    "},
	{'\0', 0x00, 0x00, "end record       "}
};

	switch (code) {
	case REPEAT_MENU:
		*kb_cmd_list = kb_repeat_cmd;
		break;
	case ALL_MENU:
		*kb_cmd_list = kb_all_cmd;
		break;
	case x8E_MENU:
		*kb_cmd_list = kb_8e_cmd;
		break;
	default:
		return 1;
	}
	return 0;
}

/* list of keyboard strokes and command each invokes */
/* When '?' is pressed, a command list is displayed and a FALSE is   */
/* returned. When unrecognized keystroke is entered, error message   */
/* appears and a FALSE is returned. Otherwise, the command code gets */
/* loaded and a TRUE is returned.                                    */
void display_cmds (short code)
{
	short
		icmd, icol, irow, col_len,
		num_kb_cmds;
	KB_CMD
		*kb_cmd_list,
      *kb_cmd;

	get_menu (code, &kb_cmd_list);
	highvideo ();
	cprintf ("Keystroke Command List (Key Pkt-ID Description):");
	normvideo ();
	textcolor (LIGHTGRAY);
	textbackground (BLUE);
	clreol ();
	for (icmd=0; icmd < MAX_KB_CMDS; icmd++)
	{
		if (!kb_cmd_list[icmd].cmdcode) break;
	}
	if (icmd == MAX_KB_CMDS)
	{
		show_crlf();
		cprintf ("Menu too large or not terminated!");
	}
	num_kb_cmds = icmd;
	col_len = (num_kb_cmds + 2) / 3;
	for (irow = 0; irow < col_len; irow++) {
		show_crlf ();
		for (icol = 0; icol < 3; icol++) {
			icmd = irow + (col_len * icol);
			if (icmd >= num_kb_cmds) break;
         kb_cmd = &kb_cmd_list[icmd];
		   if (kb_cmd->cmdcode == 0x10)
         {
         	highvideo ();
	         if (kb_cmd->kbch <= cntrl('Z'))
   	      {
	     	   	cprintf (" ^%c", kb_cmd->kbch+CNTRLKEY);
	         }
   	      else
      	   {
         		cprintf ("  %c", kb_cmd->kbch);
	         }
     	   	cprintf ("  --  %s", kb_cmd->cmdtext);
			   normvideo ();
				textcolor (LIGHTGRAY);
				textbackground (BLUE);
         }
         else if (kb_cmd->kbch <= cntrl('Z'))
         {
         	cprintf (" ^%c 0x%2.2X %s", kb_cmd->kbch + CNTRLKEY,
            	kb_cmd->cmdcode, kb_cmd->cmdtext);
         }
         else
         {
         	cprintf ("  %c 0x%2.2X %s", kb_cmd->kbch,
            	kb_cmd->cmdcode, kb_cmd->cmdtext);
         }
		}
	}
	show_crlf ();
}

static void confirm_keystroke (short code, KB_CMD *kb_cmd)
{
	KB_CMD
		*kb_cmd_list;
	unsigned char
		kbch;
	short
		ikb;

	kbch = kb_cmd->kbch;
	get_menu (code, &kb_cmd_list);
	for (ikb = 0; ikb < MAX_KB_CMDS && kb_cmd_list[ikb].cmdcode; ikb++) {
		if (kbch == kb_cmd_list[ikb].kbch) {
			clreol ();
			*kb_cmd = kb_cmd_list[ikb];
         if (kb_cmd->kbch <= cntrl('Z'))
         {
         	cprintf (" '^%c' 0x%2.2X %s", kb_cmd->kbch + CNTRLKEY,
            	kb_cmd->cmdcode, kb_cmd->cmdtext);
         }
         else
         {
         	cprintf (" ' %c' 0x%2.2X %s", kb_cmd->kbch,
            	kb_cmd->cmdcode, kb_cmd->cmdtext);
         }
         if (kb_cmd->cmdtext[0] == '*')
         {
         	cprintf ("  (old form; newer command preferred)");
         }
			show_crlf ();
			return;
		}
	}
	if (ikb == MAX_KB_CMDS)
	{
		show_crlf();
		cprintf ("Menu too large or not terminated!");
	}
	if (isprint (kbch) || ((kbch >= cntrl('A')) && (kbch <= cntrl('Z')))) {
		cprintf ("Keystroke Unknown");
	}
	clreol ();
	kb_cmd->kbch = 0x1B;
	kb_cmd->cmdcode = 0;
	kb_cmd->replycode = 0;
}

short menu_cmd_prompt (short code, KB_CMD *kb_cmd)
{
	start_menu_window ();
	display_cmds (code);
   highvideo ();
	cprintf ("Enter Keystroke: ");
   normvideo ();
   textcolor (LIGHTGRAY);
   textbackground (BLUE);
	kb_cmd->kbch = read_rpts_wait_for_kbhit ();
	confirm_keystroke (code, kb_cmd);
	end_menu_window ();
	return (kb_cmd->kbch == 0x1B);
}

/* returns TRUE if a command is to be sent to the receiver; otherwise   */
/* a FALSE is returned                                                  */
void proc_kbd (TSIPPKT *pCmd, unsigned char kbch, short *reply)
{
	KB_CMD
		kb_cmd;

	num_replies = 1;
   pCmd->code = 0;
	set_cmd_esc (FALSE);
	if (kbch == '=')
   {
		menu_cmd_prompt (x8E_MENU, &kb_cmd);
   }
   else
   {
		kb_cmd.kbch = kbch;
		confirm_keystroke (ALL_MENU, &kb_cmd);
   }

	if (kb_cmd.kbch == 0x1B) {
		return;
	}
   kb_cmd.cmdfn (pCmd);
	if (cmd_esc ()) {
		show_crlf ();
		cprintf ("-- aborted --");
	}
	else
	{
		clreol ();
		/* general case; display the message if a report has been requested */
		if (kb_cmd.replycode) {
			reply[kb_cmd.replycode] = num_replies;
         if (num_replies)
         {
				switch (kb_cmd.replycode) {
				case 0x6D:
					reply [0x44] = 1;
					break;

				case 0x46:
					reply [0x4B] = 1;
					break;

				case 0x57:
					reply [0x42] = reply [0x83] = reply [0x4A] =
					reply [0x84] = reply [0x43] = reply [0x56] =
					reply [0x120] = reply [0x117] = reply [0x118] = 1;
					break;
				}
				if (kb_cmd.replycode > 0x100)
				{
					cprintf ("...waiting for reply (0x8F-%X)\r",
						kb_cmd.replycode - 0x100);
				}
				else
				{
					cprintf ("...waiting for reply (0x%X)\r",
						kb_cmd.replycode);
				}
         }
		}
	}
}


