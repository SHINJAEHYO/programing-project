//#pragma once

class MENU;

void ShowMenu(void);
void updatemenu(MENU* accArr[], int& accNum); //메뉴추가함수
void deletemenu(MENU* accArr[], int& accNum); //메뉴삭제함수
void searchmenu(MENU* accArr[], int& accNum); //메뉴검색함수
void arraymenu(MENU* accArr[], int& accNum); //메뉴정렬함수
void paymenu(MENU* accArr[], int& accNum); //메뉴결제함수
void printmenu(MENU* accArr[], int& accNum); //메뉴출력함수
