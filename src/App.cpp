#include "App.h"

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "ConsolUI.h"
#include "InputManager.h"
#include "DataBaseManager.h"
#include "Item.h"
#include "Storage.h"

void App::run()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	storage.loadItems(bd);
}

void App::record()
{
	Item item = in.inputFullItem();

	storage.addItem(item);
	bd.recordItem(item);
}

void App::printAll()
{
	system("cls");
	for (Item item : storage.getItems())
	{
		item.print();
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

