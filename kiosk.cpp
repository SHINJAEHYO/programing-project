#include <iostream>
#include "menu.h"
#include "kioskfunc.h"
using namespace std;

const int TOTAL_ACC = 100; //MENU클래스를 가리키는 배열 크기 100으로 설정
enum {UPDATE = 1, DELETE, SEARCH, ARRAY, PAY, SHOW}; //앞에서부터 순서대로 번호 1, 2, 3, 4, 5, 6 할당
int main(void)
{
	int choice;
	MENU * accArr[TOTAL_ACC];
	int accNum = 0;
	while (true)
	{
		ShowMenu();
		cout << endl << "번호 입력 : ";
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
			cout << "잘못된 메뉴 선택" << endl;
			break;
		}
	}
	return 0;
}
