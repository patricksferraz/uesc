object Drill: TDrill
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Drill-up / Drill-down'
  ClientHeight = 508
  ClientWidth = 907
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 3
    Top = 18
    Width = 165
    Height = 13
    Caption = 'Dimens'#245'es/Fato (clique na Tabela)'
  end
  object Label5: TLabel
    Left = 6
    Top = 236
    Width = 146
    Height = 13
    Caption = 'Arraste atributos para SELECT'
  end
  object Label1: TLabel
    Left = 176
    Top = 18
    Width = 51
    Height = 13
    Caption = 'SELECT ...'
  end
  object Label2: TLabel
    Left = 174
    Top = 131
    Width = 44
    Height = 13
    Caption = 'FROM ...'
  end
  object Label3: TLabel
    Left = 170
    Top = 238
    Width = 51
    Height = 13
    Caption = 'WHERE ...'
  end
  object Label6: TLabel
    Left = 168
    Top = 357
    Width = 109
    Height = 13
    Caption = 'GROUP BY ...  ROLLUP'
  end
  object Label8: TLabel
    Left = 360
    Top = 16
    Width = 81
    Height = 13
    Caption = 'Resultado Query'
  end
  object ListBox2: TListBox
    Left = 8
    Top = 249
    Width = 129
    Height = 250
    DragMode = dmAutomatic
    ItemHeight = 13
    TabOrder = 0
  end
  object ListBox1: TListBox
    Left = 8
    Top = 33
    Width = 129
    Height = 177
    ItemHeight = 13
    TabOrder = 1
    OnClick = ListBox1Click
  end
  object DBGrid1: TDBGrid
    Left = 352
    Top = 35
    Width = 428
    Height = 459
    DataSource = DataSource1
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object ButtonExecutarSQL: TButton
    Left = 786
    Top = 160
    Width = 113
    Height = 25
    Caption = 'Executar SQL'
    TabOrder = 3
    OnClick = ButtonExecutarSQLClick
  end
  object ListBoxSelect: TListBox
    Left = 143
    Top = 33
    Width = 194
    Height = 97
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 4
    OnDragDrop = ListBoxSelectDragDrop
    OnDragOver = ListBoxSelectDragOver
  end
  object ListBoxFrom: TListBox
    Left = 143
    Top = 148
    Width = 194
    Height = 86
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 5
  end
  object ButtonLimparSQL: TButton
    Left = 786
    Top = 209
    Width = 113
    Height = 25
    Caption = 'Limpar SQL'
    TabOrder = 6
    OnClick = ButtonLimparSQLClick
  end
  object ListBoxRollup: TListBox
    Left = 143
    Top = 376
    Width = 194
    Height = 89
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 8
  end
  object ListBoxWhere: TListBox
    Left = 143
    Top = 256
    Width = 194
    Height = 95
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 7
  end
  object ListBoxWhereAux: TListBox
    Left = 143
    Top = 257
    Width = 194
    Height = 95
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 9
    Visible = False
  end
  object Edit1: TEdit
    Left = 786
    Top = 472
    Width = 113
    Height = 22
    AutoSize = False
    TabOrder = 10
    Text = 'SQL Gerado'
  end
  object UniQuery1: TUniQuery
    Connection = Form2.UniConnection1
    AutoCalcFields = False
    Left = 848
    Top = 376
  end
  object DataSource1: TDataSource
    DataSet = UniQuery1
    Left = 792
    Top = 376
  end
  object UniQuery2: TUniQuery
    Connection = Form2.UniConnection1
    Left = 848
    Top = 440
    object UniQuery2COLUMN_NAME: TStringField
      FieldName = 'COLUMN_NAME'
      Required = True
      Size = 64
    end
  end
  object DataSource2: TDataSource
    DataSet = UniQuery2
    Left = 792
    Top = 440
  end
end
