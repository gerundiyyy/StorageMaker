#include "ConsolUI.h"

#include <iostream>
#include <string>
#include "InputManager.h"
#include "DataBaseManager.h"

using namespace std;
void ConsolUI::showMenu()
{
	cout << "����:" << endl;
	cout << "(1) �������� ������ � ��" << endl;
	cout << "(2) �������� ������ � ��" << endl;
	cout << "(3) ������� ������ �� ��" << endl;
	cout << "(4) ������� ��� ������� ��" << endl;
	cout << "(5) ����� � ����������" << endl;
	cout << "(0) ����� �� ���������" << endl;
	cout << endl;
}
void ConsolUI::searchItem()
{
	cout << "=============Search=============" << endl;
	cout << "������� id ������:";
}

void ConsolUI::showMessage(const string& message)
{
	cout << message << endl;
}