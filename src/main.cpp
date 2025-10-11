#include "App.h"

int main()
{
	DataBaseManager* db = new DataBaseManager();
	ConsolUI* ui = new ConsolUI();
	InputManager* in = new InputManager();
	ItemExtractor* ex;
	Storage* storage = new Storage(*ex);
	App* app = new App(*db, *storage, *ui, *in);
	app->run();
	app->appMenu();
	delete db;
	delete storage;
	delete ui;
	delete in;
	delete ex;
	delete app;
}