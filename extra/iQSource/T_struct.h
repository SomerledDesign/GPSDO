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
 * Vers	Date		   Changes										 			Author
 * ----	---------   ----------------------------------------	   ----------
 * v1.40
 * 7.52a			   	matched 7.52 manual									pvwl
 *	0.99d	 9/15/99    split from TSIP_IFC.C								pah
 * *************************************************************************
 *
 * This header file contains definitions for general TSIP data structures
 *
 * This source code is supplied without warranty and is intended only as
 * sample source code for exercising the TSIP interface.  We do appreciate
 * comments and try to support the software as much as possible.
 *
 * *************************************************************************
 *
 */
 #define TSIP_VERNUM "7.82"

#ifndef FALSE
#define FALSE 	(0)
#define TRUE 	(!FALSE)
#endif
#define GPS_PI 	(3.1415926535898)
#define	D2R		(GPS_PI/180.0)
#define	R2D		(180.0/GPS_PI)
#define WEEK 	(604800.)
#define MAXCHAN  (8)

/* control characters for TSIP packets */
#define DLE 	(0x10)
#define ETX 	(0x03)

#define MAX_RPTBUF (256)

/* values of TSIPPKT.status */
#define TSIP_PARSED_EMPTY 	0
#define TSIP_PARSED_FULL 	1
#define TSIP_PARSED_DLE_1 	2
#define TSIP_PARSED_DATA 	3
#define TSIP_PARSED_DLE_2 	4

/* TSIP packets have the following structure, whether report or command. */
typedef struct {
	short
		counter,				/* counter */
      len;				/* size of buf; < MAX_RPTBUF unsigned chars */
	unsigned char
		status,			 /* TSIP packet format/parse status */
		code;				/* TSIP code */
	unsigned char
		buf[MAX_RPTBUF];	/* report or command string */
} TSIPPKT;

/* TSIP binary data structures */
typedef struct {
	unsigned char
		t_oa_raw, SV_health;
	float
		e, t_oa, i_0, OMEGADOT, sqrt_A,
		OMEGA_0, omega, M_0, a_f0, a_f1,
		Axis, n, OMEGA_n, ODOT_n, t_zc;
	short
		weeknum, wn_oa;
} ALM_INFO;

typedef struct {     /*  Almanac health page (25) parameters  */
	unsigned char
		WN_a, SV_health[32], t_oa;
} ALH_PARMS;

typedef struct {     /*  Universal Coordinated Time (UTC) parms */
	double
		A_0;
	float
		A_1;
	short
		delta_t_LS;
	float
		t_ot;
	short
		WN_t, WN_LSF, DN, delta_t_LSF;
} UTC_INFO;

typedef struct {      /*  Ionospheric info (float)  */
	float
		alpha_0, alpha_1, alpha_2, alpha_3,
		beta_0, beta_1, beta_2, beta_3;
} ION_INFO;

typedef struct {      /*  Subframe 1 info (float)  */
	short
		weeknum;
	unsigned char
		codeL2, L2Pdata, SVacc_raw, SV_health;
	short
		IODC;
	float
		T_GD, t_oc, a_f2, a_f1, a_f0, SVacc;
} EPHEM_CLOCK;

typedef	struct {     /*  Ephemeris info (float)  */
	unsigned char
		IODE, fit_interval;
	float
		C_rs, delta_n;
	double
		M_0;
	float
		C_uc;
	double
		e;
	float
		C_us;
	double
		sqrt_A;
	float
		t_oe, C_ic;
	double
		OMEGA_0;
	float
		C_is;
	double
		i_0;
	float
		C_rc;
	double
		omega;
	float
		OMEGADOT, IDOT;
	double
		Axis, n, r1me2, OMEGA_n, ODOT_n;
} EPHEM_ORBIT;

typedef struct {     /* Navigation data structure */
	short
		sv_number;     /* SV number (0 = no entry) */
	float
		t_ephem;       /* time of ephemeris collection */
	EPHEM_CLOCK
		ephclk;        /* subframe 1 data */
	EPHEM_ORBIT
		ephorb;        /* ephemeris data */
} NAV_INFO;

typedef struct {
	float
		flt1;
	unsigned char
		chr1, chr2, chr3, chr4;
	float
		flt2, flt3, flt4, flt5;
	unsigned char
		chr5;
} TSIP_POS_FILT_PARMS;

typedef struct {
	unsigned char
		bSubcode,
		operating_mode,
		dgps_mode,
		dyn_code,
		trackmode;
	float
		elev_mask,
		cno_mask,
		dop_mask,
		dop_switch;
	unsigned char
		dgps_age_limit;
} TSIP_RCVR_CFG;

typedef struct cph1_datablock_struct {
	unsigned char prn, flagbyte, reserved;
	signed char elev;
	short azim;
	unsigned char signal_strength;
	double pseudorange, carrier_phase;
	float Doppler;
};

typedef struct cph1_msg_struct {
	unsigned char subcode, preamble;
	unsigned short length;
	double receive_time, clock_offset;
	unsigned char numsvs;
	struct cph1_datablock_struct db[MAXCHAN];
	unsigned short checksum;
	unsigned char postamble;
};
