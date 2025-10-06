#pragma once

#include <string>
#include <vector>
#include "ObjectBD.h"

class DataBaseManager
{
private:
	int lastId;

	int toInt(const std::string& inputObject);
	double toDouble(const std::string& inputObject);
public:
	int getLastId() const;

	void recordObjectBD(const ObjectBD& obj);
	std::vector <ObjectBD> readObjectBD();
	ObjectBD parseObject(const std::vector<std::string>& lines);
};