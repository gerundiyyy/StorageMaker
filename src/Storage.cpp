#include "Storage.h"
#include <algorithm>
#include <vector>
#include "DataBaseManager.h"
#include "Item.h"

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
        std::sort(Items.begin(), Items.end(), [&](const Item& a, const Item& b) {
            return key(a) < key(b);
        });
    }
    else {
        std::sort(Items.begin(), Items.end(), [&](const Item& a, const Item& b) {
            return key(b) < key(a);
        });
    }
}
const Item* Storage::searchForId(int id) const
{
    auto it = std::find_if(Items.cbegin(), Items.cend(),
        [id](const Item& item) { return item.getId() == id; });
    return (it != Items.cend()) ? &*it : nullptr;
}
const std::vector<Item>& Storage::getItems() const
{
    return Items;
}
