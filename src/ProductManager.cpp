#include "ProductManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace {
    int toInt(const string& s) {
        stringstream ss(s);
        int v = 0;
        ss >> v;
        return v;
    }

    double toDouble(const string& s) {
        string sanitized = s;
        replace(sanitized.begin(), sanitized.end(), ',', '.');
        stringstream ss(sanitized);
        double v = 0.0;
        ss >> v;
        return v;
    }
}

// Путь по умолчанию можно изменить через initializeDB
void ProductManager::initializeDB(const std::string& address)
{
    // просто убедимся, что файл существует (создаём при необходимости)
    ofstream ensure(address, ios::app);
    if (!ensure) throw runtime_error("Не удалось создать/открыть файл БД: " + address);
    ensure.close();
    // Сохраняем путь в приватное поле, если хотите (в заголовке его нет)
    // Для простоты оставляем фиксированный путь в методах ниже
}

void ProductManager::record(const Product& item)
{
    ofstream file("data/product_data.txt", ios::app);
    if (!file) throw runtime_error("Не удалось открыть файл для записи");
    file << item.toText();
    file.close();
}

void ProductManager::record(const std::vector<Product>& items)
{
    ofstream file("data/product_data.txt", ofstream::out | ofstream::trunc);
    if (!file) throw runtime_error("Не удалось открыть файл для записи");
    for (const auto& item : items) {
        file << item.toText();
    }
    file.close();
}

std::vector<Product> ProductManager::readItem()
{
    ifstream file("data/product_data.txt");
    if (!file) throw runtime_error("Не удалось открыть файл для чтения");
    vector<Product> result;
    vector<string> buffer;
    string line;

    while (getline(file, line)) {
        if (line == "===") {
            Product obj = parseItem(buffer);
            result.push_back(obj);
            buffer.clear();
        }
        else {
            buffer.push_back(line);
        }
    }

    // В конце файла может не быть "===", тогда соберём остаток
    if (!buffer.empty()) {
        Product obj = parseItem(buffer);
        result.push_back(obj);
    }

    return result;
}

void ProductManager::parseLine(Product& item, const std::string& line)
{
    if (line.find("id: ") == 0)
        item.setId(toInt(line.substr(4)));
    else if (line.find("Имя: ") == 0)
        item.setName(line.substr(5));
    else if (line.find("Количество: ") == 0)
        item.setQuantity(toInt(line.substr(12)));
    else if (line.find("Цена: ") == 0)
        item.setPrice(toDouble(line.substr(6)));
    else if (line.find("Дата регистрации: ") == 0)
        item.setDate(line.substr(18));
    else if (line.find("Кто зарегистрировал: ") == 0)
        item.setRegisteredBy(line.substr(21));
    // Игнорируем неизвестные строки
}

Product ProductManager::parseItem(const std::vector<std::string>& lines)
{
    Product item;
    try {
        for (const auto& line : lines) parseLine(item, line);
    }
    catch (const exception& e) {
        throw runtime_error(string{ "Ошибка парсинга Product: " } + e.what());
    }
    return item;
}
