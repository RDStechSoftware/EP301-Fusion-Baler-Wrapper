object ProSeries: TProSeries
  Left = 893
  Top = 169
  AutoSize = True
  BorderIcons = []
  BorderStyle = bsNone
  Caption = 'EP300'
  ClientHeight = 783
  ClientWidth = 517
  Color = clBtnFace
  TransparentColor = True
  TransparentColorValue = clAqua
  DockSite = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 517
    Height = 783
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
    OnMouseUp = Image1MouseUp
  end
  object screen: TImage
    Left = 99
    Top = 88
    Width = 320
    Height = 256
    Visible = False
  end
  object LedL1: TShape
    Left = 257
    Top = 458
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedL2: TShape
    Left = 257
    Top = 531
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedL3: TShape
    Left = 257
    Top = 594
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedL4: TShape
    Left = 257
    Top = 661
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedR1: TShape
    Left = 406
    Top = 458
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedR2: TShape
    Left = 406
    Top = 526
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedR3: TShape
    Left = 406
    Top = 594
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object LedR4: TShape
    Left = 406
    Top = 661
    Width = 11
    Height = 11
    Brush.Color = clAqua
    Pen.Style = psClear
    Shape = stCircle
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 352
    Top = 24
  end
end
