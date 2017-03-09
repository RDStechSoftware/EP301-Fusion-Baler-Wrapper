
#include <inh83.h>
#include <ioh83003.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bytedef.h"

/* ###test */
/*
unsigned long int ltime;
unsigned short int lastcall, maxcall;
*/

/* define x,y offset for main machine pic and animations */
#define OffX 7
#define OffY 69
const unsigned char *CropPickupAnim[] = { CropPickup1_V2, CropPickup2_V2, CropPickup3_V2, CropPickup4_V2 };


void main_loop( void )
{
static unsigned char *sp1, *sp2, *sp3, *sp4, balerstatus, DoorOpen, LubeConfirm;
static unsigned char NetRoll, RearBaleSel, temp_balerstatus;
static unsigned char temp_bit, old_InfoSel, old_out08, BaleTr, BaleTi, CropFeedSel, temp_flash;
static unsigned char NetIconChanged, RefreshBalerDisplay, last_InfoSel, SideDisplay; 
static unsigned char CropPickupAnimIdx = 0;

unsigned char *pt1, *pt2, *pt3, *pt4;
unsigned char c, old_selection, old_kniv1pres, old_kniv2pres, tstring[32], InfoSel, AutoTip;
unsigned char Switch;

/*int a, b, d;
float f1, f2;*/

struct WarningBitmap *pWbm;

if( !startup )
  {
  startup = 1;

  startup_frame();

  if( KnivSystem == RELIEF_VALVE )
    {
    write_bitmap( adm, SIDEDISPLAY,  129, 18, OR );
    /* Filmlayers */
    sprintf ( tstring, "%u", CountSet );
    display_f1_text( tstring, TSMAX, 143, 28, FIXED | CENTER );

    /* Bale Total selection (A/B etc. ) */
    sprintf( tstring, "%1c", 'A' +  BaleTotal);
    display_f1_text( tstring, TSMAX, 147, 51, FIXED );
    }

  LubeConfirm = 0;
  /*SideDisplay = 0;*/
  
  /* display crop type */
  if( !Korean )
	display_f1_text( CropTypeString[CropType]->l[lang], TSMAX, 72, 4, FIXED | CENTER | FRAMED );
  else
    write_bitmap( adm, KCropTypeBitMap[CropType],  53, 4, OR );
  
  SecondPress = 1;

  /* initialise variables on screen startup */
  balerstatus = 0;
  NetRoll = 0;
  RearBaleSel = 0;
  temp_balerstatus = 0;
  temp_bit = AutoMan;
  mainscreen_delay = 0;

  old_selection = 0xff;
  old_kniv1pres = 0xff;
  old_kniv2pres = 0xff;
  
  NetIconChanged = 0xff;
  RefreshBalerDisplay = 0xff;
  last_InfoSel = 0xff;
  
  InfoSel = 0;
  old_InfoSel = 0xff;
  old_out08 = Ip.I.IP08;
  BaleTr = 0;
  BaleTi = 0;
  CropFeedSel = 0;
  temp_flash = 1;
  DoorOpen = 0;
  demi_secs = 0; /*added from rev. 30*/
  }
else
  {
	/* used to delay output 3 when in manual mode so
	that when pressing esc from menus it isn't activated */
  if( !mainscreen_delay )
    {
    if( demi_secs & 0x01 )
      mainscreen_delay = 1;
    }

  temp_flash = (temp_flash)?0:1;
  InfoSel = 0;

  old_selection = selection;
    /*AlarmFlags &= ~ExternAlarm;*/
  }

Switch = 0;

/* for enabling key06 */
if( Op.O.OP02 )
  {
  NetCutPosNorm = 1;
  }
else if(Ip.I.IP09 && (NetCutPosNorm))
  {
  NetCutPosNorm = 0;
  }

/* set if door is opening */
if( Op.O.OP12 )
  {
  DoorOpen = 1;
  }
else if( Op.O.OP11 )
  {
  DoorOpen = 0;
  }

AutoTip = Facts[DelPul[AUTOTP]][0];

TimeDisplay();

if( AutoMan )
{
  if( Ip.I.IP10 && Ip.I.IP04 ) /* remote park and TIPUP closed */
  {
    if( IP10_Delay < 250 )
    {
      IP10_Delay++;

      if(Ip.I.IP01)
      	  IP10_Flag = 1;
      else
    	  IP10_Flag = 2;
    }
  }
  else
  {
    IP10_Delay = 0;
  }

  if( IndexTable > 1 )
  {
    IndexTable--;
  }

  /*if( SafetyCount > SAFETYLEVEL )*/
  if( (SafetyCount > SAFETYLEVEL) || ( (PulseFrequency > IP02Freq) ) )
  {
    Sel = 2;
    ResetSequenceFactors( SEQ_ALL );
  }

}

switch( key )   
  {
  case Key_S1:   /* AUTO */
	if( KnivSystem == RELIEF_VALVE )
	  {
	    if( (selection == 0) && (AutoMan != AM_MANUAL) ) 
	      { /* AUTO */
	      KnivesEnabled = KnivesEnabled? 0:1;
	
	      if( KnivesEnabled && !(KnivesStatus & KS_KNIVESOUT) )
	        {
	        KnivesAutoUp = 1;
	        }
	      else
	        {
	        KnivesAutoUp = 0;
	        }
	
	      if( !KnivesEnabled /*&& (KnivesStatus & KS_KNIVESOUT)*/ )
	        {
	        /*if( !(Tipping || OMS_TIP) && !(Transfering || OMS_TRANS) )*/
	          {
	          FA[DelPul[DLYKS1]] = 0x00; /* set delay for action */
	          /*TimingBit = 1;
	          KnivesStatus = KS_KNIVESSETIN;*/
	          KnivesAutoUp = 0;
	          }
	        }
	      old_selection = 0xff;

		  knifeip6 = 2;
		  knifeip7 = 2;
	      }
	  }
	else if( (KnivSystem == x23_Std) || (KnivSystem == x25_Std))
	  {
	    if( (selection == 0) && (AutoMan != AM_MANUAL) ) 
	      {     
		  if( !KnivesBank )
		    {
			KnivesBank = KB_KNIVES11; 
			InitialKnivDownRoutineDone = 0;	
			KeyS1Delay = 0;
			KnivStage = 0;
			KnivMonitorStage = 0;
			KnivTopUpDone = 0;
		    }
		  else if( KnivesBank & KB_KNIVES11 )
		    {
			KnivesBank = KB_KNIVES00;
			InitialKnivDownRoutineDone = 0;
			KeyS1Delay = 0;
			KnivStage = 0;
			KnivMonitorStage = 0;		
		    }

		  knifeip6 = 2;
		  knifeip7 = 2;

	      old_selection = 0xff;      
	      }		
	  }
	else if( KnivSystem == x23_Select || KnivSystem == x25_Select )
	  {
	    if( (selection == 0) && (AutoMan != AM_MANUAL) ) 
	      {     
		  if( !KnivesBank )
		    {
			  if((knifeip6 != 1) && (knifeip7 != 1))
			  {
					KnivesBank = KB_KNIVES11; /* change to KB_KNIVES11 */
					InitialKnivDownRoutineDone = 0;
					KeyS1Delay = 0;
					KnivTopUpDone = 0;
					KnivStage = 0;
					KnivMonitorStage = 0;
			  }
		    }
		  else if( KnivesBank & KB_KNIVES11 )
		    {
			  if((knifeip6 != 1) && (knifeip7 != 1))
			  {
				KnivesBank = KB_KNIVES12;
				InitialKnivDownRoutineDone = 0;
				KeyS1Delay = 0;
				KnivTopUpDone = 0;
				KnivStage = 0;
				KnivMonitorStage = 0;
			  }
		    }
		  else if( KnivesBank & KB_KNIVES12 )
		    {
			  if((knifeip6 != 1) && (knifeip7 != 1))
			  {
				KnivesBank = KB_KNIVES23;
				KeyS1Delay = 0;
				KnivTopUpDone = 0;
				KnivStage = 0;
				KnivMonitorStage = 0;
			  }
		    }
		  else if( KnivesBank & KB_KNIVES23 )
		    {
			  if((knifeip6 != 1) && (knifeip7 != 1))
			  {
				KnivesBank = KB_KNIVES00;
				InitialKnivDownRoutineDone = 0;
				KeyS1Delay = 0;
				KnivStage = 0;
				KnivMonitorStage = 0;
			  }
		    }
	      old_selection = 0xff;

		  knifeip6 = 2;
		  knifeip7 = 2;
	      }
	  }
    break;

  case Key_S2: 
    /* reset errors, when present */
	  S2_flag = 0; 	/*Iss-131: Used as an escape flag for IP01.*/
      if( ((old_InfoSel==25) || (old_InfoSel==26)) && !CANWarnCanc )    	  
        {
        CANWarnCanc = 1;
        }
      
    if( old_InfoSel && (old_InfoSel != 2) && (old_InfoSel != 8) && (old_InfoSel != 1) )
      {
      if( !AutoMan )
        {
        CountCur = 0;
        }
      
      if( !NetCheck )
        {
        SafetyCount = 0;
        IP01Count = 0; /* ISS-086 */
        PulseFrequency = 0.0;
        oldMachineStatus = 0;
        DispenserPosError = 0;
        DispenserStatus = 0;
      
        TipPosErr = 0;

        if( NetCutPosAlarm & 0x01 )
          { 	 
          NetCutPosAlarm = 0x02;
          }                  	
        MachineStatus &= ~MS_TRANSFER;
        }
      else
        {
        NetWarnCanc |= 0x04;
        }
      
      if( LubeCount <= 0 )
        {
        LubeConfirm = 1;
        }
      }
    else if( old_InfoSel == 8 )
      {
      temp_bit |= 0x10;
      }
    break;
    
  case Key_S3:  
	if( LubeConfirm )
	  {
	  ResetLubeCheck();
	  LubeConfirm = 0;	
	  draw_box( adm, 14, 40, 126, 77, CLEAR );
  	  RefreshBalerDisplay = 0xff;
	  NetIconChanged = 0xff;
	  }
	break;
	
  case Key_S4:  
	  if( KnivSystem == RELIEF_VALVE )
		{
	    if( mainscreen_delay )
	      {
	      if( !AutoMan ) 
	        { /* MANUAL */
	        old_selection = 0xff;
	        }
	      }
		} /*Key 4 modification rev 30*/
	  else if( ((KnivSystem == x23_Std) || (KnivSystem == x25_Std) || (KnivSystem == x23_Select)
			 || (KnivSystem == x25_Select)) && (TAB_FLAG == 0))
	    {	  
	    if( mainscreen_delay )
	      {
	      if( !AutoMan )
	        { /* MANUAL */
	    	SideDisplay = SideDisplay? 0:1;
	    	SecondScreen = SecondScreen? 0:1;
	        old_selection = 0xff;
	        }
		  else
	        {
	    	if( SideDisplay )
	    	  {    	  
	    	  SideDisplay = 0;
	    	  SecondScreen = 0;
	    	  }
	    	else
	    	  {
	    	  SideDisplay = 1; 
	    	  SecondScreen = 1;
	    	  }		
	    	old_selection = 0xff;
	        }
	      }
	    }
  
    if( LubeConfirm ) /* Start beeping again */
      {
      LubeConfirm = 0;
  	  NetIconChanged = 0xff;
  	  RefreshBalerDisplay = 0xff;
      draw_box( adm, 14, 40, 126, 77, CLEAR ); 
      }
    break;

  case Key_F1:
    if( KnivSystem == x23_Select || KnivSystem == x25_Select)
      {	
      if( (Ip.I.IP01 || Ip.I.IP04 || Ip.I.IP08) || AutoMan ) /* safety cutout */
        {
        if( AutoMan )
          {
          AutoMan = 0;
          }
        else
          {
          AutoMan = 1;
          KeyOp.L = 0;
          NetCutPosAlarm = NetCutPosNorm = 0;
          if( !Ip.I.IP04 ) /* TIPUP */
            {
            TipPosErr = 1;
            }
          }
        }
      }
    else /* x23_Std or RELIEF_VALVE or x25_Std*/
      {
      if( Ip.I.IP06 || AutoMan ) /* safety cutout */
        {
        if( AutoMan )
          {
          AutoMan = 0;
          }
        else
          {
          AutoMan = 1;
          KeyOp.L = 0;
          NetCutPosAlarm = NetCutPosNorm = 0;
          if( !Ip.I.IP04 ) /* TIPUP */
            {
            TipPosErr = 1;
            }
          }
        }    	
      }
    
      if( MachineStatus & MS_BALEON )
        LEDSel |= 0x01;

      oldMachineStatus &= ~MS_NETTING;
      MachineStatus &= ~MS_NETTING;
      NetWarnCanc &= ~0x01;
      NetWarnCanc |= 0x02;

      NetCutPosAlarm = 0;
      SafetyCount = 0;
      IP01Count  = 0; /* ISS-086 */
      PulseFrequency = 0.0;
      SavedCountCur = 0;
      DispenserStatus = 0;
      RunOnce = 0;
      if(!TAB_FLAG) /*If kniv warning was entered, then we can listen to inputs 6 and 7*/
      {
    	  AutoKnivFlag = 1;
      }
       
      ResetSequenceFactors( SEQ_ALL );
      if( BeepOff == 0 ) /* cancel continuous beep */
        {
        BeepOff = 25;
        }
      old_selection = 0xff;
      
    break;

  case Key_F2:
    if( !Wrapping && !Tipping && !Transfering )
    {
      if( !(MachineStatus & MS_NETTING) )
        { window = screen02; } /* Operator Menu Display */
    }
    TipPosErr = 0;
    mainscreen_delay = 0;
    break;

  	
  case Key_L4:
  if( AutoMan )
    {
    if( AutoTip )
      {
      if( (RearBaleStatus & 0x01) || (RearBaleStatus & 0x02) )
        {
          /* ignore pause tip if already tipping */
        if( !(MachineStatus & MS_TIPPING) )
          {
          PauseTip = 1;
          AutoTip = 0;
          }
        }
      }
    }
    break;
    
  default:
	if( !key )
	  {
      if( CANWarnCanc == 1 )
        {
  	    CANWarnCanc = 2;
        }      
	  }
    break;
  }

switch( swrel )
  {
  case 6:
	/*SecondPress = 1;*/ /*Set speed to slow after 3 seconds */
	  SpeedChanged = 2;
    break;
  case 0:
    old_selection = 0xff;
    break;
  }

if( (Wrapping && !Ip.I.IP04) && !(MachineStatus & MS_TRANSFER)) /* TIPUP */
  {
  ResetSequenceFactors( SEQ_WRAP );
  TipPosErr = 1;
  }
else if( Ip.I.IP04 ) /* TIPUP */
  {
  TipPosErr = 0;
  }

if( selection && (Sel == 2) && (demi_secs > 4) )
  {
  selection = 0;
  demi_secs = 0;
  }

if( RearBaleStatus & 0x04 )
{ /* bale transfer has begun */
  if( Ip.I.IP08 )
  { 
	  if( CropType )
	      { /* if crop type, then bale is ready for tipping */
	        RearBaleStatus |= 0x10;
	      }
    /* door closed */
    RearBaleStatus &= ~0x04;
    RearBaleStatus |= 0x01;
    RaiseDoor = 0;
  }
}

if( (RearBaleStatus & 0x01) && (!CropType) ) /*Silage*/
{ /* bale being wrapped */
  if(Op.O.OP05 && Op.O.OP13)
  { /* cut and hold started */
    RearBaleStatus |= 0x08;
  }

  if(RearBaleStatus & 0x08)
  {
    if(!Op.O.OP05 && !Op.O.OP13)
    { /* bale wrap complete */
      RearBaleStatus &= 0x20;
      RearBaleStatus |= 0x02;
      RearBaleStatus |= 0x10;
    }
  }
}

if((!Ip.I.IP04) && (!Ip.I.IP08) && (!AutoMan) && !(MachineStatus & MS_TRANSFER) )
{ /* Door opened and bale tipped */
  balerstatus = 7;
  RearBaleStatus &= 0x02;
}
else if((!Ip.I.IP04) && (DoorOpen) && (AutoMan) && !(MachineStatus & MS_TRANSFER))
{ /* Door opened and bale tipped */
  balerstatus = 7;
  RearBaleStatus &= 0x02;
}
else if((!Ip.I.IP04) && !(MachineStatus & MS_TRANSFER))
{ /* Bale Tipped */
  balerstatus = 5;
  RearBaleStatus &= 0x02;
}
else if((DoorOpen) && (RearBaleStatus & 0x10) && (AutoMan)) /*OP12 also turns on*/
{ /* Door open and rear bale present */
  balerstatus = 6;
}
else if((!Ip.I.IP08) && (RearBaleStatus & 0x10) && (!AutoMan))
{ /* Door open and rear bale present */
  balerstatus = 6;
}
else if( ( (!Ip.I.IP08) && (!AutoMan) ) || ( (DoorOpen) && (AutoMan) ) || (RearBaleStatus & 0x04) )
{
  if( Ip.I.IP05 || (RearBaleStatus & 0x04) )
    { /* bale being transfered */
    balerstatus = 2;
    RearBaleStatus &= 0x20;
    RearBaleStatus |= 0x04;
    PauseTip = 0;
    
    /* mid transfer pause */
    if( !RaiseDoor && (Facts[DelPul[DIVDEL]][0] == SL_MANUAL) )
      {	
      RaiseDoor = 0x01;
      }
    }
  else
    { /* Door opened */
  	if( balerstatus != 1 )
  	  {
  	  NetCutPosAlarm = 0;
  	  }
  	  
    balerstatus = 1;
    }
}
else if( RearBaleStatus & 0x02 )
{ /* rear bale wrapped */
  balerstatus = 4;
}
else if( RearBaleStatus & 0x01 )
{ /* rear bale unwrapped */
  balerstatus = 3;
  NetWarnCanc &= ~0x02;
}
else
{ /* no rear bale door closed */
  balerstatus = 0;
  RearBaleStatus &= 0x20;
}

if( ((key & ~KeyMask) == Key_R1) && AutoMan && StartDelayComplete() )
  { /* Rebale pressed */
  balerstatus = 3;	
  RearBaleStatus |= 0x01;
  demi_secs = 0;
  StartWrapSequence( SWS_WRAP);
  }

/* if bale status changes, update display */
if( temp_balerstatus != balerstatus )
  {
  if( balerstatus == 3 )
    {
    RearBaleStatus &= 0x01;
    }
  
  if( (temp_balerstatus == 5) || (temp_balerstatus == 7) )
    {
    RearBaleStatus &= ~0x02;
    balerstatus = 0;
    }
  
  temp_balerstatus = balerstatus;
  old_selection = 0xff;
  }

/* if AutoMan changes, update display */
if( !(temp_bit & AutoMan) )
  { 
  temp_bit &= 0xf0;
  temp_bit |= AutoMan;
  
  /* delete crop feed pic */
  draw_box( adm, OffX-3, OffY+21, OffX-3+28, OffY+21+6, CLEAR );

  /* redraw the crop pickup */
  draw_box( adm, OffX+26, OffY+15, OffX+26+13, OffY+15+13, CLEAR );
  write_bitmap( adm, FusionP02_v2, OffX+23, OffY-24, OR );
  
  
  old_selection = 0xff;
  }

if( Kniv1Pres != old_kniv1pres )
  {
  old_kniv1pres = Kniv1Pres;  
  old_selection = 0xff; 	  
  }

if( Kniv2Pres != old_kniv2pres )
  {
  old_kniv2pres = Kniv2Pres;
  old_selection = 0xff; 	
  }
/* disable netting status */
if( Ip.I.IP09 )
  {
  if( NetWarnCanc & 0x01 )
    {
    MachineStatus &= ~MS_NETTING;
    }  
  NetWarnCanc &= ~0x01;
  NetWarnCanc |= 0x02;
  
/*  if(NetCheck)
    NetWarnCanc |= 0x04;*/
  }

/* If netting starts cancel oldMachineStatus */
if( oldMachineStatus & MS_NETTING )
  {
  oldMachineStatus &= ~MS_NETTING;
  MachineStatus &= ~MS_NETTING;
  NetWarnCanc &= ~0x01;
  NetWarnCanc |= 0x02;
  }

/* Cancel net alarm when tipping */
if( !Ip.I.IP04 )
  {
  NetCutPosAlarm &= ~0x02;
  }

/* update display if IP08 changes */
if( old_out08 != Ip.I.IP08 )
  {
  old_out08 = Ip.I.IP08;

  /* update display */
  old_selection = 0xff;
  }

if( BaleTr )
  {
  old_selection = 0xff;
  }

if( (BaleTi) && (BaleTi != 6) )
  {
  old_selection = 0xff;
  }

if( AutoMan )
  {
  if( oldMachineStatus & MS_WRAPPING )
    { /* wrap not complete */
    balerstatus = 3;
    if( !temp_flash )
      {
      Switch = 2;
      }

    old_selection = 0xff;
    }
  else if( DispenserPosError )
    {
    Switch = 3;
    }
  else if( (( TipCheck && !Wrapping ) && !PauseTip ) || ( oldMachineStatus & MS_BALEON ) )
    { /* Tip bale? */
    if( !temp_flash )
      {
      balerstatus = 0;
      }
    
    old_selection = 0xff;
    }
  else if( (TipPosErr && !PauseTip) || (oldMachineStatus & MS_TIPPING) )
    { /* Tip Postion && Tip not complete */
    if( !temp_flash )
      {    	
      balerstatus = 0;
      }
    BaleTi = 2;

    if( TipPosErr && !PauseTip )
      {
      Switch = 1;
      }
    
    old_selection = 0xff;
    }
  else if( oldMachineStatus & MS_TRANSFER )
    { /* Transfer not complete */
    balerstatus = 2;
    BaleTr = 0;
    if( !temp_flash )
      {    	
      Switch = 1;
      }
    
    old_selection = 0xff;
    }

  if( Ip.I.IP08 && (MachineStatus & MS_CHAMBEROPEN) )
	{
	TransferBale = 1;
    ResetSequenceFactors( SEQ_NET );
    }
  
  }
else if( DispenserPosError )
  { /* Display Dispensor postion error even in Man mode */
  Switch = 3;
  }

if( balerstatus == 2 )
  { /* clear Net alarm */
  NetCutPosAlarm = 0;
  }

/* ISS-090 */
if( PulseFrequency > IP02Freq )
  {
  if( OverspeedDelay < 250 )
    {
	OverspeedDelay++;
    }
  }
else
  {
  OverspeedDelay = 0;	
  }

AlarmFlags &= ~NoteAltMask;
/* Set warning if present */
if( (MachineStatus & MS_CHAMBERFULL) && !(NetCutPosAlarm & 0x02) )
  { /* baler full */
  }
else if( SupplyVolts < 105 )
  { /* LOW VOLTAGE */
  InfoSel = 15;
  old_InfoSel = 0xff;
  }
else if( ((KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std)) && (Kniv1Pres > KnifePresWarnBar)
		 && !KnivMonitorStage && !UnBlockStatus ) /* Iss-108 */
  {
  /* Warnirng disabled in Zone51 which happens only for 
     the first bale after Kniv23 has been selected */
  /*if( !KnivPresHigh )
    {
    KnivPresHigh = 1;
    Ip.I.HPRES = 1;
    }*/ /*rev. 30*/
	if(KnivesBank == KB_KNIVES12)
	{

	}
	else
	{
	  InfoSel = 23;
	  old_InfoSel = 0xff;
	  AlarmFlags &= ~NoteMask;
	  SetBeepType( BT7 | BP2, TBINT, 1 ); /* 100/200ms On/Off, Int, 1 Count */
	}
  }
#if 0
else if( ((KnivSystem == x23_Select) || (KnivSystem == x25_Select)) && (CanStatus == CSTATUS_NOCHIP2) && !CANWarnCanc )
  {	 
  InfoSel = 26;
  old_InfoSel = 0xff;
  SetBeepType( BT1 | BP2, TBINT, 1 ); /* 100/200ms On/Off, Int, 1 Count */		
  }
else if( ((KnivSystem == x23_Select) || (KnivSystem == x25_Select)) && ((CanInitCount - Old_CanInitCount) > 2) && !CANWarnCanc )
  {
  InfoSel = 25;
  old_InfoSel = 0xff;
  SetBeepType( BT1 | BP2, TBINT, 1 ); /* 100/200ms On/Off, Int, 1 Count */	
  }
#endif
else if( ((KnivSystem == x23_Select) || (KnivSystem == x25_Select)) && (Kniv2Pres > KnifePresWarnBar) /*rev. 30*/
		 && !KnivMonitorStage && !UnBlockStatus ) /* Iss-108 */
  {
	if(KnivesBank == KB_KNIVES11)
	{

	}
	else
	{
		InfoSel = 24;
		old_InfoSel = 0xff;
		AlarmFlags &= ~NoteMask;
		SetBeepType( BT7 | BP2, TBINT, 1 ); /* 100/200ms On/Off, Int, 1 Count */
	}
  }
else if( IndexTable ) /*Beep set when S3 is pressed*/
  { /* ' INDEXING ' */
  InfoSel = 10;
  old_InfoSel = 0xff;

  AlarmFlags |= NoteAlt;
  AlarmFlags &= ~NoteMask;
  SetBeepType( BT6 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
  }
else if( DispenserPosError )
  { /* 'DISPENSER POSITION?' */
  InfoSel = 17;
  old_InfoSel = 0xff;

  AlarmFlags |= NoteAlt;
  AlarmFlags &= ~NoteMask;
  SetBeepType( BT6 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
  }
else if( (SafetyCount > SAFETYLEVEL) && (IP01Count > SAFETYLEVEL) ) /* no pulses on IP02 or IP01 */
  { /* ' SAFETY SWITCH? ' */
  InfoSel = 12;
  old_InfoSel = 0xff;

  AlarmFlags |= NoteAltFour;
  AlarmFlags &= ~NoteMask;
  SetBeepType( BT5 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
  }
else if( (SafetyCount > SAFETYLEVEL) && (IP01Count < SAFETYLEVEL) ) /* no pulses on IP02 but pulses on IP01 */
  { /* ' MOTOR SPEED SENSOR? ' */
  InfoSel = 21;
  old_InfoSel = 0xff;

  AlarmFlags |= NoteAltFour;
  AlarmFlags &= ~NoteMask;
  SetBeepType( BT5 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
  }
else if( (PulseFrequency > IP02Freq) && (OverspeedDelay > 6 ) ) /* ' Wrapper Too Fast' Wiat 2s before warn */
  {   
  InfoSel = 22;
  old_InfoSel = 0xff;

  AlarmFlags |= NoteAltFour;
  AlarmFlags &= ~NoteMask;
  SetBeepType( BT5 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
  }
else if( LubeCount <= 0 )
  { /* ' CHECK LUBE ' */
  InfoSel = 14;
  old_InfoSel = 0xff;

  /*if( !LubeConfirm )*/
    {
    SetBeepType( BT5 | BP2, TBEXT, 1 ); /* 100/400ms On/Off, nt, 1 Count */
    } 
  }
else if( AutoMan && (oldMachineStatus & ~MS_NETTING) )
  {
  if( oldMachineStatus & MS_TIPPING )
    { /* 'TIP NOT COMPLETE ' */
    InfoSel = 18;
    }
  else if( oldMachineStatus & MS_WRAPPING )
    { /* 'WRAP NOT COMPLETE' */
    InfoSel = 5;
    }
  else if( oldMachineStatus & MS_TRANSFER )
    { /* ' TRANSFER NOT COMPLETE ' */
    InfoSel = 16;
    }
  else if( oldMachineStatus & MS_BALEON )
    { /* 'TIP BALE?'*/
    InfoSel = 4;
    }
  else
    {
    InfoSel = 0;
    }

  if( InfoSel )
    {
    old_InfoSel = 0xff;

    AlarmFlags |= NoteAltThree;
    AlarmFlags &= ~NoteMask;
    SetBeepType( BT7 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
    }
  }
else if( UnBlockStatus  )
  {
  if( (UnBlockStatus == 4) || (UnBlockStatus == 3) )
    { /* 'RESET'*/
    InfoSel = 7;
    old_InfoSel = 0xff;
    }
  else
    { /* 'UNBLOCK' */
    InfoSel = 6;
    old_InfoSel = 0xff;
    }

  SetBeepType( BT4 | BP2, TBEXT, 1 ); /* 100/200ms On/Off, Int, 1 Count */
  AlarmFlags &= ~NoteMask;
  AlarmFlags |= NoteTwo;
  }
else if( NetCheck && !(NetWarnCanc & 0x04) )
  { /* ' NET ERROR ' */
  InfoSel = 11;
  old_InfoSel = 0xff;

  SetBeepType( BT5 | BP2, TBEXT, 1 );
  NetWarnCanc |= 0x01;
  AlarmFlags &= ~NoteMask;
  }
else if( ((balerstatus == 3) && !CropType) && (DispenserStatus == 1) ) /*Silage*/
  { /* '1 Dispenser Only' */
  InfoSel = 8;
  old_InfoSel = 0xff;

  if( !(temp_bit & 0x10) )
    {
    AlarmFlags |= NoteAltTwo;
    AlarmFlags &= ~NoteMask;
    SetBeepType( BT6 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
    }
  }
else if( DispenserStatus == 2 )
  { /* '  Out Of Film   ' */
  InfoSel = 9;
  old_InfoSel = 0xff;

  AlarmFlags |= NoteAltThree;
  AlarmFlags &= ~NoteMask;
  SetBeepType( BT6 | BP2, TBEXT, 1 ); /* 100/300ms On/Off, Int/Ext, 1 Count */
  }
else if( Speed > ALARMSPEED )
  { /* ' SPEED TOO FAST! ' */
  InfoSel = 3;
  old_InfoSel = 0xff;

  SetBeepType( BT1 | BP2, TBINT, 1 ); /* 100/200ms On/Off, Int, 1 Count */
  }
else if( TipCheck && !Wrapping && !PauseTip )
  { /* 'TIP BALE?' */
  InfoSel = 4;
   old_InfoSel = 0xff;

  AlarmFlags &= ~NoteMask;
  AlarmFlags |= NoteThree;
  SetBeepType( BT5 | BP2, TBEXT, 1 ); /* 20/20ms On/Off, Int, 1 Count */
  }
else if( NetCutPosAlarm & 0x01 )
  { /* Net Cut Alarm Postion */
  InfoSel = 19;
  old_InfoSel = 0xff;

  SetBeepType( BT5 | BP2, TBEXT, 1 );
  NetWarnCanc |= 0x01;
  AlarmFlags &= ~NoteMask;
  }
else if( TipPosErr && !PauseTip )
  { /* ' TIP POSITION!' */
  InfoSel = 13;
  old_InfoSel = 0xff;

  AlarmFlags &= ~NoteMask;
  AlarmFlags |= NoteThree;

  SetBeepType( BT5 | BP2, TBEXT, 1 ); /* 20/20ms On/Off, Int, 1 Count */
  }
else if( (MachineStatus & MS_NETTING) || (!AutoMan && Op.O.OP02) )
  { /* ' Netting' */
  InfoSel = 1;
  }
else if( ((balerstatus == 3) && !CropType) || (Wrapping && (RearBaleStatus & 0x10)) ) /*Silage*/
  { /* 'Wrapping' */
  InfoSel = 2;
  old_InfoSel = 0xff;
  }
else
  {
  AlarmFlags &= ~NoteMask;
  LubeConfirm = 0;
  }

if( NoPWM && !InfoSel ) /* No PWM set */
  {
  InfoSel = 20;
  }

/* Update display if Errors status, or wrapping */
/*if( old_InfoSel )
  {
  old_selection = 0xff;
  }*/

if( last_InfoSel != InfoSel )
  {
  last_InfoSel = InfoSel;
  
  pWbm = &Wbm[InfoSel];
  if( (pWbm->BitMap != NULL) || (pWbm->x == 0xff) )
    {
    }
  else
    {
    RefreshBalerDisplay = 0xff;
    }
  }

if( RefreshBalerDisplay )
  {
  RefreshBalerDisplay = 0;

  /* clear InfoSel warning box */
  draw_box( adm, 35, 43, 115, 92, CLEAR );

  write_bitmap( adm, FusionP01, OffX+0, OffY+0, OR );
  write_bitmap( adm, FusionP02_v2, OffX+23, OffY-24, OR );
  write_bitmap( adm, FusionP04, OffX+64, OffY+19, OR );

  old_selection = 0xff;
  }

if( selection != old_selection )
  {
  /* ###test */
  /*SCI1_SCR = 0x00;
  P9DR |= 0x02;*/

  sp1 = sp2 = sp3 = sp4 = NULL;

  /* display operational mode (man/semi/auto) */
  draw_box( adm, 113, 4, 113+42, 4+9, CLEAR );
  write_bitmap( adm, AutoMan ? MODEAUTO : MODEMAN, 113, 4, OR );

  /* clear RPM display space */
  draw_box( adm, 92, 20, 92+17, 20+16, CLEAR );
  
  draw_box( adm, OffX+85, OffY-25, OffX+85+29, OffY-25+6, CLEAR );      /* clear arrows */
  draw_box(adm, OffX+42, OffY-44, OffX+42+45-1, OffY-44+52-1, CLEAR);   /* clear netting chamber */
  draw_box(adm, OffX+87, OffY-20, OffX+87+25-1, OffY-20+28-1, CLEAR);   /* clear bale table */
  draw_box(adm, OffX+89, OffY-11, OffX+89+30-1, OffY-11+29-1, CLEAR);   /* clear part tipped bale */
  draw_box( adm, OffX+90, OffY+3, OffX+90+29, OffY+3+28, CLEAR );       /* clear fully tipped bale */
 
  write_bitmap( adm, FusionP03_v2, OffX+42, OffY+3, OR );
  write_bitmap( adm, FusionP05, OffX+110, OffY-23, OR );
  write_bitmap( adm, FusionP06, OffX+87, OffY-28, OR );
  display_f1_text( AutoTip? "A":" ", TSMAX, OffX+98, OffY+17, FIXED );

  switch( balerstatus )
    {
    case 0: /* Door closed, No rear bale */
      if( AutoMan && (!Ip.I.IP08 || (RearBaleStatus & 0x20)) )
        {
        RearBaleStatus |= 0x20;
        write_bitmap( adm, BALENORMAL2_v2, OffX+42, OffY-28, OR );
        }
      else
        {
        write_bitmap( adm, BALENORMAL_V2, OffX+42, OffY-28, OR );
        }
      AutoTip_Sel = 0;
      break;

    case 1: /* Door Open */
      write_bitmap( adm, AutoMan ? BALETRANSFER1_V2 : BALETRANSFER4_V2, OffX+42, OffY-44, OR );
      AutoTip_Sel = 0;
      break;

    case 2: /* Bale being transfered */
      switch( BaleTr )
        {
        case 0:
        case 1:
          write_bitmap( adm, (AutoMan && !Switch) ? BALETRANSFER2_V2 : BALETRANSFER3_V2, OffX+42, OffY-44, OR );
          break;

        case 2:
        case 3:
          write_bitmap( adm, BALETRANSFER3_V2, OffX+42, OffY-44, OR );
          if( AutoMan )
            {
            draw_box( adm, OffX+87, OffY-20, OffX+87+23, OffY-20+27, CLEAR );
            write_bitmap( adm, REARBALE, OffX+87, OffY-20, OR );
            }
          break;

        case 4:
          if( AutoMan || !Ip.I.IP05 )
            {
            write_bitmap( adm, BALETRANSFER4_V2, OffX+42, OffY-44, OR );
            }
          else
            {
            write_bitmap( adm, BALETRANSFER3_V2, OffX+42, OffY-44, OR );
            }

          if( AutoMan )
            {
            draw_box( adm, OffX+87, OffY-20, OffX+87+23, OffY-20+27, CLEAR );
            write_bitmap( adm, REARBALE, OffX+87, OffY-20, OR );
            }
          break;
        }
      
      if( BaleTr < 4 )
        {    	  
        BaleTr++;
        }
      AutoTip_Sel = 0;
      break;

    case 3: /* Rear bale present, door closed */
      if( AutoMan && (!Ip.I.IP08 || (RearBaleStatus & 0x20)) )
        {
        RearBaleStatus |= 0x20;
        write_bitmap( adm, BALENORMAL2_v2, OffX+42, OffY-28, OR );
        }
      else
        {  
        write_bitmap( adm, BALENORMAL_V2, OffX+42, OffY-28, OR );
        }

      if( AutoMan )
        {
        draw_box( adm, OffX+87, OffY-20, OffX+87+23, OffY-20+27, CLEAR );
        write_bitmap( adm, REARBALE, OffX+87, OffY-20, OR );
        }
      break;

    case 4: /* Rear bale wrapped, door closed */ 
      if( AutoMan && (!Ip.I.IP08 || (RearBaleStatus & 0x20)) )
        {
        RearBaleStatus |= 0x20;
        write_bitmap( adm, BALENORMAL2_v2, OffX+42, OffY-28, OR );
        }
      else
        {  
        write_bitmap( adm, BALENORMAL_V2, OffX+42, OffY-28, OR );
        }

      if( AutoMan )
        {
        write_bitmap( adm, BALEWRAPPED, OffX+87, OffY-20, OR );
        }
      temp_bit &= ~0x10;
      break;

    case 5: /* bale tipped, door closed */
      if( AutoMan && (!Ip.I.IP08 || (RearBaleStatus & 0x20)) )
        {
        RearBaleStatus |= 0x20;
        write_bitmap( adm, BALENORMAL2_v2, OffX+42, OffY-28, OR );
        }
      else
        {
        write_bitmap( adm, BALENORMAL_V2, OffX+42, OffY-28, OR );
        }

      if( AutoMan && !Switch )
        {
        switch( BaleTi )
          {
          case 0:
          case 1:
          case 2:
          case 3:
          case 4:
            draw_box( adm, OffX+89, OffY-11, OffX+89+29, OffY-11+28, CLEAR );
            write_bitmap( adm, (RearBaleStatus & 0x02) ? WRAPPEDTIP1_V2 : UNWRAPPEDTIP1_V2, OffX+89, OffY-11, OR );
            break;

          case 5:
            draw_box( adm, OffX+90, OffY+3, OffX+90+29, OffY+3+28, CLEAR );
            write_bitmap( adm, (RearBaleStatus & 0x02) ? WRAPPEDTIP2  :UNWRAPPEDTIP2, OffX+90, OffY+3, OR );
            break;
          }
        }
      else
        {
        draw_box( adm, OffX+90, OffY+3, OffX+90+19, OffY+3+4, CLEAR );
        draw_box( adm, OffX+90, OffY+3, OffX+90+15, OffY+3+14, CLEAR );
        write_bitmap( adm, TIP_V2, OffX+90, OffY+3, OR );
        }

      if( BaleTi < 5 )
        {
        BaleTi++;
        }
      RearBaleStatus &= ~0x20;
      break;

    case 6: /* Rear bale present, door open */
      write_bitmap( adm, AutoMan ? BALETRANSFER1_V2 : BALETRANSFER4_V2, OffX+42, OffY-44, OR );

      if( AutoMan )
        {
        draw_box( adm, OffX+87, OffY-20, OffX+87+23, OffY-20+27, CLEAR );
        write_bitmap( adm, (!CropType) ? BALEWRAPPED : REARBALE, OffX+87, OffY-20, OR );
        }
      break;

    case 7: /* Bale tipped, Door present */
      write_bitmap( adm, AutoMan ? BALETRANSFER1_V2 : BALETRANSFER4_V2, OffX+42, OffY-44, OR );

      if( AutoMan && !Switch )
        {
        switch( BaleTi )
          {
          case 0:
          case 1:
          case 2:
          case 3:
          case 4:
            draw_box( adm, OffX+89, OffY-11, OffX+89+29, OffY-11+28, CLEAR );
            write_bitmap( adm, (RearBaleStatus & 0x02) ? WRAPPEDTIP1_V2 : UNWRAPPEDTIP1_V2, OffX+89, OffY-11, OR );
            break;

          case 5:
            draw_box( adm, OffX+90, OffY+3, OffX+90+29, OffY+3+28, CLEAR );
            write_bitmap( adm, (RearBaleStatus & 0x02) ? WRAPPEDTIP2 : UNWRAPPEDTIP2, OffX+90, OffY+3, OR );
            break;
          }
        }
      else
        {
        draw_box( adm, OffX+90, OffY+3, OffX+90+19, OffY+3+4, CLEAR );
        draw_box( adm, OffX+90, OffY+3, OffX+90+15, OffY+3+14, CLEAR );
        write_bitmap( adm, TIP_V2, OffX+90, OffY+3, OR );
        }

      if( BaleTi < 5 )
        {
        BaleTi++;
        }

      RearBaleStatus &= ~0x20;
      break;
    }

  if( balerstatus != 2 )
    {
    BaleTr = 0;
    }

  if( (balerstatus != 5) && (balerstatus != 7) )
    {
    BaleTi = 0;
    }
  /* side display */
  
#if 0  
  if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
    {
    /* Iss-109 change 
    write_bitmap( adm, SideDisplay? SIDE_DISPLAY2:SIDE_DISPLAY1, 129, 18, OR );*/
    }
  else
    {
	write_bitmap( adm, SideDisplay? SideDisplay2 : Side_display1, 129, 18, OR );
	/* display knife outline/filled */
	if( SideDisplay )
	  write_bitmap( adm, Ip.I.IP07? KNIFE_FILLED:KNIFE_OUTLINE, 137, 49, OR );
    } 
#endif  
  if( KnivSystem == RELIEF_VALVE )
    {
    /* Bale amount */
    sprintf ( tstring, "%3lu", TotalBales[BaleTotal] );
    display_f1_text( tstring, TSMAX, 135, 64, FIXED );

    /* voltage */
    sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
    display_f1_text( tstring, TSMAX, 133, 93, FIXED );
    }
  else /*All other KnivSystem available*/
    {
	draw_box( adm, 129, 18, 156, 102, CLEAR );

	if( (KnivSystem == x23_Std) || (KnivSystem == x25_Std))
	  {
	  write_bitmap( adm, SideDisplay? SideDisplay2 : Side_display1, 129, 18, OR );
	  }
	else if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
	  {
	  write_bitmap( adm, SideDisplay? SideDisplay2: Side_display1, 129, 18, OR );
	  }

	input_count++;

	if((KnivSystem == x23_Std) || (KnivSystem == x25_Std) /*&& (AutoMan != AM_MANUAL)*/ ) /*IP7 screen warning for x23 Std and x25 Std*/
	  {
		  knife_pos_input_7(); /*Only check and act on the state of input 7*/

		  RefreshBalerDisplay = 0xff;

		  if(Op.O.OP16)
		  {
			  input_count = 0; /*reset count*/
			  TAB_FLAG = 0;	 /*Display tabs of Main Screen*/
			  flag =1;
		  }
	  }
	  else if( ((KnivSystem == x23_Select) || (KnivSystem == x25_Select))/* && (AutoMan != AM_MANUAL)*/)
	  {
		  knife_pos_input_6(); /*Check and act on the state of input 6*/
		  knife_pos_input_7(); /*Check and act on the state of input 7*/

		  RefreshBalerDisplay = 0xff;

		  if(Op.O.OP16)
		  {
			  input_count = 0; /*reset count*/
			  TAB_FLAG = 0;	 /*Display tabs of Main Screen*/
			  flag =1;
		  }
	  }

    if( !SideDisplay )
      {
      /* Filmlayers */
      sprintf ( tstring, "%u", CountSet );
      display_f1_text( tstring, TSMAX, 142, 27, FIXED | CENTER );

      /* Bale Total selection (A/B etc. ) */
      sprintf( tstring, "%1c", 'A' +  BaleTotal);
      display_f1_text( tstring, TSMAX, 148, 50, FIXED );

      /* Bale amount */
      sprintf ( tstring, "%3lu", TotalBales[BaleTotal] );
      display_f1_text( tstring, TSMAX, 135, 63, FIXED );
      }
    else
      {
      		  /* voltage */
		sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
		display_f1_text( tstring, TSMAX, 132, 34, FIXED );

		/*rev. 30*/
    	 if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select) )
    	  {
			sprintf( tstring, "%3u", Kniv1Pres );	/* Knives 1 pressure on AnIP5 */
			display_f1_text( tstring, TSMAX, 134, 63, FIXED );

			sprintf( tstring, "%3u", Kniv2Pres ); 	/* Knives 2 pressure on AnIP4 */
			display_f1_text( tstring, TSMAX, 134, 93, FIXED );
    	  }
    	  else /*if x23_std or x25_std*/
    	  {
    		  Kniv2Pres = 0;
    		  sprintf( tstring, "%3u", Kniv1Pres ); 	/* Knives 1 pressure on AnIP5 */
    		  display_f1_text( tstring, TSMAX, 134, 63, FIXED );
    	  }

    	  if( (KnivSystem == x23_Std) || (KnivSystem == x25_Std))
		  {
			/* display knife outline/filled IP07*/
			write_bitmap( adm, Ip.I.IP07? KNIFE_FILLED:KNIFE_OUTLINE, 137, 49, OR );
    	  }
    	  else if ( (KnivSystem == x23_Select) || (KnivSystem == x25_Select) ) /*x23_select and x25_select*/
    	  {
    		  /* display knife outline/filled IP07*/
    		  write_bitmap( adm, Ip.I.IP07? KNIFE_FILLED:KNIFE_OUTLINE, 137, 49, OR );
    		  /* display knife outline/filled IP06*/
    		  write_bitmap( adm, Ip.I.IP06? KNIFE_FILLED:KNIFE_OUTLINE, 138, 80, OR );
    	  }

      }
    }
  
  /*P9DR &= ~0x02;*/

  } /* selection != old_selection */

/* Rotate net icon if netting */
if( !NetCheck &&
	(AutoMan && ((MachineStatus & MS_NETTING) && !(NetWarnCanc & 0x01)) ||
    (!AutoMan && Op.O.OP02) ||
    (AutoMan && (MachineStatus & MS_NETTING) && (NetWarnCanc & 0x01) && (Op.O.OP02))) )
  {
  if( NetRoll < 7 )
    {
    NetRoll++;
    }
  else
    {  
    NetRoll = 0;
    }
  NetIconChanged = 0xff;
  }

if( NetIconChanged )
  {
  NetIconChanged = 0x00;

  /* draw netting icon */
  draw_box( adm, 10, 43, 10 + 16, 43 + 16, CLEAR );
  write_bitmap( adm, ROLLER[NetRoll], 10, 43, OR );
  }

/* Draw the crop input on display, deleted when automan is changed to man */
if( AutoMan )
  {
  draw_box( adm, OffX-3, OffY+21, OffX-3+28, OffY+21+6, CLEAR );
  write_bitmap( adm, CROPFEED[CropFeedSel], OffX-3, OffY+21, OR );

  /* draw the crop pickup animation */
  draw_box( adm, OffX+26, OffY+15, OffX+26+13, OffY+15+13, CLEAR );
  write_bitmap( adm, CropPickupAnim[CropPickupAnimIdx], OffX+26, OffY+15, OR );

  /* move on to next crop pickup animation */
  CropPickupAnimIdx++;
  if (CropPickupAnimIdx >= (sizeof (CropPickupAnim) / sizeof(unsigned char*)) )
  {
  	CropPickupAnimIdx = 0;
  }


  if( Ip.I.IP08 )
    {
    CropFeedSel++;
    if( CropFeedSel > 11 )
      {
      CropFeedSel = 0;
      }
    }
  }

/* Wrapping RPM */
if( durationA0 )
  {
  rpm = (unsigned short int)(((float)countA0 * (60.0 * 2e6 / 2.0) / (float)durationA0) + 0.5);
  }

#if 0
if( RpmCountBit && ITU_GRB3 && !IndexTable ) /* moving */
  {
  CalculateFreq();
  }
#endif

/* Iss-094 */
if( MonitorFrequency && ITU_GRB3 && !IndexTable ) /* moving */
  {
  CalculateFreq();
  } 

/* Wrapping */
if( ((balerstatus == 3) && !CropType) || (Wrapping && (RearBaleStatus & 0x10)) ) /*Silage*/
  {
  DispenserCountBit = 1;
  
  sprintf ( tstring, "%2u", rpm  );
  display_f1_text( tstring, TS20, 95, 20, FIXED );
  
  display_f1_text( "RPM", TS20, 92, 30, FIXED );
  }

/*DEBUGGING#################################*/
/*	sprintf ( tstring, "%u,%u,%u,%u,%u,%u", Flag, Ip.I.IP10, IP01, Wrapping, AutoTip, TableOccupied );
	display_f1_text( tstring, TS20, 40, 20, FIXED );

	sprintf(tstring, "%u,%u", SA[SwLook[RSWTCF]], SavedCountCur);
	display_f1_text( tstring, TS20, 40, 27, FIXED );*/
/*DEBUGGING#################################*/

/* dispenser rotate display */
if( !CropType && !Switch && (balerstatus == 3) ) /*Silage*/
  {
  /* Wrapping box moves vertically on rear bale and shows roller direction */
  if( (Op.O.OP03 && AutoMan) || (!AutoMan && ((key & ~KeyMask) == Key_S4)) )
    {
    /* if Man then need to draw bale */
    if( !AutoMan )
      {
      draw_box( adm, OffX+87, OffY-20, OffX+87+23, OffY-20+27, CLEAR );
      write_bitmap( adm, REARBALE, OffX+87, OffY-20, OR );
      }

    draw_box( adm, OffX+95, OffY-19, OffX+95+9, OffY-19+23, CLEAR );
    write_bitmap( adm, BALERREAR[RearBaleSel], OffX+95, OffY-19, OR );

    /* select roller direction */
    if( RearBaleSel < 10 )
      {
      RearBaleSel++;
      }
    else
      {
      RearBaleSel = 0;
      }
    }
  else if( (Op.O.OP04 && AutoMan) || (!AutoMan && ((key & ~KeyMask) == Key_S3)) )
    {
    /* if Man then need to draw bale */
    if( !AutoMan )
      {
      draw_box( adm, OffX+87, OffY-20, OffX+87+23, OffY-20+27, CLEAR );
      write_bitmap( adm, REARBALE, OffX+87, OffY-20, OR );
      }

    draw_box( adm, OffX+95, OffY-19, OffX+95+9, OffY-19+23, CLEAR );
    write_bitmap( adm, BALERREAR[RearBaleSel], OffX+95, OffY-19, OR );

    /* select roller direction */
    if( RearBaleSel )
      {	
      RearBaleSel--;
      }
    else
      {
      RearBaleSel = 10;
      }
    }
  }
else if( Switch == 2 )
  {
  draw_box( adm, OffX+95, OffY-19, OffX+95+9, OffY-19+23, CLEAR );
  for( RearBaleSel = 0; RearBaleSel < 10; RearBaleSel++ )
    {
    write_bitmap( adm, BALERREAR[RearBaleSel], OffX+95, OffY-19, OR );
    }
  }
else if( Switch == 3 )
  {
  draw_box( adm, OffX+85, OffY-25, OffX+85+29, OffY-25+6, CLEAR );
  if( !temp_flash )
    {
    write_bitmap( adm, ARROWS, OffX+85, OffY-25, OR );
    }
  else
    {
    write_bitmap( adm, FusionP05, OffX+110, OffY-23, OR );
    }
  draw_box( adm, OffX+96, OffY-23, OffX+96 + 7, OffY-23 + 2, FULL );

  }

/* Bale paused, draw symbol on rear bale */
if( PauseTip && ((RearBaleStatus & 0x01) || (RearBaleStatus & 0x02)) )
  {
  if( (balerstatus != 5) && (balerstatus != 7) )
    {
    draw_box( adm,  OffX+94, OffY-12, OffX+98, OffY-4, CLEAR );
    draw_box( adm, OffX+101, OffY-12, OffX+105, OffY-4, CLEAR );
    draw_box( adm,  OffX+94, OffY-12, OffX+98, OffY-4, EMPTY );
    draw_box( adm, OffX+101, OffY-12, OffX+105, OffY-4, EMPTY );
    }
  }

if( TransferSeqPaused == 1 )
	{
	draw_box( adm,  OffX+55, OffY-15, OffX+66, OffY-5, CLEAR );
	write_bitmap( adm, PAUSE, OffX+56, OffY-14, OR );
	}


/* display error if present */
if( old_InfoSel != InfoSel )
  {
  old_InfoSel = InfoSel;
  draw_box( adm, 2, 14, 2 + 28, 14 + 24, CLEAR );

  pWbm = &Wbm[InfoSel];
  	  if( pWbm->Warn != NULL )
		{
		write_bitmap( adm, pWbm->Warn,  2, 14, OR );
		}

	  if( (pWbm->BitMap != NULL) || (pWbm->x == 0xff) )
		{
		draw_box( adm, 35, 43, 115, 92, CLEAR );
		draw_box( adm, 35, 43, 115, 92, EMPTY );
		}

	  if( !flash_bit && (pWbm->BitMap != NULL) )
		{
		write_bitmap( adm, pWbm->BitMap, pWbm->x, pWbm->y, OR );
		}

  switch( InfoSel )
    {
    case 2: /* Wrapping */
      c = Facts[DelPul[FILMBK]][0];
      switch( c )
      {
      	case 2:
      	  sprintf( tstring, "%2u", (CountCur / 4) );
      	  break;
      	  
      	case 1:
      	default:
          sprintf( tstring, "%2u", (CountCur / 2) ); 
          break;
      }
      display_f1_text( tstring, TS20, 5, 18, FIXED );
      
      sprintf( tstring, "%2u", CountSet ); 
      display_f1_text( tstring, TS20, 16, 28, FIXED );
      break;

    case 3: /* Speed Warning */
      display_f1_text( SpeedWarning[demi_secs % 2]->l[lang], TSMAX, 38, 65, FIXED );
      break;

    case 8: /* 1 Dispensor Only */
      sprintf( tstring, "%2u", (CountCur / 2) );
      display_f1_text(tstring, TS20, 5, 18, FIXED );

      sprintf( tstring, "%2u", CountSet );
      display_f1_text(tstring, TS20, 16, 28, FIXED );
      break;

    case 14: /* Check Lube */
      write_bitmap( adm, (demi_secs % 2)? WARNINGBOX:LUBEBOX,  2, 14, OR );
      break;
      
    case 26: /* No CAN chip fitted */
      display_f1_text( (demi_secs % 2)? s0392.l[lang]:"           ", TSMAX, 42, 56, FIXED );
      display_f1_text( (demi_secs % 2)? s0393.l[lang]:"       ", TSMAX, 54, 66, FIXED );
      break;      
    }     
  }

if( LubeConfirm )
  {
  draw_box( adm, 14, 40, 126, 77, CLEAR );
  draw_box( adm, 14, 40, 126, 77, EMPTY );
     
  sprintf ( tstring, "%s?", s0299.l[lang]); /* Reset Lube Count? */
  display_f1_text( tstring, TSMAX, 20, 55, FIXED );
  }

/* Different tabs for different knife systems */
if( KnivSystem == RELIEF_VALVE )
  {
	if( AutoMan )
	  { /* auto */
	  pt1 = TAB;
	  pt2 = TAB;

	  if( KnivesEnabled )
	    {
	    pt1 = TBKNVON;
	    }
	  else
	    {
	    pt1 = TBKNOFF;
	    }

	  /* enable reverse/index */
	  if( (!IP01 && !Wrapping && !Tipping && !Transfering) || (S2_flag && IndexTable) ) /*Iss-131: S2_flag is 1 if IP01 is open for more than half a second*/
	    {
	    if( DispenserPosError && flash_bit )
	      {
	      pt3 = TAB;
	      pt4 = TAB;	
	      }
	    else if( !IndexTable )
	      {
	      pt3 = TABREV;
	      pt4 = TBINDEX;
	      }
	    else if( IP01_timer > 10 )
	      {
	      S2_flag = 1;
	      pt3 = TABESC;
	      pt4 = TBINDEX;
	      }
	      else
		  {
		  pt3 = TAB;
		  pt4 = TBINDEX;
		  }
	    }
	  else
	    {
	    pt3 = TAB;
	    pt4 = TAB;
	    if( LubeConfirm )
	      {
	      pt3 = TABTICK;
	      pt4 = TABCROSS;    	
	      }
	    }
	  }
	else
	  { /* manual */
	  pt1 = TBKNUPDN; /* dual tab */
	  pt3 = TBFWDREV; /* dualt tab */
	  }

	/* display escape if error status present */
	if( old_InfoSel && (old_InfoSel != 2) && (old_InfoSel != 1) )
	  {
	  pt2 = TABESC;
	  if( LubeCount <= 0  )
	    { pt2 = TABRESET; }
	  }

	if( pt1 != sp1 )
	  {
	  sp1 = pt1;

	  if( (selection == 0) && !AutoMan )
	    { /* dual tab */
	    draw_box( adm, 3-2, 106, 3+75+2, 106+20, CLEAR );
	    }
	  else
	    {
	    draw_box( adm, 3-2, 106, 3+36+2, 106+20, CLEAR );
		write_bitmap( adm, pt1,   3, 106, OR );
	    }
	  write_bitmap( adm, pt1,   3, 106, OR );
	  }

	if( pt2 != sp2 )
	  {
	  sp2 = pt2;

	  if( (selection == 0) && !AutoMan )
	    { /* dual tab */
	    }
	  else
	    {
	    draw_box( adm, 42, 106, 42+36+2, 106+20, CLEAR );
	    write_bitmap( adm, pt2,  42, 106, OR );
	    }
	  }

	if( pt3 != sp3 )
	  {
	  sp3 = pt3;

	  if( (selection == 0) && !AutoMan )
	    { /* dual tab + icon */
	    draw_box( adm, 81, 106, 81+75+2, 106+20, CLEAR );

	    write_bitmap( adm, SYMSLW, 81+13, 106+2, OR );
	    }
	  else
	    { /* single tab */
	    draw_box( adm, 81, 106, 81+36+2, 106+20, CLEAR );
	    }
	  write_bitmap( adm, pt3,  81, 106, OR );
	  }

	if( pt4 != sp4 )
	  {
	  sp4 = pt4;

	  if( (selection == 0) && !AutoMan )
	    { /* dual tab icon only */
	    write_bitmap( adm, SecondPress ? SYMSLW : SYMFST, 81+50, 106+2, OR );
	    }
	  else
	    { /* single tab */
	    draw_box( adm, 120, 106, 120+36, 106+20, CLEAR );
	    write_bitmap( adm, pt4,  120, 106, OR );
	    }
	  }
	
  }

else if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
  {
	if( AutoMan )
	  { /* auto */
	  if( (KnivSystem == x23_Select) )
	    {
		  if( !KnivesBank )
		    {
			pt1 = TAB_KNIV00;  
		    }
		  else if( KnivesBank & KB_KNIVES11 )
		    {
			pt1 = TAB_KNIV11;
		    }
		  else if( KnivesBank & KB_KNIVES12 )
		    {
			pt1 = TAB_KNIV12;
		    }
		  else if( KnivesBank & KB_KNIVES23 )
		    {
			pt1 = TAB_KNIV23;
		    }
	    }
	  if( KnivSystem == x23_Std )
	    {
		  if( !KnivesBank )
		    {
			pt1 = TAB_KNIV00;  
		    }
		  else if( KnivesBank & KB_KNIVES11 )
		    {
			pt1 = TAB_KNIV23; /* display TAB_KNIV23 for KB_KNIVES11 */
		    }	  		  
	    }
	  if( KnivSystem == x25_Std )
	  {
		  if( !KnivesBank )
			{
			pt1 = TAB_KNIV00;
			}
		  else if( KnivesBank & KB_KNIVES11 )
			{
			pt1 = TAB_KNIV25; /* display TAB_KNIV25 for KB_KNIVES11 */
			}
	  }
	  if(KnivSystem == x25_Select)
	  {
		  if( !KnivesBank )
			{
			pt1 = TAB_KNIV00;
			}
		  else if( KnivesBank & KB_KNIVES11 )
			{
			pt1 = TAB_KNIV13;
			}
		  else if( KnivesBank & KB_KNIVES12 )
			{
			pt1 = TAB_KNIV12;
			}
		  else if( KnivesBank & KB_KNIVES23 )
			{
			pt1 = TAB_KNIV25;
			}

	  }
	  	    
	  pt2 = TAB;
	  pt4 = TAB_INFO;
	  
	  /* enable reverse/index */
	  if( (!IP01 && !Wrapping && !Tipping && !Transfering) || (S2_flag && IndexTable) )
	    {
	    if( DispenserPosError && flash_bit )
	      {
	      pt2 = TAB;
	      pt3 = TAB;	
	      }
	    else if( !IndexTable )
	      {
	      pt2 = TABREV;
	      pt3 = TBINDEX;
	      }
	    else if(IP01_timer > 10)
	      {
	      S2_flag = 1;
	      pt2 = TABESC;
	      pt3 = TBINDEX;
	      }
	    else
		  {
		  pt2 = TAB;
		  pt3 = TBINDEX;
		  }
	    }
	  else
	    {
	    pt2 = TAB;
	    pt3 = TAB;
	    }
	  }
	else
	  { /* manual */
	  pt1 = SecondScreen? TAB_KNIV_DOWN:TAB;
	  if(KnivSystem == x23_Select)
	    {
	    pt2 = SecondScreen? TAB_KNIV1UP:TABFWDREV; /* defualt tab */
	    }
	  else if(KnivSystem == x25_Select)
	  {
		  pt2 = SecondScreen? TAB_KNIV1UP_X25_SELECT:TABFWDREV; /* Display knife-up number for the x25_Select option */
	  }
	  else
	    {
		pt2 = SecondScreen? TAB_KNIVUP:TABFWDREV; /* defualt tab */
	    }
	  
	  if( SecondScreen )
	    {
		pt3 = ((KnivSystem == x23_Select) || (KnivSystem == x25_Select))? TAB_KNIV2UP:TAB;
	    }
	  pt4 = TAB_INFO; /* info tab */
	  }
	
	/* display escape if error status present */
	if( old_InfoSel && (old_InfoSel != 2) && (old_InfoSel != 1) && (old_InfoSel != 23) && (old_InfoSel != 24) )
	  {
	  pt2 = TABESC;
	  if( LubeCount <= 0 )
	    { 
		pt2 = TABRESET; 
		}
	  
	  if( !SecondScreen && ( (old_InfoSel == 13) || (old_InfoSel == 25) || (old_InfoSel == 26) ) )
	    {
		pt3 = TAB;
	    }
	  }
	 
	if( pt1 != sp1 )
	  {
	  sp1 = pt1;
	
	  if( (selection == 0) && !AutoMan )
	    { /* dual tab */
		draw_box( adm, 2, 106, 38, 106+20, CLEAR );  
	    }
	  else
	    {
		draw_box( adm, 2, 106, 38, 106+20, CLEAR );
		write_bitmap( adm, pt1,  2, 106, OR );
	    }
	  write_bitmap( adm, pt1,  2, 106, OR );
	  }
	
	if( pt2 != sp2 )
	  {
	  sp2 = pt2;
	
	  if( (selection == 0) && !AutoMan && (old_InfoSel != 13) && (old_InfoSel != 25) && (old_InfoSel != 26) )
	    { /* dual tab */
		draw_box( adm, 41-2, 106, 41+75+3, 106+20, CLEAR );
		if( !SecondScreen )
		  {    
	      write_bitmap( adm, SYMSLW, 41+13, 106+2, OR );
		  }
	    }
	  else
	    {
	    draw_box( adm, 41-2, 106, 41+36+2, 106+20, CLEAR );
	    }
	  write_bitmap( adm, pt2, 41, 106, OR );
	  }
	
	if( pt3 != sp3 )
	  {
	  sp3 = pt3;
	  if( (selection == 0) && !AutoMan && (old_InfoSel != 13) && (old_InfoSel != 25) && (old_InfoSel != 26) )
	    { /* dual tab + icon */
		if( SecondScreen )
		  {
		  draw_box( adm, 82-2, 106, 82+36+3, 106+20, CLEAR );		
		  write_bitmap( adm, pt3,  82, 106, OR );	  
		  }
		else
		  {
		  write_bitmap( adm, SecondPress? SYMSLW:SYMFST, 45+50, 106+2, OR );
		  }
	    }
	  else
	    { /* single tab */
	    draw_box( adm, 82-2, 106, 82+36+3, 106+20, CLEAR );
	    write_bitmap( adm, pt3,  82, 106, OR );
	    }
	  }
	
	if( pt4 != sp4 )
	  {
	  sp4 = pt4;
	  draw_box( adm, 122, 106, 157, 106+20, CLEAR );
	  write_bitmap( adm, pt4,  122, 106, OR );
	  }
  }
if (((KnivSystem == x23_Std) || (KnivSystem == x25_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select )) /*&& (AutoMan != AM_MANUAL) */) /*rev. 30*/
{
  if(TAB_FLAG == 1)
	  {

		draw_box( adm, 3, 106, 3+36+2, 106+20, CLEAR );
		draw_box( adm, 42, 106, 42+36+2, 106+20, CLEAR );
		draw_box( adm, 81, 106, 81+36+2, 106+20, CLEAR );
		draw_box( adm, 120, 106, 120+36, 106+20, CLEAR );

		write_bitmap( adm, TAB, 3, 106, OR );
		write_bitmap( adm, TABESC, 42, 106, OR );
		write_bitmap( adm, TAB, 81, 106, OR );
		write_bitmap( adm, TAB, 120, 106, OR );

	  }
  else{
	  TAB_FLAG = 0;
  	  }
}
Facts[DelPul[AUTOTP]][0] = AutoTip;

if( SeqErr )
  {
  display_f1_text( ErrS[SeqErr], TS20, 33, 16, FIXED );
  c = ErrPos;
  if( c >= MAXSEQ )
    {	  
    c = MAXSEQ - 1;
    }
  sprintf( tstring, "at %u (%u,%u,%u)", ErrPos, SQ[ErrPos].Dlp, SQ[ErrPos].Pdl, SQ[ErrPos].Wdl );
  display_f1_text( tstring, TS20, 33, 26, FIXED );
  }

/* ###test1 */
#ifdef TEST
 sprintf( tstring, "Z%2u PZ%u PS%u", Zone, PauseZone, TransferSeqPaused );
 display_f1_text(tstring, 30, 33, 16, FIXED );

 sprintf( tstring, "L%u H%u H%u", FlashLedR2, Here[0], Here[1] );
 display_f1_text(tstring, 30, 33, 26, FIXED );

 sprintf( tstring, "T%u,M%u,%u", TableOccupied, MTDchk, Here[2] );
 display_f1_text(tstring, 30, 33, 36, FIXED );
#endif
 /*
 sprintf( tstring, "KTp%u Ks%u KT%3u", KnifePressureBar, KnivMonitorStage, KeyS1Delay );
 display_f1_text( tstring, 30, 33, 26, FIXED ); 

 sprintf( tstring, "Z%2u P%u M%04x ", Zone, Kniv1PresHigh, MachineStatus );
 display_f1_text( tstring, 30, 33, 25, FIXED );

sprintf( tstring, "CW%2u", CANWarnCanc ); 
display_f1_text(tstring, TS20, 33, 15, FIXED );

sprintf( tstring, "%u %u      ", PWMSlowTarget1); 
display_f1_text(tstring, TS20, 33, 34, FIXED );

sprintf( tstring, "Z%2u %c M%4x", Zone, PulseFrequency, MachineStatus );  
display_f1_text(tstring, 30, 33, 26, FIXED );
*/	  
/*
if( key == Key_S4 )
  {
  maxcall = 0;
  }
sprintf( tstring, "%ums       ", maxcall );
display_f1_text(tstring, TS20, 33, 16, FIXED );
sprintf( tstring, "%ums       ", lastcall );
display_f1_text(tstring, TS20, 33, 25, FIXED );
*/

/*
else
  {	
  sprintf( tstring, "%u %u %u %u %u %u %u %02x ", 
 CropType,
 Switch,
 balerstatus,
 RearBaleStatus,
 AutoMan,
 Op.O.OP03,
 InfoSel,
 old_selection );
 display_f1_text(tstring, TS20, 33, 25, FIXED );

  sprintf( tstring, "%2u %2u %u      ", Zone, CapB0, ITU_GRB3 ); 
  display_f1_text(tstring, TS20, 33, 16, FIXED );

  sprintf( tstring, "%u %u %u       ", PWMmax, PWMSlow2, PWMstep ); 
  display_f1_text(tstring, TS20, 33, 25, FIXED );

  sprintf( tstring, "%u %u      ", PWMSlowTarget1); 
  display_f1_text(tstring, TS20, 33, 34, FIXED );

  c = FA[DelPul[PULSER]];
  tstring[0] = hex[c / 0x10];
  tstring[1] = hex[c % 0x10];
  tstring[2] = ' ';

  c = FA[DelPul[DELYRS]];
  tstring[3] = hex[c / 0x10];
  tstring[4] = hex[c % 0x10];
  tstring[5] = ' ';

  c = FA[DelPul[PULSET]];
  tstring[6] = hex[c / 0x10];
  tstring[7] = hex[c % 0x10];
  tstring[8] = ' ';

  c = FA[DelPul[PLSTRT]];
  tstring[9] = hex[c / 0x10];
  tstring[10] = hex[c % 0x10];
  tstring[11] = ' ';

  c = FA[DelPul[PULSEU]];
  tstring[12] = hex[c / 0x10];
  tstring[13] = hex[c % 0x10];
  tstring[14] = ' ';
  tstring[15] = 0;

  display_f1_text( tstring, TS20, 33, 43, FIXED );
  }
*/
	/* ###test */

	/*
	sprintf( tstring, "d%u   ", KeyS1Delay );
	display_f1_text( tstring, TS20, 33, 32, FIXED );
*/
/*
	sprintf( tstring, "%u %u %lu     ", CanStatus, CanStage, CanCurrentTime );
	display_f1_text( tstring, TS20, 33, 15, FIXED );
		
	sprintf( tstring, "%u %u       ", CanHead, CanTail );
	display_f1_text( tstring, TS20, 33, 24, FIXED );


	struct CanMessage *CMpt;
	unsigned char ypos;
	
  	CMpt = &CanM[0];
	ypos = 53;
	for( c = 0; c < CAN_MAXMESSAGE; c++, ypos += 9, CMpt++ )
	{
		sprintf( tstring, "%03X.%02X.%02X.%02X.%02X.%02X.%02X.%02X.%02X",
			(unsigned short)(CMpt->id.l >> 21),
			CMpt->dat[0], CMpt->dat[1], CMpt->dat[2], CMpt->dat[3],
			CMpt->dat[4], CMpt->dat[5], CMpt->dat[6], CMpt->dat[7] );
		display_f1_text( tstring, 27, 8,  ypos, FIXED );
	}
*/

	/* Pressure is displayed here, but is always available globally if CanStatus == CSTATUS_OK */
	/* pressure is stored and transmitted as 10 x real value in bar, so 123 = 12.3bar, so no fp needed */
/*
	switch( CanStatus )
	{
	default:
		pt1 = CanErrorString[CanStatus];
		break;
		
	case CSTATUS_OK:
		sprintf( tstring, "%u.%0uBar      ", Pressure / 10, Pressure % 10 );
		pt1 = &tstring[0];
		break;
	}
	display_f1_text( pt1, TS20, 33, 33, FIXED );
	
	sprintf( tstring, "%u", CanInitCount - Old_CanInitCount ); / * indication of errors occuring on bus * /
	display_f1_text( tstring, TS20, 33, 42, FIXED );
*/
}

void Knife_pos_Warn (void)
{
	draw_box( adm, 35, 43, 115, 92, CLEAR );
	draw_box( adm, 35, 43, 115, 92, EMPTY );
	write_bitmap( adm, FUSION_warning_knife_position, 40, 50, OR );

	SetBeepType( BT4 | BP2, TBEXT, 1 );

	TAB_FLAG = 1; /*Display TABS of warning message*/

}

void knife_pos_input_6(void)	/*Iss 146*/
{


/*	Debug infomation.
  	unsigned char tstring[12];
	sprintf( tstring, "%01u %01u", knifeip6, knifeip7 );
	display_f1_text( tstring, TS20, 33, 32, FIXED ); */

	/* knifeip6 and knifeip7 explanation
	 * knifeipX = 0 - warning has been previously cleared, now waiting for inputX to open,
	 * knifeipX = 1 - inputX has opened so display warning,
	 * knifeipX = 2 - S2 has been pressed so warning is cleared, now wait until inputX closes.
	 */
	if( AutoMan )
	{
		if (input_count > 4)/*too fast increase it to 8?*/
		{
			if ((knifeip6 == 0) && (Ip.I.IP06 == 0)) /*Input 6 has been opened again after warning has been cleared (or for the first time)*/
			{
				knifeip6 = 1;
			}
			else if (knifeip6 == 1) /*Show warning message if the warning hasn't been cleared*/
			{
				Knife_pos_Warn();
				/*RefreshBalerDisplay = 0xff;	*//*Refresh image of BalerDisplay to clean up screen*/

				switch (key)
				{

				case Key_S2:
					input_count = 0;
					TAB_FLAG = 0;
					flag = 1;
					knifeip6 = 2;
					knifeip7 = 2;
					break;

				case Key_S1:
				case Key_S3:
				case Key_S4:
					break;
				}
			}
		}

		if ((knifeip6 == 2) && (Ip.I.IP06 == 1)) /*Warning has been cleared and input 6 is closed*/
		{
			knifeip6 = 0;
		}
	}
	else /*if(!AutoMan)*/
	{
		if (knifeip6 != 2)
		{
			input_count = 0;
			TAB_FLAG = 0;
			flag = 1;
			knifeip6 = 2;
			knifeip7 = 2;
		}
	}

}

void knife_pos_input_7(void)	/*Iss 146*/
{


	/* knifeip6 and knifeip7 explanation
	 * knifeipX = 0 - warning has been previously cleared, now waiting for inputX to open,
	 * knifeipX = 1 - inputX has opened so display warning,
	 * knifeipX = 2 - S2 has been pressed so warning is cleared, now wait until inputX closes.
	 */
	if( AutoMan )
	{
		if (input_count > 4)/*too fast increase it to 8?*/
		{
			if ((knifeip7 == 0) && (Ip.I.IP07 == 0)) /*Input 6 has been opened again after warning has been cleared (or for the first time)*/
			{
				knifeip7 = 1;
			}
			else if (knifeip7 == 1) /*Show warning message if the warning hasn't been cleared*/
			{
				Knife_pos_Warn();
				/*RefreshBalerDisplay = 0xff;	*//*Refresh image of BalerDisplay to clean up screen*/

				switch (key)
				{

				case Key_S2:
					input_count = 0;
					TAB_FLAG = 0;
					flag = 1;
					knifeip6 = 2;
					knifeip7 = 2;
					break;

				case Key_S1:
				case Key_S3:
				case Key_S4:
					break;
				}
			}
		}

		if ((knifeip7 == 2) && (Ip.I.IP07 == 1)) /*Warning has been cleared and input 6 is closed*/
		{
			knifeip7 = 0;
		}

	}
	else /*if(!AutoMan)*/
	{
		if (knifeip7 != 2)
		{
			input_count = 0;
			TAB_FLAG = 0;
			flag = 1;
			knifeip6 = 2;
			knifeip7 = 2;
		}
	}
}
unsigned char KeyToggle( void )
{
	/*static unsigned char SpeedChanged;*/  /* Iss-107 change */

/*	if( swrel > 5 )
	{
		SecondPress = 0;	FAST
		SpeedChanged = 0;
	}
	else */
	if( SpeedChanged == 0 /*!(key & KeyDone)*/ ) /* first key press */
	{
		SpeedChanged = 1;
		SecondPress = SecondPress? 0:1;	/*inverts SecondPress. if (SecondPress == 1), SecondPress = 0; else SecondPress = 1;*/
	}
	else if( SpeedChanged == 1)
	{
		SpeedChanged = 1; /*Do nothing as button has not been released yet*/
	}
	else if( SpeedChanged == 2)	/*141.08 If a key hasn't been pressed for 3 seconds then set the pwm to slow when next pressed */
	{
		SpeedChanged = 1;
		SecondPress = 0;
	}

	return( SecondPress );
}


void AutoSequence ( void )
{
	unsigned char Action;
	unsigned short int SeqPnt, SQAct;
	struct Sequence *SQSP;

	/* ### sequence actions here */
	if( DecTens )
	  {
		DecTens--;
		/* Iss-106 */
		if( KnivTimer )
		{
			KnivTimer--;
		}
		Action |= 0x01;
	  }
	else
	  Action &= ~0x01;

	if( DecUnits )
	{
		DecUnits--;
		Action |= 0x02;
	}
	else
		Action &= ~0x02;

	if( DecPulse && Wrapping )
	{
		DecPulse--;
		Action |= 0x04;
	}
	else
		Action &= ~0x04;

	if ( DecRpm )
	{
		DecRpm--;
		Action |= 0x08;
	}
	else
		Action &= ~0x08;

	for( SeqPnt=0; SeqPnt < MAXSEQ; SeqPnt++ )    /* check each entry */
	{
	SQSP = &SQ[SeqPnt];
	if( SQSP->Seq & CurrentSequenceMask )  /* entry for this sequence? */
	{
			SQAct = SQSP->Act;
			if( SQAct & CancelIfDone ) /* action cancel */
			{
				CancelBothIfOneDone( SQSP, SeqPnt );
			}
			else if( WaitUntilDone( SQSP, SeqPnt ) ) /* wait for delay/pulse/switch */
			{
				if( SQAct & DelayOrPulseWait )
				{
					CheckDelayOrPulse( SQSP, SeqPnt, Action );
				}
				else if( SQAct & SwitchWait )
				{
					CheckSwitch( SQSP, SeqPnt );
				}
				else if( SQAct & EnableAndLoad )
				{
					LoadDelayAndOutputs( SQSP, SeqPnt );
				}
			}
		}
	}
}


void OutputSet( void )
{
static unsigned char RemoteActionDone, ChamberCount, BPress;
unsigned char *pt, AutoTip;
static unsigned char KnivesDown;
/* ###test */
/*
unsigned long int ctime;
*/

/* ###test */
/*SCI1_SCR = 0x00;
P9DR |= 0x02;*/

KeyOp.L = 0UL;			/* All Key/Remote outputs Off */

AutoTip = Facts[DelPul[AUTOTP]][0];

if( IP01 )
  {
  DispenserPosError = 0;
  KS3_Flag = 0;
	  if( (IP10_Flag == 2) ) /* If IP01 was already closed, or started open after IP10 was closed */
	  {
		  IP10_Flag = 0;
		  /* TURN OFF! */
		  ITU_GRB3 = 0;       /* off */
		  ITU_TIER0 &= ~0x02; /* Timer Capture Int B off */
		  OP03 = 0;
		  ITU_TMDR &= ~0x08;  /* Timer 3 PWM off */
		  /* TURN OFF! */
	  }
  }

if( AutoMan )
  { /* AUTO */
  if( !(CurrentSequenceMask & (O_Flm | O_Ps)) )
    {
    FilmBreakCheck();

    if( TransferBale )
      {
      }
    /* if bale chamber switch closes then opens, reset sequence */
    else if( (Sel < 5) && Ip.I.IP08 && !OMS_TRANS && (MachineStatus & MS_CHAMBERFULL) )
      {/* was (Zone == (Zone01 & 0x7f))  )*/
      ResetSequenceFactors( SEQ_NET );
      Zone = 0;
      SetBeepType( BT0 | BP1, TBOFF, 0 ); /* all Beeps off */
      } /* AutoStart if key pressed or chamber closed */
    else if( SupplyVolts > 104 ) /* if voltage > 10.4v */
      {
      if( !Ip.I.IP08 && !(Transfering || OMS_TRANS) && !UnBlockStatus && !NetDoneWaitingTransfer )
        {
        Ip.I.AUTOST = 1; /* VSWTCA */
        if( !SavedCountCur && !(Wrapping || OMS_WRAP) )
          {
          DispenserStatus = 0;
          }
        }
      else if( !SavedCountCur && !UnBlockStatus ) /* and not film break/dispenser safety */
        {
        if( ResumeFrom == 0xaa )
          {
          ResumeFrom = Zone04;
          /*Ip.I.TIPST = 1;  commented out in ISS-036 */
          }
        else if( ResumeFrom == 0xab )
          {
          ResumeFrom = 0;
          if( !Wrapping && !Tipping && !OMS_TIPWRAP && !NetCheck && Ip.I.IP09 )
            {
            StartWrapSequence( SWS_TRANS | SWS_RESETCOUNT ); /* from transfer */
            }
          }
        else if( !Ip.I.IP08 && !(Transfering || OMS_TRANS) && !UnBlockStatus )
          {
          Ip.I.AUTOST = 1; /* VSWTCA */
          if( !(Wrapping || OMS_WRAP) )
            {
            DispenserStatus = 0;
            }
          }
        else if( (CurrentSequenceMask & O_S1) &&
                 ((key & ~KeyMask) == Key_R1) &&
                 !Wrapping && !Tipping && !OMS_TIPWRAP )
          {
          if( ((!IP01) && (IP01_timer > 10)) || (S2_flag))
            {
        	S2_flag = 1;
            DispenserPosError = 1;
            }
          else if( !Ip.I.IP04 ) /* TIPUP */
            {
            TipPosErr = 1;
            }
          else if( StartDelayComplete() )
            {
        	demi_secs = 0;
            SafetyCount = 0;
            IP01Count = 0;
            PulseFrequency = 0.0;
            DispenserStatus = 0;
            ResetSequenceFactors( SEQ_WRAP );

            StartWrapSequence( SWS_WRAP | SWS_RESETCOUNT ); /* from delykl */
            }
          }
        }
      }

    if( !CapB0 && !(Tipping || OMS_TIP) &&
        (!(Wrapping || OMS_WRAP) || (DispenserStatus == 2)) )
      {
      if(( Ip.I.IP10 && !Ip.I.IP04 ) ) /* remote park and TIPUP open */
        {	
        IP10_Delay = 0;
        TipPosErr = 1;
        }
      else if( IP10_Delay >= 3 ) /* remote 'park dispenser' */
        {
        IndexTable = 10;
        CapB0 = 13;           /* set for controlled slow rotate */
        ITU_GRB3 = PWMSlow1;  /* start rotation */
        if( ITU_TSR0 & 0x02 ) /* Clear interrupt request flag */
          ITU_TSR0 &= ~0x02;
        ITU_TIER0 |= 0x02;    /* Timer Capture Int B on */
        ITU_TMDR |= 0x08;     /* Timer 3 PWM on */
        }
      }

    if( UnBlockStatus == 1 )
      {
      UnBlockStatus = 0;
      }

    /* AUTO - allow auto start in wrap screen only, check table positon */
    if( Sel == 2 )
      {
      switch( key & ~KeyMask )
        {
        case Key_R1: /* Resume Start */
          /* only in bale & wrap sequence, not in bale only or others */
        	if( WrapSeq == WS_RUNNING) /* pause the sequence */
			{
					CurrentSequenceMask = O_Ps;
					WrapSeq = WS_PAUSED;
			}
		  else
			{
				if( CurrentSequenceMask & O_S1 )
					{
					if( WrapSeq == WS_PAUSED ) /* resume the wrap sequence */
						{
						if( ((!IP01) && (IP01_timer > 10)) || (S2_flag)) /*Rotate sensor input*/
							{
							S2_flag = 1;
							DispenserPosError = 1;
							}
						else if( !Ip.I.IP04 ) /* TIPUP */
							{
							TipPosErr = 1;
							}
						else if( StartDelayComplete() )/*rev. 30 fix*/
							{
							demi_secs = 0;
							SetForReStart();
							StartWrapSequence( SWS_WRAP ); /* from delykl */
							WrapSeq = WS_RESUMED;
							}
						}
					else if( OMS_WRAP )
						{
						if( ((!IP01) && (IP01_timer > 10)) || (S2_flag) ) /*Rotate sensor input*/
							{
							S2_flag = 1;
							DispenserPosError = 1;
							}
						else if( !Ip.I.IP04 ) /* TIPUP */
							{
							TipPosErr = 1;
							}
						else if( StartDelayComplete() )
							{
							oldMachineStatus = 0;
							SavedCountCur = CountCur;

							SetForResume();
							StartWrapSequence( SWS_WRAP ); /* from delykl */
							}
						}
					else if( SavedCountCur )
						{
						if( ((!IP01) && (IP01_timer > 10)) || (S2_flag) ) /*Rotate sensor input*/
							{
							S2_flag = 1;
							DispenserPosError = 1;
							}
						else if( !Ip.I.IP04 ) /* TIPUP */
							{
							TipPosErr = 1;
							}
						else if( StartDelayComplete() )
							{
							demi_secs = 0;
							SetForReStart();
							StartWrapSequence( SWS_WRAP ); /* from delykl */
							}
						}
					}
			}

          break;

        case Key_L3: /* UnBlock3/4 */
          if( UnBlockStatus == 3 )
            { /* set at end of unblock sequnce, when zone is set to 23 */
            ResetFloor();
            }
          break;

        case Key_R3: /* UnBlock1/2 */
          if( UnBlockStatus == 0 )
            {
        	if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
        	  {
              SeqOp.L &= ~(O07 | O10 | O15);
        	  }
        	UnBlock();
            }
          break;
          
        case Key_R4: /* Tip Start */
        case Key_BL:
          if( TableOccupied && !(Wrapping || OMS_WRAP) && (SafetyCount < SAFETYLEVEL) &&  !(MachineStatus & MS_CHAMBEROPEN) )
            {
				if( !IP01 ) /* check table position  */
				{
					DispenserPosError = 1;
				}
				else if( key && !(key & KeyDone) && (!Tipping || OMS_TIP) && !UnBlockStatus && !Op.O.OP13 && (!Op.O.OP11 || CropType) ) /* For Hay or Straw, dont wait for door close overtravel time. */
				{
					if( PauseTip )
					{
						AutoTip = 1;
					}

					AutoTip_Sel = 1;
					oldMachineStatus = 0;

					if( !Ip.I.IP10 )
					{
						Ip.I.TIPST = 1;
					}

					TipCheck = 0;
				}
            }
          break;

        default:
        	if( WrapSeq == WS_RESUMED )
        		{
        		WrapSeq = WS_RUNNING;
        		}
        	break;
        }
      }
    }
   /* filmbreak or dispenser safety running */
  else if( CurrentSequenceMask & O_Flm )
    {
    if( SupplyVolts > 104 ) /* if voltage > 10.4v */
      {
      if( !Ip.I.IP08 && !(Transfering || OMS_TRANS) && !UnBlockStatus )
        {
        Ip.I.AUTOST = 1; /* VSWTCA */
        }
      }
    }

  switch ( RemoteCode )
    {
    case RSTART:
      /* allow auto start in wrap screen only, if voltage > 10.4v */
      if( !Zone && (Sel == 2) && (SupplyVolts > 104) ) /* sequence not running */
        {
        if( Ip.I.IP08 && TableOccupied && !(Wrapping || OMS_WRAP || OMS_TRANS) && !DispenserStatus )
          {
          if( !IP01 && (IP01_timer > 10)) /* check table position  */
            {         /* error if not closed */
            ResetSequenceFactors( SEQ_WRAP );
            DispenserPosError = 1;
            }
          else if( !UnBlockStatus )
            {
        	  if( !Ip.I.IP10 )
                {
                Ip.I.TIPST = 1;
                }
            RemoteRun = 1;
            }
          }
        else if( SavedCountCur ) /* Resume Start */
          {
          if( !IP01 && (IP01_timer > 10))
            {
            DispenserPosError = 1;
            }
          else if( !Ip.I.IP04 ) /* TIPUP */
            {
            TipPosErr = 1;
            }
          else
            {
            SetForReStart();
            StartWrapSequence( SWS_WRAP ); /* from delykl */
            RemoteRun = 1;
            }
          }
        else if( !RemoteActionDone && IP01 ) /* check table positon */
          {
          if( !Ip.I.IP08 && !(Transfering || OMS_TRANS) && !UnBlockStatus )
            {
            RemoteActionDone = 0xff;
            Ip.I.AUTOST = 1; /* VSWTCA */
            RemoteRun = 1;
            }
          }
        }
      break;
    case RSTOP:
      ResetSequenceFactors( SEQ_ALL );
      SavedCountCur = 0;
      break;

    default:
    case RFWD:
    case RREV:
      if( RemoteActionDone )
        {
        RemoteActionDone = 0x00;
        ITU_GRB3 = 0;      /* Fwd off */
        OP03 = 0;
        ITU_TMDR &= ~0x08; /* Timer 3 PWM off */
        }
      break;
    }

  /* Auto - any time/cursor keys  */
  if( (selection == 0) && (window == main_loop) )
    {
	if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
	  {
	    switch( key & ~KeyMask ) /* Auto Switch Options - shared function */
	      {
	      case Key_S2: /* Reverse - check table position */
	        if( !IP01 && !IndexTable && Ip.I.IP04 && /* TipUp */
	            !Wrapping && !Tipping && !Transfering )
	          {
	          KeyOp.L = O04; /* OP04 Reverse Slow */
	          }
	        break;
	
	      case Key_S3: /* Fwd */
	        if( mainscreen_delay )
	          {
	          if( !IP01 && !IndexTable && Ip.I.IP04 && /* TipUp */
	            !Wrapping && !Tipping && !Transfering )
	            {
				KS3_Flag = 1;
	            IndexTable = 1;
	            CapB0 = 13;           /* set for controlled slow rotate */
	            ITU_GRB3 = PWMSlow1;  /* start rotation */
	            if( ITU_TSR0 & 0x02 ) /* Clear interrupt request flag */
	              ITU_TSR0 &= ~0x02;
	            ITU_TIER0 |= 0x02;    /* Timer Capture Int B on */
	            ITU_TMDR |= 0x08;     /* Timer 3 PWM on */
	            }
	          }
	        break;
	      }
	  }
	else if( KnivSystem == RELIEF_VALVE )
	  {
	    switch( key & ~KeyMask ) /* Auto Switch Options - shared function */
	      {
	      case Key_S3: /* Reverse - check table position */
	        if( !IP01 && !IndexTable && Ip.I.IP04 && /* TipUp */
	            !Wrapping && !Tipping && !Transfering )
	          {
	          KeyOp.L = O04; /* OP04 Reverse Slow */
	          }
	        break;

	      case Key_S4: /* Fwd */
	        if( mainscreen_delay )
	        {
	          if( !IP01 && !IndexTable && Ip.I.IP04 && /* TipUp */
	            !Wrapping && !Tipping && !Transfering )
	          {
	            IndexTable = 1;
	            CapB0 = 13;           /* set for controlled slow rotate */
	            ITU_GRB3 = PWMSlow1;  /* start rotation */
	            if( ITU_TSR0 & 0x02 ) /* Clear interrupt request flag */
	              ITU_TSR0 &= ~0x02;
	            ITU_TIER0 |= 0x02;    /* Timer Capture Int B on */
	            ITU_TMDR |= 0x08;     /* Timer 3 PWM on */
	          }
	        }
	        break;
	      }
		
	  }
    }

  /* Auto - any time keys  */
  switch ( key & ~KeyMask ) /* Auto Switch Options */
    {
    case Key_L1: /* AUTO */

    	if( NetCutPosAlarm || NetCutPosNorm ) /*This triggers the beeping sound*/
		{
		KeyOp.L = O02;
		}
		pt = &FA[DelPul[DELYAB]];
		if( !NetHoldTime )
		  {
			NetHoldTime = *pt; 	/*load beeping after L1 has been pressed*/
		  }
		*pt = 200; 				/*Reset DELYAB*/
		SetBeepType( BT1 | BP2, TBINT, 1 ); 								/* 100/200ms On/Off, Int, 1 Count */
		/*}*/

			/*KeyOp.L = O02;*/ 			/* OP06 Net On */
			 Transfering = 0;
			/*ResetSequenceFactors(SEQ_NET);*/

      break;

    case Key_L2:
    	if( PauseZone )
    		{
    		TransferSeqPaused = 1;
    		}
    	break;

    case Key_R2: /* Auto - Open Baler */
    	if( TransferSeqPaused > 0 ) /* Iss-124 */
    	{
    		StartTransfer();
    		FlashLedR2 = 0;
    		TransferSeqPaused = 2;
    	}
    	else
			{
				if(!TableOccupied)
				{
					if( MTDcnt )
					{
					}
					else if( (!Wrapping && !Tipping && !Transfering &&
							 (((TransferNow == 1) && !OMS_TIPWRAP)))
							 || PauseTip )
					{
						/* continue with transfer after netting */
						MachineStatus &= ~MS_CHAMBERFULL;
						NetCutPosAlarm = 0;
						PauseTip = 0;
						oldMachineStatus = 0;
						TransferNow = 0;
						ResetSequenceFactors( SEQ_WRAP );
						SeqOp.L &= ~(O08 | O09 | O11);
						StartWrapSequence( SWS_TRANS | SWS_RESETCOUNT ); /* from transfer */
						NetWarnCanc = 0;

						if( Facts[DelPul[DIVDEL]][0] == SL_MANUAL )
							{
							MachineStatus |= MS_TRANSFER;
							}
					}
					else if( (IP01 && !NetCheck && (ResumeFrom == Zone04)) )
					{
						if( TableOccupied )
						{
							ResumeFrom = 0xaa;
						}
						else
						{
							ResumeFrom = 0xab;
						}
					}
				}
				else /* TableOccupied */
				{
					if( !Wrapping && !Tipping && !Transfering && TransferBale )
					{
									MachineStatus &= ~MS_CHAMBEROPEN;
									TransferBale = 0;
									ResetSequenceFactors( SEQ_TIP );
									StartWrapSequence( SWS_WRAP | SWS_RESETCOUNT ); /* from delykl */
					}
					else if( MachineStatus & MS_TRANSFER )
					{
						/* mid transfer pause */
						if( RaiseDoor )
							RaiseDoor = 0x02;

						if( (Facts[DelPul[DIVDEL]][0] == SL_MANUAL) || (BPress) )
						{
							/* if pause transfer selected */
							ManTransDelay = 2;
							BPress = 0;

						}
						else
						{
							/* pause this transfer */
							MTDchk = 2;
							ManTransDelay = 0;
							Facts[DelPul[DLYOGH]][0] = 200;/* set long pause */
							BPress = 1;
						}
					}
				}
			}
      break;

    default:
      if( NetHoldTime )
        {
			FA[DelPul[DELYAB]] = 0; /*Iss-136*/
			SetBeepType( BT2 | BP2, TBINT, NetHoldTime / 2 ); /* 100/100ms On/Off, Int, n Count */

			/*Iss-136: below*/
				RearBaleStatus |= 0x20;
				write_bitmap( adm, BALENORMAL2_v2, OffX+42, OffY-28, OR );

				MachineStatus |= MS_CHAMBERFULL;
				MachineStatus &= ~MS_CHAMBEROPEN;

				SetOneDispRevs();

				if(Ip.I.IP08)
					Ip.I.AUTOST = 1;
				else
					Ip.I.AUTOST = 0;
			/*Iss-136: Above*/

			/*Here[0] = 1;*/
			 NetHoldTime = 0;

        }

      if( TransferSeqPaused == 2 )
      	{
      	TransferSeqPaused = 0;
      	}
      break;
    }
  

/*--------------------------------------------------------------*/

/* Iss-105, whenever Knife pressure warning appears OP07/OP10 should turn on to reduce the pressure */
  if( !KnivStage && !KnivMonitorStage 
    && ((KnivSystem == x23_Std) || (KnivSystem == x23_Select)|| (KnivSystem == x25_Select) || (KnivSystem == x25_Std)) ) /* Iss-107 */
    {
	/* Iss-108 O07 also inhibited during floor top-up */
	if( ((KnivesBank == KB_KNIVES11) || (KnivesBank == KB_KNIVES23)) 
	  && !UnBlockStatus && !(MachineStatus & MS_FLOORTOPUP) )
	  {
	  if( !Kniv1PresHigh )
	    {
		if( Kniv1Pres > KnifePresWarnBar )
		  {
		  Kniv1PresHigh = 1;
		  /*SeqOp.L |= O07;*//* Iss-146 */
		  }	  
	    }
	  else if( Kniv1PresHigh == 1 )/* kniv1 pressure high */
	    {
		if( Kniv1Pres < (Korean? KoreanPresBar:KnifePressureBar) )
		  {
	      /*SeqOp.L |= O15;*//* Iss-145 */
	      Kniv1PresHigh = 2;      
		  }  
	    }	  
	  else if( Kniv1PresHigh == 2 )
	    {
		if( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) )
		  {
		  /*SeqOp.L &= ~( O07 | O15 ); *//* Iss-145 */
		  Kniv1PresHigh = 0;			
		  }
	    }	    
	  }
	
	/*if( ((KnivesBank == KB_KNIVES12) || (KnivesBank == KB_KNIVES23)) && !UnBlockStatus )*/
	/* Iss-108 O07 also inhibited during floor top-up *//* Iss-108 O10 also inhibited during floor top-up */
	if( ((KnivesBank == KB_KNIVES12) || (KnivesBank == KB_KNIVES23)) 
	  && !UnBlockStatus && !(MachineStatus & MS_FLOORTOPUP) )
	  {
	  if( !Kniv2PresHigh )
	    {
	    if( Kniv2Pres > KnifePresWarnBar )
	  	  {
	  	  Kniv2PresHigh = 1;
	  	  /*SeqOp.L |= O10;*//* Iss-146 */
	  	  }  
	    }
	  else if( Kniv2PresHigh == 1 )/* kniv2 pressure high */
	    {
		if( Kniv2Pres < (Korean? KoreanPresBar:KnifePressureBar)  )
		  {
	      /*SeqOp.L |= O15;*//* Iss-145 */
	      Kniv2PresHigh = 2; 
		  }
	    }	  	  
	  else if( Kniv2PresHigh == 2 ) /* kniv2 pressure high */
	    {
	    if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )
		  {
		  /*SeqOp.L &= ~( O10 | O15); *//* Iss-145 */
		  Kniv2PresHigh = 0;			
		  }		  
	    }
	  }
    }

/* -------/\-------  ISS-105/106 change  -------/\------- */
  
/* #################  ISS-097 change  ################## */

if( (window == main_loop) && !UnBlockStatus ) /* only in AUTO */
  {  
  if( (KnivSystem == x23_Std) || (KnivSystem == x25_Std) )/*############### Iss-102 change - Single knife system ##############*/
    {
	  if( !KnivesBank && (KeyS1Delay > 19) )
	    {	
		if( !InitialKnivDownRoutineDone )
		  {
		  if( FA[DelPul[DLYUS1]] == 0xFD )
		    {
			SeqOp.L &= ~O15; /* always off */
		    FA[DelPul[DLYUS1]] = 0x00;
		    InitialRoutine = 1; /* EP306-004 */
		    TimingBit = 1;
		    Zone = Zone22 & 0x7f;
		    } 
		  }			  
	    }
	  else if( (KnivesBank == KB_KNIVES11) && (KeyS1Delay > 19) 
			  && !Kniv1PresHigh ) /* TAB_KNIV11 is being displayed */
	    {
		if( !InitialRoutine )
		  {
	      if( !KnivTopUpDone )
	    	{
	    	MonitorKnives();	    	  
	    	}		  
	      }
	    }	  
    } /* end single knife system */
  else if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
    {
	  if( !KnivesBank && (KeyS1Delay > 19) )
	    {	
		if( !InitialKnivDownRoutineDone )
		  {
		  if( FA[DelPul[DLYUS1]] == 0xFD )
		    {
			SeqOp.L &= ~O15; /* always off */
		    FA[DelPul[DLYUS1]] = 0x00;
		    InitialRoutine = 1; /* EP306-004 */
		    TimingBit = 1;
		    Zone = Zone22 & 0x7f;
		    } 
		  }			  
	    }
	  else if( (KnivesBank == KB_KNIVES11) && (KeyS1Delay > 19) 
			  && !Kniv1PresHigh ) /* TAB_KNIV11 is being displayed */
	    {
		  if( (Kniv2Pres > KnifeDownPresBar) /*&& (CanStatus == CSTATUS_OK)*/
		   && !InitialKnivDownRoutineDone )
		    {			
		    if( FA[DelPul[DLYUS1]] == 0xFD )
		      {
		      SeqOp.L &= ~O15;
			  FA[DelPul[DLYUS1]] = 0x00;
			  InitialRoutine = 1; /* EP306-004 */
			  TimingBit = 1;
			  Zone = Zone22 & 0x7f;
		      }			  
		    }
	      else if( !InitialRoutine )/* EP306-004, either initial knives down rouitne didnt start or has finished. */
		    {	  	
	    	if( !KnivTopUpDone )
	    	  {
	    	  MonitorKnives();	    	  
	    	  }		
		    }  
	    }
	  else if( (KnivesBank == KB_KNIVES12) && (KeyS1Delay > 19) 
			   && !Kniv2PresHigh ) /* TAB_KNIV12 is being displayed */
	    {						  
		  if( (Kniv1Pres > KnifeDownPresBar) && !InitialKnivDownRoutineDone ) 
			{				

			if( FA[DelPul[DLYUS1]] == 0xFD )
			  {
				SeqOp.L &= ~O15;
				FA[DelPul[DLYUS1]] = 0x00;
				InitialRoutine = 1; /* EP306-004 */
				TimingBit = 1;
				Zone = Zone22 & 0x7f;
			  }			  
			}
	      else if( !InitialRoutine ) /* EP306-004, either knives down rouitne didnt start or has finished. */
			{
			SeqOp.L &= ~O07; /*  */
	    	if( !KnivTopUpDone )
	    	  {
	    	  MonitorKnives();	    	  
	    	  }	
			}				  		  
	    }
	  else if( (KnivesBank == KB_KNIVES23) && (KeyS1Delay > 19) )
		{
    	if( !KnivTopUpDone )
    	  {
    	  MonitorKnives();	    	  
    	  }	  
		}      	
    }	  
  }
/* ################ End ISS-097 change ################# */

  /* if IP01 opens in the first 3 sec of tipping, Iss-093 */
  if( (Zone == (Zone14 & 0x7f)) && ((!IP01) && (IP01_timer > 10)) || S2_flag)
    {

	if(KS3_Flag || IP10_Flag)  	/* If key_S3 or IP10 has been toggled, then clear s2_flag to exit alarm routine*/
		S2_flag = 0;
	else			/* Else, only if key_s2 has been pressed, then s2_flag is cleared*/
		S2_flag = 1;

    ResetSequenceFactors( SEQ_TIP );
    Tipping = 0;
    SeqOp.L &= ~(O17 | O13 | O08);
    DispenserPosError = 1;
    }
  
  /* Chamber Closed & Not transfer mode & (top up count < 2) & not waiting for transfer bale */
  if( Ip.I.IP08 && !Transfering && (TopUpCount < 1) && !(MachineStatus & MS_CHAMBEROPEN) && !TransferBale )
    {
    Ip.I.CTOP = 1; /* start top up sequence */
    }
  else
    {
    if( !Ip.I.IP08 )
      {
      TopUpCount = 0;
      }
    
    if( SA[SwLook[VSWTCD]] == 0x00 ) /* switch done, then reset */
      {
      /* if O11 delay running then wait */
      if( FA[DelPul[DLYT02]] > 250 )
        {
        ResetSequenceFactors( SEQ_CTOP );
        }
      }
    }

  if( MachineStatus & MS_CHAMBERFULL )
  /* was if( Zone == (Zone01 & 0x7f) ) */
  	{
	if((key & ~KeyMask) == Key_S2)
  	  {
  	  ChamberCount = 0;
  	  }
  	
    /* used for NetCutPosAlarm */
    if(!Ip.I.IP09)
      {
      ChamberCount = 0;
      }
    else
      {
      if( ChamberCount < 10 )
    	{	
    	ChamberCount++;	
    	}
      }

    if( (ChamberCount < 10) && (!(NetCutPosAlarm & 0x02)) )
      { 
      SetBeepType( BT2 | BP1, TBEXT, 1 ); /* 100/100ms On/Off, Ext, 1 Count */
      if((!Ip.I.IP08 ) && ExtBuzzer && ExternalBuzzSet)
        {
  	    SeqOp.L ^= O18; 
  	    ExternalBuzzSet = 0;
        }
      }
    else if(!(NetCutPosAlarm & 0x02))
      {
      NetCutPosAlarm |= 0x01;
      }
    else
      {
      SeqOp.L &= ~O18;
      ExternalBuzzSet = 0;
      }
    }
  else
    {
    SeqOp.L &= ~O18;
    ExternalBuzzSet = 0;
    }

  /* if delay running then alarm */
  if( FA[DelPul[DELYBC]] < 250 )
    {
    if( Music == NULL )
      {
      SetVolume( AlarmVolume );
      Music = Alarm01;
      ChamberCount = 0;
      }
    }

  CheckLubeTopUp();

  AutoSequence();
  
  Op.L = KeyOp.L | SeqOp.L;
  }
else if( (Sel == 2) && (selection == 0) && (window == main_loop) )  /* MANUAL */
  {
  DispenserCountBit = 1;
  RpmCountBit = 1;
  
  if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
    {
	  switch( key & ~KeyMask  ) /* MANUAL Switch Options */
	    {
	    case Key_S1:
	      if( SecondScreen )
	        {
	      	if((KnivSystem == x23_Select) || (KnivSystem == x25_Select))
	      	  {
	      		KeyOp.L = O07 | O10; /* Knives Down */
	      	  }
	      	else
	      	  {
	      	  KeyOp.L = O07; /* Knives Down */
	      	  }	    	
	    	
	    	if( (Op.L & O07) && (swtim > 5) ) /* Iss-099 change */
	    	  {
	    	  KeyOp.L |= O16;
	    	  KnivesDown = 1;
	    	  }
	        }
	      break;
	
	    case Key_S2:   /* MANUAL */ 
	      if( !SecondScreen )
	        {
	        if( !Ip.I.IP04 ) /* TIPUP */
	          {
	          TipPosErr = 1;
	          }
	        else 
	          { /* in twin knives selected, then dont turn on these ops when esc tab is shown */
	          if( (KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
	            {
	        	KeyOp.L = O04; /* OP04 Reverse Slow */
	            }
	          }
	        }
	      else
	        { /* in twin knives selected, then dont turn on these ops when esc tab is shown */
	    	if( (KnivSystem == x23_Std)  || (KnivSystem == x23_Select) || (KnivSystem == x25_Select)  || (KnivSystem == x25_Std))
	    	  {
		      KeyOp.L = O07;
		      
		      if( (Op.L & O07) && (swtim > 5) ) 
		    	{
		    	KeyOp.L |= O15;
		    	}
		      if( (Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar)) && !(WasHigh & KB_KNIVES11) )    		
		    	{
		    	KeyOp.L &= ~(O07 | O15); /* OP04 Reverse Slow */
		    	}
	    	  }
	        }
	      break;
	
	    case Key_S3:  /* MANUAL */
	    if( !SecondScreen )
	      {
	      if( mainscreen_delay )
	        {   	  
	        if( !Ip.I.IP04 ) /* TIPUP */
	          {
	          TipPosErr = 1;
	
	          ITU_GRB3 = 0;      /* off all the time */
	          OP03 = 0;
	          ITU_TMDR &= ~0x08; /* Timer 3 PWM off */
	          }
	        else
	          {
	          if( KeyToggle() )
	            {
	            ITU_GRB3 = PWMFREQ + 1; /* OP03 Fast */
	            }
	          else
	            {
	            ITU_GRB3 = PWMSlowTarget1; /* OP03 Slow */
	            }
	          ITU_TMDR |= 0x08; /* Timer 3 PWM on */
	          }
	        }
	      }
	    else if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
	      {	    	
	      KeyOp.L = O10; 
	  	  if( swtim > 5 )
	  	    {
	  	    KeyOp.L |= O15;
	  	    }	  	  
	  	  if( (Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar)) && !(WasHigh & KB_KNIVES12) )
	  	    {
	  	    KeyOp.L &= ~(O10 | O15); /* OP04 Reverse Slow */
	  	    }
	      }
	      break;
	
	    case Key_L1: /* MAN */
	      if( !Ip.I.IP09 ) /* net cut sensor open */
	        {
	        KeyOp.L = O02; /* OP06 Net On */
	        }
	      break;
	
	    case Key_L2:
	      KeyOp.L = O11; /* OP11 Baler Close */
	      break;
	
	    case Key_R2:
	      KeyOp.L = O12; /* OP01 Baler Open */
	      break;
	
	    case Key_L3:
	      KeyOp.L = O15; /* Floor Up  */
	      break;
	
	    case Key_R3:
	      KeyOp.L = O16; /* Floor Down (Reel Down & Diverter1) */
	      break;
	
	    case Key_R4:
			if(!IP01) /* check table position  */
			{
				DispenserPosError = 1;
			}
			else
			{
				KeyOp.L = O08; /* OP08 Tip Up (Tip Off) */
			}
	      break;
	
	    case Key_L4:
	      SafetyCount = 0;
	      KeyOp.L = O09; /* OP09 Tip Down (Tip Return) */
	      break;
	      
	    default:

	      if( SpeedChanged == 1)
		  {
			 SpeedChanged = 0;
		  }


	      if( KnivesDown )
	        {	    	
	    	KeyOp.L = O07;	    	  	    	
	    	if( swtim > 5 )
	    	  {	    	  
	    	  KnivesDown = 0;
	    	  }
	        }
	      break;
	    }
    }
  else if( KnivSystem == RELIEF_VALVE )
    {
	  switch( key & ~KeyMask ) /* Manual Switch Options */
	    {
	    case Key_S1:
	      KeyOp.L = O16; /* Knives Up */
	      break;

	    case Key_S2:
	      KeyOp.L = O15; /* Knives Down */
	      break;

	    case Key_S3:
	      if( !Ip.I.IP04 ) /* TIPUP */
	        {
	        TipPosErr = 1;
	        }
	      else 
	        {
	        KeyOp.L = O04; /* OP04 Reverse Slow */
	        }
	      break;

	    case Key_S4:
	      if(mainscreen_delay)
	      {
	        if( !Ip.I.IP04 ) /* TIPUP */
	        {
	          TipPosErr = 1;

	          ITU_GRB3 = 0;      /* off all the time */
	          OP03 = 0;
	          ITU_TMDR &= ~0x08; /* Timer 3 PWM off */
	        }
	        else
	        {
	          if( KeyToggle() )
	          {
	            ITU_GRB3 = PWMFREQ + 1; /* OP03 Fast */
	          }
	          else
	          {
	            ITU_GRB3 = PWMSlowTarget1; /* OP03 Slow */
	          }
	          ITU_TMDR |= 0x08; /* Timer 3 PWM on */
	        }
	      }
	      break;

	    case Key_L1: /* MAN */
	      if( !Ip.I.IP09 ) /* net cut sensor open */
	        {
	        KeyOp.L = O02; /* OP06 Net On */
	        }
	      break;

	    case Key_L2:
	      KeyOp.L = O11; /* OP11 Baler Close */
	      break;

	    case Key_R2:
	      KeyOp.L = O12; /* OP01 Baler Open */
	      break;

	    case Key_L3:
	      KeyOp.L = O15 | O07; /* Floor Up (Reel Up & Diverter1) */
	      break;

	    case Key_R3:
	      KeyOp.L = O16 | O07; /* Floor Down (Reel Down & Diverter1) */
	      break;

	    case Key_R4:
	      if(!IP01) /* check table position  */
	        {
	        DispenserPosError = 1;
	        }
	      else
	        {
	        KeyOp.L = O08; /* OP08 Tip Up (Tip Off) */
	        }
	      break;

	    case Key_L4:
	      SafetyCount = 0;
	      KeyOp.L = O09; /* OP09 Tip Down (Tip Return) */
	      break;

	    default:
		  if( SpeedChanged == 1)
		  {
			 SpeedChanged = 0;
		  }
	      break;
	    }	  
    }

  if( ( ((KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std))
		  && ((key & ~KeyMask) != Key_S3) ) || ((KnivSystem == RELIEF_VALVE) && ((key & ~KeyMask) != Key_S4)) )   /* Fwd */
    {
    ITU_GRB3 = 0;      /* off all the time */
    OP03 = 0;
    ITU_TMDR &= ~0x08; /* Timer 3 PWM off */
    }


  if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select)) /* Iss-124 */
  	{
		if( !Ip.I.IP08 && (Ip.L & 0x000fff00) ) /* stop beeps if all digital i/ps are open */
			{
			SetBeepType( BT2 | BP1, TBEXT, 1 ); /* 100/100ms On/Off, Ext, 1 Count */
			}
  	}
  else
  	{
  	if( !Ip.I.IP08 && Ip.I.IP06 )
  		{
  		SetBeepType( BT2 | BP1, TBEXT, 1 ); /* 100/100ms On/Off, Ext, 1 Count */
  		}
  	}

  ITU_TIER0 &= ~0x02;        /* Timer Capture Int B off */

  Op.L = KeyOp.L;
  }

if( (NetCheck || (NetWarnCanc & 0x02)) 
&& !UnBlockStatus && Ip.I.IP09 ) /* net cut sensor closed */
  {
  if( NetCheck )
	NetWarnCanc |= 0x04;
  
  NetCheck = 0;
  if( !TableOccupied )
    {
    if( UnBlockStatus == 3 )
      {
      TransferNow = 2;
      }
    else
      {
      TransferNow = 1;
      }
    }
  }

if( !(Tipping || OMS_TIP) && (DispenserStatus == 1) )
  {
  SeqOp.O.OP13 = 0;
  if( OP13_On && Op.O.OP03 )
    {
    Op.O.OP13 = 1;
    }
  }
else
  {
  OP13_On = 0;
  }

if( ExtPower )
  {
  Op.O.OP14 = 1; /* turn output 14 on for 12v supply */
  }

if( !key && ((KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std)) ) /* Iss-101 change */
  {
  if( Kniv1Pres > (Korean? KoreanPresBar:KnifePressureBar) )
    { 
  	WasHigh |= KB_KNIVES11;   	 	
    }
  else
    {
    WasHigh &= ~KB_KNIVES11;
    } 

  if( Kniv2Pres > (Korean? KoreanPresBar:KnifePressureBar) )	
    {
    WasHigh |= KB_KNIVES12; 	
    }
  else
    {
    WasHigh &= ~KB_KNIVES12;
    } 
  }

if( !key && ((KnivSystem == x23_Std) || (KnivSystem == x23_Select) || (KnivSystem == x25_Select) || (KnivSystem == x25_Std)) )
  {	
  TempKeyOp = 0UL;
  }


/* Iss-103, OP10 designated as 'Additive enable' */
/*
if( AutoMan && AdditiveEnOp && (KnivSystem == RELIEF_VALVE) )
  {
  Op.O.OP10 = 1; 
  }
*/

if( AutoMan && AdditiveEnOp )
  {
  Op.O.OP01 = 1;
  }


/* manual transfer delay always, or manual transfer pause once set */
if( (MTDchk > 1) || (Facts[DelPul[DIVDEL]][0] == SL_MANUAL) )
  {
  pt = &FA[DelPul[DLYOGH]];
  if( *pt < 250 ) /* delay running */
    {
    switch( ManTransDelay )
      {
      case 0:
        ManTransDelay = 1;
        MTDcnt = 30;
        break;

      case 2:
        ManTransDelay = 3;
        MTDcnt = 30;
        MTDchk = 3;
        *pt = 0; /* set for action */
        break;
      case 3:
        break;

      default:
        *pt = 200; /* reset */
        if( MTDcnt >= 30 )
          {
          MTDcnt = 0;
          SetBeepType( BT2 | BP1, TBOTH, 1 ); /* 100/100ms On/Off, Ext, 1 Count */
          Here[2] = 1;
          }
        else
          {
          MTDcnt++;
          }
        break;
      }
    }
  else
    {
    ManTransDelay = 0;
    if( MTDchk > 2 )
      {
      MTDchk = 0;
      }
    }
  }

if( MTDcnt && (ManTransDelay == 0) )
  {
  MTDcnt--;
  }

Facts[DelPul[AUTOTP]][0] = AutoTip;

if( IndexTable )
  {
  Op.O.OP17 = 1;
  }

/* O17 is the buzzer output so needs pulsing 300ms on / 300ms off */
if ((Op.O.OP17) && (BuzzerTimer>2))
	{
		Op.O.OP17 = 0; /* force the output to off for the second half of the BuzzerTimer cycle */
	}


TestOp = Op;

/* turn on Outputs */
OP01 = Op.O.OP01;
OP02 = Op.O.OP02;
OP03 = Op.O.OP03;
OP04 = Op.O.OP04;

latch1_out = Op.C[2]; /* OP05-12 */
latch2_out = Op.C[3]; /* OP13-20 */

/* ###test */
/*P9DR &= ~0x02;*/

/* ###test */
/*
ctime = (t0_high * 0x10000UL) + ITU_TCNT0; 
if( ctime > ltime )
  {
  lastcall = (ctime - ltime) / 2000UL;
  if( lastcall > maxcall )
    {
    maxcall = lastcall;
    }
  ltime = ctime;
  }
else
  {
  ltime = ctime + 0x10000UL;
  }
*/
}


void CheckIndexing(void)
{

/* Check IP01 closing while indexing outside display loop
   to catch short pulses */

if( (IndexTable == 1) && IP01 )
  {
  IndexTable = 0;
  CapB0 = 0;
  ITU_GRB3 = 0;       /* off */
  ITU_TIER0 &= ~0x02; /* Timer Capture Int B off */
  OP03 = 0;
  ITU_TMDR &= ~0x08;  /* Timer 3 PWM off */

  if( (ResumeFrom == Zone04) && !NetCheck && Ip.I.IP04 ) /* TipUp */
    {
    if( TableOccupied )
      {
      ResumeFrom = 0xaa;
      }
    else
      {
      ResumeFrom = 0xab;
      }
    }
  }
}

