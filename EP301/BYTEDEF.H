#ifndef __bytedef_h
#define __bytedef_h

/* #define WINDOWS */
/*#define SECONDSERIAL*/

#define RESET_KEY 0x20120530

#define PINTECH 3473
#define PIN_GRANDTOT 868257
/*#define PINTECH 0000 */
/*#define TEST*/
#define SOFTWARE 301 
#define ISSUE 150 /*20140422*/

/*******************************************************************************************************************************************************/
/* 		Iss-150  made based on Iss-148
 * 		Changes made by : Keir Egginton 	Date: 2016.09.07
 *
 *		Reverted back to version 148 due to 149 introducing more issues than it fixed.
 *
 *		Changed the ‘Knife Pressure’ default from 0.75 Volt to 0.80 Volt.
 *		The Knife pressures are now the correct value for standard (0.95v) and Selectable (0.80v).
 *		Removed debugging information accidentally left on screen (KTp47 Ks0 KT250).
 *		Improvements made to the ‘Knife Position’ warning:
 *			The warning will now activate when an input opens when both IP6+IP7 are already closed.
 *			The warning remains on the screen when the input closes again.
 *			Switching to MAN should clear the warning
 *		Added automatic topup for the knives when set to the ‘Relief Valve’ knife system:
 *			When knives are set to on, OP16 switches on for the duration of the 'chamber closing' after transferring the bale.
 *			When knives are set to off, OP15 switches on for ‘Knives Down’ time.
 *
 *		Can't replicate the issues with the Latvian language.
 *
 */
/*******************************************************************************************************************************************************/
/*
 * 		Iss-148  made based on Iss-147
 * 		Changes made by : Keir Egginton 	Date: 2015.03.04
 *		Changes made using the TR Fusion EP301-147.xls
 *
 *		If the instrument is switched on and IP6 or IP7 is open the 'Knives position' warning no longer appears.
 *		Fixed issue that was encountered while switching the knife selection. (Issue where the outputs wouldn't switch on correctly after knife selection)
 *		Knives sensors need to be closed and then opened in order to trigger knife position warning after knives are lowered.
 *		Text in the technician menu now appears when Latvian language is selected. (Items appear in English as I don't have the Latvian translation)
 *
 */
/*******************************************************************************************************************************************************/
/*
 * 		Iss-147  made based on Iss-146
 * 		Changes made by : Keir Egginton 	Date: 2015.02.06
 *		Changes made using the TR Fusion EP301-146.xls
 *
 *		OP7/OP10 no longer automatically switch on If AnIP4 or 5 go above 'Knife pressure warn'.
 *		The logic behind the knife position warning has been reworked so that the warning appears when an input opens no matter the state of the other input. (This is in x23 & x25 mode where both inputs are used).
			Functions:
			knife_pos_input_6();
			knife_pos_input_7();

 *		The Knife position  warning now remains on screen even if the input closes. it remains on screen until S2 is pressed.
 *
 */
/*******************************************************************************************************************************************************/
/*
 * 		Iss-146  made based on Iss-141
 * 		Changes made by : Keir Egginton 	Date: 2015.02.04
 *		Changes made using the TR Fusion EP301-145.xls
 *
 *		Changed the default 'Korean pressure' value to 0.65 volts
 *		Re-added the Latvian language.
 *		Changed the ordering of the knife systems so that it is correctly retained after the software is updated from versions 128 and earlier.
 *		Added a 1 second beep to 'knife position' warning.
 *		Pressing and holding S3 toggles the value of PWM on OP3 between slow and fast. if S3 isn't pressed for 3 seconds then slow speed is set on next press.
 *
 */
/*******************************************************************************************************************************************************/
/*
 * 		Iss-141
 * 		Changes made by : Joel Ravazzolo 	Date: 20140423
 *		Changes made using the TR Fusion EP301-139 ver2.xls
 *
 *		2 year major Bug and probably present in ISOCAN, caused by the film break.
 *		When this happened, 'SavedCountCur' would save the number of wraps to add to the bale after the break.
 *		Because it did not reset after wrapping, this caused the tipping and transfer not to occur.
 *		'SavedCountCur' did however reset when Key_F1 was pressed unsolving the problem for the user.
 *
 *		The bug has been fixed, by automatically resetting 'SavedCountCur' before auto-tipping.
 *******************************************************************************************************************************************************/
/*
 * 		Iss-139
 * 		Changes made by : Joel Ravazzolo 	Date: 20140307
 * 		Changes made using the TR Fusion EP301-138.xls
 *
 * 		IP10 sequence made more secure for OP03 apparantly not turning off.
 *
 * 		Bale design modification
 *******************************************************************************************************************************************************/
/*
 * 		Iss-138
 * 		Changes made by : Joel Ravazzolo 	Date: 20140305
 * 		Changes made using the TR Fusion EP301-137.xls
 *
 * 		IP10 sequence with IP01 warning could only be disabled by pressing S2. This was fixed.
 *
 * 		IP09 debounce has been properly fixed. It was reading Ip.I.IP09 (impossible to disable). Delay (FA[DelPul[DELAY7]]) was orred with IP09.
 *
 * 		New design by McHale for bottom of the Base.
 *
 ********************************************************************************************************************************************************/
/*		Iss-137
 * 		Changes made by: Joel Ravazzolo Date: 20140228
 * 		Changes made using CT Fusion EP301-136.xls
 *
 * 		1) Previously, if IP1 opened when button R4 was pressed, OP8 would switch on for ~1 second and then the 'Dispenser position' warning would appear.
 * 		   This has been fixed by removing S2_flag from the if statement in Key_r4.
 *
 * 		2) Previously, if IP1 opened the tipping sequence would start, but after ~1 second the outputs would switch off and the 'Dispenser position' warning would
 * 		   appear. Tipping should not start if IP1 is open.
 *
 * 		3) During tipping if IP1 opens for >0.5 seconds the 'Dispenser position' warning is triggered.  This seemed to work correctly for the first 1-2
 * 		   seconds of the tipping sequence, but after 1-2 seconds the 'Dispenser position' warning was triggered if IP1 opened for a fraction
 * 		   of a second. This was fixed by creating a spedific timer triggered by IP01.
 *
 * 		4) If IP10 closes for >2 seconds then opens again it starts a routine to index the wrapping ring for 1/2 a rotation until IP1 next closes.
 * 		   This routine functions correctly but the 'Dispenser position' warning was triggered and remained on screen until button S2 (ESC) is pressed.
 * 		   This was fixed by disabling S2_flag out of the if statement.
 *
 * 		5) Same problem with Key_S3, fixed with the same solution.
 *
 * 		6)  There were still occasions (~10% of the time) when pressing and holding button R1 did not start the 'Re-wrap' routine i.e. OP3 and OP13
 * 			didn't switch on. When R1 was pressed the intermittent beeps were sometimes slower/different than normal and this seemed to coincide with when
 * 			the routine didn't start properly. This was fixed by adding StartWrapSequence(SWS_WRAP); when R1 was pressed.
 *
 * *************************************************************************************************************************************/
/*		Changes from EP301135 to EP301136 based on the CT FUSION Plus EP301-135.xla
 *		Changes made by: 	Joel Ravazzolo
 *
 *	1)  Previously pressing button L1 before the bale full beeped (before IP8 has opened) had no function.  Also, pressing and holding L1
 *		during the bale full beeped delayed the netting from starting until button L1 was released.  This has been changed so that
 *		anytime L1 is pressed and held netting will be delayed, but netting can also start as soon as button L1 is released (even if IP8 has
 *		not opened).
*******************************************************************************************************************************************/
/*
 * 		Change from EP301134 to EP301135 based on the CT FUSION Plus EP301-134.xls
 * 		Changes made by:	Joel Ravazzolo
 *
 * 		1) The 2 second debounce delay based before the IP09 was moved afterwards in order to carry on with the sequence
 * 		   (Zone04) and stop IP09 having any influence over the sequence.
 * ****************************************************************************************************************************************/

/*
 * 		Change from EP301133 to EP301134 based on the TR FUSION Plus EP301-133
 * 		Joel Ravazzolo 20131212
 *
 *
 * 		1) When IP08 was triggered and IP09 did not close after ~20 seconds, the net warning came on occasionally and the bale opened.
 * 		   This was fixed by taking off the restart of DELAY7 in both zon04 and zone28.
 *
 * *****************************************************************************************************************************************/

/*
 * 		Change from EP301132 to EP301133 based on the TR FUSION Plus EP301-132
 * 		Joel Ravazzolo 20131209

	1) If IP7 or IP6 is open when AUTO is selected the 'Knives position' warning used to appear.  The warning now only appears if IP7 or IP6 goes from
	   closed to open whilst in AUTO.  The warning does not appear if the input is already open when AUTO is selected.

	2) OP8 was removed from the Programmable factors as it was used as a debugging tool.

	3) When Key_F1 was pressed during the Knife warning display (with IP6 and IP7 still open), it would change back to Manual but the
	   TABS would remain as if still in the knife warning (TAB, ESC, TAB, TAB).

 * ******************************************************************************************************************************/

/*
 * 		Change from EP301131 to EP301132 based on the TR FUSION Plus EP301-131
 * 		Joel Ravazzolo 20131206
 *
	1) When IP1 was triggered, the digital delay of swtim > 5 does not actually equal to 0.5 seconds but is almost instant.
	   The delay was increased to swtim > 10 so that the user physcially has about 0.5 seconds debouncing time.

	2) OP09 and OP10 where on when IP09 was switched. These were left in from debugging. These have now been taken off.

	3) Before wrapping in AUTO with HAY or STRAW (after IP08, CHAMBER, closed) there was an infinite beep which could only be
	   stopped by pressing AUTO. This was fixed by stopping the beep in zone18 as zone33 was never triggered by DELYUV.

	4) The 'knife warning' should not be displayed while working in MANUAL. This was fixed by adding another condition.

	5) The 'knife warning' is disabled when OP16 turns on (KEY_S2). If IP6 or IP7 change from closed to open whilst OP16 is
	   on, the warning doesn't reappear as soon as OP16 switches off.

 * ****************************************************************************************************************************/

/**
 * 		Changes from EP301130 to EP301131 based on the CT Fusion Plus EP301-130 report.
 * 		Joel Ravazzolo 20131128
 *

 	 1) Currently if IP1 opens during a tipping sequence the tip sequence will be stopped. This has has now been changed so that IP1 is triggered
 	    the 'Dispenser position' warning appears and the sequence stops after have been triggered for more that 0.5 seconds.

 	 2) If IP1 opens for >0.5 seconds during tipping the tipping sequence will stop and the 'Dispenser position' warning is shown.  The
 	 	'Dispenser position' warning now remains on the screen even if IP1 closes again.  Pressing button S2 (ESC) cancels the warning.

     3) When the net is cut, IP9 closes to 0v and this is the signal for the transfer sequence to begin.  In reality, as the net is cut, IP9 has
     	a tendency to bounce causing IP9 to open/close several times before it settles in the closed position.  This can occasionally cause the
     	sequence to stall.  To avoid this a 2 second debounce has been added when IP9 closes.  Any opening/closing of IP9 within this 2 second
     	period is ignored.
 *
 ****************************************************************************************************************/

/*
 * 		Changes from EP301129 to EP301130 based on the TR Fusion Plus EP301-129 report.
 * 		Joel Ravazzolo.
 *

 1) 	When button S1 (knives down) or S2 (knives up) is being pressed and IP7 goes from closed to open for >1 second the warning now does not
 	 	appear. (MANUAL MODE for the x23_Std and x25_std).

 2) 	When button S1 (knives down) or S2 (knives up) is being pressed and IP7 goes from closed to open for >1 second the warning now does not
 	 	appear. (MANUAL MODE for the x23_Select and x25_Select).

 3)		When button S1 (knives down) or S2 (knives up) is being pressed and IP7 or IP6 goes from closed to open for >1 second the warning now does not
 	 	appear. (MANUAL MODE for the x23_Std and x25_std).

 4) 	When button S1 (knives down) or S2 (knives up) is being pressed and IP7 or IP6 goes from closed to open for >1 second the warning now does not
 	 	appear. (MANUAL MODE for the x23_Select and x25_Select).

 5) 	The 'Knife position warning' only appears if the instrument is on the 2nd main screen.  If IP6 or IP7 open for >1 second whilst on the 1st
 	 	main screen the warning doesn't appear until S4 is pressed to cycle to the 2nd main screen.  The 'Knife position warning' now appears on
 	 	either screen.

 6) 	On the knife system selection screen the serial number for the 'x25 Std' option has chaged to 656841+ (before it showed 654556+).
 7)  	On the knife system selection screen the serial number for the 'x25 Select' option has chaged to 656841+ (before it showed 654556+).

 8) 	On the main screen the second knife pressure (AnIP4) in the bottom right info box is now not shown and is blank.

 9) 	On the main screen the pressure display for both knife systems (AnIP4 and AnIP5) is now shown in the info box on the right hand side.

 * ********************************************************************************************************************/

/*EP301128 => Ep301129
J.Ravazzolo (Software change report TR Fusion Plus EP301-128.xls)

1)	Change warning image to the requested image saved in
	Q:\Product information\Current Products\OEM\McHale Fusion Plus (341)\Development Documents\Specs\Screens\Screens 14_08_06\Twin knife screens
	as ‘MAIN AUTO warn knives3.pcx’

2)	Change technician pin code to 3475

3)	If 11/13 have been selected then AnIP4 is ignored. Same for 12 knives, AnIP5 is ignored.

4)	Random text removed from Digital Inputs diagnostic screen

5)	Software bug fixed when initiating bale wrap. Less than 50% of the time it took 6 seconds to turn OP3 and OP13 on. Now it turns on everytime
	under 2 seconds.

6)	Knife system option screen modified as requested using ‘Knife system menu5.pcx’ as main reference under
	Q:\Product information\Current Products\OEM\McHale Fusion Plus (341)\Development Documents\Specs\Screens\Screens 14_08_06\Twin knife screens.

7)	Pressure sensing knife option named to x23 Std

8)	Selectable knives renamed to x23 Select

9)	New knife option named as x25 Std

10)	Knife option x25 Std given same functionality as x23 Std (Pressure sensing) but symbol over S1 should move between 0 and 25 rather than 0 and 23

11)	New knife option named as x25 Select with same functionality as x23 Select but  with the following changes:
	a.	S1 should be able to scroll through 0, 13, 12 and 25
	b.	S2 symbol changed to 13 rather than 11

12)	If at any time IP7 is triggered from closed to open for > 1 second the ‘FUSION warning knife position.pcx’ should be shown
	(DURING MAN MODE using x23_STD and x25_STD).
	a.	S2 shall be the only button to exit the warning
	b.	If S1 or S2 are pressed while IP7 goes from close to open then the warning shall not appear.

13)	If at any time IP6 or IP7 are triggered from closed to open for > 1 second the ‘FUSION warning knife position.pcx’ should be shown
	(DURING MAN MODE using x23_Select and x25_Select).
	a.	S2 shall be the only button to exit the warning
	b.	If S1, S2 or S3 are pressed while IP7 goes from close to open then the warning shall not appear.

14)	If at any time IP7 is triggered from closed to open for > 1 second the ‘FUSION warning knife position.pcx’ should be shown
	(DURING AUTO MODE using x23_STD and x25_STD).
	a.	S2 shall be the only button to exit the warning
	b.	If S1 is

15)	If at any time IP6 or IP7 are triggered from closed to open for > 1 second the ‘FUSION warning knife position.pcx’ should be shown
	(DURING AUTO MODE using x23_Select and x25_Select).
	a.	S2 shall be the only button to exit the warning
	b.	If S1 is pressed while IP7 goes from close to open then the warning shall not appear.
	c.	 pressed while IP7 goes from close to open then the warning shall not appear.

********************************************************************************************************************************************/

/*
  EP301127 => EP301128
  I.Moody (Software change report CT Fusion EP301-127.xls)

  1 - #1. New main screen graphics to reflect the new design of machine.

  2 - #2. Overspeed default changed to 20 Hz.

  3 - #3. OP17, Buzzer, now pulses 300ms on, 300ms off when active.

  4 - #4. Knife top-up during netting removed.

  5 - #5. Crop pickup animation added to main screen.

*/


/*
 Iss 127 based on Iss 126 20120531.		ZW
*/

/*
 Iss 126 based on Iss 125 20120530.		ZW

	Moved if( (PauseZone == 1) && (TransferSeqPaused == 1) ){} outside of other if else blocks in Zone04.
	Also added if( (PauseZone == 0) && (TransferSeqPaused == 0) ) check before StartTransfer() function.
*/

/*
 Iss 125 based on Iss 124 20120529.		ZW

1	changed PLSPAS from 2 to 3.
3 if( TransferSeqPaused ) check added in Zone16.
*/

/*
 Iss 124 based on Iss 122 20120502.		ZW
1		Added Zone71.
 		OP11 in zone71 only turns on during wrapping (i.e. when OP03 is on ).
3 	'Additive Enable' OP10 replaced by OP1.
5 	'WrapSeq' and 'O_Ps' added s that seq can be stopped by pressing Key_R1.
10  PauseZone, SeqPaused and FlashLedR2 added so that the transfer sequence can be
		stopped by pressing Key_R2.
*/

/*
 Iss 122 based on Iss 113 - 20101015		ZW

 Added a new programmable factor in the wrapping section of technician menu called 'Tip bale French'. Default = 4.0 seconds.
 When language is set to French, the software uses 'Tip bale French' time rather than 'Tip wrapped bale'.

*/

/*
 Iss 113 based on Iss 112 - 20101015		ZW
 
 KnivSytem == Selectable Knives....
 
 The default KnifePressure for Selectable KnivSystem has been changed to 0.75V. It remains 
 0.95V for PressureSensing KnivSystem.

 Commented out (CanStatus == CSTATUS_OK) in 010 to fix a bug in CT EP301-112.xls as CANOpen is no longer used. 
*/

/*
 Iss 112 based on Iss 111 - 20101015		ZW
 
 KnivSytem == Selectable Knives....
 
 Minor change in the MonitorKnives() routine. At KnivMonitorStage==2 voltage on both 
 AnIP5 and AnIP6 does not have to be below the threshold before OP15 can come on. If voltage on 
 either of the two inputs is low, OP15 comes on.   
 
*/

/*
 Iss 111 based on Iss 110 - 20101013		ZW
 
 In the 'Knife System' menu added a new option called 'Selectable Knives'. 
 If Knives System is set to 'Selectable Knives' then the knife system operates in the same way
 as in EP301-108 but with the following changes:
 AnIP4 is used for 12 knife pressure (instead of YDAC CAN sensor).  
 IP6 is no longer used as safety input. To access AUTO IP1, IP4 or IP8 has to be closed. If any of these inputs
 open, the instrument stays in AUTO and not return to MAN until the operator switches to MAN or the instrument 
 is turned off.
 IP7 designated as '11 knives sensor'. If IP7 is closed then the knife symbol for 11 knives appears solid.
 IP6 designated as '12 knives sensor'. If IP6 is closed then the knife symbol for 12 knives appears solid. 
 
*/

/*
 Iss 110 based on Iss 109 - 20100927		ZW
 
 If the knife system is set to x23_Std, OP07 now does not come on when the chamber (IP08)
 is closed (011 -> Zone38).
*/

/*
 Iss 109 based on Iss 108 - 20100903		ZW
 
 The scrren for selecting the knives system is now accessed by pressing and holding the 
 Key_F2 (menu button) for > 5 seconds (010, 001).  
 Removed the 'Twin knife' option from the knife system menu (010, 011).
 In the knife system menu there is a new option called 'Relief valve'.  Default will be 'Pressure sensing'. 
 If the knife system is set to 'Pressure sensing' then it functions as it currently should. 
 If knife system is set to 'Relief valve' then the knives function as they do in EP301-103
 
*/

/*
 Iss 108 based on Iss 107 - 20100903		ZW

 There are two knife top-up routines: a) during netting of every bale and b) when a new 
 knife bank is selected using Key_S1.
 
 Previously O15 used to switch on for 5 seconds for both the topup routines. Now this 5 second 
 is reduced to 2.5 seconds for topup during netting. For the topup on a new knife selection O15 still
 comes on for 5 seconds (010).
 
 The 'knife pressure too high' warning is disabled at all times during the either of the above 
 mentioned knife topup routines.
 
 If the knife pressure goes too high during the floor topup a the start of wrapping (where OP15 switches on 
 after IP8 is closing), OP7 will not switch on. Only the 'knife pressure too high' warning will appear.  
 
 Technician factor 'Floor up' changed to 6 seconds. 
*/

/*
 Iss 107 based on Iss 106 - 20100831		ZW
 
 Added new variable 'SpeedChanged' in KeyToggle() routine (000) to fix the bug of fluctuating 
 PWM on pressing Key_S3 for a second time if( swrel < 5 ).
 
 Knife position is now topped up for every bale rather than just the first bale. FirstBaleAfterKniv11/12/23
 now removed.
 
 A new knife monitoring routine MonitorKnives() has been added(011). It works only once after a 
 knife slection has been made by pressing Key_S1. This routine is identical to the Knife topup
 routine(010) during netting of each bale that was added in Iss-105. 
 
 Added new bit variable 'InitialRoutine' so that during kniv monitoring knives up routine can not start 
 before kniv down has finished compleltely(010).
 
 Bit variables 'Kniv1PresHigh' and 'Kniv2PresHigh' have been changed to byte variable to enable them to 
 attain a value of 2 (010).
 
 For x23_Select system the 'Knife Pressure' default has been changed from 0.95 to 0.79 volts.
 001 -> KnifeSystem(). 
*/

/*
 Iss 106 based on Iss 105 - 20100715		ZW

 Moved the extra knife top-up routine from sequence table to SetOutput()->(010) because it was disturbing
 the sequence.
 Similarly the two new lines to turn on OP07/10 when 'Knife1/2 Pressure too High' appear, have been 
 commented out and implemented in SetOutput()->(010). 
 
*/

/*
 Iss 105 based on Iss 102 - 20100715		ZW

 Added a new programmable factor 'Korean pressure' in the Top-up/floor section of the tech menu (000, 005).
 If Korean language is selected then 'Korean pressure' is used as a target instead of 'Knife pressure' (010) .  
 
 Pressure Sensing...
 IP07 allocated as Knives position sensor. If IP07 is closed then knives
 are in 'up' working position.
 
 Twin Knives...
 After a CAN warning, pressing ESC now does not stop executing CANfunctions(). It only cancels the warning.
 
 Added a programmable factor 'Korean pressure' in the Top-up/floor section of the technician menu. Default = 0.57 volts
 
 If Korean language is selected then the 'Korean pressure' value is used as the target instead of 'Knife pressure'.
  
 Added four new lines in the sequence table for a knives top up routine once OP02 turns off in AUTO. Normal 
 knife routine is disabled (DisableKnifeOperation=1) during this knife topup routine(bytedef, 010, 011->Zone53/51/52/54).
 
 Added two new lines in the sequence table to turn on OP07/10 when 'Knife1/2 Pressure too High' appears(bytedef, 010, 011). 
 Normal knife routine is disabled (Kniv1/2PresHigh = 1) during this routine(bytedef, 010, 011->Zone55/56).
*/

/*
 Iss 102 based on Iss 101 - 20100524		ZW
 
 Added a new screen called 'Knife System' that appears when the down button is pressed and held
 on the Machine Menu screen. It allows the operator to select between 'Pressure sensing knives' 
 and 'Twin knife system'.  Default = 'Pressure sensing knives'.  
 
 If 'Twin knife system' is selected the software functions as it currently does. 
 If 'Pressure sensing knives' is selected then the following changes apply:
 The following inputs and outputs are used for 'Pressure sensing knives'. Selecting between 0 and 23 knives 
 on 'Pressure sensing knives' is the same as selecting between 0 and 11 knives on the twin kniv system.
 Knives up = OP16 + OP7
 Knives down = OP15 + OP7
 Floor up = OP16
 Floor down = OP15
 Knife pressure = AnIP5
 
 If 'Pressure sensing knives' is selected than user can only slelect between 0 and 23 knives.
 When 0 is selected it operates as it currently does.  When 23 is selected it functions the same 
 as when 11 is selected if 'Twin knife system' is selected.
 
 If 'Pressure sensing knives' is selected  the 'No CANBUS Comm.' is inhibited becasue HYDAC CAN sensor 
 will not be connected, therefore the software does not look for it.
 
 */

/*
 Iss 101 based on Iss 99 - 20100510		ZW
 
 'Floor up' default changed to 5.0 seconds( bytedef ).  
 During a 'Knife pressure too high' error the beep frequency reduced to 1 Hz (010, changed from BT1 to BT7).
 In MAN pressing S1 turns OP7, 10 & 16 on, when released OP16 turns off 0.5 seconds after OP7 and OP10 (010)
 In AUTO pressing S1 when knives are set to 0 turns on OP7, 10 & 16. When S1 is released released OP16 
 turns off 0.5 seconds after OP7 and OP10 (010). 
 Floor top up should not happen (i.e. O15 does not come on) if O07 or O10 is on (Zone39). 
 If AnIP5 > target when S2 is pressed, OP7 and OP15 stay on for the duration of the key press even if 
 AnIP5 drops below target and then goes above it again. WasHigh is now set/cleared only when no key is pressed (010). 
 Same for S3 and OP10 and OP15.
 If there is a 'CAN communication' error, or 'NO CAN CHIP FITTED' error pressing S2 sets CANWarnCanc = 1. 
 OP4 can turns on only when CANWarnCanc == 2. CANWarnCanc is set to 2 when key is released after cancelling a CAN alarm.
 If Canstatus == CSTATUS_NOCHIP2, 'NO CAN CHIP FITTED' warning is dispalyed(010 -> (InfoSel == 26) ).

*/

/*
 Iss 99 based on Iss 98 - 20100408		ZW
 'Floor up' default changed to 4.0 seconds.
 'Floor down' default changed to 4.0 seconds
 'Knives down' default changed to 4.0 seconds.
 'Knives pressure warning' default changed to 1.38 volts.
 Functions of OP15 and OP16 swapped.
 The knives diverter valves (OP7 & 10) always come on 0.5 seconds before OP15 or OP16( 010 ).
 In MAN mode when the target pressure is reached on AnIP5 or the CAN sensor, prevously only 
 the diverter( OP7 or OP10 ) turned off.  Now OP15 also turns off when the target pressure is reached( 010 ).
 At the start of unblock routine OP07, OP10 and OP15 are turned off( 010 ). Also the Knives functions
 (kniv11, kniv12, kniv23) are disbaled( 010 -> !UnBlockStatus ) during unblock sequence so that they cant switch off 
 the unblock outputs (i.e. OP15 and OP16). DLYU05 now used at the end of reset floor sequence (just for a gap).
 When the chamber door (IP08) closes, OP15 turns on for 'floor up' time (i.e. DLYU06, a duplicate of DLYU04).
 When pressing S1 to scroll through the knives setting, the symbols change immediately with each 
 button press, however the knives only move once the button has not been pressed for 2 seconds( 010 ).
 KeyS1Delay now incremented every 10th of a second (INT). 
 
*/

/*
 Iss 98 based on Iss 97 - 20100330		ZW
 Minor bugs mentioned in TR Fusion EP301-097(3).xls fixed.
 */
 
/*
 Iss 97 based on Iss 96 - 20100315		ZW
 
 OP16 is now 'Floor Up' (was previously 'knives up)
 OP15 is now 'Floor Down' (was previously 'knives down)
 OP7 is now 'Knives 1 Diverter' (was previously 'floor diverter')
 AnIP5 is now used for 'Knives 1 Pressure'.
 A HYDAC pressure sensor is used which turns the pressure into a CAN signal. 
 This pressure is known as 'Knives 2 Pressure' and the signal is called CAN AnIP1. 
 The Key_S4 will show info as shown in W341-014.xls -> MainScreen.
 The 'S' buttons on the main screen have new functions as decribed in W341-014.xls -> MainScreen(010).
 The chopping knives system has been changed so that the bank of knives is split into 2 sections 
 (knives 1 = 11 knives, knives 2 = 12 knives) so the operator can select 0, 11, 12 or 23 knives.  
 Full description of the operation is in W341-014.xls -> Knives_Floor. 
 Added three new programmable factor in the top-up/floor section of the technician menu (bytedef,000,005):
 'Knife Pressure', default = 0.95 volts.
 'Knife Pressure Warning', default = 1.30 volts.
 'Knife Down Pressure', default = 0.20 volts.
 If the signal on AnIP5 > 'Knife pressure warning' then 'KNIFE 1 PRESSURE TOO HIGH' warning is shown(010).
 If the signal on CANAnIP1 > 'Knife pressure warning' then 'KNIFE 2 PRESSURE TOO HIGH' warning is shown(010).
 The unblock routine has been changed so that when Key_R3 is pressed and held to start the 
 unblocking sequence only OP15 comes on for 'Floor down' time (bytedef).
 When Key_L3 is pressed to reset the floor position, only OP16 should turn on for 'Floor up' time(bytedef). 
 
*/

/*
 Iss 96 based on Iss 95 - 20100315 		CP
 
 added CAN routines in files EPL_CAN.C/EPL_CAN.H
 
 added ustoc union to decode short to char without multiplying/dividing/shifting (bytedef)
 IRAM renamed to H8RAM (bytedef/lnk.xcl)
 main(), H8RAM now initialised to zero at startup (000)
 can_hs_read now split int low/high parts for CAN chip test when pin wait is off (bytedef)
 Added CAN routines to check CANOpen sensor HDA 4748-K-0250 and other similar sensors (can)
 sensor is set to sent a reading every CM_REPEAT_TIME which is currently 100ms (bytedef)
 interrupt [IRQ_5], CAN_controller_int(), 'CAN general interrupt' added (int)
 interrupt variables for CAN interrupt placed in H8RAM (bytedef/int)
 added CanMessage structure for receive message buffer and Can variables (bytedef)
 can message buffer length must be a power of 2 for pointer mask to work correctly (bytedef/int/can)
 CanCurrentTime incremented in CMI interrupt (int)
 Pressure is calculate from a moving average of PRESSURE_AVERAGE_LIMIT readings (can) 
 test display lines added, shows pressure or error & initilisation count, count stays at 1 unless
 errors restart CAN bus and sensor (010) 
 
*/

/*
 Iss 95 based on Iss 94 20100312.
 
 Tip Return+ default changed to 4 seconds (bytedef).
 
 In Iss-094 O03 was not ramping down because Zone10 was never reached. The reason being this line.
 
 PULSER, DELYRS, DELYW1,          NoneOn,      NoneOff,   Zone09,  O_S1, DelayOrPulseWait | WaitForWdl,
 
 PULSER required decrementing with every pulse on IP01 whereas in above statement it cant happen before 
 DELYWI is executed.
 So it has been replaced with the original stamenet in the last version:
 
 PULSER, DELYRS,      0,          NoneOn,      NoneOff,   Zone09,  O_S1, DelayOrPulseWait,
 
 Tipping sequence has been reversed to as it was in Iss-086. 
 */

/*
 Iss 94 based on Iss 93 20100305.
 
 Overspeed default changed to 7.7Hz( bytedef ).
 
 IP2 frequency is now monitored from Zone47( MonitorFrequency = 1 ) to 
 Zone12( MonitorFrequency = 0 ).
 
 DELYNT made programmable and moved to technician -> Baler full/net menu (bytedeft, 005).
 */

/*
 Iss 93 based on Iss 92 20100218.
 
 Overspeed default changed to 7.4Hz( bytedef ).
 If IP01 opens during the first 3 seconds of a Tipping sequence, the sequence 
 is stopped and DispenserPosError is set to 1 to give the relevant alarm.
 
 */

/*
 Iss 92 based on Iss 90 20091214.
 
 Changes made in screen11() and set_language() in 001 to fix the bugs when 
 instrument is working in Korean language ( mentioned in CT Fusion EP301-090.xls ).
 */

/*
 Iss 90 based on Iss 86 20090908.
 
 Tipping sequence can only start when Ip10 is open (010 -> OUtputSet() -> KeyR4), (011).
 
 'Tip Wrapped Bale' DELYWX now starts when IP04 opens instead of when OP08 turns on (as previously).
 (bytedef)
 
 Added Hungarian language from Fusion2 Hungarian language 140809.xls.
 
 */

/*
 Iss 86 based on Iss 84 20090630.
 Closing IP10 when previous bale is on the wrapping table and the current one is netted, does not
 start tipping sequence (010).
  
 If there are no pulses on IP2 but there are pulses on IP1 then 'Motor Speed Sensor' error message 
 is displayed (instead of 'SAFETY SWITCH' error) and wrapping stopped (010). 
 
 If there are no pulses on either of IP2 and IP1 then 'Safety Switch' error message 
 is displayed (010).
 
 A new programmable factor in the 'Rotation' section of the technician menu called 'Overspeed' 
 (default = 13.5Hz) has been added.
 
 During wrapping if the frequency on IP2 exceeds 'Overspeed' setting (13.5 Hz) then 'Wrapper Too Fast' 
 warning is displayed and wrapping stopped (010, 011, INT).
 
 After a lube count warning it is now possible to reset the count from the main screen (010).
*/

/*
 Iss 84 based on Iss 83 20090527
 'Net Brake Power' option removed from 'Machine Setup 2'(001) and funcion of OP01 removed from
 netting sequence (bytedef & 011 -> Zone03 and Zone45).
 
 Local variable old_lang added in set_language() to save lang before displaying langugae names.
 Because font EUR/CYR depends on 'lang' it needs to be changed for each language to select the right
 font i.e. EUR/CYR ( 001 -> set_language() ). 
 
*/

/*
 Iss 83 based on Iss 80 20090509
 
 Added Polish, Lithuanian, Italian and Russian. Czeck updated.
 
 After netting and transfer, once the chamber door closes (IP8 closes) it is now possible 
 to start tipping (pressing R4) before the (OP11 turned off) door close overtravel time has elapsed (010).
 
 IN case of a net error warning (If net is applied but there is no pulse from IP9) LED next to Key_R2 flashes
 no matter waring was ignored by pressinf Key_S2 or not (010).   if(NetCheck) {NetWarnCanc |= 0x04;}
 
 Demo Screens added as per EP304.
 
 Unlike in Iss 80 and earlier, DELYFG is not set to DLYU02 for the first bale to have a different first bale.
 (bytedef)  and (011 -> Zone30).
 
 'Net Brake Power' option added in netting sequence. OP1 is used as a brake on the net feed roller. 
 As soon as OP2 (net on) switches off, OP1 (net brake) comes on at 'Net brake power' %PWM (011 -> Zone03). 
 OP1 remains on throughout netting and switches off 1 second after IP9 closes (Zone45). 
  
*/

/*
 Iss 80 20090108
 
 Added Korean language in the form of bitmaps in Iss 77.
  
*/

/*
 Iss 77 20080730
 
 based on issue 71
 
 DELYLM 'Ramp Up' from 1.6 to 3.0 
 DLYU04 'Floor Up' from 2.2 to 3.3
 DLYU03 'Floor Down' from 2.0 to 2.6
 DLYU01 'Knives Down' from 1.3 to 2.0
 DELYBC 'Net On' from 2.2 to 2.8
 
*/
 
/*
 Iss 71 20080424
 
 epl_lan1 now has 14th extra language, as it was only put into epl_lan2 (lan1)
 screen06, 'Reset Defaults' now clears text before updating display (001) 
 
*/

/*
 Iss 70 20080423
 
 added Portugese (lan2)
 increased font pointer table size (f1all)
 corrections made to other languages (lan2)
 
 MAXLANG from 13 to 14 (bytedef) 

*/

/*
 Iss 69 20080407
 
 DELYVW, 'Overshoot Time' from 0.3 to 0.2 (bytedef)

 Language Changes...
  s0351, 'Factors reset to defaults' text now split over 2 lines
  as needed (001)
  
 moved all pointers on menu screens from x = 10 to x = 4 (001/005) 
 all menu text moved form x = 20 to x = 12 (001/005)
 BaleCount x moved from 26 to 12 (001) 
  
 windows startup now clears and displays screen (000)
 screens no longer reset selection to 0 at start up
  so windows language change does not reset it (001/005)
  
 deleted screen05 'Help Line' as it was not shown (proto/001) 
 
*/

/*
 Iss 68 20080327
 
 swedish/norwegian/czech languages updated (lan2)
 
 new display_f1_text() option FRAMED added (bytedef/001)
 main display now displays crop in FRAMED box (010)
 old_crop variable removed as crop not changed in main screen, and
  croptype displayed at startup (010)
 screen13/131, Machine Setup 1/2 text displays altered to accomodate
  different length language strings (001)
  
 added NoPWM variable (bytedef)
 added screen076(), 'Diagnostics - No PWM' option (001)
 
 ResetSequenceFactors(), NoPWM defaults set here,
  PWMSlowTarget1/2,PWMmax/min set to 78/78,81/78 (011)
  
 PULSET, Zone11, no longer sets O13, just O05 (bytedef)
 Zone11 now sets O13 if NoPWM is clear (011)
 
 NoPWM sets infoset to 20 (010)
 WarningBitmap for 'No PWM' warning added (lan0/bm_sym) 
 
*/

/*
 Iss 67 20080320
 
 additional languages added + new tranlations (lan2)
 MAXLANG from 12 to 13 (bytedef) 
 set_language() updated to allow for additional languages (001)
 
 DIVDEL range changed from 2-5 to 0-2, losing 'DELAY' option (bytedef)
 ShortLong[] reduced to 3 options 'DELAY' option removed (bytedef)
 added #defs for SL_SHORT/LONG/MANUAL to match ShortLong (bytedef)
 updated DIVDEL option to remove 'DELAY' option (010/011)
 
 CheckIndexing() now no longer stops indexing if !IP04, TipUp open (010)
 
*/

/*
 Iss 65 20080131
 
 Filmbreak not working
 FilmBreakCheck(), switch using i, not DelPul[FILMBK] (011)
 modified draw_line() INV added, pointers added (002)
 modified draw_box) INV changed, clips corners (002)
 
*/

/*
 Iss 64 20080118
 
 Slowing of sequence not happening correctly at end of wrap?

 changed PWMSL2, ' Slow Speed PWM ' from 37 to 35 (bytdef) 
   
 write_bitmap routine was taking 53.6ms to copy FUSIONMAIN, 107x64 pixels
  to display buffer

 bitmap routines rewritten to use pointers, saves >12ms on above time (002)
 bitmap routines rewritten to use mask look up rather than left<</>>right shifts
  as H8 was looping 8 times for an 8 bit shift, saves >12ms on above time (002)
  
 write_bitmap time reduced form 53.6ms to 26.8ms for FUSIONMAIN  
 
 original display_screen() restored, as no improvement was noticed with modified one (002)
 
 main_loop modified to speed up changes to bitmaps FUSIONMAIN now split into
  7 different sections that are not always redrawn (010)
  
 chamber bitmaps now all the same width (baler)    

 
 added index array DelPul[FCLAST] to speed search for delays (bytedef)
 added index array SwLook[SWLAST] to speed search for switches (bytedef)
 setup in SetLookUps() (011)
 modified check routines now use lookup DelPul[DELAY]/SwLook[SWITVH] rather
  than loop through table each time to find Tag (011)
 
 lookups now reduce OutputSet time from 60ms to 7.6ms (010)

 OutputSet() modified to include setting outputs and latches (010)
 main loop now only sets outputs and latches if OutputSet() not called (000)
 OutputSet() now called called before display_screen() (000)
 
 maximum delay between OutputSet() calls from 200ms to 25ms while wrapping
 
 KeyCheck() called before eack OutputSet() call (000) 

*/

/*
 Iss 63 20071120
 
 -01-
  pilot error, remote handset is disabled if SIOdata set, 'Serial Logging' on,
  so Key_BL/IP11 will not start tip (xxx)
 
 -02-
  if MS_CHAMBEROPEN or TransferBale, close baler topup is now disabled (010)
  Key_R2, if TableOccupied only TransferBale is used for restart check, MS_CHAMBEROPEN check removed (010)
  net sequence now not reset if TransferBale set and IP08 closes (010)
  
 -03-
   DELYWX, 'Tip Wrapped Bale' default from 4.0 to 5.0 seconds (bytedef)
*/

/*
 Iss 62 20071112
 
 based on Iss 60, so no demo mode
 
 modified screen17 to use table for minimum/max values (005)
  to do -  use table for text (PF.name) and format (PF.type)
 
 changed contrast/brightness box sizes so EMPTY box uses same x_co as FULL box (005)
 
 key references now use spec notation, Key_S1/2/3/4 not Key01/2/3/4 (bytedef/010/011/HDW)
 
 SetLedData() modified to use LED name references (011)
 
 -01-
  Zone04 if Tipping then PauseWhileTipping is set (011) 
  
 -02-   
 main_loop() is now only defaulted to if !BootRun && (demi_secs > 99) && (window != main_loop) (000)

 -03-
 KeyCheck() now checks BootRun rather than startup before checking hand controller (hdw)
 Key_TL/TR/BL/BR now defined (bytedef)
 Key_TL/TR/BL/BR now set in KeyCheck() (hdw)
 KeyBL now starts tip in auto (010)
 
 -04-
 O09 no longer comes on in auto sequence during chamber open, (on at DLYODE, off at DLYOFG) (bytedef)

 -05-
 DELYYZ, 'Tip Return+' default change from 0.2 to 3.0 seconds (000)
 
 -06-
 Zone16 now set when RSWTCH, Tip Sensor closes, rather than end of DELYYZ, 'tip up+' (bytedef)
 
 -07-
 added DELYHI to enum SeqVars (bytedef)
 added DELYHI factor to SeqFactors, non programmable, default 10.0 seconds (bytedef)
 DELYHI starts when OP11 turns on in sequence, after DELYGH (bytedef)
 when DELYHI completes Zone44 is set (bytedef)
 DELYHI canceled by RSWTCA in Zone06 (011)
 added MS_CHAMBEROPEN & TransferBale (bytedef)
 if Zone44 set the sequence is stopped, MS_CHAMBEROPEN set and MS_TRANSFER & Transfering cleared (011)
 MS_CHAMBEROPEN cleared by SEQ_INIT in ResetSequenceFactors(), and in Zone01/05/14 (011)
 if in auto and MS_CHAMBEROPEN and IP08 closed, Chamber Closed switch set TransferBale to 1 (010)
 SetLedData() now flashes LED04, next to Key_R2, if TransferBale set (011)
 pressing Key_R2 when MS_CHAMBEROPEN and TransferBale set will start bale wrapping (010)
 
 -08-
 ResetSequenceFactors(), SEQ_INIT now sets SeqOp.L = 0 rather than leaving output O02 & O08 on,
  as O02 was being left on when switching from auto to manual to auto (011)
 
 -09-
 CMI interrupt sends TestIp/Op as serial data every 0.1 seconds (int) 
 added s0380, 'Serial Logging'
 added SIODAT to enum SeqVars (bytedef)
 added SIOdata, set to SIODAT status in ResetSequenceFactors() (bytedef/001)
 added InpsWide TestIp & OutsWide TestOp (bytedef)
 TestIp = Ip in KeyCheck() (HDW)
 TestOp = Op in OutputSet() (010)
 BootRun added to disable SIODAT routine if boot loader running (bytedef/232/int)
 renamed screen07 to screen071 (proto/001)
 renamed screen08 to screen072 (proto/001)
 renamed screen09 to screen073 (proto/001)
 renamed screen12 to screen074 (proto/001)
 added screen075 to program SIODAT (proto/001)

 MAXFACTOR from 117 to 118
 MAXSEQ from 115 to 116
 
 */

/* Iss 61
 * added simple slideshow bitmaps (bm_demo)
 * added Demo00 screen (001)
 * 
 */

/* Iss 60:
 * Edited film layers postion on main screen.
 */

/* Iss 59:
 * Auto tip default now Off
 * Diagnostic menu string change
 * R2 transfer advance changes.
 * Net error warning given prioriety over 1 disp only
 * Baler full alarm given highest prioriety
 * Film layers symbol changed
 * Pause tipped now 0.1s default
 * Index PWM now 35% default.
 */

/* Iss 58:
 * Switch buzzer off now when netting starts
 */

/* Iss 57:
 * External buzzer now works when IP08 changes not OP08....
 */

/* Iss 56:
 * Added external buzzer on O18 and added programable factor ExtBuzzer
 * for selecting On / Off
 */

/* Iss 55:
 * fix: MS_TRANSFER removed from MachineStatus when alarm cancelled.
 */

/* Iss 54:
 * If L$ pressed for pause tip, ignored if autotip already occured.
 * min pwm value = 33
 * knives down = 13
 * knives up = 23
 * floor down = 20
 * floor up = 22
 * if 0p05 comes on, switches off op06
 * disp pos error flashes key03 & key04
 * after tip/wrap/transfer not complete baler full beep now works
 * changing to auto resets NetCutPosAlarm & NetCutPosNorm
 * unblock warning has priority over 1 disp only
 * 1 disp only mode disabled
 */ 

/* Iss 53:
 * NEW FEATURE
 * Film sensor option added " 1 disp."
 * Means wrapping can be done by one disp with no alarms unless break occurs
 * 1 disp rev count added to wrapping options
 * pauses bale revolving at this point in the wrap cycle for
 * one pulses using O13.
 */

/* Iss 52:
 * 
 * Status LedR2 comes on when bale paused in Manual bale
 * transfer mode
 * Status LEDR4 Now comes on when switched to Auto from Man
 * even without restart
 * Pressing Key_R1 swicthes balerstatus to 3 in Auto mode.
 */ 

/* Iss 51:
 *  
 * Startup screen reduced by 1 second
 * Displays Language screen on startup
 * German Language added
 * Slow down time removed from options
 * Grand total bale count can now pass 999
 * If bale manually transfered RPM now displayed
 * If Autotip on fix added to stop it switching off.
 * Status LEDS added into SetLedData( void )
 */

/* ISS 50: From Iss 40:
 * 
 * Changed Film Check Count Default to 9.
 * IP04 ignored while transfering as
 * heavy bale may quickly change switch state.
 */

/* Iss 42: Sorted Language file out 
   Lube alarm can be cancelled using ESc
   Dispensor warning added in MAN mode
   If instrument switched off or to MAN during netting, icon stops rotating
   OP17 comes on when renet button pressed
   Indexing cancel (IP01) done throught interupt so as to catch short pulses. CheckIndexing()
*/

/* ISS 41: Moved OP01 to OP17 when indexing.
*/

/* Iss 40: Beacon sounder moved from O01 to O17
   Removed Knife Postion Sensor from IP04
   Moved Rear Tip Roller Input from IP17 to IP04.
*/

/* ISS 39: Buzzer fixed for chamber full
   Delay added as transfer option
   Delay Open Time added to Bale transfer options (tec)
   Delay Pause Time added to Bale transfer options (tec)
   If transfer time is set to delay then O12 switchs off then 
   back on during transfer to pause the door opening.
   DELAY, DELAY5 and DELAY6 are loaded with valus to set the
   times for this in the sequance and have replaced DELYEF
*/


/* ISS 38: Stopped O2 and O8 being reset after wrapping.
   Changed Net Cut, and Net Cut postion pics.
   enabled L1 while netting until IP9 closes.
   Chamber pause can now be contiuned with R2
   Chamber can be paused in normal mode by pressing R2.
*/

/* ISS 37: Altered following alarm warnings:
   Tip Postion, Transfer not complete, Tip not complete, 
   wrap not complete, Dispenser postion.
*/

/* ISS 36: AutoTip and PauseTip bug fixes, no longer activates in 
   man mode and only when rear bale present, also autotip can be 
   changed while pausetip active and this resets pausetip.
   Cut tie relase default changed from 1 to 2.
   Power on rest added by holding Key_F2 for two seconds.
   Options no-longer accesible while neeting.
   Diplay changed for old machine status and MS_BALEON
*/

/* ISS 35: Main pic fix, bale in chamber disapperaed if ip8 closed
   while wrapping. Tip bale alarm fix and display change.
   DELYDX increased to 20.
*/

/* Iss 34: Bale remains in chamber in auto even if IP8 closes
   If Autotip off tipbale warning wont appear when chamber fills.
   Cannot use R2 to progress bale if rear bale is present
   Machine setup 1 + 2 unavalable while netting
   DELAY3 reduced to 1s
*/

/* ISS 33: Small mods to manual screens */

/* ISS 32: Changed IP10 to be closed for 1sec before indexing begins,
   Bale stays on screen as soon as IP8 opens.
   No Tip Pos error while Pause Tip is active.
   Stopped unwrapped bale appearing after Tip bale warning.
   Removed bale from man mode.
   Slowed bale tip animation.
   Removed 1 sec hold on advance bale key.
*/

/* ISS 31: Pause symbol now cancelled during transfer just in case auto transfer oocurs.
   When not wrapping bale complete alarm deleayed to stop early bale tip.

*/

/* ISS 30: Moved AutoTip Load in mainscreen */

/* ISS 29: 20061102

  Adjusted timing of screen to every 0.3s instead of 0.1s.
  This was so that the control routine isn't disruppted too much
  by the animations on the main screen.
  Added new feature, pause bale in auto tip mode. Pause the rear bale for
  one bale only. Added the crop feed to new revision 8 screens.

*/

/* ISS 28: 20061030

  Changed main display screens to rev8

*/

/* ISS 25 20061016

  Small fix to unblock/reset routine

*/

/* ISS 24: 20061016

  Modified Unblock/Reset Routine to increase floor divertor delays
  Change tones and make sure Knives up comes on when needed.
  fixed external alarm in main(), changed button sequence to stop
  ESC flashing on key02

*/

/* ISS 23  20061012

  Removed two speed chamber opening, swited OP01 and OP12
  back around, Decreased rpm damping, added new alarm sounds
  fixed buttons after 'net error' occurs. changed defaults

*/


/* 
 ISS 20   20060922

 Screens updated, menu system updated
 alarm screens updated 
 
*/


/*
 ISS 16   20060818

 OP01/OP12 values were not swapped!
  added bit ExternalAlarm (bytedef)
  IndexTable not longer turns on OP12 in OutputSet() (010)
  IndexTable now turns on OP12 directly in main while loop (000)
  change OP01 to ExternalAlarm in timer_int external alarm drive (int)
  Op.O.OP12 = ExternalAlarm before latches set (000)

*/

/*
 ISS 15   20060816

 Key_S2 action in auto no longer lower knives (010)

 swapped O01 & O12 actions (bytedef/010)

 added PWMCS1/2/3 (bytedef)
 added PWMChamber[3] (bytedef/011)
 added PWMChamberNow (bytedef)

 main_loop(), Key_S2 now alter/displays PWMChamber value in auto (010)

 MAXFACTOR from 107 to 110
*/

/*
 ISS 14   20060626

 Baler Full alarm now an alternating 3200/830 Hz ever 0.5 secs

*/

/*
 ISS 13   20060613

 FilmBreakCheck() error check times altered
  added new factor FILMPS, default 7 (bytedef)
  added FilmPassCount to hold active FILMPS (bytedef)
  FFCount set to FILMPS in ResetSequenceFactors() (001)
  added s0322 'Film Check Count' (lan1)

 MAXFACTOR from 106 to 107
*/

/*
 ISS 12   20060606
 
 added new delay DELYDX to delay O07, floor diverter turning off before O15, 
  default 0.2 seconds (bytedef)

 MAXFACTOR from 10? to 106
 MAXSEQ from 112 to 113
*/

/*
 ISS 11   20060512

 IP10, remote park now checks IP17 TipUp sensor (010)

*/

/*
 ISS 10   20060512

 after Key_S4 is pressed and TipUp is opened O03 is now turned off (010)
 
*/

/*
 ISS 9    20060512
 
 DELYYZ, 'Tip Return+' defaulted to 0.2 seconds

*/

/*
 ISS 8    20060511

 the wrap cycle now stops if TIPUP opens (010)
 now explicitly turn off OP03 every time PWM is turned off on that channel 
  (010/011)

 Key_S3/04 now don't move bale unless TipUp is closed, manual/auto (010)
 Indexing is stopped if TipUp opens (010)
 ResetSequenceFactors(), SEQ_WRAP option now turns off all outputs (011)

 re-wrap now checks IP17, TIPUP (010)

 TipUp is now checked where IP01, DispenserPos is checked (010)

*/

/*
 ISS 7    20060509

 LoadDelayAndOutputs() now clears OP03 when turning O03 pwm off so output does 
  suddenly go high (fully on) until main loop clears it (011)

 removed PressureCheck bit (bytedef)
 removed Zone20/21 actions setting/clearing PressureCheck bit (011)

 PRESSURE2 becomes TIPUP (bytedef)
 PSWTWX/YZ removed, RSWTCH added (bytedef)
 PDELWX/YZ removed (bytedef)
 s0249 becomes, 'Tip Return+' added (lan2)

 TipPosition warning message added (lan0)
 added s0324/5 (lan1)
 added TipPosErr bit

 moved (ResumeFrom == Zone04) from Key_S3 to Key_R2 (010)

 MAXFACTOR from 108 to 106
 MAXSEQ from 112 to 105
 MAXSWITCH from 16 to 15
*/

/*
 ISS 6    20060425

 after DLYOGH, O08 no longer comes on, Zone19 (bytedef)
 RSWTCA no longer turns off O08 (bytedef)

*/

/*
 ISS 5    20060419

 reset_factors() was clearing all ram up to 21E000, now only clears up to 
 &FillIn (21DFE0), so GrandTotalBales is not reset (000)

 some alarms now canceld when KeyCL pressed (010)

 Key_R1 now displays error if IP01 is at the incorrect level before starting 
  (010)

 DispenserPosError now enables Key_S3/04 for reverse or index (010)
 display of Key_S3/04 key tabs updated (010)

 main screen key tabs now only updated if bitmaps change (010)

 added knives setup from baler epl302-006 (bytedef/010/011)

 removed AUTOKN & s0312 'Knives'

 knives outputs O15/16 reversed (O10)

 added DLY05/06/07/08/09/10 for unblock sequence (bytedef)

 MAXFACTOR from 103 to 108
 MAXSEQ from 107 to 112

*/

/*
 ISS 4    20060407

 more changes...
 unified Volts & SupplyVoltage to SupplyVoltage (000/010)
 main display now show battery voltage in top right corner (010) 

 removed O10 for sequence (bytedef)
 
 added DispensesPosError to resume sequence from DELYKL Key_R1 press (010)

 O01 now set in main loop (000)
 updated screen09, 'Diagnostics - Outputs' to EP302-005 version (001)
 updated screen02, 'Operator Menu Display' to EP302-005 version (001)

 Key_L2 no longer checks IP05 before setting O11 to close baler (010)
 
*/

/*
 ISS 3    20060230

 array of pointers to strings made const
  const unsigned char *pt[] ----> const unsigned char * const pt[] (lan0)

 screen04, (selection > 0) always true, so now commented out (001)
 screen09, Diagnostics - Output, removed auto stepping (001)

 added fusion logo to startup screen (sym/001)

 MainDispalys, string -> tstring & tstring[16] = 0 (010)

 O10 no longer comes on with knives Key_S2/3 (010)

 Key_L4 no longer start/stops uinblock (010)

*/


/*
 ISS 2    20060223

 imported EXP304-094 20060221

*/


/*
 ISS 1    20060120

 based on initital test software EPL300-001

*/

#define MAXSEQ 		124
#define MAXFACTOR 	137 	/* Number of programmable factors in table */
#define MAXTYPE 	2     	/* Number of sequences */
/*#define MAXLANG 	19    	*//* Number of Language Strings */
#define MAXLANG 	20    	/* Number of Language Strings */

#include "bitmaps.h" 

#define CAN_CHIP

#define DEFAULT_BRIGHTNESS 152
#define BRIGHTRANGE 56
#define DEFAULT_CONTRAST 112 
#define DCRANGE 64

#define RAM_CODE_BASE 0x21C000
#define END_OF_DATA_STORE 0x21BFFD

#define CN_DAY 0
#define CN_NIGHT 1

#define NOTEDURATION 40
#define KEYDURATION (1 * NOTEDURATION)

#ifdef TEST
#define DEFAULT_KEYVOLUME 1
#define DEFAULT_ALARMVOLUME1 1
#else
#define DEFAULT_KEYVOLUME 15
#define DEFAULT_ALARMVOLUME1 15
#endif


#define DEFAULT_KEYNOTE 82
#define DEFAULT_ALARMNOTE1 71

#define PWMFREQ (unsigned short)9000 /* 222.22'Hz (2e6/9000 Hz) */
#define RPMAVG 2

#define MAXSPEED  	14.0
#define ALARMSPEED 	12.0

#define AREF 5.0
#define ATOD_IP_SCALE ((AREF/65535.0)*(3.0/2.0))
#define ATOD_VI_SCALE ((AREF/65535.0)*((2000.0+330.0)/330.0))

#define AM_MANUAL   0x00
#define AM_SEMIAUTO 0x01
#define AM_FULLAUTO 0x02
#define AM_CHANGE   0x80

#define UB_UNBLOCKOFF  0x00
#define UB_UNBLOCKWAIT 0x01
#define UB_UNBLOCKIN   0x02
#define UB_UNBLOCKSET  0x03
#define UB_UNBLOCKOUT  0x04

#define KS_KNIVESOFF    0x00
#define KS_KNIVESSETOUT 0x01
#define KS_KNIVESOUT    0x02
#define KS_KNIVESSETIN  0x04
#define KS_KNIVESIN     0x08
/* KnivesBank status */
#define KB_KNIVES00     0x00
#define KB_KNIVES11		0x01
#define KB_KNIVES12		0x02
#define KB_KNIVES23     0x04

/* Knives system in use */ /*rev 30 try to order the numbers as in the display*/
/*
#define RELIEF_VALVE 		0
#define x23_Std 			1
#define x23_Select 			2
#define x25_Std				3
#define x25_Select			4*/


/* Iss-146 reordered knife values so that selection doesn't change if a unit is upgraded from a revision before rev 129.
 * This may cause an issue if the unit has software rev 129 to rev 146 on it. */
#define RELIEF_VALVE 		1
#define x23_Std 			0
#define x23_Select 			2
#define x25_Std				3
#define x25_Select			4

#define SL_SHORT  0
#define SL_LONG   1
#define SL_MANUAL 2

enum KeyNames { NOKEY,
     Key_S1, Key_S2, Key_S3, Key_S4,
     Key_F1, Key_F2, Key_F3, Key_F4,
     Key_L1, Key_L2, Key_L3, Key_L4,
     Key_R1, Key_R2, Key_R3, Key_R4,
     Key_TL, Key_TR, Key_BL, Key_BR,
     Key_RDS, Key_OFF };

#define KeyMask   0xc0
#define KeyDone   0x80
#define KeyRepeat 0x40
#define KeyRepeatTime 4

#define TSMAX 25
#define TS20  20
#define TS18  15
#define TS15  15
#define TS10  10

#define LEFT  		0
#define RIGHT 		1

#define PFLOAT 		0
#define PLONG  		1
#define PSHORT 		2
#define PCHAR  		3

#define FIXED   	0x00
#define EDIT    	0x01
#define CENTER  	0x02
/*#define INV     	0x04*/
#define FRAMED  	0x08
#define ALPHA   	0x10
#define NUMERIC 	0x20
#define UNDERLINED 	0x40
#define GREY  		0x80

#define CASE_BOTH  	0
#define CASE_UPPER 	1
#define CASE_LOWER 	2

#define XON 		0x11
#define XOFF 		0x13

/*  IIC control  */
#define IIC_READ 	0x01
#define IIC_WRITE 	0x00
#define IIC_ACK 	0xff
#define IIC_NOACK 	0x00

/* MAX520=0x50,MAX5820M=0xb0,MAX5820L=0x70 */
#define IIC_DTOA_ADDRESS	0xb0 /* 10110000b */
#define IIC_DTOA0 			0x00
#define IIC_DTOA1 			0x10

/* MAX 520-------------------
#define IIC_DTOA_ADDRESS 0x50
#define IIC_DTOA_RESET 0x10
#define IIC_DTOA_PD    0x08
#define IIC_DTOA_0 0x00
#define IIC_DTOA_1 0x01
#define IIC_DTOA_2 0x02
#define IIC_DTOA_3 0x03
------------------- */

#define IIC_CLOCK_ADDRESS 0xd0 /* 11010000 */
#define IIC_CLOCK_SECONDS_ADDRESS 0x00
#define IIC_CLOCK_MINUTES_ADDRESS 0x01
#define IIC_CLOCK_HOURS_ADDRESS 0x02
#define IIC_CLOCK_DAY_ADDRESS 0x03
#define IIC_CLOCK_DATE_ADDRESS 0x04
#define IIC_CLOCK_MONTH_ADDRESS 0x05
#define IIC_CLOCK_YEARS_ADDRESS 0x06
#define IIC_CLOCK_CONTROL_ADDRESS 0x07
#define IIC_CLOCK_MEMORY_ADDRESS 0x08

#define RSTART 0x06
#define RFWD   0x03
#define RREV   0x0a
#define RSTOP  0x12

/*  Display Control Definitions */
#define TEXT_HOME_ADDRESS                0x0000
#define GRAPHICS_HOME_ADDRESS            0x0800
#define CHARACTER_GENERATOR_HOME_ADDRESS 0x1c00

#define GRAPHICS_SIZE                      2561
#define TEXT_SIZE                           320
#define COLUMNS                              20

#define TEXT_HOME_ADDRESS_SET        0x40
#define TEXT_AREA_SET                0x41
#define GRAPHICS_HOME_ADDRESS_SET    0x42
#define GRAPHICS_AREA_SET            0x43
#define OFFSET_ADDRESS_SET           0x22
#define ADDRESS_POINTER_SET          0x24
#define AUTO_WRITE_SET               0xb0
#define AUTO_WRITE_RESET             0xb2

#define DATA_WRITE_NOADP             0xc4

#define OR_MODE                      0x80
#define EXOR_MODE                    0x81
#define AND_MODE                     0x83
#define TEXT_ATTRIBUTE_MODE          0x84
#define INTERNAL_CG_MODE             0x80
#define EXTERNAL_CG_MODE             0x84
 
#define DISPLAY_OFF                  0x90
#define CURSOR_ON_BLINK_OFF          0x92
#define CURSOR_ON_BLINK_ON           0x93
#define TEXT_ON_GRAPHIC_OFF          0X94
#define TEXT_OFF_GRAPHIC_ON          0X98
#define TEXT_ON_GRAPHIC_ON           0X9C

#define AND   0x01
#define OR    0x02
#define INV   0x04
#define XOR   0x08
#define EMPTY 0x10
#define FULL  0x20
#define CLEAR 0x40
#define GREY  0x80

#define CONTROL0  0
#define CONTROL1  1
#define ARB0      2
#define ARB1      3
#define ARB2      4
#define ARB3      5
#define CONFIG    6
#define DATA0     7
#define DATA1     8
#define DATA2     9
#define DATA3    10
#define DATA4    11
#define DATA5    12
#define DATA6    13
#define DATA7    14

#include "proto.h"

#ifdef WINDOWS
 #include <ioh83003.h>

 #define port6_dat P6DR
 #define port6_dir P6DDR
 #define port9_dat P9DR
 #define port9_dir P9DDR
 #define portA_dat PADR
 #define portA_dir PADDR
 #define portB_dat PBDR
 #define portB_dir PBDDR
 #define portC_dat PCDR
 #define portC_dir PCDDR

 /* only 16 tiny variables allowed */
 extern unsigned char bit_flags0, bit_flags1, bit_flags2, bit_flags3;
 extern unsigned char bit_flags4, divider1, divider2, key;
 extern unsigned char swtim, swrel, demi_secs, KeyS1Delay, IP01_timer;

 extern unsigned char loop, RunOnce, KnivesAutoUp, escape;
 extern unsigned char flash_bit, ExternalAlarm, TimingBit, RpmCountBit;
 /* the above bits appear in bit_flags0 */

 extern unsigned char newA0, newA0b, newA2, MonitorFrequency;
 extern unsigned char calcA0, calcA0b, calcA2, KnivTopUpDone;
 /* the above bits appear in bit_flags1 */

 extern  unsigned char DispenserCountBit, DispenserPosError, Tipping, Transfering;
 extern  unsigned char ExtPower, OP13_On, KnivesAutoRun;
 /* the above bits appear in bit_flags2 */

 extern  unsigned char TipCheck, PauseWhileTipping, DisplayKnives, Wrapping;
 extern  unsigned char TipThenTransfer, TipPosErr, InitialRoutine, AdditiveEnOp;
 /* the above bits appear in bit_flags3 */

 extern  unsigned char DisplayWarning, FirstPulse, sprb4_2, sprb4_3;
 extern  unsigned char sprb4_4, sprb4_5, sprb4_6, sprb4_7;
 /* the above bits appear in bit_flags4 */

 /* only 496 other internal ram variables allowed */
 extern unsigned char TestResult, TestRead, StackStore[128];
 extern unsigned long TestAddress;

 extern unsigned char KeyS1;
 extern unsigned char KeyS2;
 extern unsigned char KeyS3;
 extern unsigned char KeyS4;
 extern unsigned char KeyD1;
 extern unsigned char KeyD2;
 extern unsigned char KeyD3;
 extern unsigned char KeyD4;

 extern unsigned char iic_scl;
 extern unsigned char iic_sda;

 extern unsigned char iic_scl_dir;
 extern unsigned char iic_sda_dir;

 extern unsigned char txd0;
 extern unsigned char txd1;
 extern unsigned char rxd0;
 extern unsigned char rxd1;

 extern unsigned char OP_Status;
 extern unsigned char LLatch;
 extern unsigned char IP01;
 extern unsigned char IP02;
 extern unsigned char OP01;
 extern unsigned char OP02;
 extern unsigned char IP03;
 extern unsigned char IP04;

 extern unsigned char OP03;
 extern unsigned char OP04;
 extern unsigned char Speaker;
 extern unsigned char OP_ENABLE;
 extern unsigned char Vol0;
 extern unsigned char Vol1;
 extern unsigned char Vol2;
 extern unsigned char Vol3;

 extern unsigned char LData;
 extern unsigned char LClk;

 extern unsigned char adcr;
 extern unsigned char adcsr;

 extern unsigned char atod_add0;
 extern unsigned char atod_add1;
 extern unsigned char atod_bank;
 extern unsigned char atod_clock;
 extern unsigned char atod_scan;
 extern unsigned char atod_stop;
 extern unsigned char atod_int;
 extern unsigned char atod_done;

 extern unsigned char WContR;
#else
 /* only 16 tiny variables allowed */
 extern tiny unsigned char bit_flags0, bit_flags1, bit_flags2, bit_flags3;
 extern tiny unsigned char bit_flags4, divider1, divider2, key;
 extern tiny unsigned char swtim, swrel, demi_secs, KeyS1Delay, IP01_timer;

 extern bit loop, RunOnce, KnivesAutoUp, escape;
 extern bit flash_bit, ExternalAlarm, TimingBit, RpmCountBit;
 /* the above bits appear in bit_flags0 */

 extern bit newA0, newA0b, newA2, MonitorFrequency;
 extern bit calcA0, calcA0b, calcA2, KnivTopUpDone;
 /* the above bits appear in bit_flags1 */

 extern bit DispenserCountBit, DispenserPosError, Tipping, Transfering;
 extern bit ExtPower, OP13_On, KnivesAutoRun;
 /* the above bits appear in bit_flags2 */

 extern bit TipCheck, PauseWhileTipping, DisplayKnives, Wrapping;
 extern bit TipThenTransfer, TipPosErr, InitialRoutine, AdditiveEnOp;
 /* the above bits appear in bit_flags3 */

 extern bit DisplayWarning, FirstPulse, sprb4_2, sprb4_3;
 extern bit sprb4_4, sprb4_5, sprb4_6, sprb4_7;
 /* the above bits appear in bit_flags4 */

 /* compiler -e option needed for the following */
 sfr port4_dat = 0xffffc7;     /* define special function registers */
 sfr port4_dir = 0xffffc5;

 bit KeyS1 = port4_dat.0; /* Input */
 bit KeyS2 = port4_dat.1; /* Input */
 bit KeyS3 = port4_dat.2; /* Input */
 bit KeyS4 = port4_dat.3; /* Input */
 bit KeyD1 = port4_dat.4; /* Output */
 bit KeyD2 = port4_dat.5; /* Output */
 bit KeyD3 = port4_dat.6; /* Output */
 bit KeyD4 = port4_dat.7; /* Output */

 sfr port6_dat = 0xffffcb; /* define special function registers */
 sfr port6_dir = 0xffffc9;

 bit iic_scl  = port6_dat.1;   /* Output */
 bit iic_sda  = port6_dat.2;   /* Input/Output */

 bit iic_scl_dir = port6_dir.1;
 bit iic_sda_dir = port6_dir.2;

 sfr P7_dat = 0xffffce;
 sfr adcr  = 0xffffe9;        /* control */
 sfr adcsr = 0xffffe8;        /* control/status */
 bit AtoD_a0 = adcsr.0;
 bit AtoD_a1 = adcsr.1;
 bit AtoD_bank  = adcsr.2;
 bit AtoD_clock = adcsr.3;
 bit AtoD_scan  = adcsr.4;
 bit AtoD_Run = adcsr.5;
 bit AtoD_IntEn = adcsr.6;
 bit AtoD_Done  = adcsr.7;

 sfr port9_dat = 0xffffd2;     /* define special function registers */
 sfr port9_dir = 0xffffd0;     /* serial ports 1 & 2 */

 bit txd0     = port9_dat.0;   /* Output */
 bit txd1     = port9_dat.1;   /* Output */
 bit rxd0     = port9_dat.2;   /* Input  */
 bit rxd1     = port9_dat.3;   /* Input  */

 sfr portA_dat = 0xffffd3;     /* define special function registers */
 sfr portA_dir = 0xffffd1;

 bit OP_Status = portA_dat.0;  /* Input */
 bit LLatch   = portA_dat.1;   /* Output */
 bit IP01     = portA_dat.2;   /* Input  */
 bit IP02     = portA_dat.3;   /* Input  */
 bit OP01     = portA_dat.4;   /* Output */
 bit OP02     = portA_dat.5;   /* Output */
 bit IP03     = portA_dat.6;   /* Input  */
 bit IP04     = portA_dat.7;   /* Input  */

 sfr portB_dat = 0xffffd6;     /* define special function registers */
 sfr portB_dir = 0xffffd4;

 bit OP03 = portB_dat.0;   /* Output */
 bit OP04 = portB_dat.1;   /* Output */
 bit Speaker  = portB_dat.2;   /* Output */
 bit OP_ENABLE = portB_dat.3;  /* Output */
 bit Vol0     = portB_dat.4;   /* Output */
 bit Vol1     = portB_dat.5;   /* Output */
 bit Vol2     = portB_dat.6;   /* Output */
 bit Vol3     = portB_dat.7;   /* Output */

 sfr portC_dat = 0xffffd7;     /* define special function registers */
 sfr portC_dir = 0xffffd5;     /* port c data direction set in startup */
                                     /* bits 2,3,4,5 are CS outputs */
 bit LData   = portC_dat.0;    /* Output */
 bit LClk    = portC_dat.1;    /* Output */
#endif

#pragma memory=dataseg(CSIP1):near
extern volatile char latch1_in;

#pragma memory=dataseg(CSOP1):near
extern volatile char latch1_out;

#pragma memory=dataseg(CSOP2):near
extern volatile char latch2_out;

#pragma memory=dataseg(CSDISPLAY):near
extern volatile char display_data, display_command;

#ifdef CAN_CHIP
#pragma memory=dataseg(CSCAN):near
extern volatile char can_control;
extern volatile char can_status;
extern volatile char can_CPU_interface;
extern volatile char can_RESERVED_00;
/*extern volatile unsigned short int can_hs_read;*/
extern volatile char can_hs_read_lo;
extern volatile char can_hs_read_hi;
extern volatile unsigned short int can_standard_global_mask;
extern volatile unsigned long int can_extended_global_mask;
extern volatile unsigned long int can_message15_mask;
extern volatile char message01[15];
extern volatile char can_clock_out;
extern volatile char message02[15];
extern volatile char can_bus_config;
extern volatile char message03[15];
extern volatile char can_bit_timing0;
extern volatile char message04[15];
extern volatile char can_bit_timing1;
extern volatile char message05[15];
extern volatile char can_interrupt;
extern volatile char message06[15];
extern volatile char can_RESERVED_01;
extern volatile char message07[15];
extern volatile char can_RESERVED_02;
extern volatile char message08[15];
extern volatile char can_RESERVED_03;
extern volatile char message09[15];
extern volatile char can_P1_config;
extern volatile char message10[15];
extern volatile char can_P2_config;
extern volatile char message11[15];
extern volatile char can_P1_in;
extern volatile char message12[15];
extern volatile char can_P2_in;
extern volatile char message13[15];
extern volatile char can_P1_out;
extern volatile char message14[15];
extern volatile char can_P2_out;
extern volatile char message15[15];
extern volatile char can_serial_reset;
#endif

#pragma memory=dataseg(H8RAM):near
/* only 496 other internal ram variables allowed */
extern unsigned char TestResult, TestRead, StackStore[128];
extern unsigned long TestAddress;

#pragma memory=dataseg(no_init):huge

extern unsigned long int reset_code;
extern unsigned char CheckString1[20];
extern unsigned char Korean;
extern unsigned char DayNight, Contrast[2], Brightness[2];
extern unsigned char KeyVolume, AlarmVolume, KeyNote, AlarmNote;

extern unsigned short int PinNumber, MachineStatus;
extern unsigned char CountSet, CountCur;
extern unsigned char BaleTotal;
extern unsigned long int TotalBales[10];
extern signed short int LubeCount;
extern unsigned char AutoMan, KnivesEnabled, KnivesStatus, KnivesBank;
extern unsigned char PWMChamberNow;
extern unsigned char Facts[MAXFACTOR][MAXTYPE];
extern unsigned char CropType, BalerFull[3];
extern unsigned char RearBaleStatus;
extern unsigned char ExtBuzzer, NoPWM;
extern float KnifePressure, KnifePresWarn, KnifeDownPres, KoreanPres;
extern unsigned short int KnifePressureBar, KoreanPresBar, KnifePresWarnBar, KnifeDownPresBar;
extern unsigned char S2_flag, AutoKnivFlag, KS3_Flag, IP10_Flag; /*Iss-131*/

struct serial_saved {
  unsigned baud:         4;
  unsigned stop_bits:    1;
  unsigned parity:       2;
  unsigned data_bits:    1;
  unsigned handshake:    1;
  };
extern struct serial_saved sio0;

/* last no init */
extern unsigned char CheckString2[20];

#pragma memory=dataseg(not_used):near

#pragma memory=dataseg(SavedData):huge
extern unsigned char FillIn[32-10-sizeof(long int)]; /* fill from top down */
extern unsigned long int GrandTotalBales;
extern unsigned char KnivSystem;
extern unsigned char CheckKey[8];

#pragma memory=default
extern unsigned char DecTens, DecUnits, KnivTimer, KnivStage, KnivMonitorStage, Kniv1PresHigh, Kniv2PresHigh;
extern unsigned char Units, DecPulse, DecRpm;

extern unsigned char level, selection, leaf, editing;
extern unsigned char RemoteCode, RemoteTimeOut;
extern unsigned char Sel, lev, Zone, PlsU;
extern unsigned char BeepOn, BeepOff, BeepTone, BeepCount, BeepType;

extern unsigned char seconds, minutes, hours, _day, _date, month, century;
extern unsigned short int year;

extern unsigned char loop_seconds, input_count, flag, TAB_FLAG;
extern unsigned char knifeip6, knifeip7;

extern unsigned char startup, old_time, old_date, demist, CANWarnCanc;
extern unsigned char command_point, command[20], WaitTime;
extern unsigned char SeqErr, ErrPos, SeqOffset, ResetAll;
extern unsigned char SavedCountCur, WrapSeq, AutoToManDelay, SecondPress, SpeedChanged;
extern unsigned char CapB0, NetHoldTime, TableOccupied, WasHigh;
extern unsigned char DelayLM, DelayST, RPMSlow, PPRMotor;
extern unsigned char DispenserStatus, UnBlockStatus, SafetyCount, IP01Count;
extern unsigned char RemoteRun, lang, ResumeFrom, IndexTable, NetCheck, SIOdata;
extern unsigned char NetDoneWaitingTransfer;
extern unsigned char IndexCountF, IndexCountR, TransferBale, TransferNow, TransferDone;
extern unsigned char WrapStatusEnd, ManTransDelay, MTDcnt, MTDchk;
extern unsigned char ChamberEnable, FilmPassCount;
extern unsigned char ChamberAlarm, IP10_Delay, OverspeedDelay, TopUpCount, LubeTopUpCount,  SecondScreen;
extern unsigned char CurrentSequenceMask, InitialKnivDownRoutineDone, PauseZone, FlashLedR2, TransferSeqPaused, Here[10];
extern unsigned short int PWMSlow1, PWMSlow2, PWMSlowTarget1, PWMSlowTarget2;
extern unsigned short int PWMChamber[3];
extern unsigned short int PWMmax, PWMmin, PWMerr, PWMstep, PLStable;
extern unsigned short int PWMIndexStep, oldMachineStatus;
extern unsigned long int RotateDebounce, RPMDebounce, TempKeyOp;

/*extern unsigned short int PWMBrakePower1;*/
extern float IP02Freq, PulseFrequency;

extern unsigned short rpm, FilmFrequency, analogue[8], SupplyVolts, Kniv1Pres, Kniv2Pres;
extern unsigned char Ip1count, OneDispenser, FilmBreak, CheckFilmBreak;

/*Debugging##################*/
extern unsigned char Flag;
/*Debugging##################*/

struct frequency {
  unsigned char stat;
  unsigned short time, count, pulses, duration;
  };
extern struct frequency Shaft[1];

extern float Speed;

extern unsigned char Note;
extern unsigned short int NoteLength;

/* itu timer 0 variables */
extern unsigned short int t0_high;

extern unsigned short int countA0, A0count;
extern unsigned long int startA0, durationA0;

extern unsigned short int countB0, B0count;
extern unsigned long int startB0, startB0f, durationB0f;
/*                      */

/* itu timer 2 variables */
extern unsigned short int t2_high;

extern unsigned short int countA2, A2count;
extern unsigned long int startA2, durationA2;
/*                      */

struct ret {
  unsigned char sel;
  void (*lev)(void);
  };
extern struct ret returnto[20];

extern void (*window)(void);

extern char buffer_memory[GRAPHICS_SIZE+128];
extern char adm[GRAPHICS_SIZE];

extern char s0tx_buff[256], s0tx_head, s0tx_tail;
extern char s0rx_buff[256], s0rx_head, s0rx_tail;
extern char s1tx_buff[256], s1tx_head, s1tx_tail;
extern char s1rx_buff[256], s1rx_head, s1rx_tail;

union usltoc {
  char c[4];
  unsigned long int l;
  };

union ustoc {
  char c[2];
  unsigned short int s;
  };

struct serial_mode {
  unsigned baud_divider: 2;
  unsigned mp_mode:      1;
  unsigned stop_bits:    1;
  unsigned parity:       2;
  unsigned data_bits:    1;
  unsigned async:        1;
  };

union serial_mode_char {
  char mode;
  struct serial_mode smode;
  };

struct baud_rates {
  unsigned short int baud;
  unsigned char clock_source;
  unsigned char rate_divider;
  };

extern const struct baud_rates br[11];

#ifndef WINDOWS
 struct Outs {
   unsigned OP04: 1;   /* Bit 17 */
   unsigned OP03: 1;   /* Bit 18 */
   unsigned OP02: 1;   /* Bit 19 */
   unsigned OP01: 1;   /* Bit 20 */

   unsigned Spare1: 4; /* Bit 21 - 24 */

   unsigned Spare2: 8; /* Bit 25 - 32 */

   unsigned OP13: 1;   /* Bit  1 */
   unsigned OP14: 1;   /* Bit  2 */
   unsigned OP15: 1;   /* Bit  3 */
   unsigned OP16: 1;   /* Bit  4 */

   unsigned OP17: 1;   /* Bit  5 */
   unsigned OP18: 1;   /* Bit  6 */
   unsigned OP19: 1;   /* Bit  7 */
   unsigned OP20: 1;   /* Bit  8 */

   unsigned OP05: 1;   /* Bit  9 */
   unsigned OP06: 1;   /* Bit 10 */
   unsigned OP07: 1;   /* Bit 11 */
   unsigned OP08: 1;   /* Bit 12 */

   unsigned OP09: 1;   /* Bit 13 */
   unsigned OP10: 1;   /* Bit 14 */
   unsigned OP11: 1;   /* Bit 15 */
   unsigned OP12: 1;   /* Bit 16 */
   };

#else
 struct Outs {
   unsigned OP13: 1;   /* Bit  1 */
   unsigned OP14: 1;   /* Bit  2 */
   unsigned OP15: 1;   /* Bit  3 */
   unsigned OP16: 1;   /* Bit  4 */

   unsigned OP17: 1;   /* Bit  5 */
   unsigned OP18: 1;   /* Bit  6 */
   unsigned OP19: 1;   /* Bit  7 */
   unsigned OP20: 1;   /* Bit  8 */

   unsigned OP05: 1;   /* Bit  9 */
   unsigned OP06: 1;   /* Bit 10 */
   unsigned OP07: 1;   /* Bit 11 */
   unsigned OP08: 1;   /* Bit 12 */

   unsigned OP09: 1;   /* Bit 13 */
   unsigned OP10: 1;   /* Bit 14 */
   unsigned OP11: 1;   /* Bit 15 */
   unsigned OP12: 1;   /* Bit 16 */

   unsigned OP04: 1;   /* Bit 17 */
   unsigned OP03: 1;   /* Bit 18 */
   unsigned OP02: 1;   /* Bit 19 */
   unsigned OP01: 1;   /* Bit 20 */

   unsigned Spare1: 4; /* Bit 21 - 24 */

   unsigned Spare2: 8; /* Bit 25 - 32 */
   };
 #endif

union OutsWide  {
  struct Outs O;
  unsigned char C[4];
  unsigned long int L;
  };
extern union OutsWide TestOp, Op, KeyOp, SeqOp;

struct Leds {
   unsigned LedR4: 1;  /* Bit  0 */
   unsigned LedL4: 1;  /* Bit  1 */
   unsigned LedL3: 1;  /* Bit  2 */
   unsigned LedR3: 1;  /* Bit  3 */

   unsigned LedL2: 1;  /* Bit  4 */
   unsigned LedR2: 1;  /* Bit  5 */
   unsigned LedR1: 1;  /* Bit  6 */
   unsigned LedL1: 1;  /* Bit  7 */

   unsigned Spare1: 8; /* Bit 8-15 */
   };

union LEDsWide {
  struct Leds L;
  unsigned char C[2];
  unsigned short int S;
  };
extern union LEDsWide LedData;

#ifndef WINDOWS
struct Inps {
   unsigned IP04: 1;/* lsb of C[1] */
   unsigned IP03: 1;
   unsigned IP02: 1;
   unsigned IP01: 1;

   unsigned CTOP:   1;
   unsigned TRANS:  1;
   unsigned TIPST:  1;
   unsigned AUTOST: 1; /* msb of C[1] */

   /*unsigned LPRES:  1;
   unsigned HPRES:	1;*/
   unsigned Spare2: 6; /* lsb of C[0]*/
   unsigned FTOP:   1;
   unsigned LTOP:   1;

   unsigned IP13: 1; /* lsb of C[3]*/
   unsigned IP14: 1;
   unsigned IP15: 1;
   unsigned IP16: 1;

   unsigned IP17: 1;
   unsigned IP18: 1;
   unsigned IP19: 1;
   unsigned IP20: 1; /* msb of C[3]*/

   unsigned IP05: 1; /* lsb of C[2]*/
   unsigned IP06: 1;
   unsigned IP07: 1;
   unsigned IP08: 1;

   unsigned IP09: 1;
   unsigned IP10: 1;
   unsigned IP11: 1;
   unsigned IP12: 1; /* msb of C[2]*/
   };
#else
struct Inps {
   unsigned IP13: 1;
   unsigned IP14: 1;
   unsigned IP15: 1;
   unsigned IP16: 1;

   unsigned IP17: 1;
   unsigned IP18: 1;
   unsigned IP19: 1;
   unsigned IP20: 1;

   unsigned IP05: 1;
   unsigned IP06: 1;
   unsigned IP07: 1;
   unsigned IP08: 1;

   unsigned IP09: 1;
   unsigned IP10: 1;
   unsigned IP11: 1;
   unsigned IP12: 1;

   unsigned IP04: 1;
   unsigned IP03: 1;
   unsigned IP02: 1;
   unsigned IP01: 1;

   unsigned CTOP:   1;
   unsigned TRANS:  1;
   unsigned TIPST:  1;
   unsigned AUTOST: 1;

   /*unsigned LPRES:	1;
   unsigned HPRES:	1; */  
   unsigned Spare2: 6;
   unsigned FTOP:   1;
   unsigned LTOP:   1;
   };
#endif

union InpsWide  {
  struct Inps I;
  unsigned char C[4];
  unsigned long int L;
  };
extern union InpsWide TestIp, Ip;

/* beep 'tone' tone */
#define TBOFF 0x00
#define TBEXT 0x01
#define TBINT 0x02
#define TBOTH 0x03
#define TBALL 0x04

/* beep 'tone' mask */
#define TMASK 0xc0
#define TB1 0x80
#define TB2 0x40
#define TB3 0xc0

/* beep 'type' priority */
#define PMASK 0xe0
#define BP1 0x00
#define BP2 0x20
#define BP3 0x40
#define BP4 0x60
#define BP5 0x80
#define BP6 0xa0
#define BP7 0xc0
#define BP8 0xe0

/* beep 'type' type */
#define BMASK 0x1f
#define BT0 0x00
#define BT1 0x01
#define BT2 0x02
#define BT3 0x03
#define BT4 0x04
#define BT5 0x05
#define BT6 0x06
#define BT7 0x07
#define BT8 0x08

#define AUTOSTART 0x00800000UL /* Ip.I.AUTOST associated with IP08*/
#define TIPSTART  0x00400000UL /* Ip.I.TIPST  associated with IP10*/
#define TRANSFER  0x00200000UL /* Ip.I.TRANS  associated with StartTransfer()*/
#define CTOPUP    0x00100000UL /* Ip.I.CTOP  */
#define LOWPRES   0x01000000UL /* Ip.I.LPRES */
#define HIGHPRES  0x02000000UL /* Ip.I.HPRES */
#define FTOPUP    0x40000000UL /* Ip.I.LTOP   */
#define LTOPUP    0x80000000UL /* Ip.I.LTOP   */

#define TURNTABLE 0x00080000UL /* IP01 */
#define ENCODER   0x00040000UL /* IP02 */
#define KNIVESDN  0x00020000UL /* IP03 */
#define TIPUP     0x00010000UL /* IP04 */
#define PRESSURE1 0x00000100UL /* IP05 */
#define SAFETY    0x00000200UL /* IP06 */
#define INPUT07   0x00000400UL /* IP07 */
#define CHAMBER   0x00000800UL /* IP08 */
#define NETCUT    0x00001000UL /* IP09 */
#define DISPARK   0x00002000UL /* IP10 */
#define INPUT11   0x00004000UL /* IP11 */
#define INPUT12   0x00008000UL /* IP12 */
#define INPUT13   0x00000001UL /* IP13 */
#define INPUT14   0x00000002UL /* IP14 */
#define INPUT15   0x00000004UL /* IP15 */
#define INPUT16   0x00000008UL /* IP16 */
#define INPUT17   0x00000010UL /* IP17 */
#define INPUT18   0x00000020UL /* IP18 */
#define INPUT19   0x00000040UL /* IP19 */
#define INPUT20   0x00000080UL /* IP20 */

#define I05 0x01
#define I06 0x02
#define I07 0x04
#define I08 0x08
#define I09 0x10
#define I10 0x20
#define I11 0x40
#define I12 0x80

extern const unsigned char IpDef[8];

#define AllOff  0xffffffffUL
#define NoneOn  0x00000000UL
#define NoneOff 0x00000000UL
#define O01 0x00080000UL
#define O02 0x00040000UL
#define O03 0x00020000UL
#define O04 0x00010000UL
#define O05 0x00000100UL
#define O06 0x00000200UL
#define O07 0x00000400UL
#define O08 0x00000800UL
#define O09 0x00001000UL
#define O10 0x00002000UL
#define O11 0x00004000UL
#define O12 0x00008000UL
#define O13 0x00000001UL
#define O14 0x00000002UL
#define O15 0x00000004UL
#define O16 0x00000008UL
#define O17 0x00000010UL
#define O18 0x00000020UL
#define O19 0x00000040UL
#define O20 0x00000080UL

#define FTYPE 0x000f
#define DLT 0x0000
#define DLS 0x0001
#define PLS 0x0002
#define TXT 0x0003
#define CON 0x0004
#define TIM 0x0005
#define PER 0x0006
#define RPM 0x0007
#define NUM 0x0008
#define PDP 0x0009
#define PLR 0x000a
#define NUT 0x000b
#define DLM 0x000c
#define HR0 0x000d

#define PTYPE 0x0030
#define NONP 0x0000
#define PROT 0x0010
#define PROO 0x0020
#define PROS 0x0030

#define RTYPE 0x3fc0
#define RNET  0x0000
#define RTIP  0x0040
#define RWRAP 0x0080
#define RFILM 0x00c0
#define RUNBK 0x0100
#define RKNIV 0x0200
#define RCTOP 0x0400
#define RCTPL 0x0800
#define RFTOP 0x1000
#define RPAUS 0x2000

struct SeqFactors {
  unsigned char min;
  unsigned char max;
  unsigned char def[MAXTYPE];
  unsigned short int type;
  unsigned char Tag;
  const struct pr *Name;
  };
extern const struct SeqFactors PF[MAXFACTOR];
extern unsigned char FA[MAXFACTOR];

#define O_All   0x03 /* 00000011 */
#define O_S1    0x01 /* 00000001 */
#define O_S2    0x02 /* 00000010 */
#define O_Ps    0x40 /* 01000000 */
#define O_Flm   0x80 /* 10000000 */
#define O_Net   (O_All | O_Flm) /* 10000011 */

#define SEQ_ALL  0x07ff    /* 1 1111 1111 */
#define SEQ_NET  0x0001    /* 0 0000 0001 */
#define SEQ_TIP  0x0002    /* 0 0000 0010 */
#define SEQ_WRAP 0x0004    /* 0 0000 0100 */
#define SEQ_FILM 0x0008    /* 0 0000 1000 */
#define SEQ_UNBK 0x0010    /* 0 0001 0000 */
#define SEQ_KNVS 0x0020    /* 0 0010 0000 */
#define SEQ_INIT 0x0040    /* 0 0100 0000 */
#define SEQ_CTOP 0x0080    /* 0 1000 0000 */
#define SEQ_LTOP 0x0100    /* 1 0000 0000 */
#define SEQ_FTOP 0x0200    /*10 0000 0000 */
#define SEQ_PAUS 0x0400   /*100 0000 0000 */

#define NOREM  0
#define REMEN  1                       

#define WS_RUNNING	0
#define WS_PAUSED		1
#define WS_RESUMED	2

enum SeqVars { NOFACT,
/*   1-  8 */  AUTOTP, SEQNUM, FILMBK, HRSTAG, MINTAG, DELYAB, DELYLB, DELYSB,
/*   9- 16 */  DELYBC, DELYCD, DELYNT, DELYDE, DELYEF, DELYFG, DELYGH, DELYJK, 
/*  17- 24 */  DELYOT, DELYPT, DELYKL, DELYLM, PULSEP, DELYPQ, DELYRS, DELYST, DELYUV,
/*  25- 32 */  DELYVW, DELWX1, DELWX2, DELYXY, DELYYZ, ROTDEB, DELAYL, DELYNU,
/*  33- 40 */  DELYNV, DELYNW, DELYOR, DELYZA, DELYZB, DELAYE, DELYLN, DELYK2,
/*  41- 48 */  BDELY1, BDELY2, BDELY3, DELYFP, DELYFT, DELYDX, DLYT01, DLYT02, PLSPAS,
/*  49- 56 */  DLYT03, DLYT04, DELYHI, DELYW1, MOTDEB, MOTPPR, MOTALM, RPMDEB, RPMSLO,
/*  57- 64 */  PWMSL1, PWMSL2, MAXPWM, MINPWM, PLSTAB, PLSTRT, ERRPWM, PWMCS1, PWMCS2,
/*  65- 72 */  PWMCS3, LANGUA, FRESET, DIVDEL, DIVSRT, DIVLNG, PAUSRT, PAULNG,
/*  73- 80 */  PDELEF, FILMPS, PULSER, PULSET, PULSEU, PLSFR1, PLSFR2, PLSFR3,
/*  81- 88 */  PLSF01, DELYF1, DELAY3, DELYWX, DELAY4, DELAY5, DELAY6, DELAY7, DLYUS1,
/*  89- 96 */  DLYUS4, DLYUS3, DLYU01, DLYU02, DLYU03, DLYU04, DLYV01, DLYV02, DLYV03,
/*  96-104 */  DLYV04, DLYU05, DLYU06, DLYU07, DLYU08, DLYU09, DLYU10, DLYKS1, DLYK01,
			   	 	   DLYOCD, DLYODE, DLYOEF, DLYVS1, DLYVS2, DLYVS3, DLYV05, DLYV06,
			   	 	   DLYV07, DLYV08, DLYV09, DLYV10,
/* 105-112 */  DLYOFG, DLYOGH, DLYOKL, PDLOEF, IDXCNT, IDXPWM, IP2FRQ, RESTRT, 
/* 113-118 */  LUBECK, LUBERS, LUBEDS, DLUBEF, DLUBED, SIODAT, 
               FCLAST };
     
extern unsigned char DelPul[FCLAST];     

struct Switches {
  unsigned long int Switch;
  unsigned char Act;
  unsigned char Tag;
  unsigned short int type;
  };
#define MAXSWITCH 21
extern const struct Switches SW[MAXSWITCH];

extern unsigned char SA[MAXSWITCH];
enum SwitchType { NOSWITCH, 
                  RSWTCA, RSWTCB, RSWTCC, RSWTCD,
                  RSWTCE, RSWTCF, RSWTCG, RSWTCH, RSWTCI,
                  VSWTCA, VSWTCB, VSWTCC, VSWTCD, VSWTCF, VSWTCE,/* VSWTLP, VSWCHP, VSWCLP,*/
                  PSWTEF,
                  PSWOEF,
                  SWLAST
                };
extern unsigned char SwLook[SWLAST];                
                
enum SwitchStat { CLOSED, OPEN };

struct Sequence {
  unsigned char  Dlp;
  unsigned char  Pdl;
  unsigned char  Wdl;
  unsigned long  opO;
  unsigned long  opA;
  unsigned char  Zne;
  unsigned short Seq;
  unsigned short Act;
  };
extern const struct Sequence SQ[MAXSEQ];

                                      /* 5432 1098 7654 3210 */
#define spare1               0x0001   /* 0000 0000 0000 0001 */
#define DelayOrPulseWait     0x0002   /* 0000 0000 0000 0010 */
#define SequenceReset        0x0004   /* 0000 0000 0000 0100 */
#define EnableAndLoad        0x0008   /* 0000 0000 0000 1000 */

#define CountingMask         0x0010   /* 0000 0000 0001 0000 */
#define CountingOff          0x0020   /* 0000 0000 0010 0000 */
#define CountingOn           0x0030   /* 0000 0000 0011 0000 */

#define TimingMask           0x0040   /* 0000 0000 0100 0000 */
#define TimingOff            0x0080   /* 0000 0000 1000 0000 */
#define TimingOn             0x00C0   /* 0000 0000 1100 0000 */

#define WaitForWdl           0x0100   /* 0000 0001 0000 0000 */
#define WaitForSW            0x0200   /* 0000 0010 0000 0000 */
#define SwitchWait           0x0400   /* 0000 0100 0000 0000 */
#define ResetCurrentCount    0x0800   /* 0000 1000 0000 0000 */
#define TwoBeeps             0x1000   /* 0001 0000 0000 0000 */
#define spare2               0x2000   /* 0010 0000 0000 0000 */
#define CancelIfDone         0x4000   /* 0100 0000 0000 0000 */
#define RpmCount             0x8000   /* 1000 0000 0000 0000 */

#define FF_ONE_DISPENSER 	550
#define FF_TWO_DISPENSER 	1100

#define SAFETYLEVEL 		137

#define NoChange  0
#define Zone00 0x80 
#define Zone01 (0x80 | 1)
#define Zone02 (0x80 | 2)
#define Zone03 (0x80 | 3)
#define Zone04 (0x80 | 4)
#define Zone05 (0x80 | 5)
#define Zone06 (0x80 | 6)
#define Zone07 (0x80 | 7)
#define Zone08 (0x80 | 8)
#define Zone09 (0x80 | 9)
#define Zone10 (0x80 | 10)
#define Zone11 (0x80 | 11)
#define Zone12 (0x80 | 12)
#define Zone13 (0x80 | 13)
#define Zone14 (0x80 | 14)
#define Zone15 (0x80 | 15)
#define Zone16 (0x80 | 16)
#define Zone17 (0x80 | 17)
#define Zone18 (0x80 | 18)
#define Zone19 (0x80 | 19)
#define Zone20 (0x80 | 20)
#define Zone21 (0x80 | 21)
#define Zone22 (0x80 | 22)
#define Zone23 (0x80 | 23)
#define Zone24 (0x80 | 24)
#define Zone25 (0x80 | 25)
#define Zone26 (0x80 | 26)
#define Zone27 (0x80 | 27)
#define Zone28 (0x80 | 28)
#define Zone29 (0x80 | 29)
#define Zone30 (0x80 | 30)
#define Zone31 (0x80 | 31)
#define Zone32 (0x80 | 32)
#define Zone33 (0x80 | 33)
#define Zone34 (0x80 | 34)
#define Zone35 (0x80 | 35)
#define Zone36 (0x80 | 36)
#define Zone37 (0x80 | 37)
#define Zone38 (0x80 | 38)
#define Zone39 (0x80 | 39)
#define Zone40 (0x80 | 40)
#define Zone41 (0x80 | 41)
#define Zone42 (0x80 | 42)
#define Zone43 (0x80 | 43)
#define Zone44 (0x80 | 44)
#define Zone45 (0x80 | 45)
#define Zone46 (0x80 | 46)
#define Zone47 (0x80 | 47)
#define Zone48 (0x80 | 48)
#define Zone49 (0x80 | 49)
#define Zone50 (0x80 | 50)
#define Zone51 (0x80 | 51)
#define Zone52 (0x80 | 52)
#define Zone53 (0x80 | 53)
#define Zone54 (0x80 | 54)
#define Zone55 (0x80 | 55)
#define Zone56 (0x80 | 56)
#define Zone57 (0x80 | 57)
#define Zone58 (0x80 | 58)
#define Zone59 (0x80 | 59)
#define Zone60 (0x80 | 60)
#define Zone61 (0x80 | 61)
#define Zone62 (0x80 | 62)
#define Zone63 (0x80 | 63)
#define Zone64 (0x80 | 64)
#define Zone65 (0x80 | 65)
#define Zone66 (0x80 | 66)
#define Zone67 (0x80 | 67)
#define Zone68 (0x80 | 68)
#define Zone69 (0x80 | 69)
#define Zone70 (0x80 | 70)
#define Zone71 (0x80 | 71)
#define Zone72 (0x80 | 72)
#define Zone73 (0x80 | 73)
#define Zone74 (0x80 | 74)
#define Zone75 (0x80 | 75)
#define Zone76 (0x80 | 76)
#define Zone77 (0x80 | 77)
#define Zone78 (0x80 | 78)
#define Zone79 (0x80 | 79)


#define MS_NETTING     0x0001
#define MS_TRANSFER    0x0002
#define MS_BALEON      0x0004
#define MS_WRAPPING    0x0008
#define MS_TIPPING     0x0010
#define MS_FLOORTOPUP  0x0020
#define MS_TRANSDONE   0x0040
#define MS_CLOSEPLUS   0x0080
#define MS_KNIVETOP    0x0100
#define MS_NETCUT      0x0200
#define MS_CHAMBERFULL 0x0400
#define MS_CHAMBEROPEN 0x0800

#define LT_START 0x80
#define LT_COUNT 0x7f

#define LR1 0x0001
#define LR2 0x0002
#define LR3 0x0004
#define LR4 0x0008
#define LR5 0x0010
#define LR6 0x0020
#define LL1 0x0040
#define LL2 0x0080
#define LL3 0x0100
#define LL4 0x0200
#define LL5 0x0400
#define LL6 0x0800

#define OMS_TRANS   (oldMachineStatus & MS_TRANSFER) 
#define OMS_WRAP    (oldMachineStatus & MS_WRAPPING) 
#define OMS_TIP     (oldMachineStatus & MS_TIPPING) 
#define OMS_TIPWRAP (oldMachineStatus & (MS_WRAPPING | MS_TIPPING)) 

#define SWS_MODE       0x01
#define SWS_WRAP       0x00
#define SWS_TRANS      0x01
#define SWS_RESETCOUNT 0x02

extern const unsigned char hex[16];

extern const unsigned short int NoteFrequency[105];

struct tune {
  unsigned char Note;
  unsigned char Duration;
  };
extern struct tune *Music;
extern struct tune const DixieLand[14];
extern struct tune const Alarm01[5];

extern const unsigned char *const ROLLER[8];

extern const unsigned char *const BALERREAR[11];

extern const unsigned char *const CROPFEED[12];

extern const unsigned char *const KCropTypeBitMap[3];
extern const unsigned char *const KOnOff[2];
extern const unsigned char *const KShortLong[3];

extern unsigned char mainscreen_delay;
extern unsigned char NetWarnCanc;
extern unsigned char AlarmFlags;

#define ExternAlarm     0x01
#define NoteTwo         0x02
#define NoteThree       0x04
#define NoteMask        0x06
#define NoteAlt         0x08
#define NoteAltTwo      0x10
#define NoteAltThree    0x20
#define NoteAltFour     0x40
#define NoteAltMask     0x78

extern unsigned char Knives_Up, RaiseDoor, BootRun, DemoScreens;
extern unsigned char AutoTip_Sel, LangStartup, LEDSel;
extern unsigned char PauseTip, NetCutPosAlarm, NetCutPosNorm, OneDispCount, ExternalBuzzSet;
extern unsigned char BuzzerTimer;

#include "EPL_CAN.H"

#endif
