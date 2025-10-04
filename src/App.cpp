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

	storage.loadFromDB(db);
}

void App::record()
{
	int id = db.getLastId()+1;
	system("cls");
	ObjectBD obj = in.inputFullObject(id);
	storage.addItem(obj);
	db.recordObjectBD(obj,id);
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
	while (true)
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
}

