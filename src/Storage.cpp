#include "Storage.h"
#include <algorithm>
#include <vector>
#include <string>
#include "DataBaseManager.h"
#include "Item.h"
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
