#pragma once
#ifndef STORAGE_MAKER_ITEM_H_
#define STORAGE_MAKER_ITEM_H_
#include <string>
class Item
{
private:
	int id;
	std::string name;
	int quantity;
	double price;
	std::string date;
	std::string registeredBy;
public:
	Item(int id);
	Item();

	void setId(int id);
	void setName(const std::string& name);
	void setQuantity(int quantity);
	void setPrice(double price);
	void setDate(const std::string& date);
	void setRegisteredBy(const std::string& registeredBy);

	int getId() const;
	std::string getName() const;
	int getQuantity() const;
	double getPrice() const;
	std::string getDate() const;
	std::string getRegisteredBy() const;

	std::string toText() const;
	void print() const;
};
#endif