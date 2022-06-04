#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include <iostream>
#include <cstring>
using namespace std;

MENU::MENU(char* Mname, int charge) //������ ������
	: accCharge(charge)
{
	int len = strlen(Mname) + 1;
	accMname = new char[len]; //�����Ҵ����� �޴��� ���� �迭 ũ�� ����
	strcpy(accMname, Mname); //�����Ҵ����� ������ accMname�� �Է� ���� Mname ����
}

MENU::MENU(const MENU& ref) //���� ������ ������
	: accCharge(ref.accCharge)
{
	int len = strlen(ref.accMname) + 1;
	accMname = new char[len];
	strcpy(accMname, ref.accMname);
}

void MENU::showaccCharge() const 
{
	cout << accCharge << "��" << endl;
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
