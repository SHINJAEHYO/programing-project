#include <iostream>
#include "menu.h"
#include "kioskfunc.h"
using namespace std;

const int TOTAL_ACC = 100; //MENUŬ������ ����Ű�� �迭 ũ�� 100���� ����
enum {UPDATE = 1, DELETE, SEARCH, ARRAY, PAY, SHOW}; //�տ������� ������� ��ȣ 1, 2, 3, 4, 5, 6 �Ҵ�
int main(void)
{
	int choice;
	MENU * accArr[TOTAL_ACC];
	int accNum = 0;
	while (true)
	{
		ShowMenu();
		cout << endl << "��ȣ �Է� : ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case UPDATE:
			updatemenu(accArr, accNum);
			break;
		case DELETE:
			deletemenu(accArr, accNum);
			break;
		case SEARCH:
			searchmenu(accArr, accNum);
			break;
		case ARRAY:
			arraymenu(accArr, accNum);
			break;
		case PAY:
			paymenu(accArr, accNum);
			break;
		case SHOW:
			printmenu(accArr, accNum);
			break;
		default:
			cout << "�߸��� �޴� ����" << endl;
			break;
		}
	}
	return 0;
}
