#pragma once
#ifndef STORAGE_MAKER_APP_H_
#define STORAGE_MAKER_APP_H_

#include <string>
#include <vector>

#include "ConsolUI.h"
#include "InputManager.h"
#include "DataBaseManager.h"
#include "Item.h"
#include "Storage.h"

class App {
public:
    App(DataBaseManager& db, Storage& storage, ConsolUI& ui, InputManager& in);
    void run();
    void appMenu();
    void stop();

private:
    DataBaseManager* db_;
    Storage* storage_;
    ConsolUI* ui_;
    InputManager* in_;

    // Actions
    void recordItem();
    void deleteItem();
    void changeItem();
    void printAll();

    // Search
    std::vector<const Item*> searcherMenu(int choice);
    void searcher();

    // Helpers
    void showError(const std::string& msg);
    bool askContinueOrBack();
};

#endif // STORAGE_MAKER_APP_H_
