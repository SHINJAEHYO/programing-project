#pragma once

class MENU
{
private:
	char* accMname; // 메뉴명
	int accCharge; //가격
public:
	MENU(char* Mname, int charge); //생성자
	MENU(const MENU& ref); //복사 생성자
	void showaccCharge() const; //가격 출력 함수
	void showaccMname() const; //메뉴명 출력 함수
	char *getaccMname() const; //메뉴명 반환하는 함수
	int getaccCharge() const; //가격 반환하는 함수
	~MENU(); //소멸자
};