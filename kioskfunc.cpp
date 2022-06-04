#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "kioskfunc.h"
#include "menu.h"
#include <algorithm> //sort함수 사용
#include <time.h> //시간 출력하기 위해 사용
#include <string> //find함수 사용
using namespace std;

const int NAME_LEN = 100; //메뉴명 최대 크기 100으로 설정


void ShowMenu(void)
{
	cout << endl;
	cout << "무엇을 하시겠습니까?" << endl;
	cout << "1. 메뉴추가" << endl;
	cout << "2. 메뉴삭제" << endl;
	cout << "3. 메뉴검색" << endl;
	cout << "4. 정렬" << endl;
	cout << "5. 결제" << endl;
	cout << "6. 총 메뉴출력" << endl;
}

void updatemenu(MENU* accArr[], int& accNum)
{
	char Mname[NAME_LEN];
	int charge;
	int Ufinal = 0; //등록, 취소 버튼
	
	cout << "[메뉴추가]" << endl << endl;
	cout << "메뉴명 : ";
	cin >> Mname;
	cout << "가격 : ";
	cin >> charge;
	
	cout << endl << "등록(1) / 취소(0) : ";
	cin >> Ufinal;

	if (Ufinal == 1) {
		accArr[accNum++] = new MENU(Mname, charge); //동적할당 사용하여 accArr포인터 배열이 클래스 객체 주소를 가리킴
	}
	else if (Ufinal == 0) {
		return;
	}
}

void deletemenu(MENU* accArr[], int& accNum)
{
	int dnum = 0; //삭제 메뉴 번호
	int Dfinal = 0; //삭제, 취소 버튼

	cout << "[삭제]" << endl << endl;
	for (int i = 0; i < accNum; ++i) { //넘버링한 메뉴명 출력
		cout << i + 1 << "."; //배열은 0부터 시작하므로 1을 더하여 1부터 넘버링
		accArr[i]->showaccMname();
	}
	cout << endl << "삭제할 메뉴의 번호를 입력하세요 : ";
	cin >> dnum;
	cout << endl << "삭제(1) / 취소(0) : ";
	cin >> Dfinal;
	if (Dfinal == 1)
	{
		for (int din = dnum - 1; din < accNum; din++) //1번은 accArr[0]이므로 -1
		{
			accArr[din] = accArr[din + 1]; //din(delete index number) 삭제할 인덱스 번호
		}
		accNum--; //포인터 배열 accArr이 하나 감소 했기 때문에 accNum 1감소
		return;
	}
	else if (Dfinal == 0)
	{
		return;
	}
}

void searchmenu(MENU* accArr[], int& accNum)
{
	cout << "[검색]" << endl << endl;
	string name[20]; //메뉴명 저장하는 배열(임의의 크기 20으로 지정)
	string fmenu; //검색할 메뉴명 저장 변수
	int NFnum = 0; //NOT FOUND number 

	for (int i = 0; i < accNum; i++) { //각 배열에 전체 메뉴명 하나씩 저장
		name[i] = accArr[i]->getaccMname(); 
	}

	cout << "메뉴명 검색(한 글자 이상) : ";
	cin >> fmenu;

	for (int k = 0; k < accNum; k++) { //메뉴명 제대로 입력 시 NFnum값 증가하여 while문 건너뜀
		if (name[k].find(fmenu) != string::npos) {
			NFnum++;
		}
	}
	
	while (NFnum == 0) //없는 메뉴명 입력 시 재검색 반복
	{
		cout << "찾으시는 메뉴가 없습니다. 다시 검색해주세요." << endl << endl;
		cout << "메뉴명 검색(한 글자 이상) : ";
		cin >> fmenu;
		for (int k = 0; k < accNum; k++) { //메뉴명 제대로 입력 시 while문 종료
			if (name[k].find(fmenu) != string::npos) {
				NFnum++;
			}
		}
	}

	if (NFnum != 0)
	{
		cout << endl << "메뉴명   " << "가격" << endl << endl;
		for (int j = 0; j < accNum; j++) {
			if (name[j].find(fmenu) != string::npos) { //fmenu에 입력된 글자를 name배열 전체를 반복하며 찾는다.
				cout << accArr[j]->getaccMname() << "  ";
				accArr[j]->showaccCharge();
			}
		}
	}
}

void arraymenu(MENU * accArr[], int& accNum)
{
	cout << "[정렬]" << endl << endl;

	MENU* temp; //accArr포인터 배열을 가리키는 포인터
	for (int j = 0; j < accNum; j++) //정렬
	{
		for (int i = 0; i < accNum; i++)
		{
			if (accArr[i]->getaccCharge() < accArr[i + 1]->getaccCharge()) //각 accArr포인터 배열이 가리키는 객체가 저장하고 있는 accCharge값을 비교한다.
			{                                                              //if문의 조건을 만족하면 두 포인터 배열이 저장하는 주소를 바꾼다.
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
	cout << "[결제]" << endl << endl;
	int index = 0; //index번호
	int paysum = 0; //총 구매 금액 저장 변수
	int k = 1; //k가 0이면 무한루프 종료
	int loop = 0; //while문 반복수
	int ordhis[20] = {}; //최대 고를 수 있는 메뉴 19개

	int YN = 0; //영수증 출력하기 위한 입력값(Yes or No)
	static int ordNum = 0; //주문번호(함수 종료 후에 값이 유지되도록 정적변수 선언)

	time_t timer = time(NULL);

	struct tm* t = localtime(&timer);
	struct tm {
		int tm_sec; //초
		int tm_min; //분
		int tm_hour; //시간
		int tm_mday; //일
		int tm_mon; //월
		int tm_wday; //요일
		int tm_year; //년
	};
	
	for (int i = 0; i < accNum; ++i) {
		cout << i + 1 << ".";
		accArr[i]->showaccMname();
		accArr[i]->showaccCharge();
		cout << endl;
	}
	cout << "구매하실 메뉴의 번호를 입력하세요." << endl;

	while (k != 0)
	{
		cout << "메뉴 번호 : ";
		cin >> index; //구매할 메뉴 번호
		paysum += accArr[index - 1]->getaccCharge(); //메뉴 고를 때마다 가격 더하여 저장
		cout << "추가 구매 시 1번 / 끝내려면 0번을 입력하세요 : ";
		ordhis[loop] = index - 1; //고른 메뉴 번호 - 1 값을 저장하는 배열(예:1번 메뉴 고르면 ordhis[0] = 0)
		loop++;                   //loop는 0부터 while문 반복 때마다 1씩 증가하여 각각의 배열에 고른메뉴번호 - 1 값 저장
		cin >> k;
	}
	
	cout << "총 결제 금액 : " << paysum << "원\n" << endl;
	ordNum++; //주문번호 증가
	cout << "영수증을 출력하시겠습니까? (예 = 1 / 아니오 = 0)" << " : ";
	cin >> YN;

	if (YN == 1)
	{
		cout << endl << "-----------------------------------" << endl;
		cout << "KIOSK RECEIPT\n";
		cout << "-----------------------------------" << endl;
		cout << "주문번호 : " << ordNum << endl; //주문번호 : (번호)
		cout << "-----------------------------------" << endl;                      //년도는 1900년부터, 월은 0부터 시작
		cout << t->tm_year + 1900 << " - " << t->tm_mon + 1 << " - " << t->tm_mday; //년도 - 월 - 일(요일) 시간 : 분 : 초
		if (t->tm_wday == 0)                                                        //요일은 숫자로 반환 0 = 일요일, 1 = 월요일 ... 6 = 토요일
		{
			cout << "(일) ";
		}
		else if (t->tm_wday == 1)
		{
			cout << "(월) ";
		}
		else if (t->tm_wday == 2)
		{
			cout << "(화) ";
		}
		else if (t->tm_wday == 3)
		{
			cout << "(수) ";
		}
		else if (t->tm_wday == 4)
		{
			cout << "(목) ";
		}
		else if (t->tm_wday == 5)
		{
			cout << "(금) ";
		}
		else if (t->tm_wday == 6)
		{
			cout << "(토) ";
		}
		cout << t->tm_hour << " : " << t->tm_min << " : " << t->tm_sec << endl; //시간 출력
		cout << "-----------------------------------" << endl;
		cout << "구매내역\n" << "메뉴명   " << "가격\n" << endl;
		for (int j = 0; j < loop; j++)
		{
			cout << accArr[ordhis[j]]->getaccMname() << "  " << accArr[ordhis[j]]->getaccCharge() << "원" << endl;
		} //고른 메뉴 번호-1 값을 저장하는 배열을 사용하여 각 배열에 저장된 값을 accArr 인덱스에 넣어 고른 메뉴들의 메뉴명과 가격을 출력
		cout << "-----------------------------------" << endl;
		cout << "결제 금액 : " << paysum << "원" << endl;
		cout << "-----------------------------------" << endl;
	}
	

}

void printmenu(MENU* accArr[], int& accNum)
{
	cout << "[전체 메뉴 출력]" << endl << endl;
	for (int i = 0; i < accNum; ++i) {
		cout << "메뉴명 : ";
		accArr[i]->showaccMname();
		cout << "가격 : ";
		accArr[i]->showaccCharge();
	}
}
