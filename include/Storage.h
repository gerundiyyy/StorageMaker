#pragma once
#include <algorithm>
#include <vector>
#include <functional>
#include <string>
#include <sstream>
#include <type_traits>

#include "ItemExtractor.h"
#include "InputManager.h"
#include "ConsolUI.h"

template<typename T>
class Storage {
public:
    Storage(ItemExtractor<T>& ex, InputManager& in, ConsolUI& ui)
        : ex(&ex), in(&in), ui(&ui) {}

    void addItem(const T& item) {
        Items.push_back(item);
        sortBy([](const T& it) { return it.getId(); }, true);
    }

    virtual void deleteItem() = 0;
    virtual void changeItem(const T& item) = 0;

    const std::vector<T>& getItems() const {
        return Items;
    }

    int singleSearchById() const {
        const int needle = in->inputProductId();
        for (int i = 0; i < static_cast<int>(Items.size()); ++i) {
            if (Items[i].getId() == needle) return i;
        }
        return -1;
    }

    template<typename U>
    static std::string to_string_any(const U& value) {
        if constexpr (std::is_same_v<U, std::string>) {
            return value;
        }
        else if constexpr (std::is_same_v<U, const char*>) {
            return std::string(value);
        }
        else if constexpr (std::is_same_v<U, char>) {
            return std::string(1, value);
        }
        else if constexpr (std::is_same_v<U, bool>) {
            return value ? "true" : "false";
        }
        else if constexpr (std::is_arithmetic_v<U>) {
            return std::to_string(value);
        }
        else {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
    }

    template<typename Key>
    std::vector<const T*> searchBy(
        const Key& key,
        std::function<std::string(const T&)> extractor
    ) const {
        std::string needle = to_string_any(key);
        std::vector<const T*> results;
        for (const auto& item : Items) {
            std::string hay = extractor(item);
            if (hay.find(needle) != std::string::npos) {
                results.push_back(&item);
            }
        }
        return results;
    }

    template<typename KeyFunc>
    void sortBy(KeyFunc key, bool ascending) {
        if (ascending) {
            std::sort(Items.begin(), Items.end(), [&](const T& a, const T& b) {
                return key(a) < key(b);
                });
        }
        else {
            std::sort(Items.begin(), Items.end(), [&](const T& a, const T& b) {
                return key(b) < key(a);
                });
        }
    }

protected:
    std::vector<T> Items;
    ItemExtractor<T>* ex;
    InputManager* in;
    ConsolUI* ui;
};
