#include <inh83.h>
#include <ioh83003.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bytedef.h"


unsigned char display_f1_number( float data, float offset, float con,
      unsigned char pt, unsigned char co, unsigned char ro, unsigned char just, 
      unsigned char width )
{
unsigned char tstring[32], x1, x2;
unsigned short int i;
float limit;

x1 = co;
x2 = co + (width * 6) - 1;
draw_box( adm, x1, ro, x2, ro+6, CLEAR );

limit = 1;
for( i = width; i > 2; i-- )
  {
  limit *= 10;
  }

data *= con;
if( (data + offset) >= limit )
  {
  pt = 0;
  }

if( just ) /* LEFT = 0, RIGHT = 1 */
  {
  i = width;
  }
else
  {
  i = 1;
  }
sprintf( tstring, "%*.*f", i, pt, (data + offset) );

/* LEFT = 0, RIGHT = 1 */ /* dp 2 wide, spacing 1 */
if( just && (strchr( tstring, '.' ) != NULL) )
  {
  co += 3;
  }

for( i=0; tstring[i] && (i < width); i++ )
  {
  co += ( write_bitmap( adm,
                fnt1[lang]->f1[tstring[i]], co, ro, OR ) + fnt1[lang]->spc );
  }

return( co );
}


#define CRN 2

unsigned char display_f1_text( const unsigned char *data, unsigned char max,
                       unsigned char co, unsigned char ro, unsigned char prog )
{
unsigned char i, chr, wid, coo;
unsigned char xa, xb, ya, yb;

wid = 0;
for( i=0; (chr = *(data+i)) && (i < max); i++ )
  {
  wid += (fnt1[lang]->f1[chr][0] + fnt1[lang]->spc);
  }
wid = wid - fnt1[lang]->spc - 1;

if( prog & CENTER )
  {
  co = co - (wid / 2);
  }
wid += co;

draw_box( adm, co, ro, wid, ro+6, CLEAR );
if( prog & INV )
  {
  draw_box( adm, co-1, ro-1, wid+1, ro+7, EMPTY );
  }

coo = co;

for( i=0; (chr = *(data+i)) && (i < max); i++ )
  {
  co += ( write_bitmap( adm, fnt1[lang]->f1[chr], co, ro, OR ) + fnt1[lang]->spc );
  }

if( prog & GREY )
  {
  draw_box ( adm, coo, ro, wid, ro+((prog & EDIT) ? 8 : 6), GREY );
  }

if( prog & INV )
  {
  draw_box ( adm, coo, ro, wid, ro+((prog & EDIT) ? 8 : 6), INV );
  }

if( prog & FRAMED )
  {
  xa = coo - (CRN + 2);
  xb = wid + (CRN + 2);
  ya = ro - CRN;
  yb = ro + CRN + ((prog & EDIT) ? 8 : 6);
  
  draw_line( adm, xa, ya+CRN, xa+CRN, ya, OR );
  draw_line( adm, xa+CRN, ya, xb-CRN, ya, OR );
  draw_line( adm, xb-CRN, ya, xb, ya+CRN, OR );
  draw_line( adm, xb, ya+CRN, xb, yb-(CRN+1), OR );
  draw_line( adm, xb, yb-(CRN+1), xb-(CRN+2), yb, OR );
  draw_line( adm, xb-(CRN+2), yb, xa+(CRN+2), yb, OR );
  draw_line( adm, xa+(CRN+2), yb, xa, yb-(CRN+1), OR );
  draw_line( adm, xa, yb-(CRN+1), xa, ya+CRN, OR );
  }

if( prog & UNDERLINED )
  {
  draw_line(adm, coo, ro+8, co-1, ro+8, OR );
  }

return( co );
}


unsigned char display_f2_number( float data, float offset, float con,
      unsigned char pt, unsigned char co, unsigned char ro, unsigned char just, 
      unsigned char width )
{
unsigned char tstring[32], x1, x2;
unsigned short int i;
float limit;

x1 = co;
x2 = co + (width * 12) - 1;
draw_box ( adm, x1, ro, x2, ro+13, CLEAR );

limit = 1;
for( i = width; i > 2; i-- )
  {
  limit *= 10;
  }

data *= con;
if( (data + offset) >= limit )
  {
  pt = 0;
  }

if( just ) /* LEFT = 0, RIGHT = 1 */
  {
  i = width;
  }
else
  {
  i = 1;
  }
sprintf( tstring, "%*.*f", i, pt, (data + offset) );

/* LEFT = 0, RIGHT = 1 */ /* dp 4 wide, spacing 2 */
if( just && (strchr( tstring, '.' ) != NULL) )
  {
  co += 6;                                          
  }

for( i=0; tstring[i] && (i < width); i++ )
  {
  co += ( write_bitmap( adm,
                fnt2.f2[ cf2(tstring[i]) ], co, ro, OR ) + fnt2.spc );
  }

return( co );
}


unsigned char display_f3_number( float data, float offset, float con,
      unsigned char pt, unsigned char co, unsigned char ro, unsigned char just, 
      unsigned char width )
{
unsigned char tstring[32], x1, x2;
unsigned short int i;
float limit;

x1 = co;
x2 = co + (width * 18) - 1;
draw_box ( adm, x1, ro, x2, ro+20, CLEAR );

limit = 1;
for( i = width; i > 2; i-- )
  {
  limit *= 10;
  }

data *= con;
if( (data + offset) >= limit )
  {
  pt = 0;
  }

if( just ) /* LEFT = 0, RIGHT = 1 */
  {
  i = width;
  }
else
  {
  i = 1;
  }
sprintf( tstring, "%*.*f", i, pt, (data + offset) );

/* LEFT = 0, RIGHT = 1 */ /* dp 6 wide, spacing 3 */
if( just && (strchr( tstring, '.' ) != NULL) )
  {
  co += 9;
  }

for( i=0; tstring[i] && (i < width); i++ )
  {
  co += ( write_bitmap( adm,
                fnt3.f3[ cf3(tstring[i]) ], co, ro, OR ) + fnt3.spc );
  }

return( co );
}


void startup_frame( void )
{
unsigned short int i;

for( i = 0; i < GRAPHICS_SIZE; i++ ) /* clear display memory */
  {
  adm[i] = 0;
  }
         /* mem, col, row, col, row, mode  */
draw_line ( adm,   0,   0, 159,   0, OR );  /* draw_frame */
draw_line ( adm, 159,   1, 159, 127, OR );
draw_line ( adm,   0, 127, 159, 127, OR );
draw_line ( adm,   0,   1,   0, 126, OR );
}


void TimeDisplay( void )
{
unsigned char tstring[128];

get_time();

if( seconds != old_time )
  {
  old_time = seconds;

  draw_box( adm, 2, 3, 2+(4*6)+1, 3+7, CLEAR );

  tstring[0] = hex[hours / 10];
  tstring[1] = hex[hours % 10];
  tstring[2] = ':';
  tstring[3] = hex[minutes / 10];
  tstring[4] = hex[minutes % 10];
  tstring[5] = 0x00;

  display_f1_text( tstring, TS20, 2, 3, FIXED );
  }

if( flash_bit )
  {
  draw_box( adm, 2+(2*6), 3, 2+(2*6+1), 3+6, CLEAR );
  }
else
  {
  write_bitmap( adm, F1_COL, 2+(2*6), 3, OR );
  }

}


void screen00( void ) /* Startup Splash Screen */
{
	unsigned char tstring[32];
	static unsigned char resetModeSel;

	if( startup != 1 )
	{
		startup = 1;

		startup_frame();

		write_bitmap( adm, MCHALE01, 33, 16, OR );
		write_bitmap( adm, FUSION, 26, 55, OR );

		sprintf( tstring, "EP%03u-%03u", SOFTWARE, ISSUE );
		display_f1_text( tstring, TSMAX, 80, 95, FIXED+CENTER );

		SetSerial0_Boot();
		resetModeSel = 0;
	}

	switch( key )
	{
	case Key_F2:
	case Key_F2 | KeyDone | KeyRepeat:

	if( !resetModeSel )
	{
		resetModeSel = 2;
	}

	if( swtim > 20 )
	{
		if( resetModeSel == 2 )
		{
			window = screen06; /* Reset Defaults */
		}
	}
	break;
	}

	if( demi_secs > 4 )
	{
		LangStartup = 1;
		window = set_language; /* screen01 */
		IER |= 0x01; /* turn on remote interrupt */
		demi_secs = 0;
	}

	if( !resetModeSel )
	{
		resetModeSel = 1;
	}

	CheckSerial0();

}


void Demo00( void ) /* Demo Display */
{
static unsigned char demo_step, tstring[16];

unsigned char c;	

if( startup != 1 )
  {
  startup = 1;

  demo_step = 0;
  }

startup_frame();

switch( key )
  {
  case Key_F2:
  case Key_F2 | KeyDone | KeyRepeat:
  window = screen02;
    break;
  }

c = demo_step / 4;
demo_step++;

if( c > 14 )
  {
  demo_step = 0;
  c = 0;
  }

write_bitmap( adm, DemoScreen[c], 0, 0, OR );

draw_box( adm, 2, 3, 2+(4*6)+1, 3+7, CLEAR );

get_time();

tstring[0] = hex[hours / 10];
tstring[1] = hex[hours % 10];
tstring[2] = ':';
tstring[3] = hex[minutes / 10];
tstring[4] = hex[minutes % 10];
tstring[5] = 0x00;

display_f1_text( tstring, TS20, 2, 3, FIXED );

if( flash_bit )
  {
  draw_box( adm, 2+(2*6), 3, 2+(2*6+1), 3+6, CLEAR );
  }
else
  {
  write_bitmap( adm, F1_COL, 2+(2*6), 3, OR );
  }

}



void screen02( void ) /* Operator Menu Display */
{
unsigned char old_selection;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();


  if(!Korean)
  {
	  display_f1_text( s0331.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Machine Menu */
	  
	  if(MachineStatus & MS_NETTING)
	  {
	    display_f1_text( s0332.l[lang], TSMAX, 12, 30, FIXED | GREY); /* Machine Setup 1 */
	    display_f1_text( s0333.l[lang], TSMAX, 12, 40, FIXED | GREY); /* Machine Setup 2 */
	  }
	  else
	  {
	    display_f1_text( s0332.l[lang], TSMAX, 12, 30, FIXED); /* Machine Setup 1 */
	    display_f1_text( s0333.l[lang], TSMAX, 12, 40, FIXED); /* Machine Setup 2 */
	  }
	
	  display_f1_text( s0334.l[lang], TSMAX, 12, 50, FIXED); /* Bale Count */
	  display_f1_text( s0335.l[lang], TSMAX, 12, 60, FIXED); /* Operator Menu */
	  display_f1_text( s0336.l[lang], TSMAX, 12, 70, FIXED); /* Technician Menu */
  }
  else
  {
	  write_bitmap( adm, MachineMenu, 54, 4, OR );
	  
		write_bitmap( adm, MachineSetup, 26, 23, OR );
		display_f1_text( "1", TSMAX, 85, 27, FIXED);
		write_bitmap( adm, MachineSetup, 26, 41, OR );
		display_f1_text( "2", TSMAX, 85, 43, FIXED);	  
	
		write_bitmap( adm, BaleCount, 27, 57, OR );
		write_bitmap( adm, OperatorMenu, 24, 74, OR );
		write_bitmap( adm, TechMenu, 24, 89, OR );	  
  }

  write_bitmap( adm, TABDOWN, 3, 106, OR );
  write_bitmap( adm, TABUP, 42, 106, OR );
  write_bitmap( adm, TABENTS, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  old_selection = 0xff;
  }
else
  {
  old_selection = selection;
  }

TimeDisplay();

switch( key )
  {
  case Key_F2:
  case Key_F2 | KeyDone | KeyRepeat:
	if( swtim > 45 )
	  {
	  window = KnifeSystem;
	  }
	break;
	
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
    if( selection < 4 )
      {
      selection++;
      }
    else if( (swtim > 50) /*|| (selection == 5)*/ )
      {
      selection = 5;
      /*if( selection < 6 )
    	selection++;*/
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    if( selection )
      {
      selection--;
/*    if( selection == 5 )
        selection--;*/
      }
    break;

  case Key_S3:
    switch( selection )
      {
      case 0:
        if( !(MachineStatus & MS_NETTING) )
          window = screen13; /* Machine Setup 1 */
        break;

      case 1:
        if( !(MachineStatus & MS_NETTING) )
          window = screen131; /* machine setup 2 */
        break;

      case 2:
        window = screen11; /* Bale Count */
        break;

      case 3:
        window = screen14; /* Operator Menu */
        break;

      case 4:
#ifdef TEST
      	window = screen04; /* Tech Menu */
#else
      	window = screen03; /* Pin Entry Display */
#endif
        break;
        
      case 5:
        window = screen071; /* Diagnostics - Digital Inputs */
        break;
      }
    break;

  case Key_S4:
    escape = 1;
    break;
  }

if( !Korean )
  {
    if( selection != old_selection )
	  {
	  if( selection > 4 )
	    {
		display_f1_text( s0337.l[lang],   TSMAX, 12, 80, FIXED ); /* Diagnostics */
		/*
		display_f1_text( s0386.l[lang],   TSMAX, 12, 80, FIXED ); / * Knife System * /
	    display_f1_text( s0337.l[lang],   TSMAX, 12, 90, FIXED ); / * Diagnostics * /
	    */
	    }
	  else
	    {
	    draw_box( adm, 12, 80, 150, 80+10, CLEAR );
	    }
	  }	
	standard_pointer( 4, 30, 10 );
  }
else
	standard_pointer( 14, 28, 16 );
}


void screen03( void ) /* Pin Entry Display */
{
static unsigned char dig[5];

unsigned short int pin;
unsigned char *pd, c;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0336.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Technician Menu */

  display_f1_text( s0338.l[lang], TSMAX, 80, 45, FIXED | CENTER ); /* ENTER PIN CODE */

  write_bitmap( adm, TABDOWN, 3, 106, OR );
  write_bitmap( adm, TABUP, 42, 106, OR );
  write_bitmap( adm, TABENTS, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  dig[0] = '0';
  dig[1] = '0';
  dig[2] = '0';
  dig[3] = '0';
  dig[4] = 0x00;

  leaf = 1; /* don't save this screen */
  }

TimeDisplay();

switch( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
      case 1:
      case 2:
      case 3:
        pd = &dig[selection];
        if( *pd > '0' )
          {
          (*pd)--;
          }
        else
          {
          *pd = '9';
          }
        break;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
      case 1:
      case 2:
      case 3:
        pd = &dig[selection];
        if( *pd < '9' )
          {
          (*pd)++;
          }
        else
          {
          *pd = '0';
          }
        break;
      }
    break;

  case Key_S3:
    if( selection < 3 )
      {
      selection++;
      }
    else
      {
      pin = PINTECH;
      c = (pin % 10) + '0';
      if(( dig[3] == c ))
        {
        pin /= 10;
        c = (pin % 10) + '0';
        if(( dig[2] == c ))
          {
          pin /= 10;
          c = (pin % 10) + '0';
          if(( dig[1] == c ))
            {
            pin /= 10;
            c = (pin % 10) + '0';
            if(( dig[0] == c ))
              {
              window = screen04; /* Technician Menu Display */
              }
            }
          }
        }
      else
        {
        selection = 0;
        }
      }
    break;

  case Key_S4:
    escape = 1;
    break;
  }

display_f1_text( dig, TSMAX, 68, 60, FIXED );

draw_line( adm, 68, 68, 68+22, 68, CLEAR );
c = 68+(selection*6);
if( !flash_bit )
  {
  draw_line( adm, c, 68, c+4, 68, OR );
  }

}

void GrandTotalPin( void ) /* Grand total Pin Entry Display */
{
static unsigned char dig[7];

unsigned long int pin;
unsigned char *pd, c;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0009.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Grand Total pin entry */

  display_f1_text( s0338.l[lang], TSMAX, 80, 45, FIXED | CENTER ); /* ENTER PIN CODE */

  write_bitmap( adm, TABDOWN, 3, 106, OR );
  write_bitmap( adm, TABUP, 42, 106, OR );
  write_bitmap( adm, TABENTS, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  dig[0] = '0';
  dig[1] = '0';
  dig[2] = '0';
  dig[3] = '0';
  dig[4] = '0';
  dig[5] = '0';
  dig[6] = 0x00;

  leaf = 1; /* don't save this screen */
  }

TimeDisplay();

switch( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        pd = &dig[selection];
        if( *pd > '0' )
          {
          (*pd)--;
          }
        else
          {
          *pd = '9';
          }
        break;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        pd = &dig[selection];
        if( *pd < '9' )
          {
          (*pd)++;
          }
        else
          {
          *pd = '0';
          }
        break;
      }
    break;

  case Key_S3:
    if( selection < 5 )
      {
      selection++;
      }
    else
      {
      pin = PIN_GRANDTOT;
      c = (pin % 10) + '0';
      if(( dig[5] == c ))
        {
        pin /= 10;
        c = (pin % 10) + '0';
        if(( dig[4] == c ))
          {
          pin /= 10;
          c = (pin % 10) + '0';
          if(( dig[3] == c ))
            {
            pin /= 10;
            c = (pin % 10) + '0';
            if(( dig[2] == c ))
              {
              pin /= 10;
              c = (pin % 10) + '0';
              if(( dig[1] == c ))
                {
                pin /= 10;
                c = (pin % 10) + '0';
                if(( dig[0] == c ))
                  {
                  pin /= 10;
                  c = (pin % 10) + '0';
                  window = EditGrandTotBale; /* Technician Menu Display */
                  }
                }
              }
            }
          }
        }
      else
        {
        selection = 0;
        }
      }
    break;

  case Key_S4:
    escape = 1;
    break;
  }

display_f1_text( dig, TSMAX, 68, 60, FIXED );

draw_line( adm, 68, 68, 68+40, 68, CLEAR );
c = 68+(selection*6);
if( !flash_bit )
  {
  draw_line( adm, c, 68, c+4, 68, OR );
  }

}

void EditGrandTotBale( void )
{
unsigned char tstring[32];
static unsigned long int temp_grand_total;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0009.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Grand Total pin entry */

  display_f1_text( s0405.l[lang], TSMAX, 80, 45, FIXED | CENTER ); /* EDIT TOTAL */

  write_bitmap( adm, TAB, 3, 106, OR );
  display_f1_text( "+1000", TSMAX, 7, 114, FIXED ); /* +1000 */
  write_bitmap( adm, TAB, 42, 106, OR );
  display_f1_text( "+100", TSMAX, 47, 114, FIXED ); /* +100 */
  write_bitmap( adm, TABENTS, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  leaf = 1; /* don't save this screen */
  temp_grand_total = GrandTotalBales;
  }

TimeDisplay();

switch( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
      	temp_grand_total += 1000U;
        break;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
      	temp_grand_total += 100U;
        break;
      }
    break;

  case Key_S3:
  	GrandTotalBales = temp_grand_total;
    break;

  case Key_S4:
    escape = 1;
    break;
  }

sprintf( tstring, "%6lu", temp_grand_total );
display_f1_text( tstring, TSMAX, 80, 66, FIXED | CENTER ); /* EDIT TOTAL */

if( temp_grand_total > 99999UL )
	{
	temp_grand_total = 0UL;
	}
}

void screen14( void ) /* Operator Menu Display */
{
if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  if( !Korean )
  {
  display_f1_text( s0335.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Operator Menu */

  display_f1_text( s0339.l[lang], TSMAX, 12, 30, FIXED ); /* Contrast */
  display_f1_text( s0340.l[lang], TSMAX, 12, 40, FIXED ); /* Volume */
  display_f1_text( s0341.l[lang], TSMAX, 12, 50, FIXED ); /* Clock Adjust */
  display_f1_text( s0342.l[lang], TSMAX, 12, 60, FIXED ); /* Language */
  }
  else
  {
  write_bitmap( adm, OperatorMenu,  51, 3, OR );
  
  write_bitmap( adm, KContrast,  41, 25, OR );
  write_bitmap( adm, KVolume,  42, 42, OR );
  write_bitmap( adm, KClock,  40, 59, OR );
  write_bitmap( adm, KLanguage,  43, 77, OR );
  }
	  
  write_bitmap( adm, TABDOWN,  3, 106, OR );
  write_bitmap( adm, TABUP,   42, 106, OR );
  write_bitmap( adm, TABENTS, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );
  }

TimeDisplay();

switch( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
    if( selection < 3 )
      {
      selection++;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    if( selection )
      {
      selection--;
      }
    break;

  case Key_S3:
    switch( selection )
      {
      case 0:
        window = display_levels;
        break;

      case 1:
        window = speaker_test;
        break;

      case 2:
        window = clock_set;
        break;

      case 3:
        window = set_language;
        break;
      }
    break;

  case Key_S4:
    escape = 1;
    break;
  }


if( !Korean )
standard_pointer( 4, 30, 10 );
else
standard_pointer( 19, 30, 16 );

}


void screen04( void ) /* Technician Menu Display */
{
unsigned char tstring[32];

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0336.l[lang], TSMAX, 80, 10/*14*/, FIXED | CENTER | UNDERLINED ); /* Technician Menu */

  display_f1_text( "Demo Screens", TSMAX, 12, 24, FIXED ); /* Demo Screens */
  display_f1_text( s0343.l[lang], TSMAX, 12, 34, FIXED ); /* Baler Full / Net */
  display_f1_text( s0344.l[lang], TSMAX, 12, 44, FIXED ); /* Bale Transfer */
  display_f1_text( s0345.l[lang], TSMAX, 12, 54, FIXED ); /* Wrapping */
  display_f1_text( s0346.l[lang], TSMAX, 12, 64, FIXED ); /* Top-Up / Floor */
  display_f1_text( s0347.l[lang], TSMAX, 12, 74, FIXED ); /* Rotation */
  display_f1_text( s0348.l[lang], TSMAX, 12, 84, FIXED ); /* Lube Setup */
  display_f1_text( s0349.l[lang], TSMAX, 12, 94, FIXED ); /* Reset Defaults */

  write_bitmap( adm, TABDOWN,  3, 106, OR );
  write_bitmap( adm, TABUP,   42, 106, OR );
  write_bitmap( adm, TABENTS, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  }

TimeDisplay();

switch( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
      if( selection < 7 )
      {
        selection++;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    if( selection )
      {
      selection--;
      }

    if( swtim > 99 )
    	{
    	window = GrandTotalPin;
    	}
    break;

  case Key_S3:
    switch( selection )
    {      
      case 0:
    	DemoScreens = DemoScreens? 0:1;
    	break;
    	
      case 1: /* baler full /net */
        window = screen15;
        break;

      case 2: /* Bale transfer */
        window = screen16;
        break;

      case 3: /* wrapping */
        window = screen17;
        break;

      case 4:  /* Top-Up / Floor */
        window = screen18;
        break;

      case 5:  /* Rotation */
        window = screen19;
        break;

      case 6: /* Lube Setup */
        window = screen20;
        break;

      case 7:
        window = screen06; /* Reset Defaults */
        break;
    }
    break;

  case Key_S4:
    escape = 1;
    break;
  }

sprintf( tstring, /*"%s",*/ DemoScreens? "On ":"Off" ); 
display_f1_text(tstring, TS20, 120, 24, FIXED );

standard_pointer( 4, 23, 10 );

}


void screen06( void ) /* Reset Defaults */
{
unsigned char changed, c, tstring[64];

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0349.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Reset Defaults */
 
  write_bitmap( adm, TAB,      3, 106, OR );
  write_bitmap( adm, TAB,     42, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  changed = 1;
  }
else
  {
  changed = 0;
  }

TimeDisplay();

switch( key )
  {
  case Key_S3:
    if( !selection )
      {
      reset_factors();
      selection = 1; 
      changed = 1;
      }
    break;

  case Key_S4:
    escape = 1;
    break;
  }

if( changed )
  {
  /* remove 'ENT' tab */
  draw_box( adm, 81, 106, 117, 126, CLEAR );
  
  /* clear text box */
  draw_box( adm,  1, 30, 158, 40+6, CLEAR );

  switch( selection )
    {
    case 0:
      write_bitmap( adm, TABENTS,  81, 106, OR );
      display_f1_text( s0350.l[lang], TSMAX, 80, 30, FIXED | CENTER ); /* Press '\003' to Reset      */
      break;

    case 1: 
      write_bitmap( adm, TAB,  81, 106, OR );
      
      /* if text > 25 characters then split over 2 lines */
      c = strlen( s0351.l[lang] );
      /*
      if( c > 64 )
        {
    	string to long!  
        }
      else  */
      if( c > 25 )
    	{
    	strcpy( tstring, s0351.l[lang] );
    	
    	c = 25;
    	while( tstring[c] != ' ' )
    	{
    		c--;
    	}
    	tstring[c] = 0x00;
        display_f1_text( tstring, TSMAX, 80, 30, FIXED | CENTER ); /* xxxxFactors Reset to */
        display_f1_text( tstring+c+1, TSMAX, 80, 40, FIXED | CENTER ); /*       Defaults */
    	}
      else
        {
        display_f1_text( s0351.l[lang], TSMAX, 80, 30, FIXED | CENTER ); /* Factors Reset to Defaults */
        }
      break;
    }
  }

}


#define DI_XPOS 20
#define DI_YPOS 27
#define DI_XSPACE 36
#define DI_YSPACE 26

#define DI_COL01 DI_XPOS+(DI_XSPACE * 0)
#define DI_COL02 DI_XPOS+(DI_XSPACE * 1)
#define DI_COL03 DI_XPOS+(DI_XSPACE * 2)
#define DI_COL04 DI_XPOS+(DI_XSPACE * 3)

#define DI_ROW01 DI_YPOS+(DI_YSPACE * 0)
#define DI_ROW02 DI_YPOS+(DI_YSPACE * 1)
#define DI_ROW03 DI_YPOS+(DI_YSPACE * 2)

void screen071( void ) /* Diagnostics - Digital Inputs */
{
unsigned char tstring[32];

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0352.l[lang], TSMAX, 80, 12, FIXED | CENTER | UNDERLINED ); /* Digital Inputs */

  write_bitmap( adm, BATTSLIM, 118, 2, OR );

  write_bitmap( adm, TAB,       3, 106, OR );
  write_bitmap( adm, TAB,      42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  LedData.S = 0;
  Op.L = 0;

  leaf = 1;

  SetSerial0_Boot();
  }

TimeDisplay();

sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
display_f1_text( tstring, TSMAX, 136, 3, FIXED );

CheckSerial0();

switch( key )
  {
  case Key_S3:
    window = screen072;
    break;

  case Key_S4:
    escape = 1;
    break;
  }

draw_box( adm, 4, 27, 158, 105, CLEAR );

display_f1_text( " 1     2     3     4", TSMAX, DI_XPOS-13, DI_ROW01+1, FIXED );
write_bitmap( adm, Ip.I.IP01 ? SWCLOSE : SWOPEN, DI_COL01, DI_ROW01, OR );
write_bitmap( adm, Ip.I.IP02 ? SWCLOSE : SWOPEN, DI_COL02, DI_ROW01, OR );
write_bitmap( adm, Ip.I.IP03 ? SWCLOSE : SWOPEN, DI_COL03, DI_ROW01, OR );
write_bitmap( adm, Ip.I.IP04 ? SWCLOSE : SWOPEN, DI_COL04, DI_ROW01, OR );

display_f1_text( " 5     6     7     8", TSMAX, DI_XPOS-13, DI_ROW02+1, FIXED );
write_bitmap( adm, Ip.I.IP05 ? SWCLOSE : SWOPEN, DI_COL01, DI_ROW02, OR );
write_bitmap( adm, Ip.I.IP06 ? SWCLOSE : SWOPEN, DI_COL02, DI_ROW02, OR );
write_bitmap( adm, Ip.I.IP07 ? SWCLOSE : SWOPEN, DI_COL03, DI_ROW02, OR );
write_bitmap( adm, Ip.I.IP08 ? SWCLOSE : SWOPEN, DI_COL04, DI_ROW02, OR );

display_f1_text( " 9    10    11    12", TSMAX, DI_XPOS-13, DI_ROW03+1, FIXED );
write_bitmap( adm, Ip.I.IP09 ? SWCLOSE : SWOPEN, DI_COL01, DI_ROW03, OR );
write_bitmap( adm, Ip.I.IP10 ? SWCLOSE : SWOPEN, DI_COL02, DI_ROW03, OR );
write_bitmap( adm, Ip.I.IP11 ? SWCLOSE : SWOPEN, DI_COL03, DI_ROW03, OR );
write_bitmap( adm, Ip.I.IP12 ? SWCLOSE : SWOPEN, DI_COL04, DI_ROW03, OR );

}


void screen072( void ) /* Diagnostics - Analogue Inputs */
{
unsigned char tstring[32];

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0353.l[lang], TSMAX, 80, 12, FIXED | CENTER | UNDERLINED ); /* Analogue Inputs */

  write_bitmap( adm, BATTSLIM, 118, 2, OR );

  write_bitmap( adm, TAB,       3, 106, OR );
  write_bitmap( adm, TAB,      42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  LedData.S = 0;
  Op.L = 0;

  leaf = 1;

  SetSerial0_Boot();
  }

TimeDisplay();

sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
display_f1_text( tstring, TSMAX, 136, 3, FIXED );

CheckSerial0();

switch( key )
  {
  case Key_S3:
    window = screen073;
    break;

  case Key_S4:
    escape = 1;
    break;
  }

draw_box( adm, 4, 27, 158, 105, CLEAR );

display_f1_text( "13    14    15    16", TSMAX, DI_XPOS-13, DI_ROW01+1, FIXED );
write_bitmap( adm, Ip.I.IP13 ? SWCLOSE : SWOPEN, DI_COL01, DI_ROW01, OR );
write_bitmap( adm, Ip.I.IP14 ? SWCLOSE : SWOPEN, DI_COL02, DI_ROW01, OR );
write_bitmap( adm, Ip.I.IP15 ? SWCLOSE : SWOPEN, DI_COL03, DI_ROW01, OR );
write_bitmap( adm, Ip.I.IP16 ? SWCLOSE : SWOPEN, DI_COL04, DI_ROW01, OR );

sprintf( tstring, "%3.1fV", (float)analogue[0] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL01-8, DI_ROW01+12, FIXED );

sprintf( tstring, "%3.1fV", (float)analogue[1] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL02-8, DI_ROW01+12, FIXED );

sprintf( tstring, "%3.1fV", (float)analogue[2] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL03-8, DI_ROW01+12, FIXED );

sprintf( tstring, "%3.1fV", (float)analogue[3] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL04-8, DI_ROW01+12, FIXED );

display_f1_text( "17    18    19", TSMAX, DI_XPOS-13, DI_ROW02+1, FIXED );
write_bitmap( adm, Ip.I.IP17 ? SWCLOSE : SWOPEN, DI_COL01, DI_ROW02, OR );
write_bitmap( adm, Ip.I.IP18 ? SWCLOSE : SWOPEN, DI_COL02, DI_ROW02, OR );
write_bitmap( adm, Ip.I.IP19 ? SWCLOSE : SWOPEN, DI_COL03, DI_ROW02, OR );

sprintf( tstring, "%3.1fV", (float)analogue[4] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL01-8, DI_ROW02+12, FIXED );

sprintf( tstring, "%3.1fV", (float)analogue[5] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL02-8, DI_ROW02+12, FIXED );

sprintf( tstring, "%3.1fV", (float)analogue[6] * ATOD_IP_SCALE );
display_f1_text( tstring, TSMAX, DI_COL03-8, DI_ROW02+12, FIXED );
}

#define OP_XPOS 21
#define OP_YPOS 24
#define OP_XSPACE 30
#define OP_YSPACE 18

#define OP_COL01 OP_XPOS+(OP_XSPACE * 0)
#define OP_COL02 OP_XPOS+(OP_XSPACE * 1)
#define OP_COL03 OP_XPOS+(OP_XSPACE * 2)
#define OP_COL04 OP_XPOS+(OP_XSPACE * 3)
#define OP_COL05 OP_XPOS+(OP_XSPACE * 4)

#define OP_ROW01 OP_YPOS+(OP_YSPACE * 0)
#define OP_ROW02 OP_YPOS+(OP_YSPACE * 1)
#define OP_ROW03 OP_YPOS+(OP_YSPACE * 2)
#define OP_ROW04 OP_YPOS+(OP_YSPACE * 3)

void screen073( void ) /* Diagnostics - Outputs */
{
static unsigned char OpOn;

unsigned char *pt, c, tstring[32];

struct OutPutTest {
  unsigned long int Out;
  unsigned char Xpos;
  unsigned char Ypos;
  };

const struct OutPutTest OpT[20] = {
  O01, OP_COL01, OP_ROW01,
  O02, OP_COL02, OP_ROW01,
  O03, OP_COL03, OP_ROW01,
  O04, OP_COL04, OP_ROW01,
  O05, OP_COL05, OP_ROW01,
  O06, OP_COL01, OP_ROW02,
  O07, OP_COL02, OP_ROW02,
  O08, OP_COL03, OP_ROW02,
  O09, OP_COL04, OP_ROW02,
  O10, OP_COL05, OP_ROW02,
  O11, OP_COL01, OP_ROW03,
  O12, OP_COL02, OP_ROW03,
  O13, OP_COL03, OP_ROW03,
  O14, OP_COL04, OP_ROW03,
  O15, OP_COL05, OP_ROW03,
  O16, OP_COL01, OP_ROW04,
  O17, OP_COL02, OP_ROW04,
  O18, OP_COL03, OP_ROW04,
  O19, OP_COL04, OP_ROW04,
  O20, OP_COL05, OP_ROW04
  };

struct OutPutTest *OpTp;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0354.l[lang], TSMAX, 80, 12, FIXED | CENTER | UNDERLINED ); /* Outputs */

  write_bitmap( adm, BATTSLIM, 118, 2, OR );

  write_bitmap( adm, TABLEFT,   3, 106, OR );
  write_bitmap( adm, TABRIGHT, 42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  LedData.S = 0;

  OpOn = 0;

  leaf = 1;

  SetSerial0_Boot();
  }

TimeDisplay();

sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
display_f1_text( tstring, TSMAX, 136, 3, FIXED );

CheckSerial0();

OpOn &= ~0x80; /* clear on bit */

switch( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone:
    OpOn &= ~0xe0; /* clear flag bits */
    OpOn |= 0x40;
    break;

  case Key_S2:
  case Key_S2 | KeyDone:
    OpOn &= ~0xe0; /* clear flag bits */
    OpOn |= 0x20;
    break;

  case Key_S1 | KeyDone | KeyRepeat:
  case Key_S2 | KeyDone | KeyRepeat:
    OpOn &= ~0xe0; /* clear flag bits */
    OpOn |= 0x80; /* set on bit */
    break;

  case Key_S3:
    window = screen074;
    break;

  case Key_S4:
    escape = 1;
    break;

  default:
    if( OpOn & 0x40 )
      {
      OpOn &= ~0xe0; /* clear flag bits */
      if( OpOn )
        {
        OpOn--;        
        }
      else
        {
        OpOn = 19;
        }
      }
    else if( OpOn & 0x20 )
      {
      OpOn &= ~0xe0; /* clear flag bits */
      if( OpOn < 19 )
        {
        OpOn++;
        }
      else
        {
        OpOn = 0;
        }
      }
    break;
  }

draw_box( adm, 4, 24, 158, 105, CLEAR );

display_f1_text( " 1    2    3    4    5", TSMAX, 8, OP_ROW01+2, FIXED );
display_f1_text( " 6    7    8    9   10", TSMAX, 8, OP_ROW02+2, FIXED );
display_f1_text( "11   12   13   14   15", TSMAX, 8, OP_ROW03+2, FIXED );
display_f1_text( "16   17   18   19   20", TSMAX, 8, OP_ROW04+2, FIXED );

Op.L = 0;
OpTp = &OpT[0];
for( c = 0; c < 20; c++ )
  {
  if( (OpOn & ~0xe0) == c )
    {
    if( OpOn & 0x80 ) /* ON */
      {
      Op.L = OpTp->Out;
      if( Op.L & O03 )
        {
    	Op.L |= O14; 
        }
      pt = BUTTON01;
      }
    else /* Selected */
      {
      pt = BUTTON04;
      }
    }
  else /* OFF */
    {
    pt = BUTTON03;
    }  
	  
  write_bitmap( adm, pt, OpTp->Xpos, OpTp->Ypos, OR );
  OpTp++;
  }

strcpy( tstring, s0355.l[lang] ); /* Status:  */
if( Op.L ) /* output turned on */
  {
  if( OP_Status )
    {
    pt = s0220.l[lang]; /* ON */
    }
  else
    {
    pt = s0356.l[lang]; /* OPEN or SHORT */
    }
  }
else /* output turned off */
  {
  pt = s0219.l[lang]; /* OFF */
  }
strcat( tstring, pt );
display_f1_text( tstring, TSMAX, 8, 96, FIXED );

}

struct point_pos
{
	unsigned char x;
	unsigned char y;
};

struct point_pos pp13[4] = {
 12, 65,
 80, 65,
 12, 77,
 12, 90
 };

struct point_pos Kpp13[4] = {
 27, 55,
 80, 55,
 27, 73,
 27, 90
 };

struct point_pos Kpp14[6] = {
 55, 23,
 55, 32,
 55, 41,
 55, 50,
 55, 59,
 16, 74,
 };

void screen11( void ) /* Bale Count */
{
  unsigned char tstring[32], i, data_changed;
  static unsigned char mode_sel, mode_reset;
  struct point_pos *pp;
  data_changed = 0;

  if( startup != 1 )
  {
    startup = 1;

    startup_frame();
    if( !Korean )
    display_f1_text( s0334.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Bale Count */
    else
    write_bitmap( adm, BaleCount, 55, 3, OR );	

    /*selection = 0;*/

    data_changed = 1;

    mode_sel = 1;
    mode_reset = 1;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1:
      if(mode_reset)
      {
          
        if( !Korean )
        {
    	draw_box( adm, 10, 40, 150, 77, CLEAR );
        draw_box( adm, 10, 40, 150, 77, EMPTY );
        }
        else        	
        {
       	draw_box( adm, 27, 37, 144, 77, CLEAR );
        draw_box( adm, 27, 37, 144, 77, EMPTY );
        }
        	        
        if(selection < 5)
          {
          if( mode_sel )
            { 
            if( !Korean )
              {
        	  sprintf( tstring, s0357.l[lang], 'A' + selection); /* Reset Total %1c ? */
              }
            else
              {
              write_bitmap( adm, Ktotal, 39, 50, OR );
              write_bitmap( adm, KReset, 72, 51, OR );              
              sprintf( tstring, "%1c ?", 'A' + selection);
              }
            }
          else 
            {            
            if( !Korean )
              sprintf( tstring, s0357.l[lang], 'A' + selection + 5 ); /* Reset Total %1c ? */
            else
              {
          	  write_bitmap( adm, Ktotal, 39, 50, OR );
          	  write_bitmap( adm, KReset, 72, 51, OR );
          	  sprintf( tstring, "%1c ?", 'A' + selection + 5 );
              }
            }
          }
        else
          {
          if( !Korean )        	  
        	sprintf( tstring, "%s?", s0299.l[lang]);  /* Reset Lube Count */
          else
            {
        	write_bitmap( adm, KLubeCount, 39, 51, OR );
        	write_bitmap( adm, KReset, 76, 51, OR );
        	sprintf( tstring, "?" );  
            }
          }
       
        if( !Korean )        
          display_f1_text( tstring, TSMAX, 15, 55, FIXED );
        else
          display_f1_text( tstring, TSMAX, 118, 54, FIXED );

        draw_box( adm, 2, 103, 118, 126, CLEAR );
        draw_box( adm, 128, 112, 147, 118, CLEAR );
        write_bitmap( adm, TAB,             3, 106, OR );
        write_bitmap( adm, TAB,            42, 106, OR );
        write_bitmap( adm, TABTICK,        81, 106, OR );
        write_bitmap( adm, NewTabcross,      123, 109, OR );
        
        mode_reset = 0;
      }
      break;

    case Key_S2:
      if(mode_reset)
      {
        if(mode_sel)
          mode_sel = 0;
        else
          mode_sel = 1;

        data_changed = 1;
      }
      break;  

    case Key_S3:
      if(mode_reset)
      {
        selection++;
        if(selection > 5)
          selection = 0;

        data_changed = 1;
      }
      else
      {
        if(selection < 5) /* Reset Bale Count */
        {
          if(mode_sel)
          {
            TotalBales[selection] = 0UL;
          }
          else
          {
            TotalBales[selection + 5] = 0UL;
          }
        }
        else /* Reset Lube */
        {
          ResetLubeCheck(); 
        }

        data_changed = 1;
        mode_reset = 1;
      }
      break;

    case Key_S4:
      if(mode_reset)
      {
        escape = 1;
      }
      else
      {
        data_changed = 1;
        mode_reset = 1;
      }
      break;
  }

  if(data_changed)
  {
    draw_box( adm, 2, 23, 158, 126, CLEAR );

    write_bitmap( adm, Korean? KTabReset:TABRESET, 3, 106, OR );
    write_bitmap( adm, TABCYCL,       81, 106, OR );
    write_bitmap( adm, TABESC,        120, 106, OR );

    if(mode_sel)
    {
      if( !Korean )
      {
	      for(i = 0; i < 5; i++)
	      {
	      sprintf ( tstring, s0033.l[lang], 'A' + i, TotalBales[i] );
	      display_f1_text( tstring, TSMAX, 12, (30 + (i * 10) ), FIXED );
	      }
      }
      else
      {
    	  write_bitmap( adm, Total, 14, 23, OR );    
    	  for(i = 0; i < 5; i++)
	      {
	      sprintf (tstring, "%1c        %-6lu", 'A' + i, TotalBales[i]);
	      display_f1_text( tstring, TSMAX, 66, (23 + (i * 9) ), FIXED );
	      }    	  
      }
      write_bitmap( adm, TABF2J, 42, 106, OR );
    }
    else
    {
      if( !Korean )
        {
    	for(i = 5; i < 10; i++)
          {
          sprintf ( tstring, s0033.l[lang], 'A' + i, TotalBales[i] );
          display_f1_text( tstring, TSMAX, 12, (30 + ((i- 5) * 10) ), FIXED );
          }
        }
      else
        {
    	  write_bitmap( adm, Total, 14, 23, OR );    
    	  for(i = 5; i < 10; i++)
	      {
	      sprintf ( tstring,"%1c        %-6lu", 'A' + i, TotalBales[i] );
	      display_f1_text( tstring, TSMAX, 66, (23 + ((i-5) * 9) ), FIXED );
	      }    	      	  
        }
      write_bitmap( adm, TABA2E, 42, 106, OR );
    }

    if( !Korean )
    {
    /* Lube count */    	
    display_f1_text( s0301.l[lang], TSMAX, 12, 80, FIXED );
    if( LubeCount < 0 )
      display_f1_text( " 0", TSMAX, 128, 80, FIXED );    
    else
      sprintf( tstring, " %3u", LubeCount );
    display_f1_text( tstring, TSMAX, 128, 80, FIXED );
        
    strcpy ( tstring, s0009.l[lang] );
    display_f1_text( tstring, TSMAX, 12, 90, FIXED );
    sprintf ( tstring, "%6li", GrandTotalBales );
    display_f1_text( tstring, TSMAX, 110, 90, FIXED );
    }
    else
    {
    write_bitmap( adm, KLubeCount, 31, 72, OR );
    if( LubeCount < 0 )
      sprintf( tstring, "%2u", 0 );
    else
      sprintf( tstring, "%2u", LubeCount );
    display_f1_text( tstring, TSMAX, 125, 73, FIXED );
    
    write_bitmap( adm, Grand, 34, 84, OR );
    write_bitmap( adm, Total, 45, 84, OR );
    sprintf( tstring, "%6li", GrandTotalBales );
    display_f1_text( tstring, TSMAX, 108, 89, FIXED );

    }
    
    if( !Korean )
    standard_pointer( 4, 30, 10 );
    else
    {
    pp = &Kpp14[selection];
    write_bitmap( adm, F1_POINT, pp->x, pp->y, OR );
    }
  }
}

void KnifeSystem( void ) /* Knife System */
{
unsigned char changed;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0386.l[lang], TSMAX, 35, 14, FIXED | CENTER | UNDERLINED ); /* Knife Sys */

  draw_box( adm, 6, 53, 158, 90, CLEAR );/* Knife System options */
  display_f1_text( KnivSystemString[1]->l[lang], TSMAX, 10, 35, FIXED );/*Relief Valve*/
  display_f1_text( KnivSystemString[0]->l[lang], TSMAX, 10, 45, FIXED );/*x23 Std*/
  display_f1_text( KnivSystemString[2]->l[lang], TSMAX, 10, 55, FIXED );/*x23 Select*/
  display_f1_text( KnivSystemString[3]->l[lang], TSMAX, 10, 65, FIXED );/*X25 Std*/
  display_f1_text( KnivSystemString[4]->l[lang], TSMAX, 10, 75, FIXED );/*x25 Select*/

  	 /*Knife option Serial Numbers*/
  display_f1_text( s0403.l[lang], TSMAX, 110 , 14 , FIXED | UNDERLINED); /* S/N */

  display_f1_text( "653001-654555", TSMAX, 77, 45, FIXED ); /* Relief S/N */
  display_f1_text( "654556-656840", TSMAX, 77, 35, FIXED ); /* x23 Std */
  display_f1_text( "654556-656840", TSMAX, 77, 55, FIXED ); /* x23 Select */
  display_f1_text( "656841+     ", TSMAX, 77, 65, FIXED ); /* x25 Std */
  display_f1_text( "656841+      ", TSMAX, 77, 75, FIXED ); /* x25 Select */
 
  write_bitmap( adm, TABDOWN, 3, 106, OR );
  write_bitmap( adm, TABUP, 42, 106, OR );
  write_bitmap( adm, TAB, 81, 106, OR );
  write_bitmap( adm, TABESC, 120, 106, OR );

  changed = 1;
  }
else
  {
  changed = 0;
  }

TimeDisplay();

switch( key )
  {
	case Key_S1:/*TAB_DOWN*/
	case Key_S1 | KeyDone | KeyRepeat:
	if( KnivSystem < 4 )
	 {
		KnivSystem++;
		changed = 1;
	 }
	else
	{
		KnivSystem = 4;
	}
    break;

	case Key_S2: /*TAB_UP*/
	case Key_S2 | KeyDone | KeyRepeat:
	if( KnivSystem )
	{
		KnivSystem--;
		changed = 1;
	}
    break;
    
	case Key_S3:
		break;
	  
	case Key_S4: /*ESC*/
		if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
		{
			KnifePressure = 0.80;
		}
		else
		{
			KnifePressure = 0.95;
		}

		KnifePressureBar = (unsigned short)(KnifePressure * 50.0);

		escape = 1;
    break;
  }

/*if( changed )
{
   if( (KnivSystem == x23_Select) || (KnivSystem == x25_Select))
      {
  	  KnifePressure = 0.80;
      }
    else
      {
  	  KnifePressure = 0.95;
      }

    KnifePressureBar = (unsigned short)(KnifePressure * 50.0);
 }*/

standard_pointer1( 4, 35, 10 ); /*Cursor movement*/
}

void screen074( void ) /* Diagnostics - Remote Test */
{
unsigned char tstring[32];

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0358.l[lang], TSMAX, 80, 12, FIXED | CENTER | UNDERLINED ); /* Remote Control */

  write_bitmap( adm, BATTSLIM, 118, 2, OR );

  display_f1_text( s0359.l[lang], TSMAX, OP_COL01-10, OP_ROW01+6, FIXED ); /* Top */
  display_f1_text( s0360.l[lang], TSMAX, OP_COL01-10, OP_ROW02+6, FIXED ); /* Left */
  display_f1_text( s0361.l[lang], TSMAX, OP_COL01-10, OP_ROW03+6, FIXED ); /* Right */
  display_f1_text( s0362.l[lang], TSMAX, OP_COL01-10, OP_ROW04+6, FIXED ); /* Bottom */

  write_bitmap( adm, TAB,       3, 106, OR );
  write_bitmap( adm, TAB,      42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  LedData.S = 0;
  Op.L = 0;

  leaf = 1;

  SetSerial0_Boot();
  }

TimeDisplay();

sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
display_f1_text( tstring, TSMAX, 136, 3, FIXED );

CheckSerial0();

switch( key )
  {
  case Key_S3:
    window = screen075;
    break;

  case Key_S4:
    escape = 1;
    break;
  }

draw_box( adm, OP_COL02, OP_ROW01, 158, 105, CLEAR );

write_bitmap( adm, (RemoteCode == RSTART) ? BUTTON01 : BUTTON03, OP_COL02, OP_ROW01+5, OR );
write_bitmap( adm, (RemoteCode == RFWD)   ? BUTTON01 : BUTTON03, OP_COL02, OP_ROW02+5, OR );
write_bitmap( adm, (RemoteCode == RREV)   ? BUTTON01 : BUTTON03, OP_COL02, OP_ROW03+5, OR );
write_bitmap( adm, (RemoteCode == RSTOP)  ? BUTTON01 : BUTTON03, OP_COL02, OP_ROW04+5, OR );

}


void screen075( void ) /* Diagnostics - Serial Logging */
{
unsigned char tstring[32];
unsigned int i;

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0380.l[lang], TSMAX, 80, 12, FIXED | CENTER | UNDERLINED ); /* Serial Logging */

  write_bitmap( adm, BATTSLIM, 118, 2, OR );

  write_bitmap( adm, TABLEFT,   3, 106, OR );
  write_bitmap( adm, TABRIGHT, 42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  leaf = 1;

  SetSerial0_Boot();
  }

TimeDisplay();

sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
display_f1_text( tstring, TSMAX, 136, 3, FIXED );

CheckSerial0();

/* serial logging test */
i = DelPul[SIODAT];
switch( key )
  {
  case Key_S1:
  case Key_S2:
    if( Facts[i][0] )
      {
      Facts[i][0] = 0;
      SIOdata = 0;
      }
    else
      {
      Facts[i][0] = 1;
      SIOdata = 1;
      }
    break;

  case Key_S3:
    window = screen076;
    break;

  case Key_S4:
    escape = 1;
    break;
  }

draw_box( adm, 12, 30, 150, 36, CLEAR );
strcpy( tstring, s0380.l[lang] ); /* Serial Logging */
strcat( tstring, ": " );
strcat( tstring, OnOff[SIOdata ? 1 : 0]->l[lang] ); /* 'Off'/'On' */
display_f1_text( tstring, TSMAX, 12, 30, FIXED );

}


void screen076( void ) /* Diagnostics - No PWM */
{
unsigned char tstring[32];

if( startup != 1 )
  {
  startup = 1;

  startup_frame();

  display_f1_text( s0381.l[lang], TSMAX, 80, 12, FIXED | CENTER | UNDERLINED ); /* 'No PWM' */

  write_bitmap( adm, BATTSLIM, 118, 2, OR );

  write_bitmap( adm, TABLEFT,   3, 106, OR );
  write_bitmap( adm, TABRIGHT, 42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  leaf = 1;
  }

TimeDisplay();

sprintf( tstring, "%2u.%1u", SupplyVolts / 10, SupplyVolts % 10 );
display_f1_text( tstring, TSMAX, 136, 3, FIXED );

CheckSerial0();

switch( key )
  {
  case Key_S1:
  case Key_S2:
	NoPWM = NoPWM ? 0 : 1;
    break;

  case Key_S3:
    window = screen071;
    break;

  case Key_S4:
    escape = 1;
    break;
  }

draw_box( adm, 12, 30, 150, 36, CLEAR );
strcpy( tstring, s0381.l[lang] ); /* 'No PWM' */
strcat( tstring, ": " );
strcat( tstring, OnOff[NoPWM]->l[lang] ); /* 'Off'/'On' */
display_f1_text( tstring, TSMAX, 12, 30, FIXED );

}

void screen13( void ) /* machine setup 1 */
{
unsigned char tstring[32], i, changed;  

struct point_pos *pp;

  if( !startup )
  {
    startup = 1;

    startup_frame();

    write_bitmap( adm, TABMINUS,   3, 106, OR );
    write_bitmap( adm, TABPLUS, 42, 106, OR );
    write_bitmap( adm, TABCYCL,  81, 106, OR );
    write_bitmap( adm, TABESC,  120, 106, OR );

    if( !Korean )
    display_f1_text( s0332.l[lang],   TS15, 75, 15, FIXED+CENTER+UNDERLINED ); /* Machine Setup 1 */
    else
    {
    write_bitmap( adm, MachineSetup, 48, 5, OR ); /* Machine Setup 1 */
    display_f1_text( "1", TS15, 107, 8, FIXED );
    }
    
    write_bitmap( adm, Korean? Layers:FILMLYRS,  Korean? 32:28,   Korean? 26:33, OR );
    write_bitmap( adm, TIPAUTO,   Korean? 94:90,   Korean? 23:30, OR );

    /*selection = 0;*/
    changed = 1;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1: /* minus */
    case Key_S1 | KeyDone | KeyRepeat:
      switch(selection)
      {
        case 0: /* film layers */
          if( CountSet > 2 )
            {
            CountSet--;
            }
          break;
          
        case 1: /* auto tip */
          if(PauseTip)
          {
            PauseTip = 0;
          }
          else
          {
            i = DelPul[AUTOTP];
            if( Facts[i][0] )
              Facts[i][0] = 0;
            else
              Facts[i][0] = 1;
          }
          break;

        case 2: /* crop type */
          if(CropType)
            CropType--;
          else
            CropType = 2;
          break;

        case 3: /* total select */
          if(BaleTotal)
            BaleTotal--;
          else
            BaleTotal = 9;
          break;

        }
      changed = 1;
      break;

    case Key_S2: /* plus */
    case Key_S2 | KeyDone | KeyRepeat:
      switch(selection)
      {
        case 0: /* film layers */
          if( CountSet < 99 )
            {
            CountSet++;
            }
          break;

        case 1: /* auto tip */
          if(PauseTip)
          {
            PauseTip = 0;
          }
          else
          {
            i = DelPul[AUTOTP];
            if(Facts[i][0])
              Facts[i][0] = 0;
            else
              Facts[i][0] = 1;
          }
          break;

        case 2: /* crop type */
          if(CropType < 2)
            CropType++;
          else
            CropType = 0;
          break;

        case 3: /* total select */
          if(BaleTotal < 9)
            BaleTotal++;
          else
            BaleTotal = 0;
          break;

       }
      changed = 1;
      break;

    case Key_S3: /* Selection */
      selection++;

      if(selection > 3)
        selection = 0;

      changed = 1;
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;
  }

  if( changed )
  {
	if( !Korean )
	draw_box( adm, 12, 65, 150, 96, CLEAR );
	else
    draw_box( adm, 25, 55, 130, 100, CLEAR );
    
    /* film layers */
    sprintf ( tstring, "%02u", CountSet );
    display_f1_text( tstring,     TS20,  Korean? 44:35, Korean? 55:65, FIXED );

    /* auto tip */
    i = ((Facts[DelPul[AUTOTP]][0]) || PauseTip) ? 1 : 0;
    if( !Korean )
      display_f1_text( OnOff[i]->l[lang], TS20, 90, 65, FIXED ); /* 'Off'/'On' */
    else
      write_bitmap( adm, KOnOff[i], 93, 55, OR );	
    
    /* crop select */
    if( !Korean )
      {
    strcpy( tstring, s0371.l[lang] ); /* 'Crop:' */
    strcat( tstring, ":  " );
    strcat( tstring, CropTypeString[CropType]->l[lang] ); /* Silage/Hay/Straw */
    display_f1_text( tstring, TSMAX, 20, 77, FIXED );
      }
    else
      {
      write_bitmap( adm, Crop, 37, 70, OR );
      display_f1_text( ":", TSMAX, 65, 73, FIXED );
      write_bitmap( adm, KCropTypeBitMap[CropType], 74, 71, OR );
      }
    SetCropTypeValues();

    /* Total select */
    if( !Korean )
    {
    strcpy( tstring, s0379.l[lang] ); /* 'Total:' */
    strcat( tstring, " A" );
    i = strlen( tstring ) - 1;
    tstring[i] += BaleTotal;
    display_f1_text( tstring, TS20, 20, 90, FIXED );
    }
    else
    {
    write_bitmap( adm, Total, 37, 87, OR );
    strcpy( tstring, ": A" );
    i = strlen( tstring ) - 1;
    tstring[i] += BaleTotal;
    display_f1_text( tstring, TS20, 65, 90, FIXED );  
    }
    /* set pointer */
    if( !Korean)
    pp = &pp13[selection];
    else
    pp = &Kpp13[selection];
    write_bitmap( adm, F1_POINT, pp->x, pp->y, OR );

    ResetSequenceFactors( SEQ_ALL );
  }
}


void screen131( void ) /* machine setup 2 */
{
unsigned char tstring[32], i, changed;  

  if( !startup )
  {
    startup = 1;

    startup_frame();

    write_bitmap( adm, TABMINUS,   3, 106, OR );
    write_bitmap( adm, TABPLUS, 42, 106, OR );
    write_bitmap( adm, TABCYCL,  81, 106, OR );
    write_bitmap( adm, TABESC,  120, 106, OR );

    
    
    if( !Korean )
      display_f1_text( s0333.l[lang],   TS15, 75, 15, FIXED+CENTER+UNDERLINED ); /* Machine Setup 2 */
    else
      {
      write_bitmap( adm, MachineSetup, 48, 5, OR ); /* Machine Setup 2 */
      display_f1_text( "2", TS15, 107, 8, FIXED );
      } 
    /*selection = 0;*/
    changed = 1;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1: /* minus */
    case Key_S1 | KeyDone | KeyRepeat:
      switch(selection)
      {
        case 0: /* Transfer Time */
          i = DelPul[DIVDEL];
          if( Facts[i][0] > PF[i].min )
            Facts[i][0]--;
          else
            Facts[i][0] = PF[i].max;
          break;
        
        case 1: /* film sensor */ 
          i = DelPul[FILMBK];
          if(Facts[i][0] == PF[i].min)
            Facts[i][0] = PF[i].max;
          else
            Facts[i][0]--;
          break;

        case 2: /* lube dose */
          i = DelPul[LUBEDS];
          if(Facts[i][0] > PF[i].min)
            Facts[i][0]--;
          break;
          
        case 3: /* Net Brake Power */
          /* i = DelPul[PWMBP1];
          if(Facts[i][0] > PF[i].min)
            Facts[i][0]--; */
          break;          
      }
      changed = 1;
      break;

    case Key_S2: /* plus */
    case Key_S2 | KeyDone | KeyRepeat:
      switch(selection)
      {
        case 0: /* Transfer Time */
          i = DelPul[DIVDEL];	
          if(Facts[i][0] < PF[i].max)
            Facts[i][0]++;
          else
            Facts[i][0] = PF[i].min;
          break;

        case 1: /* film sensor */
          i = DelPul[FILMBK];
          if(Facts[i][0] == PF[i].max)
            Facts[i][0] = PF[i].min;
          else
            Facts[i][0]++;
          break;

        case 2: /* lube dose */
          i = DelPul[LUBEDS];
          if(Facts[i][0] < PF[i].max)
            Facts[i][0]++;
          break;
          
        case 3: /* lube dose */
          /* i = DelPul[PWMBP1];
          if(Facts[i][0] < PF[i].max)
            Facts[i][0]++; */
          break;          
      }
      changed = 1;
      break;

    case Key_S3: /* Selection */
      selection++;

      if(selection > 2)
        selection = 0;
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;
  }

  if(changed)
  {
	if( !Korean )
	  {  
	    draw_box( adm, 12, 30, 158, 60, CLEAR );
	
	    /* Transfer Time */
	    strcpy( tstring, s0100.l[lang] ); /* 'Transfer time:' */
	    strcat( tstring, ": " );
	    i = Facts[DelPul[DIVDEL]][0];
	    strcat( tstring, ShortLong[i]->l[lang] ); /* 'Short'/'Long'/'Manual' */
	    display_f1_text( tstring, TSMAX, 12, 30, FIXED );
	
	    /* film sensor */
	    strcpy( tstring, s0206.l[lang] ); /* 'Film Sensor:' */
	    strcat( tstring, ": " );
	    i = Facts[DelPul[FILMBK]][0];
	    strcat( tstring, OnOff[i]->l[lang] ); /* 'Off'/'On' */
	    display_f1_text( tstring, TSMAX, 12, 40, FIXED );
	
	    /* lube dose */
	    strcpy( tstring, s0321.l[lang] ); /* 'Lube Dose' */
	    strcat( tstring, ": 0" );
	    i = strlen( tstring ) - 1;
	    tstring[i] += Facts[DelPul[LUBEDS]][0]; /* works with 0 to 9 only ! */
	    display_f1_text( tstring, TSMAX, 12, 50, FIXED );
	    
	    /* Net Brake Power */
	    /*
	    sprintf( tstring, s0383.l[lang], Facts[DelPul[PWMBP1]][0] ); / * Net Brake Power %3u* /	    	    
	    display_f1_text( tstring, TSMAX, 12, 60, FIXED );
	    */	    
      }
    else
      {
    	draw_box( adm, 25, 25, 158, 80, CLEAR );

	    /* Transfer Time */
    	write_bitmap( adm, TransferTime, 25, 27, OR ); /* Transfer Time */	    	
	    i = Facts[DelPul[DIVDEL]][0];
	    write_bitmap( adm, KShortLong[i], 109, 26, OR );	    
	
	    /* film sensor */
	    write_bitmap( adm, FilmSensor, 25, 49, OR ); /* 'Film Sensor:' */	    
	    i = Facts[DelPul[FILMBK]][0];
	    write_bitmap( adm, KOnOff[i], 105, 49, OR ); /* 'Off'/'On' */ 
	
	    /* lube dose */
	    write_bitmap( adm, LubeDose, 26, 67, OR ); /* 'Lube Dose' */ 
	    sprintf ( tstring, "%02u", Facts[DelPul[LUBEDS]][0] );	   
	    display_f1_text( tstring, TSMAX, 110, 69, FIXED );
	    
	    /* Net Brake Power */
	    /*
	    sprintf( tstring, s0383.l[lang], Facts[DelPul[PWMBP1]][0] ); / * Net Brake Power %3u * /	    	    
	    display_f1_text( tstring, TSMAX, 12, 80, FIXED );	    
	    */
      }
    SetOneDispRevs();
    ResetSequenceFactors( SEQ_ALL );
  }
  if( !Korean )
    standard_pointer( 4, 30, 10 );
  else
    standard_pointer( 15, 31, 20);
}


void set_language( void )
{
unsigned char c, page, offset, old_selection, old_lang;
  
  if( !startup )
  {
    startup = 1;

    startup_frame();

    write_bitmap( adm, TABDOWN,   3, 106, OR );
    write_bitmap( adm, TABUP, 42, 106, OR );
    write_bitmap( adm, TABENTS,  81, 106, OR );
    write_bitmap( adm, TABESC,  120, 106, OR );

    display_f1_text( s0342.l[lang], TS15, 75, 15, FIXED+CENTER+UNDERLINED ); /* Language */
    selection = lang;

    old_selection = 0xff;
  }
  else
  {
    old_selection = selection;
  }

  TimeDisplay();

  switch( key )
  {
  	case Key_S1: /* Down */
  	  /*if( selection < (MAXLANG - 1) )*/
  	  if( selection < MAXLANG )
  	    selection++;
  	  
  	  if(LangStartup) /* if key pressed during start up */
        LangStartup = 2; /* dont exit after 1 sec */
  	  break;
  	  
  	case Key_S2: /* Up */
  	  if( selection )
  	    selection--;
  	  
  	  if( LangStartup ) 
        LangStartup = 2;
  	  break;
  	  
    case Key_S3: /* Ent */
      if( selection < MAXLANG )
        {
    	  lang = selection;
    	  Facts[DelPul[LANGUA]][0] = selection;

		  if( Facts[DelPul[LANGUA]][0] == 3 ) /* French language */
		  {
			  Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX2]][0]; /* copy 'Tip bale French' to 'Tip wrapped bale' */
		  }
		  else
		  {
			  Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX1]][0]; /* copy 'Tip wrapped bale' */
		  }
		  Korean = 0;
        }
      else if( selection == MAXLANG )
        {
        Korean = 1;
        /* window = main_loop; */
        }
      
      startup = 0;
      old_time = 0xff;
      
      if( LangStartup )
        LangStartup = 2;
      break;

    case Key_S4: /* ESC */
      if(LangStartup == 2)
      {
        LangStartup = 0;
        window = main_loop;        
      }
      else
      {
    	  escape = 1;
      }
      break;
  }
  
  if( old_selection != selection )
  {
    draw_box( adm, 12, 30, 158, 105, CLEAR );
    
	page = selection / 7; /* think in intergers, don't simplify this */
	offset = page * 7;
    for( c = 0; c < 7; c++ )
    {
        if( offset < MAXLANG )
        {
        	old_lang = lang;
        	lang = offset;
        	display_f1_text( s0214.l[offset], TS20,  12, 30+(c*10), FIXED );
        	lang = old_lang;
        }
        else if( offset == MAXLANG  )
        {
        	display_f1_text( "Korean", TS20, 12, 30+(c*10), FIXED );
        }
        else
        {   /* '                ' */
        	display_f1_text( f0003, TS20, 12, 30+(c*10), FIXED );
        }
        offset++;
    }
    
    draw_box( adm, 4, 30, 4+4, 105, CLEAR );
    write_bitmap( adm, F1_POINT, 4, 30+((selection % 7) * 10), OR );
  }
  
  if( (LangStartup == 1) && (demi_secs > 2) )
  {
  	LangStartup = 0;
  	lang = Facts[DelPul[LANGUA]][0] = selection;
    if( Facts[DelPul[LANGUA]][0] == 3 ) /* French language */
			{
			Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX2]][0]; /* copy 'Tip bale French' to 'Tip wrapped bale' */
			}
    else
    	{
    	Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX1]][0]; /* copy 'Tip wrapped bale' */
    	}
  	window = main_loop;
  }

}

void SetCropTypeValues( void )
{
	
/* set baler full delay for crop type */
Facts[DelPul[DELYLB]][0] = BalerFull[CropType];
  
/* set bale only for crop type */
Facts[DelPul[SEQNUM]][0] = CropType;

}


void standard_pointer( unsigned char l, unsigned char s, unsigned char i )
{

draw_box( adm, l, s, l+4, 105, CLEAR );
write_bitmap( adm, F1_POINT, l, s+(selection*i), OR );
}

void standard_pointer1( unsigned char l, unsigned char s, unsigned char i )
{

draw_box( adm, l, s, l+4, 105, CLEAR );
write_bitmap( adm, F1_POINT, l, s+(KnivSystem*i), OR );
}




