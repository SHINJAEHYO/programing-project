#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "kioskfunc.h"
#include "menu.h"
#include <algorithm> //sort�Լ� ���
#include <time.h> //�ð� ����ϱ� ���� ���
#include <string> //find�Լ� ���
using namespace std;

const int NAME_LEN = 100; //�޴��� �ִ� ũ�� 100���� ����


void ShowMenu(void)
{
	cout << endl;
	cout << "������ �Ͻðڽ��ϱ�?" << endl;
	cout << "1. �޴��߰�" << endl;
	cout << "2. �޴�����" << endl;
	cout << "3. �޴��˻�" << endl;
	cout << "4. ����" << endl;
	cout << "5. ����" << endl;
	cout << "6. �� �޴����" << endl;
}

void updatemenu(MENU* accArr[], int& accNum)
{
	char Mname[NAME_LEN];
	int charge;
	int Ufinal = 0; //���, ��� ��ư
	
	cout << "[�޴��߰�]" << endl << endl;
	cout << "�޴��� : ";
	cin >> Mname;
	cout << "���� : ";
	cin >> charge;
	
	cout << endl << "���(1) / ���(0) : ";
	cin >> Ufinal;

	if (Ufinal == 1) {
		accArr[accNum++] = new MENU(Mname, charge); //�����Ҵ� ����Ͽ� accArr������ �迭�� Ŭ���� ��ü �ּҸ� ����Ŵ
	}
	else if (Ufinal == 0) {
		return;
	}
}

void deletemenu(MENU* accArr[], int& accNum)
{
	int dnum = 0; //���� �޴� ��ȣ
	int Dfinal = 0; //����, ��� ��ư

	cout << "[����]" << endl << endl;
	for (int i = 0; i < accNum; ++i) { //�ѹ����� �޴��� ���
		cout << i + 1 << "."; //�迭�� 0���� �����ϹǷ� 1�� ���Ͽ� 1���� �ѹ���
		accArr[i]->showaccMname();
	}
	cout << endl << "������ �޴��� ��ȣ�� �Է��ϼ��� : ";
	cin >> dnum;
	cout << endl << "����(1) / ���(0) : ";
	cin >> Dfinal;
	if (Dfinal == 1)
	{
		for (int din = dnum - 1; din < accNum; din++) //1���� accArr[0]�̹Ƿ� -1
		{
			accArr[din] = accArr[din + 1]; //din(delete index number) ������ �ε��� ��ȣ
		}
		accNum--; //������ �迭 accArr�� �ϳ� ���� �߱� ������ accNum 1����
		return;
	}
	else if (Dfinal == 0)
	{
		return;
	}
}

void searchmenu(MENU* accArr[], int& accNum)
{
	cout << "[�˻�]" << endl << endl;
	string name[20]; //�޴��� �����ϴ� �迭(������ ũ�� 20���� ����)
	string fmenu; //�˻��� �޴��� ���� ����
	int NFnum = 0; //NOT FOUND number 

	for (int i = 0; i < accNum; i++) { //�� �迭�� ��ü �޴��� �ϳ��� ����
		name[i] = accArr[i]->getaccMname(); 
	}

	cout << "�޴��� �˻�(�� ���� �̻�) : ";
	cin >> fmenu;

	for (int k = 0; k < accNum; k++) { //�޴��� ����� �Է� �� NFnum�� �����Ͽ� while�� �ǳʶ�
		if (name[k].find(fmenu) != string::npos) {
			NFnum++;
		}
	}
	
	while (NFnum == 0) //���� �޴��� �Է� �� ��˻� �ݺ�
	{
		cout << "ã���ô� �޴��� �����ϴ�. �ٽ� �˻����ּ���." << endl << endl;
		cout << "�޴��� �˻�(�� ���� �̻�) : ";
		cin >> fmenu;
		for (int k = 0; k < accNum; k++) { //�޴��� ����� �Է� �� while�� ����
			if (name[k].find(fmenu) != string::npos) {
				NFnum++;
			}
		}
	}

	if (NFnum != 0)
	{
		cout << endl << "�޴���   " << "����" << endl << endl;
		for (int j = 0; j < accNum; j++) {
			if (name[j].find(fmenu) != string::npos) { //fmenu�� �Էµ� ���ڸ� name�迭 ��ü�� �ݺ��ϸ� ã�´�.
				cout << accArr[j]->getaccMname() << "  ";
				accArr[j]->showaccCharge();
			}
		}
	}
}

void arraymenu(MENU * accArr[], int& accNum)
{
	cout << "[����]" << endl << endl;

	MENU* temp; //accArr������ �迭�� ����Ű�� ������
	for (int j = 0; j < accNum; j++) //����
	{
		for (int i = 0; i < accNum; i++)
		{
			if (accArr[i]->getaccCharge() < accArr[i + 1]->getaccCharge()) //�� accArr������ �迭�� ����Ű�� ��ü�� �����ϰ� �ִ� accCharge���� ���Ѵ�.
			{                                                              //if���� ������ �����ϸ� �� ������ �迭�� �����ϴ� �ּҸ� �ٲ۴�.
				temp = accArr[i];
				accArr[i] = accArr[i + 1];
				accArr[i + 1] = temp;
			}
		}
	}
	return;
}

void paymenu(MENU* accArr[], int& accNum)
{
	cout << "[����]" << endl << endl;
	int index = 0; //index��ȣ
	int paysum = 0; //�� ���� �ݾ� ���� ����
	int k = 1; //k�� 0�̸� ���ѷ��� ����
	int loop = 0; //while�� �ݺ���
	int ordhis[20] = {}; //�ִ� �� �� �ִ� �޴� 19��

	int YN = 0; //������ ����ϱ� ���� �Է°�(Yes or No)
	static int ordNum = 0; //�ֹ���ȣ(�Լ� ���� �Ŀ� ���� �����ǵ��� �������� ����)

	time_t timer = time(NULL);

	struct tm* t = localtime(&timer);
	struct tm {
		int tm_sec; //��
		int tm_min; //��
		int tm_hour; //�ð�
		int tm_mday; //��
		int tm_mon; //��
		int tm_wday; //����
		int tm_year; //��
	};
	
	for (int i = 0; i < accNum; ++i) {
		cout << i + 1 << ".";
		accArr[i]->showaccMname();
		accArr[i]->showaccCharge();
		cout << endl;
	}
	cout << "�����Ͻ� �޴��� ��ȣ�� �Է��ϼ���." << endl;

	while (k != 0)
	{
		cout << "�޴� ��ȣ : ";
		cin >> index; //������ �޴� ��ȣ
		paysum += accArr[index - 1]->getaccCharge(); //�޴� �� ������ ���� ���Ͽ� ����
		cout << "�߰� ���� �� 1�� / �������� 0���� �Է��ϼ��� : ";
		ordhis[loop] = index - 1; //�� �޴� ��ȣ - 1 ���� �����ϴ� �迭(��:1�� �޴� ���� ordhis[0] = 0)
		loop++;                   //loop�� 0���� while�� �ݺ� ������ 1�� �����Ͽ� ������ �迭�� ���޴���ȣ - 1 �� ����
		cin >> k;
	}
	
	cout << "�� ���� �ݾ� : " << paysum << "��\n" << endl;
	ordNum++; //�ֹ���ȣ ����
	cout << "�������� ����Ͻðڽ��ϱ�? (�� = 1 / �ƴϿ� = 0)" << " : ";
	cin >> YN;

	if (YN == 1)
	{
		cout << endl << "-----------------------------------" << endl;
		cout << "KIOSK RECEIPT\n";
		cout << "-----------------------------------" << endl;
		cout << "�ֹ���ȣ : " << ordNum << endl; //�ֹ���ȣ : (��ȣ)
		cout << "-----------------------------------" << endl;                      //�⵵�� 1900�����, ���� 0���� ����
		cout << t->tm_year + 1900 << " - " << t->tm_mon + 1 << " - " << t->tm_mday; //�⵵ - �� - ��(����) �ð� : �� : ��
		if (t->tm_wday == 0)                                                        //������ ���ڷ� ��ȯ 0 = �Ͽ���, 1 = ������ ... 6 = �����
		{
			cout << "(��) ";
		}
		else if (t->tm_wday == 1)
		{
			cout << "(��) ";
		}
		else if (t->tm_wday == 2)
		{
			cout << "(ȭ) ";
		}
		else if (t->tm_wday == 3)
		{
			cout << "(��) ";
		}
		else if (t->tm_wday == 4)
		{
			cout << "(��) ";
		}
		else if (t->tm_wday == 5)
		{
			cout << "(��) ";
		}
		else if (t->tm_wday == 6)
		{
			cout << "(��) ";
		}
		cout << t->tm_hour << " : " << t->tm_min << " : " << t->tm_sec << endl; //�ð� ���
		cout << "-----------------------------------" << endl;
		cout << "���ų���\n" << "�޴���   " << "����\n" << endl;
		for (int j = 0; j < loop; j++)
		{
			cout << accArr[ordhis[j]]->getaccMname() << "  " << accArr[ordhis[j]]->getaccCharge() << "��" << endl;
		} //�� �޴� ��ȣ-1 ���� �����ϴ� �迭�� ����Ͽ� �� �迭�� ����� ���� accArr �ε����� �־� �� �޴����� �޴���� ������ ���
		cout << "-----------------------------------" << endl;
		cout << "���� �ݾ� : " << paysum << "��" << endl;
		cout << "-----------------------------------" << endl;
	}
	

}

void printmenu(MENU* accArr[], int& accNum)
{
	cout << "[��ü �޴� ���]" << endl << endl;
	for (int i = 0; i < accNum; ++i) {
		cout << "�޴��� : ";
		accArr[i]->showaccMname();
		cout << "���� : ";
		accArr[i]->showaccCharge();
	}
}
