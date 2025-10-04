#pragma once

#include <string>
#include <vector>
#include "ObjectBD.h"

class DataBaseManager
{
public:
	DataBaseManager()
		: lastId(0) {};

	int getLastId() const;
	void setLastId(int lastId);
	void recordObjectBD(const ObjectBD& obj, int lastId);
	std::vector <ObjectBD> readObjectBD();
protected:
	std::ifstream openFile(const std::string& fileName);
	std::vector <ObjectBD> parseFile(std::ifstream& file);
	ObjectBD parseObject(const std::vector<std::string>& lines);
	
	int toInt(const std::string& inputObject);
	double toDouble(const std::string& inputObject);
private:
	int lastId;
};