#pragma once
#include "pch.h"
#include "Game.h"

/*
 * Сведения о магазине:
 *     • название
 *     • адрес
 *     • коллекция игр
 */
class GameStore
{
	string name_;
	string address_;

	vector<Game> games_;

public:
	GameStore();
	GameStore(const string& name, const string& address, const vector<Game>& games);

	// аксессоры
	const string& name() const;
	void name(const string& value);

	const string& address() const;
	void address(const string& value);

	const vector<Game>& games() const;
	void games(const vector<Game>& value);

	void clearGames();

#pragma region Обработки по заданию

	// Формирование коллекции фабричным методом
	void createFactory(int n, int idSeed);

	// Добавление элемента в коллекцию (фабричным методом)
	void add(const Game& game);

	// Редактирование элемента коллекции (фабричным методом, ид вводится с клавиатуры)
	void updateGameByIdFactory(int id);

	// Удаление элемента из коллекции по идентификатору
	void deleteGameById(int id);

	// Упорядочивание игр по идентификатору
	void orderByid();

	// Упорядочите вывод игр по убыванию года издания
	void orderByYearDescending();

	// Упорядочите вывод игр по возрастанию цены
	void orderByPriceAscending();

	// Упорядочите вывод игр по убыванию количества проданных копий
	void orderBySoldCopiesDescending();

	// Выборка игр по диапазону цены, упорядочивание выборки по возрастанию цены.
	vector<Game> findGamesByPriceRange(int lowPrice, int highPrice);

	// Выборка игр по году издания, упорядочивание игр по жанру
	vector<Game> findGamesByPubYear(int pubYear);

	// Выборка игр по операционной системе, упорядочивание выборки по убыванию года издания
	vector<Game> findGamesByOS(const string& os);

#pragma endregion
};
