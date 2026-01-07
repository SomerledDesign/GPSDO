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
 * TSIP_UTL.C contains five types of functions:
 *
 * 1) Borland-compatible window control functions:  The Borland version of
 * TSIPCHAT supports two windows: a command and report window and an auto
 * window.  The command and report window displays the command list, command
 * entries and parameters, and display of requested packets.  The auto window
 * scrolls through unrequested reports, which are generated according to the
 * I/O options specified.
 *
 * The following are Borland C++ functions used to create text windows.  If
 * suitable functions can be found in the Microsoft Visual C++ Compiler, the
 * windowing feaures may be recreated. (Creating TSIPCHAT without BORLAND
 * defined results in all commands, both auto and requested, scrolling up the
 * screen.)
 *
 *    ;; create a window
 *    void window (short left, short top, short right, short bottom)
 *
 *    ;; set backgrounf and foreground colors
 *    void textattr (char attr)
 *
 *    ;; go to row x, colw y w.r.t window origin
 *    void gotoxy (short x, short y)
 *
 *    ;; report row relative to window origin
 *    short wherex (void)
 *
 *    ;; report column relative to window origin
 *    short wherey (void)
 *
 *    ;; clear window to the end of the line
 *    void clrscr (void), clreol (void)
 *
 *    ;; get text attributes
 *    void gettextinfo (struct *textinfo)
 *
 * 2) User interface functions:  Specifically, these are functions that query
 * integer, double, or YES/NO inputs.  There is also a function for toggling
 * file storage on and off.
 *
 * 3) Storage file functions:  These functions open and close binary
 * storage files.
 *
 * 4) DOS-specific time functions:  These functions synchronize the receiver
 * and PC clocks.
 *
 * 5) Serial port functions:  These functions set serial port
 * parameters.  They are DOS-specific.
 *
 * *************************************************************************
 *
 */

#define END_STRING '\0'
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <time.h>
#include "t_struct.h"
#include "t_format.h"
#include "t_parser.h"
#include "tsipincl.h"

/**/
/*  *******************  1. CONSOLE WINDOW CONTROL ****************** */
/*
 * The following routines set up two windows: one which prints only
 * commands and requested reports, the other only unrequested reports.
 * The routines are set up for Borland compilers.  Similar functions can
 * be found with Microsoft compilers.  Generic versions are included
 * for non-Borland compilers.
 */

/* backspace, enter, printable characters except control characters */
#include <conio.h>

/* text attributes for different screen functions */
static short
	auto_y,
	text_color[3];
static struct text_info
	t_info,
	w_info[2];

/* current window = command or requested reply, or auto report */
/* TRUE if current window is command window */
static short
	curr_win = AUTOWIN;

void show_crlf (void)
{
	clreol ();
	cprintf ("\r\n");
	clreol ();
}

short which_window (void)
{
	return (curr_win);
}

void switch_window (short new_win)
{
	struct text_info *old_info, *new_info;

	old_info = &w_info[curr_win];
	gettextinfo (old_info);
	if (new_win == curr_win) {
		return;
	}
	curr_win = new_win;
	new_info = &w_info[curr_win];

	switch (new_win) {
	case AUTOWIN:
		/* auto window is the bottom of the screen; unrequested reports */
		/* are printed here in scrolled mode */
		window (1, old_info->cury + 1, 80, 24);

		textattr (text_color[new_win]);
		/* start at bottom of auto window and scroll */
		gotoxy (80, auto_y - (old_info->cury + 1));
		break;

	case CMDWIN:
		/* cmd window is the top of the screen; commands and requested  */
		/* reports are printed in scrolled mode in blue or reverse text */

		/* autowin absolute line coordinate */
		auto_y = old_info->cury + old_info->wintop;

		window (1, 1, 80, 24);
		textattr (text_color[new_win]);
		gotoxy (new_info->curx, new_info->cury);
		clreol ();
	  break;
	}
}

void new_cmd_window (void)
{
	/* blank out old command window */
	if (curr_win == AUTOWIN) {
		gettextinfo (&w_info[curr_win]);
		auto_y = w_info[curr_win].cury + w_info[curr_win].wintop;
	}
	textattr (text_color[AUTOWIN]);
	if (w_info[CMDWIN].cury > 1) {
		window (1, 2, 80, w_info[CMDWIN].cury);
		clrscr ();
	}
	w_info[CMDWIN].cury = 1;
	w_info[CMDWIN].curx = 1;

	/* perch in the auto window at the last location */
	curr_win = AUTOWIN;
	window (1, 2, 80, 24);
	gotoxy (80, auto_y - 2);

	switch_window (CMDWIN);
	clreol ();
	highvideo ();
	textbackground (BANNER_BACKGROUND);
	textcolor (BANNER_TEXT);
	cprintf (
		"       TSIPCHAT %s(%s)    Use <Esc> to Exit; Use '?' for Help Screen",
		TSIPCHAT_VERNUM, TSIP_VERNUM);
	clreol ();
	normvideo ();
	textcolor (LIGHTGRAY);
	textbackground (BLUE);
	gotoxy (1, 1);
}

void clr_cmd_window (short mode)
{
	short
		i;
	static short
		endline;
	switch_window (CMDWIN);
	if (mode) {
		for (i = w_info[CMDWIN].cury + 1; i <= endline; i++) {
			gotoxy (1, i);
			clreol ();
		}
	} else {
		endline = w_info[CMDWIN].cury;
		for (i = 1; i <= endline; i++) {
			gotoxy (1,i);
			clreol ();
		}
		gotoxy (1, 1);
		highvideo ();
		textbackground (BANNER_BACKGROUND);
		textcolor (BANNER_TEXT);
		cprintf (
			"            TSIPCHAT %s:%s     Use <CR> to Return to Normal Mode",
			TSIPCHAT_VERNUM, TSIP_VERNUM);
		clreol (); show_crlf ();
		normvideo ();
		textcolor (LIGHTGRAY);
		textbackground (BLUE);
	}
	switch_window (AUTOWIN);
}

void start_menu_window (void)
{
	textattr (text_color[MENUWIN]);
}

void end_menu_window (void)
{
	textattr (text_color[CMDWIN]);
}

void initialize_screen (void)
{
	/* get initial text attributes and save for restore before exit. */
	gettextinfo (&t_info);
	clrscr();
	text_color[AUTOWIN] = LIGHTGRAY + (BLACK << 4);
	text_color[CMDWIN]  = LIGHTGRAY + (BLUE  << 4);
	text_color[MENUWIN] = LIGHTGRAY + (BLUE  << 4);
	w_info[CMDWIN].cury = 1;
	w_info[CMDWIN].curx = 1;

	/* start in auto window */
	textattr (text_color[AUTOWIN]);
	clrscr ();
	gotoxy (1, 25);
}

void reset_screen (void)
{
	window (1,1,80,25);
	/* return text to original */
	textattr (t_info.normattr);
	gotoxy (80, 25);
	show_crlf ();
   clrscr();
}

/**/
/* ****************** 2. USER INPUT PROMPTS ********************* */
/* 
 * Prompt functions: allows user to supply a character string in response 
 * to a prompt.
 */

/* These routines are to set cmdesc (TRUE = abort command).
 * Used in TSIP_CMD.C.
 */
static short cmd_abort = FALSE;

short cmd_esc (void)
{
   return cmd_abort;
}

void set_cmd_esc (short x)
{
   cmd_abort = x;
}

/* Common prompt escape sequence. */
static short esc_out (char c) {
	short cmdesc;
	/* backspace, <CR>, printable characters except control characters */
	cmdesc = (c != 0x08) && (c != 0x0D) && (!isprint (c) || iscntrl (c));
	set_cmd_esc (cmdesc);
	return cmdesc;
}

static short get_prompt_string (char kbbuf[], short maxi)
{
	char kbch;
	short i;

	i = 0;
	for (i = 0; i < maxi; ) {
		kbch = read_rpts_wait_for_kbhit ();
		if (kbch == 0x08) {		      /* backspace */
			cprintf ("%c", kbch);
			if (i) i--;
		} else if (kbch == 0x0D) {    /* <CR> */
			break;
		} else if (esc_out(kbch)) {
			i = 0;
			break;
		} else {
			cprintf ("%c", kbch);
			kbbuf[i] = kbch;
			i++;
		}
	}
	/* terminate string */
	kbbuf[i] = END_STRING;
	show_crlf();
	set_cmd_esc (!i);
	return i;
}

/* prompt for an integer from user */
short ask_byte (char *prompt)
{
	short	n;
	char kbbuf[30];

   n = 0;
	clreol ();
	cprintf (prompt);
	if (get_prompt_string (kbbuf, 30)) {
		set_cmd_esc (sscanf (kbbuf, "%d", &n) < 1);
	}
	return n;
}
/* prompt for an unsigned long from user */
unsigned long ask_long (char *prompt)
{
	unsigned long n;
	char kbbuf[30];

   n = 0;
	clreol ();
	cprintf (prompt);
	if (get_prompt_string (kbbuf, 30)) {
		set_cmd_esc (sscanf (kbbuf, "%lu", &n) < 1);
	}
	return n;
}

/* prompt for a choice from among nine or fewer */
short pick_one (char *prompt, char *code_txt[], short nopts)
{
	short i, j, kbch;

	set_cmd_esc (FALSE);
	/* cycle through a series of choices & allow user to choose one. */
	/* Routine returns numerical value corresponding to choice. */
	cprintf ("%s(<Space> cycle, <CR> select, ^Z abort)", prompt);
	kbch = read_rpts_wait_for_kbhit ();
	clreol ();
	if (esc_out(kbch)) {
		return 0;
	}
	/* direct choice by digit (0..9) */
	j = (kbch - '0');
	i = 0;
	if ((j < nopts) && (j >= 0)) {
      if (code_txt[j][0] != END_STRING) {
         i = j;
      }
   }
   cprintf ("\r%s                                      ", prompt);
	for ( ; ; i++) {

		cprintf ("\r%s", prompt);
		if (i >= nopts) i -= nopts;
		/* skip choices with null character string */
		if (code_txt[i][0] == END_STRING) continue;

      highvideo ();
		cprintf ("%s (%d)", code_txt[i], i);
		lowvideo ();
		clreol ();

		for ( ; ; ) {  /* wait for <CR> or <space> or digit selection */
			kbch = read_rpts_wait_for_kbhit ();
			if (kbch == 0x0D) {  /* <CR>: choice is made */
				show_crlf ();
				return i;
			} else if (kbch == 0x20) { /* <Space>: drops out to new choice */
				break;
			} else if (esc_out(kbch)) {
				show_crlf();
				return 0;
			} else {
				j = (kbch - '0');
				if ((j < nopts) && (j >= 0)) {
					if (code_txt[j][0] != END_STRING) {
						/* direct choice by digit (0..9); offset at top of loop */
						i = j - 1;
						break;
					}
				}
			}
		}
	}
}

/* prompt user to enter an double */
double ask_dbl (char *prompt)
{
	double d = 0.0;
	char kbbuf[30];

	clreol ();
	cprintf (prompt);
	if (get_prompt_string (kbbuf, 30)) {
		set_cmd_esc (sscanf (kbbuf, "%lf", &d) < 1);
	}
	return d;
}

/* ask user for up to 4 hex codes */
unsigned char ask_hex_string (char *prompt, unsigned char *h, unsigned char maxchar)
{
	char kbbuf [90];
	unsigned char hh [30];
	short i, n;

	clreol ();
	cprintf (prompt);
   show_crlf();
	if (get_prompt_string (kbbuf, 90))
	{
		n=sscanf(kbbuf,
"%2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x",
			&hh[ 0],&hh[ 1],&hh[ 2],&hh[ 3],&hh[ 4],
         &hh[ 5],&hh[ 6],&hh[ 7],&hh[ 8],&hh[ 9],
			&hh[10],&hh[11],&hh[12],&hh[13],&hh[14],
         &hh[15],&hh[16],&hh[17],&hh[18],&hh[19]);
		if (n > 0)
		{
			if (n > maxchar) n = maxchar;
			for (i=0; i<n; i++)
			{
				h[i] = hh[i];
			}
			return n;
		}
		set_cmd_esc (TRUE);
	}
	return 0;
}


unsigned char ask_char_string (char *prompt, char *h)
{
	short i;

	clreol ();
	cprintf (prompt);
	if (get_prompt_string (h, 60)) {
		for (i=0; i<60; i++)
		{
			if (h[i] == 0) break;
		}
		if (i>0) return i;
		set_cmd_esc (TRUE);
	}
	return 0;
}


/* prompt user to verify choice with a 'Y' or 'y' */
short ask_verify (void)
{
	unsigned char kbch;
	short affirm;

	cprintf (" (Y/N) ");
	kbch = read_rpts_wait_for_kbhit ();
	if (esc_out(kbch)) return FALSE;
	affirm = ((kbch == 'Y') || (kbch == 'y'));
	cprintf (affirm ? "YES" : "NO");
	show_crlf ();
	return affirm;
}

short ask_verify_nocmdcrlf (void)
{
	unsigned char kbch;
	short affirm;

	cprintf (" (Y/N) ");
	kbch = read_rpts_wait_for_kbhit ();
	if (esc_out(kbch)) return FALSE;
	affirm = ((kbch == 'Y') || (kbch == 'y'));
	cprintf (affirm ? "YES" : "NO");
	return affirm;
}

/**/
/* ********************  3. TIMING ROUTINES *********************** */

/* logical indicating desire to set time */
static double
	timezone_hrs = -24.0;		/* timezone offset, hours; nonsense value to start */
static short
	timezone_set = FALSE;
const short days_of_month [12] = {
		  0,  31,  59,  90, 120, 151,
		181, 212, 243, 273, 304, 334};

static double raw_PC_time (void)
{
	/*
	** Note: Borland routines have a timezone implicit in them, most often
	** -5 hours.  We use DOS access directly so this does not screw us up.
	*/
	union REGS
		regs;
	double
		day, year,
		gpsday,
		hour, minute, second;
	short
		month;

	regs.h.ah = 0x2A;	/*  get date from DOS  */
	intdos (&regs, &regs);
	year = regs.x.cx;			/*  year  */
	month = regs.h.dh;		/*  month  */
	day = regs.h.dl;			/*  day  */
	gpsday = day + days_of_month[month - 1] + (year - 1980) * 365 - 6;
	/* leap years - add one for every fourth previous February */
	gpsday += (short)(12*(year-1976)+month-3)/48;

	regs.h.ah = 0x2C;			/*  get time from DOS  */
	intdos (&regs, &regs);
	hour = regs.h.ch;			/*  hours  */
	minute = regs.h.cl;		/*  minutes  */
	second = regs.h.dh;		/*  seconds  */
	return (second + 60. * (minute + 60. * (hour + 24. * gpsday)));
}

void GPS_time_from_PC (double *gpstime)
{
	time_t
		pctime;
   char *timezone_text[5] = {
"Before setting the clock, the timezone offset must be entered.  If the PC is",
"configured for local time, time must be adjusted to GPS (GMT) time with the",
"proper timezone offset, equal to the number of timezones east of Greenwich.",
"Timezones west of Greenwich are negative.  Add +1 for Daylight time.",
"(Value must be between -14 and 14)."};

	switch_window (CMDWIN);
	pctime = time(NULL);
	clreol (); show_crlf ();
	/* asctime() inserts a \n and \0 after the first 24 characters */
	cprintf ("Current PC time is %s\r", asctime (localtime(&pctime)));
	clreol ();

	if (timezone_set) {
		clreol (); show_crlf ();
		cprintf ("Local offset relative to GMT is %.1f hours", timezone_hrs);
		show_crlf ();
	}
	else
	{
		show_crlf ();
		cprintf (timezone_text[0]); show_crlf ();
		cprintf (timezone_text[1]); show_crlf ();
		cprintf (timezone_text[2]); show_crlf ();
		cprintf (timezone_text[3]); show_crlf ();
		cprintf (timezone_text[4]); show_crlf ();
		show_crlf ();
		timezone_set = TRUE;
		do {
			/*
			** Some time zones are not integer hour offsets: Newfoundland,
			** Saudi Arabia, India, Singapore, parts of Australia, etc.
			*/
			timezone_hrs = ask_dbl (
         	"Enter timezone (PST=-8, PDT=-7, EST=-5, GMT=0, JST=9): ");
			if (cmd_esc ()) {
				timezone_set = FALSE;
				timezone_hrs = -24.;
				cprintf ("Timezone set failure");
				return;
			}
		} while ((timezone_hrs < -14.) || (timezone_hrs > 14.));
		show_crlf ();
	}

	*gpstime = (double)raw_PC_time() - (timezone_hrs * 3600.);
}

/**/
/* *******************  4. STORAGE FILE CONTROL ****************** */
/* Following two routines called by open_, close_file_storage () below.
 * Return TRUE or FALSE.
 */
static short append_or_overwrite (char *newname, short *append_mode)
/* returns need_filename */
{
	FILE *stream_ptr;

	if (newname[0] == END_STRING) return TRUE;

	stream_ptr = fopen (newname, "r");
	if (stream_ptr != NULL) {
		fclose (stream_ptr);
		cprintf ("Append to existing file '%s'?", newname);
		if (ask_verify ()) {
			*append_mode = TRUE;
			return FALSE;
		} else {
			*append_mode = FALSE;
			cprintf ("Overwrite existing file '%s'?", newname);
			return (!ask_verify ());
		}
	}
	return FALSE;
}

void open_file_storage (FILE **stream_ptr, char *filename)
{
	short
		append_mode,
		need_filename;
	char
		newname[80];
	char
		open_mode[3] = {END_STRING, END_STRING, END_STRING};

	set_cmd_esc (FALSE);
	if (*stream_ptr != NULL) return;

	append_mode = FALSE;
	strcpy (newname, filename);
	if (newname[0] == END_STRING)
   {
		need_filename = TRUE;
		cprintf ("No previous storage file.");
        clreol ();
		show_crlf ();
	}
   else
   {
		need_filename = append_or_overwrite (newname, &append_mode);
	}
	if (cmd_esc ()) return;

	do {  /* open file */
		while (need_filename) {
			cprintf ("Enter new output file name ('^Z' to abort): ");
			clreol ();
			if (!get_prompt_string (newname, 70)) return;
			/* open to read; check to see if file exists already */
			need_filename = append_or_overwrite (newname, &append_mode);
			if (cmd_esc ()) return;
		}
		open_mode[0] = (append_mode) ? 'a' : 'w';
		open_mode[1] = 'b';
		*stream_ptr = fopen (newname, open_mode);
		/* open file for binary write or append */
		if (*stream_ptr != NULL)
		{
			break;
		}
		/* file open failed; loop and ask for new file name. */
		cprintf ("Could not open '%s'.", newname);
		show_crlf ();
		need_filename = TRUE;
	} while (*stream_ptr == NULL);

	strcpy (filename, newname);
	cprintf ("Saving to '%s'.", filename);
	show_crlf ();
}

void close_file_storage (FILE **stream_ptr, char *filename)
{
	set_cmd_esc (FALSE);
	if (*stream_ptr == NULL) return;

	cprintf ("Currently storing data to '%s'. Close file?", filename);
	if (!ask_verify ())
   {
		show_crlf ();
		set_cmd_esc (TRUE);
		return ;
	}
	if (fclose (*stream_ptr) == EOF)
   {
	   cprintf ("File close error, '%s'", filename);
	}
   else
   {
		*stream_ptr = NULL;
		cprintf ("Closing '%s'.", filename);
	}
	show_crlf ();
}

/**/
/* *****************  5. SERIAL PORT CONTROL  ****************** */
extern char
   *st_baud_text_app [],
	*databit_text_app [],
	*stopbit_text[];
short set_buf_serial_port (PORT_DEF *pdef)
{
	short
   	need_params;
	unsigned short
		baud_code, databits, parity_code, stopbits, iparity;
	static char
		*parity_dos[4]   =  {"NONE", "ODD ", "", "EVEN"};


   /* first time through - set to COM1 and initialize to 9600 8-odd-1 */
	need_params = TRUE;
	cprintf ("Change port parameters?");
	clreol ();
	if (!ask_verify ()) {
		return TRUE;
	}
	if (need_params &&
	      (pdef->baud_code != BAUD_4800 || pdef->databits != DATABITS_8 ||
      	pdef->parity_code != NO_PARITY || pdef->stopbits != STOPBITS_1))
	{
		cprintf ("Set to 4800 8-none-1?");
		if (ask_verify ())
		{
	      pdef->baud_code = BAUD_4800;
   	   pdef->databits = DATABITS_8;
      	pdef->parity_code = NO_PARITY;
	      pdef->stopbits = STOPBITS_1;
			need_params = FALSE;
		}
      if (cmd_esc()) return TRUE;
	}
	if (need_params &&
	      (pdef->baud_code != BAUD_9600 || pdef->databits != DATABITS_8 ||
      	pdef->parity_code != ODD_PARITY || pdef->stopbits != STOPBITS_1))
	{
		cprintf ("Set to 9600 8-odd-1?");
		if (ask_verify ())
		{
	      pdef->baud_code = BAUD_9600;
   	   pdef->databits = DATABITS_8;
      	pdef->parity_code = ODD_PARITY;
	      pdef->stopbits = STOPBITS_1;
			need_params = FALSE;
		}
      if (cmd_esc()) return TRUE;
	}
	if (need_params)
	{
		set_cmd_esc (FALSE);
      show_crlf ();
      baud_code = pdef->baud_code;
      databits = pdef->databits;
      parity_code = pdef->parity_code;
      iparity = parity_code >> 3;
      stopbits = pdef->stopbits;

		cprintf ("Current serial I\\O setting: %s, %s-%s-%s",
			st_baud_text_app[baud_code],
         databit_text_app[databits],
			parity_dos[iparity],
         stopbit_text[stopbits]);
		show_crlf ();

		baud_code = pick_one ("Baud rate: ", st_baud_text_app, 10);
		if (cmd_esc ())
      {
			show_crlf ();
			cprintf ("-- aborted --");
         return TRUE;
		}

		databits = pick_one ("Data bits: ", databit_text_app, 4);
		if (cmd_esc ())
      {
			show_crlf ();
			cprintf ("-- aborted --");
         return TRUE;
		}

		iparity = pick_one ("Parity: ", parity_dos, 4);
      parity_code = iparity << 3;
		if (cmd_esc ())
      {
			show_crlf ();
			cprintf ("-- aborted --");
         return TRUE;
		}

		stopbits = pick_one ("Stop bits: ", stopbit_text, 2);
		if (cmd_esc ())
      {
			show_crlf ();
			cprintf ("-- aborted --");
         return TRUE;
		}

		cprintf ("Set port to %s, %s-%s-%s?",
			st_baud_text_app[baud_code],
         databit_text_app[databits],
			parity_dos[iparity],
         stopbit_text[stopbits]);

		if (!ask_verify_nocmdcrlf ()) {
			show_crlf ();
			cprintf ("-- aborted --");
           return TRUE;
		}
      pdef->baud_code = baud_code;
      pdef->databits = databits;
      pdef->parity_code = parity_code;
      pdef->stopbits = stopbits;
	}
  	return FALSE;
}

