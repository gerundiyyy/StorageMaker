#pragma once

#include "UserManager.h"
#include "ConsolUI.h"
#include "InputManager.h"

class AuthManager {
public:
    AuthManager(UserManager& um, ConsolUI& ui, InputManager& in)
        : users_(&um), ui_(&ui), in_(&in) {}

    bool login();
    void logout() { currentUser_ = nullptr; }
    bool isLogged() const { return currentUser_ != nullptr; }
    const User* currentUser() const { return currentUser_; }
    bool currentIsAdmin() const { return currentUser_ && currentUser_->getRole() == User::Role::Admin; }

    // Требует входа; возвращает true если пользователь вошёл, false при отмене
    bool requireLogin();

    // Проверит права и откроет админ-панель при наличии прав
    void ensureAdminPanel();

private:
    UserManager* users_;
    ConsolUI* ui_;
    InputManager* in_;
    User* currentUser_ = nullptr;

    std::string hashPassword(const std::string& pass) const;
    bool checkPassword(const User& u, const std::string& pass) const;

    // admin helpers
    void adminPanel();
    void adminShowUsers() const;
    void adminAddUser();
    void adminDeleteUser();
    void adminChangeRole();

    // credential helpers
    User* findUserByLoginOrNotify(const std::string& login);
};
