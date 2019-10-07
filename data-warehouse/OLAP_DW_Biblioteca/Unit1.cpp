//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Uni"
#pragma resource "*.dfm"
TDrill *Drill;

//---------------------------------------------------------------------------
__fastcall TDrill::TDrill(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDrill::FormCreate(TObject *Sender){
  ListBox1->Clear();
  Form2->UniConnection1->GetTableNames(ListBox1->Items,false);
  for (int i=0;i < Form2->UniQuery1->FieldCount-1;i++)
	 Form2->UniQuery1->Fields->Fields[i]->DisplayWidth = Form2->UniQuery1->Fields->Fields[i]->DisplayText.Length();

}
//---------------------------------------------------------------------------
void __fastcall TDrill::ListBox1Click(TObject *Sender)
{
  ListBox2->Clear();
  Form2->UniConnection1->GetFieldNames(ListBox1->Items->Strings[ListBox1->ItemIndex],ListBox2->Items);
}
//---------------------------------------------------------------------------

void __fastcall TDrill::ButtonExecutarSQLClick(TObject *Sender) {
	int i;
	AnsiString campo, strSQL;

	UniQuery1->Active = false;
	DBGrid1->Enabled = false;
	UniQuery1->Close();
	UniQuery1->SQL->Clear();

	strSQL += "SELECT ";
	if (ListBoxSelect->Items->Count > 0) {
		for (i=0; i < ListBoxSelect->Items->Count; i++){  //compõe a lista de colunas de Select *
			campo = ListBoxSelect->Items->Strings[i];
			strSQL += campo + ", ";
		}

		strSQL.SetLength(strSQL.Length()-2);

		strSQL += " FROM ";
		for (i=0; i < ListBoxFrom->Items->Count; i++) {
			campo = ListBoxFrom->Items->Strings[i];
			strSQL += campo + ", ";
		}

		strSQL.SetLength(strSQL.Length()-2);

		if (ListBoxWhere->Items->Count > 0){
			strSQL += " WHERE ";
			for (i=0; i < ListBoxWhere->Items->Count; i++) {
				campo = ListBoxWhere->Items->Strings[i];
				strSQL += campo + " and ";
			}

			strSQL.SetLength(strSQL.Length()-5);
		}

		strSQL += " GROUP BY ";
		for (i=0; i < ListBoxRollup->Items->Count; i++){  //compõe a lista de colunas de Select *
			campo = ListBoxRollup->Items->Strings[i];
			strSQL += campo + ", ";
		}

		strSQL.SetLength(strSQL.Length()-2);

		strSQL += " WITH ROLLUP LIMIT 30";
		Edit1->Text = strSQL;
		UniQuery1->SQL->Add(strSQL);
		UniQuery1->Open();
		UniQuery1->Prepared = true;
		UniQuery1->Active = true;
		DBGrid1->Enabled = true;
		for (int i=0;i < UniQuery1->FieldCount-1;i++)
			UniQuery1->Fields->Fields[i]->DisplayWidth = UniQuery1->Fields->Fields[i]->DisplayText.Length()*2;
	} else {
		ShowMessage("Insira campos da SQL...");
	}
}
//---------------------------------------------------------------------------

void __fastcall TDrill::ListBoxSelectDragDrop(TObject *Sender, TObject *Source, int X, int Y) {
	AnsiString tabela;
	//adicionar no ListBoxSelect por arrastar-colar atributos para SELECT

	int busca = ListBoxSelect->Perform(LB_FINDSTRING,-1,(LPARAM)(ListBox1->Items->Strings[ListBox1->ItemIndex]+"."+ListBox2->Items->Strings[ListBox2->ItemIndex]).c_str());
	if (busca == -1)  {   //-1 = não encontrou no ListBoxFrom; 0 =  encontrou
		ListBoxSelect->Items->Add(ListBox1->Items->Strings[ListBox1->ItemIndex]+"."+ListBox2->Items->Strings[ListBox2->ItemIndex]);
	}

	//verifica se ja existe Tabela no ListBoxFrom
	if (ListBoxFrom->Items->Count == 0){
		ListBoxFrom->Items->Add("fat_biblioteca");
		tabela = ListBox1->Items->Strings[ListBox1->ItemIndex];

		if (tabela!="fat_biblioteca") {
			ListBoxFrom->Items->Add(tabela);
			chavePrimaria(tabela);
		}
	} else {
		tabela = ListBox1->Items->Strings[ListBox1->ItemIndex];

		if (tabela!="fat_biblioteca")
			chavePrimaria(tabela);

		//busca do nome da tabela no ListBoxFrom pelo nome do ListBox1 selecionado
		int busca = ListBoxFrom->Perform(LB_FINDSTRING,-1,(LPARAM)ListBox1->Items->Strings[ListBox1->ItemIndex].c_str());
		if (busca == -1)  {   //-1 = não encontrou no ListBoxFrom; 0 =  encontrou
			ListBoxFrom->Items->Add(ListBox1->Items->Strings[ListBox1->ItemIndex]);
		}
	}

	ListBoxRollup->Clear();
	ListBoxRollup->Items->AddStrings(ListBoxSelect->Items);
}
//---------------------------------------------------------------------------

void __fastcall TDrill::ListBoxSelectDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept) {
	Accept = true;
}
//---------------------------------------------------------------------------

//função para buscar a chave primária em Tabela
void TDrill::chavePrimaria(AnsiString tabela){
	String s;
	Form2->UniConnection1->GetKeyFieldNames(tabela, ListBoxWhereAux->Items); //retorna nome pk da tabela

	s = "fat_biblioteca.id="+tabela+"."+ListBoxWhereAux->Items->Strings[ListBoxWhereAux->ItemIndex+1];

	int busca = ListBoxWhere->Perform(LB_FINDSTRING,-1,(LPARAM)s.c_str());
	if (busca == -1)  {   //-1 = não encontrou no ListBoxFrom; 0 =  encontrou
		ListBoxWhere->Items->Add("fat_biblioteca.id="+tabela+"."+ListBoxWhereAux->Items->Strings[ListBoxWhereAux->ItemIndex+1]);
	}
}

void __fastcall TDrill::ButtonLimparSQLClick(TObject *Sender)
{
	ListBoxSelect->Clear();
	ListBoxFrom->Clear();
	ListBoxWhere->Clear();
	ListBoxRollup->Clear();
	Edit1->Text = "SQL Gerado";
 }
