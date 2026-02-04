#pragma once
#include "pch.h"
#include "GameStore.h"


// Приложение магазина компьютерных игр
class App
{
	GameStore store_;
	string fileName_;

	// показать вектор игр в табличном формамте
	static void showAsTable(const string& title, const vector<Game> games);

	// показать текущее состояние магазина
	void showAll(const string& title);

	void saveCsv();
	void loadCsv();

public:
	App() :App(GameStore(), "store.csv") {}
	App(const GameStore& store, const string& fileName) {
		store_ = store;
		fileName_ = fileName;
	} // App

	// показать текущее состояние магазина
	void doShowAll();

#pragma region Обработки по заданию

	// Формирование коллекции фабричным методом
	void doCreateFactoryCollection();

	// Добавление игры (фабричный метод)
	void doAddGame();

	// Редактирование игры по идентификатору (фабричный метод)
	void doEditGameById();

	// Удаление игры по идентификатору
	void doDeleteGameById();

	// Упорядочивание игр по идентификатору
	void doOrderById();

	// Упорядочить вывод игр по убыванию года издания
	void doOrderByYearDescending();

	// Упорядочить вывод игр по возрастанию цены
	void doOrderByPriceAscending();

	// Упорядочить вывод игр по убыванию проданных копий
	void doOrderBySoldCopiesDescending();

	// Выборка по диапазону цены (сортировка по возрастанию цены)
	void doFindByPriceRange();

	// Выборка по году издания (сортировка по жанру)
	void doFindByPubYear();

	// Выборка по ОС (сортировка по убыванию года издания)
	void doFindByOS();

	// Сохранение сведений о магазине в файл CSV
	void doSaveToCsv();

	// Восстановление сведений о магазине из файла CSV
	void doLoadFromCsv();

#pragma endregion
};
