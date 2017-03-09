#include "bytedef.h"
#include <inh83.h>
#include <ioh83003.h>
#include <inh83003.h>
#include <stdio.h>
#include <stdlib.h>


void SetSerial0_Boot( void ) /* serial port 0 using boot values */
{

SCI0_SCR = 0x00; /* clear transmit & receive enable set clk */
SCI0_BRR = 0x0c; /* bit rate, N, n&N give 38400 */
SCI0_SMR = 0x00; /* serial mode, 8 data, 1 stop, no parity, n */

for( command_point=0; command_point<20; command_point++ )
  {
  command[command_point] = 0x00;
  }
command_point = 0;

SCI0_SSR &= ~0x40; /* Clear RDRF */

s0tx_tail = s0tx_head = 0;
s0rx_tail = s0rx_head = 0;
}


void SetSerial0_Normal( void ) /* serial port 0 setup using programmed values */
{
union serial_mode_char smr;

SCI0_SCR = 0x00; /* clear transmit & receive enable set clk */

/* 9600,8,n,1   SCI0_SMR = 0x00, SCI0_BRR = 0x33 */
/* 4800,7,n,2   SCI0_SMR = 0x48, SCI0_BRR = 0x67 */
/* 1200,8,n,1   SCI0_SMR = 0x01, SCI0_BRR = 0x67 */
/* SCI0_SMR = 0x48; */
/* SCI0_BRR = 0x67; */
/* n = br[sio0.sm.baud].baud;  */

smr.mode = 0;
smr.smode.baud_divider = br[sio0.baud].clock_source;
smr.smode.mp_mode = 0;
smr.smode.stop_bits = sio0.stop_bits;
smr.smode.parity = sio0.parity;
smr.smode.data_bits = sio0.data_bits;
smr.smode.async = 0;

SCI0_SMR = smr.mode;
SCI0_BRR = br[sio0.baud].rate_divider;
SCI0_SSR &= ~0x40;           /* Clear RDRF */

s0tx_tail = s0tx_head = 0;
s0rx_tail = s0rx_head = 0;

}


void CheckSerial0( void )
{
unsigned char dat;

BootRun = 20;
txd0 = 1;

while( s0rx_tail != s0rx_head )
  {
  dat = s0rx_buff[s0rx_tail++];
  s0tx_buff[s0tx_head++] = dat;

  switch ( dat )
    {
    case 0x0d:
      if( (command[0] == 'K'-0x20) && (command[1] == 'Q'-0x20) )
        { /* KQ runs boot mode automatically */
        window = boot_loader;
        }
      for( command_point=0; command_point<20; command_point++ )
        {
        command[command_point] = 0x00;
        } 
      command_point = 0;
      break;

    default:
      if( (dat >= 0x20) && (dat <= 0x7a) )
        {
        command[command_point] = dat - 0x20;
        if( command_point < 20 )
          {
          command_point++;
          }
        }
      break;
    }
  }
}


void SetSerial1_Boot( void ) /* serial port 1 using boot values */
{

SCI1_SCR = 0x00; /* clear transmit & receive enable set clk */
SCI1_BRR = 0x0c; /* bit rate, N, n&N give 38400 */
SCI1_SMR = 0x00; /* serial mode, 8 data, 1 stop, no parity, n */

SCI1_SSR &= ~0x40; /* Clear RDRF */

s1tx_tail = s1tx_head = 0;
s1rx_tail = s1rx_head = 0;
}


void OutSerial0( char *dat )
{
unsigned short int i;

i = 0;
while( dat[i] )
  {
 #ifndef WINDOWS
  if( SCI0_SSR & 0x04 ) /* TEND transmit end */
 #endif
    {
    SCI0_TDR = dat[i++];
    SCI0_SSR &= ~0x84; /* Clear TEND & TDRE */
    }
  }
}


void OutSerial1( char *dat )
{
unsigned short int i;

i = 0;
while ( dat[i] )
  {
 #ifndef WINDOWS
  if ( SCI1_SSR & 0x04 )     /* TEND transmit end */
 #endif
    {
    SCI1_TDR = dat[i++];
    SCI1_SSR &= ~0x84;       /* Clear TEND & TDRE */
    }
  }

}

#ifndef WINDOWS

interrupt [SCI_ERI0] void serial_err0_int( void ) /* rx error interrupt */
{

if( SCI0_SSR & (0x20 | 0x10 | 0x08) ) /* overrun/framing/parity error */
  {
  SCI0_SSR &= ~(0x20 | 0x10 | 0x08); /* Clear ORER/FER/PER */
  }

}


interrupt [SCI_RXI0] void serial_rx0_int( void ) /* receive interrupt */
{

if( SCI0_SSR & 0x40 ) /* RDRF */
  {
  SCI0_SSR &= ~0x40; /* clear RDRF */

  s0rx_buff[s0rx_head++] = SCI0_RDR;
  }

}


interrupt [SCI_TEI0] void serial_tx0_int( void ) /* transmit end interrupt */
{

if( s0tx_tail != s0tx_head )
  {
  SCI0_TDR = s0tx_buff[s0tx_tail++];

  if( SCI0_SSR & 0x80 )
    {
    SCI0_SSR &= ~0x80; /* Clear TDRE */
    }
  }
else
  {
  SCI0_SCR &= ~0x04; /* Clear TEIE */
  }

}


interrupt [SCI_ERI1] void serial_err1_int( void ) /* rx error interrupt */
{

if( SCI1_SSR & (0x20 | 0x10 | 0x08) ) /* overrun/framing/parity error */
  {
  SCI1_SSR &= ~(0x20 | 0x10 | 0x08); /* Clear ORER/FER/PER */
  }

}


interrupt [SCI_RXI1] void serial_rx1_int( void ) /* receive interrupt */
{

if( SCI1_SSR & 0x40 ) /* RDRF */
  {
  SCI1_SSR &= ~0x40; /* clear RDRF */

  s1rx_buff[s1rx_head++] = SCI1_RDR;
  }

}


interrupt [SCI_TEI1] void serial_tx1_int( void ) /* transmit end interrupt */
{

if( s1tx_tail != s1tx_head )
  {
  SCI1_TDR = s1tx_buff[s1tx_tail++];

  if( SCI1_SSR & 0x80 )
    {
    SCI1_SSR &= ~0x80; /* Clear TDRE */
    }
  }
else
  {
  SCI1_SCR &= ~0x04; /* Clear TEIE */
  }

}

#endif
