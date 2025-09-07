#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DataBaseManager
{
private:
	int id;
	//vector<Product> product  
public:
	DataBaseManager(const string& name, int id);
	~DataBaseManager();

	int getId();
	/*Product getProducts(int i);*/

	void recordProduct(const string& text);
};