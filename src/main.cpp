#include "ProductManager.h"
#include "ProductStorage.h"
#include "UserManager.h"
#include "AuthManager.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "ItemExtractor.h"
#include "App.h"

#include <iostream>

int main()
{
    try {
        ConsolUI ui;
        InputManager in(ui);
        ProductManager productDb;
        productDb.initializeDB("data/product_data.txt");
        UserManager userDb("data/users.txt");
        userDb.load();
        ItemExtractor<Product> productExtractor;
        ProductStorage productStorage(productExtractor, in, ui);
        productStorage.loadItems(productDb);
        AuthManager auth(userDb, ui, in);
        App app(productDb, productStorage, userDb, auth, ui, in);

        app.run();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error\n";
        return 2;
    }
}
