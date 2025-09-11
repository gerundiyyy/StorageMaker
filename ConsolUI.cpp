#include <iostream>
#include <string>
#include "ConsolUI.h"
#include "ConsolInput.h"

using namespace std;
void ConsolUI::coutMenu()
{
	cout << "Меню:" << endl;
	cout << "(1) Записать объект в БД" << endl;
	cout << "(2) Изменить объект в БД" << endl;
	cout << "(3) Удалить объект из БД" << endl;
	cout << "(4) Вывести все объекты БД" << endl;
	cout << "(5) Поиск и сортировка" << endl;
	cout << "(0) Выйти из программы" << endl;
	cout << endl;
}

void ConsolUI::showMenu() 
{
	ConsolInput Cinput;
	coutMenu();
	cout << "Выберите действие: ";
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
				cout << "Введём объект для записи" << endl;
				Cinput.inputFullObject();
				system("pause");
				break;
			case 2:
				cout << "Выполняю задание!" << endl;
				break;
			case 3:
				cout << "Выполняю задание!" << endl;
				break;
			case 4:
				cout << "Выполняю задание!" << endl;
				break;
			case 5:
				cout << "Выполняю задание!" << endl;
				break;
			case 0: 
				cout << "Выполняю задание!" << endl;
				break;
			default:
				cout << "Неверный выбор! Введите номер: ";
				break;
			}
		}
		if (Cinput.toInt(number) == 0) break;
	}
}