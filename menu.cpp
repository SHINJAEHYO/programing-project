#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include <iostream>
#include <cstring>
using namespace std;

MENU::MENU(char* Mname, int charge) //생성자 재정의
	: accCharge(charge)
{
	int len = strlen(Mname) + 1;
	accMname = new char[len]; //동적할당으로 메뉴명 저장 배열 크기 생성
	strcpy(accMname, Mname); //동적할당으로 생성된 accMname에 입력 받은 Mname 저장
}

MENU::MENU(const MENU& ref) //복사 생성자 재정의
	: accCharge(ref.accCharge)
{
	int len = strlen(ref.accMname) + 1;
	accMname = new char[len];
	strcpy(accMname, ref.accMname);
}

void MENU::showaccCharge() const 
{
	cout << accCharge << "원" << endl;
}

void MENU::showaccMname() const
{
	cout << accMname << endl;
}

char* MENU::getaccMname() const
{
	return accMname;
}

int MENU::getaccCharge() const
{
	return accCharge;
}

MENU::~MENU()
{
	delete[] accMname;
}
