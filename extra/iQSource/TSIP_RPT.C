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
 * *************************************************************************
 *
 * TSIP_RPT.C consists of a primary function rpt_packet() called by main().
 * This function takes a character buffer that has been received as a report
 * from a TSIP device and interprets it.  The character buffer has been
 * assembled using tsip_input_proc() in T_PARSER.C.
 *
 * A large case statement directs processing to one of many mid-level
 * functions.  The mid-level functions specific to the current report
 * code passes the report buffer to the appropriate report decoder
 * rpt_0x?? () in T_PARSER.C, which outputs the variable values in the
 * report buffer rpt.buf.
 *
 * *************************************************************************
 *
 */

#include <stdio.h>
#include <math.h>
#include "t_struct.h"
#include "t_format.h"
#include "t_parser.h"
#include "tsipincl.h"

char
	*dayname[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"},
	 old_baudnum[BAUD_TEXT_LEN]       =
   	{0, 1, 4, 5, 6, 8, 9, 11, 28, 12},
   *st_baud_text_app [BAUD_TEXT_LEN] =
		{"", "", "", "", "",	"", "4800", "9600", "19200", "38400"},
	*databit_text_app [DATABIT_TEXT_LEN] =
		{"", "", "", "8"},
	*stopbit_text[STOPBIT_TEXT_LEN] =
		{"1", "2"},
	*old_parity_text[5]         =
   	{"EVEN", "ODD", "", "", "NONE"},
	*parity_text [PARITY_TEXT_LEN] =
		{"NONE", "ODD", "EVEN"},
	*old_input_ch[MAX_INPUT_MODE]    =
   	{"TSIP", "RTCM (6 bit)"},
	*old_output_ch[MAX_OUTPUT_MODE]  =
   	{"TSIP",	"No output", "", "",	"", "NMEA 0183"},
	*protocols_text[PROTOCOLS_TEXT_LEN] =
		{"", "TSIP ", "NMEA ", "", ""},
	*rcvr_port_text [RCVR_PORT_TEXT_LEN] =
		{"Port 1", "Port 2", "Current Port"},
	*able_text2[ABLE_TEXT_LEN] 	=
		{"DISABLE", "ENABLE "},
	*dgps_mode_text2[DGPS_MODE_TEXT_LEN] =
		{"manual GPS (DGPS off)",
       "manual DGPS (DGPS req'd)",
       "auto DGPS/GPS",
		 "auto DGPS/GPS",
       ""},
	*dyn_text [DYN_TEXT_LEN] =
		{"Unchanged", "Land", "Sea", "Air", "Static"},
	*pos_fix_text[POS_FIX_TEXT_LEN] =
		{"automatic", "", "", "2-D",
			"3-D"},
	*req_set_text[REQ_SET_TEXT_LEN] =
		{"Request", "Set"},
	*toggle_text[TOGGLE_TEXT_LEN] =
		{"off", "on"},
	*trackmode_text3[TRACKMODE_TEXT_LEN] =
		{"mode unchanged", "over-determined 8", "weighted over-determined 8"},
   *NMEA_list[NMEA_MAX_MSG] =
     {"GGA", "GLL", "VTG", "GSV", "GSA", "ZDA", "", "", "RMC"}
;

#define GOOD_PARSE 0
#define BADID_PARSE 1
#define BADLEN_PARSE 2
static short
	parsed;
static char
	*pbuf;

/* convert time of week into day-hour-minute-second and print */
char* show_time (float time_of_week)
{
	short	days, hours, minutes;
	float seconds;
	double tow;
   static char timestring [80];

	if (time_of_week == -1.0)
   {
		sprintf(timestring, "   <No time yet>   ");
	}
	else if ((time_of_week >= 604800.0) || (time_of_week < 0.0))
   {
		sprintf(timestring, "     <Bad time>     ");
	}
   else
   {
		tow = time_of_week;
		days = (short)(tow / 86400.0);
		hours = (short)fmod(tow / 3600., 24.);
		minutes =  (short) fmod(tow/60., 60.);
		seconds = (float)fmod(tow, 60.);
		sprintf(timestring, " %s %02d:%02d:%05.2f   ",
      	dayname[days], hours, minutes, seconds);
   }
   return timestring;
}

/**/
/* 0x3D */
static void old_show_port_config (
	unsigned char tx_baud_index,
   unsigned char rx_baud_index,
	unsigned char char_format_index,
	unsigned char stop_bits,
  	unsigned char tx_mode_index,
   unsigned char rx_mode_index)
{
   unsigned char databits;
   unsigned char parity;
	short
		i;

	for (i = 0; i < 10; ++i) { /* 10 baud choices */
		if (tx_baud_index == old_baudnum[i]) break;
	}
	pbuf += sprintf(pbuf, "\n   Transmit speed: %s at %s",
		(tx_mode_index>=MAX_OUTPUT_MODE)?"undefined":old_output_ch[tx_mode_index],
      (i > 9) ? "undefined" : st_baud_text_app[i]);
	for (i = 0; i < 10; ++i) { /* 10 baud choices */
		if (rx_baud_index == old_baudnum[i]) break;
	}
	pbuf += sprintf(pbuf, "\n   Receive speed: %s at %s",
		(rx_mode_index>=MAX_INPUT_MODE)?"undefined":old_input_ch[rx_mode_index],
      (i > 9) ? "undefined" : st_baud_text_app[i]);
	databits = (char_format_index & 0x03) + 5;
	parity = char_format_index >> 2;
	if (parity > 4) parity = 2;
	pbuf += sprintf(pbuf, "\n   Character format (bits/char, parity, stop bits): %d-%s-%d",
		databits, old_parity_text[parity], stop_bits);
}

static void show_chan_A_config (TSIPPKT *rpt)
{
	unsigned char
		tx_baud_index, rx_baud_index,
		char_format_index, stop_bits,
      tx_mode_index, rx_mode_index;

	/* unload rptbuf */
	if (rpt_0x3D (rpt,
		&tx_baud_index, &rx_baud_index, &char_format_index,
		&stop_bits, &tx_mode_index, &rx_mode_index)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nChannel A Configuration");
	old_show_port_config (tx_baud_index, rx_baud_index, char_format_index,
		stop_bits, tx_mode_index, rx_mode_index);
}

/**/
/* 0x40 */
static void rpt_almanac_data_page (TSIPPKT *rpt)
{
	unsigned char
		sv_prn;
	short
		week_num;
	float
		t_zc,
		eccentricity,
		t_oa,
		i_0,
		OMEGA_dot,
		sqrt_A,
		OMEGA_0,
		omega,
		M_0;

	/* unload rptbuf */
	if (rpt_0x40 (rpt,
		&sv_prn, &week_num, &t_zc, &eccentricity, &t_oa,
		&i_0, &OMEGA_dot, &sqrt_A, &OMEGA_0, &omega, &M_0)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nAlmanac for SV %02d", sv_prn);
	pbuf += sprintf(pbuf, "\n       Captured:%15.0f %s",
   	t_zc, show_time (t_zc));
	pbuf += sprintf(pbuf, "\n           week:%15d", week_num);
	pbuf += sprintf(pbuf, "\n   Eccentricity:%15g", eccentricity);
	pbuf += sprintf(pbuf, "\n           T_oa:%15.0f %s",
   	t_oa, show_time (t_oa));
	pbuf += sprintf(pbuf, "\n            i 0:%15g", i_0);
	pbuf += sprintf(pbuf, "\n      OMEGA dot:%15g", OMEGA_dot);
	pbuf += sprintf(pbuf, "\n         sqrt A:%15g", sqrt_A);
	pbuf += sprintf(pbuf, "\n        OMEGA 0:%15g", OMEGA_0);
	pbuf += sprintf(pbuf, "\n          omega:%15g", omega);
	pbuf += sprintf(pbuf, "\n            M 0:%15g", M_0);
}

/* 0x41 */
static void rpt_GPS_time (TSIPPKT *rpt)
{
	float
		time_of_week, UTC_offset;
	short
		week_num;

	/* unload rptbuf */
	if (rpt_0x41 (rpt, &time_of_week, &UTC_offset, &week_num)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nGPS time:%s GPS week: %d   UTC offset %.1f",
   	show_time(time_of_week), week_num, UTC_offset);

}

/* 0x42 */
static void rpt_single_ECEF_position (TSIPPKT *rpt)
{
	float
		ECEF_pos[3], time_of_fix;

	/* unload rptbuf */
	if (rpt_0x42 (rpt, ECEF_pos, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nSXYZ:  %15.0f  %15.0f  %15.0f    %s",
		ECEF_pos[0], ECEF_pos[1], ECEF_pos[2],
      show_time(time_of_fix));
}

/* 0x43 */
static void rpt_single_ECEF_velocity (TSIPPKT *rpt)
{

	float
		ECEF_vel[3], freq_offset, time_of_fix;

	/* unload rptbuf */
	if (rpt_0x43 (rpt, ECEF_vel, &freq_offset, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nVelECEF: %11.3f  %11.3f  %11.3f  %12.3f%s",
		ECEF_vel[0], ECEF_vel[1], ECEF_vel[2], freq_offset,
      show_time(time_of_fix));
}

/*  0x45  */
static void rpt_SW_version (TSIPPKT *rpt) {
	unsigned char
		major_nav_version, minor_nav_version,
		nav_day, nav_month, nav_year,
		major_dsp_version, minor_dsp_version,
		dsp_day, dsp_month, dsp_year;

	/* unload rptbuf */
	if (rpt_0x45 (rpt,
		&major_nav_version, &minor_nav_version,
		&nav_day, &nav_month, &nav_year,
		&major_dsp_version, &minor_dsp_version,
		&dsp_day, &dsp_month, &dsp_year)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf,
"\nFW Versions:  Nav Proc %2d.%02d  %2d/%02d/%2d  Sig Proc %2d.%02d  %2d/%02d/%2d",
		major_nav_version, minor_nav_version, nav_day, nav_month, nav_year+2000,
		major_dsp_version, minor_dsp_version, dsp_day, dsp_month, dsp_year+2000);
}

/* 0x46 */
#define MAX_SC_MESSAGE 13
#define MAX_EC_MESSAGE 6
static void rpt_rcvr_health (TSIPPKT *rpt)
{
	unsigned char
		status_code, error_code;
	short
		i;
	const char
		*sc_text[MAX_SC_MESSAGE] = {
		"Doing position fixes",
		"Don't have GPS time yet",
		"Waiting for almanac collection",
		"DOP too high          ",
		"No satellites available",
		"Only 1 satellite available",
		"Only 2 satellites available",
		"Only 3 satellites available",
		"No satellites usable   ",
		"Only 1 satellite usable",
		"Only 2 satellites usable",
		"Only 3 satellites usable",
		"Chosen satellite unusable"},

		*ec_text[MAX_EC_MESSAGE] = {
		"RAM cleared at power-up",
		"Signal processor error ",
		"Channel 1 Misalignment ",
		"Channel 2 Misalignment ",
		"Antenna line fault: ",
		"Antenna short indicator"};


	/* unload rptbuf */
	if (rpt_0x46 (rpt, &status_code, &error_code))
	{
		parsed = BADLEN_PARSE;
		return;
	}

	if (status_code > MAX_SC_MESSAGE)
	{
		pbuf += sprintf(pbuf, "\nUnknown status code 0x%02X", status_code);
	}
	else
	{
		pbuf += sprintf(pbuf, "\nRcvr status code = 0x%02X (%s)",
      	status_code,
      	sc_text[rpt->buf[0]]);
   }
	pbuf += sprintf(pbuf, "\nReceiver health byte          (0x%02X)", error_code);
	for (i = 0; i < MAX_EC_MESSAGE; i++) {
		if (error_code & (1 << i)) {
      	if (i != 4) {
				pbuf += sprintf(pbuf, "\n   %s    (0x%02X)", ec_text[i], (1<<i));
         }
         else {
				pbuf += sprintf(pbuf, "\n   %s", ec_text[i]);
         	if (error_code & (1 << (i+1)))
         		pbuf += sprintf(pbuf," short");
         	else
         		pbuf += sprintf(pbuf," open ");
				pbuf += sprintf(pbuf, " (0x%02X)", (1<<i));
         }
		}
	}
}

/* 0x47 */
static void rpt_SNR_all_SVs (TSIPPKT *rpt)
{
	unsigned char
		nsvs, sv_prn[12];
	short
		isv;
	float
		snr[12];

	/* unload rptbuf */
	if (rpt_0x47 (rpt, &nsvs, sv_prn, snr)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nSNR for satellites: %d", nsvs);
	for (isv = 0; isv < nsvs; isv++) {
		pbuf += sprintf(pbuf, "\n    SV %02d   %6.2f", sv_prn[isv], snr[isv]);
	}
}

/* 0x48 */
static void rpt_GPS_system_message (TSIPPKT *rpt)
{
	unsigned char
		message[23];

	/* unload rptbuf */
	if (rpt_0x48 (rpt, message)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nGPS message: %s", message);
}

/* 0x49 */
static void rpt_almanac_health_page (TSIPPKT *rpt)
{
	short
		iprn;
	unsigned char
		sv_health [32];

	/* unload rptbuf */
	if (rpt_0x49 (rpt, sv_health)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nAlmanac health page:");
	for (iprn = 0; iprn < 32; iprn++) {
		if (!(iprn%5)) *pbuf++ = '\n';
		pbuf += sprintf(pbuf, "    SV%02d  %2X", (iprn+1) , sv_health[iprn]);
	}
}

/* 0x4A */
static void rpt_single_lla_position (TSIPPKT *rpt) {
	short
		lat_deg, lon_deg;
	float
		lat, lon,
		alt, clock_bias, time_of_fix;
	double lat_min, lon_min;
	unsigned char
		north_south, east_west;

	if (rpt_0x4A (rpt,
		&lat, &lon, &alt, &clock_bias, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	/* convert from radians to degrees */
	lat *= (float)R2D;
	north_south = 'N';
	if (lat < 0.0) {
		north_south = 'S';
		lat = -lat;
	}
	lat_deg = (short)lat;
	lat_min = (lat - lat_deg) * 60.0;

	lon *= (float)R2D;
	east_west = 'E';
	if (lon < 0.0) {
		east_west = 'W';
		lon = -lon;
	}
	lon_deg = (short)lon;
	lon_min = (lon - lon_deg) * 60.0;

	pbuf += sprintf(pbuf, "\nSLLA: %4d: %06.3f  %c%5d:%06.3f  %c%10.2f  %12.2f%s",
		lat_deg, lat_min, north_south,
		lon_deg, lon_min, east_west,
		alt, clock_bias,
		show_time(time_of_fix));
}

/* 0x4A */
static void rpt_ref_alt (TSIPPKT *rpt) {

	float
		alt, dummy;
	unsigned char
		alt_flag;

	if (rpt_0x4A_2 (rpt,
		&alt, &dummy, &alt_flag)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nReference Alt:   %.1f m;    %s", alt, alt_flag?"ON":"OFF");
}

/* 0x4B */
#define MAX_AS1_MESSAGE 4
#define MAX_MID_MESSAGE 41
static void rpt_rcvr_id_and_status (TSIPPKT *rpt)
{
	const char
		*as1_text[MAX_AS1_MESSAGE] = {
		"",
		"No RTC Timeset at power-up",
		"",
		"Almanac not complete      "} ;

	unsigned char
		machine_id, status_1, status_2;
	short
		imsg;

	/* unload rptbuf */
	if (rpt_0x4B (rpt, &machine_id, &status_1, &status_2)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nMachine/Code ID: %d   Status: (0x%02X) %s",
   	machine_id, status_1, (status_2 & 0x01) ? "  Superpkts supported":"");
	for (imsg = 0; imsg < MAX_AS1_MESSAGE; imsg++) {
		if (status_1 & (1 << imsg)) {
			pbuf += sprintf(pbuf,
         "\n   %s (0x%02X)", as1_text[imsg], (1<<imsg));
		}
	}
}

/* 0x4C */
static void rpt_operating_parameters (TSIPPKT *rpt)
{
	unsigned char
		dyn_code;
	float
		el_mask, snr_mask, dop_mask, dop_switch;

	/* unload rptbuf */
	if (rpt_0x4C (rpt, &dyn_code, &el_mask,
		&snr_mask, &dop_mask, &dop_switch)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nOperating Parameters:");
	pbuf += sprintf(pbuf, "\n     Dynamics code = %d %s", dyn_code,
		(dyn_code < DYN_TEXT_LEN)?
		dyn_text[dyn_code] : "unknown dynamics code");
	pbuf += sprintf(pbuf, "\n     Elevation mask = %.2fø", el_mask * R2D);
	pbuf += sprintf(pbuf, "\n     SNR mask = %.2f", snr_mask);
	pbuf += sprintf(pbuf, "\n     DOP mask = %.2f", dop_mask);
	pbuf += sprintf(pbuf, "\n     DOP switch = %.2f", dop_switch);
}

/* 0x4D */
static void rpt_oscillator_offset (TSIPPKT *rpt)
{
	float
		osc_offset;

	/* unload rptbuf */
	if (rpt_0x4D (rpt, &osc_offset)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nOscillator offset: %.2f Hz = %.3f PPM",
   	osc_offset, osc_offset/1575.42);
}

/* 0x4E */
static void rpt_GPS_time_set_response (TSIPPKT *rpt)
{

	unsigned char
		response;

	/* unload rptbuf */
	if (rpt_0x4E (rpt, &response)) {
		parsed = BADLEN_PARSE;
		return;
	}

	switch (response) {
	case 'Y':
		pbuf += sprintf(pbuf, "\nTime set accepted");
		break;

	case 'N':
		pbuf += sprintf(pbuf, "\nTime set rejected or not required");
		break;

	default:
		pbuf += sprintf(pbuf, "\nTime set response error");
	}
}

/* 0x4F */
static void rpt_UTC_offset (TSIPPKT *rpt)
{
	double
		a0;
	float
		a1, time_of_data;
	short
		dt_ls, wn_t, wn_lsf, dn, dt_lsf;

	/* unload rptbuf */
	if (rpt_0x4F (rpt, &a0, &a1, &time_of_data,
		&dt_ls, &wn_t, &wn_lsf, &dn, &dt_lsf)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nUTC Correction Data");
	pbuf += sprintf(pbuf, "\n   A_0         = %g  ", a0);
	pbuf += sprintf(pbuf, "\n   A_1         = %g  ", a1);
	pbuf += sprintf(pbuf, "\n   delta_t_LS  = %d  ", dt_ls);
	pbuf += sprintf(pbuf, "\n   t_ot        = %.0f  ", time_of_data);
	pbuf += sprintf(pbuf, "\n   WN_t        = %d  ", wn_t );
	pbuf += sprintf(pbuf, "\n   WN_LSF      = %d  ", wn_lsf );
	pbuf += sprintf(pbuf, "\n   DN          = %d  ", dn );
	pbuf += sprintf(pbuf, "\n   delta_t_LSF = %d  ", dt_lsf );
}

/**/
/* 0x54 */
static void rpt_1SV_bias (TSIPPKT *rpt)
{
	float
		clock_bias, freq_offset, time_of_fix;

	/* unload rptbuf */
	if (rpt_0x54 (rpt, &clock_bias, &freq_offset, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf (pbuf, "\nTime Only Mode   Bias: %6.2f   Bias Rate: %6.2f%s",
		clock_bias, freq_offset, show_time (time_of_fix));
}

/* 0x55 */
static void rpt_io_opt (TSIPPKT *rpt)
{
	unsigned char
		pos_code, vel_code, time_code, aux_code;

	/* unload rptbuf */
	if (rpt_0x55 (rpt,
		&pos_code, &vel_code, &time_code, &aux_code)) {
		parsed = BADLEN_PARSE;
		return;
	}
	/* rptbuf unloaded */

	pbuf += sprintf(pbuf, "\nI/O Options:%2X%2X%2X%2X",
		pos_code, vel_code, time_code, aux_code);

	if (pos_code & 0x01) {
		pbuf += sprintf(pbuf, "\n    ECEF XYZ position output");
	}

	if (pos_code & 0x02) {
		pbuf += sprintf(pbuf, "\n    LLA position output");
	}

	pbuf += sprintf(pbuf, (pos_code & 0x04)?
		"\n    MSL altitude output (Geoid height) ":
		"\n    WGS-84 altitude output");

	pbuf += sprintf(pbuf, (pos_code & 0x08)?
		"\n    MSL altitude input":
      "\n    WGS-84 altitude input");

	pbuf += sprintf(pbuf, (pos_code & 0x10)?
		"\n    Double precision":
      "\n    Single precision");

	if (pos_code & 0x20) {
		pbuf += sprintf(pbuf, "\n    All Enabled Superpackets");
	}

	if (vel_code & 0x01) {
		pbuf += sprintf(pbuf, "\n    ECEF XYZ velocity output");
	}

	if (vel_code & 0x02) {
		pbuf += sprintf(pbuf, "\n    ENU velocity output");
	}

	pbuf += sprintf(pbuf, (time_code & 0x01)?
		  "\n    Time tags in UTC":
        "\n    Time tags in GPS time");

	if (time_code & 0x02) {
		pbuf += sprintf(pbuf, "\n    Fixes delayed to integer seconds");
	}

	if (time_code & 0x04) {
		pbuf += sprintf(pbuf, "\n    Fixes sent only on request");
	}

	if (time_code & 0x08) {
		pbuf += sprintf(pbuf, "\n    Synchronized measurements");
	}

	if (time_code & 0x10) {
		pbuf += sprintf(pbuf, "\n    Minimize measurement propagation");
	}

	if (aux_code & 0x01) {
		pbuf += sprintf(pbuf, "\n    Raw measurement output");
	}

	if (aux_code & 0x02) {
		pbuf += sprintf(pbuf, "\n    Code-phase smoothed before output");
	}

	if (aux_code & 0x04) {
		pbuf += sprintf(pbuf, "\n    Additional fix status");
	}

	pbuf += sprintf(pbuf, "\n    Signal Strength Output as %s",
		(aux_code & 0x08)? "dBHz" : "AMU");
}

/* 0x56 */
static void rpt_ENU_velocity (TSIPPKT *rpt)
{
	float
		vel_ENU[3], freq_offset, time_of_fix;

	/* unload rptbuf */
	if (rpt_0x56 (rpt, vel_ENU, &freq_offset, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nVel ENU: %11.3f  %11.3f  %11.3f  %12.3f%s",
		vel_ENU[0], vel_ENU[1], vel_ENU[2], freq_offset,
      show_time (time_of_fix));
}

/* 0x57 */
#define MAX_SOURCE_MESSAGE 9
static void rpt_last_fix_info (TSIPPKT *rpt)
{
	unsigned char
		source_code, diag_code;
	short
		week_num;
	float
		time_of_fix;
	const char
		*source_text[MAX_SOURCE_MESSAGE] = {
		"no current fix",
		"good current fix",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"unknown",
		"unknown"} ;


	/* unload rptbuf */
	if (rpt_0x57 (rpt, &source_code, &diag_code, &week_num, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\n%s (%d);   diag code: %2Xh",
   	source_text[source_code], source_code, diag_code);
	pbuf += sprintf(pbuf, "\n    Time of last fix:%s", show_time(time_of_fix));
	pbuf += sprintf(pbuf, "\n    Week of last fix: %d", week_num);
}

/* 0x58 */
#define MAX_DAT_MESSAGE 7
static void rpt_GPS_system_data (TSIPPKT *rpt)
{
	unsigned char
   	iprn,
		op_code, data_type, sv_prn,
		data_length, data_packet[250];
	ALM_INFO
		*almanac;
	ALH_PARMS
		*almh;
	UTC_INFO
		*utc;
	ION_INFO
		*ionosphere;
	EPHEM_CLOCK
		*cdata;
	EPHEM_ORBIT
		*edata;
	NAV_INFO
		*nav_data;
	unsigned char
		curr_t_oa;
	short
		curr_wn_oa;
	const char
		*datname[MAX_DAT_MESSAGE] =
		{"", "", "Almanac",
		"Health Page, T_oa, WN_oa", "Ionosphere", "UTC ",
		"Ephemeris"};

	/* unload rptbuf */
	if (rpt_0x58 (rpt, &op_code, &data_type, &sv_prn,
		&data_length, data_packet)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nSystem data [%d]:  %s  SV%02d",
		data_type, datname[data_type], sv_prn);
	switch (op_code)
	{
	case 1:
		pbuf += sprintf(pbuf, "  Acknowledgment");
		break;
	case 2:
		pbuf += sprintf(pbuf, "  length = %d bytes", data_length);
		switch (data_type) {
		case 2:
			/* Almanac */
			if (sv_prn == 0 || sv_prn > 32) {
				pbuf += sprintf(pbuf, "  Binary PRN invalid");
				return;
			}
			almanac = (ALM_INFO*)data_packet;
			pbuf += sprintf(pbuf, "\n   t_oa_raw = % -12d    SV_hlth  = % -12d  ", almanac->t_oa_raw , almanac->SV_health );
			pbuf += sprintf(pbuf, "\n   e        = % -12g    t_oa     = % -12g  ", almanac->e        , almanac->t_oa     );
			pbuf += sprintf(pbuf, "\n   i_0      = % -12g    OMEGADOT = % -12g  ", almanac->i_0      , almanac->OMEGADOT );
			pbuf += sprintf(pbuf, "\n   sqrt_A   = % -12g    OMEGA_0  = % -12g  ", almanac->sqrt_A   , almanac->OMEGA_0  );
			pbuf += sprintf(pbuf, "\n   omega    = % -12g    M_0      = % -12g  ", almanac->omega    , almanac->M_0      );
			pbuf += sprintf(pbuf, "\n   a_f0     = % -12g    a_f1     = % -12g  ", almanac->a_f0     , almanac->a_f1     );
			pbuf += sprintf(pbuf, "\n   Axis     = % -12g    n        = % -12g  ", almanac->Axis     , almanac->n        );
			pbuf += sprintf(pbuf, "\n   OMEGA_n  = % -12g    ODOT_n   = % -12g  ", almanac->OMEGA_n  , almanac->ODOT_n   );
			pbuf += sprintf(pbuf, "\n   t_zc     = % -12g    weeknum  = % -12d  ", almanac->t_zc     , almanac->weeknum  );
			pbuf += sprintf(pbuf, "\n   wn_oa    = % -12d", almanac->wn_oa    );
			break;

		case 3:
			/* Almanac health page */
			almh = (ALH_PARMS*)data_packet;
			pbuf += sprintf(pbuf, "\n   t_oa = %d, wn_oa&0xFF = %d  ", almh->t_oa, almh->WN_a);
			pbuf += sprintf(pbuf, "\nAlmanac health page:");
			for (iprn = 0; iprn < 32; iprn++) {
				if (!(iprn%5)) *pbuf++ = '\n';
				pbuf += sprintf(pbuf, "    SV%02d  %2X", (iprn+1) , almh->SV_health[iprn]);
			}
			curr_t_oa = data_packet[34];
			curr_wn_oa = (data_packet[35]<<8) + data_packet[36];
			pbuf += sprintf(pbuf, "\n   current t_oa = %d, wn_oa = %d  ", curr_t_oa, curr_wn_oa);
			break;

		case 4:
			/* Ionosphere */
			ionosphere = (ION_INFO*)data_packet;
			pbuf += sprintf(pbuf, "\n   alpha_0 = % -12g  alpha_1 = % -12g ", ionosphere->alpha_0, ionosphere->alpha_1);
			pbuf += sprintf(pbuf, "\n   alpha_2 = % -12g  alpha_3 = % -12g ", ionosphere->alpha_2, ionosphere->alpha_3);
			pbuf += sprintf(pbuf, "\n   beta_0  = % -12g  beta_1  = % -12g  ", ionosphere->beta_0, ionosphere->beta_1);
			pbuf += sprintf(pbuf, "\n   beta_2  = % -12g  beta_3  = % -12g  ", ionosphere->beta_2, ionosphere->beta_3);
			break;

		case 5:
			/* UTC */
			utc = (UTC_INFO*)data_packet;
			pbuf += sprintf(pbuf, "\n   A_0         = %g  ", utc->A_0);
			pbuf += sprintf(pbuf, "\n   A_1         = %g  ", utc->A_1);
			pbuf += sprintf(pbuf, "\n   delta_t_LS  = %d  ", utc->delta_t_LS);
			pbuf += sprintf(pbuf, "\n   t_ot        = %.0f  ", utc->t_ot );
			pbuf += sprintf(pbuf, "\n   WN_t        = %d  ", utc->WN_t );
			pbuf += sprintf(pbuf, "\n   WN_LSF      = %d  ", utc->WN_LSF );
			pbuf += sprintf(pbuf, "\n   DN          = %d  ", utc->DN );
			pbuf += sprintf(pbuf, "\n   delta_t_LSF = %d  ", utc->delta_t_LSF );
			break;

		case 6: /* Ephemeris */
			if (sv_prn == 0 || sv_prn > 32) {
				pbuf += sprintf(pbuf, "  Binary PRN invalid");
				return;
			}
			nav_data = (NAV_INFO*)data_packet;

			pbuf += sprintf(pbuf, "\n     SV_PRN = % -12d .  t_ephem = % -12g . ",
         	nav_data->sv_number , nav_data->t_ephem );
			cdata = &(nav_data->ephclk);
			pbuf += sprintf(pbuf,
         	"\n    weeknum = % -12d .   codeL2 = % -12d .  L2Pdata = % -12d",
         	cdata->weeknum , cdata->codeL2 , cdata->L2Pdata );
			pbuf += sprintf(pbuf,
         	"\n  SVacc_raw = % -12d .SV_health = % -12d .     IODC = % -12d",
         	cdata->SVacc_raw, cdata->SV_health, cdata->IODC );
			pbuf += sprintf(pbuf,
         	"\n       T_GD = % -12g .     t_oc = % -12g .     a_f2 = % -12g",
         	cdata->T_GD, cdata->t_oc, cdata->a_f2 );
			pbuf += sprintf(pbuf,
         	"\n       a_f1 = % -12g .     a_f0 = % -12g .    SVacc = % -12g",
         	cdata->a_f1, cdata->a_f0, cdata->SVacc );
			edata = &(nav_data->ephorb);
			pbuf += sprintf(pbuf,
	         "\n       IODE = % -12d .fit_intvl = % -12d .     C_rs = % -12g",
	         edata->IODE, edata->fit_interval, edata->C_rs );
			pbuf += sprintf(pbuf,
         	"\n    delta_n = % -12g .      M_0 = % -12g .     C_uc = % -12g",
         	edata->delta_n, edata->M_0, edata->C_uc );
			pbuf += sprintf(pbuf,
         	"\n        ecc = % -12g .     C_us = % -12g .   sqrt_A = % -12g",
	         edata->e, edata->C_us, edata->sqrt_A );
			pbuf += sprintf(pbuf,
         	"\n       t_oe = % -12g .     C_ic = % -12g .  OMEGA_0 = % -12g",
            edata->t_oe, edata->C_ic, edata->OMEGA_0 );
			pbuf += sprintf(pbuf,
	         "\n       C_is = % -12g .      i_0 = % -12g .     C_rc = % -12g",
	         edata->C_is, edata->i_0, edata->C_rc );
			pbuf += sprintf(pbuf,
	         "\n      omega = % -12g . OMEGADOT = % -12g .     IDOT = % -12g",
         	edata->omega, edata->OMEGADOT, edata->IDOT );
			pbuf += sprintf(pbuf,
   	      "\n       Axis = % -12g .        n = % -12g .    r1me2 = % -12g",
	         edata->Axis, edata->n, edata->r1me2 );
			pbuf += sprintf(pbuf,
      	   "\n    OMEGA_n = % -12g .   ODOT_n = % -12g",
	         edata->OMEGA_n, edata->ODOT_n );
			break;
		}
	}
}


/* 0x59: */
static void rpt_SVs_enabled (TSIPPKT *rpt)
{
	unsigned char
   	numsvs,
		code_type,
      status_code[32];
	short
		iprn;

	/* unload rptbuf */
	if (rpt_0x59 (rpt, &code_type, status_code)) {
		parsed = BADLEN_PARSE;
		return;
	}
   switch (code_type)
   {
   case 3:
		pbuf += sprintf(pbuf, "\nSVs Disabled:\n");
     	break;
   case 6:
		pbuf += sprintf(pbuf, "\nSVs with Health Ignored:\n");
      break;
   default:
   	return;
   }
   numsvs = 0;
	for (iprn=0; iprn<32; iprn++)
   {
     	if (status_code[iprn])
      {
	   	pbuf += sprintf(pbuf, " %02d", iprn+1);
   	   numsvs++;
      }
   }
   if (numsvs == 0) pbuf += sprintf(pbuf, "None");
}


/* 0x5A */
static void rpt_raw_msmt (TSIPPKT *rpt)
{
	unsigned char
		sv_prn;
	float
		sample_length, signal_level, code_phase, Doppler;
	double
		time_of_fix;

	/* unload rptbuf */
	if (rpt_0x5A (rpt, &sv_prn, &sample_length, &signal_level,
		&code_phase, &Doppler, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\n   %02d %5.0f %7.1f %10.2f %10.2f %12.3f %s",
		sv_prn, sample_length, signal_level, code_phase, Doppler, time_of_fix,
		show_time ((float)time_of_fix));
}

/* 0x5B */
static void rpt_SV_ephemeris_status (TSIPPKT *rpt)
{
	unsigned char
		sv_prn, sv_health, sv_iode, fit_interval_flag;
	float
		time_of_collection, time_of_eph, sv_accy;

	/* unload rptbuf */
	if (rpt_0x5B (rpt, &sv_prn, &sv_health, &sv_iode, &fit_interval_flag,
		&time_of_collection, &time_of_eph, &sv_accy)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\n  SV%02d  %s   %2Xh     %2Xh %s   %1d   %4.1f",
   	sv_prn, show_time (time_of_collection), sv_health, sv_iode,
      show_time (time_of_eph), fit_interval_flag, sv_accy);
}

/* 0x5C */
static void rpt_SV_tracking_status (TSIPPKT *rpt)
{
	unsigned char
		sv_prn, chan, slot, acq_flag, eph_flag,
		old_msmt_flag, integer_msec_flag, bad_data_flag,
		data_collect_flag;
	float
		signal_level, time_of_last_msmt,
		elev, azim;

	/* unload rptbuf */
	if (rpt_0x5C (rpt,
		&sv_prn, &slot, &chan, &acq_flag, &eph_flag,
		&signal_level, &time_of_last_msmt, &elev, &azim,
		&old_msmt_flag, &integer_msec_flag, &bad_data_flag,
		&data_collect_flag))
   {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf,
"\n SV%2d  %1d %1d  %1d   %1d   %4.1f  %s  %5.1f  %5.1f   %d    %d    %d    %d",
		sv_prn, chan, slot,
      acq_flag, eph_flag, signal_level,
      show_time(time_of_last_msmt),
		elev*R2D, azim*R2D, old_msmt_flag,
		integer_msec_flag, bad_data_flag, data_collect_flag);
}

/**/
/* 0x6D */
static void rpt_allSV_selection (TSIPPKT *rpt)
{
	unsigned char
		manual_mode, nsvs, sv_prn[8], ndim;
	short
		islot;
	float
		pdop, hdop, vdop, tdop;

	/* unload rptbuf */
	if (rpt_0x6D (rpt,
		&manual_mode, &nsvs, &ndim, sv_prn,
		&pdop, &hdop, &vdop, &tdop)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nMode: %d SV (%d-D, %s):",
		nsvs, ndim - 1, manual_mode ? "Manual" : "Auto");
	for (islot = 0; islot < nsvs; islot++) {
		if (sv_prn[islot]) pbuf += sprintf(pbuf, " %02d", sv_prn[islot]);
	}
	pbuf += sprintf(pbuf, "\n      P, H, V, TDOP = %.2f, %.2f, %.2f, %.2f",
		pdop, hdop, vdop, tdop);
}

/* 0x6E */
static void rpt_full_msmt_packet_controls (TSIPPKT *rpt)
{
	unsigned char
	subcode,
	enable,
	interval;

	if (rpt_0x6E (rpt, &subcode, &enable, &interval)) {
		parsed = BADLEN_PARSE;
		return;
	}

	if (enable) pbuf += sprintf(pbuf,
   	"\nFull msmt packet (6F-%02X) enabled with %d sec interval",
      subcode, interval);
	else pbuf += sprintf(pbuf, "\nFull msmt packet disabled");
}

/* 0x6F */
static void rpt_full_msmt_packet (TSIPPKT *rpt)
{
	int
		ichan;
	struct cph1_msg_struct
		cph1;
	struct cph1_datablock_struct
		*cph1d;
	double
		gtime;

	/* unload rptbuf */
	if (rpt_0x6F01 (rpt, &cph1)) {
		parsed = BADLEN_PARSE;
		return;
	}

	gtime = cph1.receive_time*.001;
	pbuf += sprintf(pbuf, "\n(6E-%02X)  Time = %.3f secs, off = %.3f msec, numsvs = %d",
		cph1.subcode, gtime, cph1.clock_offset, cph1.numsvs);
	for (ichan = 0; ichan < cph1.numsvs; ichan++) {
		cph1d = &cph1.db[ichan];
		pbuf += sprintf(pbuf, "\n  *SV%02d (%02X) S %5.2f  PR %10.1f  Cph %12.2f  Dp %8.2f",
			cph1d->prn,
			cph1d->flagbyte,
			(double)cph1d->signal_strength * 0.25,
			cph1d->pseudorange,
			cph1d->carrier_phase,
			cph1d->Doppler);
	}
	return;
}
/**/
/* 0x70 */
static void show_pv_operation (TSIPPKT *rpt)
{
	unsigned char dyn_switch, static_switch, alt_switch, extra;

	if (rpt_0x70 (rpt, &dyn_switch, &static_switch, &alt_switch, &extra)) {
		parsed = BADLEN_PARSE;
		return;
	}

	/* If dynamic filter is off, then static filter cannot run, so just
		inform user that the entire PV filter is disabled */

	pbuf += sprintf(pbuf, "\nFilter status:");
	if (dyn_switch == 0)
   {
		pbuf += sprintf(pbuf, "\n   PV filter disabled");
	}
	else {
		pbuf += sprintf(pbuf, "\n   PV dynamic filter %s", dyn_switch?"enabled":"disabled");
		pbuf += sprintf(pbuf, "\n   PV static filter %s", static_switch?"enabled":"disabled");
	}
	pbuf += sprintf(pbuf, "\n   Altitude filter %s", alt_switch?"enabled":"disabled");
}

/* 0x72 */
static void show_pos_filter (TSIPPKT *rpt)
{
	short
		pf;
	TSIP_POS_FILT_PARMS
		params;

	if (rpt_0x72 (rpt, &pf, &params)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nPosition filter %s (%d)",
   	(pf & 0x01) ? "enabled" : "disabled", pf);
	pbuf += sprintf(pbuf, "\n   float 1: %.5f", params.flt1);
	pbuf += sprintf(pbuf, "\n   byte 1 : %d", params.chr1);
	pbuf += sprintf(pbuf, "\n   byte 2 : %d", params.chr2);
	pbuf += sprintf(pbuf, "\n   byte 3 : %d", params.chr3);
	pbuf += sprintf(pbuf, "\n   byte 4 : %d", params.chr4);
	pbuf += sprintf(pbuf, "\n   float 2: %.3f", params.flt2);
	pbuf += sprintf(pbuf, "\n   float 3: %.0f", params.flt3);
	pbuf += sprintf(pbuf, "\n   float 4: %.3f", params.flt4);
	pbuf += sprintf(pbuf, "\n   float 5: %.0f", params.flt5);
	pbuf += sprintf(pbuf, "\n   byte 5 : %d %s", params.chr5,
		(params.chr5 == 0xFF) ? "static filter disabled":"");
}

/* 0x74 */
static void show_altitude_filter (TSIPPKT *rpt)
{
	float
		alt_filter_parm;

	/* unload rptbuf */
	if (rpt_0x74 (rpt, &alt_filter_parm)) {
		parsed = BADLEN_PARSE;
		return;
	}

	if (alt_filter_parm == -1.0) {
		pbuf += sprintf(pbuf, "\nAltitude filter disabled");
	} else {
		pbuf += sprintf(pbuf, "\nAlt filter max N = %4.0f fixes", alt_filter_parm);
	}
}

/* 0x78 */
static void rpt_DGPS_maxage (TSIPPKT *rpt)
{
	short
		max_age;

	/* unload rptbuf */
	if (rpt_0x78 (rpt, &max_age)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nDifferential Correction Max Age: %3d sec", max_age);
}

/* 0x7B */
static void rpt_nmea_parameters (TSIPPKT *rpt)
/* NMEA Control parameters */
{
	unsigned char
   	i, 
		subcode,
		interval;
	unsigned long
		nmeamask;

	if (rpt_0x7B (rpt,
		&subcode, &interval, &nmeamask)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nNMEA output interval: %d", interval);
	pbuf += sprintf(pbuf, "\n   NMEA output mask:  0x%08lX", nmeamask);
   for (i=0; nmeamask; i++, nmeamask>>=1)
   {
   	if (nmeamask & 1)
      {
      	pbuf += sprintf(pbuf, " %s", NMEA_list[i]);
      }
   }
}

/**/
/* 0x82 */
static void rpt_DGPS_position_mode (TSIPPKT *rpt)
{
	unsigned char
		diff_mode;

	/* unload rptbuf */
	if (rpt_0x82 (rpt, &diff_mode)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nFix is%s DGPS-corrected (%s mode)  (%d)",
   	(diff_mode&1) ? "" : " not",
   	(diff_mode&2) ? "auto" : "manual",
      diff_mode);
}

/* 0x83 */
static void rpt_double_ECEF_position (TSIPPKT *rpt)
{

	double
		ECEF_pos[3], clock_bias;
	float
		time_of_fix;

	/* unload rptbuf */
	if (rpt_0x83 (rpt, ECEF_pos, &clock_bias, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nDXYZ:%12.2f  %13.2f  %13.2f %12.2f%s",
		ECEF_pos[0], ECEF_pos[1], ECEF_pos[2], clock_bias,
		show_time(time_of_fix));
}

/* 0x84 */
static void rpt_double_lla_position (TSIPPKT *rpt)
{
	short
		lat_deg, lon_deg;
	double
		lat, lon, lat_min, lon_min,
		alt, clock_bias;
	float
		time_of_fix;
	unsigned char
		north_south, east_west;

	/* unload rptbuf */
	if (rpt_0x84 (rpt,
		&lat, &lon, &alt, &clock_bias, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	lat *= R2D;
	lon *= R2D;
	if (lat < 0.0) {
		north_south = 'S';
		lat = -lat;
	} else {
		north_south = 'N';
	}
	lat_deg = (short)lat;
	lat_min = (lat - lat_deg) * 60.0;

	if (lon < 0.0) {
		east_west = 'W';
		lon = -lon;
	} else {
		east_west = 'E';
	}
	lon_deg = (short)lon;
	lon_min = (lon - lon_deg) * 60.0;
	pbuf += sprintf(pbuf, "\nDLLA: %2d:%08.5f %c; %3d:%08.5f %c; %10.2f %12.2f%s",
		lat_deg, lat_min, north_south,
		lon_deg, lon_min, east_west,
		alt, clock_bias,
		show_time(time_of_fix));
}

/* 0x85 */
static void rpt_dgps_info (TSIPPKT *rpt)
{
	const char
		*dm_text[6] = {"Good", "Delt", "StaH", " Age", "UDRE", "IODE"  };
	unsigned char
		sv_prn, summary_status, station_health, SV_UDRE_parm,
		iode1, iode2;
	float
		z_cnt_tow, range_corr, range_rate_corr, delta_range_corr;

	/* unload rptbuf */
	if (rpt_0x85 (rpt,
		&sv_prn, &summary_status, &station_health,
		&SV_UDRE_parm, &iode1, &iode2,
		&z_cnt_tow, &range_corr,
		&range_rate_corr, &delta_range_corr)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf,
   	"\n    %2d %2X=%s    %d    %d    %02X    %02X  %s %6.1f %6.1f %6.1f",
		sv_prn,
      summary_status,
		(summary_status < 6) ? dm_text[summary_status] : "Unkn",
		station_health, SV_UDRE_parm, iode1, iode2,
		show_time(z_cnt_tow),
		range_corr, range_rate_corr, delta_range_corr);
}

/* 0xBB */
static void rpt_stinger_rcvr_config (TSIPPKT *rpt)
{
	TSIP_RCVR_CFG TsipxBB ;
	/* unload rptbuf */
	if (rpt_0xBB (rpt, &TsipxBB)){
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf,
   	"\nStinger receiver configuration parameters (subcode %d):",
      TsipxBB.bSubcode);
	pbuf += sprintf(pbuf, "\n   operating mode:      %s",
		(TsipxBB.operating_mode < POS_FIX_TEXT_LEN)?
		pos_fix_text[TsipxBB.operating_mode]:
		"unknown");
	pbuf += sprintf(pbuf, "\n   DGPS mode:           %s",
		(TsipxBB.dgps_mode<DGPS_MODE_TEXT_LEN)?
		dgps_mode_text2[TsipxBB.dgps_mode]:
		"unknown");
	/*pbuf += sprintf(pbuf, "\n   tracking mode:       %s",
		(TsipxBB.trackmode<TRACKMODE_TEXT_LEN)?
		trackmode_text3[TsipxBB.trackmode]:
		"unknown");   */
	pbuf += sprintf(pbuf, "\n   dynamics:            %s",
		(TsipxBB.dyn_code<DYN_TEXT_LEN)?
		dyn_text[TsipxBB.dyn_code]:
		"unknown");
	pbuf += sprintf(pbuf, "\n   elev angle mask:     %g deg",
		TsipxBB.elev_mask * R2D);
	pbuf += sprintf(pbuf, "\n   SNR mask:            %g AMU",
		TsipxBB.cno_mask);
	pbuf += sprintf(pbuf, "\n   DOP mask:            %g",
		TsipxBB.dop_mask);
	pbuf += sprintf(pbuf, "\n   DOP switch:          %g",
		TsipxBB.dop_switch);
	pbuf += sprintf(pbuf, "\n   DGPS age limit:      %u sec",
		TsipxBB.dgps_age_limit);
	return ;
}

/* 0xBC */
static void rpt_rcvr_serial_port_config (TSIPPKT *rpt)
{
	unsigned char
		port_num, in_baud, out_baud, data_bits, parity, stop_bits, flow_control,
		protocols_in, protocols_out, reserved;
	unsigned char known;

	/* unload rptbuf */
	if (rpt_0xBC (rpt, &port_num, &in_baud, &out_baud, &data_bits, &parity,
			&stop_bits, &flow_control, &protocols_in, &protocols_out, &reserved)) {
		parsed = BADLEN_PARSE;
		return;
	}
	/* rptbuf unloaded */

	pbuf += sprintf(pbuf, "\n   RECEIVER serial port %s config:",
		(port_num<RCVR_PORT_TEXT_LEN-1)?rcvr_port_text[port_num]:"unknown port number");

	pbuf += sprintf(pbuf, "\n             Input baud %s, Output baud %s, %s - %s - %s",
		(in_baud<BAUD_TEXT_LEN)?st_baud_text_app[in_baud]:"unknown input baud rate",
		(out_baud<BAUD_TEXT_LEN)?st_baud_text_app[out_baud]:"unknown output baud rate",
		(data_bits<DATABIT_TEXT_LEN)?databit_text_app[data_bits]:"unknown data bits",
		(parity<PARITY_TEXT_LEN)?parity_text[parity]:"unknown parity",
		(stop_bits<STOPBIT_TEXT_LEN)?stopbit_text[stop_bits]:"unknown stop bits");
	pbuf += sprintf(pbuf, "\n             Input protocols: ");
	known = FALSE;
	if (protocols_in&TAIP) {
		pbuf += sprintf(pbuf, "%s ", protocols_text[0]);
		known = TRUE;
	}
	if (protocols_in&TSIP) {
		pbuf += sprintf(pbuf, "%s ", protocols_text[1]);
		known = TRUE;
	}
	if (protocols_in&NMEA) {
		pbuf += sprintf(pbuf, "%s ", protocols_text[2]);
		known = TRUE;
	}
	if (protocols_in&RTCM){
		pbuf += sprintf(pbuf, "%s ", protocols_text[3]);
		known = TRUE;
	}
	if (known == FALSE) pbuf += sprintf(pbuf, "No known");

	pbuf += sprintf(pbuf, "\n             Output protocols: ");
	known = FALSE;
	if (protocols_out&TAIP) {
		pbuf += sprintf(pbuf, "%s ", protocols_text[0]);
		known = TRUE;
	}
	if (protocols_out&TSIP) {
		pbuf += sprintf(pbuf, "%s ", protocols_text[1]);
		known = TRUE;
	}
	if (protocols_out&NMEA) {
		pbuf += sprintf(pbuf, "%s ", protocols_text[2]);
		known = TRUE;
	}
	if (known == FALSE) pbuf += sprintf(pbuf, "No known");
	reserved = reserved;

 }

/* 0x8F */
static void rpt_8F03 (TSIPPKT *rpt)
/* channel B configuration parameters */
{
	unsigned char
		tx_baud_index, rx_baud_index,
		char_format_index, stop_bits,
		tx_mode_index, rx_mode_index;

	/* unload rptbuf */
	if (rpt_0x8F03 (rpt,
		&tx_baud_index, &rx_baud_index, &char_format_index,
		&stop_bits, &tx_mode_index, &rx_mode_index)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nChannel B Configuration");
	old_show_port_config (tx_baud_index, rx_baud_index, char_format_index,
		stop_bits, tx_mode_index, rx_mode_index);
}

/* 0x8F15 */
static void rpt_8F15 (TSIPPKT *rpt)
/* Datum parameters */
{
	double
		datum_coeffs[5];
	short
		datum_idx;

	/* unload rptbuf */
	if (rpt_0x8F15 (rpt, &datum_idx, datum_coeffs)) {
		parsed = BADLEN_PARSE;
		return;
	}

	if (datum_idx == -1)
   {
   	pbuf += sprintf(pbuf, "\nUser-Entered Datum:");
   }
   else if (datum_idx == 0)
   {
   	pbuf += sprintf(pbuf, "\nWGS-84 datum, Index 0 ");
   }
   else
   {
   	pbuf += sprintf(pbuf, "\nStandard Datum, Index %3d ", datum_idx);
   }
	pbuf += sprintf(pbuf, "\n   dx        = %6.1f", datum_coeffs[0]);
	pbuf += sprintf(pbuf, "\n   dy        = %6.1f", datum_coeffs[1]);
	pbuf += sprintf(pbuf, "\n   dz        = %6.1f", datum_coeffs[2]);
	pbuf += sprintf(pbuf, "\n   a-axis    = %10.3f", datum_coeffs[3]);
	pbuf += sprintf(pbuf, "\n   e-squared = %16.14f", datum_coeffs[4]);
}

/* 0x8F17 */
static void rpt_8F17 (TSIPPKT *rpt)
/* UTM single precision position response */
{
	unsigned char UTM_grid_letter;
	short UTM_grid_number;
	float UTM_northing_value,
			   UTM_easting_value,
			   UTM_altitude,
			   clock_bias,
			time_of_fix;

	/* unload rptbuf */
	if (rpt_0x8F17 (rpt,
	  &UTM_grid_letter, &UTM_grid_number, &UTM_northing_value,
		&UTM_easting_value, &UTM_altitude, &clock_bias, &time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nSP UTM: %d%c Nrthg: %7.0f   Eastg:%7.0f   Alt:%6.0f  %s",
		UTM_grid_number,
		UTM_grid_letter,
		UTM_northing_value,
		UTM_easting_value,
		UTM_altitude,
      show_time(time_of_fix));
}

static void rpt_8F18 (TSIPPKT *rpt)
/* UTM double precision position response */
{
	unsigned char UTM_grid_letter;
	short UTM_grid_number;

	double UTM_northing_value,
			   UTM_easting_value,
			   UTM_altitude,
			   clock_bias;

	float time_of_fix;

	/* unload rptbuf */
	if (rpt_0x8F18 (rpt, &UTM_grid_letter, &UTM_grid_number, &UTM_northing_value,
					&UTM_easting_value, &UTM_altitude, &clock_bias,
					&time_of_fix)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nDP UTM: %d%c Nrthg: %8.1f Eastg: %8.1f Alt:%8.1f%s",
		UTM_grid_number,
		UTM_grid_letter,
		UTM_northing_value,
		UTM_easting_value,
		UTM_altitude,
      show_time(time_of_fix));
}

static void rpt_8F19 (TSIPPKT *rpt)
/* UTM message enable status response */
{
	short UTM_enabled;

	if (rpt_0x8F19 (rpt, &UTM_enabled)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nUTM Position Output is %s",
   	UTM_enabled ? "Enabled" : "Disabled");
}


#define INFO_DGPS       0x02
#define INFO_2D         0x04
#define INFO_ALTSET     0x08
#define INFO_FILTERED   0x10
static void rpt_8F20 (TSIPPKT *rpt)
{
	unsigned char
		subpacket_id, info, nsvs, sv_prn[32];
	short
		week_num, datum_index, sv_IODC[32];
	double
		lat, lon, alt, time_of_fix;
	double
		londeg, latdeg, vel[3];
	short
		isv;
   char
   	datum_string[20];

	/* unload rptbuf */
	if (rpt_0x8F20 (rpt,
		&subpacket_id, &info, &lat, &lon, &alt, vel,
		&time_of_fix,
		&week_num, &nsvs, sv_prn, sv_IODC, &datum_index))
	{
		parsed = BADLEN_PARSE;
		return;
	}
	/* convert from radians to degrees */
	latdeg = R2D * fabs(lat);
	londeg = R2D * fabs(lon);
	pbuf += sprintf(pbuf,
   	"\nGPS time (UTC + %2d): %04d:%3s:%02d:%02d:%06.3f     FixType: %s%s%s",
      (char)rpt->buf[29],		/* UTC offset */
   	week_num,
		dayname[(short)(time_of_fix/86400.0)],
		(short)fmod(time_of_fix/3600., 24.),
		(short)fmod(time_of_fix/60., 60.),
		fmod(time_of_fix, 60.),
		(info & INFO_DGPS)?"Diff":"",
		(info & INFO_2D)?((info&INFO_ALTSET)?"2D-AltSet":"2D-AltHld"):"3D",
		(info & INFO_FILTERED)?"-Filtrd":"");

   if (datum_index > 0)
   {
		sprintf(datum_string, "Datum%3d", datum_index);
   }
   else if (datum_index)
   {
		sprintf(datum_string, "Unknown ");
   }
   else
   {
		sprintf(datum_string, " WGS-84 ");
   }

	pbuf += sprintf(pbuf,
   	"\n   Pos   (%s):  %4d:%09.6f %c %5d:%09.6f %c %10.2f m HAE",
      datum_string,
		(short)latdeg, fmod (latdeg, 1.)*60.0,
		(lat<0.0)?'S':'N',
		(short)londeg, fmod (londeg, 1.)*60.0,
		(lon<0.0)?'W':'E',
		alt);
	pbuf += sprintf(pbuf,
   	"\n   Vel   (m/sec)   :    %9.3f E       %9.3f N      %9.3f U",
		vel[0], vel[1], vel[2]);

	pbuf += sprintf(pbuf, "\n   SVs  &  IODEs   :");
	for (isv = 0; isv < nsvs; isv++) {
		pbuf += sprintf(pbuf, " %02d", sv_prn[isv]);
	}
	pbuf += sprintf(pbuf, "       ( ");
	for (isv = 0; isv < nsvs; isv++) {
		pbuf += sprintf(pbuf, "%02X ", sv_IODC[isv]&0xFF);
	}
	pbuf += sprintf(pbuf, ")");
}

#define MAX_LONG  (2147483648.)   /* 2**31 */
static void rpt_8F23 (TSIPPKT *rpt)
{
	unsigned char
		subpacket_id, UTC_Offset, fix_type;
   unsigned long
   	TOW, lon;
   unsigned short
   	week;
   long
   	lat, alt;
	short
   	east, north, up;
   double
   	lonTemp, latDegrees, lonDegrees, altFlt,
      eastFlt, northFlt, upFlt, vel_scale;

	/* unload rptbuf */
	if (rpt_0x8F23 (rpt,
		&subpacket_id, &TOW, &week, &UTC_Offset, &fix_type,
      &lat, &lon, &alt, &east, &north, &up))
	{
		parsed = BADLEN_PARSE;
		return;
	}

   pbuf += sprintf(pbuf,
   	"\nGPS Time (UTC+%d): %3s:%02d:%02d:%06.3f     Week: %d     FixType: %s%s%s",
      UTC_Offset,
		dayname[(short)((double)TOW/86400.0)],
		(short)fmod((double)TOW/3600., 24.),
		(short)fmod((double)TOW/60., 60.),
		fmod((double)TOW, 60.),
      week,
		(fix_type & INFO_DGPS)?"Diff":"",
		(fix_type & INFO_2D)?((fix_type&INFO_ALTSET)?"2D-AltSet":"2D-AltHld"):"3D",
		(fix_type & INFO_FILTERED)?"-Filtrd":"");

   latDegrees = R2D * fabs((double)lat*(GPS_PI/MAX_LONG));

   lonTemp = (double)lon*(GPS_PI/MAX_LONG); 
	if (lonTemp > GPS_PI)
   	lonTemp -= 2.0*GPS_PI;
   lonDegrees = R2D * fabs(lonTemp);

   altFlt = (double)alt*0.001;

	pbuf += sprintf(pbuf,
   	"\n   Pos (WGS-84)  : %4d:%09.6f %c %5d:%09.6f %c %10.2f m HAE ",
		(short)latDegrees, fmod (latDegrees, 1.)*60.0,
		(lat<0.0)?'S':'N',
		(short)lonDegrees, fmod (lonDegrees, 1.)*60.0,
		(lonTemp<0.0)?'W':'E',
		altFlt);

	vel_scale = (fix_type&32)? 0.020 : 0.005;
	eastFlt  = (double)east*vel_scale;
	northFlt = (double)north*vel_scale;
	upFlt    = (double)up*vel_scale;

	pbuf += sprintf(pbuf,
   	"\n   Vel (m/sec)   : %9.3f E       %9.3f N      %9.3f U",
		eastFlt, northFlt, upFlt);
}

static void rpt_8F24(TSIPPKT *rpt)
{
	short shutdown_in, shutdown_len;

	if (rpt_0x8F24(rpt, &shutdown_in, &shutdown_len)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nTime until shutdown : %2u seconds",shutdown_in);
	pbuf += sprintf(pbuf, "\nDuration of shutdown: %2u seconds",shutdown_len);
}

static void rpt_8F25(TSIPPKT *rpt)
{
	short mode_mask;

	if (rpt_0x8F25(rpt, &mode_mask)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nLP Modes: %02X",mode_mask);

	if (mode_mask & 0x01) {
		pbuf += sprintf(pbuf, "\n    LPSTOP");
	}

	if (mode_mask & 0x04) {
		pbuf += sprintf(pbuf, "\n    Scheduled Track");
	}

	if (mode_mask & 0x08) {
		pbuf += sprintf(pbuf, "\n    Auto SV Data Collection");
	}
}

static void rpt_8F26(TSIPPKT *rpt)
{
	unsigned long
		flash_write;

	if (rpt_0x8F26(rpt, &flash_write)) {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nFlash write %s",  flash_write?"failed":"successful");
}

static void rpt_8F27(TSIPPKT *rpt)
{
	unsigned long ST_period;
   short ST_awake_time;

	if (rpt_0x8F27(rpt, &ST_period, &ST_awake_time))
   {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nST Period                  : %6lu s",ST_period);
	pbuf += sprintf(pbuf, "\nST Awake Time              : %6u s",ST_awake_time);
}

#define MAX_HBS_TEXT 17
static void rpt_8F40 (TSIPPKT *rpt)
{
	unsigned char
   	Flags,
      HeartBeatSentence;
   short
      TopOfHourOffset,
      Frequency;
   char
   	VehicleID[5];
   char
   	*FlagsText[8] = {"ID","CS","EC","FR","CR","","",""},
      *HBSentenceText[MAX_HBS_TEXT] = {
      	"AL", "", "CP", "", "", "", "ID", "", "LN", "",
         "", "PV", "", "ST", "TM", "", "VR"};
   short
   	i;

	if (rpt_0x8F40(rpt,
   	&Flags,
      &HeartBeatSentence,
      &TopOfHourOffset,
      &Frequency,
      VehicleID))
   {
		parsed = BADLEN_PARSE;
		return;
	}

	pbuf += sprintf(pbuf, "\nFlags (%d):", Flags);
	for (i=0; i<8; i++)
   {
   	if (Flags & 1)	pbuf += sprintf(pbuf, " %s ", FlagsText[i]);
      Flags>>=1;
   }
	pbuf += sprintf(pbuf, "\n   Heartbeat Sentence: %s (%d)",
   	(HeartBeatSentence<MAX_HBS_TEXT)?HBSentenceText[HeartBeatSentence]:"Unknown",
      HeartBeatSentence);
	pbuf += sprintf(pbuf, "\n   Top-of-hour offset %d, Frequency %d ",
   	TopOfHourOffset, Frequency);
	VehicleID[4] = 0;
   pbuf += sprintf(pbuf, "\n   VehicleID = %s", VehicleID);
}

short print_msg_table_header (unsigned char rptcode, char *HdrStr, unsigned char force)
{
	/* force header is to help auto-output function */
	/* last_rptcode is to determine whether to print a header */
	/* for the first occurence of a series of reports */
	static unsigned char
		last_rptcode = 0;
   short
   	numchars;

   numchars = 0;
	if (force || rptcode!=last_rptcode)
   {
   	switch (rptcode)
		{
		case 0x5A:
			/* supply a header in console output */
			numchars = sprintf(HdrStr,
   	   	"\nRaw Measurement Data");
			numchars += sprintf(HdrStr+numchars,
      		"\n   SV  Sample   SNR  Code Phase   Doppler    Seconds     Time of Meas");
			break;

		case 0x5B:
			numchars = sprintf(HdrStr,
         	"\nEphemeris Status");
			numchars += sprintf(HdrStr+numchars,
				"\n    SV     Time collected     Health  IODE        t oe         Fit   URA");
			break;

		case 0x5C:
			numchars = sprintf(HdrStr,
      		"\nTracking Info");
			numchars += sprintf(HdrStr+numchars,
   	   	"\n   SV  C S Acq Eph   SNR     Time of Meas       Elev  Azim   Old Msec BadD DCol");
			break;

		case 0x85:
			numchars = sprintf(HdrStr,
      		"\nDifferential Correction Status");
			numchars += sprintf(HdrStr+numchars,
   	   	"\n    SV  Status  StaH  SV H  IODE1  IODE2  Z-count time        PRC    RRC    DRC");
			break;
      }
	}
	last_rptcode = rptcode;
   return numchars;
}

static void unknown_rpt (TSIPPKT *rpt)
{
	short i;

	/* app-specific rpt packets */
	if (parsed == BADLEN_PARSE)
   {
		pbuf += sprintf(pbuf, "\nTSIP report packet ID %2Xh, length %d: Bad length",
      	rpt->code, rpt->len);
   }
	if (parsed == BADID_PARSE)
   {
		pbuf += sprintf(pbuf, "\nTSIP report packet ID %2Xh, length %d: translation not supported",
   		rpt->code, rpt->len);
   }

	for (i = 0; i < rpt->len; i++) {
		if ((i % 20) == 0) *pbuf++ = '\n';
		pbuf += sprintf(pbuf, " %02X", rpt->buf[i]);
	}
}
/**/
void rpt_packet (TSIPPKT *rpt, char *obuf)
{

	pbuf = obuf;

	parsed = GOOD_PARSE;

	/* print a header if this is the first of a series of messages */
	pbuf += print_msg_table_header (rpt->code, pbuf, FALSE);

	switch (rpt->code) {
	case 0x3D:
		show_chan_A_config (rpt);
		break;

	case 0x40:
		rpt_almanac_data_page (rpt);
		break;

	case 0x41:
		rpt_GPS_time (rpt);
		break;

	case 0x42:
		rpt_single_ECEF_position (rpt);
		break;

	case 0x43:
		rpt_single_ECEF_velocity (rpt);
		break;

	case 0x45:
		rpt_SW_version (rpt);
		break;

	case 0x46:
		rpt_rcvr_health (rpt);
		break;

	case 0x47:
		rpt_SNR_all_SVs (rpt);
		break;

	case 0x48:
		rpt_GPS_system_message (rpt);
		break;

	case 0x49:
		rpt_almanac_health_page (rpt);
		break;

	case 0x4A:
		if (rpt->len == 20)
		{
			rpt_single_lla_position (rpt);
		}
		else if (rpt->len == 9)

		{
			rpt_ref_alt (rpt);
		}
		break;

	case 0x4B:
		rpt_rcvr_id_and_status (rpt);
		break;

	case 0x4C:
		rpt_operating_parameters (rpt);
		break;

	case 0x4D:
		rpt_oscillator_offset (rpt);
		break;

	case 0x4E:
		rpt_GPS_time_set_response (rpt);
		break;

	case 0x4F:
		rpt_UTC_offset (rpt);
		break;

   case 0x54:
      rpt_1SV_bias (rpt);
      break;

	case 0x55:
		rpt_io_opt (rpt);
		break;

	case 0x56:
		rpt_ENU_velocity (rpt);
		break;

	case 0x57:
		rpt_last_fix_info (rpt);
		break;

	case 0x58:
		rpt_GPS_system_data (rpt);
		break;

	case 0x59:
		rpt_SVs_enabled (rpt);
		break;

	case 0x5A:
		rpt_raw_msmt (rpt);
		break;

	case 0x5B:
		rpt_SV_ephemeris_status (rpt);
		break;

	case 0x5C:
		rpt_SV_tracking_status (rpt);
		break;

	case 0x6D:
		rpt_allSV_selection (rpt);
		break;

	case 0x6E:
		rpt_full_msmt_packet_controls (rpt);
		break;

	case 0x6F:
		rpt_full_msmt_packet (rpt);
		break;

	case 0x70:
		show_pv_operation (rpt);
		break;

	case 0x72:
		show_pos_filter (rpt);
		break;

	case 0x74:
		show_altitude_filter (rpt);
		break;

	case 0x78:
		rpt_DGPS_maxage (rpt);
		break;

	case 0x7B:
		rpt_nmea_parameters (rpt);
		break;

	case 0x82:
		rpt_DGPS_position_mode (rpt);
		break;

	case 0x83:
		rpt_double_ECEF_position (rpt);
		break;

	case 0x84:
		rpt_double_lla_position (rpt);
		break;

	case 0x85:
		rpt_dgps_info (rpt);
		break;

	case 0x8F:
		switch (rpt->buf[0]) {
		case 0x03:
			rpt_8F03 (rpt);
			break;

		case 0x15:
			rpt_8F15 (rpt);
			break;

		case 0x17:
			rpt_8F17 (rpt);
			break;

		case 0x18:
			rpt_8F18 (rpt);
			break;

		case 0x19:
			rpt_8F19 (rpt);
			break;

		case 0x20:
			rpt_8F20 (rpt);
			break;

      case 0x23:
			rpt_8F23 (rpt);
			break;

      case 0x24:
      	rpt_8F24 (rpt);
         break;

      case 0x25:
      	rpt_8F25 (rpt);
         break;

		case 0x26:
			rpt_8F26 (rpt);
			break;

      case 0x27:
      	rpt_8F27 (rpt);
         break;

		case 0x40:
			rpt_8F40 (rpt);
			break;

		default:
			parsed = BADID_PARSE;
			break;
		}
		break;

	case 0xBB: /* Stinger receiver configuration */
		rpt_stinger_rcvr_config (rpt);
		break;

	case 0xBC:  	/* Stinger receiver serial port config */
		rpt_rcvr_serial_port_config (rpt);
		break;

	default:
		parsed = BADID_PARSE;
		break;
	}

	if (parsed != GOOD_PARSE)
	{
		unknown_rpt (rpt);
	}

   pbuf = '\0';
}


