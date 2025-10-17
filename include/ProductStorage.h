#pragma once

#include "Storage.h"
#include "Product.h"
#include "ProductManager.h"

#include <vector>
#include <functional>
#include <optional>
#include <string>

class ProductStorage : public Storage<Product> {
public:
    ProductStorage(ItemExtractor<Product>& ex, InputManager& in, ConsolUI& ui)
        : Storage<Product>(ex, in, ui) {}

    void loadItems(ProductManager& db);

    void addItem(const Product& item);
    void deleteItem() override;
    void changeItem(const Product& item) override;

    const std::vector<Product>& getItems() const;
    int singleSearchById() const;

    std::vector<const Product*> searchById() const;
    std::vector<const Product*> searchByName() const;
    std::vector<const Product*> searchByQuantity() const;
    std::vector<const Product*> searchByPrice() const;
    std::vector<const Product*> searchByDate() const;
    std::vector<const Product*> searchByRegisteredBy() const;

    struct Filter {
        std::optional<int> minMonthsAgo;
        std::optional<double> minPrice;
        std::optional<int> minQuantity;
        std::optional<std::string> nameContains;
        std::optional<std::string> registeredBy;
        std::optional<std::string> sortKey;
        bool ascending = true;
    };

    std::vector<const Product*> filter(const Filter& f) const;

private:
    int monthsSince(const std::string& dateStr) const;
};
