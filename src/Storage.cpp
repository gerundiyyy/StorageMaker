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
std::vector<const Item*> Storage::searchById(const int needle) const
{
    return searchBy(needle, ex->byId());
}
std::vector<const Item*> Storage::searchByName(const string& needle) const
{
    return searchBy(needle, ex->byName());
}
std::vector<const Item*> Storage::searchByQuantity(const int needle) const
{
    return searchBy(needle, ex->byQuantity());
}
std::vector<const Item*> Storage::searchByPrice(const double needle) const
{
    return searchBy(needle, ex->byPrice());
}
std::vector<const Item*> Storage::searchByDate(const string& needle) const
{
    return searchBy(needle, ex->byDate());
}
std::vector<const Item*> Storage::searchByRegisterdBy(const string& needle) const
{
    return searchBy(needle, ex->byRegisteredBy());
}