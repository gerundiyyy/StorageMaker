#include "Storage.h"
#include <algorithm>
#include <vector>
#include <string>
#include "DataBaseManager.h"
#include "Item.h"
#include "ItemExtractor.h"
using namespace std;

void Storage::loadItems(DataBaseManager& db)
{
    Items = db.readItem();
    sortBy([](const Item& it) { return it.getId(); }, true);
}
void Storage::addItem(const Item& item)
{
    Items.push_back(item);
    sortBy([](const Item& it) { return it.getId(); }, true);
}
void Storage::deleteItem()
{
    sortBy([](const Item& it) { return it.getId(); }, true);
    int idx = singleSearchById();
    if (idx < 0) 
        throw runtime_error("Товар не найден.");
    if (static_cast<size_t>(idx) >= Items.size())
        throw out_of_range("Некорректный индекс удаления.");
    Items.erase(Items.begin() + idx);
}
void Storage::changeItem(const Item& item)
{
    sortBy([](const Item& it) { return it.getId(); }, true);
    int idx = singleSearchById();
    if (idx < 0)
        throw runtime_error("Товар не найден.");
    if (static_cast<size_t>(idx) >= Items.size())
        throw out_of_range("Некорректный индекс изменения.");
    Items.erase(Items.begin() + idx);
    addItem(item);
}

template<typename Key>
void Storage::sortBy(Key key, bool ascending) {
    if (ascending) {
        sort(Items.begin(), Items.end(), [&](const Item& a, const Item& b) {
            return key(a) < key(b);
        });
    }
    else {
        sort(Items.begin(), Items.end(), [&](const Item& a, const Item& b) {
            return key(b) < key(a);
        });
    }
}

const vector<Item>& Storage::getItems() const
{
    return Items;
}
int Storage::singleSearchById() const
{
    const int needle = in->inputItemId();
    for (int i = 0; i < Items.size(); i++) {
        if (Items[i].getId() == needle) return i;
    }
    return -1;
}
std::vector<const Item*> Storage::searchById() const
{
    const int needle = in->inputItemId();
    return searchBy(needle, ex->byId());
}
std::vector<const Item*> Storage::searchByName() const
{
    const string& needle = in->inputItemName();
    return searchBy(needle, ex->byName());
}
std::vector<const Item*> Storage::searchByQuantity() const
{
    const int needle = in->inputItemQuantity();
    return searchBy(needle, ex->byQuantity());
}
std::vector<const Item*> Storage::searchByPrice() const
{
    const double needle = in->inputItemPrice();
    return searchBy(needle, ex->byPrice());
}
std::vector<const Item*> Storage::searchByDate() const
{
    const string& needle = in->inputItemDate();
    return searchBy(needle, ex->byDate());
}
std::vector<const Item*> Storage::searchByRegisterdBy() const
{
    const string& needle = in->inputItemRegisteredBy();
    return searchBy(needle, ex->byRegisteredBy());
}