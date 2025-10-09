#pragma once
#ifndef STORAGE_MAKER_STORAGE_H_
#define STORAGE_MAKER_STORAGE_H_
#include <algorithm>
#include <vector>
#include <functional>
#include "DataBaseManager.h"
#include "Item.h"
#include "ItemExtractor.h"

class Storage
{
public:
    void loadItems(DataBaseManager& db);
    void addItem(const Item& item);
    
    const std::vector<Item>& getItems() const;

    template<typename Key>
    std::vector<const Item*> searchBy(const Key& key, std::function<std::string(const Item&)> extractor) const
    {
        const std::string needle = std::to_string(key);
        std::vector<const Item*> results;

        for (const auto& item : Items) {
            std::string hay = extractor(item);
            if (hay.find(needle) != std::string::npos) {
                results.push_back(&item);
            }
        }

        return results;
    }

    template<typename Key>
    void sortBy(Key key, bool ascending);
private:
	std::vector <Item> Items;
};
#endif