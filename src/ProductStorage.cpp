#include "ProductStorage.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

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
