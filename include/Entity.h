#pragma once
#include <string>
class Entity
{
private:
	int id;
	std::string name;
public:
	Entity(int id, std::string name)
		: id(id), name(name) {}
	Entity()
		: id(0), name("None") {}
	void setId(int id)
	{
		this->id = id;
	}
	void setName(const std::string& name)
	{
		this->name = name;
	}
	int getId() const
	{
		return id;
	}
	std::string getName() const
	{
		return name;
	}
	virtual std::string toText() const
	{
		return "id: " + std::to_string(id) + "\n" +
			"Èìÿ: " + name + "\n" +
			"===\n";
	}
};