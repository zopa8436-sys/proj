#include "pch.h"
#include "GameFactory.h"
#include "GameStore.h"
#include "Utils.h"


GameStore::GameStore() :
	GameStore("Магазин \"GameHub\""s, "г. Донецк, ул. Артёма, 1"s, GameFactory::create(getRand(12, 15), 1001))
{
} // GameStore::GameStore


GameStore::GameStore(const string& name, const string& address, const vector<Game>& games) {
	this->name(name);
	this->address(address);
	this->games(games);
} // GameStore::GameStore


// аксессоры
const string& GameStore::name() const { return name_; } // GameStore::name
void GameStore::name(const string& value) {
	name_ = value.empty()
		? throw exception("GameStore: Пустое название магазина.")
		: value;
} // GameStore::name


const string& GameStore::address() const { return address_; } // GameStore::address
void GameStore::address(const string& value) {
	address_ = value.empty()
		? throw exception("GameStore: Пустой адрес магазина.")
		: value;
} // GameStore::address


const vector<Game>& GameStore::games() const { return games_; } // GameStore::games
void GameStore::games(const vector<Game>& value) { games_ = value; } // GameStore::games

void GameStore::clearGames() { games_.clear(); } // GameStore::clearGames


#pragma region Обработки по заданию

void GameStore::createFactory(int n, int idSeed) {
	games_ = GameFactory::create(n, idSeed);
} // GameStore::createFactory


void GameStore::add(const Game& game) { games_.emplace_back(game); } // GameStore::add


void GameStore::updateGameByIdFactory(int id) {
	auto it = find_if(games_.begin(), games_.end(), [id](Game& game) {
		return game.id() == id;
		});

	if (it != games_.end()) {
		*it = GameFactory::create(id);
	} // if
} // GameStore::updateGameByIdFactory


void GameStore::deleteGameById(int id) {
	auto it = find_if(games_.begin(), games_.end(), [id](Game& game) {
		return game.id() == id;
		});

	if (it != games_.end()) {
		games_.erase(it);
	} // if
} // GameStore::deleteGameById


void GameStore::orderByid() {
	sort(games_.begin(), games_.end(), [](Game& g1, Game& g2) {
		return g1.id() < g2.id();
		});
} // GameStore::orderByid


void GameStore::orderByYearDescending() {
	sort(games_.begin(), games_.end(), [](Game& g1, Game& g2) {
		return g2.year() < g1.year();
		});
} // GameStore::orderByYearDescending


void GameStore::orderByPriceAscending() {
	sort(games_.begin(), games_.end(), [](Game& g1, Game& g2) {
		return g1.price() < g2.price();
		});
} // GameStore::orderByPriceAscending


void GameStore::orderBySoldCopiesDescending() {
	sort(games_.begin(), games_.end(), [](Game& g1, Game& g2) {
		return g2.soldCopies() < g1.soldCopies();
		});
} // GameStore::orderBySoldCopiesDescending


vector<Game> GameStore::findGamesByPriceRange(int lowPrice, int highPrice) {
	vector<Game> result;

	copy_if(games_.begin(), games_.end(), back_inserter(result),
		[lowPrice, highPrice](Game& game) {
			return game.price() >= lowPrice and game.price() <= highPrice;
		}
	);

	sort(result.begin(), result.end(), [](Game& g1, Game& g2) {
		return g1.price() < g2.price();
		});

	return result;
} // GameStore::findGamesByPriceRange


vector<Game> GameStore::findGamesByPubYear(int pubYear) {
	vector<Game> result;

	copy_if(games_.begin(), games_.end(), back_inserter(result),
		[pubYear](Game& game) {
			return game.year() == pubYear;
		}
	);

	sort(result.begin(), result.end(), [](Game& g1, Game& g2) {
		return g1.genre() < g2.genre();
		});

	return result;
} // GameStore::findGamesByPubYear


vector<Game> GameStore::findGamesByOS(const string& os) {
	vector<Game> result;

	copy_if(games_.begin(), games_.end(), back_inserter(result),
		[os](Game& game) {
			return game.os() == os;
		}
	);

	sort(result.begin(), result.end(), [](Game& g1, Game& g2) {
		return g2.year() < g1.year();
		});

	return result;
} // GameStore::findGamesByOS

#pragma endregion
