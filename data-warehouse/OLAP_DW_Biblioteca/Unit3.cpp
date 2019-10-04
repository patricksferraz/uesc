//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h" // use Form2
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
//na criação de nova MATRIZ BARRAMENTO lança dois primeiras coluna ID (autoinc) e Entidades (string) orinada do DW
AnsiString DataFile = "dados.xml";
if (ClientDataSet2Processo->Value=="") {
	ShowMessage("Lançar nome do processos no Grid Abaixo !!!");
}
else {
 DBGrid1->Enabled = false;
 ClientDataSet1->Close();
  ClientDataSet1->FileName = ExtractFilePath(Application->ExeName) + DataFile;

   if  (FileExists(ClientDataSet1->FileName))  {
		 ClientDataSet1->FieldDefs->Clear();
		 ClientDataSet1->FieldDefs->Add("ID", ftAutoInc);
		 ClientDataSet1->FieldDefs->Add("Entidades", ftString,30);
		 novaColuna();
   }
 ClientDataSet1->CreateDataSet();
 ClientDataSet1->Active = true;
 ClientDataSet1->Open();
 carregarDimensoes();
 DBGrid1->Enabled = true;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
    //salva dados no formato XML (noSQL)
	ClientDataSet1->SaveToFile("dados.xml",dfXML);
	ShowMessage("Programa ou edição salvos com sucesso !!!");
}
//---------------------------------------------------------------------------

//carrega dimensões do DW no DBGrid1 na coluna Entidades
void TForm3::carregarDimensoes(){
	AnsiString str, dim, fat;
 	Form2->UniConnection1->GetTableNames(ListBox1->Items,false);
	 if (ListBox1->Items->Count > 0) {
	   for (int i = 0; i < ListBox1->Items->Count; i++){  //compõe a coluna Entidades com tabela de préfixo dim_ e fat_
		 str = ListBox1->Items->Strings[i];
		 dim = str.SubString(str.Pos("dim_"), 4);
		 fat = str.SubString(str.Pos("fat_"), 4);
		  // só carrega com tabelas de préfixo dim_ e fat_
			if ( (CompareStr("dim_", dim) == 0 )||(CompareStr("fat_", fat) == 0 ) ) {
				 ClientDataSet1->Append();
				 ClientDataSet1->FieldByName("Entidades")->AsString = ListBox1->Items->Strings[i];
				 ClientDataSet1->Post();
			}
	   }
	 }
   else {
	 ShowMessage("As tabelas precisão ter o prefixo dim_ ou fat_");
  }
}

//carrega dados originado da base em XML no arquivo dados.xml
void TForm3::carregarDados(){
    ClientDataSet1->Open();
	ClientDataSet1->First();
	if (FileExists(ExtractFilePath(ParamStr(0))+"dados.xml")) {
		ClientDataSet1->LoadFromFile("dados.xml");
	}else {
		ShowMessage("Não há base de dados criada...");
	}
    ClientDataSet1->IndexFieldNames = "ID";
}
void __fastcall TForm3::Button3Click(TObject *Sender)
{
 carregarDados();
}

//carrega novas colunas conforme processos digitados no DBGrid2
void TForm3::novaColuna(){
  AnsiString coluna;
  ClientDataSet2->First();
  for (int i=0; i < ClientDataSet2->RecordCount; i++){
   	coluna = ClientDataSet2Processo->Value+IntToStr(i);
	ClientDataSet1->FieldDefs->Add(coluna, ftString,1);
    ClientDataSet2->Next();
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
   carregarDados();
}
//---------------------------------------------------------------------------

