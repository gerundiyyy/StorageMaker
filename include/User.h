#pragma once
#include "Entity.h"
#include <string>

class User : public Entity {
public:
    enum class Role { User, Admin };

    User() = default;
    User(int id, const std::string& username, const std::string& passwordHash, Role role = Role::User,
        const std::string& registeredBy = "", const std::string& date = "")
        : Entity(id, username), passwordHash_(passwordHash), role_(role),
        registeredBy_(registeredBy), date_(date) {}

    const std::string& getPasswordHash() const { return passwordHash_; }
    void setPasswordHash(const std::string& h) { passwordHash_ = h; }

    Role getRole() const { return role_; }
    void setRole(Role r) { role_ = r; }

    const std::string& getRegisteredBy() const { return registeredBy_; }
    void setRegisteredBy(const std::string& s) { registeredBy_ = s; }

    const std::string& getDate() const { return date_; }
    void setDate(const std::string& s) { date_ = s; }

    std::string toText() const override {
        return "id: " + std::to_string(getId()) + "\n"
            + "username: " + getName() + "\n"
            + "password: " + passwordHash_ + "\n"
            + "role: " + roleToString(role_) + "\n"
            + "registeredBy: " + registeredBy_ + "\n"
            + "date: " + date_ + "\n"
            + "===\n";
    }

    static Role roleFromString(const std::string& s) {
        return (s == "admin") ? Role::Admin : Role::User;
    }
    static std::string roleToString(Role r) {
        return (r == Role::Admin) ? "admin" : "user";
    }

private:
    std::string passwordHash_;
    Role role_ = Role::User;
    std::string registeredBy_;
    std::string date_;
};
