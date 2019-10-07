object Form2: TForm2
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'DW_Biblioteca (OLAP)'
  ClientHeight = 548
  ClientWidth = 1001
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
  object Label7: TLabel
    Left = 48
    Top = 24
    Width = 31
    Height = 13
    Caption = 'Label7'
  end
  object Label10: TLabel
    Left = 488
    Top = 288
    Width = 37
    Height = 13
    Caption = 'Label10'
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 1
    Width = 985
    Height = 524
    ActivePage = TabSheet1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Rollup'
      object Label2: TLabel
        Left = 19
        Top = 315
        Width = 37
        Height = 13
        Caption = 'Tabelas'
      end
      object Label3: TLabel
        Left = 208
        Top = 315
        Width = 38
        Height = 13
        Caption = 'Campos'
      end
      object Label1: TLabel
        Left = 406
        Top = 316
        Width = 19
        Height = 13
        Caption = 'SQL'
      end
      object Label4: TLabel
        Left = 24
        Top = 285
        Width = 119
        Height = 13
        Caption = 'Clique na Dimens'#227'o/Fato'
      end
      object Label5: TLabel
        Left = 181
        Top = 284
        Width = 179
        Height = 13
        Caption = 'Arrasta atributos para ListBox e Edits'
      end
      object Label6: TLabel
        Left = 393
        Top = 285
        Width = 134
        Height = 13
        Caption = 'Query -  forma'#231#227'o de cubos'
      end
      object Label8: TLabel
        Left = 784
        Top = 285
        Width = 166
        Height = 13
        Caption = 'Atributos com sum() - (Edit1/Edit2)'
      end
      object Label9: TLabel
        Left = 784
        Top = 35
        Width = 132
        Height = 13
        Caption = 'Atributos do Cubo (ListBox)'
      end
      object Label11: TLabel
        Left = 472
        Top = 240
        Width = 37
        Height = 13
        Caption = 'Label11'
      end
      object Label12: TLabel
        Left = 20
        Top = 9
        Width = 249
        Height = 19
        Caption = 'OLAP - FORMA'#199#195'O DE CUBO DW '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Edit1: TEdit
        Left = 784
        Top = 304
        Width = 190
        Height = 21
        TabOrder = 0
        OnDragDrop = Edit1DragDrop
        OnDragOver = Edit1DragOver
      end
      object DBGrid1: TDBGrid
        Left = 19
        Top = 44
        Width = 759
        Height = 231
        DataSource = DataSource1
        TabOrder = 1
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
      end
      object ListBox1: TListBox
        Left = 19
        Top = 300
        Width = 161
        Height = 177
        ItemHeight = 13
        TabOrder = 2
        OnClick = ListBox1Click
      end
      object ListBox2: TListBox
        Left = 183
        Top = 300
        Width = 194
        Height = 177
        DragMode = dmAutomatic
        ItemHeight = 13
        TabOrder = 3
        OnDblClick = ListBox2DblClick
        OnDragDrop = ListBox2DragDrop
      end
      object RichEdit1: TRichEdit
        Left = 393
        Top = 304
        Width = 385
        Height = 177
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        Zoom = 100
        OnKeyPress = RichEdit1KeyPress
      end
      object Button1: TButton
        Left = 600
        Top = 281
        Width = 178
        Height = 22
        Caption = 'Executa SQL no ListBox abaixo:'
        TabOrder = 5
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 784
        Top = 48
        Width = 190
        Height = 22
        Caption = 'Executa SQL ListBox abaixo:'
        TabOrder = 6
        OnClick = Button2Click
      end
      object Edit2: TEdit
        Left = 784
        Top = 331
        Width = 190
        Height = 21
        TabOrder = 7
        OnDragDrop = Edit2DragDrop
        OnDragOver = Edit2DragOver
      end
      object ListBoxSelect: TListBox
        Left = 784
        Top = 72
        Width = 190
        Height = 203
        ItemHeight = 13
        TabOrder = 8
        OnDragDrop = ListBoxSelectDragDrop
        OnDragOver = ListBoxSelectDragOver
      end
      object Button4: TButton
        Left = 656
        Top = 16
        Width = 75
        Height = 22
        Caption = 'Limpar'
        TabOrder = 9
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 447
        Top = 14
        Width = 114
        Height = 24
        Caption = 'Drill-up - Drill-down'
        TabOrder = 10
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 328
        Top = 14
        Width = 113
        Height = 24
        Caption = 'Matriz Barramento'
        TabOrder = 11
        OnClick = Button6Click
      end
      object ListBoxWhere: TListBox
        Left = 784
        Top = 415
        Width = 190
        Height = 20
        ItemHeight = 13
        TabOrder = 12
        Visible = False
        OnDragDrop = ListBoxSelectDragDrop
        OnDragOver = ListBoxSelectDragOver
      end
      object ListBoxWhereAux: TListBox
        Left = 784
        Top = 441
        Width = 190
        Height = 20
        ItemHeight = 13
        TabOrder = 13
        Visible = False
        OnDragDrop = ListBoxSelectDragDrop
        OnDragOver = ListBoxSelectDragOver
      end
      object ListBoxRollup: TListBox
        Left = 784
        Top = 467
        Width = 190
        Height = 20
        ItemHeight = 13
        TabOrder = 14
        Visible = False
        OnDragDrop = ListBoxSelectDragDrop
        OnDragOver = ListBoxSelectDragOver
      end
      object ListBoxFrom: TListBox
        Left = 784
        Top = 389
        Width = 190
        Height = 20
        ItemHeight = 13
        TabOrder = 15
        Visible = False
        OnDragDrop = ListBoxSelectDragDrop
        OnDragOver = ListBoxSelectDragOver
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'CrossTab'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label13: TLabel
        Left = 20
        Top = 9
        Width = 66
        Height = 19
        Caption = 'CrossTab'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label14: TLabel
        Left = 797
        Top = 129
        Width = 35
        Height = 19
        Caption = 'Ano:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object ButtonExecutarCrossTab: TButton
        Left = 819
        Top = 178
        Width = 105
        Height = 33
        Caption = 'Executar CrossTab'
        TabOrder = 0
        OnClick = ButtonExecutarCrossTabClick
      end
      object DBGrid2: TDBGrid
        Left = 19
        Top = 44
        Width = 759
        Height = 437
        DataSource = DataSource3
        TabOrder = 1
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
      end
      object EditAno: TEdit
        Left = 843
        Top = 129
        Width = 89
        Height = 21
        TabOrder = 2
      end
    end
    object Pivot: TTabSheet
      Caption = 'Pivot'#31#31#31#31
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label15: TLabel
        Left = 20
        Top = 9
        Width = 35
        Height = 19
        Caption = 'Pivot'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label16: TLabel
        Left = 757
        Top = 129
        Width = 53
        Height = 19
        Caption = 'Tabela:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label17: TLabel
        Left = 757
        Top = 169
        Width = 95
        Height = 19
        Caption = 'Identificador:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label18: TLabel
        Left = 757
        Top = 209
        Width = 41
        Height = 19
        Caption = 'Pivot:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label19: TLabel
        Left = 757
        Top = 249
        Width = 101
        Height = 19
        Caption = 'Quantificador:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object DBGrid3: TDBGrid
        Left = 19
        Top = 44
        Width = 718
        Height = 437
        DataSource = DataSource4
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
      end
      object EditTabela: TEdit
        Left = 867
        Top = 129
        Width = 89
        Height = 21
        TabOrder = 1
      end
      object ButtonExecutarPivot: TButton
        Left = 803
        Top = 306
        Width = 105
        Height = 33
        Caption = 'Executar Pivot'
        TabOrder = 2
        OnClick = ButtonExecutarPivotClick
      end
      object EditIdentificador: TEdit
        Left = 867
        Top = 169
        Width = 89
        Height = 21
        TabOrder = 3
      end
      object EditPivot: TEdit
        Left = 867
        Top = 209
        Width = 89
        Height = 21
        TabOrder = 4
      end
      object EditQuantificador: TEdit
        Left = 867
        Top = 249
        Width = 89
        Height = 21
        TabOrder = 5
      end
    end
  end
  object DataSource1: TDataSource
    DataSet = UniQuery1
    Left = 272
    Top = 488
  end
  object DataSource2: TDataSource
    DataSet = UniQuery2
    Left = 328
    Top = 488
  end
  object UniConnection1: TUniConnection
    ProviderName = 'MySQL'
    Port = 3306
    Database = 'dw_biblioteca'
    Username = 'root'
    Server = 'localhost'
    Connected = True
    LoginPrompt = False
    Left = 812
    Top = 377
  end
  object UniQuery1: TUniQuery
    Connection = UniConnection1
    SQL.Strings = (
      '')
    Left = 900
    Top = 377
  end
  object UniQuery2: TUniQuery
    Connection = UniConnection1
    SQL.Strings = (
      '')
    Left = 932
    Top = 377
  end
  object MySQLUniProvider1: TMySQLUniProvider
    Left = 860
    Top = 377
  end
  object UniStoredProc1: TUniStoredProc
    Connection = UniConnection1
    Left = 960
    Top = 376
  end
  object DataSource3: TDataSource
    DataSet = UniQuery3
    Left = 408
    Top = 488
  end
  object UniQuery3: TUniQuery
    Connection = UniConnection1
    SQL.Strings = (
      '')
    Left = 900
    Top = 425
  end
  object UniQuery4: TUniQuery
    Connection = UniConnection1
    SQL.Strings = (
      '')
    Left = 932
    Top = 425
  end
  object DataSource4: TDataSource
    DataSet = UniQuery4
    Left = 456
    Top = 488
  end
end
