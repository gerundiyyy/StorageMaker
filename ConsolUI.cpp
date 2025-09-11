#include <iostream>
#include <string>
#include "ConsolUI.h"
#include "ConsolInput.h"

using namespace std;
void ConsolUI::coutMenu()
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

void ConsolUI::showMenu() 
{
	ConsolInput Cinput;
	coutMenu();
	cout << "�������� ��������: ";
	while (true)
	{
		string number;
		cin >> number;
		if (Cinput.isInt(number))
		{
			switch (Cinput.toInt(number))
			{
			case 1:
				system("cls");
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "����� ������ ��� ������" << endl;
				Cinput.inputFullObject();
				system("pause");
				break;
			case 2:
				cout << "�������� �������!" << endl;
				break;
			case 3:
				cout << "�������� �������!" << endl;
				break;
			case 4:
				cout << "�������� �������!" << endl;
				break;
			case 5:
				cout << "�������� �������!" << endl;
				break;
			case 0: 
				cout << "�������� �������!" << endl;
				break;
			default:
				cout << "�������� �����! ������� �����: ";
				break;
			}
		}
		if (Cinput.toInt(number) == 0) break;
	}
}