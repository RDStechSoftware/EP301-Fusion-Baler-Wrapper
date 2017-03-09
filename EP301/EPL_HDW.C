/* hardware specific */
#include <ioh83003.h>
#include <inh83.h>
#include <stdio.h>
#include <stdlib.h>
#include "bytedef.h"


unsigned char iic_start( void )
{
unsigned char ret;

P6DDR = 0x80; /* set scl & sda as inputs */

if( !iic_scl || !iic_sda )
  {
  ret = 0xff;
  }
else
  {
  P6DDR = 0x86; /* set scl & sda as outputs */

  iic_scl = 1;               /* set clock bit */
  iic_sda = 1;               /* set data bit */
  iic_sda = 0;               /* clear data bit */
  ret = 0;
  }

return( ret );
}

void iic_clock_start( void ) /* only called if iic running */
{

P6DDR = 0x86; /* set scl & sda as outputs */

iic_scl = 0; /* clear clock bit */
iic_sda = 1; /* set data bit */
iic_scl = 1; /* set clock bit */
iic_sda = 0; /* clear data bit */

}


unsigned char iic_transmit( unsigned char data )
{
unsigned char c;

P6DDR = 0x86; /* set scl & sda as outputs */

for( c = 0; c < 8; c++ )
  {
  iic_scl = 0; /* clear clock bit */
  if( data & 0x80 )
    {
    iic_sda = 1; /* set data bit */
    }
  else
    {
    iic_sda = 0; /* clear data bit */
    }
  data <<= 1;
  iic_scl = 1; /* set clock bit */
  }

iic_scl = 0; /* clear clock bit */

P6DDR = 0x82; /* set scl as output, scl = bit1 */
              /* set sda as input,  sda = bit2 */

iic_scl = 1;  /* set clock bit */
if( iic_sda ) /* read ack */
  {
  c = 0xff;
  }
else
  {
  c = 0x00;
  }
return( c );
}


unsigned char iic_receive( unsigned char ack )
{
unsigned char ret, c;

iic_scl = 0; /* clear clock bit */
P6DDR = 0x82; /* set scl as output, scl = bit0 */
              /* set sda as input,  sda = bit1 */
for( c = 0; c < 8; c++ )
  {
  iic_scl = 1; /* set clock bit */
  ret <<= 1;

  if( iic_sda )
    {
    ret |= 0x01;
    }
  else
    {
    ret &= 0xfe;
    }
  iic_scl = 0; /* clear clock bit */
  }

if( ack )
  {
  iic_sda = 0; /* set ack bit */
  }
else
  {
  iic_sda = 1;
  }
P6DDR = 0x86; /* set scl & sda as outputs */

iic_scl = 1; /* set clock bit */

return( ret );
}


void iic_stop( void ) /* only called if iic running */
{

P6DDR = 0x86; /* set scl & sda as outputs */

iic_scl = 0; /* clear clock bit */
iic_sda = 0; /* clear data bit */
iic_scl = 1; /* set clock bit */
iic_sda = 1; /* set data bit */

P6DDR = 0x80; /* set scl & sda as inputs */

}


void WakeUpDtoA( void )
{

iic_start();
iic_transmit( IIC_DTOA_ADDRESS );
iic_transmit( 0xf0 ); /* extended command */
iic_transmit( 0x0c ); /* power up A & B */
iic_stop();

}


void SetContrast( void )
{
unsigned char c;

iic_start();
iic_transmit( IIC_DTOA_ADDRESS );
c = Contrast[DayNight];
iic_transmit( IIC_DTOA0 | (c / 0x10) );
iic_transmit( (c % 0x10) * 0x10 );
iic_stop();

}


void SetBrightness( void )
{
unsigned char c;

iic_start();
iic_transmit( IIC_DTOA_ADDRESS );
c = Brightness[DayNight];
iic_transmit( IIC_DTOA1 | (c / 0x10) );
iic_transmit( (c % 0x10) * 0x10 );
iic_stop();

}


char btobcd ( char data )
{

return ( ((data / 10) * 16) + (data % 10) );
}


char bcdtob ( char data )
{

return ( ((data / 16) * 10) + (data % 16) );
}


void get_time( void )
{
#ifdef WINDOWS
#include <stdlib.h>
#include <time.h>

struct tm *time_now;
time_t secs_now;

tzset();
time(&secs_now);
time_now = localtime(&secs_now);

seconds = time_now->tm_sec;
minutes = time_now->tm_min;
hours = time_now->tm_hour;
_day = time_now->tm_wday;
_date = time_now->tm_mday;
month = time_now->tm_mon+1;
year = time_now->tm_year + 1900;
century = 0;

#else
unsigned char c;

iic_start();
iic_transmit( IIC_CLOCK_ADDRESS );
iic_transmit( IIC_CLOCK_SECONDS_ADDRESS );
iic_clock_start();
iic_transmit( (IIC_CLOCK_ADDRESS | IIC_READ) );
seconds = bcdtob( iic_receive( IIC_ACK ) );
minutes = bcdtob( iic_receive( IIC_ACK ) );
c = iic_receive( IIC_ACK );
hours = bcdtob( c & 0x3f );
century = (c & 0x40) ? 1 : 0;
_day = bcdtob( iic_receive( IIC_ACK ) );
_date = bcdtob( iic_receive( IIC_ACK ) );
month = bcdtob( iic_receive( IIC_ACK ) );
c = bcdtob( iic_receive( IIC_NOACK ) );
iic_stop();

year = 2000 + c;

#endif
}


void set_time( void )
{
unsigned char c;

iic_start();
iic_transmit( IIC_CLOCK_ADDRESS );
iic_transmit( IIC_CLOCK_SECONDS_ADDRESS );
iic_transmit( btobcd(seconds) );
iic_transmit( btobcd(minutes) );
c = (btobcd(hours) & 0x3f) | (century ? 0xc0 : 0x80);
iic_transmit( c );
iic_transmit( btobcd(_day) );
iic_transmit( btobcd(_date) );
iic_transmit( btobcd(month) );
c = btobcd( year - 2000 );
iic_transmit( c );
iic_stop();

}


void KeyCheck( unsigned char mode )
{
static unsigned char old_key;

if( mode )
  {
  Ip.L = 0; /* reset all inputs */
  }
Ip.I.IP01 = IP01;
Ip.I.IP02 = IP02;
Ip.I.IP03 = IP03;
Ip.I.IP04 = IP04;
Ip.C[2] = latch1_in;
Ip.C[3] = ~P7DR; /* Analogue Input status */

TestIp = Ip;

key = 0;
if( !BootRun && !SIOdata )
  {
  if( !txd0 )
    {
    if( !rxd0 )
      {
      key = Key_BR;
      }

    switch( old_key )
      {
      case Key_TL:
      case Key_TR:
      case Key_BL:
        key = old_key;
        break;
      }
    }
  else if( txd0 )
    {
    if( Ip.I.IP12 )
      {
      key = Key_TR;
      }
    /*else if( Ip.I.IP07 )
      {
      key = Key_TL;
      }*/
    else if( Ip.I.IP11 )
      {
      key = Key_BL;
      }

    switch( old_key )
      {
      case Key_BR:
        key = old_key;
        break;
      }
    }
  }

P4DR = 0xe0; /* KeyD1 low, check row 1, P4=11100000 */
if( !KeyS1 )
  {
  key = Key_S1;
  }
else if( !KeyS2 )
  {
  key = Key_L1;
  }
else if( !KeyS3 )
  {
  key = Key_L3;
  }
else if( !KeyS4 )
  {
  key = Key_F1;
  }

P4DR = 0xd0; /* KeyD2 low / KeyD1 high, check row 2, P4=11010000 */
if( !KeyS1 )
  {
  key = Key_S2;
  }
else if( !KeyS2 )
  {
  key = Key_R1;
  }
else if( !KeyS3 )
  {
  key = Key_R3;
  }
else if( !KeyS4 )
  {
  key = Key_F3;
  }

P4DR = 0xb0; /* KeyD3 low / KeyD2 high, check row 3, P4=10110000 */
if( !KeyS1 )
  {
  key = Key_S3;
  }
else if( !KeyS2 )
  {
  key = Key_L2;
  }
else if( !KeyS3 )
  {
  key = Key_L4;
  }
else if( !KeyS4 )
  {
  key = Key_F4;
  }

P4DR = 0x70; /* KeyD4 low / KeyD3 high, check row 4, P4=01110000 */
if( !KeyS1 )
  {
  key = Key_S4;
  }
else if( !KeyS2 )
  {
  key = Key_R2;
  }
else if( !KeyS3 )
  {
  key = Key_R4;
  }
else if( !KeyS4 )
  {
  key = Key_F2;
  }
KeyD4 = 1;

if( !mode )
  {
  return;
  }

if( old_key != key )
  {
  old_key = key;

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

}

#if 0
void KeyCheck ( void )
{
static unsigned char old_key;

old_key = key & ~KeyMask;
key = 0;

Ip.L = 0; /* reset all inputs */
Ip.I.IP01 = IP01;
Ip.I.IP02 = IP02;
Ip.I.IP03 = IP03;
Ip.I.IP04 = IP04;
Ip.C[2] = latch1_in;
Ip.C[3] = ~P7DR; /* Analogue Input status */

TestIp = Ip;

if( !BootRun && !SIOdata )
  {
  if( !txd0 )
    {
    if( !rxd0 )
      {
      key = Key_BR;
      }

    switch( old_key )
      {
      case Key_TL:
      case Key_TR:
      case Key_BL:
        key = old_key;
        break;
      }
    }
  else if( txd0 )
    {
    if( Ip.I.IP12 )
      {
      key = Key_TR;
      }
    else if( Ip.I.IP07 )
      {
      key = Key_TL;
      }
    else if( Ip.I.IP11 )
      {
      key = Key_BL;
      }

    switch( old_key )
      {
      case Key_BR:
        key = old_key;
        break;
      }
    }
  }

P4DR = 0xe0; /* KeyD1 low, check row 1, P4=11100000 */
if( !KeyS1 )
  {
  key = Key_S1;
  }
else if( !KeyS2 )
  {
  key = Key_L1;
  }
else if( !KeyS3 )
  {
  key = Key_L3;
  }
else if( !KeyS4 )
  {
  key = Key_F1;
  }

P4DR = 0xd0; /* KeyD2 low / KeyD1 high, check row 2, P4=11010000 */
if( !KeyS1 )
  {
  key = Key_S2;
  }
else if( !KeyS2 )
  {
  key = Key_R1;
  }
else if( !KeyS3 )
  {
  key = Key_R3;
  }
else if( !KeyS4 )
  {
  key = Key_F3;
  }

P4DR = 0xb0; /* KeyD3 low / KeyD2 high, check row 3, P4=10110000 */
if( !KeyS1 )
  {
  key = Key_S3;
  }
else if( !KeyS2 )
  {
  key = Key_L2;
  }
else if( !KeyS3 )
  {
  key = Key_L4;
  }
else if( !KeyS4 )
  {
  key = Key_F4;
  }

P4DR = 0x70; /* KeyD4 low / KeyD3 high, check row 4, P4=01110000 */
if( !KeyS1 )
  {
  key = Key_S4;
  }
else if( !KeyS2 )
  {
  key = Key_R2;
  }
else if( !KeyS3 )
  {
  key = Key_R4;
  }
else if( !KeyS4 )
  {
  key = Key_F2;
  }
KeyD4 = 1;

if( old_key != key )
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

}
#endif

void LedDisplay( unsigned short int dat )
{
#ifndef WINDOSW
unsigned char c;

LLatch = 0; /* enable latch */

for( c = 0; c < 12; c++ )
  {
  LClk = 0; /* LED clock */
  LData = (dat & 0x0800) ? 0 : 1; /* LED data */
  dat <<= 1;
  LClk = 1; /* Clock data in */
  }

LLatch = 1; /* latch data */
#endif

}


void SetVolume( unsigned char vol )
{

Vol3 = (vol & 0x01) ? 1 : 0;
Vol2 = (vol & 0x02) ? 1 : 0;
Vol1 = (vol & 0x04) ? 1 : 0;
Vol0 = (vol & 0x08) ? 1 : 0;
}

