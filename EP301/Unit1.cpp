//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "bytedef.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProSeries *ProSeries;

static HRGN regS1, regS2, regS3, regS4;
static HRGN regF1, regF2;
static HRGN regL1, regL2, regL3, regL4;
static HRGN regR1, regR2, regR3, regR4;
static HRGN regOFF, regRDS;

extern "C"
{
  void sim_startup();
  void sim_main( int );
}

//---------------------------------------------------------------------------
extern "C" void WriteToScreen( void )
{
char byte, bitcounter;
int bytepointer;
int x,y;

x = 0;
y = 0;

ProSeries->screen->Canvas->Brush->Color = ProSeries->BackGround;
ProSeries->screen->Canvas->FillRect( Rect(0, 0, 320, 256 ));

ProSeries->screen->Canvas->Brush->Color = ProSeries->ForeGround;

for( bytepointer = 0 ; bytepointer < 2560 ; bytepointer++)
  {
  byte = adm[bytepointer];
  for( bitcounter = 0 ; bitcounter < 8 ; bitcounter++ )
    {
    if( byte & 0x80 )
      {
      ProSeries->screen->Canvas->FillRect( Rect( x, y, x + 2, y + 2 ));
      }
    byte <<= 1;
    x = x + 2;
    if( x >= 320 )
      {
      x = 0;
      y += 2;
      }

    }
  }

ProSeries->screen->Visible = true;
}

//------------------------------------------------------------------------

__fastcall TProSeries::TProSeries(TComponent* Owner)
        : TForm(Owner)
{

DoubleBuffered = true;

ProSeries->BackGround = PS_BACKGROUND_WHITE;
ProSeries->ForeGround = PS_FOREGROUND_WHITE;

ProSeries->LedL1->Visible = true;
ProSeries->LedR2->Visible = true;
ProSeries->LedR4->Visible = true;

ProSeries->LedL2->Visible = false;
ProSeries->LedL3->Visible = false;
ProSeries->LedL4->Visible = false;
ProSeries->LedR1->Visible = false;
ProSeries->LedR3->Visible = false;

sim_startup();
}
//---------------------------------------------------------------------------
void __fastcall TProSeries::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
int key;

key = 0;

if( Button == mbLeft )
  {
  if( PtInRegion( regOFF, X, Y ) )
    {
    ProSeries->Close();
    key = -1;
    }
  else if( PtInRegion( regRDS, X, Y ) )
    {
    FormAbout->Visible = true;
    key = -1;
    }
  else if( PtInRegion( regS1, X, Y ) )
    {
    key = Key_S1;
    }
  else if( PtInRegion( regS2, X, Y ) )
    {
    key = Key_S2;
    }
  else if( PtInRegion( regS3, X, Y ) )
    {
    key = Key_S3;
    }
  else if( PtInRegion( regS4, X, Y ) )
    {
    key = Key_S4;
    }
  else if( PtInRegion( regF1, X, Y ) )
    {
    key = Key_F1;
    }
  else if( PtInRegion( regF2, X, Y ) )
    {
    key = Key_F2;
    }
  else if( PtInRegion( regL1, X, Y ) )
    {
    key = Key_L1;
    }
  else if( PtInRegion( regL2, X, Y ) )
    {
    key = Key_L2;
    }
  else if( PtInRegion( regL3, X, Y ) )
    {
    key = Key_L3;
    }
  else if( PtInRegion( regL4, X, Y ) )
    {
    key = Key_L4;
    }
  else if( PtInRegion( regR1, X, Y ) )
    {
    key = Key_R1;
    }
  else if( PtInRegion( regR2, X, Y ) )
    {
    key = Key_R2;
    }
  else if( PtInRegion( regR3, X, Y ) )
    {
    key = Key_R3;
    }
  else if( PtInRegion( regR4, X, Y ) )
    {
    key = Key_R4;
    }

  if( key != -1 )
    {
    ProSeries->Timer1->Enabled = false;
    sim_main( key );
    ProSeries->Timer1->Enabled = true;
    }
  }

if( key == 0 )
  {
  ReleaseCapture();
  SendMessage( ProSeries->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0 );
//  SendMessage( ProSeries->Handle, WM_SYSCOMMAND, 61458, 0 );
//  SendMessage( ProSeries->Handle, WM_SYSCOMMAND, SC_MOVE, 0 );

/* alternative is to intercept message - in visual basic
protected override void WndProc(ref Message m)
{
base.WndProc(ref m);

//int WM_NCHITTEST = 0x84;
if( m.Msg == WM_NCHITTEST )
  {
//  int HTCLIENT = 1;
//  int HTCAPTION = 2;
  if( m.Result.ToInt32() == HTCLIENT )
    {
    m.Result = (IntPtr)HTCAPTION;
    }
  }
}
*/
  }

}
//---------------------------------------------------------------------------
void __fastcall TProSeries::FormCreate(TObject *Sender)
{

Image1->Picture->LoadFromFile( "ExpertPlus.bmp" );

regS1 = CreateEllipticRgn( 123, 393, 166, 436 );
regS2 = CreateEllipticRgn( 199, 393, 242, 436 );
regS3 = CreateEllipticRgn( 275, 393, 318, 436 );
regS4 = CreateEllipticRgn( 350, 393, 394, 436 );

regF1 = CreateEllipticRgn( 123, 482, 166, 525 );
regF2 = CreateEllipticRgn( 123, 547, 166, 591 );

regL1 = CreateEllipticRgn( 275, 482, 318, 525 );
regL2 = CreateEllipticRgn( 275, 547, 318, 591 );
regL3 = CreateEllipticRgn( 275, 613, 318, 656 );
regL4 = CreateEllipticRgn( 275, 679, 318, 722 );

regR1 = CreateEllipticRgn( 350, 482, 394, 525 );
regR2 = CreateEllipticRgn( 350, 547, 394, 591 );
regR3 = CreateEllipticRgn( 350, 613, 394, 656 );
regR4 = CreateEllipticRgn( 350, 679, 394, 722 );

regOFF = CreateEllipticRgn( 105, 636, 183, 714 );
regRDS = CreateRectRgn( 104, 26, 145, 58 );

}
//---------------------------------------------------------------------------
void __fastcall TProSeries::Timer1Timer(TObject *Sender)
{

if( swtim != 0xff )
  {
  swtim++;
  }

if( swrel != 0xff )
  {
  swrel++;
  }

divider2++;
if( divider2 > 5 )
  {
  divider2 = 0;
  loop_seconds++; /* loop_seconds used in clock check */
  demi_secs++;
  demist++;

  flash_bit = flash_bit ? 0 : 1;
  }

sim_main( -1 );

if( ProSeries->LedL1->Visible == true )
  {
  ProSeries->LedL1->Brush->Color = LedData.L.LedL1 ? clRed : clMaroon;
  }

if( ProSeries->LedL2->Visible == true )
  {
  ProSeries->LedL2->Brush->Color = LedData.L.LedL2 ? clRed : clMaroon;
  }

if( ProSeries->LedL3->Visible == true )
  {
  ProSeries->LedL3->Brush->Color = LedData.L.LedL3 ? clRed : clMaroon;
  }

if( ProSeries->LedL4->Visible == true )
  {
  ProSeries->LedL4->Brush->Color = LedData.L.LedL4 ? clRed : clMaroon;
  }

if( ProSeries->LedR1->Visible == true )
  {
  ProSeries->LedR1->Brush->Color = LedData.L.LedR1 ? clRed : clMaroon;
  }

if( ProSeries->LedR2->Visible == true )
  {
  ProSeries->LedR2->Brush->Color = LedData.L.LedR2 ? clRed : clMaroon;
  }

if( ProSeries->LedR3->Visible == true )
  {
  ProSeries->LedR3->Brush->Color = LedData.L.LedR3 ? clRed : clMaroon;
  }

if( ProSeries->LedR4->Visible == true )
  {
  ProSeries->LedR4->Brush->Color = LedData.L.LedR4 ? clRed : clMaroon;
  }

}
//---------------------------------------------------------------------------
void __fastcall TProSeries::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{

if( PtInRegion( regOFF, X, Y ) ||
    PtInRegion( regRDS, X, Y ) ||
    PtInRegion( regS1, X, Y ) ||
    PtInRegion( regS2, X, Y ) ||
    PtInRegion( regS3, X, Y ) ||
    PtInRegion( regS4, X, Y ) ||
    PtInRegion( regF1, X, Y ) ||
    PtInRegion( regF2, X, Y ) ||
    PtInRegion( regL1, X, Y ) ||
    PtInRegion( regL2, X, Y ) ||
    PtInRegion( regL3, X, Y ) ||
    PtInRegion( regL4, X, Y ) ||
    PtInRegion( regR1, X, Y ) ||
    PtInRegion( regR2, X, Y ) ||
    PtInRegion( regR3, X, Y ) ||
    PtInRegion( regR4, X, Y ) )
  {
  Image1->Cursor = crHandPoint;
  }
else
  {
  Image1->Cursor = crDefault;
  }

}
//---------------------------------------------------------------------------



void __fastcall TProSeries::Image1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

// cancel key press when mouse released
sim_main( 0 );

}
//---------------------------------------------------------------------------

