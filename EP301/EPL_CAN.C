#include "bytedef.h"
#include <inh83.h>
#include <ioh83003.h>
#include <inh83003.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* variable definitions */
/* -----------------------------------------------------------------------------------------*/
#pragma memory=dataseg(H8RAM):near
/* only 496 other internal ram variables allowed - some already used (search on H8RAM) */
/* access time is faster, so used in interrupts */ 
unsigned long int CanCurrentTime, CanTimeoutStartTime;
unsigned char CanStatus, CanInitCount, Old_CanInitCount, CanStage, CanHead, CanTail;

#pragma memory=default

unsigned char const * const CanTestString = "CANTEST"; /* 7 characters + NULL */
unsigned char const * const CanErrorString[7] = {
	"INIT",
	"CAN OK",
	"TIMEOUT1", 
	"TIMEOUT2", 
	"TIMEOUT3", 
	"NOCHIP1",
	"NOCHIP2"
};

unsigned short int Pressure, PressureArray[PRESSURE_AVERAGE_LIMIT];

/*struct CanMessage {
  union usltoc id;
  unsigned char dat[8];
  unsigned long time;
  };*/
struct CanMessage CanM[CAN_MAXMESSAGE]; /* CAN_MAXMESSAGE is a power of 2*/
/* -----------------------------------------------------------------------------------------*/

/* functions */
/* -----------------------------------------------------------------------------------------*/
/* void CANfunctions( void ) */
/* read pressure from a CAN open pressure sensor with default NodeID = 1 */
/* pressure is stored and transmitted as 10 x real value in bar, so 123 = 12.3bar, so no fp needed */
/* function is placed in main program loop, so it must not block, ie it should always return in a timely manner */
/* -----------------------------------------------------------------------------------------*/
void CANfunctions( void )
{
	struct CanMessage *CMpt;
	union usltoc lid; /* see bytedef.h */
	union ustoc sdat;
	
	/*unsigned char near *ptd;*/
	unsigned char *pts, *ptd, uc;
	unsigned long int lsum;	
	
	if( window == screen00 ) /* wait until startup screen has finished */
	{
		return;
	}

	switch( CanStage ) /* CanStage is initialized to 0 with other H8RAM variables */
	{
	default:
	case CS_STARTUP:
		CanStatus = CSTATUS_INIT;
	case CS_INIT0:
		/* set default wait states until CAN detected */
		WCR = 0xf3; /* program 3 wait states */
		WCER = 0xff; /* wait state control enabled in all areas, CS0-CS7 */
		
		IER &= ~0x20; /* turn off can interrupt - IRQ5 */
		ISR &= ~0x20; /* clear pending flag - IRQ5 */
		
		CanInitCount++; /* for error checking, incremented every time bus is setup */

		CanTail = CanHead;
		CanTimeoutStartTime = CanCurrentTime;
		CanStage = CS_INIT1;
	case CS_INIT1:
		if( !(can_CPU_interface & 0x80) ) /* wait for can hardware reset - bit set if reset in progres */
		{
			/* check for can chip, by writing a test pattern to message memory */
			strcpy( &message02[DATA0], CanTestString ); /* test string */
			
			CanStage = CS_INIT2;
		}
		else if( (CanCurrentTime - CanTimeoutStartTime) > CAN_TIMEOUT ) /* receive timeout */
		{
			CanStage = CS_INIT0;
			CanStatus = CSTATUS_NOCHIP1;
		}
		break;

	case CS_INIT2:
		/* check test pattern - use double read method as wait pin control is off */
		ptd = &message02[DATA0];
		pts = &CanTestString[0];
		while( *pts )
		{
			uc = *ptd++; /* read low speed register, transfers value to high speed register */
			uc = can_hs_read_lo; /* read high speed register */
			if( uc != *pts )
			{
				uc = 1;
				break;
			}
			pts++;
			uc = 0;
		}
		
		/*if( strcmp( &message02[DATA0], CanTestString ) == 0 )*/
		if( uc == 0 )
		{
			CanStage = CS_INIT3; /* ok */
		}
		else
		{
			CanStage = CS_INIT0;
			CanStatus = CSTATUS_NOCHIP2;
		}
		break;

	case CS_INIT3:
		/* restore startup wait states */
		WCR = 0xf9;  /* pin wait mode 1, 1 wait state */
		WCER = 0xfc; /* wait state control disabled in area CS0 & CS1 */
		
		/* clock out enabled (bit0=1 for test) ie 0x1 not 0x40 */
		can_CPU_interface = 0x41; /* sysclk = xtal/2, memclk = sysclk, clk out */
		can_control = 0x41;       /* change config enabled, software init enabled */

		can_clock_out = 0x17;     /* 16MHz/8 = 2MHz clock out */
		can_bus_config = 0x08;

		can_bit_timing0 = 0x01;   /* SJW = 1 (0+1), BRP = 2 (1+1) (tq = 250 nS) */
		can_bit_timing1 = 0x2B;   /* SPL = 1 (0+1), TSEG2 = 3 (2+1), TSEG1 = 12 (11+1) */
		/* bit time = (1+3+12) * 250nS = 4uS (250000bps) */
		can_control = 0x01;       /* change to config disabled (sw init enabled)  */

		message01[CONFIG] = CAN_DLC8 | CAN_RX | CAN_ID11;   /* set config to 8bytes, receive, standard id */
		message01[CONTROL0] = C0_MSGVAL_CLR | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; 
		message01[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_CLR | C1_CPUUPD_CLR | C1_NEWDAT_CLR;

		message02[CONFIG] = CAN_DLC8 | CAN_TX | CAN_ID11;   /* set config to 8bytes, transmit, standard id */
		message02[CONTROL0] = C0_MSGVAL_CLR | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; 
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_CLR | C1_CPUUPD_CLR | C1_NEWDAT_CLR;

		/* can_standard_global_mask = 0xffff;      */  /* all must match */
		can_standard_global_mask = 0x0000;             /* don't care     */
		/* can_extended_global_mask = 0xffffffffUL;*/  /* all must match */
		can_extended_global_mask = 0x00000000UL;       /* don't care     */

		message01[CONTROL0] = C0_MSGVAL_SET | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; /* set message control registers */
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_CLR | C1_CPUUPD_CLR | C1_NEWDAT_CLR;

		CanStage = CS_SETUP;

	case CS_SETUP:
		for( uc = 0; uc < PRESSURE_AVERAGE_LIMIT; uc++ )
		{
			PressureArray[uc] = 0;
		}
		Pressure = 0;
		
		can_control = 0x01; /* change to config disabled (sw init enabled)  */
		message01[CONTROL0] = C0_MSGVAL_NOP | C0_TXIE_NOP | C0_RXIE_SET | C0_INTPND_NOP; /* set receive interrupt */
		can_status = 0x00; /* reset warning bits */
		can_control = 0x02; /* enable interrupts */

		IER |= 0x20; /* turn on can interrupt - IRQ5 */
		
		CanStage = CS_RESET;

	case CS_RESET: /* Reset Node */
		message02[CONTROL0] = C0_MSGVAL_CLR | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; 
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_CLR | C1_CPUUPD_SET | C1_NEWDAT_CLR; /* updating message */

		/* ID in top 11 bits for standard message, top 29 bits for extended */
		lid.l = CM_NMT << 21;
		message02[ARB0] = lid.c[0];
		message02[ARB1] = lid.c[1];
		message02[ARB2] = lid.c[2];
		message02[ARB3] = lid.c[3];
		
		message02[CONFIG] = CAN_DLC2 | CAN_TX | CAN_ID11; /* 2bytes of data, 11 bit identifier, transmit mode */
		
		message02[DATA0] = CM_NRSNODE; /* node reset */
		message02[DATA1] = 0x00; /* all nodes */

		message02[CONTROL0] = C0_MSGVAL_SET | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; /* message valid */
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_SET | C1_CPUUPD_CLR | C1_NEWDAT_SET; /* transmit data, not updating, new data written */
		
		CanTimeoutStartTime = CanCurrentTime;
		CanStage = CS_BOOTUP;
		break;
		
	case CS_BOOTUP: /* Check for BOOTUP Message after a reset */
		if( CanTail != CanHead ) /* decode received messages */
		{
			CMpt = &CanM[CanTail++ & (CAN_MAXMESSAGE - 1)]; /* CAN_MAXMESSAGE is a power of 2*/
			lid.l = CMpt->id.l;
			if( lid.l == ((CM_HBEAT | CM_NODEID) << 21) )
			{
				if( CMpt->dat[0] == 0x00 )
				{
					CanStage = CS_TIMETX;
				}
			}
		}
		else if( (CanCurrentTime - CanTimeoutStartTime) > CAN_TIMEOUT ) /* receive timeout */
		{
			CanStage = CS_INIT0;
			CanStatus = CSTATUS_TIMEOUT1;
		}
		break;
		
	case CS_TIMETX: /* Set PDO1 Message Repeat Time to 100ms */
		message02[CONTROL0] = C0_MSGVAL_CLR | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; 
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_CLR | C1_CPUUPD_SET | C1_NEWDAT_CLR; /* updating message */

		/* ID in top 11 bits for standard message, top 29 bits for extended */
		lid.l = (CM_RSDO | CM_NODEID) << 21;
		message02[ARB0] = lid.c[0];
		message02[ARB1] = lid.c[1];
		message02[ARB2] = lid.c[2];
		message02[ARB3] = lid.c[3];
		
		message02[CONFIG] = CAN_DLC8 | CAN_TX | CAN_ID11; /* 8bytes of data, 11 bit identifier, transmit mode */
		
		message02[DATA0] = 0x2b;
		message02[DATA1] = CM_INDEX % 256; /* index low */
		message02[DATA2] = CM_INDEX / 256; /* index high */
		message02[DATA3] = CM_SUBIX; /* sub index */
		message02[DATA4] = CM_REPEAT_TIME % 256; /* timer low */
		message02[DATA5] = CM_REPEAT_TIME / 256; /* timer high */
		message02[DATA6] = 0x00;
		message02[DATA7] = 0x00;

		message02[CONTROL0] = C0_MSGVAL_SET | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; /* message valid */
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_SET | C1_CPUUPD_CLR | C1_NEWDAT_SET; /* transmit data, not updating, new data written */
		
		CanTimeoutStartTime = CanCurrentTime;
		CanStage = CS_TIMERX;
		break;

	case CS_TIMERX: /* Check PDO1 Message Repeat Time has been set */
		if( CanTail != CanHead ) /* decode received messages */
		{
			CMpt = &CanM[CanTail++ & (CAN_MAXMESSAGE - 1)]; /* CAN_MAXMESSAGE is a power of 2*/
			lid.l = CMpt->id.l;
			if( lid.l == ((CM_TSDO | CM_NODEID) << 21) )
			{
				if( (CMpt->dat[0] & 0xe0) == 0x60 ) /* cs = 3 */
				{
					sdat.c[0] = CMpt->dat[2];
					sdat.c[1] = CMpt->dat[1];
					if( sdat.s == CM_INDEX ) /* PDO1 mesurement index */
					{
						CanStage = CS_STARTX;
					}
				}
			}
		}
		else if( (CanCurrentTime - CanTimeoutStartTime) > CAN_TIMEOUT ) /* receive timeout */
		{
			CanStage = CS_INIT0;
			CanStatus = CSTATUS_TIMEOUT2;
		}
		break;
		
	case CS_STARTX: /* Start Node */
		message02[CONTROL0] = C0_MSGVAL_CLR | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; 
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_CLR | C1_CPUUPD_SET | C1_NEWDAT_CLR; /* updating message */

		/* ID in top 11 bits for standard message, top 29 bits for extended */
		lid.l = CM_NMT << 21;
		message02[ARB0] = lid.c[0];
		message02[ARB1] = lid.c[1];
		message02[ARB2] = lid.c[2];
		message02[ARB3] = lid.c[3];
		
		message02[CONFIG] = CAN_DLC2 | CAN_TX | CAN_ID11; /* 8bytes of data, 11 bit identifier, transmit mode */
		
		message02[DATA0] = CM_NSTART;
		message02[DATA1] = CM_NODEID;

		message02[CONTROL0] = C0_MSGVAL_SET | C0_TXIE_CLR | C0_RXIE_CLR | C0_INTPND_CLR; /* message valid */
		message02[CONTROL1] = C1_RMTPND_CLR | C1_TXRQST_SET | C1_CPUUPD_CLR | C1_NEWDAT_SET; /* transmit data, not updating, new data written */
		
		CanTimeoutStartTime = CanCurrentTime;
		CanStage = CS_RUN;
		break;
		
	/* only decode 1 message per loop so it is quicker to exit */
	/* some messages will be lost if it takes > 0.1sec to loop back here */
	/* but we don't want this routine to take too long and upset the main loop timing */
	case CS_RUN: /* CAN detected, so check messages */
		if( CanTail != CanHead ) /* decode received messages */
		{
			CMpt = &CanM[CanTail++ & (CAN_MAXMESSAGE - 1)]; /* CAN_MAXMESSAGE is a power of 2*/
			lid.l = CMpt->id.l;
			/* don't left/right shift variables unless really neaded, as H8 con only do 1 bit at a time */
			/* and would have to loop 21 times for << 21 */
			/* So to chedck id, shift id constant, then check, ie lid.l == (0x601 << 21), not (lid.l >> 21) == 0x601 */
			if( lid.l == (0x181 << 21) ) /* PD01 Transmit */
			{
				lsum = 0;
				/* shift array */
				for( uc = (PRESSURE_AVERAGE_LIMIT - 1); uc > 0; uc--  )
				{
					sdat.s = PressureArray[uc - 1];
					PressureArray[uc] = sdat.s;
					lsum += sdat.s;
				}
				sdat.c[0] = CMpt->dat[1];
				sdat.c[1] = CMpt->dat[0];
				PressureArray[uc] = sdat.s;
				lsum += sdat.s;

				Pressure = lsum / PRESSURE_AVERAGE_LIMIT;

				CanStatus = CSTATUS_OK;
			}
			CanTimeoutStartTime = CMpt->time;
		}
		else if( (CanCurrentTime - CanTimeoutStartTime) > CAN_TIMEOUT ) /* receive timeout */
		{
			CanStage = CS_INIT0;
			CanStatus = CSTATUS_TIMEOUT3;
		}
		break;
	}
	

}
/* -----------------------------------------------------------------------------------------*/
