//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------

// clLime;
// RGB( 114, 167, 20 );
#define PS_BACKGROUND_GREEN ((TColor)RGB( 114, 167,  20 )) // Winstar Yellow Green

// clNavy;
// RGB( 36, 55, 25 );
#define PS_FOREGROUND_GREEN ((TColor)RGB(  36,  55,  25 )) // Winstar Yellow Green

// clWhite;
// RGB( 185, 185, 195 );
// RGB( 155, 157, 156 ); // G-Wiz
#define PS_BACKGROUND_WHITE ((TColor)RGB( 221, 214, 225 )) // GTK-Psi

// clBlack;
// RGB( 45, 45, 125 );
// RGB( 56, 70, 115 ); // G-Wiz
#define PS_FOREGROUND_WHITE ((TColor)RGB(  91,  58,  75 )) // GTK-Psi


class TProSeries : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        TImage *screen;
        TShape *LedL1;
        TShape *LedL2;
        TShape *LedL3;
        TShape *LedL4;
        TShape *LedR1;
        TShape *LedR2;
        TShape *LedR3;
        TShape *LedR4;
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        TColor ForeGround, BackGround;

        __fastcall TProSeries(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProSeries *ProSeries;
//---------------------------------------------------------------------------
#endif
