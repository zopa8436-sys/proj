#include "pch.h"

#include "Game.h"
#include "GameFactory.h"

#include "Utils.h"


vector<string> GameFactory::titles_ = {
	"Night Runner", "Skyline Drift", "Quantum Fields", "Red Fortress", "Silent Harbor",
	"Crystal Rift", "Iron Protocol", "Neon Circuit", "Winter Siege", "Echoes of Mars",
	"Last Signal", "Frontier Dawn", "Shadow District", "Aurora Line", "Steel Horizon"
};

vector<string> GameFactory::os_ = {
	"Windows", "Linux", "macOS"
};

vector<string> GameFactory::genres_ = {
	"Action", "RPG", "Strategy", "Adventure", "Shooter", "Simulation", "Racing", "Puzzle"
};

vector<string> GameFactory::publishers_ = {
	"ArcLight", "NovaWorks", "SilverGate", "OrionSoft", "BlueBrick", "PixelForge"
};

vector<string> GameFactory::developers_ = {
	"Team North", "Studio K", "RedFox Lab", "IronTree", "CloudNine", "Delta Dev"
};

vector<string> GameFactory::ageCategories_ = {
	"0+", "6+", "12+", "16+", "18+"
};


Game GameFactory::create(int idSeed) {
	int iTitle = getRand(0, (int)titles_.size() - 1);
	int iOs = getRand(0, (int)os_.size() - 1);
	int iGenre = getRand(0, (int)genres_.size() - 1);
	int iPublisher = getRand(0, (int)publishers_.size() - 1);
	int iDeveloper = getRand(0, (int)developers_.size() - 1);
	int iAge = getRand(0, (int)ageCategories_.size() - 1);

	int year = getRand(2000, getCurrentYear());
	int sold = getRand(10000, 2000000);
	bool multiplayer = getRand(0, 1) == 1;
	int price = getRand(499, 6999);

	return Game(
		idSeed,
		titles_[iTitle],
		os_[iOs],
		year,
		genres_[iGenre],
		publishers_[iPublisher],
		developers_[iDeveloper],
		sold,
		multiplayer,
		ageCategories_[iAge],
		price
	);
} // GameFactory::create


vector<Game> GameFactory::create(int n, int idSeed) {

	vector<Game> games(n);

	generate(games.begin(), games.end(), [&idSeed]() { return create(idSeed++); });

	return games;
} // GameFactory::create
