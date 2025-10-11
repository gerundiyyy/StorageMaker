#pragma once
#ifndef STORAGE_MAKER_STORAGE_H_
#define STORAGE_MAKER_STORAGE_H_
#include <algorithm>
#include <vector>
#include <functional>
#include <typeinfo>
#include <string>
#include <sstream>
#include <type_traits>
#include "DataBaseManager.h"
#include "Item.h"
#include "ItemExtractor.h"

class Storage
{
public:
    void loadItems(DataBaseManager& db);
    void addItem(const Item& item);
    
    const std::vector<Item>& getItems() const;

    template<typename T>
    static std::string to_string_any(const T& value) {
        if constexpr (std::is_same_v<T, std::string>) {
            return value;
        }
        else if constexpr (std::is_same_v<T, const char*>) {
            return std::string(value);
        }
        else if constexpr (std::is_same_v<T, char>) {
            return std::string(1, value);
        }
        else if constexpr (std::is_same_v<T, bool>) {
            return value ? "true" : "false";
        }
        else if constexpr (std::is_arithmetic_v<T>) {
            return std::to_string(value);
        }
        else {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
    }

    template<typename Key>
    std::vector<const Item*> searchBy(const Key& key, std::function<std::string(const Item&)> extractor) const
    {
        std::string needle = to_string_any(key);

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