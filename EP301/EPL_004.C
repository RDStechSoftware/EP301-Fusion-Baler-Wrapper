#include <inh83.h>
#include <ioh83003.h>
#include <string.h>
#include <stdio.h>
#include "bytedef.h"


unsigned char sercr( void )
{
unsigned short int time_out;
#ifndef WINDOWS
time_out = 0;                /* loop takes approx 7.5uS, this gives 0.49S */
while ( !(SCI0_SSR & 0x40) )         /* RDRF */
  {
  if ( SCI0_SSR & 0x38 )             /* reset serial errors */
    SCI0_SSR &= ~ 0x38;
  time_out--;
  if ( !time_out )
    break;
  }
SCI0_SSR &= ~0x40;                   /* clear RDRF */
#endif
return ( SCI0_RDR );
}


void serct( unsigned char dat )
{
#ifndef WINDOWS
while ( !(SCI0_SSR & 0x80) )         /* TDRE */
  ;
SCI0_TDR = ( dat );
SCI0_SSR &= ~0x80;                   /* Clear TDRE */
#endif
}


unsigned char send_data( unsigned char dat )
{
#ifndef WINDOWS
serct( hex[dat / 0x10] );
serct( hex[dat % 0x10] );
#endif
return( dat );
}


unsigned char receive_data( unsigned char *sum )
{
unsigned char dat, ret;
#ifndef WINDOWS
dat = sercr();
if ( dat & 0x40 )                    /* A to F */
  dat += 9;
ret = (dat & 0x0f) * 0x10;

dat = sercr();
if ( dat & 0x40 )                    /* A to F */
  dat += 9;
ret += (dat & 0x0f);
*sum += ret;
#endif
return ( ret );
}


void send_text( unsigned char *cp, unsigned short int len )
{
unsigned char pause;
#ifndef WINDOWS
pause = 0;
while ( len )
  {
  if ( SCI0_SSR & 0x40 )             /* RDRF */
    {
    if ( SCI0_RDR == XOFF )          /* XOFF then set pause */
      pause = 1;
    SCI0_SSR &= ~0x40;               /* clear RDRF */
    }

  while ( pause )                    /* XOFF, then pause */
    {
    if ( SCI0_SSR & 0x40 )           /* RDRF */
      {
      if ( SCI0_RDR == XON )         /* until XON */
        pause = 0;
      SCI0_SSR &= ~0x40;             /* clear RDRF */
      }
    }

  serct( *cp++ );                    /* data */
  len--;
  }
#endif
}


void upload ( unsigned char *cp, unsigned short int len )
{
unsigned char pause, dat, sum, *cp_saved;
unsigned short len_saved;
unsigned long int adl, adl_saved;
#ifndef WINDOWS
adl = 0;
pause = 0;

if ( SCI0_SSR & 0x40 )               /* clear RDRF */
  SCI0_SSR &= ~0x40;

while ( len )
  {
  if ( SCI0_SSR & 0x40 )             /* RDRF */
    {
    if ( SCI0_RDR == XOFF )          /* XOFF then set pause */
      pause = 1;
    SCI0_SSR &= ~0x40;               /* clear RDRF */
    }

  while ( pause )                    /* XOFF, then pause */
    {
    if ( SCI0_SSR & 0x40 )           /* RDRF */
      {
      if ( SCI0_RDR == XON )         /* until XON */
        pause = 0;
      SCI0_SSR &= ~0x40;             /* clear RDRF */
      }
    }

  if ( !(adl & 0x001f) )
    {
    cp_saved = cp;
    len_saved = len;
    adl_saved = adl;

    serct( ':' );                    /* record start   */
    if ( len / 0x20 )
      dat = 0x20;
    else
      dat = len;
    sum = send_data( dat );          /* record length  */
    sum += send_data( adl / 0x0100 );/* high address   */
    sum += send_data( adl % 0x0100 );/* low address    */
    sum += send_data( 0x00 );        /* record type 00 */
    }

  len--;

  sum += send_data( *cp++ );         /* data           */

  if ( !(++adl & 0x001f) || !len )
    {
    send_data( -sum );               /* checksum       */
    serct( 0x0d );
    serct( 0x0a );

    /* if checksum failed then send line again */
    if ( sercr() != '+' )            /* + is ok, ? is fail */
      {
      cp = cp_saved;
      len = len_saved;
      adl = adl_saved;
      }
    }

  }

dat = 0;
while ( !dat )
  {
  serct( ':' );                      /* record start  */
  sum = send_data( 0x00 );           /* record length */
  sum += send_data( 0x00 );          /* high address  */
  sum += send_data( 0x00 );          /* low address   */
  sum += send_data( 0x01 );          /* record type   */
  send_data( -sum );                 /* checksum      */
  serct( 0x0d );
  serct( 0x0a );

    /* if checksum failed then send line again */
  if ( sercr() == '+' )              /* + is ok, ? is fail */
    dat = 1;
  }
#endif
}


void download ( unsigned long int offset )
{
unsigned char *cp;
unsigned char bloop, sum;
unsigned short int i, n;
unsigned long int adh, adl;
#ifndef WINDOWS
bloop = 1;
adh = 0UL;

while ( bloop )
  {
  if ( SCI0_SSR & 0x38 )             /* reset serial errors after a pause */
    {
    for (i=0; i < 8000; i++ )
      ;
    SCI0_SSR &= ~ 0x38;
    }

  while ( sercr() != ':' )           /* wait for start of line */
    ;
  sum = 0;                           /* reset checksum  */
  i = receive_data( &sum );          /* number of bytes */

  adl = receive_data( &sum );        /* load address */
  adl *= 0x100;
  adl |= receive_data( &sum );

  n = receive_data( &sum );          /* record type */

  switch ( n )
    {
    case 4:                          /* Extended Linear Record */
      adh = receive_data( &sum );    /* top 16 bits of 32 bit address */
      adh *= 0x100;
      adh |= receive_data( &sum );
      adh *= 0x10000;
      break;

    case 2:                          /* Extended Address Record */
      adh = receive_data( &sum );    /* top 16 bits of 32 bit address */
      adh *= 0x100;
      adh |= receive_data( &sum );
      adh *= 0x10;
      break;

    case 1:                          /* end of file */
      bloop = 0;
      break;

    case 0:                          /* Data Record */
      cp = (unsigned char *)(adh + adl + offset);
      while ( i-- )
        *cp++ = receive_data( &sum );
      break;
    }

  receive_data( &sum );

  if ( sum )                 /* checksum error */
    serct( '?' );
  else
    serct( '+' );
  }

sercr();     /* read cr */
sercr();     /* read lf */
#endif
}


void boot_loader( void )
{
unsigned char write, command_point, command[20];
unsigned char dat;
unsigned short int text_point = (TEXT_HOME_ADDRESS + 20);
unsigned short int i;
unsigned long int l;

const char RemOte[] = "Remote Data Transfer";

void (*routine)(void);

#ifndef WINDOWS
set_interrupt_mask( 3 );     /* all INTS except NMI off */

portA_dat = 0x00;
portB_dat = 0x00;
latch1_out = 0x00; /* set ouputs  4-13 low */
latch2_out = 0x00; /* set ouputs 13-20 low */

while( (display_command & 0x20) != 0x20 )
  ;
write_int( TEXT_HOME_ADDRESS );      /* text home address set */
command_write(TEXT_HOME_ADDRESS_SET);

write_int( GRAPHICS_HOME_ADDRESS );  /* graphics home address set */
command_write(GRAPHICS_HOME_ADDRESS_SET);

write_int( COLUMNS );                /* number of columns */
command_write(TEXT_AREA_SET);

write_int( COLUMNS );                /* number of columns */
command_write(GRAPHICS_AREA_SET);

command_write(DISPLAY_OFF);          /* Text off, Graphics off */
command_write(TEXT_ATTRIBUTE_MODE);  /* Attribute mode & INTERNAL CG MODE & OR */

/* 00011 100 00000 000 == 0x1C00 CG ram start address, charater code 0x80h */
/* offset address for external cg (bits 11-15) */
write_int( CHARACTER_GENERATOR_HOME_ADDRESS / 0x800 );
command_write(OFFSET_ADDRESS_SET);

/* blank controller text memory */
write_int( TEXT_HOME_ADDRESS );
command_write(ADDRESS_POINTER_SET);
command_write(AUTO_WRITE_SET);

i = 0;
while ( (dat = RemOte[i++]) )  /* 'Remote Data Transfer' */
  {
  while( (display_command & 0x08) != 0x08 )
    ;
  display_data = dat - 0x20;
  }

for (  ; i < 320; i++ )
  {
  while( (display_command & 0x08) != 0x08 )
    ;
  display_data = 0x00;
  }
while( (display_command & 0x08) != 0x08 )
  ;
display_command = AUTO_WRITE_RESET;

/* blank controller attribute (graphics) memory */
write_int( GRAPHICS_HOME_ADDRESS );
command_write(ADDRESS_POINTER_SET);
command_write(AUTO_WRITE_SET);
for (i=0; i < 320; i++ )
  {
  while( (display_command & 0x08) != 0x08 )
    ;
  display_data = 0x00;
  }
display_command = AUTO_WRITE_RESET;

command_write( TEXT_ON_GRAPHIC_ON ); /* Text + Attributes Only */

reset_code = 0xffffffff;

routine = (void *)0x0021BFFE;      /* boot program will be loaded here */

SCI0_SCR = 0x00;             /* clear transmit & receive enable set clk */
/*SCI0_BRR = 0x33;      */   /* bit rate, N, n&N give 9600  */
SCI0_BRR = 0x0c;             /* bit rate, N, n&N give 38400 */
SCI0_SMR = 0x00;             /* serial mode, 8 data, 1 stop, no parity, n */

for( i=0; i<20; i++ )
  {
  command[i] = 0x00;
  }

SCI0_SSR &= ~0x40;           /* Clear RDRF */
SCI0_SCR = 0x30;             /* transmit/receive enable */

serct( ':' );                /* send ready char */

write = 0;
command_point = 0;

while( window == boot_loader )
  {
  if ( SCI0_SSR & 0x38 )     /* reset serial errors after a pause */
    {
    for (i=0; i < 8000; i++ )
      ;
    SCI0_SSR &= ~ 0x38;
    }

  if ( SCI0_SSR & 0x40 )     /* RDRF receive data register full */
    {
    dat = SCI0_RDR;
    SCI0_SSR &= ~0x40;       /* RDRF */

    if ( SCI0_SSR & 0x80 )   /* TX empty (TDRE set) */
      {
      SCI0_TDR = dat;
      SCI0_SSR &= ~0x80;     /* Clear TDRE */
      }

    switch ( dat )
      {
      case  8:
        if ( command_point )
          {
          command_point--;
          command[command_point] = 0x00;
          write = 1;
          }
        break;

      case 0x0d:
        /* wait for last char to be sent, TEND set when last bit sent */
        for ( i=0; (i < 8000) && !(SCI0_SSR & 0x04); i++ )
          ;
        for (i=0; i < 8000; i++ )
          ;
        if ( (command[0] == 'K'-0x20) && (command[1] == 'Q'-0x20) )
          { /* KQ just echos command */
          }
        else if ( (command[0] == 'S'-0x20) && (command[1] == 'E'-0x20) )
          { /* SE send programmable factors */
          l = (unsigned long int)&CheckString2 + 20 - (unsigned long int)&reset_code;
          upload( (unsigned char *)&reset_code, l );
          }
        else if ( (command[0] == 'R'-0x20) && (command[1] == 'E'-0x20) )
          { /* RE receive programmable factors */
          download ( (unsigned long int)&reset_code );
          }
        else if ( (command[0] == 'P'-0x20) && (command[1] == 'D'-0x20) )
          { /* PD program download (code contains load address) */
          download ( 0x00L );
          } 
        else if ( (command[0] == 'R'-0x20) && (command[1] == 'U'-0x20) )
          { /* RU runs program pointed to by routine (loaded by PD) */
          if( *(unsigned char *)routine )
            {
            routine();
            }
          }
        else if ( (command[0] == 'I'-0x20) && (command[1] == 'D'-0x20) )
          { /* ID sends software type/issue */
          l = sprintf( command, "EP%03u-%03u\r\n", SOFTWARE, ISSUE );
          send_text( &command[0], l );
          }
        else if ( (command[0] == 'E'-0x20) && (command[1] == 'X'-0x20) )
          { /* EX restarts instrument - setup watchdog timer & wait */
          WDT_WTCNT = 0x5a00; /* unlock, reset count */
          WDT_WTCSR = 0xa57f; /* unlock, wd reset/count on/maximum divider */
          while( 1 )
            {
            /* wait for watchdog reset */
            }
          }

        text_point += 20;
        if ( text_point >= (TEXT_HOME_ADDRESS+(16*20)) )
          text_point = TEXT_HOME_ADDRESS + 20;
        command_point = 0;
        for ( i=0; i<20; i++ )
          command[i] = 0x00;
        write = 1;
        break;

      default:
        if ( (dat >= 0x20) && (dat <= 0x7a) )
          {
          command[command_point] = dat - 0x20;
          if ( command_point < 20 )
            command_point++;
          write = 1;
          }
        break;
      }

    if ( write )
      {
      write = 0;

      write_int( text_point );
      command_write ( ADDRESS_POINTER_SET );
      command_write ( AUTO_WRITE_SET );
      for ( i=0; i<20; i++ )
        {
        while( (display_command & 0x08) != 0x08 )
          ;
        display_data = command[i];
        }
      while( (display_command & 0x08) != 0x08 )
        ;
      display_command = AUTO_WRITE_RESET;
      }

    }
  }
#endif
}


