#include "App.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdlib>
#include <iostream>

#include "ProductManager.h"
#include "ProductStorage.h"
#include "Product.h"

App::App(ProductManager& db, ProductStorage& storage, ConsolUI& ui, InputManager& in)
    : db_(&db), storage_(&storage), ui_(&ui), in_(&in) {}

void App::run() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    try {
        db_->initializeDB("data/product_data.txt");
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
        Product item = in_->inputFullProduct();
        storage_->addItem(item);
        db_->record(item);
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
        storage_->deleteItem();
        db_->record(storage_->getItems());
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
        Product item = in_->inputFullProduct();
        ui_->showMessage("Введите id товара, который хотите переписать:");
        storage_->changeItem(item);
        db_->record(storage_->getItems());
        ui_->showMessage("Товар успешно изменён.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при изменении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::printAll() {
    system("cls");
    ui_->printProduct(storage_->getItems());
    askContinueOrBack();
}

std::vector<const Product*> App::searcherMenu(int choice) {
    switch (choice) {
    case 1: return storage_->searchById();
    case 2: return storage_->searchByName();
    case 3: return storage_->searchByQuantity();
    case 4: return storage_->searchByPrice();
    case 5: return storage_->searchByDate();
    case 6: return storage_->searchByRegisteredBy();
    default: return {};
    }
}

void App::searcher() {
    while (true) {
        system("cls");
        ui_->showSearcherMenu();
        ui_->showMessage("Выберите критерий поиска или 0 для возврата:");
        ui_->showMessage("1 - Простой поиск по полю\n2 - Продвинутый фильтр (несколько условий)");
        int mode = in_->inputMenu();
        if (mode == 0) return;
        if (mode == 1) {
            ui_->showMessage("Выберите поле для простого поиска:");
            int choice = in_->inputMenu();
            if (choice == 0) continue;
            ui_->showMessage("Введите значение для поиска:");
            auto found = searcherMenu(choice);
            if (found.empty()) ui_->showMessage("Товар не найден.");
            else ui_->printProduct(found);
            if (!askContinueOrBack()) return;
        }
        else if (mode == 2) {
            ProductStorage::Filter f;
            ui_->showMessage("Введите минимальное количество месяцев на складе (или 0 чтобы пропустить):");
            int months = in_->inputNumberAllowZero();
            if (months > 0) f.minMonthsAgo = months;

            ui_->showMessage("Введите минимальную цену (или 0 чтобы пропустить):");
            double price = in_->inputDoubleAllowZero();
            if (price > 0.0) f.minPrice = price;

            ui_->showMessage("Введите минимальное количество (или 0 чтобы пропустить):");
            int qty = in_->inputNumberAllowZero();
            if (qty > 0) f.minQuantity = qty;

            ui_->showMessage("Введите часть названия для поиска (пустая строка чтобы пропустить):");
            std::string namePart = in_->inputOptionalString();
            if (!namePart.empty()) f.nameContains = namePart;

            ui_->showMessage("Введите часть ФИО регистратора (пустая строка чтобы пропустить):");
            std::string reg = in_->inputOptionalString();
            if (!reg.empty()) f.registeredBy = reg;

            ui_->showMessage("По какому полю отсортировать результат? (id,name,quantity,price,date,registeredBy или пусто):");
            std::string key = in_->inputOptionalString();
            if (!key.empty()) {
                f.sortKey = key;
                ui_->showMessage("Направление сортировки: 1 - по возрастанию, 2 - по убыванию");
                int dir = in_->inputMenu();
                f.ascending = (dir != 2);
            }

            auto result = storage_->filter(f);
            if (result.empty()) ui_->showMessage("Ничего не найдено по заданным критериям.");
            else ui_->printProduct(result);
            if (!askContinueOrBack()) return;
        }
        else {
            ui_->showMessage("Неверный режим поиска.");
        }
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
    int maybe = in_->waitForKey();
    return maybe != 0;
}
