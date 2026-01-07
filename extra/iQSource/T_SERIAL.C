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
 * Vers	Date		   Changes										 Author
 * ----	---------   ----------------------------------------	   ----------
 * 1.1   21 Jun 93	Initial version								     		pvwl
 * 1.11  19 Jul 95   Revisions                                       ahl
 *       26 Jul 95   Communications above 9600 bps
 *       29 mar 97   combined MS & Borland routines into one         pvwl
 *       08 jun 98   simplified into a one-serial port routine       pvwl
 * *************************************************************************
 *
 * This module demonstrates the advantage of some of the Borland C++
 * extensions to the C language to perform asynchronous communications
 * without having to write supporting assembly language routines.
 8
 * This module bypasses the PC BIOS communications
 * routines and installs a serial interrupt handler.  Direct access to
 * PC hardware allows the module to execute at faster baud rates and
 * eliminates the need for TSIPCHAT to continuously poll the serial
 * port for data -- thus implementing background communications.  Data
 * entering the serial port is stored in a circular buffer.
 *
 * Compile this program with Test Stack Overflow OFF.  The following
 * are application level routines for:
 *
 *    a. Initializing a serial port							(initsio)
 *    b. Closing both serial ports							(closeserial)
 *    c.	Reading a character from the receive buffer	(get_char)
 *    d. Outputting characters from a serial port		(put_char)
 *
 * *************************************************************************
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "t_struct.h"
#include "t_format.h"
#include "t_parser.h"
#include "tsipincl.h"

#define COM1            1
#define COM2            2
#define COM1BASE        0x3F8   /* Base port address for COM1 */
#define COM2BASE        0x2F8   /* Base port address for COM2 */

/*
 * The 8250 UART has 10 registers accessible through 7 port addresses.
 * Here are their addresses relative to COM1BASE and COM2BASE. Note
 * that the baud rate registers, (DLL) and (DLH) are active only when
 * the Divisor-Latch Access-Bit (DLAB) is on. The (DLAB) is bit 7 of
 * the (LCR).
 *
 *    - TXR Output data to the serial port
 *    - RXR Input data from the serial port
 *    - LCR Initialize the serial port
 *    - IER Controls interrupt generation
 *    - IIR Identifies interrupts
 *    - MCR Send contorl signals to the modem
 *    - LSR Monitor the status of the serial port
 *    - MSR Receive status of the modem
 *    - DLL Low byte of baud rate divisor
 *    - DHH High byte of baud rate divisor
 */
#define TXR             0       /* Transmit register (WRITE) */
#define RXR             0       /* Receive register  (READ)  */
#define IER             1       /* Interrupt Enable          */
#define IIR             2       /* Interrupt ID              */
#define LCR             3       /* Line control              */
#define MCR             4       /* Modem control             */
#define LSR             5       /* Line Status               */
#define MSR             6       /* Modem Status              */
#define DLL             0       /* Divisor Latch Low         */
#define DLH             1       /* Divisor Latch High        */

/*-------------------------------------------------------------------*
   Bit values held in the Line Control Register (LCR)

   Bit		Definition
   ---		----------
   0-1		00=5 bits, 01=6 bits, 10=7 bits, 11=8 bits
   2		   Stop bits
   3		   0=parity off, 1=parity on
   4		   0=parity odd, 1=parity even
   5		   Sticky parity
   6		   Set break
   7		   Toggle port addresses
*-------------------------------------------------------------------*/
#define NO_PARITY       0x00
#define EVEN_PARITY     0x18
#define ODD_PARITY      0x08

/*-------------------------------------------------------------------*
   Bit values held in the Line Status Register (LSR)

   Bit		Definition
   ---		----------
   0		   Data ready
   1		   Overrun error - Data register overwritten
   2		   Parity error - bad transmission
   3		   Framing error - No stop bit was found
   4		   Break detect - End to transmission requested
   5		   Transmitter holding register is empty
   6		   Transmitter shift register is empty
   7        Time out - off line
*-------------------------------------------------------------------*/
#define RCVRDY          0x01
#define OVRERR          0x02
#define PRTYERR         0x04
#define FRMERR          0x08
#define BRKERR          0x10
#define XMTRDY          0x20
#define XMTRSR          0x40
#define TIMEOUT		   0x80

/*-------------------------------------------------------------------*
   Bit values held in the Modem Output Control Register (MCR)

   Bit     	Definition
   ---		----------
   0		   Data Terminal Ready; computer ready to go
   1		   Request To Send; computer wants to send data
   2		   auxillary output #1
   3		   auxillary output #2 (Note: This bit must be
			   set to allow the communications card to send
               interrupts to the system)
   4		   UART ouput looped back as input
   5-7		not used
*------------------------------------------------------------------*/
#define DTR             0x01
#define RTS             0x02
#define MC_INT		      0x08

/*------------------------------------------------------------------*
   Bit values held in the Modem Input Status Register (MSR)

   Bit		Definition
   ---		----------
   0		   delta Clear To Send
   1		   delta Data Set Ready
   2		   delta Ring Indicator
   3		   delta Data Carrier Detect
   4		   Clear To Send
   5		   Data Set Ready
   6		   Ring Indicator
   7		   Data Carrier Detect
*------------------------------------------------------------------*/
#define CTS             0x10
#define DSR             0x20

/*------------------------------------------------------------------*
   Bit values held in the Interrupt Enable Register (IER)

   Bit		Definition
   ---		----------
   0		   Interrupt when data received
   1		   Interrupt when transmitter holding reg; empty
   2		   Interrupt when data reception error
   3		   Interrupt when change in modem status register
   4-7		Not used
*------------------------------------------------------------------*/
#define RX_INT          0x01
  
/*------------------------------------------------------------------*
   Bit values held in the Interrupt Identification Register (IIR)
   
   Bit		Definition
   ---		----------
   0		   Interrupt pending
   1-2      Interrupt ID code

			   00=Change in modem status register
			   01=Transmitter holding register empty
			   10=Data received
			   11=reception error, or break encountered

   3-7		Not used
*------------------------------------------------------------------*/
#define RX_ID           0x04
#define RX_MASK         0x07

/* 8259 Programmable Interrupt Controller (PIC)port addresses */
#define IMR             0x21  /* Interrupt Mask Register port */
#define ICR             0x20  /* Interrupt Control Port       */

/* An end of interrupt needs to be sent to the Control Port of
   the 8259 when a hardware interrupt ends. */
#define EOI             0x20  /* End Of Interrupt */

/* The (IMR) tells the (PIC) to service an interrupt only if it
   is not masked (FALSE). */
#define IRQ3            0xF7  /* COM2 */
#define IRQ4            0xEF  /* COM1 */

#define   COM1_INTRPT_NUM   0x0C
#define   COM2_INTRPT_NUM   0x0B
static unsigned short
	portbase1, portbase2;

void  (interrupt *oldvects2)()=NULL;
void  (interrupt *oldvects1)()=NULL;
/***************************************************************************/
#define MAXMSG		1024
static struct {
   unsigned char *firstptr;
   unsigned char *lastptr;
   unsigned char *endmsgbuf;
	unsigned char msgbuf[MAXMSG];   /* receive buffer						   */
} 	siobuf;			            /* 1 buffer for each port */

void interrupt com_int_1 (void);
void interrupt com_int_2 (void);

/* The following are the definitions for port number and parity:
COM1 = 1
COM2 = 2
NO_PARITY   =   0x00
EVEN_PARITY =   0x18
ODD_PARITY  =   0x08
*/

void closeserial (void)
{
	short c;

   //	comm_off ();
	// Go off-line
	//	i_disable ();
	// Turn off communications interrupts
	_disable ();

	c = inp (IMR) | ~IRQ3 | ~IRQ4;
	outp (IMR, c);

	if (portbase1)
	{
		outp (portbase1 + IER, 0);
		c = inp (portbase1 + MCR) & ~MC_INT;
		outp (portbase1 + MCR, c);
	}

	if (portbase2)
	{
		outp (portbase2 + IER, 0);
		c = inp (portbase2 + MCR) & ~MC_INT;
		outp (portbase2 + MCR, c);
	}

	_enable ();

	if (portbase1)
	{
		outp (portbase1 + MCR, 0);
	}
	if (portbase2)
	{
		outp (portbase2 + MCR, 0);
	}

	//	resvects ();
	// Uninstall our vectors before exiting the program
	if (oldvects1!=NULL)
   {
   	_dos_setvect (COM1_INTRPT_NUM, oldvects1);
      oldvects1 = NULL;
   }
	if (oldvects2!=NULL)
   {
      _dos_setvect (COM2_INTRPT_NUM, oldvects2);
      oldvects2 = NULL;
   }
   portbase1 = 0;
   portbase2 = 0;
}

//void initsio (short port, unsigned short speed, short bits, short stopbits, short parity)
void initsio (PORT_DEF *pdef)
{
	unsigned short
   	speed,
		divisor,
		setting,
		Offset,
		c,
		ipb,
   	port,
      bits,
      stopbits,
      parity;
	unsigned short
		far *RS232_Addr;
	unsigned char
		cr;

   /* clear outold settings */
   closeserial();
   port = pdef->port;
   speed = (75 << pdef->baud_code);
   bits = pdef->databits + 5;
   stopbits = pdef->stopbits + 1;
   parity = pdef->parity_code;

	// Set the port number to use
	switch (port) {
		// Sort out the base address
	case COM1:
		Offset = 0x0000;
		break;

	case COM2:
		Offset = 0x0002;
		break;

	default:
		fprintf (stderr, "Serial Port setup error 1.\n");
		exit (1);
	}

	RS232_Addr = MK_FP (0x0040, Offset);	// find out where the port address is
	ipb = *RS232_Addr;
	if (ipb==0) {
		fprintf (stderr, "Serial Port setup error: RS232 not found.\n");
		exit (1);   						      // if NULL then port not used
	}
	if (port==COM1)
	{
		portbase1 = ipb;      // set portbase
	}
	else if (port==COM2)
	{
		portbase2 = ipb;      // set portbase
	}

// Setting the speed requires that the DLAB be set on.
	if (speed == 0) {
		fprintf (stderr, "Serial Port setup error: baud rate = %d.\n", speed);
		exit (1);   						      // Avoid divide by zero
	} else {
		divisor = (short)(115200L / speed);
	}

	_disable ();
	cr = inp (ipb + LCR);
	outp (ipb + LCR, (cr | 0x80)); /* Set DLAB */
	outp (ipb + DLL, (divisor & 0x00FF));
	outp (ipb + DLH, ((divisor >> 8) & 0x00FF));
	outp (ipb + LCR, cr);          /* Reset DLAB */
	_enable ();

	//	if (SetOthers (port, Parity, Bits, stopbits)) return (-1);
	// Set other communications parameters */
	if ((bits < 5) || (bits > 8)) {
		fprintf (stderr, "Serial Port setup error: databits = %d.\n", bits);
		exit (1);
	}
	if ((stopbits != 1) && (stopbits != 2)) {
		fprintf (stderr, "Serial Port setup error: stopbits = %d.\n", stopbits);
		exit (1);
	}
	if (parity != NO_PARITY && parity != ODD_PARITY && parity != EVEN_PARITY) {
		fprintf (stderr, "Serial Port setup error: parity = %d.\n", parity);
		exit (1);
	}

	setting  = (bits-5) | ((stopbits==1)?0x00:0x04) | parity;

	_disable ();
	outp (ipb + LCR, setting);
	_enable ();

	siobuf.lastptr  = siobuf.msgbuf;
	siobuf.firstptr = siobuf.msgbuf;
	siobuf.endmsgbuf = &siobuf.msgbuf[MAXMSG-1];

	// Install our functions to handle communications
	if (port==COM1 && oldvects1==NULL)
	{
		oldvects1 = _dos_getvect (COM1_INTRPT_NUM);
		_dos_setvect (COM1_INTRPT_NUM, com_int_1);
	}
	else if (port==COM2 && oldvects2==NULL)
	{
		oldvects2 = _dos_getvect (COM2_INTRPT_NUM);
		_dos_setvect (COM2_INTRPT_NUM, com_int_2);
	}

	// Tell modem that we're ready to go
	_disable ();
	c = inp (ipb + MCR) | MC_INT;
	outp (ipb + MCR, c);
	outp (ipb + IER, RX_INT);
	c = inp (IMR) & ((port == COM1) ? IRQ4 : IRQ3);
	outp (IMR, c);
	_enable ();

	c = inp (ipb + MCR) | DTR | RTS;
	outp (ipb + MCR, c);
}

short get_char (short port)
{
	unsigned char retval;

	if (port > 2 || siobuf.lastptr == siobuf.firstptr) return -1;

	retval = *(siobuf.firstptr);
   /* advance ptr */
   if (siobuf.firstptr == siobuf.endmsgbuf)
   {
   	siobuf.firstptr = siobuf.msgbuf;
   }
   else
   {
	   siobuf.firstptr++;
   }
   return (retval);
}

/* Output a character to the serial port */
short put_char (short port, unsigned char x)
{
	long timeout = 0x0000FFFFL;
	unsigned short useport;

	if (port==COM1) useport = portbase1;
	else if (port==COM2) useport = portbase2;
	else return -1;

	outp (useport + MCR,  MC_INT | DTR | RTS);

	// Wait for Clear To Send from modem */
/*
   while ( (inp (useport + MSR) & CTS) == 0)
   if (! (--timeout)) return (-1);
*/
   timeout = 0x0000FFFFL;

   // Wait for transmitter to clear
   while ( (inp (useport + LSR) & XMTRDY) == 0) {
	   if (! (--timeout)) {
		 return (-1);
		}
	}
	_disable ();
	outp (useport + TXR, x);
	_enable ();
	return (0);
}

/***************************************************************************/
/* Handle communications interrupts */
void interrupt com_int_1 (void)
{
	unsigned char ch;
   unsigned char *nextc;


	_disable ();
	if ((inp (portbase1 + IIR) & RX_MASK) == RX_ID) {
		ch = inp (portbase1 + RXR);
		/* check for overflow */
     	nextc = (siobuf.lastptr == siobuf.endmsgbuf)?
        	siobuf.msgbuf : (siobuf.lastptr + 1);
		if (nextc != siobuf.firstptr) {
			*siobuf.lastptr = ch;
         siobuf.lastptr = nextc;
		}
	}
	/* Signal end of hardware interrupt */
	outp (ICR, EOI);
	_enable ();
}

void interrupt com_int_2 (void)
{
	unsigned char ch;
   unsigned char *nextc;

	_disable ();
	if ( (inp (portbase2 + IIR) & RX_MASK) == RX_ID) {
		ch = inp (portbase2 + RXR);
		/* check for overflow */
     	nextc = (siobuf.lastptr == siobuf.endmsgbuf)?
        	siobuf.msgbuf : (siobuf.lastptr + 1);
		if (nextc != siobuf.firstptr) {
			*siobuf.lastptr = ch;
         siobuf.lastptr = nextc;
		}
  	}
	/* Signal end of hardware interrupt */
	outp (ICR, EOI);
	_enable ();
}
/******************************************************************************/
/* send break to receiver  07/23/99 PAH */
void sendBreak(short port, unsigned short msecs)
{
	int setting;
	unsigned short useport;

	if (port==COM1) useport = portbase1;
	else if (port==COM2) useport = portbase2;

	setting  = (3) | (0x00) | NO_PARITY;
	outp(useport + 3, setting|0x40);
   delay (msecs);
	outp(useport + 3, setting&0xBF);
	return;
}
