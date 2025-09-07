#include <iostream>
#include <string>
#include "DataBaseManager.h"
#include "ObjectBD.h"
using namespace std;

//Constructor and Destructors
ObjectBD::ObjectBD(int id, const string& name, int quantity, double price, const string& date, const string& registeredBy)
{
	this->id = id;
	this->name = name;
	this->quantity = quantity;
	this->price = price;
	this->date = date;
	this->registeredBy = registeredBy;

	cout << "ObjectBD has been created!" << endl;
}

ObjectBD::~ObjectBD()
{
	cout << "ObjectBD has been deleted!" << endl;
}

//Setters
void ObjectBD::setName(const string& name)
{
	this->name = name;
}
void ObjectBD::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void ObjectBD::setPrice(double price)
{
	this->price = price;
}
void ObjectBD::setDate(const string& date)
{
	this->date = date;
}
void ObjectBD::setRegisteredBy(const string& registeredBy)
{
	this->registeredBy = registeredBy;
}

//Getters
int ObjectBD::getId() const
{
	return id;
}
string ObjectBD::getName() const
{
	return name;
}
int ObjectBD::getQuantity() const
{
	return quantity;
}
double ObjectBD::getPrice() const
{
	return price;
}
string ObjectBD::getDate() const
{
	return date;
}
string ObjectBD::getRegisteredBy() const
{
	return registeredBy;
}
