//---------------------------------------------------------------------------
#include <vcl.h>
#include <fstream>
#include <string>
#pragma hdrstop
#include "Unit1.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TStringGrid *StringGrid1;

bool isMagic = true;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	Image1->SendToBack();
}
int** CreateSquare(int rowCount, int colCount, TStringGrid* stringGrid) {
	int** arr = new int*[rowCount];
	for (int i = 0; i < rowCount; i++) {
		arr[i] = new int[colCount];
	}
	for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < colCount; j++) {
			arr[i][j] = StrToInt(stringGrid->Cells[i][j]);
		}
	}
	return arr;
}
//---------------------------------------------------------------------------
bool isPrime(int n) {
	if (n <= 1) return false;

	for (int i = 2; i <= sqrt(n); i++)
		if (n % i == 0) return false;

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender) {
	StringGrid1->RowCount = 2;
	StringGrid1->ColCount = 2;
	StringGrid1->Width = 155;
	StringGrid1->Height = 155;
	StringGrid1->DefaultColWidth = 75;
	StringGrid1->DefaultRowHeight = 75;
	StringGrid1->Left = 265;
	StringGrid1->Top = 120;

	if (RadioButton1->Checked){
		StringGrid1->Visible = true;
		Button4->Enabled = true;
	}
	else StringGrid1->Visible = false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton2Click(TObject *Sender) {
	StringGrid1->RowCount = 3;
	StringGrid1->ColCount = 3;
	StringGrid1->Width = 192;
	StringGrid1->Height = 192;
	StringGrid1->DefaultColWidth = 62;
	StringGrid1->DefaultRowHeight = 62;
	StringGrid1->Left = 245;
	StringGrid1->Top = 105;

	if (RadioButton2->Checked){
		StringGrid1->Visible = true;
		Button4->Enabled = true;
	}
	else StringGrid1->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton3Click(TObject *Sender) {
	StringGrid1->RowCount = 4;
	StringGrid1->ColCount = 4;
	StringGrid1->Width = 199;
	StringGrid1->Height = 199;
	StringGrid1->DefaultColWidth = 48;
	StringGrid1->DefaultRowHeight = 48;
	StringGrid1->Left = 240;
	StringGrid1->Top = 98;

	if (RadioButton3->Checked){
		StringGrid1->Visible = true;
		Button4->Enabled = true;
	}
	else StringGrid1->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton4Click(TObject *Sender) {
		StringGrid1->RowCount = 5;
		StringGrid1->ColCount = 5;
		StringGrid1->Width = 213;
		StringGrid1->Height = 213;
		StringGrid1->DefaultColWidth = 41;
		StringGrid1->DefaultRowHeight = 41;
		StringGrid1->Left = 235;
		StringGrid1->Top = 90;

	if (RadioButton4->Checked){
		StringGrid1->Visible = true;
		Button4->Enabled = true;
	}
	else StringGrid1->Visible = false;
}
//---------------------------------------------------------------------------
bool IsGridFilled(TStringGrid *Grid) {
	bool IsFilled = true;
    for(int Row = 0; Row < Grid->RowCount; ++Row) {
        for(int Col = 0; Col < Grid->ColCount; ++Col) {
            if(Grid->Cells[Col][Row].IsEmpty()) {
                IsFilled = false;
                break;
            }
        }
		if(!IsFilled) break;
    }
    return IsFilled;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {
	if(IsGridFilled(StringGrid1)){
		int** arr = CreateSquare(StringGrid1->RowCount, StringGrid1->ColCount, StringGrid1);
		int sum = 0;
		int diagSum1 = 0, diagSum2 = 0;

		for (int j = 0; j < StringGrid1->RowCount; j++) sum += arr[0][j]; // ����� ������ ������

		for (int i = 1; i < StringGrid1->RowCount; i++) {
			int rowSum = 0, colSum = 0;

			for (int j = 0; j < StringGrid1->RowCount; j++) {
				rowSum += arr[i][j]; // ����� ������
				colSum += arr[j][i]; // ����� �������
			}
			if (rowSum != sum || colSum != sum) {
				isMagic = false;
				break;
			}
		}

		for (int i = 0; i < StringGrid1->RowCount; i++) {
			diagSum1 += arr[i][i]; // ����� ������� ���������
			diagSum2 += arr[i][StringGrid1->RowCount-i-1]; // ����� �������� ���������
		}
		if (diagSum1 != sum || diagSum2 != sum) {
			isMagic = false;
		}

		bool prim = false;
		if(CheckBox1->Checked){
			for(int i = 0; i < StringGrid1->RowCount; i++){
				for(int j = 0; j < StringGrid1->ColCount; j++){
					if(isPrime(arr[i][j])){
						prim = true;
						break;
					}
				}
			}
			if(isMagic == true && prim == true)
				ShowMessage("��� ������� � ������� �� �� �����i �����");
			else if(isMagic == true && prim == false)
				ShowMessage("��� ������� � ������� i �� �� ������� �����");
			else if(isMagic == false && prim == true)
				ShowMessage("��� ������� �� � ������� ��� �� ����� �����");
			else
				ShowMessage("��� ������� �� � ������� � �� �� ����� �����");
		} else {
			if(isMagic == true) ShowMessage("��� ������� � �������");
			else ShowMessage("��� ������� �� �������");
		}

		for (int i = 0; i < StringGrid1->RowCount; i++) delete[] arr[i];
		delete[] arr;

		Button2->Enabled = true;
	} else ShowMessage("�������� ����-����� �������!");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	int** brr = CreateSquare(StringGrid1->RowCount, StringGrid1->ColCount, StringGrid1);
	const char* filename = "output.txt";
	// ��������� ���� ��� ������
	std::ofstream file(filename);

	// ���� �� ������� ������� ����, ������� �� �������
	if (!file.is_open()) {
		std::cerr << "Failed to create file: " << filename << std::endl;
        return;
	}

	// ���������� ������ �� ������� � ����
	for (int i = 0; i < StringGrid1->RowCount; i++) {
		for(int j = 0; j < StringGrid1->RowCount; j++){
			file << "| " << brr[i][j] << " |";
		}
		file << "\n";
	}
	if(isMagic) file << "\n��� ������� � �������";
	else file << "\n��� ������� �� �������";
	// ��������� ����
	file.close();
	for (int i = 0; i < StringGrid1->RowCount; i++) delete[] brr[i];
	delete[] brr;

	ShowMessage("��������!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!isdigit(Key) && Key != VK_BACK && Key != VK_DELETE) Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ShowMessage("����� ��������: ����� ����\n��� ��������� ���������� ������� ����� �������� �� �������� ���� �������");
}
//---------------------------------------------------------------------------
void ReadDataFromFile(TStringGrid *StringGrid1, AnsiString filename) {
	ifstream file(filename.c_str());
    if (file.is_open()) {
        int row = 0;
        int col = 0;
        std::string number;
        char ch;
        while (file.get(ch)) {
			if (isdigit(ch)) number += ch;
			else if (!number.empty()) {
				StringGrid1->Cells[col][row] = AnsiString(number.c_str());
                number.clear();
                col++;
				if (col == StringGrid1->ColCount) {
                    col = 0;
                    row++;
					if (row == StringGrid1->RowCount) break; // ��������� ����� �������
                }
            }
        }
		if (!number.empty()) StringGrid1->Cells[col][row] = AnsiString(number.c_str());
        file.close();
	} else ShowMessage("��������� ������� ����!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	TOpenDialog *OpenDialog1 = new TOpenDialog(NULL);
    // ������ ������� ��� ������
	OpenDialog1->Filter = "Text Files (*.txt)";
	if (OpenDialog1->Execute()) ReadDataFromFile(StringGrid1, OpenDialog1->FileName);
}
//---------------------------------------------------------------------------

