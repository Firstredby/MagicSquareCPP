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

		for (int j = 0; j < StringGrid1->RowCount; j++) sum += arr[0][j]; // сумма первой строки

		for (int i = 1; i < StringGrid1->RowCount; i++) {
			int rowSum = 0, colSum = 0;

			for (int j = 0; j < StringGrid1->RowCount; j++) {
				rowSum += arr[i][j]; // сумма строки
				colSum += arr[j][i]; // сумма столбца
			}
			if (rowSum != sum || colSum != sum) {
				isMagic = false;
				break;
			}
		}

		for (int i = 0; i < StringGrid1->RowCount; i++) {
			diagSum1 += arr[i][i]; // сумма главной диагонали
			diagSum2 += arr[i][StringGrid1->RowCount-i-1]; // сумма побочной диагонали
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
				ShowMessage("Цей квадрат є магічним та має простi числа");
			else if(isMagic == true && prim == false)
				ShowMessage("Цей квадрат є магічним i не має простих чисел");
			else if(isMagic == false && prim == true)
				ShowMessage("Цей квадрат не є магічним але має прості числа");
			else
				ShowMessage("Цей квадрат не є магічним і не має прості числа");
		} else {
			if(isMagic == true) ShowMessage("Цей квадрат є магічним");
			else ShowMessage("Цей квадрат не магічний");
		}

		for (int i = 0; i < StringGrid1->RowCount; i++) delete[] arr[i];
		delete[] arr;

		Button2->Enabled = true;
	} else ShowMessage("Заповніть будь-ласка таблицю!");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	int** brr = CreateSquare(StringGrid1->RowCount, StringGrid1->ColCount, StringGrid1);
	const char* filename = "output.txt";
	// Открываем файл для записи
	std::ofstream file(filename);

	// Если не удалось открыть файл, выходим из функции
	if (!file.is_open()) {
		std::cerr << "Failed to create file: " << filename << std::endl;
        return;
	}

	// Записываем данные из массива в файл
	for (int i = 0; i < StringGrid1->RowCount; i++) {
		for(int j = 0; j < StringGrid1->RowCount; j++){
			file << "| " << brr[i][j] << " |";
		}
		file << "\n";
	}
	if(isMagic) file << "\nЦей квадрат є магічним";
	else file << "\nЦей квадрат не магічний";
	// Закрываем файл
	file.close();
	for (int i = 0; i < StringGrid1->RowCount; i++) delete[] brr[i];
	delete[] brr;

	ShowMessage("Виконано!");
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
	ShowMessage("Автор програми: Щиров Іван\nДля отримання результату виберіть розмір квадрату та заповніть його числами");
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
					if (row == StringGrid1->RowCount) break; // достигнут конец таблицы
                }
            }
        }
		if (!number.empty()) StringGrid1->Cells[col][row] = AnsiString(number.c_str());
        file.close();
	} else ShowMessage("Неможливо відкрити файл!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	TOpenDialog *OpenDialog1 = new TOpenDialog(NULL);
    // Задаем фильтры для файлов
	OpenDialog1->Filter = "Text Files (*.txt)";
	if (OpenDialog1->Execute()) ReadDataFromFile(StringGrid1, OpenDialog1->FileName);
}
//---------------------------------------------------------------------------

