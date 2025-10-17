#pragma once

#include "Storage.h"
#include "Product.h"
#include "ProductManager.h"

#include <vector>

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
};
