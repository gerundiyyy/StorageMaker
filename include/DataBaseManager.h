#pragma once
#ifndef STORAGE_MAKER_DBmanager_H_
#define STORAGE_MAKER_DBmanager_H_
#include <string>
#include <vector>
#include "Item.h"

class DataBaseManager
{
private:
	int toInt(const std::string& inputObject);
	double toDouble(const std::string& inputObject);
public:
	int getLastId() const;

	void recordItem(const Item& item);
	void recordItem(const std::vector<Item>& items) const;
	std::vector <Item> readItem();
	Item parseItem(const std::vector<std::string>& lines);
};
#endif