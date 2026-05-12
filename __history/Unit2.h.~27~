//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *btFile;
	TLabel *lbTask;
	TOpenTextFileDialog *OpenTextFileDialog1;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TRichEdit *reSrcText;
	TLabel *lbSrcText;
	TRichEdit *reDestText;
	TLabel *lbDestText;
	TLabel *lbKey;
	TEdit *edKey;
	TButton *btCipher;
	TButton *btRecipher;
	TButton *btClear;
	TSaveTextFileDialog *SaveTextFileDialog1;
	TRichEdit *reGenKey;
	TLabel *lbKeyText;
	void __fastcall saveFileInput(std::ofstream &fileName, TObject* Sender);
	void __fastcall readFileInput(std::ifstream &fileName, TObject* Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall btClearClick(TObject *Sender);
	void __fastcall btFileClick(TObject *Sender);
	void __fastcall btCipherClick(TObject *Sender);
	void __fastcall btDecipherClick(TObject *Sender);
	void __fastcall reSrcTextChange(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall edKeyKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
