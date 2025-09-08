#pragma once
#include <string>
using namespace std;

class ObjectBD
{
private:
	int id;
	string name;
	int quantity;
	double price;
	string date;
	string registeredBy;
public:
	ObjectBD();
	~ObjectBD();

	void setId(int id);
	void setName(const string& name);
	void setQuantity(int quantity);
	void setPrice(double price);
	void setDate(const string& date);
	void setRegisteredBy(const string& registeredBy);

	int getId() const;
	string getName() const;
	int getQuantity() const;
	double getPrice() const;
	string getDate() const;
	string getRegisteredBy() const;
};