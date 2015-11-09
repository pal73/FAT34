object Form1: TForm1
  Left = 192
  Top = 114
  Width = 338
  Height = 142
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button4: TButton
    Left = 60
    Top = 19
    Width = 113
    Height = 25
    Caption = 'Сохранить файл'
    TabOrder = 0
    OnClick = Button4Click
  end
  object SaveDialog1: TSaveDialog
    Options = [ofHideReadOnly, ofCreatePrompt, ofEnableSizing]
    Left = 16
    Top = 16
  end
end
