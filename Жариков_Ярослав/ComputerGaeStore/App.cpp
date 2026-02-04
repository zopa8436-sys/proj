#include "pch.h"
#include "GameFactory.h"
#include "Utils.h"
#include "App.h"

void App::showAsTable(const string& title, const vector<Game> games) {
	cout << title << "\n" << Game::header();

	int row = 1;
	for_each(games.begin(), games.end(), [&row](Game game) {
		cout << "\t" << game.toTableRow(row++) << "\n";
		});

	cout << Game::footer();
} // App::showAsTable


void App::showAll(const string& title) {
	showAsTable(title, store_.games());
} // App::showAll


void App::doShowAll() {
	showNavBarMessage(hintColor, "    Магазин компьютерных игр. Текущее состояние");
	showAll("\t" + store_.name() + " | " + store_.address());
} // App::doShowAll


#pragma region Обработки по заданию


void App::doCreateFactoryCollection() {
	showNavBarMessage(hintColor, "    Магазин. Формирование коллекции (фабричный метод)");

	COORD position;
	getXY(&position);
	int n = getRand(12, 15);
	store_.createFactory(n, 1001);

	cout << pos(0, position.Y) << setw(90) << " " << "\r";
	showAll("\tКаталог сформирован заново (фабричный метод), количество игр: " + to_string(n));
} // App::doCreateFactoryCollection


void App::doAddGame() {
	showNavBarMessage(hintColor, "    Магазин. Добавление игры (фабричный метод)");

	auto games = store_.games();

	int idMax = games.empty()
		? 1000
		: max_element(games.begin(), games.end(),
			[](const Game& g1, const Game& g2) { return g1.id() < g2.id(); })->id();

	Game game = GameFactory::create(idMax + 1);

	store_.add(game);

	showAll("\tВ каталог добавлена игра с ид. " + to_string(game.id()));
} // App::doAddGame

void App::doEditGameById() {
	showNavBarMessage(hintColor, "    Магазин. Редактирование игры по идентификатору (фабричный метод)");

	showAll("\tКаталог");

	int id;
	COORD position;
	cout << "\n\tИдентификатор редактируемой игры: "
		<< color(infoColor) << setw(30) << " ";
	getXY(&position);
	cin >> pos(position.X - 29, position.Y) >> id >> color(mainColor);
	checkInputFormat(cin);

	store_.updateGameByIdFactory(id);

	cout << pos(0, position.Y) << setw(90) << " " << "\r";
	showAll("\tКаталог после редактирования игры с ид: " + to_string(id));
} // App::doEditGameById

void App::doDeleteGameById() {
	showNavBarMessage(hintColor, "    Магазин. Удаление игры по идентификатору");

	showAll("\tКаталог");

	int id;
	COORD position;
	cout << "\n\tИдентификатор удаляемой игры: "
		<< color(infoColor) << setw(30) << " ";
	getXY(&position);
	cin >> pos(position.X - 29, position.Y) >> id >> color(mainColor);
	checkInputFormat(cin);

	store_.deleteGameById(id);

	cout << pos(0, position.Y) << setw(90) << " " << "\r";
	showAll("\tКаталог после удаления игры с ид: " + to_string(id));
} // App::doDeleteGameById


void App::doOrderById() {
	showNavBarMessage(hintColor, "    Магазин. Упорядочивание игр по идентификатору");

	store_.orderByid();
	showAll("\tКаталог упорядочен по идентификаторам");
} // App::doOrderById

void App::doOrderByYearDescending() {
	showNavBarMessage(hintColor, "    Магазин. Упорядочивание по убыванию года издания");

	store_.orderByYearDescending();
	showAll("\tКаталог, упорядоченный по убыванию года издания");
} // App::doOrderByYearDescending


void App::doOrderByPriceAscending() {
	showNavBarMessage(hintColor, "    Магазин. Упорядочивание по возрастанию цены");

	store_.orderByPriceAscending();
	showAll("\tКаталог, упорядоченный по возрастанию цены");
} // App::doOrderByPriceAscending


void App::doOrderBySoldCopiesDescending() {
	showNavBarMessage(hintColor, "    Магазин. Упорядочивание по убыванию проданных копий");

	store_.orderBySoldCopiesDescending();
	showAll("\tКаталог, упорядоченный по убыванию проданных копий");
} // App::doOrderBySoldCopiesDescending

void App::doFindByPriceRange() {
	showNavBarMessage(hintColor, "    Магазин. Выборка по диапазону цен (сортировка по цене)");

	showAll("\tКаталог");

	int minPrice, maxPrice;
	COORD position;
	cout << "\n\tМинимальная цена: "
		<< color(infoColor) << setw(30) << " ";
	getXY(&position);
	cin >> pos(position.X - 29, position.Y) >> minPrice >> color(mainColor);
	checkInputFormat(cin);

	cout << "\n\tМаксимальная цена: "
		<< color(infoColor) << setw(30) << " ";
	getXY(&position);
	cin >> pos(position.X - 29, position.Y) >> maxPrice >> color(mainColor);
	checkInputFormat(cin);

	if (minPrice > maxPrice)
	{
		throw exception("minPrice не должен быть больше maxPrice");
	} // if

	vector<Game> selected = store_.findGamesByPriceRange(minPrice, maxPrice);

	showAsTable("\tВыборка по диапазону цен [" + to_string(minPrice) + "; " + to_string(maxPrice) + "]", selected);
} // App::doFindByPriceRange


void App::doFindByPubYear() {
	showNavBarMessage(hintColor, "    Магазин. Выборка по году издания (сортировка по жанру)");

	showAll("\tКаталог");

	int year;
	COORD position;
	cout << "\n\tГод издания для отбора: "
		<< color(infoColor) << setw(30) << " ";
	getXY(&position);
	cin >> pos(position.X - 29, position.Y) >> year >> color(mainColor);
	checkInputFormat(cin);

	vector<Game> selected = store_.findGamesByPubYear(year);

	showAsTable("\tВыборка игр за " + to_string(year) + " год (сортировка по жанру)", selected);
} // App::doFindByPubYear


void App::doFindByOS() {
	showNavBarMessage(hintColor, "    Магазин. Выборка по ОС (сортировка по убыванию года)");

	showAll("\tКаталог");

	COORD position;
	cout << "\n\tОперационная система для отбора: "
		<< color(infoColor) << setw(30) << " " << color(mainColor);

	getXY(&position);
	gotoXY(position.X - 29, position.Y);

	string os;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, os);
	setColor(mainColor);

	vector<Game> selected = store_.findGamesByOS(os);

	showAsTable("\tВыборка игр по ОС \"" + os + "\" (сортировка по убыванию года)", selected);
} // App::doFindByOS

#pragma endregion

void App::doSaveToCsv() {
	showNavBarMessage(hintColor, "    Магазин. Сохранение сведений в файл формата CSV");

	saveCsv();

	auto title = "\tСведения о магазине сохранены в файл '" + fileName_ + "'\n" +
		"\t" + store_.name() + " | " + store_.address();
	showAll(title);
} // App::doSaveToCsv


void App::doLoadFromCsv() {
	showNavBarMessage(hintColor, "    Магазин. Восстановление сведений из файла формата CSV");

	loadCsv();

	auto title = "\tСведения о магазине восстановлены из файла '" + fileName_ + "'\n" +
		"\t" + store_.name() + " | " + store_.address();
	showAll(title);
} // App::doLoadFromCsv


void App::saveCsv() {
	if (fileName_.empty()) {
		throw exception("CSV: пустое имя файла.");
	} // if

	ofstream out(fileName_, ios::out | ios::trunc);
	if (!out.is_open()) {
		throw exception(("CSV: не удалось открыть файл '" + fileName_ + "' для записи.").c_str());
	} // if

	out << store_.name() << ";" << store_.address() << "\n";

	auto games = store_.games();
	for_each(games.begin(), games.end(), [&out](const Game& g) {
		out << g.id() << ";"
			<< g.title() << ";"
			<< g.os() << ";"
			<< g.year() << ";"
			<< g.genre() << ";"
			<< g.publisher() << ";"
			<< g.developer() << ";"
			<< g.soldCopies() << ";"
			<< (g.multiplayer() ? 1 : 0) << ";"
			<< g.ageCategory() << ";"
			<< g.price()
			<< "\n";
		});

	if (out.fail()) {
		throw exception("CSV: ошибка записи в файл.");
	} // if
} // App::saveCsv

void App::loadCsv() {
	if (fileName_.empty()) {
		throw exception("CSV: пустое имя файла.");
	} // if

	ifstream in(fileName_);
	if (!in.is_open()) {
		throw exception(("CSV: не удалось открыть файл '" + fileName_ + "' для чтения.").c_str());
	} // if

	string line;

	if (!getline(in, line)) {
		throw exception("CSV: файл пуст.");
	} // if

	{
		istringstream iss(line);
		string name, address;

		if (!getline(iss, name, ';') || !getline(iss, address)) {
			throw exception("CSV: неверная 1-я строка (название; адрес).");
		} // if

		store_.name(name);
		store_.address(address);
	}

	vector<Game> loaded;

	// строки игр:
	// id;title;os;year;genre;publisher;developer;soldCopies;multiplayer;ageCategory;price
	while (getline(in, line)) {
		if (line.empty()) continue;

		istringstream iss(line);

		int id, year, sold, mp, price;
		string title, os, genre, publisher, developer, age;

		iss >> id;
		checkInputFormat(iss);

		if (iss.get() != ';') throw exception("CSV: неверный формат строки игры.");

		if (!getline(iss, title, ';')) throw exception("CSV: неверный формат строки игры.");
		if (!getline(iss, os, ';')) throw exception("CSV: неверный формат строки игры.");

		iss >> year;
		checkInputFormat(iss);
		if (iss.get() != ';') throw exception("CSV: неверный формат строки игры.");

		if (!getline(iss, genre, ';')) throw exception("CSV: неверный формат строки игры.");
		if (!getline(iss, publisher, ';')) throw exception("CSV: неверный формат строки игры.");
		if (!getline(iss, developer, ';')) throw exception("CSV: неверный формат строки игры.");

		iss >> sold;
		checkInputFormat(iss);
		if (iss.get() != ';') throw exception("CSV: неверный формат строки игры.");

		iss >> mp;
		checkInputFormat(iss);
		if (mp != 0 and mp != 1) {
			throw exception("CSV: неверное значение мультиплеера (должно быть 0 или 1).");
		} // if

		if (iss.get() != ';') throw exception("CSV: неверный формат строки игры.");

		if (!getline(iss, age, ';')) throw exception("CSV: неверный формат строки игры.");

		iss >> price;
		checkInputFormat(iss);

		loaded.emplace_back(id, title, os, year, genre, publisher, developer, sold, mp ==1 , age, price);
	} // while

	if (loaded.empty()) {
		throw exception("CSV: в файле нет игр для загрузки.");
	} // if

	store_.games(loaded);
} // App::loadCsv
