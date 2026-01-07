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
 * -------  BYTE-SWAPPING  -------
 * TSIP is big-endian (Motorola) protocol.  To use on little-endian (Intel)
 * systems, the bytes of all multi-byte types (shorts, floats, doubles, etc.)
 * must be reversed.  This is controlled by the MACRO BYTESWAP; if defined, it
 * assumes little-endian protocol.
 * --------------------------------
 *
 * T_PARSER.C and T_PARSER.H contains primitive functions that interpret
 * reports received from the receiver.  A second source file pair,
 * T_FORMAT.C and T_FORMAT.H, contin the matching TSIP command formatters.
 *
 * The module is in very portable, basic C language.  It can be used as is, or
 * with minimal changes if a TSIP communications application is needed separate
 * from TSIPCHAT. The construction of most argument lists avoids the use of
 * structures, but the developer is encouraged to reconstruct them using such
 * definitions to meet project requirements.  Declarations of T_PARSER.C
 * functions are included in T_PARSER.H to provide prototyping definitions.
 *
 * There are two types of functions: a serial input processing routine,
 * tsip_input_proc() which assembles incoming bytes into a TSIPPKT
 *	structure, and the report parsers, rpt_0x??().
 *
 * 1) The function tsip_input_proc() accumulates bytes from the receiver,
 * strips control bytes (DLE), and checks if the report end sequence (DLE ETX)
 * has been received.  rpt.status is defined as TSIP_PARSED_FULL (== 1)
 * if a complete packet is available.
 *
 * 2) The functions rpt_0x??() are report string interpreters patterned after
 * the document called "Trimble Standard Interface Protocol".  It should be
 * noted that if the report buffer is sent into the receiver with the wrong
 * length (byte count), the rpt_0x??() returns the Boolean equivalence for
 * TRUE.
 *
 * *************************************************************************
 *
 */

#include <string.h>
#include "t_struct.h"
#include "t_parser.h"

/**/
void tsip_input_proc (TSIPPKT *rpt, short inbyte)
/* reads bytes until serial buffer is empty or a complete report
 * has been received; end of report is signified by DLE ETX.
 */
{                 
	unsigned char newbyte;

	if (inbyte & 0xFF00) return;

	newbyte = (unsigned char)(inbyte & 0x00FF);
	switch (rpt->status)
	{
	case TSIP_PARSED_DLE_1:
		switch (newbyte)
		{
		case 0:
		case ETX:
      	/* illegal TSIP IDs */
         rpt->len = 0;
			rpt->status = TSIP_PARSED_EMPTY;
			break;
		case DLE:
      	/* try normal message start again */
			rpt->len = 0;
			rpt->status = TSIP_PARSED_DLE_1;
			break;
		default:
      	/* legal TSIP ID; start message */
			rpt->code = newbyte;
         rpt->len = 0;
			rpt->status = TSIP_PARSED_DATA;
			break;
		}
		break;
	case TSIP_PARSED_DATA:
		switch (newbyte) {
		case DLE:
      	/* expect DLE or ETX next */
			rpt->status = TSIP_PARSED_DLE_2;
			break;
		default:
      	/* normal data byte  */
			rpt->buf[rpt->len] = newbyte;
			rpt->len++;
         /* no change in rpt->status */
			break;
		}
		break;
	case TSIP_PARSED_DLE_2:
		switch (newbyte) {
		case DLE:
      	/* normal data byte */
			rpt->buf[rpt->len] = newbyte;
			rpt->len++;
			rpt->status = TSIP_PARSED_DATA;
			break;
		case ETX:
			/* end of message; return TRUE here. */
			rpt->status = TSIP_PARSED_FULL;
			break;
		default:
			/* error: treat as TSIP_PARSED_DLE_1; start new report packet */
			rpt->code = newbyte;
         rpt->len = 0;
			rpt->status = TSIP_PARSED_DATA;
		}
		break;
	case TSIP_PARSED_FULL:
	case TSIP_PARSED_EMPTY:
	default:
		switch (newbyte) {
		case DLE:
      	/* normal message start */
			rpt->len = 0;
			rpt->status = TSIP_PARSED_DLE_1;
			break;
		default:
			/* error: ignore newbyte */
			rpt->len = 0;
			rpt->status = TSIP_PARSED_EMPTY;
		}
		break;
	}
	if (rpt->len > MAX_RPTBUF) {
		/* error: start new report packet */
		rpt->status = TSIP_PARSED_EMPTY;
		rpt->len = 0;
	}
}

/* for DOS machines, reverse order of bytes as they come through the
 * serial port. */
#define BYTESWAP

#ifdef BYTESWAP
static short bGetShort (unsigned char *bp)
{
	short outval;
   unsigned char *optr;

   optr = (unsigned char*)&outval + 1;
   *optr-- = *bp++;
   *optr = *bp;
	return outval;
}

static long bGetLong (unsigned char *bp)
{
	long outval;
   unsigned char *optr;

   optr = (unsigned char*)&outval + 3;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr = *bp;
	return outval;
}

static unsigned long bGetULong (unsigned char *bp)
{
	unsigned long outval;
   unsigned char *optr;

   optr = (unsigned char*)&outval + 3;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr = *bp;
	return outval;
}

static float bGetSingle (unsigned char *bp)
{
	float outval;
   unsigned char *optr;

   optr = (unsigned char*)&outval + 3;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr = *bp;
	return outval;
}

static double bGetDouble (unsigned char *bp)
{
	double outval;
   unsigned char *optr;

   optr = (unsigned char*)&outval + 7;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr-- = *bp++;
   *optr = *bp;
	return outval;
}

#else	/* not BYTESWAP */

#define bGetShort(bp) 	(*(short*)(bp))
#define bGetLong(bp) 	(*(long*)(bp))
#define bGetULong(bp) 	(*(unsigned long*)(bp))
#define bGetSingle(bp) 	(*(float*)(bp))
#define bGetDouble(bp)	(*(double*)(bp))

#endif

/**/
short rpt_0x3D (TSIPPKT *rpt,
	unsigned char *tx_baud_index,
	unsigned char *rx_baud_index,
	unsigned char *char_format_index,
	unsigned char *stop_bits,
	unsigned char *tx_mode_index,
	unsigned char *rx_mode_index)
/* Channel A configuration for dual port operation */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 6) return TRUE;
	*tx_baud_index = buf[0];
	*rx_baud_index = buf[1];
	*char_format_index = buf[2];
	*stop_bits = (buf[3] == 0x07) ? 1 : 2;
	*tx_mode_index = buf[4];
	*rx_mode_index = buf[5];
	return FALSE;
}

/**/
short rpt_0x40 (TSIPPKT *rpt,
	unsigned char *sv_prn,
	short *week_num,
	float *t_zc,
	float *eccentricity,
	float *t_oa,
	float *i_0,
	float *OMEGA_dot,
	float *sqrt_A,
	float *OMEGA_0,
	float *omega,
	float *M_0)
/* almanac data for specified satellite */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 39) return TRUE;
	*sv_prn = buf[0];
	*t_zc = bGetSingle (&buf[1]);
	*week_num = bGetShort (&buf[5]);
	*eccentricity = bGetSingle (&buf[7]);
	*t_oa = bGetSingle (&buf[11]);
	*i_0 = bGetSingle (&buf[15]);
	*OMEGA_dot = bGetSingle (&buf[19]);
	*sqrt_A = bGetSingle (&buf[23]);
	*OMEGA_0 = bGetSingle (&buf[27]);
	*omega = bGetSingle (&buf[31]);
	*M_0 = bGetSingle (&buf[35]);
	return FALSE;
}

short rpt_0x41 (TSIPPKT *rpt,
	float *time_of_week,
	float *UTC_offset,
	short *week_num)
/* GPS time */
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 10) return TRUE;
	*time_of_week = bGetSingle (buf);
	*week_num = bGetShort (&buf[4]);
	*UTC_offset = bGetSingle (&buf[6]);
	return FALSE;
}

short rpt_0x42 (TSIPPKT *rpt,
	float pos_ECEF[3],
	float *time_of_fix)
/* position in ECEF, single precision */
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 16) return TRUE;
	pos_ECEF[0] = bGetSingle (buf);
	pos_ECEF[1]= bGetSingle (&buf[4]);
	pos_ECEF[2]= bGetSingle (&buf[8]);
	*time_of_fix = bGetSingle (&buf[12]);
	return FALSE;
}

short rpt_0x43 (TSIPPKT *rpt,
	float ECEF_vel[3],
	float *freq_offset,
	float *time_of_fix)
/* velocity in ECEF, single precision */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 20) return TRUE;
	ECEF_vel[0] = bGetSingle (buf);
	ECEF_vel[1] = bGetSingle (&buf[4]);
	ECEF_vel[2] = bGetSingle (&buf[8]);
	*freq_offset = bGetSingle (&buf[12]);
	*time_of_fix = bGetSingle (&buf[16]);
	return FALSE;
}

short rpt_0x45 (TSIPPKT *rpt,
	unsigned char *major_nav_version,
	unsigned char *minor_nav_version,
	unsigned char *nav_day,
	unsigned char *nav_month,
	unsigned char *nav_year,
	unsigned char *major_dsp_version,
	unsigned char *minor_dsp_version,
	unsigned char *dsp_day,
	unsigned char *dsp_month,
	unsigned char *dsp_year)
/* software versions */	
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 10) return TRUE;
	*major_nav_version = buf[0];
	*minor_nav_version = buf[1];
	*nav_day = buf[2];
	*nav_month = buf[3];
	*nav_year = buf[4];
	*major_dsp_version = buf[5];
	*minor_dsp_version = buf[6];
	*dsp_day = buf[7];
	*dsp_month = buf[8];
	*dsp_year = buf[9];
	return FALSE;
}

short rpt_0x46 (TSIPPKT *rpt,
	unsigned char *status_code,
	unsigned char *error_code)
/* receiver health and status */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 2) return TRUE;
	*status_code = buf[0];
	*error_code = buf[1];
	return FALSE;
}

short rpt_0x47 (TSIPPKT *rpt,
	unsigned char *nsvs, unsigned char *sv_prn,
	float *snr)
/* signal levels for all satellites tracked */
{
	short isv;
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 1 + 5*buf[0]) return TRUE;
	*nsvs = buf[0];
	for (isv = 0; isv < (*nsvs); isv++) {
		sv_prn[isv] = buf[5*isv + 1];
		snr[isv] = bGetSingle (&buf[5*isv + 2]);
	}
	return FALSE;
}

short rpt_0x48 (TSIPPKT *rpt,
	unsigned char *message)
/* GPS system message */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 22) return TRUE;
	memcpy (message, buf, 22);
	message[22] = 0;
	return FALSE;
}

short rpt_0x49 (TSIPPKT *rpt,
	unsigned char *sv_health)
/* health for all satellites from almanac health page */
{
	short i;
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 32) return TRUE;
	for (i = 0; i < 32; i++) sv_health [i]= buf[i];
	return FALSE;
}

short rpt_0x4A (TSIPPKT *rpt,
	float *lat,
	float *lon,
	float *alt,
	float *clock_bias,
	float *time_of_fix)
/* position in lat-lon-alt, single precision */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 20) return TRUE;
	*lat = bGetSingle (buf);
	*lon = bGetSingle (&buf[4]);
	*alt = bGetSingle (&buf[8]);
	*clock_bias = bGetSingle (&buf[12]);
	*time_of_fix = bGetSingle (&buf[16]);
	return FALSE;
}

short rpt_0x4A_2 (TSIPPKT *rpt,
	float *alt, float *dummy , unsigned char *alt_flag)
/* reference altitude parameters */
{
	unsigned char *buf;

	buf = rpt->buf;

	if (rpt->len != 9) return TRUE;
	*alt = bGetSingle (buf);
	*dummy = bGetSingle (&buf[4]);
	*alt_flag = buf[8];
	return FALSE;
}

short rpt_0x4B (TSIPPKT *rpt,
	unsigned char *machine_id,
	unsigned char *status_1,
	unsigned char *status_2)
/* machine ID code, status */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 3) return TRUE;
	*machine_id = buf[0];
	*status_1 = buf[1];
	*status_2 = buf[2];
	return FALSE;
}

short rpt_0x4C (TSIPPKT *rpt,
	unsigned char *dyn_code,
	float *el_mask,
	float *snr_mask,
	float *dop_mask,
	float *dop_switch)
/* operating parameters and masks */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 17) return TRUE;
	*dyn_code = buf[0];
	*el_mask = bGetSingle (&buf[1]);
	*snr_mask = bGetSingle (&buf[5]);
	*dop_mask = bGetSingle (&buf[9]);
	*dop_switch = bGetSingle (&buf[13]);
	return FALSE;
}

short rpt_0x4D (TSIPPKT *rpt,
	float *osc_offset)
/* oscillator offset */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 4) return TRUE;
	*osc_offset = bGetSingle (buf);
	return FALSE;
}

short rpt_0x4E (TSIPPKT *rpt,
	unsigned char *response)
/* yes/no response to command to set GPS time */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 1) return TRUE;
	*response = buf[0];
	return FALSE;
}

short rpt_0x4F (TSIPPKT *rpt,
	double *a0,
	float *a1,
	float *time_of_data,
	short *dt_ls,
	short *wn_t,
	short *wn_lsf,
	short *dn,
	short *dt_lsf)
/* UTC data */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 26) return TRUE;
	*a0 = bGetDouble (buf);
	*a1 = bGetSingle (&buf[8]);
	*dt_ls = bGetShort (&buf[12]);
	*time_of_data = bGetSingle (&buf[14]);
	*wn_t = bGetShort (&buf[18]);
	*wn_lsf = bGetShort (&buf[20]);
	*dn = bGetShort (&buf[22]);
	*dt_lsf = bGetShort (&buf[24]);
	return FALSE;
}

/**/
short rpt_0x54 (TSIPPKT *rpt,
	float *clock_bias,
   float *freq_offset,
   float *time_of_fix)
/* clock offset and frequency offset in 1-SV (0-D) mode */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 12) return TRUE;
	*clock_bias = bGetSingle (buf);
	*freq_offset = bGetSingle (&buf[4]);
	*time_of_fix = bGetSingle (&buf[8]);
	return FALSE;
}

short rpt_0x55 (TSIPPKT *rpt,
	unsigned char *pos_code,
	unsigned char *vel_code,
	unsigned char *time_code,
	unsigned char *aux_code)
/* I/O serial options */
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 4) return TRUE;
	*pos_code = buf[0];
	*vel_code = buf[1];
	*time_code = buf[2];
	*aux_code = buf[3];
	return FALSE;
}

short rpt_0x56 (TSIPPKT *rpt,
	float vel_ENU[3], float *freq_offset, float *time_of_fix)
/* velocity in east-north-up coordinates */	
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 20) return TRUE;
	/* east */
	vel_ENU[0] = bGetSingle (buf);
	/* north */
	vel_ENU[1] = bGetSingle (&buf[4]);
	/* up */
	vel_ENU[2] = bGetSingle (&buf[8]);
	*freq_offset = bGetSingle (&buf[12]);
	*time_of_fix = bGetSingle (&buf[16]);
	return FALSE;
}

short rpt_0x57 (TSIPPKT *rpt,
	unsigned char *source_code, unsigned char *diag_code,
	short *week_num,
	float *time_of_fix)
/* info about last computed fix */
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 8) return TRUE;
	*source_code = buf[0];
	*diag_code = buf[1];
	*time_of_fix = bGetSingle (&buf[2]);
	*week_num = bGetShort (&buf[6]);
	return FALSE;
}

short rpt_0x58 (TSIPPKT *rpt,
	unsigned char *op_code, unsigned char *data_type, unsigned char *sv_prn,
	unsigned char *data_length, unsigned char *data_packet)
/* GPS system data or acknowledgment of GPS system data load */
{
	unsigned char *buf, *buf4;
	short dl;
	ALM_INFO* alminfo;
	ION_INFO* ioninfo;
	UTC_INFO* utcinfo;
	NAV_INFO* navinfo;

	buf = rpt->buf;

	if (buf[0] == 2) {
		if (rpt->len < 4) return TRUE;
		if (rpt->len != 4+buf[3]) return TRUE;
	}
	else if (rpt->len != 3) {
		return TRUE;
	}
	*op_code = buf[0];
	*data_type = buf[1];
	*sv_prn = buf[2];
	if (*op_code == 2) {
		dl = buf[3];
		*data_length = (unsigned char)dl;
		buf4 = &buf[4];
		switch (*data_type) {
		case 2:
			/* Almanac */
			if (*data_length != sizeof (ALM_INFO)) return TRUE;
			alminfo = (ALM_INFO*)data_packet;
			alminfo->t_oa_raw  = buf4[0];
			alminfo->SV_health = buf4[1];
			alminfo->e         = bGetSingle(&buf4[2]);
			alminfo->t_oa      = bGetSingle(&buf4[6]);
			alminfo->i_0       = bGetSingle(&buf4[10]);
			alminfo->OMEGADOT  = bGetSingle(&buf4[14]);
			alminfo->sqrt_A    = bGetSingle(&buf4[18]);
			alminfo->OMEGA_0   = bGetSingle(&buf4[22]);
			alminfo->omega     = bGetSingle(&buf4[26]);
			alminfo->M_0       = bGetSingle(&buf4[30]);
			alminfo->a_f0      = bGetSingle(&buf4[34]);
			alminfo->a_f1      = bGetSingle(&buf4[38]);
			alminfo->Axis      = bGetSingle(&buf4[42]);
			alminfo->n         = bGetSingle(&buf4[46]);
			alminfo->OMEGA_n   = bGetSingle(&buf4[50]);
			alminfo->ODOT_n    = bGetSingle(&buf4[54]);
			alminfo->t_zc      = bGetSingle(&buf4[58]);
			alminfo->weeknum   = bGetShort(&buf4[62]);
			alminfo->wn_oa     = bGetShort(&buf4[64]);
			break;

		case 3:
			/* Almanac health page */
			if (*data_length != sizeof (ALH_PARMS) + 3) return TRUE;

			/* this record is returned raw */
			memcpy (data_packet, buf4, dl);
			break;

		case 4:
			/* Ionosphere */
			if (*data_length != sizeof (ION_INFO) + 8) return TRUE;
			ioninfo = (ION_INFO*)data_packet;
			ioninfo->alpha_0   = bGetSingle (&buf4[8]);
			ioninfo->alpha_1   = bGetSingle (&buf4[12]);
			ioninfo->alpha_2   = bGetSingle (&buf4[16]);
			ioninfo->alpha_3   = bGetSingle (&buf4[20]);
			ioninfo->beta_0    = bGetSingle (&buf4[24]);
			ioninfo->beta_1    = bGetSingle (&buf4[28]);
			ioninfo->beta_2    = bGetSingle (&buf4[32]);
			ioninfo->beta_3    = bGetSingle (&buf4[36]);
			break;

		case 5:
			/* UTC */
			if (*data_length != sizeof (UTC_INFO) + 13) return TRUE;
			utcinfo = (UTC_INFO*)data_packet;
			utcinfo->A_0       = bGetDouble (&buf4[13]);
			utcinfo->A_1       = bGetSingle (&buf4[21]);
			utcinfo->delta_t_LS = bGetShort (&buf4[25]);
			utcinfo->t_ot      = bGetSingle(&buf4[27]);
			utcinfo->WN_t      = bGetShort (&buf4[31]);
			utcinfo->WN_LSF    = bGetShort (&buf4[33]);
			utcinfo->DN        = bGetShort (&buf4[35]);
			utcinfo->delta_t_LSF = bGetShort (&buf4[37]);
			break;

		case 6:
			/* Ephemeris */
			if (*data_length != sizeof (NAV_INFO) - 1) return TRUE;

			navinfo = (NAV_INFO*)data_packet;

			navinfo->sv_number = buf4[0];
			navinfo->t_ephem = bGetSingle (&buf4[1]);
			navinfo->ephclk.weeknum = bGetShort (&buf4[5]);

			navinfo->ephclk.codeL2 = buf4[7];
			navinfo->ephclk.L2Pdata = buf4[8];
			navinfo->ephclk.SVacc_raw = buf4[9];
			navinfo->ephclk.SV_health = buf4[10];
			navinfo->ephclk.IODC = bGetShort (&buf4[11]);
			navinfo->ephclk.T_GD = bGetSingle (&buf4[13]);
			navinfo->ephclk.t_oc = bGetSingle (&buf4[17]);
			navinfo->ephclk.a_f2 = bGetSingle (&buf4[21]);
			navinfo->ephclk.a_f1 = bGetSingle (&buf4[25]);
			navinfo->ephclk.a_f0 = bGetSingle (&buf4[29]);
			navinfo->ephclk.SVacc = bGetSingle (&buf4[33]);

			navinfo->ephorb.IODE = buf4[37];
			navinfo->ephorb.fit_interval = buf4[38];
			navinfo->ephorb.C_rs = bGetSingle (&buf4[39]);
			navinfo->ephorb.delta_n = bGetSingle (&buf4[43]);
			navinfo->ephorb.M_0 = bGetDouble (&buf4[47]);
			navinfo->ephorb.C_uc = bGetSingle (&buf4[55]);
			navinfo->ephorb.e = bGetDouble (&buf4[59]);
			navinfo->ephorb.C_us = bGetSingle (&buf4[67]);
			navinfo->ephorb.sqrt_A = bGetDouble (&buf4[71]);
			navinfo->ephorb.t_oe = bGetSingle (&buf4[79]);
			navinfo->ephorb.C_ic = bGetSingle (&buf4[83]);
			navinfo->ephorb.OMEGA_0 = bGetDouble (&buf4[87]);
			navinfo->ephorb.C_is = bGetSingle (&buf4[95]);
			navinfo->ephorb.i_0 = bGetDouble (&buf4[99]);
			navinfo->ephorb.C_rc = bGetSingle (&buf4[107]);
			navinfo->ephorb.omega = bGetDouble (&buf4[111]);
			navinfo->ephorb.OMEGADOT=bGetSingle (&buf4[119]);
			navinfo->ephorb.IDOT = bGetSingle (&buf4[123]);
			navinfo->ephorb.Axis = bGetDouble (&buf4[127]);
			navinfo->ephorb.n = bGetDouble (&buf4[135]);
			navinfo->ephorb.r1me2 = bGetDouble (&buf4[143]);
			navinfo->ephorb.OMEGA_n=bGetDouble (&buf4[151]);
			navinfo->ephorb.ODOT_n = bGetDouble (&buf4[159]);
			break;
		}
	}
	return FALSE;
}

short rpt_0x59 (TSIPPKT *rpt,
	unsigned char *code_type,
	unsigned char status_code[32])
/* satellite enable/disable or health heed/ignore list */	
{
	short iprn;
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 33) return TRUE;
	*code_type = buf[0];
	for (iprn = 0; iprn < 32; iprn++)
		status_code[iprn] = buf[iprn + 1];
	return FALSE;
}

short rpt_0x5A (TSIPPKT *rpt,
	unsigned char *sv_prn,
	float *sample_length,
	float *signal_level,
	float *code_phase,
	float *Doppler,
	double *time_of_fix)
/* raw measurement data - code phase/Doppler */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 25) return TRUE;
	*sv_prn = buf[0];
	*sample_length = bGetSingle (&buf[1]);
	*signal_level = bGetSingle (&buf[5]);
	*code_phase = bGetSingle (&buf[9]);
	*Doppler = bGetSingle (&buf[13]);
	*time_of_fix = bGetDouble (&buf[17]);
	return FALSE;
}

short rpt_0x5B (TSIPPKT *rpt,
	unsigned char *sv_prn,
	unsigned char *sv_health,
	unsigned char *sv_iode,
	unsigned char *fit_interval_flag,
	float *time_of_collection,
	float *time_of_eph,
	float *sv_accy)
/* satellite ephorb status */	
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 16) return TRUE;
	*sv_prn = buf[0];
	*time_of_collection = bGetSingle (&buf[1]);
	*sv_health = buf[5];
	*sv_iode = buf[6];
	*time_of_eph = bGetSingle (&buf[7]);
	*fit_interval_flag = buf[11];
	*sv_accy = bGetSingle (&buf[12]);
	return FALSE;
}

short rpt_0x5C (TSIPPKT *rpt,
	unsigned char *sv_prn,
	unsigned char *slot,
	unsigned char *chan,
	unsigned char *acq_flag,
	unsigned char *eph_flag,
	float *signal_level,
	float *time_of_last_msmt,
	float *elev,
	float *azim,
	unsigned char *old_msmt_flag,
	unsigned char *integer_msec_flag,
	unsigned char *bad_data_flag,
	unsigned char *data_collect_flag)
/* satellite tracking status */
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 24) return TRUE;
	*sv_prn = buf[0];
	*slot = (buf[1] & 0x07) + 1;
	*chan = buf[1] >> 3;
	if (*chan == 0x10) *chan = 2;
	else (*chan)++;
	*acq_flag = buf[2];
	*eph_flag = buf[3];
	*signal_level = bGetSingle (&buf[4]);
	*time_of_last_msmt = bGetSingle (&buf[8]);
	*elev = bGetSingle (&buf[12]);
	*azim = bGetSingle (&buf[16]);
	*old_msmt_flag = buf[20];
	*integer_msec_flag = buf[21];
	*bad_data_flag = buf[22];
	*data_collect_flag = buf[23];
	return FALSE;
}

/**/
short rpt_0x6D (TSIPPKT *rpt,
	unsigned char *manual_mode,
	unsigned char *nsvs,
	unsigned char *ndim,
	unsigned char sv_prn[],
	float *pdop,
	float *hdop,
	float *vdop,
	float *tdop)
/* over-determined satellite selection for position fixes, PDOP, fix mode */
{
	short islot;
	unsigned char *buf;
	buf = rpt->buf;

	*nsvs = (buf[0] & 0xF0) >> 4;
	if ((*nsvs)>8) return TRUE;
	if (rpt->len != 17 + (*nsvs) ) return TRUE;

	*manual_mode = buf[0] & 0x08;
	*ndim  = (buf[0] & 0x07);
	*pdop = bGetSingle (&buf[1]);
	*hdop = bGetSingle (&buf[5]);
	*vdop = bGetSingle (&buf[9]);
	*tdop = bGetSingle (&buf[13]);
	for (islot = 0; islot < (*nsvs); islot++)
		sv_prn[islot] = buf[islot + 17];
	return FALSE;
}

short rpt_0x6E (TSIPPKT *rpt,
	unsigned char *subcode,
	unsigned char *enable,
	unsigned char *interval)
{
	if (rpt->len != 3) return TRUE;
	*subcode = rpt->buf[0];
	*enable = rpt->buf[1];
	*interval = rpt->buf[2];
	return FALSE;
}


/* note: 6F-03 has same structure */
short rpt_0x6F01 (TSIPPKT *rpt,
	struct cph1_msg_struct *cph)
{
	unsigned char *buf;
	int i, isv;
	unsigned short checksum;
	struct cph1_datablock_struct *cdb;
	int db_size, header_size;

	db_size=27;
	header_size=21;
	buf = rpt->buf;

	if (rpt->len < 2) return TRUE;
	cph->length = bGetShort (&buf[2]);

	if (rpt->len != cph->length + 1) return TRUE;

	cph->subcode = buf[0];
	cph->preamble = buf[1];
	cph->receive_time = bGetDouble (&buf[4]);
	cph->clock_offset = bGetDouble (&buf[12]);
	cph->numsvs = buf[20];
	buf += header_size;
	for (isv = 0; isv < cph->numsvs; isv++) {
		cdb = &cph->db[isv];
		cdb->prn = buf[0];
		cdb->flagbyte = buf[1];
		cdb->reserved = buf[2];
		cdb->elev = buf[3];
		cdb->azim = bGetShort (&buf[4]);
		cdb->signal_strength = buf[6];
		cdb->pseudorange = bGetDouble (&buf[7]);
		cdb->carrier_phase = bGetDouble (&buf[15]);
		cdb->Doppler = bGetSingle (&buf[23]);
		buf += db_size;
	}

	for (i = 1, checksum = 0; i < rpt->len - 3; i++) checksum += buf[i];
	cph->checksum = bGetShort(&buf[rpt->len - 3]);
	cph->postamble = buf[rpt->len - 1];
	return FALSE;
}

/**/
short rpt_0x70 (TSIPPKT *rpt, unsigned char *dyn_switch, unsigned char *static_switch,
	unsigned char *alt_switch, unsigned char *extra)

{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 4) return TRUE;
	*dyn_switch = buf[0];
	*static_switch = buf[1];
	*alt_switch = buf[2];
	*extra = buf[3];
	return FALSE;
}

short rpt_0x72 (TSIPPKT *rpt,
	short *pf,
	TSIP_POS_FILT_PARMS *params)
/* position-velocity filter parameters */
{
/*
 * The receiver reports the filter parameters as ints,
 * but in reality they are chars.  To preserve parallel structure
 * with the commands, they are jammed into chars here.
 * If there is an overflow, the routine responds with FALSE.
 */

	unsigned char *buf;
	short temp;
	buf = rpt->buf;

	if (rpt->len != 32) return TRUE;

	*pf = bGetShort (&buf[0]);
	params->flt1 = bGetSingle (&buf[2]);
	temp = bGetShort (&buf[6]);
	params->chr1 = (unsigned char)temp;
	temp = bGetShort (&buf[8]);
	params->chr2 = (unsigned char)temp;
	temp = bGetShort (&buf[10]);
	params->chr3 = (unsigned char)temp;
	temp = bGetShort (&buf[12]);
	params->chr4 = (unsigned char)temp;
	params->flt2 = bGetSingle(&buf[14]);
	params->flt3 = bGetSingle(&buf[18]);
	params->flt4 = bGetSingle(&buf[22]);
	params->flt5 = bGetSingle(&buf[26]);
	temp = bGetShort (&buf[30]);
	params->chr5 = (unsigned char)temp;
	return FALSE;
}

short rpt_0x74 (TSIPPKT *rpt,
	float *alt_filter_parm)
/* altitude filter parameters */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 4) return TRUE;
	*alt_filter_parm = bGetSingle(buf);
	return FALSE;
}

short rpt_0x78 (TSIPPKT *rpt,
	short *maxage)
/* DC max age parameters */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 2) return TRUE;
	*maxage = bGetShort (&buf[0]);
   return FALSE;
}

short rpt_0x7B (TSIPPKT *rpt,
	unsigned char *subcode,
	unsigned char *nmea_interval,
	unsigned long *nmea_mask)
/* NMEA Control parameters */
{
	if(rpt->len != 6) return TRUE;
	*subcode = rpt->buf[0];
	if (*subcode!= 0) return TRUE;
	*nmea_interval = rpt->buf[1];
	*nmea_mask = bGetLong(&rpt->buf[2]);
	return FALSE;
}

/**/
short rpt_0x82 (TSIPPKT *rpt,
	unsigned char *diff_mode)
/* differential fix mode */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 1) return TRUE;
	*diff_mode = buf[0];
	return FALSE;
}

short rpt_0x83 (TSIPPKT *rpt,
	double ECEF_pos[3],
	double *clock_bias,
	float *time_of_fix)
/* position, ECEF double precision */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 36) return TRUE;
	ECEF_pos[0] = bGetDouble (buf);
	ECEF_pos[1] = bGetDouble (&buf[8]);
	ECEF_pos[2] = bGetDouble (&buf[16]);
	*clock_bias  = bGetDouble (&buf[24]);
	*time_of_fix = bGetSingle (&buf[32]);
	return FALSE;
}

short rpt_0x84 (TSIPPKT *rpt,
	double *lat,
	double *lon,
	double *alt,
	double *clock_bias,
	float *time_of_fix)
/* position, lat-lon-alt double precision */	
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 36) return TRUE;
	*lat = bGetDouble (buf);
	*lon = bGetDouble (&buf[8]);
	*alt = bGetDouble (&buf[16]);
	*clock_bias = bGetDouble (&buf[24]);
	*time_of_fix = bGetSingle (&buf[32]);
	return FALSE;
}

short rpt_0x85 (TSIPPKT *rpt,
	unsigned char *sv_prn,
	unsigned char *summary_status,
	unsigned char *station_health,
	unsigned char *SV_UDRE_parm,
	unsigned char *iode1,
	unsigned char *iode2,
	float *z_cnt_tow,
	float *range_corr,
	float *range_rate_corr,
	float *delta_range_corr)
/* satellite differential correction info */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 22) return TRUE;
	*sv_prn = buf[0];
	*summary_status = buf[1];
	*station_health = buf[2];
	*SV_UDRE_parm = buf[3];
	*iode1 = buf[4];
	*iode2 = buf[5];
	*z_cnt_tow = bGetSingle (&buf[6]);
	*range_corr = bGetSingle (&buf[10]);
	*range_rate_corr = bGetSingle (&buf[14]);
	*delta_range_corr = bGetSingle (&buf[18]);
	return FALSE;
}


short rpt_0xBB(TSIPPKT *rpt,
	TSIP_RCVR_CFG *TsipxBB)
{

	unsigned char *buf;
	buf = rpt->buf;

	/* Manual  29473-00 Rev B. is in error.  Byte count is 40, not 41. */
	if (rpt->len != 40) return TRUE;

	TsipxBB->bSubcode		=	buf[0];
   if (TsipxBB->bSubcode == 0)
   {
		TsipxBB->operating_mode	=	buf[1]	;
		TsipxBB->dgps_mode		=	buf[2]	;
		TsipxBB->dyn_code			=	buf[3]	;
		TsipxBB->trackmode		=	buf[4]	;
		TsipxBB->elev_mask		=  bGetSingle (&buf[5]);
		TsipxBB->cno_mask			=	bGetSingle (&buf[9]);
		TsipxBB->dop_mask 		=  bGetSingle (&buf[13]);
		TsipxBB->dop_switch 	=  bGetSingle (&buf[17]);
		TsipxBB->dgps_age_limit	=	buf[21] ;
   }
   else if (TsipxBB->bSubcode == 3)
   {
		TsipxBB->operating_mode	=	buf[1]	;
		TsipxBB->dgps_mode		=	buf[2]	;
		TsipxBB->dyn_code			=	buf[3]	;
		TsipxBB->trackmode		=	buf[6]	;
		TsipxBB->elev_mask		=  	bGetSingle (&buf[15]);
		TsipxBB->cno_mask		=	bGetSingle (&buf[19]);
		TsipxBB->dop_mask 		=  	bGetSingle (&buf[23]);
		TsipxBB->dop_switch 	=  	bGetSingle (&buf[27]);
		TsipxBB->dgps_age_limit	=	buf[35] ;
   }
   else return TRUE;
	return FALSE;
}

short rpt_0xBC (TSIPPKT *rpt, unsigned char *port_num, unsigned char *in_baud,
	unsigned char *out_baud, unsigned char *data_bits,
	unsigned char *parity, unsigned char *stop_bits, unsigned char *flow_control,
	unsigned char *protocols_in, unsigned char *protocols_out, unsigned char *reserved)
/* Receiver serial port configuration */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 10) return TRUE;
	*port_num = buf[0];
	*in_baud = buf[1];
	*out_baud = buf[2];
	*data_bits = buf[3];
	*parity = buf[4];
	*stop_bits = buf[5];
	*flow_control = buf[6];
	*protocols_in = buf[7];
	*protocols_out = buf[8];
	*reserved = buf[9];

	return FALSE;
}

/**** Superpackets ****/

short rpt_0x8F03 (TSIPPKT *rpt,
	unsigned char *tx_baud_index,
	unsigned char *rx_baud_index,
	unsigned char *char_format_index,
	unsigned char *stop_bits,
	unsigned char *tx_mode_index,
	unsigned char *rx_mode_index)
/* Channel B configuration for dual port operation */
{
	unsigned char *buf;
	buf = rpt->buf;
	
	if (rpt->len != 7) return TRUE;
	*tx_baud_index = buf[1];
	*rx_baud_index = buf[2];
	*char_format_index = buf[3];
	*stop_bits = (buf[4] == 0x07) ? 1 : 2;
   	*tx_mode_index = buf[5];
	*rx_mode_index = buf[6];
	return FALSE;
}

short rpt_0x8F15 (TSIPPKT *rpt,
	short *datum_idx,
	double datum_coeffs[5])
/*  datum index and coefficients  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 43) return TRUE;
	*datum_idx = bGetShort(&buf[1]);
	datum_coeffs[0] = bGetDouble (&buf[3]);
	datum_coeffs[1] = bGetDouble (&buf[11]);
	datum_coeffs[2] = bGetDouble (&buf[19]);
	datum_coeffs[3] = bGetDouble (&buf[27]);
	datum_coeffs[4] = bGetDouble (&buf[35]);
	return FALSE;
}


short rpt_0x8F17 (TSIPPKT *rpt,
	unsigned char *UTM_grid_letter,
	short *UTM_grid_number,
	float *UTM_northing_value,
	float *UTM_easting_value,
	float *UTM_altitude,
	float *clock_bias,
	float *time_of_fix)
/*  UTM Single precision position response  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 24) return TRUE;
	*UTM_grid_letter    = buf[1];
	*UTM_grid_number    = bGetShort (&buf[2]);
	*UTM_northing_value = bGetSingle (&buf[ 4]);
	*UTM_easting_value  = bGetSingle (&buf[ 8]);
	*UTM_altitude       = bGetSingle (&buf[12]);
	*clock_bias         = bGetSingle (&buf[16]);
	*time_of_fix        = bGetSingle (&buf[20]);
	return FALSE;
}


short rpt_0x8F18 (TSIPPKT *rpt,
	unsigned char *UTM_grid_letter,
	short *UTM_grid_number,
	double *UTM_northing_value,
	double *UTM_easting_value,
	double *UTM_altitude,
	double *clock_bias,
	float *time_of_fix)
/*  UTM double precision position response  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 40) return TRUE;
	*UTM_grid_letter 	  = buf[1];
	*UTM_grid_number    = bGetShort (&buf[2]);
	*UTM_northing_value = bGetDouble (&buf[ 4]);
	*UTM_easting_value  = bGetDouble (&buf[12]);
	*UTM_altitude       = bGetDouble (&buf[20]);
	*clock_bias         = bGetDouble (&buf[28]);
	*time_of_fix        = bGetSingle (&buf[36]);
	return FALSE;
}


short rpt_0x8F19 (TSIPPKT *rpt,
   short *UTM_enabled)
/*  UTM position message enabled/disabled response  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 3) return TRUE;
	*UTM_enabled = (buf[2] == 'E') ? TRUE : FALSE;
	return FALSE;
}

#define MAX_LONG  (2147483648.)   /* 2**31 */
short rpt_0x8F20 (TSIPPKT *rpt,
	unsigned char *subpacket_id,
	unsigned char *info,
	double *lat,
	double *lon,
	double *alt,
	double vel_enu[],
	double *time_of_fix,
	short *week_num,
	unsigned char *nsvs,
	unsigned char sv_prn[],
	short sv_IODC[],
	short *datum_index)
{
	short
		isv;
	unsigned char
		*buf, prnx;
	unsigned long
		ulongtemp;
	long
		longtemp;
	double
		vel_scale;

	buf = rpt->buf;

	if (rpt->len != 56) return TRUE;
	*subpacket_id = buf[0];

	vel_scale = (buf[24]&1)? 0.020 : 0.005;
	vel_enu[0] = bGetShort (buf+2)*vel_scale;
	vel_enu[1] = bGetShort (buf+4)*vel_scale;
	vel_enu[2] = bGetShort (buf+6)*vel_scale;

	*time_of_fix = bGetULong (buf+8)*.001;

	longtemp = bGetLong (buf+12);
	*lat = longtemp*(GPS_PI/MAX_LONG);

	ulongtemp = bGetULong (buf+16);
	*lon = ulongtemp*(GPS_PI/MAX_LONG);
	if (*lon > GPS_PI) *lon -= 2.0*GPS_PI;

	*alt = bGetLong (buf+20)*.001;
	/* 25 blank; 29 = UTC */
	*datum_index = (short)buf[26] - 1;
	*info = buf[27];
	*nsvs = buf[28];
	*week_num = bGetShort (&buf[30]);
	for (isv = 0; isv < 8; isv++) {
		prnx = buf[32+2*isv];
		sv_prn[isv] = prnx&0x3F;
		sv_IODC[isv] = buf[32 + 2 * isv + 1] + (short)(prnx - sv_prn[isv]) * 4;
	}
	return FALSE;
}

short rpt_0x8F23 (TSIPPKT *rpt,
		unsigned char *subpacket_id,
      unsigned long *TOW,
      unsigned short *week,
      unsigned char *UTC_Offset,
      unsigned char *fix_type,
      long *lat,
		unsigned long *lon,
      long *alt,
      short *east,
      short *north,
      short *up)
/* Compact super packet */
{
	unsigned char
   	*buf;

	buf = rpt->buf;

	if (rpt->len != 29) return TRUE;

	*subpacket_id = buf[0];

	*TOW          = bGetULong(&buf[1])*.001;  /* convert from ms to s */
   *week         = bGetShort(&buf[5]);
   *UTC_Offset   = buf[7];
   *fix_type     = buf[8];

   *lat          = bGetLong (&buf[9]);
   *lon          = bGetULong(&buf[13]);
   *alt          = bGetLong (&buf[17]);

   *east         = bGetShort(&buf[21]);
   *north        = bGetShort(&buf[23]);
   *up           = bGetShort(&buf[25]);

	return FALSE;
}

short rpt_0x8F24 (TSIPPKT *rpt,
	short *shutdown_in,
	short *shutdown_len)
/*  LP Graceful Shutdown info  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 5) return TRUE;
	*shutdown_in  = bGetShort(&buf[1]);
	*shutdown_len = bGetShort(&buf[3]);
	return FALSE;
}

short rpt_0x8F25 (TSIPPKT *rpt,
	short *mode_mask)
/*  LP Modes  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 3) return TRUE;
	*mode_mask  = bGetShort(&buf[1]);
	return FALSE;
}

short rpt_0x8F26(TSIPPKT *rpt,
		  unsigned long *flash_write)
{
	unsigned char
		*buf;
	
	buf = rpt->buf;
   if (rpt->len != 5) return TRUE;
   *flash_write = bGetLong(&buf[1]);

   return FALSE;
}

short rpt_0x8F27 (TSIPPKT *rpt,
	unsigned long *ST_period,
	short 		  *ST_awake_time)
/*  LP Config info  */
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 14) return TRUE;
	*ST_period			= bGetULong(&buf[1]);
	*ST_awake_time		= bGetShort(&buf[5]);
	return FALSE;
}

short rpt_0x8F40 (TSIPPKT *rpt,
   	unsigned char *Flags,
      unsigned char *HeartBeatSentence,
      short *TopOfHourOffset,
      short *Frequency,
      char *VehicleID)
/* TAIP configuration &*/
{
	unsigned char *buf;
	buf = rpt->buf;

	if (rpt->len != 11) return TRUE;
	*Flags    			= buf[1];
	*HeartBeatSentence= buf[2];
	*TopOfHourOffset 	= bGetShort (&buf[3]);
	*Frequency  		= bGetShort (&buf[5]);
   VehicleID[0] = buf[7];
   VehicleID[1] = buf[8];
   VehicleID[2] = buf[9];
   VehicleID[3] = buf[10];
	return FALSE;
}
