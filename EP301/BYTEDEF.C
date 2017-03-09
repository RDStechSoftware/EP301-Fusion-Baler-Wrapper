
#include "bytedef.h"

#ifdef WINDOWS
 /* only 16 tiny variables allowed */
 unsigned char bit_flags0, bit_flags1, bit_flags2, bit_flags3;
 unsigned char bit_flags4, divider1, divider2, key;
 unsigned char swtim, KeyS1Delay, swrel, demi_secs, IP01_timer;

 unsigned char loop, RunOnce, KnivesAutoUp, escape;
 unsigned char flash_bit, ExternalAlarm, TimingBit, RpmCountBit;
 /* the above bits appear in bit_flags0 */

 unsigned char newA0, newA0b, newA2, MonitorFrequency;
 unsigned char calcA0, calcA0b, calcA2, KnivTopUpDone;
 /* the above bits appear in bit_flags1 */

 unsigned char DispenserCountBit, DispenserPosError, Tipping, Transfering;
 unsigned char ExtPower, OP13_On, KnivesAutoRun;
 /* the above bits appear in bit_flags2 */

 unsigned char TipCheck, PauseWhileTipping, DisplayKnives, Wrapping;
 unsigned char TipThenTransfer, TipPosErr, InitialRoutine, AdditiveEnOp;
 /* the above bits appear in bit_flags3 */

 unsigned char DisplayWarning, FirstPulse, sprb4_2, sprb4_3;
 unsigned char sprb4_4, sprb4_5, sprb4_6, sprb4_7;
 /* the above bits appear in bit_flags4 */

 /* only 496 other internal ram variables allowed */
 unsigned char TestResult, TestRead, StackStore[128];
 unsigned long TestAddress;

 unsigned char KeyS1;
 unsigned char KeyS2;
 unsigned char KeyS3;
 unsigned char KeyS4;
 unsigned char KeyD1;
 unsigned char KeyD2;
 unsigned char KeyD3;
 unsigned char KeyD4;

 unsigned char iic_scl;
 unsigned char iic_sda;

 unsigned char iic_scl_dir;
 unsigned char iic_sda_dir;

 unsigned char txd0;
 unsigned char txd1;
 unsigned char rxd0;
 unsigned char rxd1;

 unsigned char OP_Status;
 unsigned char LLatch;
 unsigned char IP01;
 unsigned char IP02;
 unsigned char OP01;
 unsigned char OP02;
 unsigned char IP03;
 unsigned char IP04;

 unsigned char OP03;
 unsigned char OP04;
 unsigned char Speaker;
 unsigned char OP_ENABLE;
 unsigned char Vol0;
 unsigned char Vol1;
 unsigned char Vol2;
 unsigned char Vol3;

 unsigned char LData;
 unsigned char LClk;

 unsigned char adcr;
 unsigned char adcsr;

 unsigned char atod_add0;
 unsigned char atod_add1;
 unsigned char atod_bank;
 unsigned char atod_clock;
 unsigned char atod_scan;
 unsigned char atod_stop;
 unsigned char atod_int;
 unsigned char atod_done;

 unsigned char WContR;

 unsigned char h8_sfr[256];
#else
 /* only 16 tiny variables allowed */
 tiny unsigned char bit_flags0, bit_flags1, bit_flags2, bit_flags3;
 tiny unsigned char bit_flags4, divider1, divider2, key;
 tiny unsigned char swtim, swrel, demi_secs, KeyS1Delay, IP01_timer;

 bit loop, RunOnce, KnivesAutoUp, escape;
 bit flash_bit, ExternalAlarm, TimingBit, RpmCountBit;
 /* the above bits appear in bit_flags0 */

 bit newA0, newA0b, newA2, MonitorFrequency;
 bit calcA0, calcA0b, calcA2, KnivTopUpDone;
 /* the above bits appear in bit_flags1 */

 bit DispenserCountBit, DispenserPosError, Tipping, Transfering;
 bit ExtPower, OP13_On, KnivesAutoRun;
 /* the above bits appear in bit_flags2 */

 bit TipCheck, PauseWhileTipping, DisplayKnives, Wrapping;
 bit TipThenTransfer, TipPosErr, InitialRoutine, AdditiveEnOp;
 /* the above bits appear in bit_flags3 */

 bit DisplayWarning, FirstPulse, sprb4_2, sprb4_3;
 bit sprb4_4, sprb4_5, sprb4_6, sprb4_7;
 /* the above bits appear in bit_flags4 */
#endif

#pragma memory=dataseg(CSIP1):near
volatile char latch1_in;

#pragma memory=dataseg(CSOP1):near
volatile char latch1_out;

#pragma memory=dataseg(CSOP2):near
volatile char latch2_out;

#pragma memory=dataseg(CSDISPLAY):near
volatile char display_data, display_command;

 #ifdef CAN_CHIP
#ifndef WINDOWS
 #pragma memory=dataseg(CSCAN):near
#endif
 volatile char can_control;
 volatile char can_status;
 volatile char can_CPU_interface;
 volatile char can_RESERVED_00;
 /*volatile unsigned short int can_hs_read;*/
 volatile char can_hs_read_lo;
 volatile char can_hs_read_hi;
 volatile unsigned short int can_standard_global_mask;
 volatile unsigned long int can_extended_global_mask;
 volatile unsigned long int can_message15_mask;
 volatile char message01[15];
 volatile char can_clock_out;
 volatile char message02[15];
 volatile char can_bus_config;
 volatile char message03[15];
 volatile char can_bit_timing0;
 volatile char message04[15];
 volatile char can_bit_timing1;
 volatile char message05[15];
 volatile char can_interrupt;
 volatile char message06[15];
 volatile char can_RESERVED_01;
 volatile char message07[15];
 volatile char can_RESERVED_02;
 volatile char message08[15];
 volatile char can_RESERVED_03;
 volatile char message09[15];
 volatile char can_P1_config;
 volatile char message10[15];
 volatile char can_P2_config;
 volatile char message11[15];
 volatile char can_P1_in;
 volatile char message12[15];
 volatile char can_P2_in;
 volatile char message13[15];
 volatile char can_P1_out;
 volatile char message14[15];
 volatile char can_P2_out;
 volatile char message15[15];
 volatile char can_serial_reset;

#ifndef WINDOWS
 #pragma memory=dataseg(H8RAM):near
#endif
#endif
 /* only 496 other internal ram variables allowed */
 unsigned char TestResult, TestRead, StackStore[128];
 unsigned long TestAddress;

#ifndef WINDOWS
 #pragma memory=dataseg(no_init):huge
#endif

unsigned long int reset_code;
unsigned char CheckString1[20];
unsigned char Korean;
unsigned char DayNight, Contrast[2], Brightness[2];
unsigned char KeyVolume, AlarmVolume, KeyNote, AlarmNote;

unsigned short int PinNumber, MachineStatus;
unsigned char CountSet, CountCur;
unsigned char BaleTotal;
unsigned long int TotalBales[10];
signed short int LubeCount;
unsigned char AutoMan, KnivesEnabled, KnivesStatus, KnivesBank;
unsigned char PWMChamberNow;
unsigned char Facts[MAXFACTOR][MAXTYPE];
unsigned char CropType, BalerFull[3];
unsigned char RearBaleStatus;
unsigned char ExtBuzzer, NoPWM;
float KnifePressure, KnifePresWarn, KnifeDownPres, KoreanPres;
unsigned short int KnifePressureBar, KoreanPresBar, KnifePresWarnBar, KnifeDownPresBar;
unsigned char S2_flag, AutoKnivFlag, KS3_Flag, IP10_Flag; /*Iss-131*/
/*
struct serial_saved {
  unsigned baud:         4;
  unsigned stop_bits:    1;
  unsigned parity:       2;
  unsigned data_bits:    1;
  unsigned handshake:    1;
  }; */
struct serial_saved sio0;

/* last no init */
unsigned char CheckString2[20];

#pragma memory=dataseg(not_used):near

#pragma memory=dataseg(SavedData):huge
unsigned char FillIn[32-10-sizeof(long int)]; /* fill from top down */
unsigned long int GrandTotalBales;
unsigned char KnivSystem;
unsigned char CheckKey[8];

#pragma memory=default
unsigned char DecTens, DecUnits, KnivTimer, KnivStage, KnivMonitorStage, Kniv1PresHigh, Kniv2PresHigh;
unsigned char Units, DecPulse, DecRpm;

unsigned char level, selection, leaf, editing;
unsigned char RemoteCode, RemoteTimeOut;
unsigned char Sel, lev, Zone, PlsU;
unsigned char BeepOn, BeepOff, BeepTone, BeepCount, BeepType;

unsigned char seconds, minutes, hours, _day, _date, month, century;
unsigned short int year;

unsigned char loop_seconds, input_count, flag, TAB_FLAG = 0;
unsigned char knifeip6, knifeip7 = 0;

unsigned char startup, old_time, old_date, demist, CANWarnCanc;
unsigned char command_point, command[20], WaitTime;
unsigned char SeqErr, ErrPos, SeqOffset, ResetAll;
unsigned char SavedCountCur, WrapSeq, AutoToManDelay, SecondPress;
unsigned char SpeedChanged = 2;
unsigned char CapB0, NetHoldTime, TableOccupied, WasHigh;
unsigned char DelayLM, DelayST, RPMSlow, PPRMotor;
unsigned char DispenserStatus, UnBlockStatus, SafetyCount, IP01Count;
unsigned char RemoteRun, lang, ResumeFrom, IndexTable, NetCheck, SIOdata;
unsigned char NetDoneWaitingTransfer;
unsigned char IndexCountF, IndexCountR, TransferBale, TransferNow, TransferDone;
unsigned char WrapStatusEnd, ManTransDelay, MTDcnt, MTDchk;
unsigned char ChamberEnable, FilmPassCount;
unsigned char ChamberAlarm, IP10_Delay, OverspeedDelay, TopUpCount, LubeTopUpCount,SecondScreen;
unsigned char CurrentSequenceMask, InitialKnivDownRoutineDone, PauseZone, FlashLedR2, TransferSeqPaused, Here[10];
unsigned short int PWMSlow1, PWMSlow2, PWMSlowTarget1, PWMSlowTarget2;
unsigned short int PWMChamber[3];
unsigned short int PWMmax, PWMmin, PWMerr, PWMstep, PLStable;
unsigned short int PWMIndexStep, oldMachineStatus;
unsigned long int RotateDebounce, RPMDebounce, TempKeyOp;
/*unsigned short int PWMBrakePower1;*/

float  IP02Freq, PulseFrequency ;
unsigned short rpm, FilmFrequency, analogue[8], SupplyVolts, Kniv1Pres, Kniv2Pres;

/*Debugging#############*/
unsigned char Flag;
/*Debugging#############*/
/*
struct frequency {
  unsigned char stat;
  unsigned short time, count, pulses, duration;
  }; */
struct frequency Shaft[1];

float Speed;

unsigned char Note;
unsigned short int NoteLength;

/* itu timer 0 variables */
unsigned short int t0_high;

unsigned short int countA0, A0count;
unsigned long int startA0, durationA0;

unsigned short int countB0, B0count;
unsigned long int startB0, startB0f, durationB0f;
/*                      */

/* itu timer 2 variables */
unsigned short int t2_high;

unsigned short int countA2, A2count;
unsigned long int startA2, durationA2;
/*                      */

void (*window)(void);

/*
struct ret {
  unsigned char sel;
  void (*lev)(void);
  };*/
struct ret returnto[20];

char buffer_memory[GRAPHICS_SIZE+128];
char adm[GRAPHICS_SIZE];

char s0tx_buff[256], s0tx_head, s0tx_tail;
char s0rx_buff[256], s0rx_head, s0rx_tail;
char s1tx_buff[256], s1tx_head, s1tx_tail;
char s1rx_buff[256], s1rx_head, s1rx_tail;

const struct baud_rates br[11] = {
         110, 3,  70,
         150, 2, 207,
         300, 2, 103,
         600, 1, 207,
        1200, 1, 103,
        2400, 0, 207,
        4800, 0, 103,
        9600, 0,  51,
       19200, 0,  25,
       31250, 0,  15,
       38400, 0,  12
       };

union OutsWide TestOp, Op, KeyOp, SeqOp;
union LEDsWide LedData;
union InpsWide TestIp, Ip;

const unsigned char IpDef[8] = {
 I05, I06, I07, I08, I09, I10, I11, I12 };

const unsigned char hex[16] = {
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
 };

const unsigned short int NoteFrequency[105] = {
/*   0 B0n 30.867Hz */ 64794, /* +23 for MIDI key */
/*   1 C1n 32.703Hz */ 61156,
/*   2 C1# 34.648Hz */ 57723,
/*   3 D1n 36.708Hz */ 54484,
/*   4 D1# 38.890Hz */ 51427,
/*   5 E1n 41.203Hz */ 48540,
/*   6 F1n 43.654Hz */ 45815,
/*   7 F1# 46.249Hz */ 43244,
/*   8 G1n 48.999Hz */ 40817,
/*   9 G1# 51.914Hz */ 38525,
/*  10 A1n 55.001Hz */ 36363,
/*  11 A1# 58.272Hz */ 34322,
/*  12 B1n 61.736Hz */ 32396,
/*  13 C2n 65.407Hz */ 30578,
/*  14 C2# 69.295Hz */ 28862,
/*  15 D2n 73.416Hz */ 27242,
/*  16 D2# 77.782Hz */ 25713,
/*  17 E2n 82.406Hz */ 24270,
/*  18 F2n 87.310Hz */ 22907,
/*  19 F2# 92.503Hz */ 21621,
/*  20 G2n 98.001Hz */ 20408,
/*  21 G2# 103.82Hz */ 19264,
/*  22 A2n 110.00Hz */ 18181,
/*  23 A2# 116.54Hz */ 17161,
/*  24 B2n 123.47Hz */ 16198,
/*  25 C3n 130.81Hz */ 15289,
/*  26 C3# 138.59Hz */ 14431,
/*  27 D3n 146.83Hz */ 13621,
/*  28 D3# 155.57Hz */ 12856,
/*  29 E3n 164.81Hz */ 12135,
/*  30 F3n 174.61Hz */ 11454,
/*  31 F3# 185.00Hz */ 10811,
/*  32 G3n 196.00Hz */ 10204,
/*  33 G3# 207.66Hz */ 9631,
/*  34 A3n 220.02Hz */ 9090,
/*  35 A3# 233.10Hz */ 8580,
/*  36 B3n 246.94Hz */ 8099,
/*  37 C4n 261.64Hz */ 7644,
/*  38 C4# 277.20Hz */ 7215,
/*  39 D4n 293.69Hz */ 6810,
/*  40 D4# 311.14Hz */ 6428,
/*  41 E4n 329.65Hz */ 6067,
/*  42 F4n 349.28Hz */ 5726,
/*  43 F4# 370.03Hz */ 5405,
/*  44 G4n 392.00Hz */ 5102,
/*  45 G4# 415.37Hz */ 4815,
/*  46 A4n 440.04Hz */ 4545,
/*  47 A4# 466.20Hz */ 4290,
/*  48 B4n 493.95Hz */ 4049,
/*  49 C5n 523.29Hz */ 3822,
/*  50 C5# 554.48Hz */ 3607,
/*  51 D5n 587.37Hz */ 3405,
/*  52 D5# 622.28Hz */ 3214,
/*  53 E5n 659.41Hz */ 3033,
/*  54 F5n 698.57Hz */ 2863,
/*  55 F5# 740.19Hz */ 2702,
/*  56 G5n 784.01Hz */ 2551,
/*  57 G5# 830.91Hz */ 2407,
/*  58 A5n 880.28Hz */ 2272,
/*  59 A5# 932.40Hz */ 2145,
/*  60 B5n 988.14Hz */ 2024,
/*  61 C6n 1046.6Hz */ 1911,
/*  62 C6# 1109.3Hz */ 1803,
/*  63 D6n 1175.1Hz */ 1702,
/*  64 D6# 1244.6Hz */ 1607,
/*  65 E6n 1319.3Hz */ 1516,
/*  66 F6n 1397.6Hz */ 1431,
/*  67 F6# 1480.4Hz */ 1351,
/*  68 G6n 1568.6Hz */ 1275,
/*  69 G6# 1662.5Hz */ 1203,
/*  70 A6n 1760.6Hz */ 1136,
/*  71 A6# 1865.7Hz */ 1072,
/*  72 B6n 1976.3Hz */ 1012,
/*  73 C7n 2094.2Hz */ 955,
/*  74 C7# 2219.8Hz */ 901,
/*  75 D7n 2350.2Hz */ 851,
/*  76 D7# 2490.7Hz */ 803,
/*  77 E7n 2638.5Hz */ 758,
/*  78 F7n 2797.2Hz */ 715,
/*  79 F7# 2963.0Hz */ 675,
/*  80 G7n 3139.7Hz */ 637,
/*  81 G7# 3327.8Hz */ 601,
/*  82 A7n 3521.1Hz */ 568,
/*  83 A7# 3731.3Hz */ 536,
/*  84 B7n 3952.6Hz */ 506,
/*  85 C8n 4192.9Hz */ 477,
/*  86 C8# 4444.4Hz */ 450,
/*  87 D8n 4705.9Hz */ 425,
/*  88 D8# 4987.5Hz */ 401,
/*  89 E8n 5277.0Hz */ 379,
/*  90 F8n 5602.2Hz */ 357,
/*  91 F8# 5934.7Hz */ 337,
/*  92 G8n 6289.3Hz */ 318,
/*  93 G8# 6666.7Hz */ 300,
/*  94 A8n 7042.3Hz */ 284,
/*  95 A8# 7462.7Hz */ 268,
/*  96 B8n 7905.1Hz */ 253,
/*  97 C9n 8403.4Hz */ 238,
/*  98 C9# 8888.9Hz */ 225,
/*  99 D9n 9434.0Hz */ 212,
/* 100 D9#  10000Hz */ 200,
/* 101 E9n  10582Hz */ 189,
/* 102 F9n  11236Hz */ 178,
/* 103 F9#  11905Hz */ 168,
/* 104 G9n  12579Hz */ 159 };

/*
struct tune {
  unsigned char Note;
  unsigned char Duration;
  };
*/
struct tune *Music;

struct tune const DixieLand[14] = {
/* --- */  0, 2,
/* G5n */ 56, 1,
/* E5n */ 53, 1,
/* C5n */ 49, 2,
/* C5n */ 49, 2,
/* C5n */ 49, 1,
/* D5n */ 51, 1,
/* E5n */ 53, 1,
/* F5n */ 54, 1,
/* G5n */ 56, 2,
/* G5n */ 56, 2,
/* G5n */ 56, 2,
/* E5n */ 53, 2,
/* --- */  0, 0 };

struct tune const Alarm01[5] = {
/* F5n */ 54, 2,
/* F6n */ 66, 2,
/* F5n */ 54, 2,
/* F6n */ 66, 2,
/* --- */  0, 0 };

const unsigned char *const ROLLER[8] = {
  ROLL01, ROLL02, ROLL03, ROLL04, ROLL05, ROLL06, ROLL07, ROLL08
  };

const unsigned char *const BALERREAR[11] = {
  REARBALE1, REARBALE2, REARBALE3, REARBALE4, REARBALE5, REARBALE6, REARBALE7, REARBALE8,
  REARBALE9, REARBALE10, REARBALE11
  };

const unsigned char *const CROPFEED[12] = {
  GRASS01, GRASS01, GRASS02, GRASS02,
  GRASS03, GRASS03, GRASS04, GRASS04,
  GRASS05, GRASS05, GRASS06, GRASS06
  };

const unsigned char *const KCropTypeBitMap[3] = {
		KSilage,
		KHay,
		KStraw
		};

const unsigned char *const KOnOff[2] = {
		Off,
		On
		};

const unsigned char *const KShortLong[3] = {
		KSHORT,
		KLONG,
		KMANUAL
		};
/*
  unsigned char min;
  unsigned char max;
  unsigned char def[MAXTYPE];
  unsigned short int type;
  unsigned char Tag;
  const struct pr *Name;
*/
const struct SeqFactors PF[MAXFACTOR] = {
/* min,     max, Full, Bale,     Type,   Name,              1234567890123456 */
   0,         1, {  0, 252}, RWRAP+TXT+PROO, AUTOTP, &s0377, /* '     AUTO TIP   ' */
   0,         2, {  0, 252}, RWRAP+TXT+PROO, SEQNUM, &s0377, /* '     BALE ONLY  ' */
   0,         2, {  0, 252}, RWRAP+TXT+PROO, DIVDEL, &s0377, /* '   Transfer Time' */
   2,         3, {  3, 252}, RWRAP+PLS+PROO, PULSER, &s0377, /* '  Slow Down Time' */ /* PULSE2 = TARGET - PULSER */
   0,         1, {  1, 252}, RWRAP+TXT+PROO, FILMBK, &s0206, /* '     Film Sensor' */
   0,         1, {  0,   0}, RWRAP+TXT+PROO, LUBERS, &s0299, /* 'Reset Lube Count' */
   1,         8, {  3, 252},  RTIP+NUM+PROO, LUBEDS, &s0321, /* '     Lube Dose  ' */
   
   0,        23, { 12, 252}, RWRAP+TIM+PROO, HRSTAG, &s0377, /* '     Hours      ' */
   0,        59, {  0, 252}, RWRAP+TIM+PROO, MINTAG, &s0377, /* '     Minutes    ' */

   0,       250, { 30, 252},  RNET+DLT+PROT, DELYLB, &s0231, /* '     Baler Full ' */
   0,        30, {  5, 252},  RNET+DLT+PROT, DELYSB, &s0377, /* 'Short Baler Full' */
   0,       250, { 28, 252},  RNET+DLT+PROT, DELYBC, &s0232, /* '     Net On     ' */
   0,       250, { 10, 252},  RNET+DLT+PROT, DELYCD, &s0233, /* '   Pre Net Wait ' */
  10,        99, { 20, 252},  RNET+DLS+PROT, DELYNT, &s0391, /* '   Net error    ' */
/* 0,       100, { 50, 252},  RNET+PER+PROO, PWMBP1, &s0383, */ /* ' Net Brake Power' */   
   0,       250, {  2, 252}, RWRAP+DLT+PROT, DELYDE, &s0234, /* '   Post Net Wait' */

   0,       250, { 50, 252}, RWRAP+DLT+PROT, DELYEF, &s0377, /* 'Open      Lid Up' */
   0,       250, {  6, 252}, RWRAP+DLT+PROT, DELYFG, &s0377, /* 'Open     Lid Up+' */
   0,       250, {  2, 252}, RWRAP+DLT+PROT, DLYOCD, &s0377, /* 'Open       Pause' */
   0,       250, {  2, 252}, RWRAP+DLT+PROT, DIVSRT, &s0377, /* 'Open Divtr Short' */
   0,       250, { 12, 252}, RWRAP+DLT+PROT, DIVLNG, &s0377, /* 'Open Divtr Long ' */
   0,       250, {120, 252}, RWRAP+DLT+PROT, DLYOEF, &s0377, /* 'Open  Segment Up' */
   0,       250, {  2, 252}, RWRAP+DLT+PROT, DLYOFG, &s0377, /* 'Open Segment Up+' */
   0,       250, {  0, 252}, RWRAP+DLT+PROT, PAUSRT, &s0237, /* 'Pause Open Short' */
   0,       250, {  8, 252}, RWRAP+DLT+PROT, PAULNG, &s0294, /* 'Pause Open Long ' */
   0,       250, {  0, 252}, RWRAP+DLT+PROT, DLYOKL, &s0377, /* 'Close   Diverter' */
   0,       250, {  0, 252}, RWRAP+DLT+PROT, DELYGH, &s0377, /* 'Close      Pause' */
   0,       250, { 40, 252}, RWRAP+DLT+PROT, DELYJK, &s0377, /* 'Close    Travel+' */
   0,       250, { 15, 252}, RWRAP+DLT+PROT, DELYOT, &s0377, /* 'Delay Open Time ' */
   0,       250, { 20, 252}, RWRAP+DLT+PROT, DELYPT, &s0377, /* 'Delay Pause Time' */

   0,       250, {  0, 252}, RWRAP+DLT+PROT, DELYKL, &s0239, /* 'Wrap Start Pause' */
   1,        30, { 30, 252}, RWRAP+DLT+PROT, DELYLM, &s0240, /* '     Ramp Up    ' */
   0,        30, { 10, 252}, RWRAP+DLT+PROT, DELYLN, &s0241, /* '     Hold Delay ' */
   1,         4, {  2, 252}, RWRAP+PLS+PROT, PULSEP, &s0242, /* ' Cut Tie Release' */
  10,       100, { 50, 252}, RWRAP+DLT+PROT, DELYPQ, &s0242, /* ' Cut Tie Release' */
   0,        30, {  0, 252}, RWRAP+DLT+PROT, DELYRS, &s0244, /* ' Delay Ramp Down' */
   0,        40, { 25, 252}, RWRAP+DLT+PROT, DELYST, &s0245, /* ' Ramp Down Time ' */
   0,        40, { 10, 252}, RWRAP+DLT+PROT, DELYUV, &s0246, /* '    Wrapped Beep' */
   1,       100, { 50, 252}, RWRAP+PER+PROT, PWMCS1, &s0377, /* ' Chamber Speed 1' */
   1,       100, { 75, 252}, RWRAP+PER+PROT, PWMCS2, &s0377, /* ' Chamber Speed 2' */
   1,       100, {100, 252}, RWRAP+PER+PROT, PWMCS3, &s0377, /* ' Chamber Speed 3' */
   /*0,       100, { 50, 252},  RTIP+DLT+PROT, DELYWX, &s0247,*/ /* 'Tip Wrapped Bale' */
   0,       100, { 50, 252},  RTIP+DLT+PROT, DELWX1, &s0247, /* 'Tip Wrapped Bale' */
   0,       100, { 40, 252},  RTIP+DLT+PROT, DELWX2, &s0395, /* 'Tip Bale French ' */
   5,        30, {  1, 252},  RTIP+DLT+PROT, DELYXY, &s0248, /* '    Pause Tipped' */
   0,       100, { 40, 252},  RTIP+DLT+PROT, DELYYZ, &s0249, /* '     Tip Return+' */
 
   0,        99, { 20, 252}, RCTOP+DLS+PROT, DLYT03, &s0315, /* '2nd Topup Wait  ' */
   0,        99, {  0, 252}, RCTOP+DLT+PROT, DLYT04, &s0316, /* '2nd Topup Length' */

   1,        50, {  6, 252}, RWRAP+DLT+PROT, ROTDEB, &s0250, /* ' Rotate Debounce' */
   0,       100, { 10, 252}, RWRAP+DLT+PROT, DELAYL, &s0377, /* '   Ignore Rotate' */
   0,       100, { 25, 252}, RWRAP+DLT+PROT, DELAYE, &s0252, /* '     Ignore E-1 ' */

   1,        30, { 30, 252}, RWRAP+DLM+PROT, RPMDEB, &s0272, /* '    RPM Debounce' */

   1,        50, {  2, 252}, RWRAP+DLT+PROT, MOTDEB, &s0253, /* '  Motor Debounce' */
   1,       240, { 24, 252}, RWRAP+PLS+PROT, MOTPPR, &s0254, /* '   Motor PPW rev' */
   0,        10, {  2, 252}, RWRAP+PLR+PROT, MOTALM, &s0255, /* '     Motor Slip ' */

   5,        20, {  8, 252}, RWRAP+RPM+PROT, RPMSLO, &s0256, /* '     Slow RPM   ' */
   1,       100, { 35, 252}, RWRAP+PER+PROT, PWMSL1, &s0377, /* ' Index Slow PWM ' */
   1,       100, { 35, 252}, RWRAP+PER+PROT, PWMSL2, &s0302, /* ' Slow Speed PWM ' */
   0,        99, { 44, 252}, RWRAP+PER+PROT, MAXPWM, &s0258, /* '  Max PWM Value ' */
   0,        99, { 33, 252}, RWRAP+PER+PROT, MINPWM, &s0259, /* '  Min PWM Value ' */
   1,       250, { 10, 252}, RWRAP+PDP+PROT, ERRPWM, &s0260, /* '  PWM Step (Max)' */
   0,        99, {  0, 252}, RWRAP+PLR+PROT, PLSTAB, &s0267, /* 'Ramp Pause Count' */
   0,        50, { 18, 252}, RWRAP+PLR+PROT, PLSTRT, &s0290, /* '   Control Count' */

   0,       100, { 40, 252}, RKNIV+DLT+PROT, DLYU01, &s0274, /* '     Knives Down' */
   0,       100, { 23, 252}, RUNBK+DLT+PROT, DLYU02, &s0275, /* '     Knives Up  ' */
   0,       100, { 40, 252}, RUNBK+DLT+PROT, DLYU03, &s0276, /* '     Floor Down ' */
   0,       100, { 60, 252}, RUNBK+DLT+PROT, DLYU04, &s0277, /* '     Floor Up   ' */
   /* Iss-109 - For old knife and floor routines (RELIEF_VAVLE) */
   0,       100, { 20, 252}, RUNBK+DLT+PROT, DLYV01, &s0274, /* '     Knives Down' */
   0,       100, { 23, 252}, RUNBK+DLT+PROT, DLYV02, &s0275, /* '     Knives Up  ' */
   0,       100, { 26, 252}, RUNBK+DLT+PROT, DLYV03, &s0276, /* '     Floor Down ' */
   0,       100, { 33, 252}, RUNBK+DLT+PROT, DLYV04, &s0277, /* '     Floor Up   ' */
   /* End - for old knife and floor routines (RELIEF_VAVLE) */
   0,        50, {  7, 252}, RWRAP+DLT+PROT, PDLOEF, &s0288, /* '    Pressure OEF' */
  20,        40, { 30, 252}, RWRAP+HR0+PROT, LUBECK, &s0295, /* '   Lube Interval' */
   
   1,        20, { 10, 252}, RCTPL+DLS+PROT, DLUBEF, &s0322, /* '  Lube Frequency' */
   0,        20, { 10, 252}, RCTPL+DLT+PROT, DLUBED, &s0323, /* '   Lube Duration' */

   0,        30, { 10, 252}, RWRAP+PLS+PROT, IDXCNT, &s0308, /* 'Index Slow Count' */
   0,        99, { 20, 252}, RWRAP+PDP+PROT, IDXPWM, &s0309, /* 'Index Slow PWM  ' */
   0,       250, {200, 252}, RWRAP+RPM+PROT, IP2FRQ, &s0390, /* 'Overspeed       ' */
   0,         1, {  1, 252}, RWRAP+TXT+PROT, RESTRT, &s0310, /* '  Power Restart ' */

   0,        50, {  2, 252}, RWRAP+DLT+PROT, DELYVW, &s0313, /* '  Overshoot Time' */
   0,        50, {  2, 252}, RWRAP+DLT+PROT, DELYZA, &s0314, /* 'C & H Open Delay' */
   0,        10, {  4, 252}, RWRAP+NUM+PROT, PLSFR1, &s0319, /* 'Extra Wrap After' */
   1,        10, {  5, 252}, RWRAP+NUM+PROT, PLSFR2, &s0320, /* 'Extra Wrap Count' */
   0,        99, {  4, 252}, RWRAP+NUM+PROT, PLSFR3, &s0320, /* ' rev stop count ' */

   0,        99, {  9, 252}, RWRAP+NUM+PROT, FILMPS, &s0326, /* 'Film Check Count' */
   0, MAXLANG-1, {  0, 252}, RWRAP+TXT+PROT, LANGUA, &s0342, /* '     Language   ' */
   0,         1, {  0, 252}, RWRAP+TXT+PROT, SIODAT, &s0377, /* '     Ex Trace   ' */
   0,         1, {  0,   0}, RWRAP+TXT+PROT, FRESET, &s0377, /* '     Set Default' */

   0,        50, { 15, 252}, RWRAP+DLT+NONP, PDELEF, &s0377, /* '     Pressure EF' */

   0,        50, { 30, 252},  RTIP+DLT+NONP, BDELY1, &s0228, /* '\002               ' */
   0,        50, { 30, 252},  RTIP+DLT+NONP, BDELY2, &s0228, /* '\002               ' */
   0,       250, { 80, 252},  RTIP+DLT+NONP, BDELY3, &s0228, /* '\002               ' */
   0,        50, { 10, 252},  RTIP+DLT+NONP, DELAY3, &s0228, /* 'Unwrapped alarm delay' */
   0,       100, { 50, 252},  RTIP+DLT+NONP, DELYWX, &s0228, /* 'Tip Wrapped Bale' */
   0,       250, {  0, 252}, RWRAP+DLT+PROT, DELAY4, &s0377, /* 'Open      Lid Up' */
   0,       250, {  0, 252}, RWRAP+DLT+PROT, DELAY5, &s0377, /* '                ' */
   0,       250, { 50, 252}, RWRAP+DLT+PROT, DELAY6, &s0377, /* '                ' */
   0,       250, { 20, 252},  RNET+DLT+NONP, DELAY7, &s0377, /* '                ' */

   0,       250, { 30, 252},  RNET+DLT+NONP, DELYAB, &s0228, /* '\002               ' */

   0,        50, {  0, 252},  RNET+DLT+NONP, DELYNU, &s0228, /* '\002               ' */
   0,        50, {  0, 252},  RNET+DLT+NONP, DELYNV, &s0228, /* '\002               ' */
   0,        50, {  0, 252},  RNET+DLT+NONP, DELYNW, &s0228, /* '\002               ' */

   0,        10, {  1, 252}, RWRAP+PLS+NONP, PULSET, &s0228, /* '\002               ' */
   0,        99, {  0, 252}, RWRAP+PLS+NONP, PULSEU, &s0228, /* '\002               ' */
   0,       250, {  2, 252}, RWRAP+DLT+NONP, DLYODE, &s0228, /* '\002               ' */
   0,       250, {  1, 252}, RWRAP+DLT+PROT, DLYOGH, &s0228, /* '\002               ' */
   0,        50, {  5, 252}, RWRAP+DLT+NONP, DELYOR, &s0228, /* '\002               ' */
   0,        50, { 10, 252}, RWRAP+DLT+NONP, DELYK2, &s0228, /* '\002               ' */
   0,        50, {  1, 252}, RWRAP+DLT+NONP, DELYZB, &s0228, /* '\002               ' */
   0,        50, {  5, 252}, RWRAP+DLT+NONP, DELYFP, &s0228, /* '\002               ' */
   0,        50, { 20, 252}, RWRAP+DLT+NONP, DELYFT, &s0228, /* '\002               ' */
   0,        50, { 20, 252}, RWRAP+DLT+NONP, DELYDX, &s0228, /* '\002               ' */
   0,        50, {100, 252}, RWRAP+DLT+NONP, DELYHI, &s0228, /* '\002               ' */
   0,        50, { 10, 252}, RWRAP+DLT+NONP, DELYW1, &s0228, /* '\002               ' */

   0,        10, {  2, 252}, RFILM+PLS+NONP, PLSF01, &s0228, /* '\002               ' */
   0,        50, {  0, 252}, RKNIV+DLT+NONP, DLYUS1, &s0228, /* '\002               ' */
   0,        50, {  0, 252}, RUNBK+DLT+NONP, DLYUS4, &s0228, /* '\002               ' */
   0,        50, {  0, 252}, RUNBK+DLT+NONP, DLYUS3, &s0228, /* '\002               ' */
   0,        50, {  5, 252}, RUNBK+DLT+NONP, DLYU05, &s0228, /* '\002               ' */
   0,       100, { 60, 252}, RFTOP+DLT+NONP, DLYU06, &s0228, /* '\002               ' */
   0,        50, {  5, 252}, RKNIV+DLT+NONP, DLYU07, &s0228, /* '\002               ' */
   0,        50, {  5, 252}, RKNIV+DLT+NONP, DLYU08, &s0228, /* '\002               ' */
   0,        50, {  2, 252}, RUNBK+DLT+NONP, DLYU09, &s0228, /* '\002               ' */
   0,        50, {  1, 252}, RUNBK+DLT+NONP, DLYU10, &s0228, /* '\002               ' */

   0,        50, {  0, 252}, RKNIV+DLT+NONP, DLYKS1, &s0228, /* '\002               ' */
   0,        50, { 30, 252}, RKNIV+DLT+NONP, DLYK01, &s0228, /* '\002               ' */
   /* Iss-109 - For old knife and floor routines (RELIEF_VAVLE) */
   0,        50, {  0, 252}, RUNBK+DLT+NONP, DLYVS1, &s0228, /* '\002               ' */
   0,        50, {  0, 252}, RUNBK+DLT+NONP, DLYVS2, &s0228, /* '\002               ' */
   0,        50, {  0, 252}, RUNBK+DLT+NONP, DLYVS3, &s0228, /* '\002               ' */
   0,        50, {  1, 252}, RUNBK+DLT+NONP, DLYV05, &s0228, /* '\002               ' */
   0,        50, { 10, 252}, RUNBK+DLT+NONP, DLYV06, &s0228, /* '\002               ' */
   0,        50, {  2, 252}, RUNBK+DLT+NONP, DLYV07, &s0228, /* '\002               ' */
   0,        50, { 10, 252}, RUNBK+DLT+NONP, DLYV08, &s0228, /* '\002               ' */
   0,        50, {  2, 252}, RUNBK+DLT+NONP, DLYV09, &s0228, /* '\002               ' */
   0,        50, {  1, 252}, RUNBK+DLT+NONP, DLYV10, &s0228, /* '\002               ' */
   /* End - Iss-109 - For old knife and floor routines (RELIEF_VAVLE) */
#if 0   
   0,        50, {  5, 252}, RKNIV+DLT+NONP, DLYT05, &s0228, /* '\002               ' */
   0,        50, {  5, 252}, RKNIV+DLS+NONP, DLYT06, &s0228, /* '\002               ' */
#endif   
  
   0,        50, { 15, 252}, RCTOP+DLS+NONP, DLYT01, &s0228, /* '\002               ' */
   0,        50, { 15, 252}, RCTOP+DLT+NONP, DLYT02, &s0228, /* '\002               ' */

   0,        10, {  3, 252}, RPAUS+PLS+NONP, PLSPAS, &s0228, /* '\002               ' */
   0,        50, { 10, 252}, RFILM+DLT+NONP, DELYF1, &s0228  /* '\002               ' */
   };
unsigned char FA[MAXFACTOR];

unsigned char DelPul[FCLAST];     

/*
  unsigned long int Switch;
  unsigned char Act;
  unsigned char Tag;
  unsigned short int type;
*/ 
const struct Switches SW[MAXSWITCH] = {
   CHAMBER,   CLOSED, RSWTCA, RWRAP, /* real switch */

   NETCUT,    CLOSED, RSWTCB, RNET,  /* real switch */
   NETCUT,    CLOSED, RSWTCE, RNET,  /* real switch */
   NETCUT,      OPEN, RSWTCF, RNET,  /* real switch */

   TURNTABLE,   OPEN, RSWTCC, RWRAP, /* real switch */
   TURNTABLE, CLOSED, RSWTCD, RWRAP, /* real switch */
   TURNTABLE, CLOSED, RSWTCG, RWRAP, /* real switch */

   AUTOSTART, CLOSED, VSWTCA, RNET,  /* virtual switch */
   TIPSTART,  CLOSED, VSWTCB, RTIP,  /* virtual switch */
   TRANSFER,  CLOSED, VSWTCC, RTIP,  /* virtual switch */
   CTOPUP,    CLOSED, VSWTCD, RCTOP, /* virtual switch */
   FTOPUP,    CLOSED, VSWTCF, RFTOP, /* virtual switch */
   LTOPUP,    CLOSED, VSWTCE, RCTPL, /* virtual switch */

   PRESSURE1, CLOSED, PSWTEF, RWRAP, /* real switch  */
   PRESSURE1, CLOSED, PSWOEF, RWRAP, /* real switch - IP05 */

   TIPUP,     CLOSED, RSWTCH, RTIP,  /* real switch */
   TIPUP,       OPEN, RSWTCI, RTIP  /* real switch */
   /*
   LOWPRES,   CLOSED, VSWTLP, RKNIV, / * Analog virtual switch * /
   HIGHPRES,  CLOSED, VSWCHP, RKNIV, / * Analog virtual switch * /
   LOWPRES,   CLOSED, VSWCLP, RKNIV  / * Analog virtual switch * / */
   };

unsigned char SA[MAXSWITCH];

unsigned char SwLook[SWLAST];                

/*
  unsigned char  Dlp;
  unsigned char  Pdl;
  unsigned char  Wdl;
  unsigned long  opO;
  unsigned long  opA;
  unsigned char  Zne;
  unsigned short Seq;
  unsigned short Act;
*/
const struct Sequence SQ[MAXSEQ] = {
/* Film Break */
      0, DELYF1,      0,          NoneOn,      NoneOff,   Zone15, O_Flm, EnableAndLoad | CountingOff | TimingOn,
 DELYF1, PLSF01,      0,          NoneOn,      NoneOff, NoChange, O_Flm, DelayOrPulseWait | CountingOn,
 PLSF01,      0,      0,          NoneOn,  AllOff & ~(O02 | O18), Zone43, O_Flm, DelayOrPulseWait | CountingOff | SequenceReset,

 /* Wrapping paused by pressing R1 */
 	 	 	0, PLSPAS,      0,          NoneOn,      NoneOff,   Zone15, O_Ps, EnableAndLoad,
 PLSPAS,      0,      0,    			NoneOn,       AllOff,   Zone72, O_Ps, DelayOrPulseWait | CountingOff | TimingOff | SequenceReset,
/* Dispenser Safety */
      /*0, DELYF1,      0,          NoneOn,       AllOff, NoChange, O_Ds, EnableAndLoad | CountingOn | TimingOff | SequenceReset,*/

/* Iss-97, Knives down */
 DLYUS1, DLYU07,      0,       O07 | O10,      NoneOff,   Zone22, O_All, DelayOrPulseWait,
 DLYU07, DLYU01,      0,             O16,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 DLYU01, DLYU08/*0*/, 0,      NoneOn,  /*O07|O10|*/O16, NoChange, O_All, DelayOrPulseWait,
 DLYU08,      0,      0,          NoneOn,      O07|O10,   Zone50, O_All, DelayOrPulseWait,
 
 /* Iss-97, new unblock sequence (PRRESURE_SENSING) */
 DLYUS3, DLYU03,      0,             O16,      NoneOff,   Zone24, O_All, DelayOrPulseWait,
 DLYU03,      0,      0,          NoneOn,          O16,   Zone23, O_All, DelayOrPulseWait,

 /* Iss-97, new reset floor sequence (PRRESURE_SENSING) */
 DLYUS4, DLYU04,      0,             O15,      NoneOff,   Zone29, O_All, DelayOrPulseWait,
 DLYU04, DLYU05,      0,          NoneOn,          O15, NoChange, O_All, DelayOrPulseWait,
 DLYU05,      0,      0,          NoneOn,      NoneOff,   Zone34, O_All, DelayOrPulseWait,
 
/* Iss-109 change - Added old knive top-up and floor unblock routines ( RELIEF_VALVE ) */
 /* Unblock 1 */
 DLYVS1, DLYV01,      0,             O15,      NoneOff,   Zone62, O_All, DelayOrPulseWait,
 DLYV01, DLYV05,      0,          NoneOn,          O15, NoChange, O_All, DelayOrPulseWait,
 DLYV05, DLYV09,      0,             O07,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 DLYV09, DLYV03,      0,             O16,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 DLYV03, DLYV06,      0,          NoneOn,          O16, NoChange, O_All, DelayOrPulseWait,
 DLYV06,      0,      0,          NoneOn,          O07,   Zone63, O_All, DelayOrPulseWait,

 /* Unblock 2 */
 DLYVS2, DLYV07,      0,             O07,      NoneOff,   Zone64, O_All, DelayOrPulseWait,
 DLYV07, DLYV04, DLYVS2,             O15,      NoneOff, NoChange, O_All, DelayOrPulseWait | WaitForWdl,
 DLYV04, DLYV08, DLYVS2,          NoneOn,          O15, NoChange, O_All, DelayOrPulseWait | WaitForWdl,
 DLYV08,      0, DLYVS2,          NoneOn,          O07,   Zone65, O_All, DelayOrPulseWait | WaitForWdl,

 /* Unblock 3 */
 DLYVS3, DLYV07,      0,             O07,      NoneOff,   Zone64, O_All, DelayOrPulseWait,
 DLYV07, DLYV04, DLYVS3,             O15,      NoneOff, NoChange, O_All, DelayOrPulseWait | WaitForWdl,
 DLYV04, DLYV08, DLYVS3,          NoneOn,          O15, NoChange, O_All, DelayOrPulseWait | WaitForWdl,
 DLYV08, DLYV10, DLYVS3,          NoneOn,          O07, NoChange, O_All, DelayOrPulseWait | WaitForWdl,
 DLYV10, DLYV02, DLYVS3,             O16,      NoneOff, NoChange, O_All, DelayOrPulseWait | WaitForWdl,
 DLYV02,      0, DLYVS3,          NoneOn,          O16,   Zone66, O_All, DelayOrPulseWait | WaitForWdl,

 /* Knives 1 */
 DLYKS1, DLYK01,      0,             O15,      NoneOff,   Zone67, O_All, DelayOrPulseWait,
 DLYK01,      0,      0,          NoneOn,          O15,   Zone68, O_All, DelayOrPulseWait,

/* End - old knive top-up and floor unblock routines ( RELIEF_VALVE ) */
  
/* Netting  O_Net = O_All | O_Flm */
 VSWTCA, DELYAB,      0,          NoneOn,      NoneOff,   Zone01, O_Net, SwitchWait | TimingOn,
 DELYAB,      0,      0,          NoneOn,      NoneOff, NoChange, O_Net, DelayOrPulseWait,
/* if NetCut(IP09) is already closed before NetOn(OP02) is on */
 RSWTCE, DELYNU, DELYAB,          NoneOn,      NoneOff,   Zone28, O_Net, SwitchWait | WaitForWdl,
      0, RSWTCE, DELYNV,          NoneOn,      NoneOff, NoChange, O_Net, CancelIfDone,
 DELYNU,      0,      0,          NoneOn,      NoneOff, NoChange, O_Net, DelayOrPulseWait,
/* NetCut Open */
 RSWTCF, DELYNV, DELYAB,          NoneOn,      NoneOff,   Zone02, O_Net, SwitchWait | WaitForWdl,
      0, RSWTCF, DELYNU,          NoneOn,      NoneOff, NoChange, O_Net, CancelIfDone,
 DELYNV, DELYNW,      0,          NoneOn,      NoneOff, NoChange, O_Net, DelayOrPulseWait,

 DELYNW, DELYBC,      0,             O02,      NoneOff,   Zone73, O_Net, DelayOrPulseWait, /* OP2 turns On - Pause Zone begins here */
      0, DELYNT, DELYNW,          NoneOn,      NoneOff, NoChange, O_Net, EnableAndLoad | WaitForWdl, /*Loaded 20 second delay for net warning*/
/* if NetCut(IP09) has not closed after time out */
 DELYNT,      0,      0,          NoneOn,          O02,   Zone28, O_Net, DelayOrPulseWait,
      0, RSWTCB, DELYNT,          NoneOn,      NoneOff, NoChange, O_Net, CancelIfDone,
 DELYBC, DELYCD,      0,          NoneOn,          O02,   Zone03, O_Net, DelayOrPulseWait, /* OP2 turns Off */
/* DELYBC, DLYT05,      0,             O07,          O02,   Zone03, O_Net, DelayOrPulseWait, */
 
 DELYCD,      0,      0,          NoneOn,      NoneOff, NoChange, O_Net, DelayOrPulseWait,
 RSWTCB, DELAY7, DELYCD,          NoneOn,      NoneOff,   Zone04, O_Net, SwitchWait | WaitForWdl, /* IP09 closes here */
 DELAY7,      0,      0,          NoneOn,      NoneOff, NoChange, O_Net, DelayOrPulseWait, /* Iss_34: 2 second delay */
/* Tip, VSWTCB checked at end */
/* VSWTCB, DELYWX,      0,       O13 | O08,      NoneOff,   Zone14, O_All, SwitchWait | TimingOn,*/
      0, BDELY2, VSWTCB,             O17,      NoneOff, NoChange, O_All, EnableAndLoad | WaitForSW,
 BDELY2,      0,      0,          NoneOn,          O17, NoChange, O_All, DelayOrPulseWait,
 DELYWX, DELYXY,      0,          NoneOn,    O13 | O08, NoChange, O_All, DelayOrPulseWait,
 DELYXY,      0,      0,             O09,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 RSWTCH, DELYYZ, DELYXY,          NoneOn,      NoneOff,   Zone16, O_All, SwitchWait | WaitForWdl,
 DELYYZ,      0,      0,          NoneOn,          O09, NoChange, O_All, DelayOrPulseWait,
 
/* Wrapping - Transfer */
 VSWTCC, DELYDE, DELYCD,          NoneOn,      NoneOff,   Zone05, O_All, SwitchWait | WaitForWdl | ResetCurrentCount | CountingOff,
      0, BDELY1, VSWTCC,             O17,      NoneOff, NoChange, O_All, EnableAndLoad | WaitForSW,
 BDELY1,      0,      0,          NoneOn,          O17, NoChange, O_All, DelayOrPulseWait,
 DELYDE, DELAY4,      0,       O13 | O12,      NoneOff,   Zone17, O_All, DelayOrPulseWait,
 DELAY4, DELAY5,      0,          NoneOn,          O12,   Zone17, O_All, DelayOrPulseWait,
 DELAY5, DELAY6,      0,             O12,      NoneOff,   Zone17, O_All, DelayOrPulseWait,
 
/* wait delay DELYDE changed to DLYODE */
      0, PDELEF, DLYODE,          NoneOn,      NoneOff,   Zone20, O_All, EnableAndLoad | WaitForWdl,
 PDELEF,      0,      0,          NoneOn,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 PSWTEF, DELYFG, PDELEF,/* IP05 */NoneOn,      NoneOff,   Zone30, O_All, SwitchWait | WaitForWdl,
 DELAY6, DELYFG,      0,          NoneOn,      NoneOff,   Zone30, O_All, DelayOrPulseWait,
      0, PSWTEF, DELYEF,          NoneOn,      NoneOff, NoChange, O_All, CancelIfDone, /* not executed */
 DELYFG,      0,      0,          NoneOn,          O12,   Zone31, O_All, DelayOrPulseWait,
 
/* DELYFG is 2.3sec (=DLYU02) for the first time and 0.6sec afterwards. */
      0, DLYOCD, DELYDE,          NoneOn,      NoneOff, NoChange, O_All, EnableAndLoad | WaitForWdl,
 DLYOCD, DLYODE,      0,          NoneOn,      NoneOff, NoChange, O_All, DelayOrPulseWait,

 DLYODE, DLYOEF,      0,          NoneOn,      NoneOff, NoChange, O_All, DelayOrPulseWait,
/* wait delay DLYODE changed to DELYEF */
      0, PDLOEF, DELYEF,          NoneOn,      NoneOff,   Zone20, O_All, EnableAndLoad | WaitForWdl, /* not executed */
 PDLOEF,      0,      0,          NoneOn,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 PSWOEF, DLYOFG, PDLOEF,          NoneOn,      NoneOff,   Zone21, O_All, SwitchWait | WaitForWdl, /* Ip05 closed */
 DLYOEF, DLYOFG,      0,          NoneOn,      NoneOff,   Zone21, O_All, DelayOrPulseWait,
      0, PSWOEF, DLYOEF,          NoneOn,      NoneOff, NoChange, O_All, CancelIfDone,

 DLYOFG, DLYOGH,      0,          NoneOn,      NoneOff,   Zone41, O_All, DelayOrPulseWait,
 DLYOGH,      0,      0,          NoneOn,      NoneOff,   Zone19, O_All, DelayOrPulseWait,

      0, DELYGH, DLYOGH,          NoneOn,      NoneOff, NoChange, O_All, EnableAndLoad | WaitForWdl,
 DELYGH, DELYHI,      0,             O11,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 DELYHI,      0,      0,          NoneOn,          O11,   Zone44, O_All, DelayOrPulseWait,
 /*Wating for IP08 to close again*/
 RSWTCA, DELYJK, DELYGH,          NoneOn,          O13,   Zone06, O_All, SwitchWait | WaitForWdl | CountingOff,
      0, DELYFP, RSWTCA,          NoneOn,      NoneOff,   Zone38, O_All, EnableAndLoad | WaitForSW,
      0, DLYOKL, RSWTCA,          NoneOn,    O15 | O16,   Zone37, O_All, EnableAndLoad | WaitForSW,
/* \/ Iss-099 change \/ */      
      /*0, DLYU06, RSWTCA,          NoneOn,      NoneOff,   Zone39, O_All, EnableAndLoad | WaitForSW,*/
/* /\ Iss-099 change /\ */      
 DLYOKL,      0,      0,          NoneOn,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 DELYJK,      0,      0,          NoneOn,          O11,   Zone36, O_All, DelayOrPulseWait,
 DELYFP, DELYFT,      0,          NoneOn,      NoneOff,   Zone69, O_All, DelayOrPulseWait,
 DELYFT, DELYDX,      0,          NoneOn,      NoneOff,   Zone70, O_All, DelayOrPulseWait,
 DELYDX,      0,      0,          NoneOn,          O07, NoChange, O_All, DelayOrPulseWait,
 
 VSWTCF, DLYU06, RSWTCA,          NoneOn,      NoneOff,   Zone39, O_All, SwitchWait | WaitForSW, 
 DLYU06,      0,      0,          NoneOn,          O15,   Zone57, O_All, DelayOrPulseWait,
/* Wrapping - Rotation */
      0, DELYKL, RSWTCA,          NoneOn,      NoneOff, NoChange, O_All, EnableAndLoad | WaitForSW,
 DELYKL, DELYK2,      0,       O13 | O03,      NoneOff,   Zone26,  O_S1, DelayOrPulseWait | CountingOff,
 DELYK2,      0,      0,          NoneOn,      NoneOff, NoChange,  O_S1, DelayOrPulseWait,
 RSWTCG,      0, DELYK2,          NoneOn,      NoneOff, NoChange,  O_S1, SwitchWait | WaitForWdl | CountingOn,

      0, DELYLN, DELYKL,          NoneOn,      NoneOff, NoChange,  O_S1, EnableAndLoad | WaitForWdl,
 DELYLN,      0,      0,          NoneOn,          O13, NoChange,  O_S1, DelayOrPulseWait,

 PULSEP, DELYPQ,      0,             O06,      NoneOff,   Zone07,  O_S1, DelayOrPulseWait,
 /* DELYPQ,      0,      0,          NoneOn,          O06,   Zone08,  O_S1, DelayOrPulseWait,*/
 DELYPQ, DELYW1,      0,          NoneOn,          O06,   Zone08,  O_S1, DelayOrPulseWait,
 /* Added 1 sec delay on 20100305 by ZW */
 DELYW1, 	  	0, 	  	0, 		  NoneOn, 	   NoneOff,   Zone47,  O_S1, DelayOrPulseWait,
 
 PULSER, DELYRS,      0,          NoneOn,      NoneOff,   Zone09,  O_S1, DelayOrPulseWait, 
 DELYRS,      0,      0,          NoneOn,      NoneOff,   Zone10,  O_S1, DelayOrPulseWait,

 PULSET,      0,      0,             O05,      NoneOff,   Zone11,  O_S1, DelayOrPulseWait,
      0, PLSTRT, PULSET,          NoneOn,      NoneOff, NoChange,  O_S1, EnableAndLoad | WaitForWdl,
 PLSTRT,      0,      0,          NoneOn,      NoneOff,   Zone27,  O_S1, DelayOrPulseWait,

 PULSEU, DELYUV,      0,          NoneOn,      NoneOff,   Zone12,  O_S1, DelayOrPulseWait | CountingOff,
      0, DELYZB, PULSEU,          NoneOn,      NoneOff, NoChange,  O_S1, EnableAndLoad | WaitForWdl,
 DELYUV,      0,      0,          NoneOn,      NoneOff,   Zone33,  O_S1, DelayOrPulseWait,
 DELYZB,      0,      0,          NoneOn,      NoneOff, NoChange,  O_S1, DelayOrPulseWait,

 RSWTCC, DELYVW, DELYZB,          NoneOn,      NoneOff, NoChange,  O_S1, SwitchWait | WaitForWdl,
 DELYVW, DELYOR,      0,          NoneOn,          O03, NoChange,  O_S1, DelayOrPulseWait,
 DELYOR, DELYZA,      0,             O04,      NoneOff, NoChange,  O_S1, DelayOrPulseWait,
 DELYZA,      0,      0,          NoneOn,    O13 | O05,   Zone35,  O_S1, DelayOrPulseWait,
 RSWTCD,      0, DELYOR,          NoneOn,          O04,   Zone13,  O_S1, SwitchWait | WaitForWdl,

 DELYKL, DELAY3, DLYOKL,          NoneOn,      NoneOff, NoChange,  O_S2, DelayOrPulseWait | WaitForWdl,
 DELAY3, DELYUV,      0,          NoneOn,      NoneOff,   Zone12,  O_S2, DelayOrPulseWait,
 DELYUV,      0,      0,          NoneOn,      NoneOff,   Zone18,  O_S2, DelayOrPulseWait,

 VSWTCD, DLYT01,      0,          NoneOn,      NoneOff, NoChange, O_All, SwitchWait | TimingOn,
 DLYT01, DLYT02,      0,   NoneOn/*O11*/,      NoneOff,   Zone71, O_All, DelayOrPulseWait, /* Iss-124, OP11 is now turned on in Zone50 only if OP3 is ON */
 DLYT02, DLYT03,      0,          NoneOn,          O11, NoChange, O_All, DelayOrPulseWait,
 DLYT03, DLYT04,      0,   NoneOn/*O11*/,      NoneOff,   Zone71, O_All, DelayOrPulseWait,
 DLYT04,      0,      0,          NoneOn,          O11,   Zone40, O_All, DelayOrPulseWait,

 VSWTCE, DLUBEF,      0,          NoneOn,      NoneOff, NoChange, O_All, SwitchWait | TimingOn,
 DLUBEF, DLUBED,      0,             O09,      NoneOff, NoChange, O_All, DelayOrPulseWait,
 DLUBED,      0,      0,          NoneOn,          O09,   Zone42, O_All, DelayOrPulseWait,

/* Tip (zone13/18 can start tip!, so need this checked here */ 
 VSWTCB, DELYWX,      0,       O13 | O08,      NoneOff,   Zone14, O_All, SwitchWait | TimingOn
 };

unsigned char mainscreen_delay;
unsigned char NetWarnCanc;
unsigned char AlarmFlags;
unsigned char Knives_Up, RaiseDoor, BootRun, DemoScreens;
unsigned char AutoTip_Sel, LangStartup, LEDSel;
unsigned char PauseTip, NetCutPosAlarm, NetCutPosNorm, OneDispCount, ExternalBuzzSet;
