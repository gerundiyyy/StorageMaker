#define _CRT_SECURE_NO_WARNINGS
#include "ProductStorage.h"

#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <sstream>

void ProductStorage::loadItems(ProductManager& db)
{
    Items = db.readItem();
    sortBy([](const Product& it) { return it.getId(); }, true);
}

void ProductStorage::addItem(const Product& item)
{
    Items.push_back(item);
    sortBy([](const Product& it) { return it.getId(); }, true);
}

void ProductStorage::deleteItem()
{
    sortBy([](const Product& it) { return it.getId(); }, true);
    int idx = singleSearchById();
    if (idx < 0)
        throw runtime_error("Товар не найден.");
    if (static_cast<size_t>(idx) >= Items.size())
        throw out_of_range("Некорректный индекс удаления.");
    Items.erase(Items.begin() + idx);
}

void ProductStorage::changeItem(const Product& item)
{
    sortBy([](const Product& it) { return it.getId(); }, true);
    int idx = singleSearchById();
    if (idx < 0)
        throw runtime_error("Товар не найден.");
    if (static_cast<size_t>(idx) >= Items.size())
        throw out_of_range("Некорректный индекс изменения.");
    Items.erase(Items.begin() + idx);
    addItem(item);
}

const std::vector<Product>& ProductStorage::getItems() const
{
    return Items;
}

int ProductStorage::singleSearchById() const
{
    return Storage<Product>::singleSearchById();
}

std::vector<const Product*> ProductStorage::searchById() const
{
    const int needle = in->inputProductId();
    return searchBy(needle, ItemExtractor<Product>::byId());
}

std::vector<const Product*> ProductStorage::searchByName() const
{
    const std::string needle = in->inputProductName();
    return searchBy(needle, ItemExtractor<Product>::byName());
}

std::vector<const Product*> ProductStorage::searchByQuantity() const
{
    const int needle = in->inputProductQuantity();
    return searchBy(needle, ItemExtractor<Product>::byQuantity());
}

std::vector<const Product*> ProductStorage::searchByPrice() const
{
    const double needle = in->inputProductPrice();
    return searchBy(needle, ItemExtractor<Product>::byPrice());
}

std::vector<const Product*> ProductStorage::searchByDate() const
{
    const std::string needle = in->inputProductDate();
    return searchBy(needle, ItemExtractor<Product>::byDate());
}

std::vector<const Product*> ProductStorage::searchByRegisteredBy() const
{
    const std::string needle = in->inputProductRegisteredBy();
    return searchBy(needle, ItemExtractor<Product>::byRegisteredBy());
}

// Вспомогательная: парсит дату в формате "YYYY-MM-DD" или "DD.MM.YYYY" и возвращает количество месяцев от даты до сегодня
int ProductStorage::monthsSince(const std::string& dateStr) const {
    int d = 0, m = 0, y = 0;
    if (dateStr.find('-') != std::string::npos) { // YYYY-MM-DD
        char sep;
        std::istringstream is(dateStr);
        is >> y >> sep >> m >> sep >> d;
    }
    else if (dateStr.find('.') != std::string::npos) { // DD.MM.YYYY
        char sep;
        std::istringstream is(dateStr);
        is >> d >> sep >> m >> sep >> y;
    }
    else {
        return 0;
    }
    std::tm tm_date = {};
    tm_date.tm_mday = d;
    tm_date.tm_mon = m - 1;
    tm_date.tm_year = y - 1900;
    std::time_t t_date = std::mktime(&tm_date);
    if (t_date == -1) return 0;
    std::time_t now = std::time(nullptr);
    std::tm tm_now = *std::localtime(&now);
    int years = tm_now.tm_year - tm_date.tm_year;
    int months = tm_now.tm_mon - tm_date.tm_mon;
    return years * 12 + months;
}

std::vector<const Product*> ProductStorage::filter(const Filter& f) const {
    std::vector<const Product*> res;
    // Собираем предикаты (AND)
    for (const auto& item : Items) {
        bool ok = true;
        if (f.minMonthsAgo) {
            int months = monthsSince(item.getDate());
            if (!(months > *f.minMonthsAgo)) ok = false;
        }
        if (ok && f.minPrice) {
            if (!(item.getPrice() > *f.minPrice)) ok = false;
        }
        if (ok && f.minQuantity) {
            if (!(item.getQuantity() >= *f.minQuantity)) ok = false;
        }
        if (ok && f.nameContains) {
            if (item.getName().find(*f.nameContains) == std::string::npos) ok = false;
        }
        if (ok && f.registeredBy) {
            if (item.getRegisteredBy().find(*f.registeredBy) == std::string::npos) ok = false;
        }
        if (ok) res.push_back(&item);
    }

    // Сортировка результата по ключу (если указан)
    if (f.sortKey) {
        const string k = *f.sortKey;
        std::sort(res.begin(), res.end(), [&](const Product* a, const Product* b) {
            if (k == "id") {
                return f.ascending ? a->getId() < b->getId() : a->getId() > b->getId();
            }
            else if (k == "name") {
                return f.ascending ? a->getName() < b->getName() : a->getName() > b->getName();
            }
            else if (k == "quantity") {
                return f.ascending ? a->getQuantity() < b->getQuantity() : a->getQuantity() > b->getQuantity();
            }
            else if (k == "price") {
                return f.ascending ? a->getPrice() < b->getPrice() : a->getPrice() > b->getPrice();
            }
            else if (k == "date") {
                return f.ascending ? a->getDate() < b->getDate() : a->getDate() > b->getDate();
            }
            else if (k == "registeredBy") {
                return f.ascending ? a->getRegisteredBy() < b->getRegisteredBy() : a->getRegisteredBy() > b->getRegisteredBy();
            }
            return true;
            });
    }

    return res;
}
