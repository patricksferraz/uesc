//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include "DBAccess.hpp"
#include "MemDS.hpp"
#include "Uni.hpp"

//---------------------------------------------------------------------------
class TDrill : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox2;
	TListBox *ListBox1;
	TLabel *Label4;
	TLabel *Label5;
	TDBGrid *DBGrid1;
	TUniQuery *UniQuery1;
	TButton *ButtonExecutarSQL;
	TDataSource *DataSource1;
	TListBox *ListBoxSelect;
	TLabel *Label1;
	TListBox *ListBoxFrom;
	TLabel *Label2;
	TLabel *Label3;
	TUniQuery *UniQuery2;
    TDataSource *DataSource2;
	TStringField *UniQuery2COLUMN_NAME;
	TButton *ButtonLimparSQL;
	TListBox *ListBoxWhere;
	TListBox *ListBoxRollup;
	TLabel *Label6;
	TLabel *Label8;
	TListBox *ListBoxWhereAux;
	TEdit *Edit1;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall ButtonExecutarSQLClick(TObject *Sender);
	void __fastcall ListBoxSelectDragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall ListBoxSelectDragOver(TObject *Sender, TObject *Source, int X, int Y,
          TDragState State, bool &Accept);
	void __fastcall ButtonLimparSQLClick(TObject *Sender);

private:	// User declarations
 TTreeNode *primeiro, *quarto, *segundo, *terceiro, *folha;

public:		// User declarations
	__fastcall TDrill(TComponent* Owner);
	void chavePrimaria(AnsiString tabela);  //declaração função
    void TDrill::limparMemo();

};
//---------------------------------------------------------------------------
extern PACKAGE TDrill *Drill;
//---------------------------------------------------------------------------
#endif
