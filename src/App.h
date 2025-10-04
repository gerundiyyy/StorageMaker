#pragma once

#include <string>

#include "ConsolUI.h"
#include "InputManager.h"
#include "DataBaseManager.h"
#include "ObjectBD.h"
#include "Storage.h"

class App
{
private:
	DataBaseManager db;
	Storage storage;
	ConsolUI ui;
	InputManager in;

	std::string currentUser;
public:
	void callMenu();

	void authorization();
	void record();
	void deleteObj();
	void printAll();
	void search();

	void run();
	void stop();
};