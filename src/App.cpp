#include "App.h"

#include <windows.h>
#include <cstdlib>
#include <iostream>

App::App(DataBaseManager& db, Storage& storage, ConsolUI& ui, InputManager& in)
    : db_(&db), storage_(&storage), ui_(&ui), in_(&in) {}

void App::run() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    try {
        db_->createFile("data/product_data.txt");
        storage_->loadItems(*db_);
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при старте: ") + e.what());
    }
    appMenu();
}

void App::appMenu() {
    while (true) {
        system("cls");
        ui_->showAppMenu();
        ui_->showMessage("Введите пункт меню: ");
        int choice = in_->inputMenu();
        switch (choice) {
        case 1: printAll(); break;
        case 2: searcher(); break;
        case 3: recordItem(); break;
        case 4: deleteItem(); break;
        case 5: changeItem(); break;
        case 0: stop(); return;
        default: ui_->showMessage("Неверный пункт. Повторите."); break;
        }
    }
}

void App::recordItem() {
    system("cls");
    ui_->printAppHead("ЗАПИСЬ ТОВАРА");
    try {
        Item item = in_->inputFullItem();
        storage_->addItem(item);
        db_->recordItem(item);
        ui_->showMessage("Товар успешно добавлен.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при добавлении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::deleteItem() {
    system("cls");
    ui_->printAppHead("УДАЛЕНИЕ ТОВАРА");
    try {
        ui_->showMessage("Введите id товара, который хотите удалить");
        storage_->deleteItem(); // предполагается, что внутри спрашивается id
        db_->recordItem(storage_->getItems());
        ui_->showMessage("Товар успешно удалён.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при удалении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::changeItem() {
    system("cls");
    ui_->printAppHead("ИЗМЕНЕНИЕ ТОВАРА");
    try {
        ui_->showMessage("Введите новые данные о товаре:");
        Item item = in_->inputFullItem();
        ui_->showMessage("Введите id товара, который хотите переписать:");
        storage_->changeItem(item);
        db_->recordItem(storage_->getItems());
        ui_->showMessage("Товар успешно изменён.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при изменении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::printAll() {
    system("cls");
    ui_->printItem(storage_->getItems());
    askContinueOrBack();
}

std::vector<const Item*> App::searcherMenu(int choice) {
    switch (choice) {
    case 1: return storage_->searchById();
    case 2: return storage_->searchByName();
    case 3: return storage_->searchByQuantity();
    case 4: return storage_->searchByPrice();
    case 5: return storage_->searchByDate();
    case 6: return storage_->searchByRegisterdBy();
    default: return {};
    }
}

void App::searcher() {
    while (true) {
        system("cls");
        ui_->showSearcherMenu();
        ui_->showMessage("Выберите критерий поиска или 0 для возврата:");
        int choice = in_->inputMenu();
        if (choice == 0) return;
        ui_->showMessage("Введите зачение для поиска:");
        auto found = searcherMenu(choice);
        if (found.empty()) ui_->showMessage("Товар не найден.");
        else ui_->printItem(found);
        if (!askContinueOrBack()) return;
    }
}

void App::stop() {
    ui_->showMessage("Завершение работы программы...");
    std::exit(0);
}

void App::showError(const std::string& msg) {
    ui_->showMessage(std::string("Ошибка: ") + msg);
    askContinueOrBack();
}

bool App::askContinueOrBack() {
    ui_->showMessage("Нажмите любую клавишу для продолжения или 0 чтобы выйти в меню.");
    int maybe = in_->waitForKey(); // переиспользуем ввод меню: 0 = назад, любое другое = продолжить
    return maybe != 0;
}
