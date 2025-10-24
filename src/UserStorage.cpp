#include "UserStorage.h"
#include <algorithm>

void UserStorage::loadItems(UserManager& db) {
    Items = db.readItem();
}

void UserStorage::addItem(const User& item) {
    Items.push_back(item);
}

void UserStorage::deleteItem() {
    ui->showMessage("Введите id пользователя для удаления:");
    int idx = singleSearchById();
    if (idx >= 0) {
        Items.erase(Items.begin() + idx);
        ui->showMessage("Пользователь удалён.");
    }
    else ui->showMessage("Пользователь не найден.");
}

void UserStorage::changeItem(const User& item) {
    ui->showMessage("Введите id пользователя для изменения:");
    int idx = singleSearchById();
    if (idx >= 0) {
        Items[idx] = item;
        ui->showMessage("Пользователь изменён.");
    }
    else ui->showMessage("Пользователь не найден.");
}

std::vector<const User*> UserStorage::searchByUsername() const {
    return searchBy<std::string>("", [](const User& u) { return u.getName(); });
}
