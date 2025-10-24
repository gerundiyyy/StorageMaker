#pragma once
#include "IDataBaseManager.h"
#include "User.h"
#include <string>
#include <vector>

class UserManager : public IDataBaseManager<User> {
public:
    explicit UserManager(const std::string& filename = "data/users.txt")
        : filename_(filename) {}

    void initializeDB(const std::string& address) override { filename_ = address; load(); }
    void record(const User& item) override;              // append single user
    void record(const std::vector<User>& items) override; // overwrite all
    std::vector<User> readItem() override;               // read all users as vector
    void parseLine(User& item, const std::string& line) override; // not used externally
    User parseItem(const std::vector<std::string>& lines) override;

    void load(); // loads file into users_
    void save() const;

    const std::vector<User>& getUsers() const { return users_; }
    void addUser(const User& u);
    bool removeUserById(int id);
    User* findByUsername(const std::string& username);
    User* findById(int id);

private:
    std::vector<User> users_;
    std::string filename_;
};
