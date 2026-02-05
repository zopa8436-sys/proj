#pragma once
#include "Palette.h"

// Модуль вспомогательных функций

// Константа ширины вывода (форматирование)
const int W = 84;

// Пример числовой константы, используемой в примерах
const double C = 1'080'000'000;

// Инициализация утилит и консоли (по умолчанию заголовок окна)
void init(const std::wstring &title = L"Консольное приложение");

// Считать нажатие клавиши с опциональным сообщением
int getKey(const std::string &message = "\t    Нажмите любую клавишу для продолжения...");

// Функции генерации псевдослучайных чисел
int    getRand(int    low, int    high);
double getRand(double low, double high);
float  getRand(float  low, float  high);
char   getRand(char   low, char   high);

// Управление цветом консоли
void setColor(short color);

// Чтение целого с проверкой
int getInt();

// Навигация и вывод сообщений
void showNavBarMessage(short hintColor, const std::string &message);
void showNavBarMessage(short hintColor, short acctColor, const std::string &message);
void showUnderConstruction(short width, short mainColor, short infoColor);
void showMessage(const std::string &msg, short msgColor, short mainColor);

// Отображение строки ввода с подсказкой
void showInputLine(const std::string &prompt = "Введите значение:", short n = 19, short color = infoColor);

// Проверка формата ввода
void checkInputFormat(std::istream& is);

// ---------------------------------------------------------------------------------
#pragma region Функции работы с WinAPI
COORD getConsoleSize();
void showCursor(bool mode);
bool isCursor();
void gotoXY(short x, short y);
void getXY(COORD* position);
void cls();
#pragma endregion

#pragma region Вспомогательные манипуляторы потоков
ostream& cls(ostream& os);
istream& cls(istream& os);
ostream& tab(ostream& os);
ostream& cursor(ostream& os);
istream& cursor(istream& is);
ostream& nocursor(ostream& os);
istream& nocursor(istream& is);

class endlm
{
	int n_;
public:
	endlm(int n) : n_(n) {}
	friend ostream& operator<<(ostream& os, const endlm& obj);
};

class color
{
	short color_;
public:
	color(short color) : color_(color) {}
	friend ostream& operator<<(ostream& os, const color& obj);
	friend istream& operator>>(istream& is, const color& obj);
};

class pos
{
	short x_;
	short y_;
public:
	pos(short x, short y) : x_(x), y_(y) {}
	friend ostream& operator<<(ostream& os, const pos& obj);
	friend istream& operator>>(istream& is, const pos& obj);
};
#pragma endregion

inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }
inline bool eq(float d1, float d2) { return abs(d1 - d2) <= 1e-6; }

int getCurrentYear();
