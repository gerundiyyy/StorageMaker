#pragma once
#include <vector>
#include <string>

#include "ProductManager.h"
#include "ProductStorage.h"
#include "UserManager.h"
#include "AuthManager.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "Product.h"

class App {
public:
    App(ProductManager& pdb,
        ProductStorage& pstorage,
        UserManager& um,
        AuthManager& auth,
        ConsolUI& ui,
        InputManager& in);

    void run();

private:
    ProductManager* db_;
    ProductStorage* storage_;
    UserManager* users_;
    AuthManager* auth_;
    ConsolUI* ui_;
    InputManager* in_;

    void appMenu();
    void printAll();
    void recordItem();
    void deleteItem();
    void changeItem();
    void simpleSearch();
    void advancedSearch();
    void searcher();
    ProductStorage::Filter buildFilterFromInput();
    std::vector<const Product*> searcherMenu(int choice);
    void stop();
    void showError(const std::string& msg);
    bool askContinueOrBack();
    bool requireAdmin();
};
