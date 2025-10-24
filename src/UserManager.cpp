// UserManager.cpp
// Простая и понятная реализация UserManager с автосозданием одного админа,
// переносимой по Windows/POSIX и без лишних зависимостей.

#include "UserManager.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <functional>

// Простая trim-функция (единственная в этом файле)
static inline std::string trim(const std::string& s) {
    auto b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

// Парсит блок строк в объект User (каждая строка вида "ключ: значение")
User UserManager::parseItem(const std::vector<std::string>& lines) {
    User u;
    for (const auto& ln : lines) {
        if (ln.rfind("id:", 0) == 0) u.setId(std::stoi(trim(ln.substr(3))));
        else if (ln.rfind("username:", 0) == 0) u.setName(trim(ln.substr(9)));
        else if (ln.rfind("password:", 0) == 0) u.setPasswordHash(trim(ln.substr(9)));
        else if (ln.rfind("role:", 0) == 0) u.setRole(User::roleFromString(trim(ln.substr(5))));
        else if (ln.rfind("registeredBy:", 0) == 0) u.setRegisteredBy(trim(ln.substr(13)));
        else if (ln.rfind("date:", 0) == 0) u.setDate(trim(ln.substr(5)));
    }
    return u;
}

void UserManager::parseLine(User& item, const std::string& line) {
    // У нас использован parseItem, поэтому этот метод можно оставить пустым или реализовать аналогично.
    // Оставим пустым, чтобы соответствовать интерфейсу.
    (void)item;
    (void)line;
}

std::vector<User> UserManager::readItem() {
    return users_;
}

void UserManager::load() {
    users_.clear();
    std::ifstream in(filename_);
    if (!in) {
        // файл отсутствует — начнём с пустого списка и затем создадим дефолтного админа
    }
    else {
        std::string line;
        std::vector<std::string> block;
        while (std::getline(in, line)) {
            std::string t = trim(line);
            if (t.empty()) continue;
            if (t == "===") {
                if (!block.empty()) users_.push_back(parseItem(block));
                block.clear();
            }
            else {
                block.push_back(t);
            }
        }
        if (!block.empty()) users_.push_back(parseItem(block));
    }

    // Если админа нет — создаём одного дефолтного
    bool hasAdmin = false;
    for (const auto& u : users_) if (u.getRole() == User::Role::Admin) { hasAdmin = true; break; }

    if (!hasAdmin) {
        std::hash<std::string> h;
        std::string defaultPass = "admin";                  // пароль по умолчанию
        std::string hash = std::to_string(h(defaultPass)); // хешируем так же, как AuthManager

        // выбираем id: 1 если пусто, иначе maxId+1
        int maxId = 0;
        for (const auto& u : users_) if (u.getId() > maxId) maxId = u.getId();
        int newId = (maxId >= 1) ? (maxId + 1) : 1;

        // Текущая дата YYYY-MM-DD (без deprecated warning)
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
#if defined(_MSC_VER)
        localtime_s(&tm, &t);
#else
        tm = *std::localtime(&t);
#endif
        char buf[16];
        std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

        User admin(newId, "admin", hash, User::Role::Admin, "system", std::string(buf));
        users_.push_back(admin);
        save(); // сохраняем, чтобы админ остался в файле
    }
}

void UserManager::save() const {
    std::ofstream out(filename_, std::ios::trunc);
    for (const auto& u : users_) {
        out << u.toText();
    }
}

void UserManager::record(const User& item) {
    // добавляем пользователя и сохраняем (append)
    users_.push_back(item);
    std::ofstream out(filename_, std::ios::app);
    out << item.toText();
}

void UserManager::record(const std::vector<User>& items) {
    users_ = items;
    save();
}

void UserManager::addUser(const User& u) {
    users_.push_back(u);
    save();
}

bool UserManager::removeUserById(int id) {
    auto it = std::remove_if(users_.begin(), users_.end(), [id](const User& u) { return u.getId() == id; });
    if (it == users_.end()) return false;
    users_.erase(it, users_.end());
    save();
    return true;
}

User* UserManager::findByUsername(const std::string& username) {
    for (auto& u : users_) if (u.getName() == username) return &u;
    return nullptr;
}

User* UserManager::findById(int id) {
    for (auto& u : users_) if (u.getId() == id) return &u;
    return nullptr;
}
