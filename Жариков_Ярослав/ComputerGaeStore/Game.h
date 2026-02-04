#pragma once
#include "pch.h"

/*
 * —ведени€ об игре:
 *     Х идентификатор
 *     Х название игры
 *     Х операционна€ система
 *     Х год
 *     Х жанр
 *     Х издатель
 *     Х разработчик
 *     Х продано копий
 *     Х многопользовательска€ (bool)
 *     Х возрастна€ категори€ игроков
 *     Х цена (int)
 */
class Game
{
	int    id_;
	string title_;
	string os_;
	int    year_;
	string genre_;
	string publisher_;
	string developer_;
	int    soldCopies_;
	bool   multiplayer_;
	string ageCategory_;
	int    price_;

public:
	Game();
	Game(
		int id, const string& title, const string& os, int year,
		const string& genre, const string& publisher, const string& developer,
		int soldCopies, bool multiplayer, const string& ageCategory, int price
	);

	// аксессоры
	int id() const;

	string title() const;
	void title(const string& value);

	string os() const;
	void os(const string& value);

	int year() const;
	void year(int value);

	string genre() const;
	void genre(const string& value);

	string publisher() const;
	void publisher(const string& value);

	string developer() const;
	void developer(const string& value);

	int soldCopies() const;
	void soldCopies(int value);

	bool multiplayer() const;
	void multiplayer(bool value);

	string ageCategory() const;
	void ageCategory(const string& value);

	int price() const;
	void price(int value);

	string toString();

	string toTableRow(int row);

	static string header();
	static string footer();
};
