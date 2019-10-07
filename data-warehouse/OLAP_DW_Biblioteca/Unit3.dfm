object Form3: TForm3
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Matriz Barramento Orientado ao Neg'#243'cio'
  ClientHeight = 557
  ClientWidth = 984
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIForm
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 52
    Top = 372
    Width = 409
    Height = 13
    Caption = 
      'Registrar processos de neg'#243'cios que aparecer'#227'o na colunas da Mat' +
      'riz de Barramento'
  end
  object Label2: TLabel
    Left = 72
    Top = 16
    Width = 393
    Height = 19
    Caption = 'MATRIZ DE BARRAMENTO DO DW PARA CONSULTAS'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object DBGrid1: TDBGrid
    Left = 52
    Top = 92
    Width = 924
    Height = 278
    DataSource = DataSource1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Orientation = 1
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object DBNavigator1: TDBNavigator
    Left = 52
    Top = 48
    Width = 632
    Height = 42
    DataSource = DataSource1
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbDelete, nbEdit, nbCancel, nbRefresh]
    TabOrder = 1
  end
  object Button1: TButton
    Left = 608
    Top = 391
    Width = 98
    Height = 25
    Caption = 'Criar Matriz'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 683
    Top = 48
    Width = 77
    Height = 42
    Caption = 'Salvar'
    TabOrder = 3
    OnClick = Button2Click
  end
  object ListBox1: TListBox
    Left = 52
    Top = 356
    Width = 161
    Height = 14
    ItemHeight = 13
    TabOrder = 4
    Visible = False
  end
  object Button3: TButton
    Left = 712
    Top = 391
    Width = 90
    Height = 25
    Caption = 'Carregar Dados'
    TabOrder = 5
    OnClick = Button3Click
  end
  object DBGrid2: TDBGrid
    Left = 52
    Top = 391
    Width = 409
    Height = 146
    BorderStyle = bsNone
    DataSource = DataSource2
    TabOrder = 6
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
  end
  object DataSource1: TDataSource
    DataSet = ClientDataSet1
    Left = 712
    Top = 440
  end
  object ClientDataSet1: TClientDataSet
    Aggregates = <>
    FileName = 
      'C:\Users\cleiv\Documents\Embarcadero\Studio\Projects\OLAP_DW_Bib' +
      'lioteca\Win32\Debug\dados.xml'
    Params = <>
    Left = 776
    Top = 432
  end
  object ClientDataSet2: TClientDataSet
    PersistDataPacket.Data = {
      370000009619E0BD01000000180000000100000000000300000037000850726F
      636573736F0100490000000100055749445448020002001E000000}
    Active = True
    Aggregates = <>
    Params = <>
    Left = 840
    Top = 472
    object ClientDataSet2Processo: TStringField
      DisplayWidth = 63
      FieldName = 'Processo'
      Size = 30
    end
  end
  object DataSource2: TDataSource
    DataSet = ClientDataSet2
    Left = 928
    Top = 432
  end
end
