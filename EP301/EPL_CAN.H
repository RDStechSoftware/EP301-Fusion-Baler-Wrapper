#ifndef EPL_CAN_H_
#define EPL_CAN_H_

/* definitions/enumerations */
/* -----------------------------------------------------------------------------------------*/
#define C0_MSGVAL_SET	0x80	/* object valid if set */
#define C0_MSGVAL_CLR	0x40
#define C0_MSGVAL_NOP	0xC0
#define C0_TXIE_SET		0x20	/* TX interrupt enabled if set if IE set */	
#define C0_TXIE_CLR		0x10
#define C0_TXIE_NOP		0x30
#define C0_RXIE_SET		0x08	/* RX interrupt enabled if set if IE set */
#define C0_RXIE_CLR		0x04
#define C0_RXIE_NOP		0x0C
#define C0_INTPND_SET	0x02	/* Interrupt pending if set */
#define C0_INTPND_CLR	0x01
#define C0_INTPND_NOP	0x03

#define C1_RMTPND_SET	0x80	/* Remote Frame has requested this message if set if in TX mode */	
#define C1_RMTPND_CLR	0x40
#define C1_RMTPND_NOP	0xC0
#define C1_TXRQST_SET	0x20	/* Transmission requested, but not complete if set */
#define C1_TXRQST_CLR	0x10
#define C1_TXRQST_NOP	0x30
#define C1_CPUUPD_SET	0x08	/* RX Message Overwritten / TX CPU updating so cant transmit is set*/
#define C1_CPUUPD_CLR	0x04
#define C1_CPUUPD_NOP	0x0C
#define C1_NEWDAT_SET	0x02	/* RX new data written / TX message has been updated */
#define C1_NEWDAT_CLR	0x01
#define C1_NEWDAT_NOP	0x03

#define CAN_DLC8	0x80
#define CAN_DLC7	0x70
#define CAN_DLC6	0x60
#define CAN_DLC5	0x50
#define CAN_DLC4	0x40
#define CAN_DLC3	0x30
#define CAN_DLC2	0x20
#define CAN_DLC1	0x10
#define CAN_DLC0	0x00

#define CAN_TX		0x08
#define CAN_RX		0x00

#define CAN_ID29	0x04
#define CAN_ID11	0x00

enum EnumCanStage {
	CS_STARTUP,
	CS_INIT0,
	CS_INIT1,
	CS_INIT2,
	CS_INIT3,
	CS_SETUP,
	CS_RESET,
	CS_BOOTUP, 
	CS_TIMETX, 
	CS_TIMERX, 
	CS_STARTX, 
	CS_RUN
};

enum EnumCanStatus {
	CSTATUS_INIT,
	CSTATUS_OK,
	CSTATUS_TIMEOUT1, 
	CSTATUS_TIMEOUT2, 
	CSTATUS_TIMEOUT3, 
	CSTATUS_NOCHIP1,
	CSTATUS_NOCHIP2
};

#define CM_NMT		0x000
#define CM_SYNC		0x080
#define CM_EMERG	0x080
#define CM_STAMP	0x100
#define CM_TPDO1	0x180
#define CM_RPDO1	0x200
#define CM_TPDO2	0x280
#define CM_RPDO2	0x300
#define CM_TPDO3	0x380
#define CM_RPDO3	0x400
#define CM_TPDO4	0x480
#define CM_RPDO4	0x500
#define CM_TSDO		0x580
#define CM_RSDO		0x600
#define CM_HBEAT	0x700

#define CM_NSTART	0x01 
#define CM_NSTOP	0x02 
#define CM_NRSPRE	0x80 
#define CM_NRSNODE	0x81 
#define CM_NRSCOM	0x82 

#define CM_NODEID 1
#define CM_INDEX 0x1800
#define CM_SUBIX 5
#define CM_REPEAT_TIME 100

#define CAN_MAXMESSAGE 8 /* must be a power of 2 */
#define CAN_TIMEOUT 1250 /* 1.0s in 800us counts */
#define PRESSURE_AVERAGE_LIMIT 8
/* -----------------------------------------------------------------------------------------*/

/* variable definitions */
/* -----------------------------------------------------------------------------------------*/
struct CanMessage {
  union usltoc id;
  unsigned char dat[8];
  unsigned long time;
  };

#pragma memory=dataseg(H8RAM):near
/* only 496 other internal ram variables allowed - some already used (search on H8RAM) */
/* access time is faster, so used in interrupts */ 
extern unsigned long int CanCurrentTime, CanTimeoutStartTime;
extern unsigned char CanStatus, CanInitCount, Old_CanInitCount, CanStage, CanHead, CanTail;

#pragma memory=default
 
extern unsigned short int Pressure, PressureArray[PRESSURE_AVERAGE_LIMIT];
 
extern unsigned char const * const CanTestString;
extern unsigned char const * const CanErrorString[7];

extern struct CanMessage CanM[CAN_MAXMESSAGE]; /* CAN_MAXMESSAGE is a power of 2*/
/* -----------------------------------------------------------------------------------------*/

/* function prototypes */
/* -----------------------------------------------------------------------------------------*/
void CANfunctions( void );

/* -----------------------------------------------------------------------------------------*/

#endif /*EPL_CAN_H_*/
