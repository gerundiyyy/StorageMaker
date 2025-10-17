#include "ProductManager.h"
#include "ProductStorage.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "ItemExtractor.h"
#include "App.h"

int main()
{
    try {
        // Создаём конкретные типы — не абстрактные
        ProductManager db;
        ConsolUI ui;
        InputManager in(ui);
        ItemExtractor<Product> ex;                  // шаблонный извлекатель для Product
        ProductStorage storage(ex, in, ui);         // конкретный Storage<Product>
        App app(db, storage, ui, in);               // App принимает конкретные типы

        app.run();
        return 0;
    }
    catch (const std::exception& e) {
        // Если хотите — используйте std::cerr
        return 1;
    }
}
