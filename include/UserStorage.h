#pragma once
#include "Storage.h"
#include "User.h"
#include "UserManager.h"
#include <vector>
#include <string>

class UserStorage : public Storage<User> {
public:
    UserStorage(ItemExtractor<User>& ex, InputManager& in, ConsolUI& ui)
        : Storage<User>(ex, in, ui) {}

    void loadItems(UserManager& db);
    void deleteItem() override;
    void changeItem(const User& item) override;
    void addItem(const User& item);
    const std::vector<User>& getItems() const { return Items; }

    std::vector<const User*> searchByUsername() const;
};
