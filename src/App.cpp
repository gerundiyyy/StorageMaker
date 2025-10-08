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

	storage.loadItems(db);
}
void App::record()
{
	system("cls");
	Item item = in.inputFullItem();
	storage.addItem(item);
	db.recordItem(item);
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
	ui.showMessage("Введите пункт меню: ");
	switch (in.inputMenu())
	{
	case 1:
		record();
		break;
	case 4:
		printAll();
		break;
	case 5:
		search();
		break;
	default:

		break;
	}
}
void App::search()
{
	system("cls");
	ui.searchItem();
	int id = in.inputItemId();
	const Item* found = storage.searchForId(id);

	if (found) {
		found->print(); // передаём найденный объект
	}
	else {
		ui.showMessage("Товар с таким ID не найден.");
	}
}

