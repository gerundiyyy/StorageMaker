#pragma once
#include "IDataBaseManager.h"
#include <string>
#include <vector>
#include "User.h"
class UserManager : public IDataBaseManager<User>
{
public:
	void initializeDB(const std::string& address) override;
	void record(const User& item) override;
	void record(const std::vector<User>& items) override;
	std::vector <User> readItem() override;
	void parseLine(User& item, const std::string& line) override;
	User parseItem(const std::vector<std::string>& lines) override;
};

