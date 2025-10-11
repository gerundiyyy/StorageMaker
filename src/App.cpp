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
}
void App::searcher()
{
	system("cls");
	ui->showSearcherMenu();
	int choice = in->inputMenu();
	const auto foundList = searcherMenu(choice);

	static const std::unordered_map <int, std::vector<const Item*>(Storage::*)()> menuActions
	{
		{1, &Storage::searchById},
		{2, &Storage::searchByName},
		{3, &Storage::searchByQuantity},
		{4, &Storage::searchByPrice},
		{5, &Storage::searchByDate},
		{6, &Storage::searchByRegisterdBy},
	};
	auto it = menuActions.find(choice);
	if (it != menuActions.end()) {
		(this->*(it->second))();
	}

	if (foundList.empty()) {
		ui->showMessage("Товар не найден.");
		return;
	}
	for (size_t i = 0; i < foundList.size(); ++i)
		foundList[i]->print();
}

void App::stop() {
	ui->showMessage("Завершение работы программы...");
	std::exit(0);
}
