#pragma once
#include "Entity.h"
#include <string>
class Product : public Entity 
{
private:
	int quantity;
	double price;
	std::string date;
	std::string registeredBy;
public:
	Product(int id);
	Product();

	void setQuantity(int quantity);
	void setPrice(double price);
	void setDate(const std::string& date);
	void setRegisteredBy(const std::string& registeredBy);

	int getQuantity() const;
	double getPrice() const;
	std::string getDate() const;
	std::string getRegisteredBy() const;

	std::string toText() const override;
};

