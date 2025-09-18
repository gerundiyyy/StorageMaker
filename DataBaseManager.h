#pragma once

#include <string>
#include <vector>
#include "ObjectBD.h"

class DataBaseManager
{
private:
	int id;
public:
	DataBaseManager(int id);
	~DataBaseManager();

	int getId() const;

	int toInt(const std::string& inputObject);
	double toDouble(const std::string& inputObject);
	void recordObjectBD(const ObjectBD& obj);
	std::vector <ObjectBD> readObjectBD();
	ObjectBD parseObject(const std::vector<std::string>& lines);
};