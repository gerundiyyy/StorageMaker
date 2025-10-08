#include "ConsolUI.h"

#include <iostream>
#include <string>
#include "InputManager.h"
#include "DataBaseManager.h"

using namespace std;
void ConsolUI::showMenu()
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
void ConsolUI::searchItem()
{
	cout << "=============Search=============" << endl;
	cout << "Введите id товара:";
}

void ConsolUI::showMessage(const string& message)
{
	cout << message << endl;
}