//---------------------------------------------------------------------------

#include <vcl.h>
#include <System.IOUtils.hpp>
#include "Math.h"
#pragma hdrstop

#include <set>
#include <iostream>
#include <fstream>
#include <bitset>
#include <stdio.h>
#include <cstdint>
#include "string.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm* MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------

char* src;
int* res;
int size = 0;


const int MAX_OPTION = 2;
const int MIN_EXT = 5;
const int MIN_LEN = 1;
const int MAX_LEN = 32;
const int MIN_TEXT = 1;
const int MAX_TEXT = 255;
const int MAX_NUM = 2000000;

enum TErrorCode
{
    CORRECT,
    INCORRECT_CHOICE,
    NON_NUMERIC,
    OUT_OF_RANGE,
    FILE_NOT_TXT,
    FILE_NOT_EXIST,
    FILE_NOT_READABLE,
    FILE_NOT_WRITABLE,
    FILE_IS_EMPTY,
    FILE_NOT_FULL
};

const std::wstring ERR[] = { L"",
    L"Error. Incorrect choice. Please try again. ",
    L"Error. Non-numeric value. Please try again. ",
    L"Error. Out of Range. Please try again. ",
    L"Error. File not .txt. Please try again. ",
    L"Error. File not Exist. Please try again. ",
    L"Error. File not readable. Please try again. ",
    L"Error. File not writable. Please try again. ",
    L"Error. File is empty. Please try again. ",
    L"Error. The file lacks sufficient information . Please try again. " };

std::wstring __fastcall getExtension(
    const std::wstring &str, const int posStart, const int posEnd)
{
    int i;
    std::wstring extension;
    extension = L"";
    for (i = posStart; i < posEnd; i++) {
        extension += str[i];
    }
    return extension;
}

TErrorCode __fastcall isFileExist(std::wstring &pathToFile)
{
    TErrorCode error;
    std::ifstream fileName(pathToFile);
    error = CORRECT;
    if (!fileName) {
        error = FILE_NOT_EXIST;
    }
    return error;
}

TErrorCode __fastcall isFileReadable(const std::ifstream &fileName)
{
	TErrorCode error;
	error = CORRECT;
	if (!fileName.is_open()) {
        error = FILE_NOT_READABLE;
    }
	return error;
}

TErrorCode __fastcall isFileWritable(const std::ofstream &fileName)
{
    TErrorCode error;
    error = CORRECT;
    if (!fileName.is_open()) {
        error = FILE_NOT_WRITABLE;
    }
    return error;
}

void __fastcall TMainForm::N3Click(TObject* Sender)
{
	TMainForm::btFileClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btClearClick(TObject* Sender)
{
	reOpenKey->Text = "";
    reCloseKey->Text = "";
	reSrcText->Text = "";
	reHash->Text = "";
	reENS->Text = "";
	edP->Text = "";
	edQ->Text = "";
	edE->Text = "";
}
//---------------------------------------------------------------------------
char* resizeArray(char* arr, int &currentCapacity)
{
	int newCapacity = currentCapacity * 2;
	char* newArr = new char[newCapacity];

	for (int i = 0; i < currentCapacity; i++) {
		newArr[i] = arr[i];
		//String str = IntToHex(newArr[i])+ "<====" + IntToHex(arr[i]);
		//Application->MessageBox(
		//	 str.w_str(), L"Ошибка!", MB_OK | MB_ICONWARNING);
	}

	delete[] arr;
	currentCapacity = newCapacity;
    return newArr;
}
//---------------------------------------------------------------------------
String printArr(char* arr, int arr_size){
	String binaryStr = "";
	int counter = 0;
	unsigned int num = 0;
	char ch;
	if (arr_size > 15) {
		int nums = 10;
		for (int j = 0; j < nums; j++) {
			ch = arr[j];
			if (ch != ' ') {
				num = abs(ch);
				binaryStr += StrToInt(num);
				binaryStr += ' ';
			} else {
				nums++;
			}
		}
		num = 0;
		binaryStr += "\n---------------------------------------------\n";
		for (int j = arr_size - 10; j < arr_size; j++) {
			ch = arr[j];
			if (ch != ' ') {
				num = abs(ch);
				binaryStr += StrToInt(num);
				binaryStr += ' ';
			}
		}
	} else {
		num = 0;
		for (int j = 0; j < arr_size; j++) {
			ch = arr[j];
			if (ch != ' ') {
				num = abs(ch);
				binaryStr += StrToInt(num);
				binaryStr += ' ';
			}
		}
	}
	return binaryStr;
}
//---------------------------------------------------------------------------
String printIntArr(int* arr, int arr_size){
	String binaryStr = "";
	int counter = 0;
	int ch;
	if (arr_size > 19) {
		int nums = 10;
		for (int j = 0; j < nums; j++) {
			ch = arr[j];
			binaryStr += IntToStr(ch);
			binaryStr += " ";
		}
		binaryStr += "\n---------------------------------------------\n";
		for (int j = arr_size - 10; j < arr_size; j++) {
			ch = arr[j];
			binaryStr += IntToStr(ch);
			binaryStr += " ";
		}
	} else {
		for (int j = 0; j < arr_size; j++) {
			ch = arr[j];
			binaryStr += IntToStr(ch);
			binaryStr += " ";
		}
	}
	return binaryStr;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::readFileInput(
    std::ifstream &fileName, TObject* Sender)
{
	String binaryStr = "";
    char ch;
    int i = 0;
    size = 65535;
	src = new char[size];
	unsigned char byte;
    while (fileName.read(&ch, 1)) {
		if (i >= size) {
			src = resizeArray(src, size);
		}
        src[i] = ch;
        i++;
    }
	size = i;
	binaryStr = printArr(src, size);
	reSrcText->Lines->Text = binaryStr;
	fileName.close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::saveFileInput(
    std::ofstream &fileName, TObject* Sender)
{
	fileName.write(src, size);
    Application->MessageBox(
        L"Файл сохранен!", L"Готово!", MB_OK | MB_ICONWARNING);
    fileName.close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btFileClick(TObject* Sender)
{
    //std::ifstream fileName;
    std::wstring pathToFile;
    TErrorCode error;
    if (OpenTextFileDialog1->Execute()) {
        pathToFile = OpenTextFileDialog1->FileName.c_str();

        std::ifstream fileName(pathToFile, std::ios::binary);

        error = CORRECT;
        if (error == CORRECT) {
            error = isFileExist(pathToFile);
        }
        if (error == CORRECT) {
            //fileName.open(pathToFile, std::ios::binary);
            error = isFileReadable(fileName);
        }
        if ((error == CORRECT) &&
            fileName.peek() == std::ifstream::traits_type::eof()) {
            error = FILE_IS_EMPTY;
        }
		if (error == CORRECT) {
			reSrcText->Text = "";
			reHash->Text = "";
			reENS->Text = "";
            readFileInput(fileName, Sender);
        }
        if (error != CORRECT) {
            Application->MessageBox(
                ERR[error].c_str(), L"Ошибка!", MB_OK | MB_ICONWARNING);
        }
    }
}
//---------------------------------------------------------------------------
unsigned int get_mi(long long di, int b, int n){
	unsigned int mi;
	if ((di - b)%2 == 0) {
		mi = ((-b+di)/2)%n;
	} else {
		mi = ((-b+n+di)/2)%n;
	}
	return mi;
}

long long mul_mod(long long a, long long b, long long mod) {
    long long res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

long long modular_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mul_mod(res, base, mod);
		base = mul_mod(base, base, mod);
        exp /= 2;
    }
    return res;
}
//---------------------------------------------------------------------------
int extended_gcd(int a, int b, int &x, int &y)
{
    x = 1;
    y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        a1 %= b1;
        std::swap(a1, b1);
        x -= q * x1;
        std::swap(x, x1);
        y -= q * y1;
        std::swap(y, y1);
    }
    return a1;
}
//---------------------------------------------------------------------------
bool is_prime(long long n) {
	if (n < 2) return false;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btCipherClick(TObject* Sender)
{
	TErrorCode error = CORRECT;
	int r, fr, p, q, e, x, y;
    String resStr = "";

	p = StrToInt(edP->Text);
    q = StrToInt(edQ->Text);
	e = StrToInt(edE->Text);
	if (!extended_gcd(p, q, x, y)) {
		error = NON_NUMERIC;
		Application->MessageBox(
			L"Не взаимно простые P, Q!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	if (!is_prime(p)) {
		error = NON_NUMERIC;
		Application->MessageBox(
			L"Не простое P!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	if (!is_prime(q)) {
		error = NON_NUMERIC;
		Application->MessageBox(
			L"Не простое Q!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	r = p * q;
	fr = (p-1) * (q-1);
	if (e >= r || e < 2) {
		error = NON_NUMERIC;
        Application->MessageBox(
			L"1 < e < f(r) не выполнолось", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	if (!extended_gcd(e, fr, x, y)) {
		error = NON_NUMERIC;
        Application->MessageBox(
			L"e, f(r) - не взаимно простые", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}

	if (reSrcText->Text.Length() != 0 && error == CORRECT) {
		extended_gcd(e, fr, x, y);
		int d = x;
		reOpenKey->Lines->Text = "r = " + IntToStr(r) + "\ne = " + IntToStr(e);
		reCloseKey->Lines->Text = "r = " + IntToStr(r) + "\nd = " + IntToStr(d);
		char ch;
		int num = 0;
		int c = 0;

		res = new int[size + 1];
		res[0] = 100;
        res[1] = 0;

		for (int j = 0; j < size; j++) {
			ch = src[j];
			num = ch & 0xff;
			c = ((res[j] + num) * (res[j] + num)) % r;
            res[j + 1] = c;
			num = 0;
		}
		int S = modular_pow(c, d, r);
		String binaryStr = "";
		binaryStr = printIntArr(res, size + 1);
		reHash->Lines->Text = binaryStr;
		reENS->Lines->Text = IntToStr(S);
		int curSize = size;
		src = resizeArray(src, size);
		size = curSize;
        for (int i = 0; i < 4; i++){
			src[size] = ((S >> (8 * i)) & 0xFF);
			size++;
		}
	} else if (error == CORRECT){
		Application->MessageBox(
			L"Выберите файл!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btDecipherClick(TObject* Sender)
{
	TErrorCode error = CORRECT;
	int r, fr, p, q, e, x, y;
	String resStr = "";

    p = StrToInt(edP->Text);
    q = StrToInt(edQ->Text);
	e = StrToInt(edE->Text);
	if (!extended_gcd(p, q, x, y)) {
		error = NON_NUMERIC;
		Application->MessageBox(
			L"Не взаимно простые P, Q!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	if (!is_prime(p)) {
		error = NON_NUMERIC;
		Application->MessageBox(
			L"Не простое P!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	if (!is_prime(q)) {
		error = NON_NUMERIC;
		Application->MessageBox(
			L"Не простое Q!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	r = p * q;
	fr = (p-1) * (q-1);
	if (e >= r || e < 2) {
		error = NON_NUMERIC;
        Application->MessageBox(
			L"1 < e < f(r) не выполнолось", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}
	if (!extended_gcd(e, fr, x, y)) {
		error = NON_NUMERIC;
        Application->MessageBox(
			L"e, f(r) - не взаимно простые", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}

	if (reSrcText->Text.Length() != 0 && error == CORRECT) {
		extended_gcd(e, fr, x, y);
		int d = x;
		reOpenKey->Lines->Text = "r = " + IntToStr(r) + "\ne = " + IntToStr(e);
		reCloseKey->Lines->Text = "r = " + IntToStr(r) + "\nd = " + IntToStr(d);
		char ch;
		int num = 0;
		int c = 0;

		res = new int[size + 1 - 4];
		res[0] = 100;
		for (int j = 0; j < size - 4; j++) {
			ch = src[j];
			num = ch & 0xff;
			c = ((res[j] + num) * (res[j] + num)) % r;
            res[j + 1] = c;
			num = 0;
		}
		num = 0;
		for (int i = size - 4; i < size; i++) {
			ch = src[i];
			num += ((ch & 0xFF) << (8*(i - size)));
		}
		int S = modular_pow(num, e, r);

		String binaryStr = "";
		binaryStr = printIntArr(res, size + 1 - 4);
		reHash->Lines->Text = binaryStr;
		reENS->Lines->Text = IntToStr(num);
        if (S != c) {
			Application->MessageBox(
				L"Цифровая подпись не верна!", L"Ошибка!", MB_OK | MB_ICONWARNING);
		} else {
            Application->MessageBox(
				L"Цифровая подпись верна!", L"Ошибка!", MB_OK | MB_ICONWARNING);
		}

	} else if (error == CORRECT){
		Application->MessageBox(
			L"Выберите файл!", L"Ошибка!", MB_OK | MB_ICONWARNING);
	}

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N4Click(TObject* Sender)
{
    //std::ofstream fileName;
    std::wstring pathToFile;
    TErrorCode error;
    if (SaveTextFileDialog1->Execute()) {
        pathToFile = SaveTextFileDialog1->FileName.c_str();

        std::ofstream fileName(pathToFile, std::ios::binary);

        error = CORRECT;
        if (error == CORRECT) {
            //error = isFileExist(pathToFile);
        }
        if (error == CORRECT) {
            //fileName.open(pathToFile, std::ios::binary);
            error = isFileWritable(fileName);
        }
        if (error == CORRECT) {
            saveFileInput(fileName, Sender);
        }
        if (error != CORRECT) {
            Application->MessageBox(
                ERR[error].c_str(), L"Ошибка!", MB_OK | MB_ICONWARNING);
        }
    }
}
//---------------------------------------------------------------------------


