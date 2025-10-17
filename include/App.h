#pragma once
#ifndef STORAGE_MAKER_APP_H_
#define STORAGE_MAKER_APP_H_

#include <string>
#include <vector>

#include "ConsolUI.h"
#include "InputManager.h"
#include "ProductManager.h"
#include "Product.h"
#include "ProductStorage.h"

class App {
public:
    App(ProductManager& db, ProductStorage& storage, ConsolUI& ui, InputManager& in);
    void run();
    void appMenu();
    void stop();

private:
    ProductManager* db_;
    ProductStorage* storage_;
    ConsolUI* ui_;
    InputManager* in_;

    // Actions
    void recordItem();
    void deleteItem();
    void changeItem();
    void printAll();

    // Search
    std::vector<const Product*> searcherMenu(int choice);
    void searcher();

    // Helpers
    void showError(const std::string& msg);
    bool askContinueOrBack();
};

#endif // STORAGE_MAKER_APP_H_
