#pragma once
#include "Palette.h"

// Common utility functions

// Window width for formatting
const int W = 84;

// Physical constants (for examples)
// Speed constant used in samples
const double C = 1'080'000'000;

// Initialize utilities and console (title default)
void init(const std::wstring &title = L"Console Application");

// Read a key with an optional message
int getKey(const std::string &message = "\t    Press any key to continue...");

// Random helpers
int    getRand(int    low, int    high);
double getRand(double low, double high);
float  getRand(float  low, float  high);
char   getRand(char   low, char   high);

// Console color helper
void setColor(short color);

// Read integer with prompt
int getInt();

// Navigation and UI helpers
void showNavBarMessage(short hintColor, const std::string &message);
void showNavBarMessage(short hintColor, short acctColor, const std::string &message);
void showUnderConstruction(short width, short mainColor, short infoColor);
void showMessage(const std::string &msg, short msgColor, short mainColor);

// Show input line with prompt (default message)
void showInputLine(const std::string &prompt = "Enter value:", short n = 19, short color = infoColor);

// Input format check
void checkInputFormat(std::istream& is);

// ---------------------------------------------------------------------------------
#pragma region WinAPI helpers
COORD getConsoleSize();
void showCursor(bool mode);
bool isCursor();
void gotoXY(short x, short y);
void getXY(COORD* position);
void cls();
#pragma endregion

#pragma region Stream helpers
// stream manipulators and helpers
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
