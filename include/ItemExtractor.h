#pragma once

#include <functional>
#include <string>
#include <type_traits>

template<typename T>
struct ItemExtractor {
    static std::function<std::string(const T&)> byId() {
        return [](const T& i) { return std::to_string(i.getId()); };
    }
    static std::function<std::string(const T&)> byName() {
        return [](const T& i) { return i.getName(); };
    }
    static std::function<std::string(const T&)> byQuantity() {
        return [](const T& i) { return std::to_string(i.getQuantity()); };
    }
    static std::function<std::string(const T&)> byPrice() {
        return [](const T& i) { return std::to_string(i.getPrice()); };
    }
    static std::function<std::string(const T&)> byDate() {
        return [](const T& i) { return i.getDate(); };
    }
    static std::function<std::string(const T&)> byRegisteredBy() {
        return [](const T& i) { return i.getRegisteredBy(); };
    }
};
