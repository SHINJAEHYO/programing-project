#pragma once

class MENU
{
private:
	char* accMname; // �޴���
	int accCharge; //����
public:
	MENU(char* Mname, int charge); //������
	MENU(const MENU& ref); //���� ������
	void showaccCharge() const; //���� ��� �Լ�
	void showaccMname() const; //�޴��� ��� �Լ�
	char *getaccMname() const; //�޴��� ��ȯ�ϴ� �Լ�
	int getaccCharge() const; //���� ��ȯ�ϴ� �Լ�
	~MENU(); //�Ҹ���
};