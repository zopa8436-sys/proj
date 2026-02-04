#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"
#include "Palette.h"


int main()
{
    // настройка вывода в консоль
    init(L"Задание на 04.02.2026 - практика использования STL в разработке приложений");
    ostringstream oss;

    // коды команд
    enum Commands : int {
        // Покаазать текущие сведения о магазине
        CMD_SHOW_ALL = 1001,

        // Формирование коллекции фабричным методом
        CMD_CREATE_FACTORY,

        // Добавление игры, сформированной фабричным методом
        CMD_ADD,

        // Редактирование игры (фабричным методом, ид вводится с клавиатуры)
        CMD_EDIT_BY_ID,

        // Удаление игры по идентификатору
        CMD_DELETE_BY_ID,

        // Упорядочивание игр по идентификатору
        CMD_ORDER_BY_ID,

        // Упорядочите вывод игр по убыванию года издания
        CMD_ORDER_BY_YEAR_DESC,

        // Упорядочите вывод игр по возрастанию цены
        CMD_ORDER_BY_PRICE_ASC,

        // Упорядочите вывод игр по убыванию количества проданных копий
        CMD_ORDER_BY_SOLD_DESC,

        // Выборка игр по диапазону цены, сортировка по возрастанию цены
        CMD_SELECT_BY_PRICE_RANGE,

        // Выборка игр по году издания, сортировка по жанру
        CMD_SELECT_BY_YEAR,

        // Выборка игр по ОС, сортировка по убыванию года издания
        CMD_SELECT_BY_OS,

        // Запись сведений о магазине и коллекции игр в CSV-файл
        CMD_SAVE_CSV,

        // Чтение сведений о магазине и коллекции игр из CSV-файла
        CMD_LOAD_CSV,
    };

    // вектор пунктов меню
    vector<MenuItem> items = {
        {CMD_SHOW_ALL,              "Покаазать текущие сведения о магазине"},
        {CMD_CREATE_FACTORY,        "Формирование коллекции (фабричный метод)"},
        {CMD_ADD,                   "Добавление игры (фабричный метод)"},
        {CMD_EDIT_BY_ID,            "Редактирование игры по идентификатору (фабричный метод)"},
        {CMD_DELETE_BY_ID,          "Удаление игры по идентификатору"},
        {CMD_ORDER_BY_ID,           "Упорядочивание игр по идентификатору"},
        {CMD_ORDER_BY_YEAR_DESC,    "Упорядочить вывод игр по убыванию года издания"},
        {CMD_ORDER_BY_PRICE_ASC,    "Упорядочить вывод игр по возрастанию цены"},
        {CMD_ORDER_BY_SOLD_DESC,    "Упорядочить вывод игр по убыванию проданных копий"},
        {CMD_SELECT_BY_PRICE_RANGE, "Выборка по диапазону цен (сортировка по возрастанию цены)"},
        {CMD_SELECT_BY_YEAR,        "Выборка по году издания (сортировка по жанру)"},
        {CMD_SELECT_BY_OS,          "Выборка по ОС (сортировка по убыванию года издания)"},
        {CMD_SAVE_CSV,              "Запись сведений о магазине в файл CSV"},
        {CMD_LOAD_CSV,              "Чтение сведений о магазине из файла CSV"},
        {Menu::CMD_QUIT,            "Выход из приложения"}
    };

    Menu mainMenu(COORD{ 5, 5 }, items, infoColor, hintColor);

    // Объект класса приложения для обработок по заданию
    App* app = nullptr;

    while (true) {
        try {
            // Создание объекта приложения в защищенной области
            if (app == nullptr) {
                app = new App();
            } // if

            cout << color(mainColor) << cls;
            showNavBarMessage(
                hintColor, acctColor,
                "  Магазин компьютерных игр (STL, алгоритмы)  |  ~Esc~ ~F10~ Выход"
            );
            int cmd = mainMenu.navigate();
            cout << color(mainColor) << cls;
            if (cmd == Menu::CMD_QUIT) break;

            switch (cmd) {
                // Покаазать текущие сведения о магазине
            case CMD_SHOW_ALL:
                app->doShowAll();
                break;

                // Формирование коллекции фабричным методом
            case CMD_CREATE_FACTORY:
                app->doCreateFactoryCollection();
                break;

                // Добавление игры, сформированной фабричным методом
            case CMD_ADD:
                app->doAddGame();
                break;

                // Редактирование игры (фабричным методом, ид вводится с клавиатуры)
            case CMD_EDIT_BY_ID:
                app->doEditGameById();
                break;

                // Удаление игры по идентификатору
            case CMD_DELETE_BY_ID:
                app->doDeleteGameById();
                break;

                // Упорядочивание игр по идентификатору
            case CMD_ORDER_BY_ID:
                app->doOrderById();
                break;

                // Упорядочите вывод игр по убыванию года издания
            case CMD_ORDER_BY_YEAR_DESC:
                app->doOrderByYearDescending();
                break;

                // Упорядочите вывод игр по возрастанию цены
            case CMD_ORDER_BY_PRICE_ASC:
                app->doOrderByPriceAscending();
                break;

                // Упорядочите вывод игр по убыванию количества проданных копий
            case CMD_ORDER_BY_SOLD_DESC:
                app->doOrderBySoldCopiesDescending();
                break;

                // Выборка игр по диапазону цены, сортировка по возрастанию цены
            case CMD_SELECT_BY_PRICE_RANGE:
                app->doFindByPriceRange();
                break;

                // Выборка игр по году издания, сортировка по жанру
            case CMD_SELECT_BY_YEAR:
                app->doFindByPubYear();
                break;

                // Выборка игр по ОС, сортировка по убыванию года издания
            case CMD_SELECT_BY_OS:
                app->doFindByOS();
                break;

                // Запись сведений о магазине и коллекции игр в CSV-файл
            case CMD_SAVE_CSV:
                app->doSaveToCsv();
                break;

                // Чтение сведений о магазине и коллекции игр из CSV-файла
            case CMD_LOAD_CSV:
                app->doLoadFromCsv();
                break;
            } // switch
        }
        catch (exception& ex) {
            // заливка экрана базовым цветом, вывод строки навигации с сообщением
            cout << color(mainColor) << cls;
            showNavBarMessage(hintColor, "  Ошибка в приложении, нажмите любую клавишу для продолжения");

            int width = 72;

            oss.str("");
            oss << endlm(4) << left
                << "\t" << setw(width) << " " << "\n"
                << "\t" << setw(width) << "    [Ошибка]" << "\n"
                << "\t    " << left << setw(width - 4) << ex.what() << right << "\n"
                << "\t" << setw(width) << " " << "\n"
                << "\t" << setw(width) << " " << "\n"
                << endlm(4)
                << right;
            showMessage(oss.str(), errColor, mainColor);
        } // try-catch

        getKey("    Нажмите любую клавишу для продолжения...");
    } // while

    delete app;
    cls();
    return 0;
} // main
