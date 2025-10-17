#pragma once
#include "Entity.h"
#include <string>
class User : public Entity
{
private:
	std::string password;
	std::string passwordHash;
	bool isAdmin;
public:
	User(int id, std::string& name, std::string& login, bool isAdmin = false);
	const std::string& getLogin() const;
	bool admin() const;
	void setAdmin(bool v);
	bool checkPassword(const std::string& plain) const;
};

