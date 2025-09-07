#pragma once

#include <string>
#include <vector>
#include "ObjectBD.h"
using namespace std;

class DataBaseManager
{
private:
	int id;
	/*vector<ObjectBD> ObjectsBD;*/
public:
	DataBaseManager(const string& name, int id);
	~DataBaseManager();

	int getId() const;
	/*ObjectBD getObjectBD(int i);*/

	void recordObjectBD(const ObjectBD& ObjectBD);
};