#pragma once
#include <string>

class ObjectBD
{
private:
	int id;
	std::string name;
	int quantity;
	double price;
	std::string date;
	std::string registeredBy;
public:
	ObjectBD(int id);
	ObjectBD();

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