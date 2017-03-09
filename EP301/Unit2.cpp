//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Bytedef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::RadioGroup1Click(TObject *Sender)
{

switch( RadioGroup1->ItemIndex )
  {
  default:
  case 0:
    ProSeries->BackGround = PS_BACKGROUND_WHITE;
    ProSeries->ForeGround = PS_FOREGROUND_WHITE;
    break;

  case 1:
    ProSeries->BackGround = PS_BACKGROUND_GREEN;
    ProSeries->ForeGround = PS_FOREGROUND_GREEN;
    break;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::Button1Click(TObject *Sender)
{

FormAbout->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{


ReleaseCapture();
SendMessage( FormAbout->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0 );

}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::Button2Click(TObject *Sender)
{

if( lang < (MAXLANG - 1) )
  {
  lang++;
  }
else
  {
  lang = 0;
  }
/*StaticText1->Caption = (String)(char *)s8080.l[lang];*/

Facts[DelPul[LANGUA]][0] = lang;

old_time = 0xff;
old_date = 0xff;
startup = 0;

}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::Button3Click(TObject *Sender)
{

if( CropType < 2 )
  {
  CropType++;
  }
else
  {
  CropType = 0;
  }
StaticText2->Caption = (String)(char *)CropTypeString[CropType]->l[0];

old_time = 0xff;
old_date = 0xff;
startup = 0;

}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::FormCreate(TObject *Sender)
{


FormAbout->Top = ProSeries->Top + ProSeries->Height - FormAbout->Height - 40;
FormAbout->Left = ProSeries->Left + ProSeries->Width - FormAbout->Width - 60;

/*StaticText1->Caption = (String)(char *)s8080.l[lang];*/
StaticText2->Caption = (String)(char *)CropTypeString[CropType]->l[0];

}
//---------------------------------------------------------------------------

