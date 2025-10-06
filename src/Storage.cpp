#include "Storage.h"

#include <vector>
#include "DataBaseManager.h"
#include "Item.h"

using namespace std;

void Storage::loadItems(DataBaseManager& db)
{
    Items = db.readItem();
}

void Storage::addItem(const Item& item)
{
    Items.push_back(item);
}

const vector<Item>& Storage::getItems() const
{
    return Items;
}