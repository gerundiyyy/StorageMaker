#include "App.h"

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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

	storage->loadItems(*db);
}
void App::record()
{
	system("cls");
	Item item = in->inputFullItem();
	storage->addItem(item);
	db->recordItem(item);
}
void App::printAll()
{
	system("cls");
	for (Item item : storage->getItems())
	{
		item.print();
	}
}
void App::appMenu()
{
	bool isContinue;
	do {
		system("cls");
		ui->showAppMenu();
		ui->showMessage("Введите пункт меню: ");
		int choice = in->inputMenu();
		static const std::unordered_map <int, void(App::*)()> menuActions
		{
			{1, &App::printAll},
			{2, &App::searcher},
			{3, &App::record},
			{0, &App::stop},
		};
		auto it = menuActions.find(choice);
		if (it != menuActions.end()) {
			(this->*(it->second))();
		}
		isContinue = in->isContinue();
	} while (&isContinue);	
}

const auto App::searcherMenu(int choice)
{
	switch(choice)
	{
		case 1: return storage->searchById();
		case 2: return storage->searchByName();
		case 3: return storage->searchByQuantity();
		case 4: return storage->searchByPrice();
		case 5: return storage->searchByDate();
		case 6: return storage->searchByRegisterdBy();
		case 0: appMenu();
	}
}

void App::searcher()
{
	bool isContinue;
	do{
		system("cls");
		ui->showSearcherMenu();
		int choice = in->inputMenu();
		const auto foundList = searcherMenu(choice);

		if (foundList.empty()) {
			ui->showMessage("Товар не найден.");
			return;
		}
		for (size_t i = 0; i < foundList.size(); ++i)
			foundList[i]->print();
		isContinue = in->isContinue();
	} while (&isContinue);
}

void App::stop() {
	ui->showMessage("Завершение работы программы...");
	std::exit(0);
}
