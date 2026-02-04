#include "pch.h"
#include "Game.h"
#include "Utils.h"

Game::Game() :
	Game(
		1001, "Game Title"s, "Windows"s, 2022,
		"Action"s, "Publisher"s, "Developer"s,
		150000, true, "16+"s, 1999
	)
{
} // Game::Game


Game::Game(
	int id, const string& title, const string& os, int year,
	const string& genre, const string& publisher, const string& developer,
	int soldCopies, bool multiplayer, const string& ageCategory, int price
)
{
	id_ = id;
	this->title(title);
	this->os(os);
	this->year(year);
	this->genre(genre);
	this->publisher(publisher);
	this->developer(developer);
	this->soldCopies(soldCopies);
	this->multiplayer(multiplayer);
	this->ageCategory(ageCategory);
	this->price(price);
} // Game::Game


// аксессоры
int Game::id() const { return id_; } // Game::id


string Game::title() const { return title_; } // Game::title
void Game::title(const string& value) {
	title_ = value.empty()
		? throw exception("Game: Пустое название игры.")
		: value;
} // Game::title


string Game::os() const { return os_; } // Game::os
void Game::os(const string& value) {
	os_ = value.empty()
		? throw exception("Game: Пустая операционная система.")
		: value;
} // Game::os


int Game::year() const { return year_; } // Game::year
void Game::year(int value) {
	year_ = value < 1990 or value > getCurrentYear()
		? throw exception("Game: Недопустимый год издания.")
		: value;
} // Game::year


string Game::genre() const { return genre_; } // Game::genre
void Game::genre(const string& value) {
	genre_ = value.empty()
		? throw exception("Game: Пустой жанр.")
		: value;
} // Game::genre


string Game::publisher() const { return publisher_; } // Game::publisher
void Game::publisher(const string& value) {
	publisher_ = value.empty()
		? throw exception("Game: Пустой издатель.")
		: value;
} // Game::publisher


string Game::developer() const { return developer_; } // Game::developer
void Game::developer(const string& value) {
	developer_ = value.empty()
		? throw exception("Game: Пустой разработчик.")
		: value;
} // Game::developer


int Game::soldCopies() const { return soldCopies_; } // Game::soldCopies
void Game::soldCopies(int value) {
	soldCopies_ = value < 0
		? throw exception("Game: Недопустимое количество проданных копий.")
		: value;
} // Game::soldCopies


bool Game::multiplayer() const { return multiplayer_; } // Game::multiplayer
void Game::multiplayer(bool value) { multiplayer_ = value; } // Game::multiplayer


string Game::ageCategory() const { return ageCategory_; } // Game::ageCategory
void Game::ageCategory(const string& value) {
	ageCategory_ = value.empty()
		? throw exception("Game: Пустая возрастная категория.")
		: value;
} // Game::ageCategory


int Game::price() const { return price_; } // Game::price
void Game::price(int value) {
	price_ = value <= 0
		? throw exception("Game: Недопустимая цена.")
		: value;
} // Game::price


string Game::toString() {
	return "Game { id: "s + to_string(id_) +
		", title: '"s + title_ + "'s" +
		", os: "s + os_ +
		", year: "s + to_string(year_) +
		", genre: "s + genre_ +
		", publisher: "s + publisher_ +
		", developer: "s + developer_ +
		", sold: "s + to_string(soldCopies_) +
		", players: "s + (multiplayer_ ? "мультиплеер"s : "однопользовательская"s) +
		", age: "s + ageCategory_ +
		", price: "s + to_string(price_) +
		" }"s;
} // Game::toString


string Game::toTableRow(int row) {
	ostringstream oss;

	string players = multiplayer_ ? "мультиплеер"s : "однопользовательская"s;

	oss << "| " << setw(3) << row
		<< " | " << setw(4) << id_
		<< " | " << setw(22) << left << title_
		<< " | " << setw(10) << os_
		<< " | " << setw(4) << year_
		<< " | " << setw(12) << genre_
		<< " | " << setw(12) << publisher_
		<< " | " << setw(12) << developer_ << right
		<< " | " << setw(8) << soldCopies_
		<< " | " << setw(20) << left << players << right
		<< " | " << setw(4) << ageCategory_
		<< " | " << setw(5) << price_
		<< " |";

	return oss.str();
} // Game::toTableRow

string Game::header() {
	return "\t+-----+------+------------------------+------------+------+--------------+--------------+--------------+----------+----------------------+------+-------+\n"s
		"\t|  No |  Ид. | Название игры           | ОС         | Год  | Жанр         | Издатель     | Разработчик  | Продано  | Игроки               | Возр | Цена  |\n"s
		"\t+-----+------+------------------------+------------+------+--------------+--------------+--------------+----------+----------------------+------+-------+\n"s;
} // Game::header


string Game::footer() {
	return "\t+-----+------+------------------------+------------+------+--------------+--------------+--------------+----------+----------------------+------+-------+\n"s;
} // Game::footer
