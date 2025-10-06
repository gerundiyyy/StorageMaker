#include <vector>

#include "DataBaseManager.h"
#include "ObjectBD.h"
#include "Storage.h"

using namespace std;

void Storage::loadFromDB(DataBaseManager& db)
{
    Objects = db.readObjectBD();
}

void Storage::addItem(const ObjectBD& Object)
{
    Objects.push_back(Object);
}

const vector<ObjectBD>& Storage::getItems() const
{
    return Objects;
}