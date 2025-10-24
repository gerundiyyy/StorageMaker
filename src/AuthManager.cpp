#include "AuthManager.h"
#include <functional>
#include <string>
#include <iostream>

std::string AuthManager::hashPassword(const std::string& pass) const {
    std::hash<std::string> h;
    return std::to_string(h(pass));
}

bool AuthManager::checkPassword(const User& u, const std::string& pass) const {
    return u.getPasswordHash() == hashPassword(pass);
}

User* AuthManager::findUserByLoginOrNotify(const std::string& login) {
    User* u = users_->findByUsername(login);
    if (!u) ui_->showMessage("Пользователь не найден.");
    return u;
}

bool AuthManager::login() {
    ui_->showMessage("Вход. Введите имя пользователя (пусто чтобы отменить):");
    std::string login = in_->inputOptionalString();
    if (login.empty()) { ui_->showMessage("Вход отменён."); return false; }

    User* u = findUserByLoginOrNotify(login);
    if (!u) return false;

    ui_->showMessage("Введите пароль:");
    std::string pass = in_->inputOptionalString();
    if (!checkPassword(*u, pass)) { ui_->showMessage("Неверный пароль."); return false; }

    currentUser_ = u;
    ui_->showMessage(std::string("Вход успешен. ") + u->getName());
    return true;
}

bool AuthManager::requireLogin() {
    while (true) {
        ui_->showMessage("Требуется вход в систему. Введите имя пользователя (пусто чтобы отменить):");
        std::string login = in_->inputOptionalString();
        if (login.empty()) return false;

        User* u = findUserByLoginOrNotify(login);
        if (!u) continue;

        ui_->showMessage("Введите пароль:");
        std::string pass = in_->inputOptionalString();
        if (checkPassword(*u, pass)) {
            currentUser_ = u;
            return true;
        }

        ui_->showMessage("Неверный пароль. Попробуйте снова или оставьте логин пустым чтобы отменить.");
    }
}

void AuthManager::ensureAdminPanel() {
    if (!currentUser_) {
        ui_->showMessage("Требуется вход.");
        if (!requireLogin()) return;
    }
    if (!currentIsAdmin()) {
        ui_->showMessage("У вас нет прав администратора.");
        return;
    }
    adminPanel();
}

void AuthManager::adminPanel() {
    while (true) {
        system("cls");
        ui_->showAdminMenu();
        int choice = in_->inputMenu();
        if (choice == 0) break;

        switch (choice) {
        case 1: adminShowUsers(); in_->waitForKey(); break;
        case 2: adminAddUser(); break;
        case 3: adminDeleteUser(); break;
        case 4: adminChangeRole(); break;
        default: ui_->showMessage("Неверный пункт."); break;
        }
    }
}

void AuthManager::adminShowUsers() const {
    system("cls");
    const auto& list = users_->getUsers();
    ui_->printUsers(list);
}

void AuthManager::adminAddUser() {
    system("cls");
    ui_->showMessage("Добавление пользователя:");
    ui_->showMessage("Введите id:");
    int id = in_->inputProductId();
    ui_->showMessage("Введите username:");
    std::string username = in_->inputOptionalString();
    ui_->showMessage("Введите пароль:");
    std::string pass = in_->inputOptionalString();
    std::string reg = currentUser_ ? currentUser_->getName() : std::string("system");

    User u(id, username, hashPassword(pass), User::Role::User, reg, "");
    users_->addUser(u);
    users_->save();
    ui_->showMessage("Пользователь добавлен.");
}

void AuthManager::adminDeleteUser() {
    system("cls");
    ui_->showMessage("Введите id для удаления:");
    int id = in_->inputProductId();
    if (users_->removeUserById(id)) {
        users_->save();
        ui_->showMessage("Удалено.");
    }
    else {
        ui_->showMessage("Не найдено.");
    }
}

void AuthManager::adminChangeRole() {
    system("cls");
    ui_->showMessage("Введите id пользователя для изменения прав:");
    int id = in_->inputProductId();
    User* u = users_->findById(id);
    if (!u) { ui_->showMessage("Не найдено."); return; }

    ui_->showMessage("1 - сделать админом, 2 - снять админ");
    int c = in_->inputMenu();
    u->setRole(c == 1 ? User::Role::Admin : User::Role::User);
    users_->save();
    ui_->showMessage("Роль изменена.");
}
