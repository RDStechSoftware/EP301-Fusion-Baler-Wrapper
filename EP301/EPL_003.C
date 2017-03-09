#include <ioh83003.h>
#include <inh83.h>
#include <stdio.h>
#include <stdlib.h>
#include "bytedef.h"


char cf2 ( char c )
{

if ( (c >= '0') && (c <= '9') )
  return ( c - '0' );
else if ( c == '.' )
  return ( 10 );
else if ( c == ':' )
  return ( 11 );
else if ( c == ' ' )
  return ( 12 );
else if ( c == '-' )
  return ( 13 );
else
  return ( 14 );
}


char cf3 ( char c )
{

if ( (c >= '0') && (c <= '9') )
  return ( c - '0' );
else if ( c == '.' )
  return ( 10 );
else if ( c == ':' )
  return ( 11 );
else if ( c == ' ' )
  return ( 12 );
else if ( c == '-' )
  return ( 13 );
else
  return ( 14 );
}


