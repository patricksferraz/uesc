//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"  //chama Form1 Drill
#include "Unit3.h"  //chama Form3 Matriz de Barramento
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "MemDS"
#pragma link "Uni"
#pragma link "MySQLUniProvider"
#pragma link "UniProvider"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
  //Executa SQL digitada livrimente pelo usuário
  if (RichEdit1->Lines->Text=="") {
	 ShowMessage("Insira SQL para formação do cubo OLAP");
   }
   else
   {
	 DBGrid1->Enabled = false;
	 UniQuery2->Active = false;
	 UniQuery2->Close();
	 UniQuery2->SQL->Clear();
	 UniQuery2->SQL->Add(RichEdit1->Lines->Text);
	 UniQuery2->Open();
     UniQuery2->Prepared = true;
	 UniQuery2->Active = true;
	 DBGrid1->DataSource = DataSource2;
	 DBGrid1->Enabled = true;
   }
   //diminuir tamanho de caracteres nas colunas do grid
   for (int i=0; i < UniQuery2->FieldCount-1; i++)
	 UniQuery2->Fields->Fields[i]->DisplayWidth = UniQuery2->Fields->Fields[i]->DisplayText.Length()*2;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	 //ao carregar o Form2 executa a SQL com Rollup abaixo
	 UniQuery1->Active = false;
	 UniQuery1->Close();
	 UniQuery1->SQL->Clear();
	 UniQuery1->SQL->Add("SELECT obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo, data.semana_emprestimo, data.dia_emprestimo, count(obr.titulo) AS 'Total de emprestimos' ");
	 UniQuery1->SQL->Add("FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib ");
	 UniQuery1->SQL->Add("WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id ");
	 UniQuery1->SQL->Add("GROUP BY obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo, data.semana_emprestimo, data.dia_emprestimo WITH ROLLUP");
	 UniQuery1->Prepared = true;
	 UniQuery1->Active = true;
	 UniQuery1->Open();
	 ListBox1->Clear();
	 UniConnection1->GetTableNames(ListBox1->Items,false); //carrega ListBox1 com nome das Tabelas do BD
	 for (int i=0;i < UniQuery1->FieldCount-1;i++)
	   UniQuery1->Fields->Fields[i]->DisplayWidth = UniQuery1->Fields->Fields[i]->DisplayText.Length();
 }
//---------------------------------------------------------------------------

void TForm2::chavePrimaria(AnsiString tabela){
	String s;
	Form2->UniConnection1->GetKeyFieldNames(tabela, ListBoxWhereAux->Items); //retorna nome pk da tabela

	s = "fat_biblioteca.id="+tabela+"."+ListBoxWhereAux->Items->Strings[ListBoxWhereAux->ItemIndex+1];

	int busca = ListBoxWhere->Perform(LB_FINDSTRING,-1,(LPARAM)s.c_str());
	if (busca == -1)  {   //-1 = não encontrou no ListBoxFrom; 0 =  encontrou
		ListBoxWhere->Items->Add("fat_biblioteca.id="+tabela+"."+ListBoxWhereAux->Items->Strings[ListBoxWhereAux->ItemIndex+1]);
	}
}


void __fastcall TForm2::Button2Click(TObject *Sender) {
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

		if (Edit1->Text != "")
		   strSQL += ", format(sum("+Edit1->Text+"),2)";

		if (Edit2->Text != "")
		   strSQL += ", format(sum("+Edit2->Text+"),2)";

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

		UniQuery1->SQL->Add(strSQL);
		UniQuery1->Open();
		UniQuery1->Prepared = true;
		UniQuery1->Active = true;
		DBGrid1->DataSource = DataSource1;
		DBGrid1->Enabled = true;
		for (int i=0;i < UniQuery1->FieldCount-1;i++)
			UniQuery1->Fields->Fields[i]->DisplayWidth = UniQuery1->Fields->Fields[i]->DisplayText.Length()*2;
	} else {
		ShowMessage("Insira campos da SQL...");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox1Click(TObject *Sender)
{
	 //carrega o ListBox2 com atributos da tabela selecionada no ListBox1
	 ListBox2->Clear();
	 UniConnection1->GetFieldNames(ListBox1->Items->Strings[ListBox1->ItemIndex],ListBox2->Items);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RichEdit1KeyPress(TObject *Sender, System::WideChar &Key)
{
  // verifica se o RichEdit1 (editor) está sem escrita SELECT (valor null)
  if ( Pos("SELECT", RichEdit1->Text,0  ) !=0 )
	 ShowMessage("Palavra encontrada");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox2DblClick(TObject *Sender)
{
	Edit1->Text = ListBox2->Items->Strings[ListBox2->ItemIndex];

}
//---------------------------------------------------------------------------

void __fastcall TForm2::ListBox2DragDrop(TObject *Sender, TObject *Source, int X,
		  int Y)
{
  // arrasta atributo da tabela selecionada para o Edit1 para formação do Select
  Edit1->Text = ListBox2->Items->Strings[ListBox2->ItemIndex];
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1DragOver(TObject *Sender, TObject *Source, int X, int Y,
		  TDragState State, bool &Accept)
{
  //Aceita o atributo em arrasto para o Edit1
  Accept = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1DragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
  // arrasta atributo da tabela selecionada para o Edit1 para formação de SUM() no Select
  Edit1->Text = ListBox2->Items->Strings[ListBox2->ItemIndex];

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2DragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
	 // arrasta atributo da tabela selecionada para o Edit2 para formação de SUM() no Select
	Edit2->Text = ListBox2->Items->Strings[ListBox2->ItemIndex];
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit2DragOver(TObject *Sender, TObject *Source, int X, int Y,
		  TDragState State, bool &Accept)
{
	//Aceita o atributo em arrasto para o Edit2
	Accept = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ListBoxSelectDragDrop(TObject *Sender, TObject *Source, int X, int Y) {
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

void __fastcall TForm2::ListBoxSelectDragOver(TObject *Sender, TObject *Source, int X,
		  int Y, TDragState State, bool &Accept)
{
	 //Aceita o atributo em arrasto para o ListBox3
	 Accept = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender) {
  //Limpa os objetos visuais
	ListBoxSelect->Clear();
	ListBoxFrom->Clear();
	ListBoxWhere->Clear();
	ListBoxRollup->Clear();
	Edit1->Clear();
	Edit2->Clear();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::Button5Click(TObject *Sender)
{
  //Abre o Form de nome Drill. Necessário incluir na área declarativa desta código o #include "Unit1.h"
  Drill->Show();

}
//---------------------------------------------------------------------------



void __fastcall TForm2::Button6Click(TObject *Sender)
{
	 //Abre o Form de nome Form3. Necessário incluir na área declarativa desta código o #include "Unit3.h"
	Form3->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonExecutarCrossTabClick(TObject *Sender){
	if (EditAno->Text != ""){
		UniQuery3->Active = false;
		DBGrid2->Enabled = false;
		UniQuery3->Close();
		UniQuery3->SQL->Clear();
		UniQuery3->SQL->Add(" CALL movimentacaoAnual(:ano_movimentacao) ");
		UniQuery3->ParamByName("ano_movimentacao")->AsString = EditAno->Text;
		UniQuery3->Open();
		UniQuery3->Prepared = true;
		UniQuery3->Active = true;
		DBGrid2->Enabled = true;

		for (int i=0;i < UniQuery3->FieldCount-1;i++)
			UniQuery3->Fields->Fields[i]->DisplayWidth = 20;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ButtonExecutarPivotClick(TObject *Sender){
	if (EditTabela->Text != "" && EditIdentificador->Text != "" && EditPivot->Text != "" && EditQuantificador->Text != ""){
		UniQuery4->Active = false;
		DBGrid3->Enabled = false;
		UniQuery4->Close();
		UniQuery4->SQL->Clear();
		UniQuery4->SQL->Add("CALL Pivot(:tbl_name, :base_cols, :pivot_col, :tally_col, '', '') ");
		UniQuery4->ParamByName("tbl_name")->AsString = EditTabela->Text;
		UniQuery4->ParamByName("base_cols")->AsString = EditIdentificador->Text;
		UniQuery4->ParamByName("pivot_col")->AsString = EditPivot->Text;
		UniQuery4->ParamByName("tally_col")->AsString = EditQuantificador->Text;
		UniQuery4->Open();
		UniQuery4->Prepared = true;
		UniQuery4->Active = true;
		DBGrid3->Enabled = true;

		for (int i=0;i < UniQuery4->FieldCount-1;i++)
			UniQuery4->Fields->Fields[i]->DisplayWidth = 20;
	}

}
//---------------------------------------------------------------------------

