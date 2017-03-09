#include <stdio.h>
#include "bytedef.h"

LANGUAGE_TEXT f0001[19] = "\002      %02u       ";
LANGUAGE_TEXT f0002[17] = "     %04u       ";
LANGUAGE_TEXT f0003[17] = "                ";
LANGUAGE_TEXT f0004[11] = " oMS Net? ";

LANGUAGE_TEXT f0005[8] = "\001 \006----";
LANGUAGE_TEXT f0006[8] = "\001 ----\005";

LANGUAGE_TEXT f0008[15] = "\002         %6lu";

LANGUAGE_TEXT f0011[6] = " \001\002\003 ";
LANGUAGE_TEXT f0012[8] = "%2u-%2u";
LANGUAGE_TEXT f0013[6] = "%s%6u";
LANGUAGE_TEXT f0014[8] = "MemSet!";
/*LANGUAGE_TEXT f0014[6] = "EP701";*/
LANGUAGE_TEXT f0015[20] = "Chris Parsons 1999 ";

LANGUAGE_TEXT f0031[12] = "           ";
const struct pr s0225 = {  /* '\001          ' */
 f0031, f0031, f0031, f0031, f0031, f0031, f0031, f0031, f0031, f0031, f0031, f0031, f0031 };

LANGUAGE_TEXT f0032[17] = "\002               ";
const struct pr s0228 = { /* '\002               ' */
 f0032, f0032, f0032, f0032, f0032, f0032, f0032, f0032, f0032, f0032, f0032, f0032, f0032 };

/*                         12345678901234567890 */  
LANGUAGE_TEXT f0037[10] = "No Errors";
LANGUAGE_TEXT f0026[5] = "Wait";
LANGUAGE_TEXT f0025[7] = "Switch";
LANGUAGE_TEXT f0034[12] = "Delay/Pulse";
LANGUAGE_TEXT f0024[10] = "Pdl1 Load";
LANGUAGE_TEXT f0027[13] = "Wait Default";
LANGUAGE_TEXT f0023[13] = "Pdl1 Default";
LANGUAGE_TEXT f0036[20] = "Delay/Pulse Default";
LANGUAGE_TEXT f0035[19] = "Delay/Pulse Cancel";
LANGUAGE_TEXT f0038[17] = "Delay Lookup Err";
LANGUAGE_TEXT f0039[18] = "Switch Lookup Err";
LANGUAGE_TEXT *const ErrS[11] = {
  f0037, /* SeqErr = 0 'No Errors ' */
  f0026, /* SeqErr = 1 'Wait at   ' */
  f0025, /* SeqErr = 2 'Switch at ' */
  f0034, /* SeqErr = 3 'Del/Pul at' */
  f0024, /* SeqErr = 4 'Pdl1 Load ' */
  f0027, /* SeqErr = 5 'Wait Def. ' */
  f0023, /* SeqErr = 6 'Pdl1 Def. ' */
  f0036, /* SeqErr = 7 'Dl/Pl Def.' */
  f0035, /* SeqErr = 8 'Dl/Pl Can.' */
  f0038, /* SeqErr = 9 'Delay Lookup Err' */
  f0039  /* SeqErr = 10 'Switch Lookup Err' */
  };

const struct WarningBitmap Wbm[27] = {
/*  0 Normal   */								OKBOX,		NULL,	0, 0,
/*  1 Netting  */				WARNINGBOX,	NULL,					0, 0,
/*  2 Wrapping */				LAYERBOX,	NULL,					0, 0,
/*  3 Speed Warning */			WARNINGBOX,	NULL,					0xff, 0, /* Text in box */
/*  4 Tip Bale*/				WARNINGBOX,	NULL,					0, 0,
/*  5 Wrap Not Complete */		WARNINGBOX,	NULL,					0, 0, /* WRAPNOTCOMPLETE, 45, 53 */
/*  6 Unblock */				WARNINGBOX,	UNBLOCKBLAER,			43, 48,
/*  7 Unblock Reset */			WARNINGBOX,	UNBLOCKRESET,			43, 48,
/*  8 1 Dispensor Only */		LAYERBOX,	ONEDISPENSER,			43, 53,
/*  9 Out of film */			WARNINGBOX,	NODISPENSER,			43, 53,
/* 10 Indexing */				WARNINGBOX,	INDEXINGDISP,			40, 53,
/* 11 Net Error*/				WARNINGBOX,	CHECKNET,				42, 56,
/* 12 Saftey Switch */			WARNINGBOX,	SAFETYSWITCH,			45, 59,
/* 13 Tip Postion */			WARNINGBOX,	NULL,					0, 0, /* TIPPOS, 44, 56 */
/* 14 check lube */				NULL,		NULL,					0, 0,
/* 15 low voltage */			WARNINGBOX,	LOWBAT,		    		47, 58,
/* 16 Transfer not complete */	WARNINGBOX,	NULL,					0, 0, /* RFRNTCMP,  46, 48 */
/* 17 Dispensor postion */		WARNINGBOX,	NULL,					0, 0, /* DISPPOS,   40, 53 */
/* 18 Tip not complete */		WARNINGBOX,	NULL,					0, 0, /* TIPNOTCMP, 45, 53 */
/* 19 Net Cut Postion */		WARNINGBOX,	NETCUTPOS,	    		40, 53,
/* 20 No PWM */         		NOPWMBOX,	NULL,    				0, 0,
/* 21 MotorSpeedSensor */ 		WARNINGBOX,	MOTORSPEED,	    		46, 51,
/* 22 Wrapper too fast */ 		WARNINGBOX,	WRAPPERFAST,    		43, 51,
/* 23 Knife 1 Pressure High*/   WARNINGBOX, MAIN_AUTO_WARN_KNIVES3,	34, 48,
/* 24 Knife 2 Pressure High*/   WARNINGBOX, MAIN_AUTO_WARN_KNIVES3, 34, 48,
/* 25 No CAN BUS Comm.     */   WARNINGBOX, CAN_ERROR,       		46, 50,
/* 26 No CAN CHIP FITTED   */   WARNINGBOX, NULL,     		 		0xff, 0 /* Text in box */
};

/*
  unsigned char Seq;
  const struct pr *Name;
*/
const struct SeqType OPTi[MAXTYPE] = {
 O_S1, &s0217, /* '    Sequence 1  ' */
 O_S2, &s0218  /* '    Sequence 2  ' */
 };

const struct pr *const OnOff[2] = {
 &s0219, /* 'OFF' */
 &s0220  /* 'ON' */
 };

const struct pr *const SpeedWarning[3] = {
 &s0229, /* '\001 SPEED    ' */
 &s0230, /* '\001 TOO FAST!' */
 &s0225  /* '\001          ' */
 };

const struct pr *const ShortLong[3] = {
 &s0143, /* '     SHORT      ' */
 &s0144, /* '     LONG       ' */
 &s0317  /* '     MANUAL     ' */
 };
 
const struct pr *const CropTypeString[3] = {
 &s0363, /* Silage */
 &s0364, /* Hay    */
 &s0365  /* Straw  */
 };

const struct pr *const KnivSystemString[5] = { /*Knife option menu order*/
 &s0402, 	/* Relief Valve */
 &s0400, 	/* x23 Std */
 &s0404, 	/* x23 Select */
 &s0407,	/* x25 Std. New Knife option (rev. 30)*/
 &s0406		/* x25 Select. New knife option (rev. 30)*/
};
