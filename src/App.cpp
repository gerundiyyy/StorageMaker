#include "App.h"

#include <windows.h>

#include <cstdlib>
#include <iostream>

App::App()
    : ui_()                         
    , in_(ui_)                              
    , productExtractor_()                        
    , db_()                                
    , users_("data/users.txt")                
    , storage_(productExtractor_, in_, ui_)    
    , auth_(users_, ui_, in_)
{
}

void App::run() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    try {
        db_.initializeDB("data/product_data.txt");
        users_.load();                         
        storage_.loadItems(db_);
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при старте: ") + e.what());
        return;
    }

    // Требуем входа перед работой
    if (!auth_.requireLogin()) {
        ui_.showMessage("Вход не выполнен. Завершение работы.");
        return;
    }

    appMenu();
}

bool App::requireAdmin() {
    if (auth_.currentIsAdmin()) return true;
    ui_.showMessage("Операция требует прав администратора. Войдите как админ.");
    return auth_.login();
}

void App::appMenu() {
    while (true) {
        system("cls");
        ui_.showAppMenu();
        ui_.showMessage("Введите пункт меню: ");
        int choice = in_.inputMenu();

        switch (choice) {
        case 1: printAll(); break;
        case 2: searcher(); break;
        case 3: if (requireAdmin()) recordItem(); break;
        case 4: if (requireAdmin()) deleteItem(); break;
        case 5: if (requireAdmin()) changeItem(); break;
        case 6: auth_.ensureAdminPanel(); break;
        case 7:
            if (auth_.isLogged()) {
                auth_.logout();
                ui_.showMessage("Вы вышли из системы.");
            }
            else auth_.login();
            break;
        case 0: stop(); return;
        default: ui_.showMessage("Неверный пункт. Повторите."); break;
        }
    }
}

void App::recordItem() {
    system("cls");
    ui_.printAppHead("ЗАПИСЬ ТОВАРА");
    try {
        Product item = in_.inputFullProduct();
        storage_.addItem(item);
        db_.record(item);
        ui_.showMessage("Товар успешно добавлен.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при добавлении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::deleteItem() {
    system("cls");
    ui_.printAppHead("УДАЛЕНИЕ ТОВАРА");
    try {
        ui_.showMessage("Введите id товара, который хотите удалить");
        storage_.deleteItem();
        db_.record(storage_.getItems());
        ui_.showMessage("Товар успешно удалён.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при удалении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::changeItem() {
    system("cls");
    ui_.printAppHead("ИЗМЕНЕНИЕ ТОВАРА");
    try {
        ui_.showMessage("Введите новые данные о товаре:");
        Product item = in_.inputFullProduct();
        ui_.showMessage("Введите id товара, который хотите переписать:");
        storage_.changeItem(item);
        db_.record(storage_.getItems());
        ui_.showMessage("Товар успешно изменён.");
    }
    catch (const std::exception& e) {
        showError(std::string("Ошибка при изменении: ") + e.what());
    }
    if (!askContinueOrBack()) return;
}

void App::printAll() {
    system("cls");
    ui_.printProduct(storage_.getItems());
    askContinueOrBack();
}

std::vector<const Product*> App::searcherMenu(int choice) {
    switch (choice) {
    case 1: return storage_.searchById();
    case 2: return storage_.searchByName();
    case 3: return storage_.searchByQuantity();
    case 4: return storage_.searchByPrice();
    case 5: return storage_.searchByDate();
    case 6: return storage_.searchByRegisteredBy();
    default: return {};
    }
}

void App::searcher() {
    while (true) {
        system("cls");
        ui_.showSearcherMenu();
        ui_.showMessage("Выберите критерий поиска или 0 для возврата:");
        ui_.showMessage("1 - Простой поиск по полю\n2 - Продвинутый фильтр (несколько условий)");
        int mode = in_.inputMenu();
        if (mode == 0) return;

        if (mode == 1) {
            simpleSearch();
            if (!askContinueOrBack()) return;
        }
        else if (mode == 2) {
            advancedSearch();
            if (!askContinueOrBack()) return;
        }
        else {
            ui_.showMessage("Неверный режим поиска.");
        }
    }
}

void App::simpleSearch() {
    ui_.showMessage("Выберите поле для простого поиска (0 чтобы отменить):");
    int choice = in_.inputMenu();
    if (choice == 0) return;

    ui_.showMessage("Введите значение для поиска:");
    auto found = searcherMenu(choice);
    if (found.empty()) ui_.showMessage("Товар не найден.");
    else ui_.printProduct(found);
}

void App::advancedSearch() {
    ProductStorage::Filter f = buildFilterFromInput();

    auto result = storage_.filter(f);
    if (result.empty()) ui_.showMessage("Ничего не найдено по заданным критериям.");
    else ui_.printProduct(result);
}

ProductStorage::Filter App::buildFilterFromInput() {
    ProductStorage::Filter f;

    ui_.showMessage("Введите минимальное количество месяцев на складе (или 0 чтобы пропустить):");
    if (int months = in_.inputNumberAllowZero(); months > 0) f.minMonthsAgo = months;

    ui_.showMessage("Введите минимальную цену (или 0 чтобы пропустить):");
    if (double price = in_.inputDoubleAllowZero(); price > 0.0) f.minPrice = price;

    ui_.showMessage("Введите минимальное количество (или 0 чтобы пропустить):");
    if (int qty = in_.inputNumberAllowZero(); qty > 0) f.minQuantity = qty;

    ui_.showMessage("Введите часть названия для поиска (пустая строка чтобы пропустить):");
    if (std::string s = in_.inputOptionalString(); !s.empty()) f.nameContains = std::move(s);

    ui_.showMessage("Введите часть ФИО регистратора (пустая строка чтобы пропустить):");
    if (std::string s = in_.inputOptionalString(); !s.empty()) f.registeredBy = std::move(s);

    ui_.showMessage("По какому полю отсортировать результат? (id,name,quantity,price,date,registeredBy или пусто):");
    if (std::string key = in_.inputOptionalString(); !key.empty()) {
        f.sortKey = std::move(key);
        ui_.showMessage("Направление сортировки: 1 - по возрастанию, 2 - по убыванию");
        int dir = in_.inputMenu();
        f.ascending = (dir != 2);
    }

    return f;
}

void App::stop() {
    ui_.showMessage("Завершение работы программы...");
    std::exit(0);
}

void App::showError(const std::string& msg) {
    ui_.showMessage(std::string("Ошибка: ") + msg);
    askContinueOrBack();
}

bool App::askContinueOrBack() {
    ui_.showMessage("Нажмите любую клавишу для продолжения или 0 чтобы выйти в меню.");
    int maybe = in_.waitForKey();
    return maybe != 0;
}
