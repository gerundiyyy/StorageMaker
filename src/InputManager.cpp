#include "InputManager.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

// Ошибочные сообщения (не модифицируют объект -> const)
void InputManager::boolError() const { ui->showMessage("Ошибка! Введите 1 или 0."); }
void InputManager::intError() const { ui->showMessage("Ошибка! Введите целое число."); }
void InputManager::doubleError() const { ui->showMessage("Ошибка! Введите число (через точку)."); }
void InputManager::voidError() const { ui->showMessage("Ошибка! Значение не может быть пустым."); }

// trim простая
std::string InputManager::trim(const std::string& s) const {
    auto first = s.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    auto last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, last - first + 1);
}

// safe getline
bool InputManager::readLine(std::string& out) const {
    if (!std::getline(std::cin, out)) {
        std::cin.clear();
        return false;
    }
    out = trim(out);
    return true;
}

// Конвертеры через stoi/stod с обработкой исключений
int InputManager::toInt(const std::string& inputObject) const {
    try {
        size_t pos = 0;
        int v = std::stoi(inputObject, &pos);
        if (pos != inputObject.size()) return 0;
        return v;
    }
    catch (...) {
        return 0;
    }
}

double InputManager::toDouble(const std::string& inputObject) const {
    try {
        size_t pos = 0;
        double v = std::stod(inputObject, &pos);
        if (pos != inputObject.size()) return 0.0;
        return v;
    }
    catch (...) {
        return 0.0;
    }
}

// Простые проверки
bool InputManager::isInt(const std::string& inputObject) const {
    if (inputObject.empty()) { intError(); return false; }
    try {
        size_t pos = 0;
        std::stoi(inputObject, &pos);
        if (pos != inputObject.size()) { intError(); return false; }
        return true;
    }
    catch (...) {
        intError();
        return false;
    }
}

bool InputManager::isDouble(const std::string& inputObject) const {
    if (inputObject.empty()) { doubleError(); return false; }
    try {
        size_t pos = 0;
        std::stod(inputObject, &pos);
        if (pos != inputObject.size()) { doubleError(); return false; }
        return true;
    }
    catch (...) {
        doubleError();
        return false;
    }
}

// Inputs
bool InputManager::isContinue() const {
    ui->showMessage("Продолжить? (1 - да, 0 - нет): ");
    std::string s;
    if (!readLine(s)) return false;
    return (s == "1");
}

int InputManager::inputProductId() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return 0; }
        if (!s.empty() && isInt(s)) return toInt(s);
        // isInt уже показывает ошибку
    }
}

std::string InputManager::inputProductName() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return {}; }
        if (!s.empty()) return s;
        voidError();
    }
}

int InputManager::inputProductQuantity() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return 0; }
        if (!s.empty() && isInt(s)) return toInt(s);
    }
}

double InputManager::inputProductPrice() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return 0.0; }
        if (!s.empty() && isDouble(s)) return toDouble(s);
    }
}

std::string InputManager::inputProductDate() {
    std::string s;
    readLine(s);
    return s;
}

std::string InputManager::inputProductRegisteredBy() {
    std::string s;
    readLine(s);
    return s;
}

Product InputManager::inputFullProduct() {
    Product p;
    ui->showMessage("id: ");
    p.setId(inputProductId());
    ui->showMessage("Имя: ");
    p.setName(inputProductName());
    ui->showMessage("Количество: ");
    p.setQuantity(inputProductQuantity());
    ui->showMessage("Цена: ");
    p.setPrice(inputProductPrice());
    ui->showMessage("Дата регистрации: ");
    p.setDate(inputProductDate());
    ui->showMessage("Кто зарегистрировал: ");
    p.setRegisteredBy(inputProductRegisteredBy());
    return p;
}

int InputManager::waitForKey() {
    std::string s;
    readLine(s);
    if (s.empty()) return 1;
    if (isInt(s)) return toInt(s);
    return 1;
}

int InputManager::inputMenu() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return 0; }
        if (isInt(s)) return toInt(s);
        intError();
    }
}

// Простые реализации для App

int InputManager::inputNumberAllowZero() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return 0; }
        if (s.empty()) return 0;
        if (isInt(s)) {
            int v = toInt(s);
            if (v >= 0) return v;
            intError();
        }
    }
}

double InputManager::inputDoubleAllowZero() {
    std::string s;
    while (true) {
        if (!readLine(s)) { ui->showMessage("Ввод прерван."); return 0.0; }
        if (s.empty()) return 0.0;
        if (isDouble(s)) {
            double v = toDouble(s);
            if (v >= 0.0) return v;
            doubleError();
        }
    }
}

std::string InputManager::inputOptionalString() {
    std::string s;
    if (!readLine(s)) return {};
    return s;
}
