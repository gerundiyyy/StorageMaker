#pragma once
#ifndef STORAGE_MAKER_STORAGE_H_
#define STORAGE_MAKER_STORAGE_H_
#include <vector>
#include "DataBaseManager.h"
#include "Item.h"

class Storage
{
private:
	std::vector <Item> Items;
public:
    void loadItems(DataBaseManager& db);
    void addItem(const Item& item);
    const std::vector<Item>& getItems() const;
};
#endif