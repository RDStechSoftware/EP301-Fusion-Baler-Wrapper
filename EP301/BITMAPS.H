#ifndef __bitmaps_h
#define __bitmaps_h

typedef const unsigned char LANGUAGE_TEXT;

struct pr {
      const unsigned char *l[MAXLANG];
      };

#include "epl_lan0.h"
#include "epl_lan1.h"
#include "epl_lan2.h"

struct fn1 {
       unsigned char spc;
       unsigned char *f1[256];
       };
extern struct fn1 const fnt1_EUR;
extern struct fn1 const fnt1_CYR;
extern struct fn1 *const fnt1[MAXLANG];

struct fn2 {
       unsigned char  spc;
       unsigned char *f2[15];
       };
extern struct fn2 const fnt2;

struct fn3 {
       unsigned char  spc;
       unsigned char *f3[15];
       };
extern struct fn3 const fnt3;

extern const unsigned char F1_CLK[9];
extern const unsigned char F1_POINT[9];
extern const unsigned char PAUSE[20];
extern const unsigned char BATTSLIM[18];

extern const unsigned char F1_COL[9];

extern const unsigned char TABUP[107];
extern const unsigned char TABDOWN[107];
extern const unsigned char TABLEFT[107];
extern const unsigned char TABRIGHT[107];
extern const unsigned char TABCYCL[107];
extern const unsigned char TABENTS[107];
extern const unsigned char TABESC[107];
extern const unsigned char TAB[107];
extern const unsigned char TABTOTL[107];
extern const unsigned char TABSERV[107];
extern const unsigned char TABKNIVE[107];
extern const unsigned char TBKNVUP[107];
extern const unsigned char TBKNDWN[107];
extern const unsigned char TBKNUPDN[212];
extern const unsigned char TBKNVON[107];
extern const unsigned char TBKNOFF[107];
extern const unsigned char TABFLOOR[107];
extern const unsigned char TABREV[107];
extern const unsigned char TBINDEX[107];
extern const unsigned char TBFWDREV[212];
extern const unsigned char TAB_KNIV00[107];
extern const unsigned char TAB_KNIV1UP[107];
extern const unsigned char TAB_KNIV2UP[107];
extern const unsigned char TAB_KNIV11[107];
extern const unsigned char TAB_KNIV12[107];
extern const unsigned char TAB_KNIV13[112];
extern const unsigned char TAB_KNIV23[107];
extern const unsigned char TAB_KNIV25[107];
extern const unsigned char TAB_KNIV_DOWN[107];
extern const unsigned char TABFWDREV[212];
extern const unsigned char TBFWDREV[212];
extern const unsigned char TABMINUS[107];
extern const unsigned char TABPLUS[107];
extern const unsigned char TABRESET[107];
extern const unsigned char TABA2E[107];
extern const unsigned char TABF2J[107];
extern const unsigned char TABCROSS[112];
extern const unsigned char NewTabcross[62]; 
extern const unsigned char TABTICK[112];

extern const unsigned char SYMSLW[22];
extern const unsigned char SYMFST[22];

extern const unsigned char NIGHTSYM[62];
extern const unsigned char DAYSYM[106];
extern const unsigned char CONTRST1[20];
extern const unsigned char BRIGHTN1[24];
extern const unsigned char CONPOINT[11];

extern const unsigned char TECHPIN[2562];
extern const unsigned char TECH[2562];

extern const unsigned char MCHALE01[340];
extern const unsigned char FUSION[422];

extern const unsigned char MODEAUTO[56];
extern const unsigned char MODESEMI[47];
extern const unsigned char MODEMAN[47];
extern const unsigned char STATOK[102];
extern const unsigned char ROLL01[53];
extern const unsigned char ROLL02[53];
extern const unsigned char ROLL03[53];
extern const unsigned char ROLL04[53];
extern const unsigned char ROLL05[53];
extern const unsigned char ROLL06[53];
extern const unsigned char ROLL07[53];
extern const unsigned char ROLL08[53];

extern const unsigned char BUTTON01[22];
extern const unsigned char BUTTON03[22];
extern const unsigned char BUTTON04[22];

extern const unsigned char SWOPEN[29];
extern const unsigned char SWCLOSE[29];

extern const unsigned char VOLUMESCALE[818];

extern const unsigned char FILMLYRS[127];
extern const unsigned char TIPAUTO[176];

extern const unsigned char SIDEDISPLAY[342];
extern const unsigned char SIDE_DISPLAY1[342];
extern const unsigned char SIDE_DISPLAY2[342];                                  

extern const unsigned char TAB_INFO[107];
extern const unsigned char BALENORMAL_V2[218];
extern const unsigned char BALENORMAL2_v2[218];
extern const unsigned char BALETRANSFER1_V2[314];
extern const unsigned char BALETRANSFER2_V2[314];
extern const unsigned char BALETRANSFER3_V2[314];
extern const unsigned char BALETRANSFER4_V2[314];
extern const unsigned char BALEWRAPPED[114];

extern const unsigned char REARBALE[114];
extern const unsigned char REARBALE1[50];
extern const unsigned char REARBALE2[50];
extern const unsigned char REARBALE3[50];
extern const unsigned char REARBALE4[50];
extern const unsigned char REARBALE5[50];
extern const unsigned char REARBALE6[50];
extern const unsigned char REARBALE7[50];
extern const unsigned char REARBALE8[50];
extern const unsigned char REARBALE9[50];
extern const unsigned char REARBALE10[50];
extern const unsigned char REARBALE11[50];

extern const unsigned char OKBOX[102];
extern const unsigned char WARNINGBOX[102];
extern const unsigned char LAYERBOX[102];
extern const unsigned char LUBEBOX[102];
extern const unsigned char NOPWMBOX[102];

/*    KOREAN    */
extern const unsigned char KSilage[62];
extern const unsigned char KHay[38];
extern const unsigned char KStraw[41];
extern const unsigned char TechMenu[100];
extern const unsigned char OperatorMenu[106];
extern const unsigned char MachineSetup[100];
extern const unsigned char MachineMenu[100];
extern const unsigned char BaleCount[100];

extern const unsigned char Total[44];
extern const unsigned char Off[50];
extern const unsigned char On[41];
extern const unsigned char Crop[41];
extern const unsigned char Layers[97];

extern const unsigned char TransferTime[93];
extern const unsigned char KSHORT[62];
extern const unsigned char KMANUAL[38];
extern const unsigned char LubeDose[58];
extern const unsigned char KLONG[41];
extern const unsigned char FilmSensor[86];
extern const unsigned char KLubeCount[38];
extern const unsigned char Ktotal[47];
extern const unsigned char KReset[67];
extern const unsigned char Grand[30];
extern const unsigned char KTabReset[112];
extern const unsigned char KClock[44];
extern const unsigned char KVolume[38];
extern const unsigned char KLanguage[44];
extern const unsigned char KContrast[44];
extern const unsigned char KYear[14];
extern const unsigned char KMonth[24];
extern const unsigned char KMins[28];
extern const unsigned char KDate[50];

/*    END KOREAN    */

extern const unsigned char TIPBALE[258];
extern const unsigned char WRAPNOTCOMPLETE[254];
extern const unsigned char UNBLOCKBLAER[258];
extern const unsigned char UNBLOCKRESET[322];
extern const unsigned char ONEDISPENSER[242];
extern const unsigned char NODISPENSER[242];
extern const unsigned char INDEXINGDISP[272];
extern const unsigned char NETCUTPOS[263];
extern const unsigned char SAFETYSWITCH[138];
extern const unsigned char MOTORSPEED[218];
extern const unsigned char WRAPPERFAST[245];
extern const unsigned char KNIFE1PRES_WARN[164];
extern const unsigned char KNIFE2PRES_WARN[164];
extern const unsigned char MAIN_AUTO_WARN_KNIVES3[530];
extern const unsigned char FUSION_warning_knife_position[335];

extern const unsigned char TIPPOS[194];
extern const unsigned char LOWBAT[138];
extern const unsigned char TRFRNTCMP[306];
extern const unsigned char DISPPOS[272];
extern const unsigned char TIPNOTCMP[250];
extern const unsigned char CHECKNET[218];

extern const unsigned char WRAPPEDTIP1_V2[118];
extern const unsigned char WRAPPEDTIP2[106];
extern const unsigned char UNWRAPPEDTIP1_V2[118];
extern const unsigned char UNWRAPPEDTIP2[106];
extern const unsigned char GRASS01[30];
extern const unsigned char GRASS02[30];
extern const unsigned char GRASS03[30];
extern const unsigned char GRASS04[30];
extern const unsigned char GRASS05[30];
extern const unsigned char GRASS06[30];

extern const unsigned char TIP_V2[32];
extern const unsigned char ARROWS[30];
extern const unsigned char *DemoScreen[15];

extern const unsigned char FusionP01[56];
extern const unsigned char FusionP02_v2[161];
extern const unsigned char FusionP03_v2[164];
extern const unsigned char FusionP04[46];
extern const unsigned char FusionP05[28];
extern const unsigned char FusionP06[17];

extern const unsigned char CAN_ERROR[268];
extern const unsigned char Side_display1[342];
extern const unsigned char SideDisplay2[342];
extern const unsigned char Side_display2[342];
extern const unsigned char TAB_KNIVUP[107];
extern const unsigned char TAB_KNIV1UP_X25_SELECT[107];
extern const unsigned char KNIFE_OUTLINE[26];
extern const unsigned char KNIFE_FILLED[26];

extern const unsigned char CropPickup1_V2[30];
extern const unsigned char CropPickup2_V2[30];
extern const unsigned char CropPickup3_V2[30];
extern const unsigned char CropPickup4_V2[30];

struct WarningBitmap {
	const unsigned char *Warn;
	const unsigned char *BitMap;
	unsigned char x;
	unsigned char y;
};
extern const struct WarningBitmap Wbm[27];

	


#endif


