//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Uni.hpp"
#include "MySQLUniProvider.hpp"
#include "UniProvider.hpp"

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TDataSource *DataSource1;
   	TDataSource *DataSource2;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TEdit *Edit1;
	TDBGrid *DBGrid1;
	TLabel *Label2;
	TListBox *ListBox1;
	TLabel *Label3;
	TListBox *ListBox2;
	TLabel *Label1;
	TRichEdit *RichEdit1;
	TButton *Button1;
	TButton *Button2;
	TTabSheet *TabSheet2;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *ButtonExecutarCrossTab;
	TEdit *Edit2;
	TLabel *Label7;
	TLabel *Label8;
	TListBox *ListBoxSelect;
	TLabel *Label9;
	TButton *Button4;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TUniConnection *UniConnection1;
	TUniQuery *UniQuery1;
	TUniQuery *UniQuery2;
	TMySQLUniProvider *MySQLUniProvider1;
	TUniStoredProc *UniStoredProc1;
	TButton *Button5;
	TButton *Button6;
	TListBox *ListBoxWhere;
	TListBox *ListBoxWhereAux;
	TListBox *ListBoxRollup;
	TListBox *ListBoxFrom;
	TLabel *Label13;
	TDBGrid *DBGrid2;
	TLabel *Label14;
	TEdit *EditAno;
	TDataSource *DataSource3;
	TUniQuery *UniQuery3;
	TTabSheet *Pivot;
	TLabel *Label15;
	TDBGrid *DBGrid3;
	TLabel *Label16;
	TEdit *EditTabela;
	TButton *ButtonExecutarPivot;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TEdit *EditIdentificador;
	TEdit *EditPivot;
	TEdit *EditQuantificador;
	TUniQuery *UniQuery4;
	TDataSource *DataSource4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall RichEdit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ListBox2DblClick(TObject *Sender);
	void __fastcall ListBox2DragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall Edit1DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State,
          bool &Accept);
	void __fastcall Edit1DragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall Edit2DragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall Edit2DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State,
		  bool &Accept);
    void __fastcall ListBoxSelectDragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall ListBoxSelectDragOver(TObject *Sender, TObject *Source, int X, int Y,
          TDragState State, bool &Accept);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall ButtonExecutarCrossTabClick(TObject *Sender);
	void __fastcall ButtonExecutarPivotClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
    void chavePrimaria(AnsiString tabela);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
