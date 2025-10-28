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
    App();

    void run();

private:
    ConsolUI ui_;
    InputManager in_;
    ItemExtractor<Product> productExtractor_;
    ProductManager db_;
    UserManager users_;
    ProductStorage storage_;
    AuthManager auth_;

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
