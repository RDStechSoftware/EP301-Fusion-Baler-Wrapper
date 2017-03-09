
#include <inh83.h>
#include <ioh83003.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bytedef.h"


void SetLookUps( void )
{
unsigned char c, j;	
	
SeqErr = 0;


/* load delay lookup table */
for( c = 1; c < FCLAST; c++ ) /* Setup index array */
  {
  for( j = 0; j < MAXFACTOR; j++ ) /* Setup index array */
    {
	if( PF[j].Tag == c )
	  {
	  DelPul[c] = j;
	  break;
	  }
    }
  if( j == MAXFACTOR )
    {
    SeqErr = 9;
    ErrPos = c;
    return;
    }
  }

/* use lookup as follows */
/* c = PF[DelPul[SIODAT]].def[0] */

/* load switch lookup table */
for( c = 1; c < SWLAST; c++ ) /* Setup index array */
  {
  for( j = 0; j < MAXSWITCH; j++ ) /* Setup index array */
    {
	if( SW[j].Tag == c )
	  {
	  SwLook[c] = j;
	  break;
	  }
    }
  if( j == MAXSWITCH )
    {
    SeqErr = 10;
    ErrPos = c;
    return;
    }
  }
	
	
}


void ResetLubeCheck( void )
{
unsigned short int i;

i = (unsigned short int)Facts[DelPul[LUBECK]][0] * 10;
if( LubeCount < 0 )
  {
  LubeCount += i;
  }
else
  {
  LubeCount = i;
  }

}


void ResetType( unsigned short int type )
{
unsigned short i;

for( i = 0; i < MAXSWITCH; i++ )
  {
  if( (SW[i].type & RTYPE) == type )
    {
    SA[i] = 0xff;
    }
  }

for( i = 0; i < MAXFACTOR; i++ )
  {
    if( (PF[i].type & RTYPE) == type )
    {
      FA[i] = 0xfd;
    }
  }

}


void ResetSequenceFactors( unsigned int seq )
{
unsigned char c;
unsigned short i;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "ResetSequenceFactors" ); 
#endif

/* 0 = baleonly off, 1 = baleonly long beep, 2 = baleonly short beep */
SeqOffset = Facts[DelPul[SEQNUM]][0] ? 1 : 0;

/* preserve film break status */
CurrentSequenceMask = (CurrentSequenceMask & O_Flm) | OPTi[SeqOffset].Seq;

/* serial logging test */
SIOdata = Facts[DelPul[SIODAT]][0];

if( seq & SEQ_INIT )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " INIT" );
#endif

  CurrentSequenceMask &= ~O_Flm;
  CurrentSequenceMask &= ~O_Ps;

  Zone = 0;
  
  SeqOp.L = 0;
/* SeqOp.L &= (O02 | O08);*/ /* not sure why these two were not turned off in init, an earlier bug? */
  
  TimingBit = 0;

  DecTens = 0;
  DecUnits = 0;
  KnivTimer = 0;
  KnivStage = 0;

  TipCheck = 0;
  ResumeFrom = 0;
  Wrapping = 0;
  TransferBale = 0;
  TransferDone = 0;
  WrapStatusEnd = 0;
  NetCheck = 0;
  AdditiveEnOp = 1;
  /*TransferNow == 3*/
  if( AutoMan && Ip.I.IP09 )
    {
    TransferNow = 1;
    }
  else
    {
    TransferNow = 0;
    }
  Transfering = 0;
  TipThenTransfer = 0;
  PauseWhileTipping = 0;
  NetDoneWaitingTransfer = 0;
  ManTransDelay = 0;
  MTDchk = 0;
  Kniv1PresHigh = 0;
  Kniv2PresHigh = 0;
  
  lang = Facts[DelPul[LANGUA]][0];

  RotateDebounce = (unsigned long int)Facts[DelPul[ROTDEB]][0] * 200000UL;

  RPMDebounce = (unsigned long int)Facts[DelPul[RPMDEB]][0] * 2000UL;  

  PPRMotor = Facts[DelPul[MOTPPR]][0];

  IndexCountF = Facts[DelPul[IDXCNT]][0];
  IndexCountR = IndexCountF;

  PWMIndexStep = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[IDXPWM]][0]) / 1000);
  
  /* copy factor DLYV01 to DLYK01 (non programmable knives down delay) */
  if( KnivSystem == RELIEF_VALVE )
    {
    Facts[DelPul[DLYK01]][0] = Facts[DelPul[DLYV01]][0];
    }

  MachineStatus &= ~(MS_CLOSEPLUS | MS_KNIVETOP | MS_CHAMBEROPEN | MS_FLOORTOPUP);
  PauseZone = 0;
 /* ShowPause = 0;*/
  TransferSeqPaused = 0;
  }

if( seq & SEQ_WRAP )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " WRAP" );
#endif
  Zone = 0;
  MonitorFrequency = 0;
  CapB0 = 0;
  ITU_GRB1 = 0; /* Chamber Open off */
  ITU_GRB3 = 0; /* Fwd off */
  Op.O.OP17 = 0;
  OP03 = 0;
  SeqOp.L &= (O02 | O08);
  ITU_TMDR &= ~(0x08 | 0x02); /* Timer 3 & 1 PWM off */
  ITU_TIER0 &= ~0x02; /* Timer Capture Int B on */

  Wrapping = 0;
  IndexTable = 0;
  DispenserPosError = 0;

  TransferDone = 0;
  WrapStatusEnd = 0;

  RemoteRun = 0;
  ResetType( RWRAP );
  ResetType( RFILM );

  DelayLM = Facts[DelPul[DELYLM]][0];

  DelayST = Facts[DelPul[DELYST]][0];

  RPMSlow = Facts[DelPul[RPMSLO]][0];
  IP02Freq = (float)Facts[DelPul[IP2FRQ]][0]/10.0;

  if( NoPWM )
  {
	  PWMSlowTarget1 = (unsigned short)((PWMFREQ * 78UL) / 100);
	  PWMSlowTarget2 = (unsigned short)((PWMFREQ * 78UL) / 100);
	  PWMmax = (unsigned short)((PWMFREQ * 81UL) / 100);
	  PWMmin = (unsigned short)((PWMFREQ * 78UL) / 100);
  }
  else
  {
	  PWMSlowTarget1 = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[PWMSL1]][0]) / 100);
	  PWMSlowTarget2 = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[PWMSL2]][0]) / 100);
	  PWMmax = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[MAXPWM]][0]) / 100);
	  PWMmin = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[MINPWM]][0]) / 100);
  }

  PWMerr = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[ERRPWM]][0]) / 1000);

  c = Facts[DelPul[PWMCS1]][0];
  if( c >= 100 )
    {
    i = PWMFREQ + 1;
    }
  else
    {
    i = (unsigned short)(((unsigned long)c * PWMFREQ) / 100);
    }
  PWMChamber[0] = i;

  c = Facts[DelPul[PWMCS2]][0];
  if( c >= 100 )
    {
    i = PWMFREQ + 1;
    }
  else
    {
    i = (unsigned short)(((unsigned long)c * PWMFREQ) / 100);
    }
  PWMChamber[1] = i;

  c = Facts[DelPul[PWMCS3]][0];
  if( c >= 100 )
    {
    i = PWMFREQ + 1;
    }
  else
    {
    i = (unsigned short)(((unsigned long)c * PWMFREQ) / 100);
    }
  PWMChamber[2] = i;

  PLStable = Facts[DelPul[PLSTAB]][0];

  i = DelPul[PULSEP];
  FA[i] = Facts[i][0];
      
  /*PlsU = (CountSet + 0.5) * 2;*/
  PlsU = (CountSet * 2) + 1;
  if( Facts[DelPul[FILMBK]][0] == 2 )
    {
  	PlsU *= 2;
    }
  FA[DelPul[PULSEU]] = PlsU;

  i = DelPul[PULSER];
  FA[i] = PlsU - Facts[i][0];

  i = DelPul[PULSET];
  FA[i] = PlsU - Facts[i][0];

  c = (Facts[DelPul[DIVDEL]][0] == SL_SHORT) ? DIVSRT : DIVLNG;
  Facts[DelPul[DLYODE]][0] = Facts[DelPul[c]][0];

  c = Facts[DelPul[DIVDEL]][0];
  if( c == SL_MANUAL ) /* Open Pause */
  {
    c = 200; /* 20 second delay, so pause can be held/cancelled in main loop */

    Facts[DelPul[DELAY4]][0] = 0;
    Facts[DelPul[DELAY5]][0] = 0;
    Facts[DelPul[DELAY6]][0] = Facts[DelPul[DELYEF]][0];
  }
  else /* SL_SHORT or SL_LONG */
  {
    c = Facts[DelPul[(c == SL_SHORT) ? PAUSRT : PAULNG]][0];

    Facts[DelPul[DELAY4]][0] = 0;
    Facts[DelPul[DELAY5]][0] = 0;
    Facts[DelPul[DELAY6]][0] = Facts[DelPul[DELYEF]][0];
  }

  Facts[DelPul[DLYOGH]][0] = c;

  FilmPassCount = Facts[DelPul[FILMPS]][0];
  
  Facts[DelPul[DLYU06]][0] = Facts[DelPul[DLYU04]][0]; /* Iss-099 change, copy 'Floor Up' delay to DLYU06 */
  }

if( seq & SEQ_NET )
  {
	  ITU_GRB1 = 0; /* Brake On */
	  ITU_TMDR &= ~0x02; /* Timer 1 PWM off */
	  
  #ifdef SECONDSERIAL /* ###test */
   SendDebugString( " NET" );
  #endif

  NetHoldTime = 0;
  MachineStatus &= ~MS_CHAMBERFULL;

  /* get long/short beep and put in DELYAB */
  /* 0 = baleonly off, 1 = baleonly long beep, 2 = baleonly short beep */
  c = (Facts[DelPul[SEQNUM]][0] == 2) ? DELYSB : DELYLB;
  Facts[DelPul[DELYAB]][0] = Facts[DelPul[c]][0];

  ResetType( RNET );
  /*PWMBrakePower1 = (unsigned short)((PWMFREQ * (unsigned long)Facts[DelPul[PWMBP1]][0]) / 100);*/
  }

if( seq & SEQ_TIP )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " TIP" );
#endif
  ResetType( RTIP );
  if( Facts[DelPul[LANGUA]][0] == 3 ) /* French language */
  	{
  	Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX2]][0]; /* copy 'Tip bale French' */
  	}
  else
  	{
  	Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX1]][0]; /* copy 'Tip wrapped bale' */
  	}
  }

if( seq & SEQ_FILM )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " FILM" );
#endif
  ResetType( RFILM );
  }

if( seq & SEQ_PAUS )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " FILM" );
#endif
  ResetType( RPAUS );
  }

if( seq & SEQ_UNBK )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " UNBK" );
#endif
  UnBlockStatus = 0;  
  ResetType( RUNBK );
  }

if( seq & SEQ_KNVS )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " KNVS" );
#endif 
  if( KnivesEnabled && 
      (KnivesStatus & (KS_KNIVESIN | KS_KNIVESSETIN)) )
    {
    KnivesAutoUp = 1;
    }
  else
    {
    KnivesAutoUp = 0;
    }
  ResetType( RKNIV );
  }

if( seq & SEQ_CTOP )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " CTOP" );
#endif
  ResetType( RCTOP );
  }

if( seq & SEQ_LTOP )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " LTOP" );
#endif
  ResetType( RCTPL );
  }

/* EP301-011 */
if( seq & SEQ_FTOP )
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( " FTOP" );
#endif

  ResetType( RFTOP );
  }

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "\r\n" );
#endif
}


void StartWrapSequence( unsigned char mode )
{

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "StartWrapSequence " ); 
#endif

if( (mode & SWS_TRANS) && TableOccupied )
  {
  TipCheck = 1;
  ResumeFrom = Zone04;
  Zone = 0;
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SWS_TRANS & TableOccupied\r\n" ); 
#endif
  return;
  }

Wrapping = 1; /* to disable tip */
TableOccupied = 1; 

if( mode & SWS_RESETCOUNT )
  {
  CountCur = 0;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SWS_RESETCOUNT " ); 
#endif
  }

DecTens = 0;
DecUnits = 0;
DecPulse = 0;
DecRpm = 0;

SA[SwLook[VSWTCC]] = 0; /* cancel switch */

switch( mode & SWS_MODE )
  {
  case SWS_WRAP:
    Transfering = 0;
    if( !NetDoneWaitingTransfer )
      {
      ResetSequenceFactors( SEQ_NET );

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "!NetDoneWaitingTransfer " ); 
#endif
      }

    FA[DelPul[PDELEF]] = 0xff; /* cancel delay */
    FA[DelPul[DLYOCD]] = 0xff; /* cancel delay */
    FA[DelPul[PDLOEF]] = 0xff; /* cancel delay */
    SA[SwLook[PSWTEF]] = 0;    /* cancel switch */
    FA[DelPul[DELYFG]] = 0xff; /* cancel delay */
    SA[SwLook[PSWOEF]] = 0;    /* cancel switch */
    FA[DelPul[DLYOFG]] = 0xff; /* cancel delay */
    SA[SwLook[RSWTCA]] = 0;    /* cancel switch */
    FA[DelPul[DELYJK]] = 0x01; /* set delay for action */

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SWS_WRAP " ); 
#endif
    break;

  case SWS_TRANS:
    Transfering = 1;

    FA[DelPul[DELYDE]] = 0x01; /* set delay for action */
    
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SWS_TRANS " ); 
#endif
    break;
  }

DispenserCountBit = 0;
RpmCountBit = 0;
TimingBit = 1;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "\r\n" ); 
#endif
}


unsigned long int ValueToDigit( unsigned short int val )
{
union usltoc lc;

lc.c[3] = val % 10;
val /= 10;
lc.c[2] = val % 10;
val /= 10;
lc.c[1] = val % 10;
val /= 10;
lc.c[0] = val % 10;

return ( lc.l );
}


unsigned short int DigitToValue( unsigned long int val )
{
union usltoc lc;

lc.l = val;
return ( (lc.c[0] * 1000) + (lc.c[1] * 100) + (lc.c[2] * 10) + lc.c[3] );
}


unsigned short int IncCount( unsigned short int val, unsigned char digit, unsigned short int min, unsigned short int max )
{
union usltoc lc;

digit--;
lc.l = ValueToDigit( val );
if ( lc.c[digit] == 9 )
  lc.c[digit] = 0;
else
  lc.c[digit] += 1;
val = DigitToValue( lc.l );

if ( max > 9999 )
  max = 9999;
if ( val > max )
  {
  if ( max < 10 )
    {
    val = min;
    }
  else
    {
    val = max;
    }
  }
else if ( !(val >= min) )
  val = min;

return ( val );
}


unsigned short int DecCount( unsigned short int val, unsigned char digit, unsigned short int min, unsigned short int max )
{
union usltoc lc;

digit--;
lc.l = ValueToDigit( val );
if ( lc.c[digit] == 0 )
  lc.c[digit] = 9;
else
  lc.c[digit] -= 1;
val = DigitToValue( lc.l );

if ( max > 9999 )
  max = 9999;
if ( val > max )
  val = max;
else if ( !(val >= min) )
  val = min;

return ( val );
}

void SetOneDispRevs( void )
{
  /* check film on status from FILMBK */
  if( Facts[DelPul[FILMBK]][0] == 2 )
    {
  	/* 1 Disp Rev Count */
    OneDispCount = (Facts[DelPul[PLSFR3]][0] * 4);
   
    if( OneDispCount > PlsU )
      OneDispCount = PlsU;  	
    }
  else
    {
  	OneDispCount = 0;
    }  	
}


void FilmBreakCheck( void )
{
static unsigned char FFCount, Pass;  

unsigned short int i;

if( newA2 )
  {
  newA2 = 0;
  if( durationA2 )
    {
    FilmFrequency = (unsigned short int)(((float)countA2 * 2e6 / (float)durationA2) + 0.5);
    }

  /* check film on status from FILMBK */
  i = Facts[DelPul[FILMBK]][0];
  if( i ) /* if film break on */
    {
    switch( i )
    	{
      case 1: /* film break on */
        if( Op.O.OP03 && (ITU_GRB3 > PWMFREQ) )
        { /* if fwd output on (O03) and full speed  */
        if( Pass < 7 )
          { /* ignore first 8 readings, to allow reading to stabalize */
          Pass++;
          }
        else if( FilmFrequency < FF_TWO_DISPENSER - (FF_ONE_DISPENSER / 2) )
          {
          FFCount++;
          if( FFCount > FilmPassCount ) /* was  5 */
            {
            FFCount--; /* was 10 */
            if( FilmFrequency < (FF_ONE_DISPENSER / 2) )
              {
              SetFilmBreak();
              }
            else
              {
              SetOneDispenser();
              }
            }
          }
        else
          {
          FFCount = 0;
          }
        }
        else
          {
          Pass = 0;
          }
        break;
        
      case 2: /* 1 disp only */
        if( Op.O.OP03 && (ITU_GRB3 > PWMFREQ) )
        { /* if fwd output on (O03) and full speed  */
        if( Pass < 7 )
          { /* ignore first 8 readings, to allow reading to stabalize */
          Pass++;
          }
        else if(FilmFrequency < (FF_ONE_DISPENSER / 2))
          {
          FFCount++;
          if( FFCount > FilmPassCount ) /* was  5 */
            {
            FFCount--; /* was 10 */
            if( FilmFrequency < (FF_ONE_DISPENSER / 2) )
              {
              SetFilmBreak();
              }
            }
          }
        else
          {
          FFCount = 0;
          }
        }
        else
          {
          Pass = 0;
          }
        break;
    }
    
    }
  else
    {
    FFCount = 0;
    Pass = 0;
    }
  }

}


void SetFilmBreak( void )
{

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SetFilmBreak " ); 
#endif

if( DispenserStatus != 2 )
  { 
  if( !DispenserStatus )
    {
    PlsU = FA[DelPul[PULSEU]]; /* save current remaining count */
    }
  DispenserStatus = 2;

  if( CountCur )
    SavedCountCur = CountCur;
  else
    SavedCountCur = 1;

  CurrentSequenceMask = O_Flm;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "DispenserStatus = 2 " ); 
#endif
  }

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "\r\n" ); 
#endif

}


void SetOneDispenser( void )
{
unsigned short i;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SetOneDispenser " ); 
#endif

if( !DispenserStatus )
  {
  DispenserStatus = 1;

  /* double pulses to end of sequence & add 2 */
  i = DelPul[PULSEU];
  if( FA[i] < 120 )
    {
    FA[i] *= 2;
    }
  FA[i] += 5;
  PlsU = FA[i];

  i = DelPul[PULSER];
  FA[i] = PlsU - Facts[i][0];

  i = DelPul[PULSET];
  FA[i] = PlsU - Facts[i][0];

  /* increase PULSEP by 1 if not done */
  i = DelPul[PULSEP];
  if( FA[i] < 250 )
    {
    FA[i]++;
    }

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "DispenserStatus = 1 " ); 
#endif
  }

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "\r\n" ); 
#endif
}


void CancelBothIfOneDone( struct Sequence *SQSP, unsigned char SeqPnt )
{
unsigned char *ptd, *pts;	
unsigned short int i, j;

i = SwLook[SQSP->Pdl];
if( i >= MAXSWITCH )
  {
  SeqErr = 2;
  ErrPos = SeqPnt;
  return;
  }

pts = &SA[i];

j = DelPul[SQSP->Wdl];
if( j >= MAXFACTOR )
  {
  SeqErr = 1;
  ErrPos = SeqPnt;
  return;
  }

ptd = &FA[j];

if( *ptd == 0xff ) /* if delay/pulse done */
  {
  *pts = 0; /* set switch Action Done */
  }
else if( *pts == 0 ) /* if switch Done */
  {
  *ptd = 0xff; /* set delay/pulse done */
  }

}


unsigned char CheckSwitch( struct Sequence *SQSP, unsigned char SeqPnt )
{
unsigned char *pt;	
unsigned short int i;

struct Switches *swp;

i = SwLook[SQSP->Dlp]; /* get switch */
if( i >= MAXSWITCH )
  {
  SeqErr = 2;
  ErrPos = SeqPnt;
  return ( 1 );
  }

pt = &SA[i];
swp = &SW[i];

if( *pt ) /* if Action not Done */
  {       /* check action */
	/*
  if( SW[i].Tag == VSWTLP )
    {
	switch( KnivesBank )
	  {
	  case KB_KNIVES11:
	  if( Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar) )
        {
        Ip.I.LPRES = 1;
        }
	  break;
	  
	  case KB_KNIVES12:
	  if( Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar) )
        {
        Ip.I.LPRES = 1;
        }
	  break;

	  case KB_KNIVES23:
	  if( (Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar)) 
	   && (Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar)) )
        {
        Ip.I.LPRES = 1;
        }
	  break;
	  }
    }
  else if( SW[i].Tag == VSWCLP )
    {
	if( (Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar)) && Kniv1PresHigh )
      {
      Ip.I.LPRES = 1;
      }
	else if( (Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar)) && Kniv2PresHigh  )
	  {
	  Ip.I.LPRES = 1;		
	  }
    }
	 */ 
  if( ((swp->Act == CLOSED) &&  (swp->Switch & Ip.L)) ||
       ((swp->Act ==   OPEN) && !(swp->Switch & Ip.L)) )
    {
    *pt = 0; /* cancel action */
    LoadDelayAndOutputs( SQSP, SeqPnt );
    return ( 0 );
    }
  else
    {  
    return ( 1 );
    }
  }
else
  {	
  return ( 0 );
  }

}


void CheckDelayOrPulse ( struct Sequence *SQSP, unsigned char SeqPnt, unsigned char Action )
{
unsigned char *pt;	
unsigned short int i;

i = DelPul[SQSP->Dlp]; /* get Delay/Pulse */
if( i >= MAXFACTOR )
  {
  SeqErr = 3;
  ErrPos = SeqPnt;
  return;
  }

pt = &FA[i];

/*if( FA[i] == 254 )*/
if( *pt == 254 )
  {
  SeqErr = 7;
  ErrPos = SeqPnt;
  return;
  }

/*if( !FA[i] )*/ /* factor 0 then load outputs */
if( !(*pt) )
  {
  (*pt)--;
  LoadDelayAndOutputs( SQSP, SeqPnt );
  }

switch( PF[i].type & FTYPE )
  {
  case DLT:  /* Tenths */
    Action &= 0x01;
    break;

  case DLS:  /* Seconds */
    Action &= 0x02;
    break;

  case PLS:  /* Pulses */
    Action &= 0x04;
    break;

  case PLR:  /* Rpm Pulses */
    Action &= 0x08;
    break;

  default:
    Action = 0;
    break;
  }
/*if( Action && (FA[i] <= 250) )
  FA[i]--;*/
if( Action && (*pt <= 250) )
  {
  (*pt)--;
  }
}


void LoadDelayAndOutputs ( struct Sequence *SQSP, unsigned char SeqPnt )
{
unsigned short int i;
unsigned char c, AutoTip, *pt;

#ifdef SECONDSERIAL /* ###test */
 unsigned char tstring[32];
#endif

/* Switch off O06 when O05 comes on */
if( (Op.O.OP05) && AutoMan )
{
  SeqOp.L &= ~O06;
}

if( SQSP->Pdl )
  {
  i = DelPul[SQSP->Pdl]; /* get delay/pulse */
  if( i >= MAXFACTOR )
    {
    SeqErr = 4;
    ErrPos = SeqPnt;
    return;
    }

  pt = &FA[i];

  if( *pt == 254 )
    {
    SeqErr = 6;
    ErrPos = SeqPnt;
    return;
    }

  if( *pt != 0xfd ) /* exit if done */
    {
    return;
    }

  c = Facts[i][SeqOffset]; /* load delay */
  if( c == 252 )
    {
    c = Facts[i][0];
    }
  
  *pt = c; /* load delay */
  }

SeqOp.L &= ~SQSP->opA;                       /* set output */
if( SQSP->opA & O03 )  /* 0x00020000UL */
  {
  CapB0 = 8; /* for run on count */
  ITU_GRB3 = 0;       /* off */
  /* if capture is off run on count will not work!
  ITU_TIER0 &= ~0x02; / * Timer Capture Int B off * /
  */
  OP03 = 0;
  ITU_TMDR &= ~0x08;  /* Timer 3 PWM off */
  }

SeqOp.L |= SQSP->opO;
if( SQSP->opO & O03 )
  {
  CapB0 = 1; /* set for ramping speed up */
  ITU_GRB3 = PWMSlow1 - (unsigned short)((PWMFREQ * (unsigned long)2) / 100); /* %on at slow start for ramp up */
  PWMstep = (unsigned short)(PWMFREQ * (unsigned long)(2+8) / 100) / DelayLM;

  if ( ITU_TSR0 & 0x02 ) /* Clear interrupt request flag */
    ITU_TSR0 &= ~0x02;
  
  ITU_TIER0 |= 0x02;     /* Timer Capture Int B on */
  ITU_TMDR |= 0x08;      /* Timer 3 PWM on */
  }

if( SQSP->Act & ResetCurrentCount )         /* Reset count */
  {
  CountCur = 0;
  DecTens = 0;
  DecUnits = 0;
  DecPulse = 0;
  DecRpm = 0;
  }

if( SQSP->Act & CountingOff )
  {
  DispenserCountBit = (SQSP->Act & CountingMask) ? 1 : 0;
  if ( !(SQSP->Act & RpmCount) )
    {
    RpmCountBit = (SQSP->Act & CountingMask) ? 1 : 0;
    }
  }

if( SQSP->Act & TimingOff )
  {
  TimingBit = (SQSP->Act & TimingMask) ? 1 : 0;
  }

if( SQSP->Zne & 0x80 )
  {
  Zone = SQSP->Zne & 0x7f;

#ifdef SECONDSERIAL /* ###test */
 sprintf( tstring, "Zone%02u\r\n", Zone ); 
 SendDebugString( tstring );
#endif
 
  AutoTip = Facts[DelPul[AUTOTP]][0];
/*
 MS_NETTING
 MS_TRANSFER
 MS_BALEON
 MS_WRAPPING
 MS_TIPPING
*/
  switch( Zone  )
  {
    case (Zone01 & 0x7f):
	if( !NetDoneWaitingTransfer )
	{
		MachineStatus |= MS_CHAMBERFULL;
	}
	MachineStatus &= ~MS_CHAMBEROPEN;

	SetOneDispRevs();
      break;

    case (Zone02 & 0x7f):
		/*if( SavedCountCur ) //Commented out: This is the 2 year bug!!!
		{
			 moved to end
			 NetDoneWaitingTransfer = 1;
		}
		else*/

		if(SavedCountCur)
			SavedCountCur = 0;

		if( UnBlockStatus )
		{
			ResumeFrom = 0xac;
			Zone = 0;
		}
		else if( AutoTip && TableOccupied )
		{
			if( Wrapping )
			{
				TipThenTransfer = 1;
			}
			else
			{
				PauseWhileTipping = 1;
				if( IP01 )
				{
					if( !Ip.I.IP10 )
					{
						Ip.I.TIPST = 1;
					}
				}
			}
		}
      MachineStatus &= ~MS_CHAMBERFULL;
      MachineStatus |= MS_NETTING;
      AdditiveEnOp = 0; /* Iss-103 */
      NetDoneWaitingTransfer = 1;
      /* ###test */
      SetVolume( AlarmVolume );
      Music = Alarm01;
      break;

    case (Zone04 & 0x7f):
      if( SavedCountCur )
        {
        TipThenTransfer = 1;
        }
      else if( UnBlockStatus )
        {
        ResumeFrom = 0xac;
        /*Zone = 0; */
        }
      else if( !PauseWhileTipping ) /* not auto tip */
        {
      	Here[0] += 1;
        if( !AutoTip && TableOccupied )
          {
          if( !(MachineStatus & MS_TIPPING) )
            TipCheck = 1;

          ResumeFrom = Zone04;
          /*Zone = 0;*/
          }
        else if( !TipThenTransfer )
          {
        /*---\/-REV62-\/---*/	
          if( MachineStatus & MS_TIPPING ) /* Tipping */
            {
            PauseWhileTipping = 1;
            }
        /*---/\-REV62-/\---*/	
          else if((!IP01 && (IP01_timer > 10)) || (S2_flag))
            {
        	S2_flag = 1;
            DispenserPosError = 1;
            ResumeFrom = Zone04;
            Zone = 0;
            }
          /*Seems like when IP01 resets to closed (1) by itself, it stops the DOOR from opening*/
          	if( /*(PauseZone == 0) &&*/ (TransferSeqPaused == 0) ) /*Iss-127*/
          		{
          		Here[1] += 1;
          		StartTransfer();  /*Ip.I.TRANS = 1*/
          		}
          }  
        }
      else /* PauseWhileTipping = 1 */
        {
        if( IP01 )
          {
        	if( !Ip.I.IP10 )
            {
            Ip.I.TIPST = 1;
            }	          
          }
        else
          {
          DispenserPosError = 1;
          ResumeFrom = Zone04;
          Zone = 0;
          }
        }
      MachineStatus &= ~MS_NETTING;
      MachineStatus |= MS_NETCUT;

      if( (PauseZone == 1) && (TransferSeqPaused == 1) ) /* Iss-126 */
      	{
      	/*Here[1] += 1;*/
      	FlashLedR2 = 1;
      	Zone = 0;
      	PauseZone = 0;
      	}
      break;

    case (Zone05 & 0x7f):
      Wrapping = 1;
      Transfering = 1;
      SafetyCount = 0;
      IP01Count = 0; /* 086 */
      PulseFrequency = 0.0;
      MachineStatus &= ~(MS_NETCUT | MS_CHAMBEROPEN);
      MachineStatus |= MS_TRANSFER;
      break;

    case (Zone06 & 0x7f):
      Transfering = 0;
      NetDoneWaitingTransfer = 0;

      FA[DelPul[DELYHI]] = 0xff; /* set delay done */
      
      ResetSequenceFactors( SEQ_NET | SEQ_FILM );
 
      MachineStatus &= ~MS_TRANSFER;
      MachineStatus |= (MS_BALEON | MS_CLOSEPLUS);
      AdditiveEnOp = 1; /* Iss-103 */
      Ip.I.FTOP = 1; /* EP301-111 */

      break;

    case (Zone12 & 0x7f):
      if( !(MachineStatus & MS_NETTING) )
        {
        SetBeepType( BT3 | BP1, TBEXT, 1 ); /* 100/0ms On/Off, Int, 1 Count */
        }
    MonitorFrequency = 0;
      break;

    case (Zone18 & 0x7f):
    	/*Iss-132: SetBeepType is added from (zone33) as DELYUV never triggered zone33. Now the alarm turns off. */
		 if( !(MachineStatus & MS_NETTING) )
		{
		SetBeepType( BT0 | BP1, TBOFF, 0 ); /* all Beeps off */
		}
      TransferDone |= 0x02;
      if( AutoTip && IP01 && TableOccupied && Ip.I.IP08 && !Wrapping )
        {
    	  if( !Ip.I.IP10 )
            {
            Ip.I.TIPST = 1;
            }
        }
      goto Case_Zone13; /* WHAT IS THIS!?!?*/
    case (Zone13 & 0x7f):
      WrapStatusEnd |= 0x01;
    Case_Zone13:
      if( AutoTip && IP01 && TableOccupied && TipThenTransfer )
        {
        TipThenTransfer = 0;
        PauseWhileTipping = 1;
        if( !Ip.I.IP10 )
          {
          Ip.I.TIPST = 1;
          }
        }
      MachineStatus &= ~MS_WRAPPING;
      Wrapping = 0;
      ResetSequenceFactors( SEQ_TIP );
      break;

    case (Zone03 & 0x7f):
      if( (Zone != (Zone18 & 0x7f)) || !(MachineStatus & MS_NETTING) )
        {
        SetBeepType( BT0 | BP1, TBOFF, 0 );	/* all Beeps off */
        }
      break;
      
    case (Zone33 & 0x7f):
      if( !(MachineStatus & MS_NETTING) )
        {
        SetBeepType( BT0 | BP1, TBOFF, 0 ); /* all Beeps off */
        }
      break;

    case (Zone11 & 0x7f):
      if( NoPWM == 0 )
    	{
        SeqOp.O.OP13 = 1;
    	}
    	break;
    
    case (Zone10 & 0x7f):
    case (Zone15 & 0x7f):
      CapB0 = 11;            /* set for slow down */
      ITU_GRB3 = (PWMmax + PWMSlow2) - PWMSlowTarget2; /* %on at slow down */
      if ( ITU_TSR0 & 0x02 ) /* Clear interrupt request flag */
        ITU_TSR0 &= ~0x02;
      ITU_TIER0 |= 0x02;     /* Timer Capture Int B on */
      break;

    case (Zone14 & 0x7f):
	LEDSel &= ~0x01;
	if(PauseTip)
	{
		PauseTip = 0;
		Facts[DelPul[AUTOTP]][0] = 1;
	}

	if( ++TotalBales[BaleTotal] > 999999UL )
		TotalBales[BaleTotal] = 0UL;

	if( ++GrandTotalBales > 999999UL )
		GrandTotalBales = 0UL;

	LubeCount--;

	Tipping = 1;
	MachineStatus |= MS_TIPPING;
	MachineStatus &= ~MS_CHAMBEROPEN;
	break;

	case (Zone16 & 0x7f):
	if( PauseWhileTipping )
	{
		PauseWhileTipping = 0;
	if( !NetCheck && (Ip.I.IP09 || (FA[DelPul[DELAY7]] <= 20)) ) /*If 20 second delay has not expired*/
	  {
		  if( MachineStatus & MS_NETCUT )
			{
				if( !TransferSeqPaused ) /* Iss-125 */
				{
					StartTransfer(); /* Ip.I.TRANS = 1 */
				}
			}
	  }
	}
	else if( ResumeFrom == Zone04 )
	{
	ResumeFrom = 0;
	if( !NetCheck && (Ip.I.IP09 || (FA[DelPul[DELAY7]] <= 20)) ) /*If 20 second delay has not expired*/
	  {
		if( !TransferSeqPaused ) /* Iss-125 */
		{
			StartTransfer(); /* Ip.I.TRANS = 1 */
		}
	  }
	}
	else
	{
		Zone = 0;
	}

	TableOccupied = 0;
	TipCheck = 0;
	Tipping = 0;
	MachineStatus &= ~(MS_TIPPING | MS_BALEON);
      break;
      
    case (Zone48 & 0x7f):
      TableOccupied = 0;
      TipCheck = 0;
      Tipping = 0;
      ResetSequenceFactors( SEQ_TIP );
      /*MachineStatus &= ~MS_TIPPING;*/
      break;
      
    case (Zone49 & 0x7f):      
      FA[DelPul[BDELY3]] = 0xff;
      break;
      
    case (Zone17 & 0x7f):      
      TableOccupied = 1;      
      MTDchk = 1;
      break;

    case (Zone23 & 0x7f):
      UnBlockStatus = 3;
      /*KnivesStatus = KS_KNIVESIN;*/
      break;

    case (Zone63 & 0x7f):
      UnBlockStatus = 3;
      KnivesStatus = KS_KNIVESIN;
      break;


    case (Zone34 & 0x7f):
      /*KnivesStatus = KS_KNIVESOUT;*/
    case (Zone32 & 0x7f):
      ResetSequenceFactors( SEQ_UNBK );
      if( TransferNow == 2 )
        {
        TransferNow = 1;
        }
      
      if( ResumeFrom == 0xac )
        {
        if( NetCheck )
          {
          ResumeFrom = 0x00;
          }
        else if( TableOccupied )
          {
          ResumeFrom = 0xaa;
          }
        else
          {
          ResumeFrom = 0xab;
          }  
        }
      break;

    case (Zone66 & 0x7f):
      KnivesStatus = KS_KNIVESOUT;
    case (Zone65 & 0x7f):
      ResetSequenceFactors( SEQ_UNBK );
      if( TransferNow == 2 )
        {
        TransferNow = 1;
        }
      
      if( ResumeFrom == 0xac )
        {
        if( NetCheck )
          {
          ResumeFrom = 0x00;
          }
        else if( TableOccupied )
          {
          ResumeFrom = 0xaa;
          }
        else
          {
          ResumeFrom = 0xab;
          }  
        }
      break;

    case (Zone26 & 0x7f):
      MachineStatus |= MS_WRAPPING;
      DispenserStatus = 0;
      break;

    case (Zone28 & 0x7f):
      NetCheck = 1;
      break;

    case (Zone19 & 0x7f):
#if 0    	
      if( UnBlockStatus < 2 )
        {
        if( !KnivesEnabled )
          {
          SeqOp.L |= O15;
          KnivesStatus = KS_KNIVESIN;
          }
        else if( KnivesEnabled )
          {
          /* If knives up or reset set (flashing 'K') */
          if( KnivesAutoUp || 
              (KnivesStatus & (KS_KNIVESOUT | KS_KNIVESSETOUT)) )
            {
              SeqOp.L |= O16;
              KnivesStatus = KS_KNIVESOUT;
            }
          }
        KnivesAutoRun = 1;
        }    
#endif    
      break;

    case (Zone21 & 0x7f):
      ITU_GRB1 = 0;
      Op.O.OP17 = 0;
      ITU_TMDR &= ~0x02; /* Timer 1 PWM off */
      break;
      /*
    case (Zone22 & 0x7f):
      if( !InitialKnivDownRoutineDone )
        {
    	SeqOp.L |= O07;
    	SeqOp.L |= O10;
        }
      else if( !KnivesBank )/ * EP306-003, knives down routine when a particular knife bank is selected has already finished * /
        {
    	if( Kniv1Pres > KnifeDownPresBar )
    	  {
    	  SeqOp.L |= O07;
    	  }
    	
    	if( (Kniv2Pres > KnifeDownPresBar) && (CanStatus == CSTATUS_OK) )        	
    	  {
    	  SeqOp.L |= O10;
    	  }
        }
      break;
      */

    case (Zone68 & 0x7f):
      KnivesStatus = KS_KNIVESIN;
      break;
      
    case (Zone30 & 0x7f):    	
      /*ITU_GRB1 = PWMChamber[PWMChamberNow];
      ITU_TMDR |= 0x02; *//* Timer 1 PWM on */

      if( !RunOnce ||
          ((KnivesStatus & (KS_KNIVESIN | KS_KNIVESSETIN)) && KnivesAutoUp) )
        {
        RunOnce = 1;
        /* O16, Knives Up, so use DLYU02 */
        /*FA[DelPul[DELYFG]] = Facts[DelPul[DLYU02]][0];*/ /* set to DLYU02 first time around */
        /* Above instruction ignored in ISS 83 on 20090518 to avoid having different bale the first time. */
        }

      if( UnBlockStatus < 2 )
        {
        if( KnivesEnabled )
          {
          /* If knives up or reset set (flashing 'K') */
           if( KnivesAutoUp /*||
              (KnivesStatus & (KS_KNIVESOUT | KS_KNIVESSETOUT))*/ )
            {*/
            SeqOp.L |= O16; /*Iss-149*/
          /*  KnivesStatus = KS_KNIVESOUT;
            }
          }
        KnivesAutoRun = 1;
        }
      MachineStatus |= MS_KNIVETOP;      
      break;

    case (Zone37 & 0x7f):
      ResetSequenceFactors( SEQ_KNVS );
    case (Zone31 & 0x7f):
      KnivesAutoRun = 0;
      MachineStatus &= ~MS_KNIVETOP;
      
      if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
        {
        SeqOp.L &= ~O15;
        }
      else if( KnivSystem == RELIEF_VALVE )
        {
    	SeqOp.L &= ~O16;
        }
      break;

    case (Zone35 & 0x7f):
      WrapStatusEnd |= 0x02;
      break;

    case (Zone36 & 0x7f):
      TransferDone |= 0x01;
      MachineStatus &= ~MS_CLOSEPLUS;
      MachineStatus |= MS_TRANSDONE;
      break;

    case (Zone38 & 0x7f):
      if( !UnBlockStatus )
        {
    	if( KnivSystem == RELIEF_VALVE )
    	  SeqOp.L |= O07; /* Turn on Floor Diverter */
        }
      break;

    case (Zone39 & 0x7f):
      if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
        {
    	if( !(SeqOp.L & (O07 | O10)) )  
          {
          SeqOp.L |= O15; /* Top up should not happen if either O07 or O10 is on. */
          MachineStatus |= MS_FLOORTOPUP; /* Iss-108 change */
          }
        }
      break;      
      
    case (Zone69 & 0x7f):
    if( KnivSystem == RELIEF_VALVE )
      {
      if( SeqOp.L & O07 ) /* Floor Diverter from Zone38 */
        {
        SeqOp.L |= O15;
        }
      }
      break;

    case (Zone70 & 0x7f):
      if( KnivSystem == RELIEF_VALVE )
        {            
        SeqOp.L &= ~O15;      
        }
      else if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
        {
      	SeqOp.L &= ~O16;
        }
      break;
            
    case (Zone57 & 0x7f):
      MachineStatus &= ~MS_FLOORTOPUP; /* Iss-108 change */
      ResetSequenceFactors( SEQ_FTOP );
      break;

    	
    case (Zone40 & 0x7f):
      ResetSequenceFactors( SEQ_CTOP );
      TopUpCount++;
      break;

    case (Zone71 & 0x7f):
      if( Op.O.OP03 && ITU_GRB3 ) /* for safety */
      	{
      	SeqOp.L |= O11;
      	}
      break;

    case (Zone41 & 0x7f):
      if( MTDchk == 1 )
        {
        MTDchk = 0;
        }
      break;

    case (Zone42 & 0x7f):
      ResetSequenceFactors( SEQ_LTOP );
      LubeTopUpCount |= LT_START; /* set for restart */
      break;

    case (Zone43 & 0x7f):
      CurrentSequenceMask &= ~O_Flm;
      ResetSequenceFactors( SEQ_FILM );
      break;

    case (Zone72 & 0x7f):
      CurrentSequenceMask &= ~O_Ps;
      ResetSequenceFactors( SEQ_PAUS );
      break;

    case (Zone73 & 0x7f):
    	PauseZone = 1;
      break;

    case (Zone44 & 0x7f):
      Transfering = 0;
      NetDoneWaitingTransfer = 0;
      MachineStatus &= ~(MS_TRANSFER | MS_CLOSEPLUS);
      MachineStatus |= (MS_CHAMBEROPEN | MS_TRANSDONE);
      ResetSequenceFactors( SEQ_WRAP );
      break;     
    
    case (Zone47 & 0x7f):      
      MonitorFrequency = 1;
      break;
      
    case (Zone22 & 0x7f):
    if( (KnivSystem == x23_Std) || (KnivSystem == x25_Std))
      {
      SeqOp.L &= ~O10;
      }      
      break; 
      
    case (Zone50 & 0x7f):      
	  ResetSequenceFactors( SEQ_KNVS );
	  if( InitialRoutine ) /* EP306-004 */
	    {
	   	InitialKnivDownRoutineDone = 1;
	   	InitialRoutine = 0;
      }
      break;
    }
  }

if( SQSP->Act & TwoBeeps )
  {
  SetBeepType( BT1 | BP3, TBINT, 2 ); /* 100/200ms On/Off, Int, 2 Count */
  }

if( TransferDone == 0x03 )
  {
  DispenserCountBit = 1;
  RpmCountBit = 1;
  ResetSequenceFactors( SEQ_WRAP );
  }

if( WrapStatusEnd == 0x03 )
  {
  DispenserCountBit = 1; /* counting on */
  ResetSequenceFactors( SEQ_WRAP );
  }

if( SQSP->Act & SequenceReset )
  {
  ResetSequenceFactors( SEQ_WRAP );
  }

}


unsigned char WaitUntilDone ( struct Sequence *SQSP, unsigned char SeqPnt )
{
unsigned char *pt;	
unsigned short int i;

if( SQSP->Act & WaitForWdl )
  {
  i = DelPul[SQSP->Wdl]; /* get delay/pulse */
  if( i >= MAXFACTOR )
    {
    SeqErr = 1;
    ErrPos = SeqPnt;
    return ( 0 );
    }
  
  pt = &FA[i];

  if( *pt == 254 )
    {
    SeqErr = 5;
    ErrPos = SeqPnt;
    return ( 0 );
    }

  if( (*pt) != 0xff ) /* check delay/pulse */
    {
    return( 0 ); /* exit if not done */
    }
  else
    {	  
    return ( 1 );
    }
  }
else if ( SQSP->Act & WaitForSW )
  {
  i = SwLook[SQSP->Wdl]; /* get switch */	
  if( i >= MAXFACTOR )
    {
    SeqErr = 1;
    ErrPos = SeqPnt;
    return ( 0 );
    }

  if( SA[i] != 0 ) /* reset action */
    {	  
    return( 0 ); /* exit if not done */
    }
  else
    {	  
    return( 1 );
    }
  }
else
  {	
  return ( 1 );
  }
}


void SetForResume( void )
{
unsigned int i;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SetForResume\r\n" ); 
#endif

DispenserStatus = 0;

/* set remaining pulses */
i = DelPul[PULSEU];
if( FA[i] > SavedCountCur ) /* FA[i] == Facts[i][0] because of reset */
  {
  FA[i] = FA[i] - SavedCountCur + 2; /* set pulse */
  }
else
  {
  FA[i] = 2;
  }
PlsU = FA[i];

/* set for cut hold open if not complete */
i = DelPul[PULSEP];
if( FA[i] > SavedCountCur )
  {
  FA[i] = FA[i] - SavedCountCur + 2; /* set pulse */
  }
else
  {
  FA[i] = 0xff; /* cancel pulse */
  }

i = DelPul[PULSER];      /* PlsU is a minimum of 2, PULSER = 2 or 3 */
if( PlsU > Facts[i][0] ) /* can't use FA[i] as this is set to X-PULSER */
  {
  FA[i] = PlsU - Facts[i][0];
  }
else
  {
  FA[i] = 0; /* set for action */
  }

i = DelPul[PULSET];
FA[i] = PlsU - Facts[i][0]; /* PlsU is a minimum of 2, PULSET = 1 */

CountCur = SavedCountCur;
SavedCountCur = 0;

}


void SetForReStart( void )
{
unsigned int i;
unsigned char rc;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "SetForReStart\r\n" ); 
#endif

DispenserStatus = 0;

/* get rewrap threshold */
i = DelPul[PLSFR1];
if( SavedCountCur > (Facts[i][0] * 2) )
  {
  /* get extra wrap count */
  i = DelPul[PLSFR2];
  rc = Facts[i][0] * 2;

  /* set remaining pulses */
  i = DelPul[PULSEU];
  if( (FA[i] + rc) > SavedCountCur )
    {
    FA[i] = (FA[i] + rc) - SavedCountCur; /* set pulse */
    }
  else
    {
    FA[i] = rc;
    }
  PlsU = FA[i]; 

  /* leave PULSEP, cut hold release (is 1) */

  i = DelPul[PULSER];
  rc = Facts[i][0]; /* can't use FA[i] as this is set to X-PULSER */
  if( PlsU > rc )
    {
    FA[i] = PlsU - rc;
    }
  else
    {
    FA[i] = 0; /* set for action */
    }

  i = DelPul[PULSET];
  FA[i] = PlsU - Facts[i][0];

  CountCur = SavedCountCur;
  }
else /* full re-wrap */
  {
  CountCur = 0;
  }

SavedCountCur = 0;

}


void SetBeepType( unsigned char type, unsigned char tone, unsigned char count )
{

if( type == TBOFF )
  {
  BeepTone = 0;
  BeepCount = 0;
  BeepType = 0;
  NoteLength = 0;
  Music = NULL;
  ExternalAlarm = 0;
  }
else
  {
  /* check priority, 0 highest, 3 lowest */
  /* if last alarm active & priority of alarm higher, then exit */
  if( BeepType && ((BeepType & PMASK) < (type & PMASK)) )
    {
    return;
    }
  BeepType = type;
  /* if tone type changes set new tone (for TB1/TB2 changes!) */
  if( !(tone & TMASK) || ((tone & TMASK) != (BeepTone & TMASK)) )
    {
    BeepTone = tone;
    switch( tone )
      {
      case TBEXT:
      case TBOTH:
      case TBALL: /* Loud */
        SetVolume( AlarmVolume );
        break;

      case TBOFF:
      case TBINT:
      default: /* Quiet */
        SetVolume( KeyVolume );
        break;
      }
    }
  BeepCount = count;
  }


if(UnBlockStatus == UB_UNBLOCKOUT)
{
  BeepOff = 62; /* 250ms Off */
  BeepOn =  62; /* 250ms On */
}
else if(UnBlockStatus == UB_UNBLOCKIN)
{
  BeepOff = 50; /* 200ms Off */
  BeepOn =  62; /* 250ms On */
}
else if(UnBlockStatus == UB_UNBLOCKSET)
{
  BeepOff = 250; /* 1000ms Off */
  BeepOn =  62; /* 250ms On */
}
else if(UnBlockStatus == UB_UNBLOCKWAIT)
{
  BeepOff = 125; /* 500ms Off */
  BeepOn =  62; /* 250ms On */
}
else
{
switch( type & BMASK )
  {
  case BT1:
    BeepOff = 50; /* 200ms Off */
    BeepOn = 25;  /* 100ms On */
    break;

  case BT2:
    BeepOff = 25; /* 100ms Off */
    BeepOn = 25;  /* 100ms On */
    break;

  case BT3: /* continuous beep */
    BeepOff = 0; /* never Off */
    BeepOn = 25; /* 100ms Off */
    break;

  case BT4:
    BeepOff = 250; /* 1000ms Off */
    BeepOn  = 125; /*  500ms Off */
    break;

  case BT5:
    BeepOff = 125; /* 500ms Off */
    BeepOn = 125;   /* 500ms On */
    break;

  case BT6:
    BeepOff = 125; /* 500ms Off */
    BeepOn  = 60;  /* 250ms On */
    break;

  case BT7:
    BeepOff = 250; /* 1000ms Off */
    BeepOn  = 60;  /* 250ms On */
    break;

  default:
    BeepOff = 50; /* 200ms Off */
    BeepOn = 25;  /* 100ms On */
    break;
  }
}

}

void UnBlock( void )
{
if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "Unblock\r\n" ); 
#endif
  if( !(Tipping || OMS_TIP) && (swtim > 19) ) /* 2 seconds */
    { /* lower floor */
    FA[DelPul[DLYUS3]] = 0x00; /* set for action */
    TimingBit = 1;
    Zone = Zone24 & 0x7f;
    UnBlockStatus = 2;
    }
  else
    {
    UnBlockStatus = 1;
    }
  }
else if( KnivSystem == RELIEF_VALVE )
  {
	unsigned char c;

	#ifdef SECONDSERIAL /* ###test */
	 SendDebugString( "StartUnblock\r\n" ); 
	#endif

	if( !KnivesAutoRun && !(Tipping || OMS_TIP) && (swtim > 19) ) /* 2 seconds */
	  { /* lower floor/knives */
	  if( KnivesStatus & KS_KNIVESOUT )
	    { /* knives down first */
	    Knives_Up = 1;
	    c = DelPul[DLYVS1];
	    }
	  else
	    { /* skip knives down */
	    Knives_Up = 0;
	    c = DelPul[DLYV01];
	    }

	  FA[c] = 0x00; /* set delay for action */
	  TimingBit = 1;
	  Zone = Zone62 & 0x7f;
	  UnBlockStatus = 2;
	  }
	else
	  {
	  UnBlockStatus = 1;
	  }	
  }
}

#if 0
void StartUnBlock( void )
{
unsigned char c;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "StartUnblock\r\n" ); 
#endif

if( !KnivesAutoRun && !(Tipping || OMS_TIP) && (swtim > 19) ) /* 2 seconds */
  { /* lower floor/knives */

  if( KnivesStatus & KS_KNIVESOUT )
    { /* knives down first */
    Knives_Up = 1;
    c = DelPul[DLYUS1];
    }
  else
    { /* skip knives down */
    Knives_Up = 0;
    c = DelPul[DLYU01];
    }

  FA[c] = 0x00; /* set delay for action */
  TimingBit = 1;
  Zone = Zone22 & 0x7f;
  UnBlockStatus = 2;
  }
else
  {
  UnBlockStatus = 1;
  }

}
#endif

#if 0 
void StopUnBlock( void )
{
unsigned char c;

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "StopUnblock\r\n" ); 
#endif


if( !KnivesAutoRun && !(key & KeyDone) )
  {/*
  if( KnivesEnabled && KnivesAutoUp )*/
  if( Knives_Up )
    { /* run knives up */
    c = DelPul[DLYUS3];
    }
  else
    { /* skip knives up */
    c = DelPul[DLYUS4];
    }

  Knives_Up = 0;
  FA[c] = 0x00; /* set delay for action */
  TimingBit = 1;
  Zone = Zone24 & 0x7f;
  UnBlockStatus = 4;
  }

}
#endif

void ResetFloor( void )
{
if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
  {
#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "StopUnblock\r\n" ); 
#endif
 
  FA[DelPul[DLYUS4]] = 0x00;  
  TimingBit = 1;
  Zone = Zone29 & 0x7f;
  UnBlockStatus = 4;
  }
else if( KnivSystem == RELIEF_VALVE )
  {
	unsigned char c;

	#ifdef SECONDSERIAL /* ###test */
	 SendDebugString( "StopUnblock\r\n" ); 
	#endif

	if( !KnivesAutoRun && !(key & KeyDone) )
	  {/*
	  if( KnivesEnabled && KnivesAutoUp )*/
	  if( Knives_Up )
	    { /* run knives up */
	    c = DelPul[DLYVS3];
	    }
	  else
	    { /* skip knives up */
	    c = DelPul[DLYVS2];
	    }

	  Knives_Up = 0;
	  FA[c] = 0x00; /* set delay for action */
	  TimingBit = 1;
	  Zone = Zone64 & 0x7f;
	  UnBlockStatus = 4;
	  }	
  }
}

/*
struct Leds {
   unsigned LedR4: 1;  / * Bit  0 * / 
   unsigned LedL4: 1;  / * Bit  1 * /
   unsigned LedL3: 1;  / * Bit  2 * /
   unsigned LedR3: 1;  / * Bit  3 * /

   unsigned LedL2: 1;  / * Bit  4 * /
   unsigned LedR2: 1;  / * Bit  5 * /
   unsigned LedR1: 1;  / * Bit  6 * /
   unsigned LedL1: 1;  / * Bit  7 * /

   unsigned Spare1: 8; / * Bit 8-15 * /
   };

union LEDsWide  {
  struct Leds L;
  unsigned char C[2];
  unsigned short int S;
  };
extern union LEDsWide LedData;
*/
void SetLedData( void )
{
	unsigned char AutoTip;
	
	if( flash_bit )
	{
		AutoTip = Facts[DelPul[AUTOTP]][0];
		
		if( NetCheck && (NetWarnCanc & 0x04) )
		{
			LedData.L.LedL1 = 1;
		}
		else if( (NetWarnCanc & 0x04) || TransferBale || FlashLedR2 ||
				 ((RaiseDoor & 0x01) && (MachineStatus & MS_TRANSFER) && TableOccupied)  )
		{
			LedData.L.LedR2 = 1; 	
		}
		else if( (PauseTip || (TableOccupied && !AutoTip) || ((LEDSel & 0x01) && AutoMan)) && 
				 !(Wrapping || OMS_WRAP) && !Tipping && !(MachineStatus & (MS_WRAPPING | MS_CHAMBEROPEN)) )
		{
			LedData.L.LedR4 = 1;  	
		}
	}
	else
	{
		LedData.S = 0;
	}
}


unsigned char StartDelayComplete( void ) /*rev. 30 fix bug!*/
{
	if( demi_secs < 2 )
	{
	SetBeepType( BT2 | BP1, TBALL, 1 ); /* 100/100ms On/Off, Ext, 1 Count */

		if(( key & ~KeyMask ) == Key_R1)
		{
			KeyOp.L = O17;
		}
		/*  SetBeepType( BT2 | BP2, TBOTH, 2 );*/ /* 100/200ms On/Off, Int, 2 Counts */
		return( 0 );
		}
		else
		{
		return( 1 );
		}
}


void StartTransfer( void )
{

#ifdef SECONDSERIAL /* ###test */
 SendDebugString( "StartTransfer\r\n" ); 
#endif

if( !Ip.I.IP04 ) /* TIPUP */
  {
  TipPosErr = 1;
  ResumeFrom = Zone04;
  Zone = 0;
  }
else
  {
  SA[SwLook[RSWTCF]] = 0x00; /* cancel switch - set switch done */
  SA[SwLook[RSWTCB]] = 0x00; /* cancel switch - set switch done */
  FA[DelPul[DELYCD]] = 0xff; /* cancel wait for delay - set delay done */

  Ip.I.TRANS = 1;
  }
}


void CheckLubeTopUp( void )
{
unsigned char c;

c = Facts[DelPul[LUBEDS]][0];
if( c > 1 ) /* 1 = off, 2-8 repeat count */
  {
  /* if Knives divertor on, cancel topup */
  if( LubeTopUpCount && (Op.O.OP10 || (MachineStatus & MS_TIPPING)) )
    {
    LubeTopUpCount = 0;

    /* if output O09 on (duration delay running) turn off */ 
    if( FA[DelPul[DLUBED]] < 250 ) /* delay running */
      {
      SeqOp.L &= ~O09; /* OP09 Tip return */
      }
    ResetType( RCTPL );
    }
  else if( (LubeTopUpCount & LT_COUNT) < c )
    {
    /* if transfer done and Knives divertor off, start topup */
    if( (MachineStatus & MS_TRANSDONE) &&
        !(MachineStatus & MS_TIPPING) &&
        !Op.O.OP10 )
      {
      if( !LubeTopUpCount )
        {
        LubeTopUpCount = LT_START;
        }

      if( LubeTopUpCount & LT_START )
        {
        LubeTopUpCount &= ~LT_START;
        LubeTopUpCount++;
        Ip.I.LTOP = 1; /* start lube topup */
        }
      }
    }
  else
    {
    MachineStatus &= ~MS_TRANSDONE;

    ResetType( RCTPL );
    }
  }
else if( LubeTopUpCount ) /* reset lube top up sequence */
  {
  LubeTopUpCount = 0;

  /* if output O09 on (duration delay running) turn off */ 
  if( FA[DelPul[DLUBED]] < 250 ) /* delay running */
    {
    SeqOp.L &= ~O09; /* OP09 Tip return */
    }
  ResetType( RCTPL );
  }

}


#ifdef SECONDSERIAL
void SendDebugString( unsigned char *pt )
{
unsigned char len, free, time;

len = strlen( pt );
time = demi_secs;

while( free && (len > free) )
  {
  if( SCI1_SSR & 0x84 ) /* enable interrupt if tx empty & transmit end */
    {
    SCI1_SCR |= 0x24;
    }

  free = s1tx_tail - s1tx_head;

  if( abs( demi_secs - time ) > 10 )
    {
    return;
    }
  }

while( len-- )
  {
  s1tx_buff[s1tx_head++] = *pt++;
  }

if( SCI1_SSR & 0x84 ) /* enable interrupt if tx empty & transmit end */
  {
  SCI1_SCR |= 0x24;
  }

}
#endif


void CalculateFreq( void )
{
/*unsigned char c;*/
if( newA0b )
  {
  newA0b = 0;
  if( durationB0f )
		{
		PulseFrequency = ( ((float)countB0 * 2e6 / (float)durationB0f) + 0.5 );
		PulseFrequency = PulseFrequency/2.0;
		}
  }
}

/* Knives monitoring outside a netting sequence */
void MonitorKnives( void )
{
	switch( KnivMonitorStage )
	{
	default:
	case 0:
		if( KnivesBank == KB_KNIVES11 )
		{
			/*if( Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar) )
		    {
		  		if( !(SeqOp.L & O07) )
		  		{
					SeqOp.L |= O07;
					KeyS1Delay = 20;
			    }	  		
		  		if( KeyS1Delay > 25 )
		  		{
		  			SeqOp.L |= O15;
		  			KnivMonitorStage = 1;
		  		}
		    }*/
			if( Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar) )
			{
				Kniv1PresHigh = 0;
				if( !(SeqOp.L & O07) )
				{
					/*SeqOp.L |= O07;*/
					KeyS1Delay = 20;
				}
			}
			else
			{
				Kniv1PresHigh = 1;
			}

			if ((SeqOp.L & O07) && !Kniv1PresHigh)
		    {
				if( KeyS1Delay > 25 )
				{
					SeqOp.L |= O15;
					KnivMonitorStage = 1;
					KnivTimer = 50;
				}
		    }
		}
		else if( KnivesBank == KB_KNIVES12 )
		{
			/*if( Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar) )
		    {
		  		if( !(SeqOp.L & O10) )
		  		{
					SeqOp.L |= O10;
					KeyS1Delay = 20;
			    }	  		
		  		if( KeyS1Delay > 25 )
		  		{
		  			SeqOp.L |= O15;
		  			KnivMonitorStage = 1;
		  		}
		    }*/
			if( Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar) )
			{
				Kniv2PresHigh = 0;
				if( !(SeqOp.L & O10) )
				{
					/*SeqOp.L |= O10;*/
					KeyS1Delay = 20;
				}
			}
			else
			{
				Kniv2PresHigh = 1;
			}

			if ((SeqOp.L & O10) && !Kniv2PresHigh)
		    {
				if( KeyS1Delay > 25 )
				{
					SeqOp.L |= O15;
					KnivMonitorStage = 1;
					KnivTimer = 50;
				}
		    }
		}
		else if( KnivesBank == KB_KNIVES23 )
		{
			if( KeyS1Delay > 25 )
			{
				if( Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar) )
				{
					Kniv1PresHigh = 0;
					if( !(SeqOp.L & O07) )
					{
						/*SeqOp.L |= O07;*/
						KeyS1Delay = 20;
					}
				}
				else
				{
					Kniv1PresHigh = 1;
				}

				if( Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar) )
				{
					Kniv2PresHigh = 0;
					if( !(SeqOp.L & O10) )
					{
						/*SeqOp.L |= O10;*/
						KeyS1Delay = 20;
					}
				}
				else
				{
					Kniv2PresHigh = 1;
				}
			}

			
			if( ((SeqOp.L & O07) && !Kniv1PresHigh) && ((SeqOp.L & O10) && !Kniv2PresHigh) )
		    {		
				if( KeyS1Delay > 25 )
				{
					SeqOp.L |= O15;
					KnivMonitorStage = 1;
					KnivTimer = 50;
				}
		    }
		}
		break;
		
	case 1:
		if( KnivesBank == KB_KNIVES11 )
		{
			if( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				/*if( !KnivTimer )
				{
					SeqOp.L |= O15;
					KnivTimer = 50;  5 sec
					KnivMonitorStage = 2;
				}*/
				if( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) )
				{
					if( !KnivTimer )
					{
						KnivTimer = 50; /* 5 sec */
						KnivMonitorStage = 2;
					}
				}
			}
		}
		else if( KnivesBank == KB_KNIVES12 )
		{
/*			if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				if( !KnivTimer )
				{
					SeqOp.L |= O15;
					KnivTimer = 50;  5 sec
					KnivMonitorStage = 2;
				}
			}*/
			if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				if( !KnivTimer )
				{
					KnivTimer = 50; /* 5 sec */
					KnivMonitorStage = 2;
				}
			}
		}
		else if( KnivesBank == KB_KNIVES23 )
		{
			if(( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) ) &&
			   ( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) ))
			{
				if( !KnivTimer )
				{
					KnivTimer = 50; /* 5 sec */
					KnivMonitorStage = 2;
				}
			}

/*			if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				if( !KnivTimer )
				{
					KnivTimer = 50;  5 sec
					KnivMonitorStage = 2;
				}
			}*/
		}
		break;
		
	case 2:
		if( !KnivTimer )
	    {
			SeqOp.L &= ~O15;                        
	    	if( KnivesBank == KB_KNIVES11 )
	    	{
	    		if( Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar) )
	            {
		    		SeqOp.L |= O15;		    	
		    		KnivMonitorStage = 3;		    		
	            }
	    	} 	    	
	    	else if( KnivesBank == KB_KNIVES12 )
	        {	    		
	    		if( Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar) )
	            {
		    		SeqOp.L |= O15;
		    		KnivMonitorStage = 3;	
	            }
	        }	    	
	    	else if( KnivesBank == KB_KNIVES23 )
	    	{
	    		if (Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar))
	    		{
	    			SeqOp.L &= ~O07;
	    		}

	    		if (Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar))
	    		{
	    			SeqOp.L &= ~O10;
	    		}
	    		/* Iss-112 change 
	    		if( (Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar)) 
	    		&& (Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar)) ) */	    
	    		if( (Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar)) 
	    		&& (Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar)) )
	            {
	    			/*SeqOp.L |= O07;
	    			SeqOp.L |= O10;*/
	    			SeqOp.L |= O15;	    		    	
	    			KnivMonitorStage = 3;
	            }
	    	}	    	
	    }
		break;
		
	case 3:
		if( KnivesBank == KB_KNIVES11 )
		{
			if( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				/* DLYU06 should not be running */	
				if( FA[DelPul[DLYU06]] > 250 ) /* during floor topup (O15 ON) when chamber opening, O15 should not be turned off */
				{
					SeqOp.L &= ~(O07 | O15);
					KnivMonitorStage = 0;
					/* if there was 'knife pressure too high' waring then Knife topup still needs to be done */
					/*if( Kniv1PresHigh )
					{
						Kniv1PresHigh = 0;
					}									
					else */
					{
						KnivTopUpDone = 1;	
					}
				}
			}
		}
		else if( KnivesBank == KB_KNIVES12 )
		{
			if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				/* DLYU06 should not be running */	
				if( FA[DelPul[DLYU06]] > 250 ) /* during floor topup (O15 ON) when chamber opening, O15 should not be turned off */
				{
					SeqOp.L &= ~(O10 | O15);
					KnivMonitorStage = 0;	
					/* if there was 'knife pressure too high' waring then Knife topup still needs to be done */
					/*if( Kniv2PresHigh ) 
					{
						Kniv2PresHigh = 0;
					}
					else*/
					{
						KnivTopUpDone = 1;
					}
				}				
			}
		}
		else if( KnivesBank == KB_KNIVES23 ) /* stage 3 */
		{
			if( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				/* DLYU06 should not be running */	
				if( FA[DelPul[DLYU06]] > 250 ) /* during floor topup (O15 ON) when chamber opening, O15 should not be turned off */
				{
					SeqOp.L &= ~O07;
				}
			}
			else
			{
				SeqOp.L |= O07;
			}
			
			if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )
			{
				/* DLYU06 should not be running */	
				if( FA[DelPul[DLYU06]] > 250 ) /* during floor topup (O15 ON) when chamber opening, O15 should not be turned off */
				{
					SeqOp.L &= ~O10;
				}				
			}
			else
			{
				SeqOp.L |= O10;
			}

			if( (SeqOp.L & (O07 | O10)) == 0UL )
			{
				/* DLYU06 should not be running */	
			    if( FA[DelPul[DLYU06]] > 250 ) /* during floor topup (O15 ON) when chamber opening, O15 should not be turned off */
			    {
			    	SeqOp.L &= ~O15;
					KnivMonitorStage = 0;	
					/* if there was 'knife pressure too high' waring then Knife topup still needs to be done */
					/*if( Kniv1PresHigh || Kniv2PresHigh ) 
					{
						Kniv1PresHigh = 0;
						Kniv2PresHigh = 0;
					}
					else */
					{
						KnivTopUpDone = 1;	
					}			
			    }
			}
		}
		break;		
	}
}
