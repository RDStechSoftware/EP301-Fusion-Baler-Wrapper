#include <inh83.h>
#include <ioh83003.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bytedef.h"


#define XSIZE 107
#define YSIZE 9
#define XPOS1 40
#define XPOS2 100
#define YPOS1 30
#define YPOS2 55
#define YPOS3 80

void display_levels( void ) /* contrast & brightness */
{
unsigned char *pd, x_co, change/*, tstring[30]*/;

if( !startup )
  {
  startup = 1;

  startup_frame();
  
  if(Korean)
  write_bitmap( adm, KContrast, 69, 5, OR );
  
  write_bitmap( adm, CONTRST1, 20-(CONTRST1[1]/2)+4, YPOS2+8, OR );
  write_bitmap( adm, BRIGHTN1, 20-(BRIGHTN1[1]/2)+4, YPOS3+6, OR );

           /*   mem, bitmap,   col, row, mode */
  write_bitmap( adm, TABLEFT,   3, 106, OR );
  write_bitmap( adm, TABRIGHT, 42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );

  leaf = 1;
  change = 1;
  }
else
  {
  change = 0;
  }

TimeDisplay();

switch( key )
  {
  case Key_S1: /* left */
  case Key_S1 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0: /* left */
        DayNight = DayNight ? 0 : 1;
        change = 1;
        break;

      case 1: /* left */
        pd = &Contrast[DayNight];
        (*pd)--;
        if( *pd < (DEFAULT_CONTRAST - DCRANGE) )
          {
          *pd = (DEFAULT_CONTRAST + DCRANGE);
          }
        change = 1;
        break;

      case 2: /* left */
        pd = &Brightness[DayNight];
        *pd -= 8;
        if( *pd < (DEFAULT_BRIGHTNESS - BRIGHTRANGE) )
          {
          *pd = (DEFAULT_BRIGHTNESS + BRIGHTRANGE);
          }
        change = 1;
        break;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0: /* right */
        DayNight = DayNight ? 0 : 1;
        change = 1;
        break;

      case 1: /* right */
        pd = &Contrast[DayNight];
        (*pd)++;
        if( *pd > (DEFAULT_CONTRAST + DCRANGE) )
          {
          *pd = (DEFAULT_CONTRAST - DCRANGE);
          }
        change = 1;
        break;

      case 2: /* right */
        pd = &Brightness[DayNight];
        *pd += 4;
        if( *pd > (DEFAULT_BRIGHTNESS + BRIGHTRANGE) )
          {
          *pd = (DEFAULT_BRIGHTNESS - BRIGHTRANGE);
          }
        change = 1;
        break;
      }
    break;

  case Key_S3: /* cycle */
    selection++;
    if( selection > 2 )
      {
      selection = 0;
      }
    change = 1;
    break;

  case Key_S4: /* ESC */
    escape = 1;
    break;
  }

if( change )
  { 
  SetContrast();
  SetBrightness();

  draw_box( adm, 4+4, (YPOS1-3), 8+4, (YPOS3+9+7), CLEAR );
  write_bitmap( adm, CONPOINT, 4+4, (YPOS1+1+7)+(selection*25), OR );

  draw_box( adm, XPOS1, YPOS1+8-(DAYSYM[1]/2)-2,
      XPOS2+DAYSYM[1]+2, YPOS1+8+(DAYSYM[1]/2)+2, CLEAR );
  if( DayNight )
    {
    draw_box( adm, XPOS2-3, YPOS1+8-(DAYSYM[1]/2)-2,
      XPOS2+DAYSYM[1]+1, YPOS1+8+(DAYSYM[1]/2)+1, EMPTY );
    }
  else
    {
    draw_box( adm, XPOS1, YPOS1+8-(DAYSYM[1]/2)-2,
      XPOS1+DAYSYM[1]+3, YPOS1+8+(DAYSYM[1]/2)+1, EMPTY );
    }
  
  write_bitmap( adm, DAYSYM, XPOS1+2, YPOS1+8-(DAYSYM[1]/2), OR );
  write_bitmap( adm, NIGHTSYM, XPOS2+2, YPOS1+8-(NIGHTSYM[1]/2), OR );

  draw_box( adm, XPOS1, YPOS2+8, XPOS1+XSIZE, YPOS2+YSIZE+8, CLEAR );
  x_co = XPOS1 + (unsigned char)(((unsigned short)Contrast[DayNight] - (DEFAULT_CONTRAST - DCRANGE)) * XSIZE / (DCRANGE * 2));
  draw_box( adm, XPOS1, YPOS2+8, x_co, YPOS2+YSIZE+8, FULL );
  draw_box( adm, x_co, YPOS2+8, XPOS1+XSIZE, YPOS2+YSIZE+8, EMPTY );

  draw_box( adm, XPOS1, YPOS3+6, XPOS1+XSIZE, YPOS3+YSIZE+6, CLEAR );
  x_co = 40 + (unsigned char)(((unsigned short)Brightness[DayNight] - (DEFAULT_BRIGHTNESS - BRIGHTRANGE)) * XSIZE / (BRIGHTRANGE * 2));
  draw_box( adm, XPOS1, YPOS3+6, x_co, YPOS3+YSIZE+6, FULL );
  draw_box( adm, x_co, YPOS3+6, XPOS1+XSIZE, YPOS3+YSIZE+6, EMPTY );
  /*sprintf( tstring, "x%03u B%03u", x_co, Brightness[DayNight] );  
  display_f1_text( tstring, 35, 3, 98, FIXED );*/
  }

}


void clock_set( void )        /* time set */
{
unsigned char change, settime;

if( !startup )
  {
  startup = 1;

  startup_frame();

           /*   mem, bitmap,   col, row, mode */
  write_bitmap( adm, TABLEFT,   3, 106, OR );
  write_bitmap( adm, TABRIGHT, 42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );
  if( !Korean )
  {
  display_f1_text( s0341.l[lang], TS15, 75, 15, FIXED+CENTER+UNDERLINED ); /* Clock Adjust */

  display_f1_text( s0366.l[lang],  TS20, 12, 30, FIXED ); /* 'Hrs' */
  display_f1_text( s0367.l[lang],  TS20, 12, 40, FIXED ); /* 'Mins' */
  display_f1_text( s0368.l[lang],  TS20, 12, 50, FIXED ); /* 'Date' */
  display_f1_text( s0369.l[lang],  TS20, 12, 60, FIXED ); /* 'Month' */
  display_f1_text( s0370.l[lang],  TS20, 12, 70, FIXED ); /* 'Year' */
  }
  else
  {
  write_bitmap( adm, KClock,   70, 3, OR );
	  
  write_bitmap( adm, KClock, 25, 24, OR );
  write_bitmap( adm, KMins, 32, 41, OR );
  write_bitmap( adm, KDate, 32, 57, OR );
  write_bitmap( adm, KMonth, 33, 73, OR );
  write_bitmap( adm, KYear, 33, 88, OR );
  }

  leaf = 1;
  change = 1;
  }
else
  {
  change = 0;
  }

TimeDisplay();

settime = 0;

switch ( key )
  {
  case Key_S1:
  case Key_S1 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
        if( hours )
          {
          hours--; 
          change = 1;
          settime = 1;
          }
        break;

      case 1:
        if( minutes )
          {
          minutes--; 
          change = 1;
          settime = 1;
          }
        break;

      case 2:
        if( _date > 1 )
          {
          _date--; 
          change = 1;
          settime = 1;
          }
        break;

      case 3:
        if( month > 1 )
          {
          month--; 
          change = 1;
          settime = 1;
          }
        break;

      case 4:
        if( year > 2000 )
          {
          year--; 
          change = 1;
          settime = 1;
          }
        break;
      }
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 0:
        if( hours < 23 )
          {
          hours++; 
          change = 1;
          settime = 1;
          }
        break;

      case 1:
        if( minutes < 59 )
          {
          minutes++; 
          change = 1;
          settime = 1;
          }
        break;

      case 2:
        if( _date < 31 )
          {
          _date++; 
          change = 1;
          settime = 1;
          }
        break;

      case 3:
        if( month < 12 )
          {
          month++; 
          change = 1;
          settime = 1;
          }
        break;

      case 4:
        if( year < 2099 )
          {
          year++; 
          change = 1;
          settime = 1;
          }
        break;
      }
    break;

  case Key_S4:
    escape = 1;
    break;
  }

if( !editing )
  {
  switch ( key )
    {
    case Key_S3:
      selection++;
      if( selection > 4 )
        {
        selection = 0;
        }
      change = 1;
      break;
    }
  }

if( change )
  {
	  if( !Korean )
	  {
	  standard_pointer( 4, 30, 10 );
	
	  display_f1_number(   hours, 0, 1, 0, 130, 30, RIGHT, 2 );
	  display_f1_number( minutes, 0, 1, 0, 130, 40, RIGHT, 2 );
	  display_f1_number(   _date, 0, 1, 0, 130, 50, RIGHT, 2 );
	  display_f1_number(   month, 0, 1, 0, 130, 60, RIGHT, 2 );
	  display_f1_number(    year, 0, 1, 0, 118, 70, RIGHT, 4 );
	  }
	  else
	  {
	  standard_pointer( 14, 26, 16 );
	
	  display_f1_number(   hours, 0, 1, 0, 91, 26, RIGHT, 2 );
	  display_f1_number( minutes, 0, 1, 0, 91, 42, RIGHT, 2 );
	  display_f1_number(   _date, 0, 1, 0, 91, 58, RIGHT, 2 );
	  display_f1_number(   month, 0, 1, 0, 91, 74, RIGHT, 2 );
	  display_f1_number(    year, 0, 1, 0, 91, 91, RIGHT, 4 );
	  }
  }

if( settime )
  {
  old_time = 0xff;
  old_date = 0xff;
  set_time();
  }
}


void speaker_test( void ) /* loud speaker test */
{
unsigned char change;
static unsigned char temp_KeyVolume, temp_AlarmVolume;

if( !startup )
  {
  startup = 1;

  startup_frame();

   /*   mem, bitmap,   col, row, mode */
  write_bitmap( adm, TABLEFT,   3, 106, OR );
  write_bitmap( adm, TABRIGHT, 42, 106, OR );
  write_bitmap( adm, TABCYCL,  81, 106, OR );
  write_bitmap( adm, TABESC,  120, 106, OR );
  if( !Korean )
  display_f1_text( s0340.l[lang], TS15, 75, 15, FIXED+CENTER+UNDERLINED ); /* Volume */
  else
  write_bitmap( adm, KVolume,  70, 5, OR );

  switch(KeyVolume)
  {
    case 0:
      temp_KeyVolume = 0;
      break;

    case 1:
      temp_KeyVolume = 1;
      break;

    case 4:
      temp_KeyVolume = 2;
      break;

    case 5:
      temp_KeyVolume = 3;
      break;

    case 6:
      temp_KeyVolume = 4;
      break;

    case 7:
      temp_KeyVolume = 5;
      break;

    case 9:
      temp_KeyVolume = 6;
      break;

    case 12:
      temp_KeyVolume = 7;
      break;

    case 13:
      temp_KeyVolume = 8;
      break;

    case 15:
      temp_KeyVolume = 9;
      break;
  }

  switch(AlarmVolume)
  {
    case 0:
      temp_AlarmVolume = 0;
      break;

    case 1:
      temp_AlarmVolume = 1;
      break;

    case 4:
      temp_AlarmVolume = 2;
      break;

    case 5:
      temp_AlarmVolume = 3;
      break;

    case 6:
      temp_AlarmVolume = 4;
      break;

    case 7:
      temp_AlarmVolume = 5;
      break;

    case 9:
      temp_AlarmVolume = 6;
      break;

    case 12:
      temp_AlarmVolume = 7;
      break;

    case 13:
      temp_AlarmVolume = 8;
      break;

    case 15:
      temp_AlarmVolume = 9;
      break;
  }

  leaf = 1;
  change = 1;
  }
else
  {
  change = 0;
  }

TimeDisplay();

switch( key )
  {
  case Key_S1: /* left */
  case Key_S1 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 1: /* left */
        if( temp_KeyVolume )
          {
          temp_KeyVolume--;
          }
        break;

      /*case 1:
        if( KeyNote )
          {
          KeyNote--;
          Note = KeyNote; 
          NoteLength = 3 * NOTEDURATION;
          }
        break;*/

      case 0: /* left */
        if( temp_AlarmVolume )
          {
          temp_AlarmVolume--;
          }
        break;

      /*case 3:
        if( AlarmNote )
          {
          AlarmNote--;
          Note = AlarmNote; 
          NoteLength = 3 * NOTEDURATION;
          }
        break;*/
      }
    change = 1;
    break;

  case Key_S2:
  case Key_S2 | KeyDone | KeyRepeat:
    switch( selection )
      {
      case 1: /* right */
        if( temp_KeyVolume < 9 )
          {
          temp_KeyVolume++;
          }
        break;

      /*case 1:
        if( KeyNote < 104 )
          {
          KeyNote++;
          Note = KeyNote;
          NoteLength = 3 * NOTEDURATION;
          }
        break;*/

      case 0: /* right */
        if( temp_AlarmVolume < 9 )
          {
          temp_AlarmVolume++;
          }
        break;

      /*case 3: 
        if( AlarmNote < 104 )
          {
          AlarmNote++;
          Note = AlarmNote;
          NoteLength = 3 * NOTEDURATION;
          }
        break;*/
      }
    change = 1;
    break;

  case Key_S3: /* cycle */
    selection++;
    if( selection > 1 )
      {
      selection = 0;
      }
    change = 1;
    break;

  case Key_S4: /* ESC */
    escape = 1;
    break;

  case Key_F1:
    NoteLength = 32 * NOTEDURATION;
    break;

  case Key_L1:
    if( Music == NULL )
      {
      Music = DixieLand;
      }
    break;

  case Key_F2:
    Music = NULL;
    break;
  }

  switch(temp_AlarmVolume)
  {
    case 0:
      AlarmVolume = 0;
      break;

    case 1:
      AlarmVolume = 1;
      break;

    case 2:
      AlarmVolume = 4;
      break;

    case 3:
      AlarmVolume = 5;
      break;

    case 4:
      AlarmVolume = 6;
      break;

    case 5:
      AlarmVolume = 7;
      break;

    case 6:
      AlarmVolume = 9;
      break;

    case 7:
      AlarmVolume = 12;
      break;

    case 8:
      AlarmVolume = 13;
      break;

    case 9:
      AlarmVolume = 15;
      break;
  }

  switch(temp_KeyVolume)
  {
    case 0:
      KeyVolume = 0;
      break;

    case 1:
      KeyVolume = 1;
      break;

    case 2:
      KeyVolume = 4;
      break;

    case 3:
      KeyVolume = 5;
      break;

    case 4:
      KeyVolume = 6;
      break;

    case 5:
      KeyVolume = 7;
      break;

    case 6:
      KeyVolume = 9;
      break;

    case 7:
      KeyVolume = 12;
      break;

    case 8:
      KeyVolume = 13;
      break;

    case 9:
      KeyVolume = 15;
      break;
  }

  if( change )
  {
    draw_box( adm, 12, 35, 143, 86, CLEAR );
    
    write_bitmap( adm, VOLUMESCALE,  20, 35, OR );

    draw_box( adm, 28 + (temp_AlarmVolume * 9), 42, 32 + (temp_AlarmVolume * 9), 52, CLEAR );
    draw_box( adm, 28 + (temp_AlarmVolume * 9), 42, 32 + (temp_AlarmVolume * 9), 52, EMPTY );

    draw_box( adm, 28 + (temp_KeyVolume * 9), 42 + 26, 32 + (temp_KeyVolume * 9), 52 + 26, CLEAR );
    draw_box( adm, 28 + (temp_KeyVolume * 9), 42 + 26, 32 + (temp_KeyVolume * 9), 52 + 26, EMPTY );

    standard_pointer( 4, 44, 26 );

  /*display_f1_number( KeyVolume, 0, 1, 0, 132, 30, RIGHT, 2 );

  display_f1_number( (2000000.0 / (float)NoteFrequency[KeyNote]),
    0, 1, 1, 102, 40, RIGHT, 7 );

  display_f1_number( AlarmVolume, 0, 1, 0, 132, 50, RIGHT, 2 );

  display_f1_number( (2000000.0 / (float)NoteFrequency[AlarmNote]),
    0, 1, 1, 102, 60, RIGHT, 7 );*/
  }

}


void screen15(void) /* Baler Full / Net */
{
unsigned char i, tstring[32], changed;

  if( startup != 1 )
  {
    startup = 1;
    
    startup_frame();

    display_f1_text( s0343.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Baler Full / Net */

    sprintf ( tstring, "%s %s", s0231.l[lang], s0363.l[lang] );
    display_f1_text( tstring, TSMAX, 12, 28, FIXED ); /* Baler Full Silage */

    sprintf ( tstring, "%s %s", s0231.l[lang], s0364.l[lang] );
    display_f1_text( tstring, TSMAX, 12, 37, FIXED ); /* Baler Full Hay */

    sprintf ( tstring, "%s %s", s0231.l[lang], s0365.l[lang] );
    display_f1_text( tstring, TSMAX, 12, 46, FIXED ); /* Baler Full Straw */

    display_f1_text( s0232.l[lang],  TSMAX, 12, 55, FIXED ); /* Net On */
    display_f1_text( s0233.l[lang],  TSMAX, 12, 64, FIXED ); /* Pre-Net Wait */
    display_f1_text( s0234.l[lang],  TSMAX, 12, 73, FIXED ); /* Post-Net Wait */
    display_f1_text( s0391.l[lang],  TSMAX, 12, 82, FIXED ); /* Net error */

    write_bitmap( adm, TABMINUS,  3, 106, OR );
    write_bitmap( adm, TABPLUS,   42, 106, OR );
    write_bitmap( adm, TABCYCL, 81, 106, OR );
    write_bitmap( adm, TABESC, 120, 106, OR );

    /* selection = 0; */
    changed = 1;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1: /* Minus */
    case Key_S1 | KeyDone | KeyRepeat:
      switch(selection)
      {
        case 0: /* baler full silage */
          if(BalerFull[0])
            BalerFull[0]--;
          break;

        case 1: /* Baler Full Hay */
          if(BalerFull[1])
            BalerFull[1]--;
          break;

        case 2: /* Baler full straw */
          if(BalerFull[2])
            BalerFull[2]--;
          break;

        case 3: /* net on */
          i = DelPul[DELYBC];
          if(Facts[i][0])
            Facts[i][0]--;
          break;

        case 4: /* pre-net wait */
          i = DelPul[DELYCD];
          if(Facts[i][0])
            Facts[i][0]--;
          break;

        case 5: /* post-net wait */
          i = DelPul[DELYDE];
          if(Facts[i][0])
            Facts[i][0]--;
          break;

        case 6: /* post-net wait */
          i = DelPul[DELYNT];
          if(Facts[i][0] > 10)
            Facts[i][0]--;
          break;
          
        case 7: /* External Buzzer */
          if(!ExtBuzzer)
            ExtBuzzer = 1;
          else
            ExtBuzzer = 0;
          break;
      }
      changed = 1;
      break;

    case Key_S2: /* Plus */
    case Key_S2 | KeyDone | KeyRepeat:
      switch(selection)
      {
        case 0:  /* baler full silage */
          if(BalerFull[0] < 250)
            BalerFull[0]++;
          break;

        case 1: /* Baler Full Hay */
          if(BalerFull[1] < 250)
            BalerFull[1]++;
          break;

        case 2: /* Baler full straw */
          if(BalerFull[2] < 250)
            BalerFull[2]++;
          break;
          
        case 3: /* net on */
          i = DelPul[DELYBC];
          if(Facts[i][0] < 250)
            Facts[i][0]++;
          break;

        case 4: /* pre-net wait */
          i = DelPul[DELYCD];
          if(Facts[i][0] < 250)
            Facts[i][0]++;
          break;

        case 5: /* post-net wait */
          i = DelPul[DELYDE];
          if(Facts[i][0] < 250)
            Facts[i][0]++;
          break;

        case 6: /* post-net wait */
          i = DelPul[DELYNT];
          if(Facts[i][0] < 99)
            Facts[i][0]++;
          break;          
                    
        case 7: /* External Buzzer */
          if(!ExtBuzzer)
            ExtBuzzer = 1;
          else
            ExtBuzzer = 0;
          break;
      }
      changed = 1;
      break;

    case Key_S3: /* cycle */
      if(selection < 7)
        selection ++;
      else
        selection = 0;
      break;

    case Key_S4: /* escape */
      escape = 1;
      break;

  }

  if( changed )
  {
    /* baler full silage */
    i = BalerFull[0];
    sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
    display_f1_text( tstring,     TS20, 124, 28, FIXED );

    /* Baler Full Hay */
    i = BalerFull[1];
    sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
    display_f1_text( tstring,     TS20, 124, 37, FIXED );

    /* Baler full straw */
    i = BalerFull[2];
    sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
    display_f1_text( tstring,     TS20, 124, 46, FIXED );

    SetCropTypeValues();

    /* net on */
    i = Facts[DelPul[DELYBC]][0];
    sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
    display_f1_text( tstring,     TS20, 124, 55, FIXED );

    /* pre-net wait */
    i = Facts[DelPul[DELYCD]][0];
    sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
    display_f1_text( tstring, TS20, 124, 64, FIXED );

    /* post-net wait */
    i = Facts[DelPul[DELYDE]][0];
    sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
    display_f1_text( tstring, TS20, 124, 73, FIXED );

    /* Net error */
    i = Facts[DelPul[DELYNT]][0];
    sprintf ( tstring, "%3us", i ); 
    display_f1_text( tstring, TS20, 124, 82, FIXED );
    
    /* External Buzzer */
    draw_box( adm, 12, 91, 150, 100, CLEAR );
    strcpy( tstring, s0382.l[lang] ); /* 'External Buzzer' */
    strcat( tstring, ": " );
    strcat( tstring, OnOff[ExtBuzzer]->l[lang] ); /* 'Off'/'On' */
    display_f1_text( tstring,  TSMAX, 12, 91, FIXED );
  }

  standard_pointer( 4, 28, 9 );

}



void screen16(void) /* Bale transfer */
{
unsigned char i, tstring[32], changed;
static unsigned char ScreenSel;

  if( startup != 1 )
  {
    startup = 1;
    
    startup_frame();

    display_f1_text( s0344.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Bale Transfer */

    write_bitmap( adm, TABMINUS,  3, 106, OR );
    write_bitmap( adm, TABPLUS,   42, 106, OR );
    write_bitmap( adm, TABCYCL, 81, 106, OR );
    write_bitmap( adm, TABESC, 120, 106, OR );

    /*selection = 0;*/
    changed = 2;
    ScreenSel = 0;

  }
  else
  {
    changed = 0;
  }

  TimeDisplay();
  
  switch( key )
  {
    case Key_S1: /* Minus */
    case Key_S1 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* Open Lid Up */
            i = DelPul[DELYEF];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 1: /* Open Lid Up+ */
            i = DelPul[DELYFG];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 2: /* Pause Open Short */
            i = DelPul[PAUSRT];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 3: /* Pause Open Long */
            i = DelPul[PAULNG];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 4: /* Close Travel+ */
            i = DelPul[DELYJK];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 5: /* Delay Open Time */
            i = DelPul[DELYOT];
            if(Facts[i][0] > PF[i].min)
              Facts[i][0]--;
            break;

          case 6: /* Delay Pause Time */
            i = DelPul[DELYPT];
            if(Facts[i][0] > PF[i].min)
              Facts[i][0]--;
            break;
        }
      }  
      else
      {
        switch(selection)
        {
          case 0: /* Chamber Speed 1 */
            i = DelPul[PWMCS1];
            if(Facts[i][0] > PF[i].min)
              Facts[i][0]--;
              break;

          case 1: /* Chamber Speed 2 */
            i = DelPul[PWMCS2];
            if(Facts[i][0] > PF[i].min)
              Facts[i][0]--;
              break;

          case 2: /* Chamber Speed 3 */
            i = DelPul[PWMCS3];
            if(Facts[i][0] > PF[i].min)
              Facts[i][0]--;
              break;  
        }
      }
      changed = 1;
      break;

    case Key_S2: /* Plus */
    case Key_S2 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* Open Lid Up */
            i = DelPul[DELYEF];
            if(Facts[i][0] < 250)
              Facts[i][0]++;
            break;

          case 1: /* Open Lid Up+ */
            i = DelPul[DELYFG];
            if(Facts[i][0] < 250)
              Facts[i][0]++;
            break;

          case 2: /* Pause Open Short */
            i = DelPul[PAUSRT];
            if(Facts[i][0] < 250)
              Facts[i][0]++;
            break;

          case 3: /* Pause Open Long */
            i = DelPul[PAULNG];
            if(Facts[i][0] < 250)
              Facts[i][0]++;
            break;

          case 4: /* Close Travel+ */
            i = DelPul[DELYJK];
            if(Facts[i][0] < 250)
              Facts[i][0]++;
            break;

          case 5: /* Delay Open Time */
            i = DelPul[DELYOT];
            if(Facts[i][0] < PF[i].max)
              Facts[i][0]++;
            break;

          case 6: /* Delay Pause Time */
            i = DelPul[DELYPT];
            if(Facts[i][0] < PF[i].max)
              Facts[i][0]++;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Chamber Speed 1 */
            i = DelPul[PWMCS1];
            if(Facts[i][0] < PF[i].max)
              Facts[i][0]++;
              break;

          case 1: /* Chamber Speed 2 */
            i = DelPul[PWMCS2];
            if(Facts[i][0] < PF[i].max)
              Facts[i][0]++;
              break;

          case 2: /* Chamber Speed 3 */
            i = DelPul[PWMCS3];
            if(Facts[i][0] < PF[i].max)
              Facts[i][0]++;
              break;  
        }
      }
      changed = 1;
      break;

    case Key_S3: /* cycle */
      if(!ScreenSel)
      {
        if(selection < 6)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 1;
          changed = 2;
        }
      }
      else
      {
        if(selection < 2)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 0;
          changed = 2;
        }
      }
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;

  }

  if(changed)
  {
    if(!ScreenSel)
    {
      if(changed == 2)
      {
        display_f1_text( "1/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0384.l[lang],   TSMAX, 12, 30, FIXED ); /* Open Lid Up      */
        display_f1_text( s0385.l[lang],   TSMAX, 12, 40, FIXED ); /* Open Lid Up+     */
        display_f1_text( s0237.l[lang],   TSMAX, 12, 50, FIXED ); /* Pause Open Short */
        display_f1_text( s0294.l[lang],   TSMAX, 12, 60, FIXED ); /* Pause Open Long  */
        display_f1_text( s0373.l[lang],   TSMAX, 12, 70, FIXED ); /* Close Travel+    */
        display_f1_text( s0374.l[lang],   TSMAX, 12, 80, FIXED ); /* Delay Open Time  */
        display_f1_text( s0375.l[lang],   TSMAX, 12, 90, FIXED ); /* Delay Pause Time */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* Open Lid Up */
      i = Facts[DelPul[DELYEF]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 30, FIXED );

      /* Open Lid Up+ */
      i = Facts[DelPul[DELYFG]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 40, FIXED );

      /* Pause Open Short */
      i = Facts[DelPul[PAUSRT]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 50, FIXED );

      /* Pause Open Long */
      i = Facts[DelPul[PAULNG]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 60, FIXED );

      /* Close Travel+ */
      i = Facts[DelPul[DELYJK]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 70, FIXED );

      /* Delay Open Time */
      i = Facts[DelPul[DELYOT]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 80, FIXED );

      /* Delay Pause Time */
      i = Facts[DelPul[DELYPT]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 90, FIXED );
    }
    else
    {
      if(changed == 2)
      {
        display_f1_text( "2/2", TSMAX, 126, 14, FIXED );

        sprintf ( tstring, s0376.l[lang], 1 );
        display_f1_text( tstring,   TSMAX, 12, 30, FIXED ); /* Chamber Speed 1  */

        sprintf ( tstring, s0376.l[lang], 2 );
        display_f1_text( tstring,   TSMAX, 12, 40, FIXED ); /* Chamber Speed 2  */

        sprintf ( tstring, s0376.l[lang], 3 );
        display_f1_text( tstring,   TSMAX, 12, 50, FIXED ); /* Chamber Speed 3  */

        display_f1_text( s0377.l[lang],   TSMAX, 12, 60, FIXED ); /*                  */
        display_f1_text( s0377.l[lang],   TSMAX, 12, 70, FIXED ); /*                  */
        display_f1_text( s0377.l[lang],   TSMAX, 12, 80, FIXED ); /*                  */
        display_f1_text( s0377.l[lang],   TSMAX, 12, 90, FIXED ); /*                  */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* Chamber Speed 1 */
      i = Facts[DelPul[PWMCS1]][0];
      sprintf ( tstring, "%3u%%", i );
      display_f1_text( tstring,     TS20, 127, 30, FIXED );

      /* Chamber Speed 2 */
      i = Facts[DelPul[PWMCS2]][0];
      sprintf ( tstring, "%3u%%", i );
      display_f1_text( tstring,     TS20, 127, 40, FIXED );

      /* Chamber Speed 3 */
      i = Facts[DelPul[PWMCS3]][0];
      sprintf ( tstring, "%3u%%", i );
      display_f1_text( tstring,     TS20, 127, 50, FIXED );

    }
    ResetSequenceFactors(SEQ_WRAP);
  }



  standard_pointer( 4, 30, 10 );
}



void screen17(void) /* Wrapping */
{
unsigned char i, tstring[32], changed;
static unsigned char ScreenSel;

const unsigned char screen17Factors[2][8] = {
  { DELYKL, DELYLM, DELYLN, PULSEP, DELYPQ, DELYRS, DELYST, 0 },
  { DELYUV, DELWX1, DELWX2, DELYXY, DELYYZ, DELYZA, PLSFR3, 0 }
  };

if( startup != 1 )
  {
    startup = 1;
    
    startup_frame();

    display_f1_text( s0345.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Wrapping */

    write_bitmap( adm, TABMINUS,  3, 106, OR );
    write_bitmap( adm, TABPLUS,   42, 106, OR );
    write_bitmap( adm, TABCYCL, 81, 106, OR );
    write_bitmap( adm, TABESC, 120, 106, OR );

    /*selection = 0;*/
    changed = 2;
    ScreenSel = 0;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();
  
  switch( key )
  	{
    case Key_S1: /* Minus */
    case Key_S1 | KeyDone | KeyRepeat:
      i = DelPul[screen17Factors[ScreenSel][selection]];
      if( Facts[i][0] > PF[i].min )
      {
    	  Facts[i][0]--;
      }
      changed = 1;
      break;

    case Key_S2: /* Plus */
    case Key_S2 | KeyDone | KeyRepeat:
      i = DelPul[screen17Factors[ScreenSel][selection]];
      if( Facts[i][0] < PF[i].max )
      {
    	  Facts[i][0]++;
      }
      changed = 1;
      break;

    case Key_S3: /* cycle */
      if(!ScreenSel)
      {
        if(selection < 6)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 1;
          changed = 2;
        }
      }
      else
      {
        if(selection < 5)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 0;
          changed = 2;
        }
      }
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;
  	}

/*
   const unsigned char screen17Factors[2][7] = {
    { DELYKL, DELYLM, DELYLN, PULSEP, DELYPQ, DELYRS, DELYST, 0 },
    { DELYUV, DELWX1, DELYXY, DELYYZ, DELYZA, PLSFR3, 0, 0 }
    };
*/

  if(changed)
  {
    if(!ScreenSel)
    {
      if(changed == 2)
      {
        display_f1_text( "1/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0239.l[lang],  TSMAX, 12, 30, FIXED ); /* Wrap Start Pause */
        display_f1_text( s0240.l[lang],  TSMAX, 12, 40, FIXED ); /* Ramp Up          */
        display_f1_text( s0241.l[lang],  TSMAX, 12, 50, FIXED ); /* Hold Delay       */
        display_f1_text( s0242.l[lang],  TSMAX, 12, 60, FIXED ); /* Cut Tie Release  */
        display_f1_text( s0242.l[lang],  TSMAX, 12, 70, FIXED ); /* Cut Tie Release  */
        display_f1_text( s0244.l[lang],  TSMAX, 12, 80, FIXED ); /* Delay Ramp Down  */
        display_f1_text( s0245.l[lang],  TSMAX, 12, 90, FIXED ); /* Ramp Down Time   */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* Wrap Start Pause */
      i = Facts[DelPul[DELYKL]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 30, FIXED );

      /* Ramp Up */
      i = Facts[DelPul[DELYLM]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 40, FIXED );

      /* Hold Delay */
      i = Facts[DelPul[DELYLN]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 50, FIXED );

      /* Cut Tie Release */
      i = Facts[DelPul[PULSEP]][0];
      sprintf ( tstring, "%1u", i );
      display_f1_text( tstring,     TS20, 139, 60, FIXED );

      /* Cut Tie Release */
      i = Facts[DelPul[DELYPQ]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 70, FIXED );

      /* Delay Ramp Down */
      i = Facts[DelPul[DELYRS]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 80, FIXED );

      /* Ramp Down Time */
      i = Facts[DelPul[DELYST]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 90, FIXED );
    }
    else
    {
      if( changed == 2 )
      {
        display_f1_text( "2/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0246.l[lang],       TSMAX, 12, 30, FIXED ); /* Wrapped beep     */
        display_f1_text( s0247.l[lang],       TSMAX, 12, 40, FIXED ); /* Tip Wrapped Bale */
        display_f1_text( s0395.l[lang],       TSMAX, 12, 50, FIXED ); /* Tip bale French */
        display_f1_text( s0248.l[lang],       TSMAX, 12, 60, FIXED ); /* Pause Tipped     */
        display_f1_text( s0249.l[lang],       TSMAX, 12, 70, FIXED ); /* Tip Return+      */
        display_f1_text( s0314.l[lang],       TSMAX, 12, 80, FIXED ); /* C&H Open Delay   */
        display_f1_text( "1 Disp Rev Count",  TSMAX, 12, 90, FIXED ); /* 1 Disp Rev Count */
        /*display_f1_text( s0377.l[lang],       TSMAX, 12, 100, FIXED );*/ /*                  */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* Wrapped beep */
      i = Facts[DelPul[DELYUV]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 30, FIXED );

      /* Tip Wrapped Bale */
      i = Facts[DelPul[DELWX1]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 40, FIXED );

      /* Tip bale French */
      i = Facts[DelPul[DELWX2]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 50, FIXED );

      /* Pause Tipped */
      i = Facts[DelPul[DELYXY]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 60, FIXED );

      /* Tip Return+ */
      i = Facts[DelPul[DELYYZ]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 70, FIXED );

      /* C&H Open Delay */
      i = Facts[DelPul[DELYZA]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 80, FIXED );
      
      /* 1 Disp Rev Count */
      i = Facts[DelPul[PLSFR3]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 90, FIXED );
      
      SetOneDispRevs();

      if( Facts[DelPul[LANGUA]][0] == 3 ) /* French language */
  			{
  			Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX2]][0]; /* copy 'Tip bale French' to 'Tip wrapped bale' */
  			}
      else
      	{
      	Facts[DelPul[DELYWX]][0] = Facts[DelPul[DELWX1]][0]; /* copy 'Tip wrapped bale' */
      	}
    }
  }

  standard_pointer( 4, 30, 10 );
}


void screen18(void) /* Top-up/floor */
{
unsigned char i, tstring[32], changed;
static unsigned char ScreenSel;

  if( startup != 1 )
  {
    startup = 1;
    
    startup_frame();

    display_f1_text( s0346.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Top-up/floor */

    write_bitmap( adm, TABMINUS,  3, 106, OR );
    write_bitmap( adm, TABPLUS,   42, 106, OR );
    write_bitmap( adm, TABCYCL, 81, 106, OR );
    write_bitmap( adm, TABESC, 120, 106, OR );

    /*selection = 0;*/
    changed = 2;
    ScreenSel = 0;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1: /* Minus */
    case Key_S1 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* 2nd Topup Wait */
            i = DelPul[DLYT03];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 1: /* 2nd Topup Length */
            i = DelPul[DLYT04];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 2: /* Rotate Debounce */
            i = DelPul[ROTDEB];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 3: /* Ignore Rotate */
            i = DelPul[DELAYL];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 4: /* Ignore E-1 */
            i = DelPul[DELAYE];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 5: /* Control Count */
            i = DelPul[PLSTRT];
            if(Facts[i][0])
              Facts[i][0]--;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Knives Down */
            i = DelPul[DLYU01];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 1: /* Knives Up */
            i = DelPul[DLYU02];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 2: /* Floor Down */
            i = DelPul[DLYU03];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 3: /* Floor Up */
            i = DelPul[DLYU04];
            if(Facts[i][0])
              Facts[i][0]--;
            break;
          case 4: /* Knife Pressure */
        	if( KnifePressure > 0.01 )
        	  {
        	  KnifePressure -= 0.01;
              KnifePressureBar = (unsigned short)(KnifePressure * 50.0);
        	  }
        	break;
        	
          case 5: /* Knife Pressure Warn */
            if( KnifePresWarn > 0.01 )
              {
        	  KnifePresWarn -= 0.01;
        	  KnifePresWarnBar = (unsigned short)(KnifePresWarn * 50.0);        	          	
              }
        	break;
        	
          case 6: /* Knife Down Pressure */
        	if( KnifeDownPres > 0.01 )
        	  {
        	  KnifeDownPres -= 0.01;
        	  KnifeDownPresBar = (unsigned short)(KnifeDownPres * 50.0);
        	  }
        	break;
        	
          case 7: /* Korean pressure */
        	if( KoreanPres > 0.01 )
        	  {
        	  KoreanPres -= 0.01; 
        	  KoreanPresBar = (unsigned short)(KoreanPres * 50.0);
        	  }
        	break;
        }
      }
      changed = 1;
      break;

    case Key_S2: /* Plus */
    case Key_S2 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* 2nd Topup Wait */
            i = DelPul[DLYT03];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;

          case 1: /* 2nd Topup Length */
            i = DelPul[DLYT04];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;

          case 2: /* Rotate Debounce */
            i = DelPul[ROTDEB];
            if(Facts[i][0] < 50)
              Facts[i][0]++;
            break;

          case 3: /* Ignore Rotate */
            i = DelPul[DELAYL];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;

          case 4: /* Ignore E-1 */
            i = DelPul[DELAYE];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;

          case 5: /* Control Count */
            i = DelPul[PLSTRT];
            if(Facts[i][0] < 50)
              Facts[i][0]++;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Knives Down */
            i = DelPul[DLYU01];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;

          case 1: /* Knives Up */
            i = DelPul[DLYU02];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;

          case 2: /* Floor Down */
            i = DelPul[DLYU03];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;

          case 3: /* Floor Up */
            i = DelPul[DLYU04];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;
            
          case 4: /* Knife Pressure */
        	if( KnifePressure < 4.99 )
        	  {
        	  KnifePressure += 0.01;
        	  KnifePressureBar = (unsigned short)(KnifePressure * 50.0); 
        	  }
        	break;
        	
          case 5: /* Knife Pressure Warn */
            if( KnifePresWarn < 4.99 )
              {
        	  KnifePresWarn += 0.01;
        	  KnifePresWarnBar = (unsigned short)(KnifePresWarn * 50.0);
              }
        	break;
        	
          case 6: /* Knife Down Pressure */
        	if( KnifeDownPres < 4.99 )
        	  {
        	  KnifeDownPres += 0.01;        	  
        	  KnifeDownPresBar = (unsigned short)(KnifeDownPres * 50.0);
        	  }
        	break;       
        	
          case 7: /* Korean pressure */
        	if( KoreanPres < 4.99 )
        	  {
        	  KoreanPres += 0.01;        	  
        	  KoreanPresBar = (unsigned short)(KoreanPres * 50.0);
        	  }
        	break;
        }
      }
      changed = 1;
      break;

    case Key_S3: /* cycle */
      if(!ScreenSel)
      {
        if(selection < 5)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 1;
          changed = 2;
        }
      }
      else
      {
        if(selection < 7)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 0;
          changed = 2;
        }
      }
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;
  }


  if( changed )
  {
    if( !ScreenSel )
    {
      if( changed == 2 )
      {
    	draw_box( adm, 12, 25, 155, 100, CLEAR );
    	
        display_f1_text( "1/2", TSMAX, 126, 14, FIXED );                        
        display_f1_text( s0315.l[lang],  TSMAX, 12, 30, FIXED ); /* 2nd Topup Wait   */
        display_f1_text( s0316.l[lang],  TSMAX, 12, 40, FIXED ); /* 2nd Topup Length */
        display_f1_text( s0250.l[lang],  TSMAX, 12, 50, FIXED ); /* Rotate Debounce  */
        display_f1_text( s0251.l[lang],  TSMAX, 12, 60, FIXED ); /* Ignore Rotate    */
        display_f1_text( s0252.l[lang],  TSMAX, 12, 70, FIXED ); /* Ignore E-1       */
        display_f1_text( s0290.l[lang],  TSMAX, 12, 80, FIXED ); /* Control Count    */
     /* display_f1_text( s0377.l[lang],  TSMAX, 12, 90, FIXED );*//*                  */       
        
      }

      /* 2nd Topup Wait */
      i = Facts[DelPul[DLYT03]][0];
      sprintf ( tstring, "%2us", i );
      display_f1_text( tstring,     TS20, 133, 30, FIXED );

      /* 2nd Topup Length */
      i = Facts[DelPul[DLYT04]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 40, FIXED );

      /* Rotate Debounce */
      i = Facts[DelPul[ROTDEB]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 50, FIXED );

      /* Ignore Rotate */
      i = Facts[DelPul[DELAYL]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 60, FIXED );

      /* Ignore E-1 */
      i = Facts[DelPul[DELAYE]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 70, FIXED );

      /* Control Count */
      i = Facts[DelPul[PLSTRT]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 80, FIXED );

    }
    else
    {
      if( changed == 2 )
      {
    	draw_box( adm, 12, 25, 155, 100, CLEAR );
    	
    	display_f1_text( "2/2", TSMAX, 126, 14, FIXED );
        display_f1_text( s0274.l[lang],  TSMAX, 12, 27, FIXED ); /* Knives Down      */
        display_f1_text( s0275.l[lang],  TSMAX, 12, 36, FIXED ); /* Knives Up        */
        display_f1_text( s0276.l[lang],  TSMAX, 12, 45, FIXED ); /* Floor Down       */
        display_f1_text( s0277.l[lang],  TSMAX, 12, 54, FIXED ); /* Floor Up         */
        display_f1_text( s0387.l[lang],  TSMAX, 12, 63, FIXED ); /* Knife Pressure   */
        display_f1_text( s0388.l[lang],  TSMAX, 12, 72, FIXED ); /* Knife Pressure Warn */
        display_f1_text( s0389.l[lang],  TSMAX, 12, 81, FIXED ); /* Knife Down Pressure */
        display_f1_text( s0394.l[lang],  TSMAX, 12, 90, FIXED ); /* Korean Pressure */

        /*draw_box( adm, 123, 27, 155, 100, CLEAR );*/
      }

      /* Knives Down */
      i = Facts[DelPul[DLYU01]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 27, FIXED );

      /* Knives Up */
      i = Facts[DelPul[DLYU02]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 36, FIXED );

      /* Floor Down */
      i = Facts[DelPul[DLYU03]][0]; 
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 45, FIXED );

      /* Floor Up */
      i = Facts[DelPul[DLYU04]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 54, FIXED );
      /* Knife Pressure   */
      sprintf ( tstring, "%4.2fV", KnifePressure );
      display_f1_text( tstring,     TS20, 124, 63, FIXED );
      
      /* Knife Pressure Warn */
      sprintf ( tstring, "%4.2fV", KnifePresWarn );
      display_f1_text( tstring,     TS20, 124, 72, FIXED );
      
      /* Knife Down Pressure */
      sprintf ( tstring, "%4.2fV", KnifeDownPres );
      display_f1_text( tstring,     TS20, 124, 81, FIXED );
      
      /* Knife Down Pressure */
      sprintf ( tstring, "%4.2fV", KoreanPres );
      display_f1_text( tstring,     TS20, 124, 90, FIXED );
    }
  }

  if( !ScreenSel )
	  standard_pointer( 4, 30, 10 );
  else
	  standard_pointer( 4, 27, 9 );
}


void screen19(void) /* Rotation */
{
unsigned char i, tstring[32], changed;
static unsigned char ScreenSel;

  if( startup != 1 )
  {
    startup = 1;
    
    startup_frame();

    display_f1_text( s0347.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Rotation */

    write_bitmap( adm, TABMINUS,  3, 106, OR );
    write_bitmap( adm, TABPLUS,   42, 106, OR );
    write_bitmap( adm, TABCYCL, 81, 106, OR );
    write_bitmap( adm, TABESC, 120, 106, OR );

    /*selection = 0;*/
    changed = 2;
    ScreenSel = 0;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1: /* Minus */
    case Key_S1 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* RPM Debounce */
            i = DelPul[RPMDEB];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 1: /* Motor Debounce */
            i = DelPul[MOTDEB];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 2: /* Motor PPW Rev */
            i = DelPul[MOTPPR];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 3: /* Motor Slip */
            i = DelPul[MOTALM];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 4: /* Slow RPM */
            i = DelPul[RPMSLO];
            if(Facts[i][0] > 5)
              Facts[i][0]--;
            break;

          case 5: /* Index Slow PWM */
            i = DelPul[PWMSL1];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 6: /* Slow Speed PWM */
            i = DelPul[PWMSL2];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Max PWM Value */
            i = DelPul[MAXPWM];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 1: /* Min PWM Value */
            i = DelPul[MINPWM];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 2: /* PWM Step (Max) */
            i = DelPul[ERRPWM];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 3: /* Ramp Pause Count */
            i = DelPul[PLSTAB];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 4: /* Index Slow Count */
            i = DelPul[IDXCNT];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 5: /* Index Slow PWM */
            i = DelPul[IDXPWM];
            if(Facts[i][0])
              Facts[i][0]--;
            break;
            
          case 6: /* Overspeed */
            i = DelPul[IP2FRQ];
            if(Facts[i][0])
              {
              Facts[i][0]--;
              IP02Freq = (float)Facts[DelPul[IP2FRQ]][0]/10.0;
              }
            break;

        }
      }
      changed = 1;
      break;

    case Key_S2: /* Plus */
    case Key_S2 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* RPM Debounce */
            i = DelPul[RPMDEB];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;

          case 1: /* Motor Debounce */
            i = DelPul[MOTDEB];
            if(Facts[i][0] <  50)
              Facts[i][0]++;
            break;

          case 2: /* Motor PPW Rev */
            i = DelPul[MOTPPR];
            if(Facts[i][0] < 240)
              Facts[i][0]++;
            break;

          case 3: /* Motor Slip */
            i = DelPul[MOTALM];
            if(Facts[i][0] < 10)
              Facts[i][0]++;
            break;

          case 4: /* Slow RPM */
            i = DelPul[RPMSLO];
            if(Facts[i][0] < 20)
              Facts[i][0]++;
            break;

          case 5: /* Index Slow PWM */
            i = DelPul[PWMSL1];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;

          case 6: /* Slow Speed PWM */
            i = DelPul[PWMSL2];
            if(Facts[i][0] < 100)
              Facts[i][0]++;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Max PWM Value */
            i = DelPul[MAXPWM];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;

          case 1: /* Min PWM Value */
            i = DelPul[MINPWM];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;

          case 2: /* PWM Step (Max) */
            i = DelPul[ERRPWM];
            if(Facts[i][0] < 250)
              Facts[i][0]++;
            break;

          case 3: /* Ramp Pause Count */
            i = DelPul[PLSTAB];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;

          case 4: /* Index Slow Count */
            i = DelPul[IDXCNT];
            if(Facts[i][0] < 30)
              Facts[i][0]++;
            break;

          case 5: /* Index Slow PWM */
            i = DelPul[IDXPWM];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;
            
          case 6: /* Overspeed */
            i = DelPul[IP2FRQ];
            if(Facts[i][0] < 250)
              {
              Facts[i][0]++;
              IP02Freq = (float)Facts[DelPul[IP2FRQ]][0]/10.0;
              }
            break;            

        }
      }
      changed = 1;
      break;

    case Key_S3: /* cycle */
      if(!ScreenSel)
      {
        if(selection < 6)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 1;
          changed = 2;
        }
      }
      else
      {
        if(selection < 6)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 0;
          changed = 2;
        }
      }
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;
  }


  if(changed)
  {
    if(!ScreenSel)
    {
      if(changed == 2)
      {
        display_f1_text( "1/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0272.l[lang],  TSMAX, 12, 30, FIXED ); /* RPM Debounce     */
        display_f1_text( s0253.l[lang],  TSMAX, 12, 40, FIXED ); /* Motor Debounce   */
        display_f1_text( s0254.l[lang],  TSMAX, 12, 50, FIXED ); /* Motor PPW Rev    */
        display_f1_text( s0255.l[lang],  TSMAX, 12, 60, FIXED ); /* Motor Slip       */
        display_f1_text( s0256.l[lang],  TSMAX, 12, 70, FIXED ); /* Slow RPM         */
        display_f1_text( s0309.l[lang],  TSMAX, 12, 80, FIXED ); /* Index Slow PWM   */
        display_f1_text( s0302.l[lang],  TSMAX, 12, 90, FIXED ); /* Slow Speed PWM   */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* RPM Debounce */
      i = Facts[DelPul[RPMDEB]][0];
      sprintf ( tstring, "%2ums", i );
      display_f1_text( tstring,     TS20, 127, 30, FIXED );

      /* Motor Debounce */
      i = Facts[DelPul[MOTDEB]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 40, FIXED );

      /* Motor PPW Rev */
      i = Facts[DelPul[MOTPPR]][0];
      sprintf ( tstring, "%3u", i );
      display_f1_text( tstring,     TS20, 127, 50, FIXED );

      /* Motor Slip */
      i = Facts[DelPul[MOTALM]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 60, FIXED );

      /* Slow RPM */
      i = Facts[DelPul[RPMSLO]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 70, FIXED );

      /* Index Slow PWM */
      i = Facts[DelPul[PWMSL1]][0];
      sprintf ( tstring, "%3u%%", i );
      display_f1_text( tstring,     TS20, 127, 80, FIXED );

      /* Slow Speed PWM */
      i = Facts[DelPul[PWMSL2]][0];
      sprintf ( tstring, "%3u%%", i );
      display_f1_text( tstring,     TS20, 127, 90, FIXED );

    }
    else
    {
      if(changed == 2)
      {
        display_f1_text( "2/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0258.l[lang],  TSMAX, 12, 30, FIXED ); /* Max PWM Value    */
        display_f1_text( s0259.l[lang],  TSMAX, 12, 40, FIXED ); /* Min PWM Value    */
        display_f1_text( s0260.l[lang],  TSMAX, 12, 50, FIXED ); /* PWM Step (Max)   */
        display_f1_text( s0267.l[lang],  TSMAX, 12, 60, FIXED ); /* Ramp Pause Count */
        display_f1_text( s0308.l[lang],  TSMAX, 12, 70, FIXED ); /* Index Slow Count */
        display_f1_text( s0309.l[lang],  TSMAX, 12, 80, FIXED ); /* Index Slow PWM   */
        display_f1_text( s0390.l[lang],  TSMAX, 12, 90, FIXED ); /* Overspeed        */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* Max PWM Value */
      i = Facts[DelPul[MAXPWM]][0];
      sprintf ( tstring, "%2u%%", i );
      display_f1_text( tstring,     TS20, 133, 30, FIXED );

      /* Min PWM Value */
      i = Facts[DelPul[MINPWM]][0];
      sprintf ( tstring, "%2u%%", i );
      display_f1_text( tstring,     TS20, 133, 40, FIXED );

      /* PWM Step (Max) */
      i = Facts[DelPul[ERRPWM]][0];
      sprintf ( tstring, "%2u.%1u%%", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 50, FIXED );

      /* Ramp Pause Count */
      i = Facts[DelPul[PLSTAB]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 60, FIXED );

      /* Index Slow Count */
      i = Facts[DelPul[IDXCNT]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 70, FIXED );

      /* Index Slow PWM */
      i = Facts[DelPul[IDXPWM]][0];
      sprintf ( tstring, "%2u.%1u%%", i / 10, i % 10);
      display_f1_text( tstring,     TS20, 124, 80, FIXED );
      
      /* Overspeed */
      i = Facts[DelPul[IP2FRQ]][0];
      sprintf ( tstring, "%2u.%1uHz", i / 10, i % 10);
      display_f1_text( tstring,    TS20, 124, 90, FIXED );
      
    }
  }
  
  standard_pointer( 4, 30, 10 );
}



void screen20(void) /* Lube Setup */
{
unsigned char i, tstring[32], changed;
static unsigned char ScreenSel;

  if( startup != 1 )
  {
    startup = 1;
    
    startup_frame();

    display_f1_text( s0348.l[lang], TSMAX, 80, 14, FIXED | CENTER | UNDERLINED ); /* Lube Setup */

    write_bitmap( adm, TABMINUS,  3, 106, OR );
    write_bitmap( adm, TABPLUS,   42, 106, OR );
    write_bitmap( adm, TABCYCL, 81, 106, OR );
    write_bitmap( adm, TABESC, 120, 106, OR );

    /*selection = 0;*/
    changed = 2;
    ScreenSel = 0;
  }
  else
  {
    changed = 0;
  }

  TimeDisplay();

  switch( key )
  {
    case Key_S1: /* Minus */
    case Key_S1 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* Pressure OEF */
            i = DelPul[PDLOEF];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 1: /* Lube Interval */ 
            i = DelPul[LUBECK];
            if(Facts[i][0] > PF[i].min)
            {
              Facts[i][0]--;
              /*LubeCount -= 10;*/
            }
            break;

          case 2: /* Lube Freq. */
            i = DelPul[DLUBEF];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 3: /* Lube Duration */
            i = DelPul[DLUBED];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 4: /* Power Restart */
            i = DelPul[RESTRT];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 5: /* Overshoot Time */
            i = DelPul[DELYVW];
            if(Facts[i][0])
              Facts[i][0]--;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Extra Wrap After */
            i = DelPul[PLSFR1];
            if(Facts[i][0])
              Facts[i][0]--;
            break;

          case 1: /* Extra Wrap Count */
            i = DelPul[PLSFR2];
            if(Facts[i][0] > 1)
              Facts[i][0]--;
            break;

          case 2: /* Film Check Count */
            i = DelPul[FILMPS];
            if(Facts[i][0])
              Facts[i][0]--;
            break;
        }
      }
      changed = 1;
      break;

    case Key_S2: /* Plus */
    case Key_S2 | KeyDone | KeyRepeat:
      if(!ScreenSel)
      {
        switch(selection)
        {
          case 0: /* Pressure OEF */
            i = DelPul[PDLOEF];
            if(Facts[i][0] < 50)
              Facts[i][0]++;
            break;

          case 1: /* Lube Interval */
            i = DelPul[LUBECK];
            if(Facts[i][0] < PF[i].max)
            {
              Facts[i][0]++;
              /*LubeCount += 10;*/
            }
            break;

          case 2: /* Lube Freq. */
            i = DelPul[DLUBEF];
            if(Facts[i][0] < 20)
              Facts[i][0]++;
            break;

          case 3: /* Lube Duration */
            i = DelPul[DLUBED];
            if(Facts[i][0] < 20)
              Facts[i][0]++;
            break;

          case 4: /* Power Restart */
            i = DelPul[RESTRT];
            if(Facts[i][0] < 1)
              Facts[i][0]++;
            break;

          case 5: /* Overshoot Time */
            i = DelPul[DELYVW];
            if(Facts[i][0] < 50)
              Facts[i][0]++;
            break;
        }
      }
      else
      {
        switch(selection)
        {
          case 0: /* Extra Wrap After */
            i = DelPul[PLSFR1];
            if(Facts[i][0] < 10)
              Facts[i][0]++;
            break;

          case 1: /* Extra Wrap Count */
            i = DelPul[PLSFR2];
            if(Facts[i][0] < 10)
              Facts[i][0]++;
            break;

          case 2: /* Film Check Count */
            i = DelPul[FILMPS];
            if(Facts[i][0] < 99)
              Facts[i][0]++;
            break;
        }
      }
      changed = 1;
      break;

    case Key_S3: /* cycle */
      if(!ScreenSel)
      {
        if(selection < 5)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 1;
          changed = 2;
        }
      }
      else
      {
        if(selection < 2)
          selection++;
        else
        {
          selection = 0;
          ScreenSel = 0;
          changed = 2;
        }
      }
      break;

    case Key_S4: /* ESC */
      escape = 1;
      break;
  }


  if(changed)
  {
    if(!ScreenSel)
    {
      if(changed == 2)
      {
        display_f1_text( "1/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0288.l[lang],  TSMAX, 12, 30, FIXED ); /* Pressure OEF     */
        display_f1_text( s0295.l[lang],  TSMAX, 12, 40, FIXED ); /* Lube Interval    */
        display_f1_text( s0322.l[lang],  TSMAX, 12, 50, FIXED ); /* Lube Freq        */
        display_f1_text( s0323.l[lang],  TSMAX, 12, 60, FIXED ); /* Lube Duration    */

        display_f1_text( s0313.l[lang],  TSMAX, 12, 80, FIXED ); /* Overshoot Time   */

        draw_box( adm, 118, 28, 155, 100, CLEAR );
      }

      /* Pressure OEF */
      i = Facts[DelPul[PDLOEF]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 30, FIXED );

      /* Lube Interval */
      i = Facts[DelPul[LUBECK]][0];
      sprintf ( tstring, "%3u", i * 10 );
      display_f1_text( tstring,     TS20, 127, 40, FIXED );

      /* Lube Freq. */
      i = Facts[DelPul[DLUBEF]][0];
      sprintf ( tstring, "%3u", i );
      display_f1_text( tstring,     TS20, 127, 50, FIXED );

      /* Lube Duration */
      i = Facts[DelPul[DLUBED]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 60, FIXED );

      /* Power Restart */
      draw_box( adm, 12, 60, 150, 76, CLEAR );
      strcpy( tstring, s0310.l[lang] ); /* 'Power Restart' */
      strcat( tstring, ": " );
      i = Facts[DelPul[RESTRT]][0] ? 1 : 0;
      strcat( tstring, OnOff[i]->l[lang] ); /* 'Off'/'On' */
      display_f1_text( tstring, TSMAX, 12, 70, FIXED );

      /* Overshoot Time */
      i = Facts[DelPul[DELYVW]][0];
      sprintf ( tstring, "%2u.%1us", i / 10, i % 10 );
      display_f1_text( tstring,     TS20, 124, 80, FIXED );
    }
    else
    {
    	draw_box( adm, 100, 70, 110, 80, CLEAR );
      if(changed == 2)
      {
        display_f1_text( "2/2", TSMAX, 126, 14, FIXED );

        display_f1_text( s0319.l[lang],  TSMAX, 12, 30, FIXED ); /* Extra Wrap After */
        display_f1_text( s0320.l[lang],  TSMAX, 12, 40, FIXED ); /* Extra Wrap Count */
        display_f1_text( s0326.l[lang],  TSMAX, 12, 50, FIXED ); /* Film Check Count */
        display_f1_text( s0377.l[lang],  TSMAX, 12, 60, FIXED ); /*                  */
        display_f1_text( s0377.l[lang],  TSMAX, 12, 70, FIXED ); /*                  */ 
        display_f1_text( s0377.l[lang],  TSMAX, 12, 80, FIXED ); /*                  */

        draw_box( adm, 123, 28, 155, 100, CLEAR );
      }

      /* Extra Wrap After */
      i = Facts[DelPul[PLSFR1]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 30, FIXED );

      /* Extra Wrap Count */
      i = Facts[DelPul[PLSFR2]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 40, FIXED );

      /* Film Check Count */
      i = Facts[DelPul[FILMPS]][0];
      sprintf ( tstring, "%2u", i );
      display_f1_text( tstring,     TS20, 133, 50, FIXED );

    }
  }
  standard_pointer( 4, 30, 10 );
}

