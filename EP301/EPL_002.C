#include <inh83.h>
#include <ioh83003.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bytedef.h"


#ifndef WINDOWS

void command_write( unsigned char data )
{

while( (display_command & 0x03) != 0x03 )
  ;
display_command = data;

}


void write_char( unsigned char data )
{

while( (display_command & 0x03) != 0x03 )
  ;
display_data = data;

}


void write_int( unsigned short int data )
{

while( (display_command & 0x03) != 0x03 )
  ;
display_data = data;         /* low byte */

while( (display_command & 0x03) != 0x03 )
  ;
display_data = (data >> 8);  /* high byte */

}


void setup_display( void )
{
unsigned int i;

WaitTime = 60; /* 240(60 * 4)mS wait */
while( ((display_command & 0x20) != 0x20) && WaitTime )
  ;
if( !WaitTime )
  {
  WDT_WTCNT = 0x5a00; /* unlock, reset count */
  WDT_WTCSR = 0xa57f; /* unlock, wd reset/count on/maximum divider */
  while( 1 )
    ;
  }

write_int( TEXT_HOME_ADDRESS );      /* text home address set */
command_write(TEXT_HOME_ADDRESS_SET);

write_int( GRAPHICS_HOME_ADDRESS );  /* graphics home address set */
command_write(GRAPHICS_HOME_ADDRESS_SET);

write_int( COLUMNS );                /* number of columns */
command_write(TEXT_AREA_SET);

write_int( COLUMNS );                /* number of columns */
command_write(GRAPHICS_AREA_SET);

command_write(INTERNAL_CG_MODE);     /* GRAPHICS OR MODE & INTERNAL CG MODE */

/* 00011 100 00000 000 == 0x1C00 CG ram start address, charater code 0x80h */
/* offset address for external cg (bits 11-15) */
write_int( CHARACTER_GENERATOR_HOME_ADDRESS / 0x800 );
command_write(OFFSET_ADDRESS_SET);

/* blank controller text memory */
write_int( TEXT_HOME_ADDRESS );
command_write(ADDRESS_POINTER_SET);
command_write(AUTO_WRITE_SET);
/* 20 columns x 16 lines */
for (i=0; i < 320; i++ )
  {
  while( (display_command & 0x08) != 0x08 )
    ;
  display_data = 0x00;
  }
auto_reset();

/* blank controller graphics memory */
write_int( GRAPHICS_HOME_ADDRESS );
command_write(ADDRESS_POINTER_SET);
command_write(AUTO_WRITE_SET);
for (i=0; i < GRAPHICS_SIZE; i++ )
  {
  while( (display_command & 0x08) != 0x08 )
    ;
  display_data = 0x00;
  }
auto_reset();

command_write(TEXT_OFF_GRAPHIC_ON);  /*  Graphics Only */

}


void display_screen( void )
{
unsigned int i;
unsigned char *pb;

/* ###test */
/*SCI1_SCR = 0x00;
P9DR |= 0x02;*/

write_int( GRAPHICS_HOME_ADDRESS );
command_write(ADDRESS_POINTER_SET);
command_write(AUTO_WRITE_SET);

pb = &adm[0];
i = GRAPHICS_SIZE;
while( i )
  {
  i--;
  while( (display_command & 0x08) != 0x08 )
    {
    }
  /*display_data = adm[i];*/
  display_data = *pb;
  pb++;
  }
auto_reset();

/* ###test */
/*P9DR &= ~0x02;*/

}

/*
void display_screen_old( void )
{
unsigned int i;

write_int( GRAPHICS_HOME_ADDRESS );
command_write(ADDRESS_POINTER_SET);
command_write(AUTO_WRITE_SET);
for( i = 0; i < GRAPHICS_SIZE; i++ )
  {
  while( (display_command & 0x08) != 0x08 )
    {
    }
  display_data = adm[i];
  }
auto_reset();

}

void display_screen_alt( void )
{
    static char last_screen[GRAPHICS_SIZE];
    static char first_call = 1;
    unsigned char write_active = 0;
    unsigned char data_written = 0;
    unsigned char *pb, *pl;
    unsigned int i, j, end_val;

/ * ###test * /
/ *SCI1_SCR = 0x00;
P9DR |= 0x02;* /
  
    
    if( first_call )
    {
        write_int( GRAPHICS_HOME_ADDRESS );
        command_write( ADDRESS_POINTER_SET );
        command_write( AUTO_WRITE_SET );
        
        pb = &adm[0];
        pl = &last_screen[0];

        for( i = 0; i < GRAPHICS_SIZE; i++ )
        {
            while( (display_command & 0x08) != 0x08 )
            	{
            	}
            / *display_data = adm[i];
            last_screen[i] = adm[i];* /        
            display_data = *pb;
            *pl = *pb;
            pb++;
            pl++;
        }   
        auto_reset();
        first_call = 0;
    }
    else / * check which bytes have been changed, and then write only the changed onces. * /
    {
        pb = &adm[0];
        pl = &last_screen[0];
        
        for( i = 0; i < GRAPHICS_SIZE; i++ )
        {

            data_written = 0;
            / *if( last_screen[i] != adm[i] )* / / * byte has to be updated * /
            if( *pl != *pb ) / * byte has to be updated * /
            {
                if( !write_active ) / * start auto_write sequence * /
                {
                    write_active = 1;
                    write_int( GRAPHICS_HOME_ADDRESS + i );
                    command_write( ADDRESS_POINTER_SET );
                    command_write( AUTO_WRITE_SET );
                    while( (display_command & 0x08) != 0x08 )
                    	{
                    	}
                    / *display_data = adm[i];* /
                    display_data = *pb;
                }
                else
                {
                    while( (display_command & 0x08) != 0x08 )
                    	{
                    	}
                    / *display_data = adm[i];* /
                    display_data = *pb;
                }
                / *last_screen[i] = adm[i];* /        
                *pl = *pb;        
            }
            else
            {
                / * writing 1 byte to the display has 5 overhead bytes
                // therefore there should be at least 6 identical bytes be seen before the auto-write
                // sequence should be ended. * /
                if( write_active )
                {
                    end_val = i + 5;
                    if( end_val > GRAPHICS_SIZE )
                    {
                        end_val = GRAPHICS_SIZE;
                    }

                    for( j = i; j < end_val; j++ )
                    {
                        / * if( last_screen[j] != adm[j] )* / / * byte has to be updated * /
                        if( *pl != *pb ) / * byte has to be updated * /
                        {
                            while( (display_command & 0x08) != 0x08 )
                            	{
                            	}
                            / *display_data = adm[i];* / / * dummy write to increment graphic controller address * /
                            display_data = *pb; / * dummy write to increment graphic controller address * /
                            j = end_val;        / * end loop * /
                            data_written = 1;
                        }
                    }
                    
                    if( !data_written ) / * next 5 byte are the same * /
                    {   / * end auto_write * /
                        auto_reset();
                        write_active = 0;
                    }
                }
            }
            pb++;
            pl++;
        }
        
        if( write_active )
        {
            auto_reset();
        }
    }
    
/ * ###test * /
/ *P9DR &= ~0x02;* /
    
}
*/

void auto_write( unsigned char data )
{

while( (display_command & 0x08) != 0x08 )
  ;
display_data = data;

}


void auto_reset( void )
{

while( (display_command & 0x08) != 0x08 )
  ;
display_command = AUTO_WRITE_RESET;

}
#endif

unsigned char greatest( unsigned char *a, unsigned char *b )
{
unsigned char c;

if ( *a < *b )
  {
  c = *b;
  *b = *a;
  *a = c;
  }

return( *a - *b );
}


void draw_line( unsigned char *buff, unsigned char x1, unsigned char y1,
                unsigned char x2, unsigned char y2, unsigned char method )
{
unsigned char *pt, n, x, y, dx, dy, dir;
unsigned short int offset;

/* mask array used instead of shifts as variable shifts use loops on H8 */
const unsigned char LeftMask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
const unsigned char RightMask[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

if( x1 > 159 )
  {
  x1 = 159;
  }
if( x2 > 159 )
  {
  x2 = 159;
  }
if( y1 > 127 )
  {
  y1 = 127;
  }
if( y2 > 127 )
  {
  y2 = 127;
  }

if( ((x2 >= x1) && (y2 >= y1)) || ((x2 < x1) && (y2 < y1)) )
  {
  dir = 0;
  }
else
  {
  dir = 1;
  }

dx = greatest( &x2, &x1 );
dy = greatest( &y2, &y1 );

if( dir )
  {
  x = x2;
  for( y = 0; y <= dy; y++ )
    {
    offset = (x / 8) + ((y + y1) * COLUMNS);
    /*n = (unsigned char)0x80 >> (x % 8);*/
    n = LeftMask[x % 8];
    while( ((y * dx) >= ((x2 - x) * dy)) && (x >= x1) )
      {
      pt = &buff[offset];
      if( method == CLEAR )
        {
		*pt &= ~n;
		}
      else if(method == INV)
        {
        *pt &= ~n;
        *pt |= ~n;
        }
      else
        {    	   
        *pt |= n;
        }
      if( !(n <<= 1) )
        {
        n = 0x01;
        offset--;
        }
      if( x )
        {
        x--;
        }
      else
        {
        break;
        }
      }
    x++;
    }
  }
else
  {
  x = x1;
  for ( y = 0; y <= dy; y++ )
    {
    offset = (x / 8) + ((y + y1) * COLUMNS);
    /*n = (unsigned char)0x01 << (7 - (x % 8));*/
    n = RightMask[7 - (x % 8)];
    while( ((y * dx) >= ((x - x1) * dy)) && (x <= x2) )
      {
      pt = &buff[offset];
      if( method == CLEAR )
        {
        *pt &= ~n;
        }
      else if( method == INV )
        {
        *pt &= ~n;
        *pt |= ~n;
        }
      else
        {
        *pt |= n;
        }
      if( !(n >>= 1) )
        {
        n = 0x80;
        offset++;
        }
      x++;
      }
    x--;
    }
  }

}


void draw_box( unsigned char *buff, unsigned char x1, unsigned char y1,
               unsigned char x2, unsigned char y2, unsigned char method )
{
/* GREY, CLEAR, FULL, INV or EMPTY(default), */

unsigned char start_byte, end_byte, right_shift, left_shift, dx, bytes;
unsigned char n, b, c, x, y, cc, nn, mask;
unsigned char *pb, *pm;
unsigned short int offset, point;

if( x1 > 159 )
  {
  x1 = 159;
  }
if( x2 > 159 )
  {
  x2 = 159;
  }
if( y1 > 127 )
  {
  y1 = 127;
  }
if( y2 > 127 )
  {
  y2 = 127;
  }

dx = greatest( &x2, &x1 );
greatest( &y2, &y1 );

if( !dx )
  {
  draw_line( buff, x1, y1, x1, y2, method );
  return;
  }
else if( dx == 1)
  {
  draw_line( buff, x1, y1, x1, y2, method );
  draw_line( buff, x2, y1, x2, y2, method );
  return;
  }

start_byte = x1 / 8;
right_shift = x1 % 8;
end_byte = x2 / 8;
left_shift = 7-(x2 % 8);
bytes = end_byte - start_byte;

c = (unsigned char)0xff >> right_shift;
n = (unsigned char)0xff << left_shift;

switch ( method )
  {
  case GREY:
    for( y = y1; y <= y2; y++ )
      {
      mask = (y & 1) ? 0xaa : 0x55;
      cc = c & mask;
      nn = n & mask;

      offset = start_byte + (y * COLUMNS);
      pb = &buff[offset];
      if( !bytes )
        {
        /*buff[offset++] &= ((cc & nn) | ~(c & n));*/
        *pb &= ((cc & nn) | ~(c & n));
        }
      else
        {
        /*buff[offset++] &= (cc | ~c);*/
        *pb &= (cc | ~c);
        pb++;    	  
        for( x = start_byte+1; x < end_byte; x++ )
          {
          /*buff[offset++] &= mask;*/
          *pb &= mask;
          pb++;
          }
        /*buff[offset] &= (nn | ~n);*/
        *pb &= (nn | ~n);
        }
      }
    break;

  case CLEAR:
    for( y = y1; y <= y2; y++ )
      {
      offset = start_byte + (y * COLUMNS);
      pb = &buff[offset];
      if( !bytes )
        {  
        /*buff[offset++] &= ~(c & n);*/
        *pb &= ~(c & n);
        }
      else
        {
        /*buff[offset++] &= ~c;*/
        *pb &= ~c;
        pb++;
        for( x = start_byte+1; x < end_byte; x++ )
          {
          *pb = 0x00;
          pb++;
          }
        /*buff[offset] &= ~n;*/
        *pb &= ~n;
        }
      }
    break;

  case FULL:
    for( y = y1; y <= y2; y++ )
      {
      offset = start_byte + (y * COLUMNS);
      pb = &buff[offset];
      if( !bytes )
        {
        /*buff[offset++] |= (c & n);*/
        *pb |= (c & n);
        }
      else
        {
        /*buff[offset++] |= c;*/
        *pb |= c;
        pb++;
        for( x = start_byte+1; x < end_byte; x++ )
          {
          /*buff[offset++] |= 0xff;*/
          *pb |= 0xff;
          pb++;
          }
        /*buff[offset] |= n;*/
        *pb |= n;
        }
      }
    break;

  case INV:
    for( y = y1; y <= y2; y++ )
      {
      offset = start_byte + (y * COLUMNS);
      pb = &buff[offset];
      if( !bytes )
        {
        /*buff[offset] &= ~(c & n);
		buff[offset] |= ~c ;
		buff[offset++] |= ~n ; no increment needed */
        *pb &= ~(c & n);
  		*pb |= ~c ;
  		*pb |= ~n ;
		}
      else
        {
		/*b = ~buff[offset];*/
  		b = ~(*pb);
		b &= c;
		/*buff[offset] &= ~c;
		buff[offset]|= b;*/
		*pb &= ~c;
		*pb |= b;

        /*offset++;*/
		pb++;
		
        for( x = start_byte+1; x < end_byte; x++ )
          {
          /*buff[offset] = ~buff[offset];
          offset++;*/
          *pb = ~(*pb);
          pb++;          	
          }
        
        /*b = ~buff[offset];*/
        b = ~(*pb);
        b &= n;
		/*buff[offset] &= ~n;
        buff[offset]|= b;*/
		*pb &= ~n;
        *pb |= b;
        }
      }
    break;

  default: /* EMPTY */
    offset = start_byte + (y1 * COLUMNS);
    pb = &buff[offset];
    	
    point =  start_byte + (y2 * COLUMNS);
    pm = &buff[point];
	   
    if( !bytes )
      {
      c = c & n;
      /*buff[offset++] |= c;
      buff[point++] |= c;*/
      *pb |= c;
      *pm |= c;
      }
    else
      {
      /*buff[offset++] |= c;
      buff[point++] |= c;*/
      *pb |= c;
      pb++;
      *pm |= c;
      pm++;

      for( x = start_byte+1; x < end_byte; x++ )
        {
        /*buff[offset++] |= 0xff;
        buff[point++] |= 0xff;*/
        *pb |= 0xff;
        pb++;
        *pm |= 0xff;
        pm++;
        }
      /*buff[offset] |= n;
      buff[point] |= n;*/
      *pb |= n;
      *pm |= n;
      }

    c = (unsigned char)0x80 >> right_shift;
    n = (unsigned char)0x01 << left_shift;

    for( y = y1+1; y < y2; y++ )
      {
      offset = start_byte + (y * COLUMNS);
      buff[offset] |= c;
      point =  end_byte + (y * COLUMNS);
      buff[point] |= n;
      }
    break;
  }

if( method == INV )
	{ /* crop corners */
	draw_line( adm, x1, y1, x1, y1, CLEAR );
	draw_line( adm, x2, y1, x2, y1, CLEAR );
	draw_line( adm, x1, y2, x1, y2, CLEAR );
	draw_line( adm, x2, y2, x2, y2, CLEAR );
	}

}


unsigned char write_bitmap( unsigned char *buff, const unsigned char *map,
                  unsigned char xpos, unsigned char ypos, unsigned char method )
{
/* method AND, OR, INV */
unsigned short int offset;/*, point;*/
unsigned char imL, imR, width, width_minus_one, x, y, n, c, d;
unsigned char *pb, *pm;

if ( (method & INV) == INV )
  {
  imL = (unsigned char)0xff;
  imR = (unsigned char)0xff << (8-(map[0] % 8));
  }
else
  {	
  imL = 0;
  imR = 0;
  }

/* map[0] = bit width of bit map */
/* map[1] = bit height of bit map */

width = (map[0] + 7) / 8;
width_minus_one = width - 1;

/* xpos adjust, right shift bitmap */
/*c = xpos % 8;*/
/*d = 8 - c;*/
n = xpos % 8;
d = 8 - n;
c = 1;
while( n )
  {	
  c *= 2;
  n--;
  }

n = d;
d = 1;
while( n )
  {	
  d *= 2;
  n--;
  }

/*point = 0;
offset = 2;*/
pb = &buffer_memory[0];
pm = &map[2];

for( y=0; y < map[1]; y++ )
  {
  /*buffer_memory[point++] = ((map[offset] ^ imL) >> c);*/
  *pb = ((*pm ^ imL) / c);
  pb++;
  for( x=1; x < width; x++ )
    {
	/* buffer_memory[point] = ((map[offset] ^ imL) << d); */
    *pb = ((*pm ^ imL) * d);
    if( x == width_minus_one )
      {	
      /*buffer_memory[point++] |= ((map[++offset] ^ imR) >> c);*/
      pm++;	
      *pb |= ((*pm ^ imR) / c);
      pb++;
      }
    else
      {	
      /*buffer_memory[point++] |= ((map[++offset] ^ imL) >> c);*/
      pm++;
      *pb |= ((*pm ^ imL) / c);
      pb++;
      }
    }
  /*buffer_memory[point++] = ((map[offset++] ^ imR) << d);*/
  *pb = ((*pm ^ imR) * d);
  pb++;
  pm++;
  }

width++;

x = (xpos / 8);
y = ypos;
/*point = 0;*/
pb = &buffer_memory[0];
for( n=0; n < map[1]; n++ )
  {
  offset = x + ((y + n) * COLUMNS);
  pm = &buff[offset];
  for( c=0; (c < width) && (offset < GRAPHICS_SIZE); c++ )
    {
    if( (method & OR) == OR )
      {	
      /*buff[offset++] |= buffer_memory[point++];*/
      *pm |= *pb;
      }
    else if ( (method & XOR) == XOR )
      {
      /*buff[offset++] ^= buffer_memory[point++];*/
      *pm ^= *pb;
      }
    else  /*  default = AND */
      {
      /*buff[offset++] = buffer_memory[point++];*/
      *pm = *pb;
      }
    pm++;
    pb++;
    }
  }

return( map[0] );

}


