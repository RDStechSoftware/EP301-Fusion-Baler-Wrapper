#include <inh83.h>
#include <ioh83003.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bytedef.h"

void reset_factors ( void )
{
unsigned short int c, i;
void *lp;

/* memcpy needed so NMI in correct place */
memcpy( (unsigned char *)&reset_code, (unsigned char *)&reset_code, 4  );

#ifndef WINDOWS
 lp = &reset_code; /* clear all data memory (preserved to FillIn) */
 while( (unsigned long)lp < (unsigned long)&FillIn )
   {
   *((unsigned char *)lp)++ = 0x00;
   }
#endif

/* 1234567  7 characters + NULL */
if( strcmp( CheckKey, f0014) )  /* 'MemSet!' returns 0 if the same */
  {
  GrandTotalBales = 0;
  KnivSystem = x23_Std;
  strcpy( CheckKey, f0014 ); /* 'MemSet!' */
  }

PinNumber = 3473;
CountSet = 8;

for( i=0; i<MAXTYPE; i++ )          /* Sequence Type */
  {
  for( c=0; c<MAXFACTOR; c++ )      /* Sequence Factors */
    {
    Facts[c][i] = PF[c].def[i];
    }
  }

Korean = 0;


/*Korean = 1; *//* just for development */
DayNight = CN_DAY;
Contrast[CN_DAY] = DEFAULT_CONTRAST;
Contrast[CN_NIGHT] = DEFAULT_CONTRAST;
Brightness[CN_DAY] = DEFAULT_BRIGHTNESS;
Brightness[CN_NIGHT] = DEFAULT_BRIGHTNESS;

KeyVolume = DEFAULT_KEYVOLUME;
KeyNote = DEFAULT_KEYNOTE;

AlarmVolume = DEFAULT_ALARMVOLUME1;
AlarmNote = DEFAULT_ALARMNOTE1;

KnifePressure = 0.95; /* volts */
/*KoreanPres = 0.57;*/ 	  /* volts */
KoreanPres = 0.65; 	  /* volts Iss-145*/
KnifePresWarn = 1.38; /* volts */
KnifeDownPres = 0.20; /* volts */

/* in Bar */
KnifePressureBar = (unsigned short)(KnifePressure * 50.0);
KoreanPresBar = (unsigned short)(KoreanPres * 50.0);
KnifePresWarnBar = (unsigned short)(KnifePresWarn * 50.0);
KnifeDownPresBar = (unsigned short)(KnifeDownPres * 50.0);

sio0.baud = 6; /* 4800 (3bits) */
sio0.stop_bits = 1; /* 2 stop bits  */
sio0.parity = 1; /* 0ff (2bits)  */
sio0.data_bits = 1; /* 7 data bits  */
sio0.handshake = 0; /* RTS handshake */

reset_code = RESET_KEY;
strcpy( CheckString1, f0015 ); /* 'Chris Parsons 1999 ' 19 chars + NULL */
strcpy( CheckString2, f0015 ); /* 'Chris Parsons 1999 ' 19 chars + NULL */

#ifndef WINDOWS
get_time();

c = 0;
if( minutes > 59 )
  {
  c++;
  }
if( hours > 23 )
  {
  c++;
  }
if( _date > 31 )
  {
  c++;
  }
if( month > 12 )
  {
  c++;
  }
if( (year < 2000) || (year > 2099) )
  {
  c++;
  }
if( (seconds & 0x80) || c ) /* start clock if not running or error */
  {
  minutes = 0;
  hours = 12;
  _date = 31;
  month = 3;
  year = 2006;

  set_time();
  }
#endif

CropType = 0;

BalerFull[0] = 30; /* silage*/
BalerFull[1] = 30; /* hay 	*/
BalerFull[2] = 5;  /* straw */

RearBaleStatus = 0;
ExtBuzzer = 1;

ResetLubeCheck();
}


#ifdef WINDOWS
 extern void WriteToScreen( void );

 void sim_startup( void )
   {
   	
#else
 void main ( void )
   {
   void (*old_window)(void);
   unsigned char near *pt, imZero;
   
#endif

unsigned char tstring[32];
struct frequency *Sf;

#ifndef WINDOWS
	/* clear H8RAM - processor internal memory */
	imZero = 0;
	for( pt = (unsigned char near *)0xFFFD10; pt < (unsigned char near *)0xFFFF10; pt++ )
	{
		*pt = imZero;
	}
	set_interrupt_mask( 3 );    /* all INTS except NMI off */
#endif

/* Port 4 is general IO, used for scanning keys */
P4DR = 0x0f;
P4DDR = 0xf0; /* OOOOIIII I=input, O=output */

/* Port 5 outputs A20-A23 in mode 3 */
/* P5DR = 0x00; default */
/* P5PCR = 0x00; default */
/* P5DDR = 0xff; default */  /* OOOO1111 I=input, O=output */

/* Port 6.0 is /WAIT input, Port 6.1 & 6.2 used for IIC */
/* P6DR = 0x00; default */
/* P6DDR = 0x80; default */  /* 10000III I=input, O=output */

/* Port 7 is analogue inputs & input only */
/* P7DR - read only */

/* Port 8 is CS0/1/2/3 & Remote Ip */
/* P8DR = 0xe0; default */
P8DDR = 0xfe; /* 111OOOOI I=input, O=output */

/* Port 9 is CAN interrupt & Serial Io */
/* serial outputs set high if serial mode not enabled */
P9DR = 0xc3;
P9DDR = 0xc3; /* 11IIIIOO I=input, O=output */

/* Port A is used for direct IO & general IO */
/* PADR = 0x00; default */
PADDR = 0x32; /* IIOOIIOI I=input, O=output */

/* Port B is used for direct IO & general IO */
PBDR = 0x08;  /* 00001000 - OP enable bit set to 1 */
PBDDR = 0xff; /* OOOOOOOO I=input, O=output */

/* Port C is used for Chip Selects & General IO */
/* PCDR = 0x00; default */
PCDDR = 0x3f; /* IIOOOOOO I=input, O=output */

/* AtoD control Register - no external trigger */
/* ADCR  = 0x7f; default - started in refresh timer int */

/* set up interrupt for Int7/6/5/4/3/2/1/0 */
ISCR = 0xff; /* 1= falling edge, 0 = Low level */
/* IER  = 0x00; default - all disabled */

/* set up interrupt for CMI interval timer */
/* RFSHCR = 0x02; default */ /* set refresh control to interval timer, 800us */
RTCOR = 24;                  /* set compare register to 25 */
RTMCSR = 0x6f;               /* enable compare match int, set divider to 512 */

/* Timer Block Setup */
/* TSNC = 0xe0; Timer Sync Register, none synced, use defaults */
/* Timer Mode register, 0,2,3,4 normal, 1 PWM == 0x82 */
/* Timer Mode register, 0,1,2,3,4 normal == 0x80 */
/* ITU_TMDR = 0x80; Timer Mode register, 0,1,2,3,4 normal, PWM set(1/3/4) when needed */
/* TFCR = 0xc0; Timer Function Control register, none changed, use defaults */
/* TOER = 0xff; Timer 3/4 Output Master Enable, none changed, use defaults */
/* TOCR = 0xff; Timer Output Control Register, none changed, use defaults */

/* Timer0 Setup */
/* TCNT0, 16 bit count */
/* GRA0,  GRB0, general 16 bit registers (output compare / input capture */
ITU_TCR0 = 0x83;  /* Timer Control Register, TCNT not cleared, rising edge, / 8 */
ITU_TIOR0 = 0xec; /* Timer I/O control Register, capture both edges on B, rising edges on A */
/* TSR0, Timer Status overflow, capture B, capture A */
ITU_TIER0 = 0xfd; /* Timer Int Enable, Timer Overflow & Capture A (Capture B off) */

/* Timer1 Setup */
/* GRA1,GRB1 general 16 bit registers (output compare / input capture */
ITU_GRA1 = PWMFREQ; /* (PWMFREQ = 9000) 222.22'Hz (2e6/9000 Hz) */
ITU_GRB1 = 0;       /* off all the time */
/* Timer Control Register, TCNT cleared by GRA1 match, rising edge, clock / 8 */
ITU_TCR1 = 0xa3;
/* Timer I/O control Register, 0 on GRA1 match, 1 on GRB1 match */
/* ITU_TIOR1 not used in PWM mode */
/* TSR1, Timer Status overflow, capture B, capture A */
/* Timer Int Enable Register not overflow, not capture B, not capture A (def) */
/* ITU_TIER1 = 0xf8; default ints off */

/* Timer2 Setup */
/* TCNT2, 16 bit count */
/* GRA2,  GRB2, general 16 bit registers (output compare / input capture */
ITU_TCR2 = 0x83;    /* Timer Control Register, TCNT not cleared, rising edge, / 8 */
ITU_TIOR2 = 0x8c;   /* Timer I/O control Register, capture rising edge on A, B not used */
/* TSR2, Timer Status overflow, capture B, capture A */
ITU_TIER2 = 0xfd;   /* Timer Int Enable, Timer Overflow & Capture A (Capture B off) */

/* Timer3 Setup */
ITU_GRA3 = PWMFREQ; /* (PWMFREQ = 9000) 222.22'Hz (2e6/9000 Hz) */
ITU_GRB3 = 0;       /* off all the time */
/* Timer Control Register, TCNT cleared by GRA1 match, rising edge, clock / 8 */
ITU_TCR3 = 0xa3;
/* ITU_TIER3 = 0xf8; */ /* defaults interrupts off */

/* Timer4 Setup - pwm on channel a */
/* GRA4,  GRB4, general 16 bit registers (output compare / input capture */
ITU_TCR4 = 0xa3; /* ITU_TCR4 = 0xf8; */
/* ITU_TIER4 = 0xf8; */ /* default interrupts off */

ITU_TSTR = 0xef; /* Timer 3 & 1 on for pwm, Timer 2 & 0 on for Capture */

#ifndef WINDOWS
 set_interrupt_mask( 0 ); /* all INTS enabled */

 setup_display();
 setup_display();
#else
 startup_frame();
 WriteToScreen();
#endif

SetSerial0_Boot();
SetSerial1_Boot();

SeqErr = 0; /* fatal errors */
ErrPos = 0;

/* setup Tag lookup tables */
SetLookUps();
/* save error if any, as reset will clear it */
tstring[0] = SeqErr;
tstring[1] = ErrPos;

/* strcmp returns 0 if the strings the */
if( (reset_code != RESET_KEY) ||
    strcmp( CheckString1, f0015 ) ||
    strcmp( CheckString2, f0015 ) )
  {
  reset_factors(); /* clear ALL data ram */
  }

/* restore error if any, as reset will clear it */
SeqErr = tstring[0];
ErrPos = tstring[1];

window = screen00;

WakeUpDtoA();
SetContrast();
SetBrightness();

LedData.S = 0;

Op.L = 0;

OP01 = Op.O.OP01;
OP02 = Op.O.OP02;
OP03 = Op.O.OP03;
OP04 = Op.O.OP04;
latch1_out = Op.C[2]; /* OP05-12 */
latch2_out = Op.C[3]; /* OP13-20 */

OP_ENABLE = 0; /* enable outputs */

SetBeepType( BT1 | BP1, TB1 | TBOTH, 3 ); /* 100/200ms On/Off, All, 3 Counts */

ResetAll = 0;
SavedCountCur = 0;
WrapSeq = WS_PAUSED; /*rev. 30 modified to WS PAUSED from WS_RUNNING*/
Facts[DelPul[FILMBK]][0] = 1; /* film break on at start-up */
AutoMan = 0; /* set manual at startup */

ResetSequenceFactors( SEQ_ALL );

if( Facts[DelPul[RESTRT]][0] )
  {
  oldMachineStatus = MachineStatus;
  TableOccupied = (MachineStatus & MS_BALEON) ? 1 : 0;
  }

/* clear transfer done status at startup */
MachineStatus &= ~MS_TRANSDONE;

NetWarnCanc = 0x00;
AlarmFlags = 0;
Knives_Up = 0;
PauseTip = 0;
NetCutPosAlarm = NetCutPosNorm = RaiseDoor = 0;
LangStartup = 0;

PWMSlow1 = PWMSlowTarget1; /* PWMSlowTarget default set in ResetSequenceFactors */
PWMSlow2 = PWMSlowTarget2; /* PWMSlowTarget default set in ResetSequenceFactors */

Sf = &Shaft[0];
Sf->stat = 0xff; /* set status, set transition */
Sf->count = 0;
Sf->pulses = 0;

analogue[7] = 0;
demi_secs = 0;
AutoTip_Sel = 0;
LEDSel = 0;
DemoScreens = 0;
BootRun = 50;
txd0 = 1;

SetOneDispRevs();

#ifdef WINDOWS
} /* end of sim_startup() if #windows */


void sim_main( int keypress )
{
unsigned int i;
struct frequency *Sf;
static unsigned char old_key;
unsigned char tstring[32];
void (*old_window)(void);

old_key = key & ~KeyMask;
if( keypress != -1 )
  {
  key = keypress;
  }

if( old_key != (key & ~KeyMask) )
  {
  if( key )
    {
    /* SetBeep */
    if( (Music == NULL) && !BeepTone )
      {
      SetVolume( KeyVolume );

      Note = KeyNote;
      NoteLength = KEYDURATION;
      }
    }
  else
    {
    swrel = 0;
    }

  loop = 1;
  divider1 = 0;
  divider2 = 0;
  swtim = 0;
  demi_secs = 0;
  flash_bit = 0;
  }
else if( key )
  {
  key |= KeyDone;
  if( swtim > KeyRepeatTime )
    {
    key |= KeyRepeat;
    }
  }

Ip.L = 0;
Ip.I.IP01 = 1;
IP01 = 1;
Ip.I.IP04 = 1;
Ip.I.IP06 = 1;
Ip.I.IP07 = 1;
Ip.I.IP08 = 1;

loop = 1;
  {
#else /* non-windows specific */

while( !analogue[7] && !demi_secs ) /* wait for atod conversion */
  ;

if (Ip.I.IP06 == 0) /*If knives are open from the start, wait until they close again before displaying a warning*/
{
	knifeip6 = 2;
}
if (Ip.I.IP07 == 0)
{
	knifeip7 = 2;
}

while( 1 )
  {
   /* KeyCheck();  */ 
  KeyCheck( 1 );
#endif /* endo of #if */
#if 0
  Iss-109 change
  if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select)) /* && (!CANWarnCanc)*/ )
    { /* do can routines */    
    CANfunctions();
    }
#endif    
  if( window != screen073 ) /* Diagnostic - Output screen */
    {
    OutputSet();
    }
  else
    {
    if( IndexTable )
	  {
	  Op.O.OP17 = 1;
	  }
	/* turn on Outputs */
	OP01 = Op.O.OP01;
	OP02 = Op.O.OP02;
	OP03 = Op.O.OP03;
	OP04 = Op.O.OP04;

	latch1_out = Op.C[2]; /* OP05-12 */
	latch2_out = Op.C[3]; /* OP13-20 */
    }
  
  if( loop )
    {
   #ifndef WINDOWS
    SupplyVolts = (unsigned short int)((float)analogue[7] * ATOD_VI_SCALE * 10.0);
    Kniv1Pres = (unsigned short int)((float)analogue[4] * ATOD_IP_SCALE * 50.0); /* multiply by 50 to display in bar */
    if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
      {
    	/*Kniv2Pres = (unsigned short int)((float)analogue[3] * ATOD_IP_SCALE * 50.0); *//* multiply by 50 to display in bar */
    	Kniv2Pres = (unsigned short int)((float)analogue[5] * ATOD_IP_SCALE * 50.0); /* multiply by 50 to display in bar */
      }
    /* Iss-109 change 
    if( KnivSystem == x23_Select )
      {
	  if( CanStatus == CSTATUS_OK )
	    {
	    Kniv2Pres = Pressure / 10;
	    Old_CanInitCount = CanInitCount;
	    }
      }*/
	#else
	    SupplyVolts = 134;
	    Kniv1Pres = 45;
	    Kniv2Pres = 45;
	    /*
	  if( KnivSystem == x23_Select )
	    {
	    Kniv2Pres = 45;
	    }*/
	#endif
      
    Sf = &Shaft[0];
    if( Sf->duration )
      {
      Speed = (float)Sf->pulses * ((1250.0*3.6)/(18.0/2.4)) / (float)Sf->duration;
      }

    if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
      {
      }
    else /* other knife systems */
      {
      if( !Ip.I.IP06 && AutoMan )
        {
        if( AutoToManDelay++ > 2 )
          {
          AutoMan = 0;
          SavedCountCur = 0;
          DispenserStatus = 0;
          ResetSequenceFactors( SEQ_ALL );
          }
        }
      else
        {
        AutoToManDelay = 0;
        }
      }
    old_window = window;

    if( window )
      {
    	window(); /* display as normal */
      }
    else
      {
      escape = 0;
      level = 0;
      selection = 0;
      leaf = 0;
      editing = 0;
      startup = 0;
      window = screen00;
      }

    if( key == Key_F2 )
      {
      if( demist > 6 )
        {
        Contrast[CN_DAY] = DEFAULT_CONTRAST;
        Contrast[CN_NIGHT] = DEFAULT_CONTRAST;
        SetContrast();

        startup = 0;
        window = display_levels;
        }
      }
    else
      {
      demist = 0;
      }

    if( swtim && !key )
      {
      if( swrel < 0xff )
        swrel++;     
      }

    if( !BootRun && (demi_secs > 99) && (window != main_loop) /*&& (window != Demo00)*/ )
      {
      window = main_loop; /* screen01 */
      }
    	      
     if( (window != old_window) || escape )
      {
      if( escape ) 
        {
        if( level )
          {
          level--;
          selection = returnto[level].sel;
          window= returnto[level].lev;
          
          if( (window==main_loop) && DemoScreens )
        	  window = Demo00;
          else if( (window==Demo00) && !DemoScreens )
        	  window = main_loop;
          }
        else
          {
          selection = 0;
          }                
        }
      else
        {
        if( !leaf )
          {
          returnto[level].sel = selection;
          returnto[level].lev = old_window;
          level++;
          }
        selection = 0;
        }

      escape = 0;
      leaf = 0;
      startup = 0;
      editing = 0;

      ExtPower = 1;

      Sel = 2;

      old_time = 0xff;
      old_date = 0xff;

      loop = 1;
      }
    else
      {    	
   	  if( window != screen073 ) /* Diagnostic - Output screen */
   	    {
        #ifndef WINDOWS
   		/* KeyCheck(); */ 
   	    KeyCheck( 0 );
        #endif
   	    OutputSet();
   	    }

   	/* ###test */
   	  /*
	   	sprintf( tstring, "%2u T%2u T2%2u", Zone, Ip.I.TIPST, T2B);  
	   	display_f1_text(tstring, 30, 33, 16, FIXED );*/

      #ifdef WINDOWS
       WriteToScreen();
      #else
       display_screen();
      #endif
       /* ######## test */
       /* sprintf( tstring, "K=%02x", key ); 
       display_f1_text(tstring, TS20, 4, 16, FIXED ); */
       /* ###end test */
      loop = 0;
      }

    SetLedData();
    LedDisplay( LedData.S ); /* turn on LEDs */
    } /* end of if if( loop ) loop */

  /* not used if remote key pad enabled */ 
  /*if( SCI0_SSR & 0x84 )*/ /* enable interrupt if tx empty & transmit end */
  /*  {
    SCI0_SCR |= 0x24;
    } */
  
  SCI0_SCR |= 0x50; /* enable receive & receive interrupt */

 #ifdef SECONDSERIAL /* ###test */
  if( SCI1_SSR & 0x84 ) / * enable interrupt if tx empty & transmit end * /
    {
    SCI1_SCR |= 0x24;
    }

  SCI1_SCR |= 0x50; /* enable receive & receive interrupt */
 #endif
  } /* end of while( 1 ) loop */

}


