#pragma once
#include "IDataBaseManager.h"
#include <string>
#include <vector>
#include "Product.h"

class ProductManager : public IDataBaseManager<Product>
{
public:
	void initializeDB(const std::string& address) override;
	void record(const Product& item) override;
	void record(const std::vector<Product>& items) override;
	std::vector <Product> readItem() override;
	void parseLine(Product& item, const std::string& line) override;
	Product parseItem(const std::vector<std::string>& lines) override;
};