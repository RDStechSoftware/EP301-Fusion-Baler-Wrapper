#include "bytedef.h"

unsigned char BuzzerTimer = 0;

#ifndef WINDOWS
#include <inh83.h>
#include <ioh83003.h>
#include <inh83003.h>
#include <stdio.h>
#include <stdlib.h>



interrupt [NMI] void power_fail_int( void )  /* power fail interrupt */
{

portA_dat = 0x00;
portB_dat = 0x00;
latch1_out = 0x00; /* set ouputs  4-13 low */
latch2_out = 0x00; /* set ouputs 13-20 low */

}


interrupt [CMI] void timer_int( void ) /* every 800us */
{
static unsigned short int ftimer, count, tone;
static unsigned char LoopCount;

unsigned short int duration, usi;
struct frequency *Sf;

CanCurrentTime++;

if( ++divider1 >= 5 ) /* incremented every 800us */
  {
  divider1 = 0;

  if( WaitTime )
    {
    WaitTime--;
    }

  divider2++; /* incremented every 4ms */

  CheckIndexing();

  if( !(divider2 % 25) ) /* every 0.1 second */
  {
  	/* Buzzer timer runs from 0 to 5 inclusive. 0 to 2 means output is (potentially) on, 3 to 5 means it is off */
  	BuzzerTimer++;

  	if (BuzzerTimer >= 6)
  		{
  		BuzzerTimer = 0;
  		}

    if( LoopCount >= 2 )
      {
      loop = 1;
      LoopCount = 0;
      }
    else
      { 
      LoopCount++;
      }

    if( KeyS1Delay < 250 )
      {
      KeyS1Delay++;
      }
    /* --------- serial test output -------------- */
    if( BootRun )
      {
      BootRun--;
      }
    else if( SIOdata )
      {
      s0tx_buff[s0tx_head] = 0xaa;
      s0tx_head++;
      
      s0tx_buff[s0tx_head] = TestOp.C[1];
      s0tx_head++;
      s0tx_buff[s0tx_head] = TestOp.C[2];
      s0tx_head++;
      s0tx_buff[s0tx_head] = TestOp.C[3];
      s0tx_head++;

      s0tx_buff[s0tx_head] = TestIp.C[1];
      s0tx_head++;
      s0tx_buff[s0tx_head] = TestIp.C[2];
      s0tx_head++;
      s0tx_buff[s0tx_head] = TestIp.C[3];
      s0tx_head++;
     
      s0tx_buff[s0tx_head] = 0x55;
      s0tx_head++;
      
      /* transmit enable, transmit end interrupt enable - turned off when bufer emptied */
      SCI0_SCR = 0x24;
      }
    else
      {
      SCI0_SCR = 0; /* turn off serial Tx/Rx enable and interrups */
      txd0 ^= 1; /* toggle txd0, to pull high/low */
      }
    /* --------- serial test output -------------- */    
   
    if( TimingBit )
      {
      DecTens++;
      if( ++Units >= 10 )
        {
        Units = 0;
        DecUnits++;
        }
      }

    if( CapB0 == 1 )
      {
      ITU_GRB3 += PWMstep;
      usi = PWMSlow1 + (unsigned short)((PWMFREQ * (unsigned long)8) / 100);
      if( ITU_GRB3 > usi )
        { 
        ITU_GRB3 = PWMFREQ + 1;
        CapB0 = 8;
        }
      }

    if( swtim != 0xff )
    	swtim++;

		if(!IP01)
		{
			if(IP10_Flag == 1)
				IP10_Flag = 2;

			if(IP01_timer != 0xff)
				IP01_timer++;
		}
		else
		{
			IP01_timer = 0;
		}

    }

  if( divider2 >= 125 ) /* every 0.5 seconds */
    {
    divider2 = 0;

    ExternalBuzzSet = 1;
      
    loop_seconds++; /* loop_seconds used in clock check */
    demi_secs++;
    demist++;
    flash_bit = flash_bit ? 0 : 1;
    }

  if( !AtoD_Done && !AtoD_Run )
    {
    ADCSR = 0x73; /* set to scan ain0-ain3 & start conversion */
    }

  if( RemoteTimeOut < 50 ) /* 0.2 seconds */
    {
    RemoteTimeOut++;
    }
  else
    {
    RemoteCode = 0;
    }

  if( BeepTone )
    {
    if( BeepCount || count )
      {
      
      if( ( !count ))
        {
        if( !tone )
          {
          tone = BeepTone & ~TMASK;
          count = BeepOn;

          if( (AlarmFlags & 0x08) || (AlarmFlags & 0x20) )
          {
            AlarmFlags |= 0x80;
            Note = 80;
          }

          if( (AlarmFlags & 0x10) || (AlarmFlags & 0x40) )
          {
            AlarmFlags |= 0x80;
            Note = 71;
          }
         
          }
        else if( (AlarmFlags & 0x08) && (AlarmFlags & 0x80) )
        {
          if( Note == 80 )
            {
            Note = 77;
            AlarmFlags &= ~0x80;
            }
          else
            {
            Note = 80;
            }
          ITU_GRA4 = NoteFrequency[Note];
          ITU_GRB4 = ITU_GRA4 / 2;
          ITU_TCNT4 = 0; /* reset timer */
          count = BeepOn;
        }
        else if( (AlarmFlags & 0x10) && (AlarmFlags & 0x80) )
        {
          if( Note == 71 )
            {
            Note = 77;
            AlarmFlags &= ~0x80;
            }
          else
            {
            Note = 71;
            }
          ITU_GRA4 = NoteFrequency[Note];
          ITU_GRB4 = ITU_GRA4 / 2;
          ITU_TCNT4 = 0; /* reset timer */
          count = BeepOn;
        }
        else if( (AlarmFlags & 0x20) && (AlarmFlags & 0x80) )
        {
          if( Note == 80 )
            {
            Note = 71;
            AlarmFlags &= ~0x80;
            }
          else
            {
            Note = 80;
            }
          ITU_GRA4 = NoteFrequency[Note];
          ITU_GRB4 = ITU_GRA4 / 2;
          ITU_TCNT4 = 0; /* reset timer */
          count = BeepOn;
        }
        else if( (AlarmFlags & 0x40) && (AlarmFlags & 0x80) )
        {
          if( Note == 77 )
            {
            Note = 80;
            AlarmFlags &= ~0x80;
            }
           else if(Note == 71)
            {
            Note = 77;
            }
          else
            {
            Note = 71;
            }
          ITU_GRA4 = NoteFrequency[Note];
          ITU_GRB4 = ITU_GRA4 / 2;
          ITU_TCNT4 = 0; /* reset timer */
          count = BeepOn;
        }
        else if( BeepOff )
          {
          switch( BeepTone )
            {
            case (TB1 | TBEXT):
              BeepTone = TB1 | TBOTH;
              tone = 0;
              break;

            case (TB1 | TBINT):
              BeepTone = TB1 | TBEXT;
              tone = 0;
              break;

            case (TB1 | TBOTH):
              BeepTone = TB1 | TBINT;
              tone = 0;
              break;

            case (TB2 | TBEXT):
              BeepTone = TB2 | TBINT;
              tone = TBINT;
              break;

            case (TB2 | TBINT):
              BeepTone = TB2 | TBEXT;
              tone = TBEXT;
              break;

            default:
              tone = 0; 
              break; 
            }
          count = BeepOff;
          BeepCount--;

          if(!BeepCount)
            AlarmFlags &= ~0x80;

          AlarmFlags &= ~ExternAlarm;
          }
        }
      else
        {
          count--;
        }

      switch( tone )
        {
        case TBEXT:
        case TBALL:
          if( AlarmFlags & 0x01 )
          {
            ExternalAlarm = 1;
          }
          else
          {
            ExternalAlarm = 0;
          }
        case TBINT:
        case TBOTH:
          if(AlarmFlags & 0x02)
            Note = 77;
          else if( (AlarmFlags & 0x04) && !(AlarmFlags & NoteAltMask) )
            Note = 80;
          else if(!(AlarmFlags & NoteAltMask))
            Note = AlarmNote;

          NoteLength = KEYDURATION;
          break;

        default:
        /* case TBOFF */
          break;
        }
      }
    else
      {
      BeepTone = 0;
      BeepType = 0;
      ExternalAlarm = 0;
      }
    }

  }

/*if( AlarmFlags & 0x01 )
{
  SetVolume( 0 );
}*/

if( NoteLength )
  {
  NoteLength--;

  if( !(ITU_TSTR & 0x10) && Note ) /* if timer not running & not silence */
    {
    ITU_GRA4 = NoteFrequency[Note];
    ITU_GRB4 = ITU_GRA4 / 2;

    ITU_TCNT4 = 0; /* reset timer */
    ITU_TMDR |= 0x10; /* set pwm on timer 4 */
    ITU_TSTR |= 0x10; /* start timer 4 */
    }
  }
else if( ITU_TSTR & 0x10 )
  {
  ITU_TSTR &= ~0x10; /* stop timer 4 */
  ITU_TMDR &= ~0x10; /* clear pwm on timer 4 */

  Note = 0;
  NoteLength = (NOTEDURATION / 2);
  }
else if( Music != NULL )
  {
  if( Music->Duration )
    {
    NoteLength = Music->Duration * (NOTEDURATION * 4);
    Note = Music->Note;
    Music++;
    }
  else
    {
    Music = NULL;
    }
  }

/* -- polled rpm measurement starts here -- */
ftimer++;
Sf = &Shaft[0];
if( !(latch1_in & IpDef[0]) )
  {
  Sf->stat = 0x00; /* clear status, clear transition */
  }
else if( !Sf->stat )
  {
  Sf->stat = 0xff; /* set status, set transition */
  Sf->count++;
  }
else
  {
  Sf->stat &= 0xf0; /* set status, clear transition */
  }

duration = ftimer - Sf->time;
if( ((Sf->stat & 0x0f) && (duration >= 1250)) || (duration >= 2500) )
  {
  Sf->duration = duration;
  Sf->pulses = Sf->count;
  Sf->count = 0;
  Sf->time = ftimer;
  }
/* -- end of polled frequency measurement -- */

if( RTMCSR & 0x80 )
  {
  RTMCSR &= ~0x80; /* Clear interrupt request flag */
  }
}


interrupt [ITU_OVI0] void t0_overflow_int( void )
{
register unsigned long int ctime;

t0_high++; /* every 0.032768 seconds ( 65536/(16e6/8) ) */

ctime = (t0_high * 0x10000UL) + ITU_TCNT0;

if ( (ctime - startA0)  > 12000000UL ) /* 6.00 secs */
  {
  countA0 = A0count;
  A0count = 0;
  durationA0 = ctime - startA0;
  startA0 = ctime;

  newA0 = 1;
  /*calcA0 = 0;*/  
  }
else if ( (ctime - startA0) > 2000000UL ) /* 1.00 secs */
  {
  if( !newA0 )
    calcA0 = 1;
  }

/*****  For frequency calculation  ****/
if ( (ctime - startB0f)  > 4000000UL ) /* 2.00 secs */
  {
  countB0 = B0count;
  B0count = 0;
  durationB0f = ctime - startB0f;
  startB0f = ctime;
  
  newA0b = 1;
  calcA0b = 0;  
  }
else if ( (ctime - startB0f) > 2000000UL ) /* 1.00 secs */
  {  	
  if( !newA0b )
	calcA0b = 1;
  }
/*************************************/
/* pwm on, and no capture pulse, increment pwm */
if( (ITU_TIER0 & 0x02) && ITU_GRB3 && (ITU_GRB3 < PWMmax) )
  {
  if( FirstPulse )
    {
    FirstPulse = 0;
    startB0 = ctime;
    }
  else if( (ctime - startB0) > 1000000UL ) /* 0.5 secs */
    {
    ITU_GRB3 += (unsigned short)((PWMFREQ * (unsigned long)2) / 100);
    if( ITU_GRB3 > PWMmax )
      {
      ITU_GRB3 = PWMmax;
      }
    startB0 = ctime;
    }
  }
else
  {
  FirstPulse = 1;
  }

/* pwm on, and no capture pulse */
if( (ITU_TIER0 & 0x02) && ITU_GRB3 && (SafetyCount < 0xff) )
  {
  SafetyCount++; /* 1 second = 30 counts */
  }
/* ISS-086 */
if( (ITU_TIER0 & 0x02) && ITU_GRB3 && (IP01Count < 0xff) )
  {
	IP01Count++; /* 1 second = 30 counts */
  }

if ( ITU_TSR0 & 0x04 )       /* Clear interrupt request flag */
  ITU_TSR0 &= ~0x04;
}


interrupt [ITU_IMIA0] void t0_captureA_int( void )
{
static unsigned long int edgeA0;
register unsigned long int ctime;

ctime = (t0_high * 0x10000UL) + ITU_GRA0;

if( (ctime - edgeA0) > RotateDebounce )
  {
  if( DispenserCountBit && ITU_GRB3 && !IndexTable ) /* moving */
    {
	IP01Count = 0; /* ISS-086 change */
	    
    if( ++CountCur > 198 )
      CountCur = 0;
      
    if( OneDispCount )
      {
      if( !(CountCur % OneDispCount) )
        {
      	SeqOp.L |= O13;
        }
      else
        {
        SeqOp.L &= ~O13;
        }
      }	 

    DecPulse++;
    A0count++;
    }

  if( calcA0 && !(A0count % 2) )    /* 2 pulses per rpm calc */
    {
    countA0 = A0count;
    A0count = 0;
    durationA0 = ctime - startA0;
    startA0 = ctime;

    newA0 = 1;
/*    calcA0 = 0;*/
    }

  IndexCountR = IndexCountF;

  if( DispenserStatus == 1 )   /* used by film break */
    OP13_On = OP13_On ? 0 : 1;
  }

edgeA0 = ctime;

if ( ITU_TSR0 & 0x01 )       /* Clear interrupt request flag */
  ITU_TSR0 &= ~0x01;
}


interrupt [ITU_IMIB0] void t0_captureB_int( void )
{
static unsigned long int edgeB0, B0time;
static unsigned char Pcnt, Rcnt;

register unsigned long int ctime, durationB0, DelayLong;
register unsigned char Rpm;

ctime = (t0_high * 0x10000UL) + ITU_GRB0;

/* both edges are captured */
/* deafult debounce is 60ms on each edge or 8.33Hz max square wave */
if( (ctime - edgeB0) > RPMDebounce )
  {
  if( RpmCountBit && ITU_GRB3 && !IndexTable ) /* moving */
    DecRpm++;

  /*******/
    B0count++;

    if( calcA0b )
      {
      countB0 = B0count;
      B0count = 0;
      durationB0f = ctime - startB0f;
      startB0f = ctime;

      newA0b = 1;
      calcA0b = 0;
      }
  /*******/
    
  if( IP02 ) /* only control on falling edge */
    {
    SafetyCount = 0;

    if( IndexCountR )
      {
      IndexCountR--;
      }
    
    durationB0 = ctime - startB0;
    startB0 = ctime;

    switch( CapB0 )
      {
      case 1: /* pwm ramp up */
        /* done in timer with equal steps per second */
        break;

      case 11: /* start of pwm ramp down */
        DelayLong = (unsigned long)DelayST * (2000000UL / 10UL);
        if( ITU_GRB3 > PWMSlow2 )
          PWMstep = (unsigned short)(DelayLong / (unsigned long)(ITU_GRB3 - PWMSlow2));
        else
          PWMstep = PWMFREQ;
        CapB0 = 12;
        break;

      case 12: /* pwm ramp down */
        ITU_GRB3 -= (durationB0 / PWMstep);
        if( ITU_GRB3 < PWMSlow2 )
          {
          ITU_GRB3 = PWMSlow2;
          if( PLStable )
            {
            CapB0 = 9;
            }
          else
            {
            CapB0 = 14;
            }
          Pcnt = 0;
          Rcnt = 0;
          B0time = 0;
          PWMstep = (PWMmax + PWMSlow2) - PWMSlowTarget2; /* max pwm value */
          }
        break;

      case 13: /* pwm slow */
        CapB0 = 14;
        Pcnt = 0;
        Rcnt = 0;
        B0time = 0;
        if( IndexTable )
          {
          PWMstep = (PWMmax + PWMSlow1) - PWMSlowTarget1; /* max pwm value */
          }
        else
          {
          PWMstep = (PWMmax + PWMSlow2) - PWMSlowTarget2; /* max pwm value */
          }
        break;

      case 14:
        B0time += durationB0;
        Rcnt++;

        if( IndexTable && !IndexCountR )
          {
          ITU_GRB3 -= PWMIndexStep;
          CapB0 = 8;
          break;
          }

        if( Rcnt > RPMAVG )
          {
          Rcnt = 0;
          B0time = 0;
          }
        else if ( (Rcnt == RPMAVG) && B0time )
          {
          Rpm = ((unsigned long int)RPMAVG * 2000000UL * 60UL / PPRMotor) / B0time;  		          
          if ( Rpm > (RPMSlow + 1) )
            {
            ITU_GRB3 -= PWMerr;
            }
          else if ( Rpm < (RPMSlow - 1) )
            {
            ITU_GRB3 += PWMerr;
            }

          if ( ITU_GRB3 < PWMmin )
            {
            ITU_GRB3 = PWMmin;
            }
          else if ( ITU_GRB3 > PWMstep )
            {
            ITU_GRB3 = PWMstep;
            }
          }

        if ( Pcnt != 0xff )
          {
          if ( Pcnt > 3 ) /* 4 times before target saved */
            {
            if( IndexTable )
              {
              PWMSlow1 = (PWMSlow1 + ITU_GRB3) / 2;
              }
            else
              {
              PWMSlow2 = (PWMSlow2 + ITU_GRB3) / 2;
              }
            }

          if ( Zone == (Zone27 & 0x7f) ) /* end controlled rotate */
            {
            Pcnt = 0xff;
            CapB0 = 8;
            }
          else
            {
            Pcnt++;
            }
          }
        break;

      case 8: /* count only, leave capture on */
        break;

      case 9: /* pwm ramp pulse wait */
        if( PLStable )
          {
          PLStable--;
          }
        else
          {
          CapB0 = 14;
          }
        break;

      /*
      case 3: on fully
      */
      default: /* Timer Capture Int B off */
        ITU_TIER0 &= ~0x02;
        break;
      }
    }
  }

edgeB0 = ctime;

if ( ITU_TSR0 & 0x02 )       /* Clear interrupt request flag */
  ITU_TSR0 &= ~0x02;
}


interrupt [ITU_OVI2] void t2_overflow_int( void )
{
register unsigned long int ctime, ftime;

t2_high++; /* every 0.032768 seconds ( 65536/(16e6/8) ) */

ctime = (t2_high * 0x10000UL) + ITU_TCNT2;

ftime = ctime - startA2;
if( ftime > 540000UL ) /* 540000 = 0.27 secs */
  {
  countA2 = A2count;
  A2count = 0;
  durationA2 = ftime;
  startA2 = ctime;

  newA2 = 1;
  calcA2 = 0;
  }
else if( ftime > 400000UL ) /* 400000 = 0.25 secs */
  {
  if( !newA2 )
    {
    calcA2 = 1;
    }
  }

if( ITU_TSR2 & 0x04 ) /* Clear interrupt request flag */
  {
  ITU_TSR2 &= 0xfb;
  }

}


interrupt [ITU_IMIA2] void t2_captureA_int( void )
{
static unsigned long int edgeA2;
register unsigned long int ctime;

ctime = (t2_high * 0x10000UL) + ITU_GRA2;

if( (ctime - edgeA2) > 200UL ) /* 100us */
  {
  A2count++;

  if( calcA2 )
    {
    countA2 = A2count;
    A2count = 0;
    durationA2 = ctime - startA2;
    startA2 = ctime;

    newA2 = 1;
    calcA2 = 0;
    }
  }

edgeA2 = ctime;

if( ITU_TSR2 & 0x01 ) /* Clear interrupt request flag */
  {
  ITU_TSR2 &= ~0x01;
  }

}


interrupt [AD_ADI] void AtoD_int( void ) /* atod interrupt */
{

AtoD_Run = 0; /* stop conversions */
if( !AtoD_bank )
  {
  analogue[0] = ADDRA;
  analogue[1] = ADDRB;
  analogue[2] = ADDRC;
  analogue[3] = ADDRD;
  if( AtoD_Done )
    {
    ADCSR = 0x77; /* set to scan ain4-ain7 & start conversion */
    }
  }
else
  {
  analogue[4] = ADDRA;
  analogue[5] = ADDRB;
  analogue[6] = ADDRC;
  analogue[7] = ADDRD;
  if( AtoD_Done )
    {
    ADCSR = 0x00; /* set to off */
    }
  }

}


interrupt [IRQ_0] void remote_control_int( void )  /* remote receive interrupt */
{
static unsigned int EdgeTime, RemotePulseWidth;
static unsigned char Code, LastCode, BitCount, CodeCount;

register unsigned int TempTime;
register unsigned char TempCode;

TempTime = ITU_TCNT0;
RemotePulseWidth = TempTime - EdgeTime;
EdgeTime = TempTime;

if( RemotePulseWidth > 41800 )      /* 20.90ms */
  {
  if( RemotePulseWidth < 46200 )    /* 23.10ms */
    BitCount = 1;
  else
    {
    BitCount = 0;
    CodeCount = 0;
    }
  Code = 0;
  }
else if( RemotePulseWidth > 20900 )            /* 10.45ms */
  {
  if( BitCount && (RemotePulseWidth < 23100) ) /* 11.55ms */
    {
    BitCount++;
    Code <<= 1;
    }
  else
    {
    BitCount = 0;
    CodeCount = 0;
    Code = 0;
    }
  }
else if( RemotePulseWidth > 13940 )             /*  6.97ms */
  {
  if( BitCount && (RemotePulseWidth < 15400) )  /*  7.70ms */
    {
    BitCount++;
    Code = (Code | 1) << 1;
    }
  else
    {
    BitCount = 0;
    CodeCount = 0;
    Code = 0;
    }
  }

if( BitCount == 6 )
  {
  BitCount = 0;
  TempCode = Code >> 1;
  if( LastCode == TempCode )
    {
    if( CodeCount > 2 )      /* 1 for 3 codes, 2 for 4 codes */
      {
      RemoteCode = TempCode; /* two valid codes required */
      RemoteTimeOut = 0;     /* to start counting */
      }
    else
      { 
      CodeCount++;
      }
    }
  else
    {
    CodeCount = 0;
    }
  LastCode = TempCode;
  }

if( ISR & 0x01 ) /* Clear interrupt request flag */
  {
  ISR &= ~0x01;
  }
}


interrupt [IRQ_5] void CAN_controller_int( void ) /* CAN general interrupt */
{
	union usltoc lid; /* see bytedef.h */
	struct CanMessage *CMpt;

	switch( can_interrupt )
	{
	case 3: /* message object 1 */
		/* circular buffer - will overwrite data not read */
		CMpt = &CanM[CanHead++ & (CAN_MAXMESSAGE - 1)]; /* CAN_MAXMESSAGE is a power of 2*/

		/* save data */
		lid.c[0] = message01[ARB0];
		lid.c[1] = message01[ARB1];
		lid.c[2] = message01[ARB2];
		lid.c[3] = message01[ARB3];
        CMpt->id.l = lid.l;
		CMpt->dat[0] = message01[DATA0];
		CMpt->dat[1] = message01[DATA1];
		CMpt->dat[2] = message01[DATA2];
		CMpt->dat[3] = message01[DATA3];
		CMpt->dat[4] = message01[DATA4];
		CMpt->dat[5] = message01[DATA5];
		CMpt->dat[6] = message01[DATA6];
		CMpt->dat[7] = message01[DATA7];
		CMpt->time = CanCurrentTime;

		message01[CONTROL0] = C0_MSGVAL_NOP | C0_TXIE_NOP | C0_RXIE_NOP | C0_INTPND_CLR; /* clear interrupt pending bit, IntPnd */
		break;
	}

	if( ISR & 0x20 )
	{
		ISR &= ~0x20; /* Clear interrupt request flag */
	}
}



#endif
