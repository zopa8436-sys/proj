#pragma once
#include "pch.h"
#include "Game.h"

class GameFactory
{
	static vector<string> titles_;
	static vector<string> os_;
	static vector<string> genres_;
	static vector<string> publishers_;
	static vector<string> developers_;
	static vector<string> ageCategories_;

public:
	GameFactory() = default;
	GameFactory(const GameFactory& other) = default;
	~GameFactory() = default;
	GameFactory& operator=(const GameFactory& other) = default;

	static Game create(int idSeed);

	static vector<Game> create(int n, int idSeed);
};
