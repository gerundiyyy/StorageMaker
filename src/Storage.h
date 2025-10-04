#pragma once

#include <vector>

#include "DataBaseManager.h"
#include "ObjectBD.h"

class Storage
{
private:
	std::vector <ObjectBD> Objects;
public:
    void loadFromDB(DataBaseManager& db);
    void addItem(const ObjectBD& Object);
    const std::vector<ObjectBD>& getItems() const;
};