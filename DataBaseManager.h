#pragma once

#include <string>
#include <vector>
#include "ObjectBD.h"
using namespace std;

class DataBaseManager
{
private:
	int id;
public:
	DataBaseManager(int id);
	~DataBaseManager();

	int getId() const;

	void recordObjectBD(const ObjectBD& ObjectBD);
};