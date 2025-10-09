#pragma once
#ifndef STORAGE_MAKER_ITEMEXTRACTOR_H_
#define STORAGE_MAKER_ITEMEXTRACTOR_H_
#include "Item.h"
class ItemExtractor {
public:
    static std::function<std::string(const Item&)> byId() {
        return [](const Item& i) { return std::to_string(i.getId()); };
    }
    static std::function<std::string(const Item&)> byName() {
        return [](const Item& i) { return i.getName(); };
    }
    static std::function<std::string(const Item&)> byQuantity() {
        return [](const Item& i) { return std::to_string(i.getQuantity()); };
    }
    static std::function<std::string(const Item&)> byPrice() {
        return [](const Item& i) { return std::to_string(i.getPrice()); };
    }
    static std::function<std::string(const Item&)> byDate() {
        return [](const Item& i) { return i.getDate(); };
    }
    static std::function<std::string(const Item&)> byRegisteredBy() {
        return [](const Item& i) { return i.getRegisteredBy(); };
    }
};

#endif