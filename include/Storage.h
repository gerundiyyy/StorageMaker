#pragma once
#ifndef STORAGE_MAKER_STORAGE_H_
#define STORAGE_MAKER_STORAGE_H_
#include <algorithm>
#include <vector>
#include <functional>
#include "DataBaseManager.h"
#include "Item.h"

class Storage
{
public:
    void loadItems(DataBaseManager& db);
    void addItem(const Item& item);
    const std::vector<Item>& getItems() const;
    const Item* searchForId(int id) const;

    template<typename Key>
    void sortBy(Key key, bool ascending);
private:
	std::vector <Item> Items;
};
#endif