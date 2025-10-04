#include <iostream>
#include <string>
#include <windows.h>;
#include <stdlib.h>

#include "App.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "DataBaseManager.h"
#include "ObjectBD.h"
#include "Storage.h"

void App::run()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	storage.loadFromDB(bd);
}

void App::record()
{
	ObjectBD obj = in.inputFullObject();

	storage.addItem(obj);
	bd.recordObjectBD(obj);
}

void App::printAll()
{
	system("cls");
	for (ObjectBD obj : storage.getItems())
	{
		obj.print();
	}
}

void App::callMenu()
{
	ui.showMenu();
	cout << "¬ведите пункт меню: ";
	switch (in.inputMenu())
	{
	case 1:
		record();
		break;
	case 4:
		printAll();
		break;
	}
}

