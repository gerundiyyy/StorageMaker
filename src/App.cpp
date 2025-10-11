#include "App.h"

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unordered_map>

#include "ConsolUI.h"
#include "InputManager.h"
#include "DataBaseManager.h"
#include "Item.h"
#include "Storage.h"
#include "ItemExtractor.h"

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
void App::appMenu()
{
	ui.showMenu();
	ui.showMessage("������� ����� ����: ");
	int choice = in.inputMenu();

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
const auto App::searcherMenu(int choice)
{
	switch(choice)
	{
	case 1:
	{
		ui.showMessage("����� �� ID");
		const auto needle = in.inputItemId();
		return storage.searchBy(needle, ex.byId());
		break;
	}
	case 2:
	{
		ui.showMessage("����� �� ��������");
		const auto needle = in.inputItemName();
		return storage.searchBy(needle, ex.byName());
		break;
	}
	case 3:
	{
		ui.showMessage("����� �� ����������");
		const auto needle = in.inputItemQuantity();
		return storage.searchBy(needle, ex.byQuantity());
		break;
	}
	case 4:
	{
		ui.showMessage("����� �� ����");
		const auto needle = in.inputItemPrice();
		return storage.searchBy(needle, ex.byPrice());
		break;
	}
	case 5:
	{
		ui.showMessage("����� �� ���� ����������");
		const auto needle = in.inputItemDate();
		return storage.searchBy(needle, ex.byDate());
		break;
	}
	case 6:
	{
		ui.showMessage("����� �� ����� ������������");
		const auto needle = in.inputItemRegisteredBy();
		return storage.searchBy(needle, ex.byRegisteredBy());
		break;
	}
	case 0:
	{
		appMenu();
		break;
	}
	/*default:
		ui.showMessage("�������� ����� ����!");
		break;*/
	}
}
void App::searcher()
{
	system("cls");
	ui.searchItem();
	int choice = in.inputMenu();
	const auto foundList = searcherMenu(choice);
	if (foundList.empty()) {
		ui.showMessage("����� �� ������.");
		return;
	}
	for (size_t i = 0; i < foundList.size(); ++i)
		foundList[i]->print();
}

void App::stop() {
	ui.showMessage("���������� ������ ���������...");
	std::exit(0);
}
