#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

template<typename T>
class IDataBaseManager
{
protected:
    int toInt(const std::string& inputObject) const
    {
        std::stringstream isString(inputObject);
        int intObject = 0;
        isString >> intObject;
        return intObject;
    }

    double toDouble(const std::string& inputObject) const
    {
        std::string sanitized = inputObject;
        std::replace(sanitized.begin(), sanitized.end(), ',', '.');
        std::stringstream isString(sanitized);
        double doubleObject = 0.0;
        isString >> doubleObject;
        return doubleObject;
    }

public:
    virtual ~IDataBaseManager() = default;

    virtual void initializeDB(const std::string& address) = 0;
    virtual void record(const T& item) = 0;
    virtual void record(const std::vector<T>& items) = 0;
    virtual std::vector<T> readItem() = 0;
    virtual void parseLine(T& item, const std::string& line) = 0;
    virtual T parseItem(const std::vector<std::string>& lines) = 0;
};
