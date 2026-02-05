#include "../Task1/pch.h"
// Модуль вспомогательных функций
#include "Utils.h"
#include "Colors.h"
#include "Palette.h"

// ����������� ���������� - ��������-���������� ����������
// ���������� ����������, ��������� ������ � ������� �����
// ��������� ���� - ������������ ����������
// ����� ����� ���������� == ����� ����� (������) ���������
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void init(const wstring &title) {
	SetConsoleTitle(title.c_str());
	SetConsoleOutputCP(CODE_PAGE);
	SetConsoleCP(CODE_PAGE);
	srand(GetTickCount());
	cout << fixed << setprecision(2) << boolalpha;
	
	setColor(mainColor);
	cls();
} // init


// Получение клавиши с выводом сообщения
int getKey(const string &message) {
	cout << message;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	return key;
} // getKey


// Генерация псевдослучайного целого в диапазоне [low, high]
int getRand(int low, int high) {
	return low + rand() % (high - low + 1);
} // getRand


// Генерация псевдослучайного double в диапазоне [low, high]
double getRand(double low, double high) {
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// Генерация псевдослучайного float в диапазоне [low, high]
float getRand(float low, float high) {
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// Генерация псевдослучайного символа в диапазоне [low, high]
char getRand(char low, char high) {
	return (char)getRand((int)low, (int)high);
} // getRand


// Установка цвета вывода в консоли
// Используется дескриптор консоли h
void setColor(short color) {
	SetConsoleTextAttribute(h, color);
} // setColor


// ���� ������ �����
int getInt() {
	int value;
	while(true) {
			// Запрос значения
			cout << "? ";
		cin >> value;
			// Если ввод корректен — выходим
			if (!cin.fail()) break;

			// Иначе очищаем состояние и пропускаем остаток строки
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
	} // while

	return value;
} // getInt


// �������� ������� �����
void checkInputFormat(istream& is) {
	// �������� ������� �����
	if (is.fail()) {
		// ����� �������� ������ � ������� ������ �����
		is.clear();
		is.ignore(is.rdbuf()->in_avail(), '\n');

		// Выбрасываем исключение об ошибке формата ввода
		throw exception("Некорректный ввод");
	} // if	
} // checkInputFormat


// ����� ������� ������ ���� - ������ ��������� ��� ���������� �����
void showNavBarMessage(short hintColor, const string &message) {
	setColor(hintColor);

	gotoXY(0, 0);

	// Вычисление размеров консоли (WinAPI)
	const COORD conSize = getConsoleSize();
	cout << setw(conSize.X) << left << message << right;
	setColor(mainColor);

	gotoXY(0, 4);
} // showNavBarMessage


// ����� ������� ������ ���� - ������ ��������� ��� ���������� �����,
// ������������������, ���������� ��������� ~~ ������� ������ acctColor
void showNavBarMessage(short hintColor, short acctColor, const string &message) {
	setColor(hintColor);
	gotoXY(0, 0);

	// ���������� � ���� ������ ������� (WinAPI)
	const COORD conSize = getConsoleSize();

	// ���� ������ ������ � ����������� ������
	bool acctFlag = false;
	int len = 0;
	for (int i = 0; message[i] != 0; i++) {
		if (message[i] == '~') { 
			setColor(!acctFlag?acctColor:hintColor);
			acctFlag = !acctFlag;
			continue;
		} // if

		cout << message[i];
		++len;
	} // for i 

	// ������� "�����" �����
	cout << setw(conSize.X - len - 1) << " ";
	setColor(mainColor);

	gotoXY(0, 4);
} // showNavBarMessage


// ����� ��������� "������� � ����������"
void showUnderConstruction(short width, short mainColor, short infoColor) {
	ostringstream oss;
	oss << "\n\n\n\n" << left
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    [В разработке]" << "\n"
		<< "\t" << setw(width) << "    Функция в разработке" << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    Этот раздел пока недоступен..." << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << " " << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << right;
	showMessage(oss.str(), infoColor, mainColor);
} // showUnderConstruction


// ����� ���������
void showMessage(const string &msg, short msgColor, short mainColor) {
	setColor(msgColor);
	cout << left << msg << right;
	setColor(mainColor);
} // showMessage


// ����� ����������� �� �����, ������������� ������ �����, ���� �������������
// � �������� color
void showInputLine(const string &prompt, short n, short color) {
	// ������� ��������� �����
	cout << prompt;               
	
	COORD pos;
	getXY(&pos);

	// �������� ���� � ������� "������ �����"
	setColor(color);              
	cout << setw(n) << "  ";

	// ����������� ������ � ������ "������ �����"
	gotoXY(pos.X + 1, pos.Y);
} // showInputLine


// ---------------------------------------------------------------------------------
#pragma region ����������_��������_�_WinAPI
// ��������� ��� ���������� ������� �������
// mode: true  - �������� ������
//       false - ��������� ������
void showCursor(bool mode) {
	// ��������� winAPI
	CONSOLE_CURSOR_INFO info;

	// ��������� ������ � ��� ���������, ������������ ���
	// ���� ���������� �������� & - �� ���� ��� ��� ���������
	// ������ ����������

	// h - ����� �������
	// info - ��������� �� ���������
	GetConsoleCursorInfo(h, &info);

	info.bVisible = mode;
	SetConsoleCursorInfo(h, &info);
} // void showCursor


// ���������� �������� ��������� ������� - true: ������� ��� false: �� �������
bool isCursor() {
	CONSOLE_CURSOR_INFO info;

	// h - ����� �������
	// info - ��������� �� ���������
	GetConsoleCursorInfo(h, &info);

	return info.bVisible;
} // isCursorVisible


// ���������������� ������� � �������� ������� �������
void gotoXY(short x, short y) {
	SetConsoleCursorPosition(h, COORD{ x, y });
} // gotoXY


// �������� ������� ������� �������
void getXY(COORD* position) {
	CONSOLE_SCREEN_BUFFER_INFO cbuf;
	GetConsoleScreenBufferInfo(h, &cbuf);

	position->X = cbuf.dwCursorPosition.X;
	position->Y = cbuf.dwCursorPosition.Y;
} // getXY

// TODO: �������� ���� � ������� ������� �������


// ������� ������ �������
void cls() {
	COORD coordScreen = { 0, 0 }; // �������� ������� ��� �������
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	// ������� ����� ���������� ����� � ������� ������.

	if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

	// ������ ���� ������� � ��������
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// �������� ��������� ����� ��������� - ��� � ���� �������
	// cCharsWritten - ������� ���������� ��������
	if (!FillConsoleOutputCharacter(h, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	// ��������� ��������������� �������� ������ �� ������� ���������.
	if (!FillConsoleOutputAttribute(h, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// �������� ������ � ��������� ������� ����� ������� ������ - ������� ����� ����
	SetConsoleCursorPosition(h, coordScreen);
} // cls


// ��������� ������� ������ �������
COORD getConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	return csbi.dwSize;
} // getConsoleSize
#pragma endregion


#pragma region ���������� ������������� ������
// "�����������" ������ ��� ���������� ��� ������� ������
// cout << cls;
ostream& cls(ostream& os) {
	cls();
	return os;
} // cls


// "�����������" ����� ��� ���������� ��� ������� ������
// cin >> cls;
istream& cls(istream& is) {
	cls();
	return is;
} // cls


// "�����������" ������ ��� ���������� ��� ������ ������� ���������
// cout << tab;
ostream& tab(ostream& os) {
	os << "\t";
	return os;
} // tab


// "�����������" ������ ��� ��������� ���������� �������
ostream& cursor(ostream& os) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ������ - ������ ��� ����������� �����������
	// � ������� �������� ������
	return os;
} // cursor


// "�����������" ����� ��� ��������� ���������� �������
istream& cursor(istream& is) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ����� - ������ ��� ����������� �����������
	// � ������� �������� �����
	return is;
} // cursor


// "�����������" ������ ��� ���������� ���������� �������
ostream& nocursor(ostream& os) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ������ - ������ ��� ����������� �����������
	// � ������� �������� ������
	return os;
} // nocursor


// "�����������" ����� ��� ���������� ���������� �������
istream& nocursor(istream& is) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ����� - ������ ��� ����������� �����������
	// � ������� �������� �����
	return is;
} // nocursor


// "�����������" ������ � ���������� ��� ������
// ��������� ���������� �������� �������� ������
ostream& operator<<(ostream& os, const endlm& obj) {
	for (int i = 0; i < obj.n_; ++i) {
		os << "\n";
	}
	return os;
} // operator<<


// "�����������" ������ � ���������� ��� ��������� ����� ������� 
// � ����� ����
ostream& operator<<(ostream& os, const color& obj) {
	SetConsoleTextAttribute(h, obj.color_);
	return os;
} // operator<<


// "�����������" ����� � ���������� ��� ��������� ����� ������� 
// � ����� ����
istream& operator>>(istream& is, const color& obj) {
	SetConsoleTextAttribute(h, obj.color_);
	return is;
} // operator>>


// "�����������" ������ � ���������� ��� ��������� ������� ������� � ������� 
ostream& operator<<(ostream& os, const pos& obj) {
	SetConsoleCursorPosition(h, { obj.x_, obj.y_ });
	return os;
} // operator<<

// "�����������" ����� � ���������� ��� ��������� ������� ������� � ������� 
istream& operator>>(istream& is, const pos& obj) {
	SetConsoleCursorPosition(h, { obj.x_, obj.y_ });
	return is;
} // operator>>
#pragma endregion


// �������� ������� ���
int getCurrentYear() {
	time_t t = time(nullptr);
	struct tm tm = *localtime(&t);
	return (tm.tm_year + 1900);
} // getCurrentYear
