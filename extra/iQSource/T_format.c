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
 * T_FORMAT.C and T_FORMAT.H contain primitive functions that prepare commands
 * to be transferred to the receiver.
 *
 * The module is in very portable, basic C language.  It can be used as is, or
 * with minimal changes if a TSIP communications application is needed separate
 * from TSIPCHAT. The construction of most argument lists avoid the use of
 * structures, but the developer is encouraged to reconstruct them using such
 * definitions to meet project requirements.  Declarations of TSIP_IFC.C
 * functions are included in TSIP_IFC.H to provide prototyping definitions.
 *
 * There are two types of functions:
 *
 * 1) send_cmd():  This command sends an assembled command in the TSIPKT
 * structure format thourgh the serial port using a user-supplied serial output
 * routine.  send_cmd adds all necessary control characters.
 *
 * 2) Command Functions:  Command functions come in the form cmd_0x??().
 * They translate a ser ies of command input parameters to a TSIPPKT structure.
 *
 * The functions cmd_0x??() are command string generators patterned after
 * the document called "Trimble Standard Interface Protocol" listed in
 * Appendix A of the "System Designer Reference Guide."  Examples of how to
 * enter the fields of these commands are given in TSIPCHAT routine
 * T_COMMND.C.  Because a TSIP command code may have different argument
 * lists depending on optional operating modes, there are more formatting
 * functions than command ID codes.  Each cmd_0x??() function corresponds to a
 * different functional mode for the command.  The following suffix convention
 * allows each function to serve a unique purpose and cleans up the argument
 * somewhat.
 *
 *             cmd_0x??q   -  query for current value
 * 	         cmd_0x??c   -  clear value (0x1D, 0x73 only)
 * 	         cmd_0x??s   -  set new values
 * 	         cmd_0x??e   -  enable
 * 	         cmd_0x??d   -  disable
 *
 *
 * *************************************************************************
 *
 */

#include <string.h>
#include "t_struct.h"
#include "t_format.h"

/**/
void send_cmd (TSIPPKT *cmd, short sendb(unsigned char))
/* formats a command for sending to TSIP receiver */
{
   unsigned char *cbuf, *cbufend;

	sendb (DLE);
	sendb (cmd->code);
   cbufend = cmd->buf + cmd->len;
	for (cbuf = cmd->buf; cbuf < cbufend; cbuf++) {
		if (*cbuf == DLE) sendb (DLE);
		sendb (*cbuf);
	}
	sendb (DLE);
	sendb (ETX);
}

/* for DOS machines, reverse order of bytes as they come through the
 * serial port. */
#define BYTESWAP

#ifdef BYTESWAP
static void bPutShort (void *in, unsigned char *out)
{
	unsigned char *inptr;

   inptr = (unsigned char*)in + 1;
   *out++ = *inptr--;
   *out = *inptr;
}

static void bPutFloat (float *in, unsigned char *out)
{
	unsigned char *inptr;

   inptr = (unsigned char*)in + 3;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out = *inptr;
}

static void bPutULong (unsigned long *in, unsigned char *out)
{
	unsigned char *inptr;

   inptr = (unsigned char*)in + 3;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out = *inptr;
}

static void bPutDouble (double *in, unsigned char *out)
{
	unsigned char *inptr;

   inptr = (unsigned char*)in + 7;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out++ = *inptr--;
   *out = *inptr;
}

#else	/* not BYTESWAP */

void bPutShort (short a, unsigned char *cmdbuf) {*(short*) cmdbuf = a;}
void bPutULong (long a, unsigned char *cmdbuf) 	{*(long*) cmdbuf = a;}
void bPutFloat (float a, unsigned char *cmdbuf) {*(float*) cmdbuf = a;}
void bPutDouble (double a, unsigned char *cmdbuf){*(double*) cmdbuf = a;}

#endif

/**/
void cmd_0x1Dc (TSIPPKT *cmd)
/* clear oscillator offset */
{
	cmd->buf[0] = 0x43;
	cmd->len = 1;
	cmd->code = 0x1D;
}

void cmd_0x1Ds  (TSIPPKT *cmd,
	float offset)
/* set oscillator offset */
{
	bPutFloat (&offset, &cmd->buf[0]);
	cmd->len = 4;
	cmd->code = 0x1D;
}

void cmd_0x1E (TSIPPKT *cmd, unsigned char reset_type)
/* clear battery back-up, then reset */
{
	cmd->buf[0] = reset_type;
	cmd->len = 1;
	cmd->code = 0x1E;
}

void cmd_0x1F (TSIPPKT *cmd)
/* request software versions */
{
	cmd->len = 0;
	cmd->code = 0x1F;
}

/**/
void cmd_0x20  (TSIPPKT *cmd, unsigned char sv_prn)
/* request almanac */
{
	cmd->buf[0] = sv_prn;
	cmd->len = 1;
	cmd->code = 0x20;
}

void cmd_0x21 (TSIPPKT *cmd)
/* request current time */
{
	cmd->len = 0;
	cmd->code = 0x21;
}

void cmd_0x22 (TSIPPKT *cmd, unsigned char nav_mode)
/* select position fix mode (2D, 3D, ...) */
{
	cmd->buf[0] = nav_mode;
	cmd->len = 1;
	cmd->code = 0x22;
}

void cmd_0x23  (TSIPPKT *cmd, float pos_ECEF[3])
/* initial position in ECEF coordinates */
{
	bPutFloat (&pos_ECEF[0], &cmd->buf[0]);
	bPutFloat (&pos_ECEF[1], &cmd->buf[4]);
	bPutFloat (&pos_ECEF[2], &cmd->buf[8]);
	cmd->len = 12;
	cmd->code = 0x23;
}

void cmd_0x24 (TSIPPKT *cmd)
/* request position fix mode */
{
	cmd->len = 0;
	cmd->code = 0x24;
}

void cmd_0x25 (TSIPPKT *cmd)
/* initiate soft reset & self-test (equivalent to power cycle) */
{
	cmd->len = 0;
	cmd->code = 0x25;
}

void cmd_0x26 (TSIPPKT *cmd)
/* request receiver health */
{
	cmd->len = 0;
	cmd->code = 0x26;
}

void cmd_0x27 (TSIPPKT *cmd)
/* request signal levels */
{
	cmd->len = 0;
	cmd->code = 0x27;
}

void cmd_0x28 (TSIPPKT *cmd)
/* request GPS system message */
{
	cmd->len = 0;
	cmd->code = 0x28;
}

void cmd_0x29 (TSIPPKT *cmd)
/* request almanac health */
{
	cmd->len = 0;
	cmd->code = 0x29;
}

void cmd_0x2Aq (TSIPPKT *cmd)
/* query altitude for 2-D mode */
{
	cmd->len = 0;
	cmd->code = 0x2A;
}

void cmd_0x2As  (TSIPPKT *cmd, float alt)
/* altitude for 2-D mode */
{
	bPutFloat (&alt, &cmd->buf[0]);
	cmd->len = 4;
	cmd->code = 0x2A;
}

void cmd_0x2Ad (TSIPPKT *cmd)
/* disable altitude for 2-D mode */
{
	cmd->buf[0] = 0xFF;
	cmd->len = 1;
	cmd->code = 0x2A;
}

void cmd_0x2B  (TSIPPKT *cmd, float lat, float lon, float alt)
/* initial position (latitude-longitude-altitude) */
{
	bPutFloat (&lat, &cmd->buf[0]);
	bPutFloat (&lon, &cmd->buf[4]);
	bPutFloat (&alt, &cmd->buf[8]);
	cmd->len = 12;
	cmd->code = 0x2B;
}

void cmd_0x2Cq (TSIPPKT *cmd)
/* request operating parameters and masks */
{
	float negative_one;
   negative_one = -1.0;
	cmd->buf[0] = 0;
	bPutFloat (&negative_one, &cmd->buf[1]);
	bPutFloat (&negative_one, &cmd->buf[5]);
	bPutFloat (&negative_one, &cmd->buf[9]);
	bPutFloat (&negative_one, &cmd->buf[13]);
	cmd->len = 17;
	cmd->code = 0x2C;
}

void cmd_0x2Cs (TSIPPKT *cmd,
	unsigned char dyn_code,
	float elev_mask, float snr,
	float pdop_mask, float pdop_switch)
/* set operating parameters and masks */
{
	cmd->buf[0] = dyn_code;
	bPutFloat (&elev_mask, &cmd->buf[1]);
	bPutFloat (&snr, &cmd->buf[5]);
	bPutFloat (&pdop_mask, &cmd->buf[9]);
	bPutFloat (&pdop_switch, &cmd->buf[13]);
	cmd->len = 17;
	cmd->code = 0x2C;
}

void cmd_0x2D (TSIPPKT *cmd)
/* request oscillator offset */
{
	cmd->len = 0;
	cmd->code = 0x2D;
}

void cmd_0x2E  (TSIPPKT *cmd, float time_of_week, short week_num)
/* set GPS time */
{
	bPutFloat (&time_of_week, &cmd->buf[0]);
	bPutShort (&week_num, &cmd->buf[4]);
	cmd->len = 6;
	cmd->code = 0x2E;
}

void cmd_0x2F (TSIPPKT *cmd)
/* request UTC params */
{
	cmd->len = 0;
	cmd->code = 0x2F;
}

/**/
void cmd_0x31  (TSIPPKT *cmd, float ECEF_pos[3])
/* initial accurate position in ECEF coordinates */
{
	bPutFloat (&ECEF_pos[0], &cmd->buf[0]);
	bPutFloat (&ECEF_pos[1], &cmd->buf[4]);
	bPutFloat (&ECEF_pos[2], &cmd->buf[8]);
	cmd->len = 12;
	cmd->code = 0x31;
}

void cmd_0x32  (TSIPPKT *cmd, float lat, float lon, float alt)
/* initial accurate position in latitude-longitude-altitude */
{
	bPutFloat (&lat, &cmd->buf[0]);
	bPutFloat (&lon, &cmd->buf[4]);
	bPutFloat (&alt, &cmd->buf[8]);
	cmd->len = 12;
	cmd->code = 0x32;
}

void cmd_0x35q  (TSIPPKT *cmd)
/* request serial I/O options */
{
	cmd->len = 0;
	cmd->code = 0x35;
}

void cmd_0x35s  (TSIPPKT *cmd, unsigned char pos_code, unsigned char vel_code,
	unsigned char time_code, unsigned char opts_code)
/* set serial I/O options */
{
	cmd->buf[0] = pos_code;
	cmd->buf[1] = vel_code;
	cmd->buf[2] = time_code;
	cmd->buf[3] = opts_code;
	cmd->len = 4;
	cmd->code = 0x35;
}

void cmd_0x37 (TSIPPKT *cmd)
/* request last position, velocity, and status */
{
	cmd->len = 0;
	cmd->code = 0x37;
}

void cmd_0x38q  (TSIPPKT *cmd, unsigned char data_type, unsigned char sv_prn)
/* request GPS system data (binary) */
{
	cmd->buf[0] = 1;
	cmd->buf[1] = data_type;
	cmd->buf[2] = sv_prn;
	cmd->len = 3;
	cmd->code = 0x38;
}

void cmd_0x38s  (TSIPPKT *cmd, unsigned char data_type, unsigned char sv_prn,
	unsigned char data_length, unsigned char *databuf)
/* load GPS system data (binary) */
{
	cmd->buf[0] = 2;
	cmd->buf[1] = data_type;
	cmd->buf[2] = sv_prn;
	cmd->buf[3] = data_length;
	memcpy (&cmd->buf[4], databuf, (short)data_length);
	cmd->len = (short)data_length + 4;
	cmd->code = 0x38;
}

void cmd_0x39  (TSIPPKT *cmd, unsigned char op_code, unsigned char sv_prn)
/* set or request enable/health-heed status of satellites */
{
	cmd->buf[0] = op_code;
	cmd->buf[1] = sv_prn;
	cmd->len = 2;
	cmd->code = 0x39;
}

void cmd_0x3A  (TSIPPKT *cmd, unsigned char sv_prn)
/* request last code-phase/Doppler measurement */
{
	cmd->buf[0] = sv_prn;
	cmd->len = 1;
	cmd->code = 0x3A;
}

void cmd_0x3B  (TSIPPKT *cmd, unsigned char sv_prn)
/* request eph status */
{
	cmd->buf[0] = sv_prn;
	cmd->len = 1;
	cmd->code = 0x3B;
}

void cmd_0x3C  (TSIPPKT *cmd, unsigned char sv_prn)
/* request tracking status */
{
	cmd->buf[0] = sv_prn;
	cmd->len = 1;
	cmd->code = 0x3C;
}

void cmd_0x3Dq (TSIPPKT *cmd)
/* request Channel A configuration for dual-port operation */
{
	cmd->len = 0;
	cmd->code = 0x3D;
}

void cmd_0x3Ds (TSIPPKT *cmd,
	unsigned char baud_out, unsigned char baud_inp,
   unsigned char char_code, unsigned char stopbitcode,
   unsigned char output_mode, unsigned char input_mode)
/* set Channel A configuration for dual-port operation */
{
	cmd->buf[0] = baud_out;		/* XMT baud rate */
	cmd->buf[1] = baud_inp;		/* RCV baud rate */
	cmd->buf[2] = char_code;	   /* parity and #bits per byte */
	cmd->buf[3] = stopbitcode;	/* number of stop bits code */
	cmd->buf[4] = output_mode;	/* Ch. A transmission mode */
	cmd->buf[5] = input_mode;	/* Ch. A reception mode */
	cmd->len = 6;
	cmd->code = 0x3D;
}

/**/
void cmd_0x62q (TSIPPKT *cmd)
/* query DGPS fix mode */
{
	cmd->buf[0] = 0xFF;
	cmd->len = 1;
	cmd->code = 0x62;
}

void cmd_0x62s (TSIPPKT *cmd,
	unsigned char dgps_mode)
/* set DGPS fix mode */
{
	cmd->buf[0] = dgps_mode;
	cmd->len = 1;
	cmd->code = 0x62;
}

void cmd_0x65  (TSIPPKT *cmd, unsigned char sv_prn)
/* request satellite differential correction info */
{
	cmd->buf[0] = sv_prn;
	cmd->len = 1;
	cmd->code = 0x65;
}

void cmd_0x6Eq  (TSIPPKT *cmd,
	unsigned char subcode)
/* query synch measurement control */
{
	cmd->buf[0] = subcode;
	cmd->len = 1;
	cmd->code = 0x6E;
}

void cmd_0x6Ed  (TSIPPKT *cmd,
	unsigned char subcode)
/* disable synch measurement */
{
	cmd->buf[0] = subcode;
	cmd->buf[1] = 0;
	cmd->buf[2] = 0;
	cmd->len = 3;
	cmd->code = 0x6E;
}

void cmd_0x6Es  (TSIPPKT *cmd,
	unsigned char subcode,
   unsigned char interval)
/* enable synchmeasurement */
{
	cmd->buf[0] = subcode;
	cmd->buf[1] = 1;
	cmd->buf[2] = interval;
	cmd->len = 3;
	cmd->code = 0x6E;
}

/**/
void cmd_0x70q (TSIPPKT *cmd)
{
	cmd->len = 0;
	cmd->code = 0x70;
}

void cmd_0x70s  (TSIPPKT *cmd,
	unsigned char dyn_switch,
	unsigned char static_switch,
	unsigned char alt_switch,
	unsigned char extra)
{
	cmd->buf[0] = dyn_switch;
	cmd->buf[1] = static_switch;
	cmd->buf[2] = alt_switch;
	cmd->buf[3] = extra;
	cmd->len = 4;
	cmd->code = 0x70;
}

void cmd_0x71q (TSIPPKT *cmd)
/* request position-velocity filter parameters */
{
	cmd->len = 0;
	cmd->code = 0x71;
}

void cmd_0x71s (TSIPPKT *cmd,
	short pf,
   TSIP_POS_FILT_PARMS *params)
/* enable position-velocity filter with default parameters */
{
	cmd->buf[0] = pf;
	bPutFloat (&params->flt1, &cmd->buf[1]);
	cmd->buf[5] = params->chr1;
	cmd->buf[6] = params->chr2;
	cmd->buf[7] = params->chr3;
	cmd->buf[8] = params->chr4;
	bPutFloat (&params->flt2, &cmd->buf[9]);
	bPutFloat (&params->flt3, &cmd->buf[13]);
	bPutFloat (&params->flt4, &cmd->buf[17]);
	bPutFloat (&params->flt5, &cmd->buf[21]);
	cmd->buf[25] = params->chr5;
	cmd->len = 26;
	cmd->code = 0x71;
}

void cmd_0x73q (TSIPPKT *cmd)
/* request altitude filter parameters */
{
	cmd->len = 0;
	cmd->code = 0x73;
}

void cmd_0x73s (TSIPPKT *cmd,
	float time_constant)
/* set altitude filter parameters */
{
	bPutFloat (&time_constant, &cmd->buf[0]);
	cmd->len = 4;
	cmd->code = 0x73;
}

void cmd_0x73d (TSIPPKT *cmd)
/* disable altitude filter */
{
	float ftemp;

   ftemp = 1.0;
	bPutFloat (&ftemp, &cmd->buf[0]);
	cmd->len = 4;
	cmd->code = 0x73;
}

void cmd_0x73c (TSIPPKT *cmd)
/* set altitude filter parameters to default */
{
	float ftemp;

   ftemp = 0.0;
	bPutFloat (&ftemp, &cmd->buf[0]);
	cmd->len = 4;
	cmd->code = 0x73;
}

void cmd_0x77q (TSIPPKT *cmd)
/* request DC max age */
{
	cmd->len = 0;
	cmd->code = 0x77;
}

void cmd_0x77s (TSIPPKT *cmd,
	short maxage)
/* request DC max age */
{
	cmd->buf[0]= maxage >> 8;
	cmd->buf[1]= maxage & 0x00ff;
	cmd->len = 2;
	cmd->code = 0x77;
}

void cmd_0x7A_0s  (TSIPPKT *cmd,
	unsigned char nmea_interval,
	unsigned long nmea_mask)
/* set NMEA interval [and message mask] */
{

	cmd->buf[0] = 0;		/* subcode */
	cmd->buf[1] = nmea_interval;
	bPutULong (&nmea_mask, &cmd->buf[2]);
	cmd->len = 6;
	cmd->code = 0x7A;
}

void cmd_0x7A_0q  (TSIPPKT *cmd)
/* request NMEA interval and message mask */
{

	cmd->buf[0] = 0;		/* subcode */
	cmd->len = 1;
	cmd->code = 0x7A;
}


void cmd_0xBBs(TSIPPKT *cmd,
	TSIP_RCVR_CFG *TsipxBB)
	/* set Stinger receiver configuration */
{

	/* Manual  29473-00 Rev B. is in error.  Byte count is 40, not 41. */
	cmd->len		= 40;
	cmd->code	= 0xBB;
   memset (cmd->buf, 0, cmd->len);	/* set reserved bytes to 0 */
   if (TsipxBB->bSubcode == 0)
   {
		cmd->buf[0]	=	0;
		cmd->buf[1]	=	TsipxBB->operating_mode;
		cmd->buf[2]	=	TsipxBB->dgps_mode;
		cmd->buf[3]	=	TsipxBB->dyn_code;
/*		cmd->buf[4]	=	TsipxBB->trackmode; not changeable in v7.52 or 7.68 */
		bPutFloat (&TsipxBB->elev_mask, &cmd->buf[5]);
		bPutFloat (&TsipxBB->cno_mask, &cmd->buf[9]);
		bPutFloat (&TsipxBB->dop_mask, &cmd->buf[13]);
		bPutFloat (&TsipxBB->dop_switch, &cmd->buf[17]);
		cmd->buf[21]	=	TsipxBB->dgps_age_limit;
   }
   else if (TsipxBB->bSubcode == 3)
   {
		cmd->buf[0]	=	3;
		cmd->buf[1]	=	TsipxBB->operating_mode;
		cmd->buf[2]	=	TsipxBB->dgps_mode;
		cmd->buf[3]	=	TsipxBB->dyn_code;
		cmd->buf[6]	=	TsipxBB->trackmode;
		bPutFloat (&TsipxBB->elev_mask, &cmd->buf[15]);
		bPutFloat (&TsipxBB->cno_mask, &cmd->buf[19]);
		bPutFloat (&TsipxBB->dop_mask, &cmd->buf[23]);
		bPutFloat (&TsipxBB->dop_switch, &cmd->buf[27]);
		cmd->buf[35]	=	TsipxBB->dgps_age_limit;
   }
}

void cmd_0xBBq (TSIPPKT *cmd,
	unsigned char subcode)
{

	cmd->len = 1;
	cmd->code = 0xBB;
	cmd->buf[0] = subcode;
}

void cmd_0xBCq  (TSIPPKT *cmd, unsigned char port_num)
/* request receiver port configuration */
{

	cmd->buf[0] = port_num;
	cmd->len = 1;
	cmd->code = 0xBC;
}

void cmd_0xBCs  (TSIPPKT *cmd,
	unsigned char port_num,
	unsigned char in_baud,
	unsigned char out_baud,
	unsigned char data_bits,
	unsigned char parity,
	unsigned char stop_bits,
	unsigned char flow_control,
	unsigned char protocols_in,
	unsigned char protocols_out,
	unsigned char reserved)
/* set receiver port configuration */
{

	cmd->buf[0] = port_num;
	cmd->buf[1] = in_baud;
	cmd->buf[2] = out_baud;
	cmd->buf[3] = data_bits;
	cmd->buf[4] = parity;
	cmd->buf[5] = stop_bits;
	cmd->buf[6] = flow_control;
	cmd->buf[7] = protocols_in;
	cmd->buf[8] = protocols_out;
	cmd->buf[9] = reserved;
	cmd->len = 10;
	cmd->code = 0xBC;
}

/**** Superpackets ****/
void cmd_0x8E03q (TSIPPKT *cmd)
/* request Channel B configuration for dual-port operation */
{
	cmd->len = 1;
	cmd->code = 0x8E;
   cmd->buf[0] = 0x03;
}

void cmd_0x8E03s (TSIPPKT *cmd,
	unsigned char baud_out, unsigned char baud_inp,
   unsigned char char_code, unsigned char stopbitcode,
   unsigned char output_mode, unsigned char input_mode)
/* set Channel B configuration for dual-port operation */
{
	cmd->buf[0] = 0x03;
	cmd->buf[1] = baud_out;		/* XMT baud rate */
	cmd->buf[2] = baud_inp;		/* RCV baud rate */
	cmd->buf[3] = char_code;	   /* parity and #bits per byte */
	cmd->buf[4] = stopbitcode;	/* number of stop bits code */
	cmd->buf[5] = output_mode;	/* Ch. A transmission mode */
	cmd->buf[6] = input_mode;	/* Ch. A reception mode */
	cmd->len = 7;
	cmd->code = 0x8E;
}

void cmd_0x8E15q  (TSIPPKT *cmd)
/* datum query */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x15;
}

void cmd_0x8E15s  (TSIPPKT *cmd, unsigned char datum_index)
/* datum set - standard parameters */
{

	cmd->buf[0] = 0x15;
	cmd->buf[1] = 0;	/* datum index is a short; this is always 0 */
	cmd->buf[2] = datum_index;
	cmd->len = 3;
	cmd->code = 0x8E;
}

void cmd_0x8E15s_2  (TSIPPKT *cmd, double datum_coeffs[5])
/* datum set - special parameters */
{

	cmd->buf[0] = 0x15;  /*Subcode 15 */
	bPutDouble (&datum_coeffs[0], &cmd->buf[1]);
	bPutDouble (&datum_coeffs[1], &cmd->buf[9]);
	bPutDouble (&datum_coeffs[2], &cmd->buf[17]);
	bPutDouble (&datum_coeffs[3], &cmd->buf[25]);
	bPutDouble (&datum_coeffs[4], &cmd->buf[33]);
	cmd->len = 41;
	cmd->code = 0x8E;
}

void cmd_0x8E19q (TSIPPKT *cmd)
/* UTM msg status */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x19;
}

void cmd_0x8E19e (TSIPPKT *cmd)
/* UTM msg enable/disable */
{

	cmd->len = 2;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x19;
	cmd->buf[1] = 0x45;
}

void cmd_0x8E19d (TSIPPKT *cmd)
/* UTM msg enable/disable */
{

	cmd->len = 2;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x19;
	cmd->buf[1] = 0x44;
}

void cmd_0x8E20q (TSIPPKT *cmd)
/* UTM SP msg query */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x20;
}

void cmd_0x8E20d (TSIPPKT *cmd)
/* 8F-20 msg auto-output disable */
{

	cmd->len = 2;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x20;
	cmd->buf[1] = 0;
}

void cmd_0x8E20e (TSIPPKT *cmd)
/* 8F-20 msg auto-output enable */
{

	cmd->len = 2;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x20;
	cmd->buf[1] = 1;
}

void cmd_0x8E24q  (TSIPPKT *cmd)
/* LP Graceful Shutdown query */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x24;
}

void cmd_0x8E24s  (TSIPPKT *cmd, short shutdown_in, short shutdown_len)
/* LP Graceful Shutdown set */
{

	cmd->len = 5;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x24;
	bPutShort (&shutdown_in, &cmd->buf[1]); 
	bPutShort (&shutdown_len, &cmd->buf[3]);
}

void cmd_0x8E25q  (TSIPPKT *cmd)
/* LP Modes query */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x25;
}

void cmd_0x8E25s  (TSIPPKT *cmd, short mode_mask)
/* LP Modes set */
{
	cmd->len = 3;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x25;
   mode_mask &= (short)0xFFFD;  /* bit 1 is reserved and must be 0 */
	bPutShort (&mode_mask, &cmd->buf[1]);
}

void cmd_0x8E26s (TSIPPKT *cmd)
/* 8F-26 save to Flash memory */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x26;
}

void cmd_0x8E27q  (TSIPPKT *cmd)
/* LP Configuration query */
{

	cmd->len = 1;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x27;
}

void cmd_0x8E27s  (TSIPPKT *cmd,
	unsigned long ST_period,
	short 		  ST_awake_time)
/* LP Configuration set */
{
	cmd->len = 14;
	cmd->code = 0x8E;
	cmd->buf[0] = 0x27;
	bPutULong (&ST_period, &cmd->buf[1]);
   bPutShort(&ST_awake_time, &cmd->buf[5]);
   cmd->buf[7] = 0;
   cmd->buf[8] = 0;
   cmd->buf[9] = 0;
   cmd->buf[10] = 0;
   cmd->buf[11] = 0;
   cmd->buf[12] = 0;
   cmd->buf[13] = 0;
}

void cmd_0x8E40q (TSIPPKT *cmd)
{
	cmd->len = 1;
   cmd->code = 0x8E;
   cmd->buf[ 0] = 0x40;
}

void cmd_0x8E40s (TSIPPKT *cmd,
	unsigned char Flags,
	unsigned char HeartBeatSentence,
   short TopOfHourOffset,
	short Frequency,
   char VehicleID[4])
{
	cmd->len = 11;
   cmd->code = 0x8E;
   cmd->buf[ 0] = 0x40;
   cmd->buf[ 1] = Flags;
   cmd->buf[ 2] = HeartBeatSentence;
   bPutShort (&TopOfHourOffset, &cmd->buf[3]);
   bPutShort (&Frequency, &cmd->buf[5]);
   cmd->buf[ 7] = VehicleID[0];
   cmd->buf[ 8] = VehicleID[1];
   cmd->buf[ 9] = VehicleID[2];
   cmd->buf[10] = VehicleID[3];
}

void cmd_0x8E  (TSIPPKT *cmd, unsigned char hexbyte[], unsigned char hexnum)
/* turn on superpacket, etc. */
{
	memcpy (cmd->buf, hexbyte, (short)hexnum);
	cmd->len = hexnum;
	cmd->code = 0x8E;
}

void cmd_0xxx  (TSIPPKT *cmd, unsigned char hexcode, unsigned char hexbyte[], unsigned char hexnum)
/* turn on superpacket, etc. */
{
	memcpy (cmd->buf, hexbyte, (short)hexnum);
	cmd->len = hexnum;
	cmd->code = hexcode;
}

