// ����� �������� �������
#include "pch.h"
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


// ��������� ���� ������� �������
int getKey(const string &message) {
    cout << message;
    int key = _getch();
    if (key == 0 || key == 224) key = _getch();

    return key;
} // getKey


// ��������� ���������� ����� ���� int � ��������� [low, high]
int getRand(int low, int high) {
    return low + rand() % (high - low + 1);
} // getRand


// ��������� ���������� ����� ���� double � ��������� [low, high]
double getRand(double low, double high) {
    return low + (high - low) * rand() / RAND_MAX;
} // getRand


// ��������� ���������� ����� ���� flost � ��������� [low, high]
float getRand(float low, float high) {
    return low + (high - low) * rand() / RAND_MAX;
} // getRand


// ��������� ���������� ������� � ��������� [low, high]
char getRand(char low, char high) {
    return (char)getRand((int)low, (int)high);
} // getRand


// ������� ����� �������
// ������������� ����������� ���������� h
void setColor(short color) {
    SetConsoleTextAttribute(h, color);
} // setColor


// ���� ������ �����
int getInt() {
    int value;
    while(true) {
        // ���������� ����
        cout << "? ";
        cin >> value;

        // ���� ����� �����, ����� �� ����� � �� �������
        if (!cin.fail()) break;

        // ���� ��� �� ����� - ����� ��������� ������,
        // ������� ������ �����
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

        // ������ ����������
        throw exception("������� �� �����");
    } // if    
} // checkInputFormat


// ����� ������� ������ ���� - ������ ��������� ��� ���������� �����
void showNavBarMessage(short hintColor, const string &message) {
    setColor(hintColor);

    gotoXY(0, 0);

    // ���������� � ���� ������ ������� (WinAPI)
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
        << "\t" << setw(width) << "    [����������]" << "\n"
        << "\t" << setw(width) << "    ������� � ����������" << "\n"
        << "\t" << setw(width) << " " << "\n"
        << "\t" << setw(width) << "    ������� ����� ������� ��� �����������..." << "\n"
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
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);

    info.bVisible = mode;
    SetConsoleCursorInfo(h, &info);
} // void showCursor


bool isCursor() {
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);

    return info.bVisible;
} // isCursorVisible


void gotoXY(short x, short y) {
    SetConsoleCursorPosition(h, COORD{ x, y });
} // gotoXY


void getXY(COORD* position) {
    CONSOLE_SCREEN_BUFFER_INFO cbuf;
    GetConsoleScreenBufferInfo(h, &cbuf);

    position->X = cbuf.dwCursorPosition.X;
    position->Y = cbuf.dwCursorPosition.Y;
} // getXY


void cls() {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(h, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
        return;

    if (!FillConsoleOutputAttribute(h, csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten))
        return;

    SetConsoleCursorPosition(h, coordScreen);
} // cls


COORD getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);

    return csbi.dwSize;
} // getConsoleSize
#pragma endregion


#pragma region ���������� ������������� ������
ostream& cls(ostream& os) { cls(); return os; }
istream& cls(istream& is) { cls(); return is; }
ostream& tab(ostream& os) { os << "\t"; return os; }

ostream& cursor(ostream& os) { CONSOLE_CURSOR_INFO info; GetConsoleCursorInfo(h, &info); info.bVisible = true; SetConsoleCursorInfo(h, &info); return os; }
istream& cursor(istream& is) { CONSOLE_CURSOR_INFO info; GetConsoleCursorInfo(h, &info); info.bVisible = true; SetConsoleCursorInfo(h, &info); return is; }
ostream& nocursor(ostream& os) { CONSOLE_CURSOR_INFO info; GetConsoleCursorInfo(h, &info); info.bVisible = false; SetConsoleCursorInfo(h, &info); return os; }
istream& nocursor(istream& is) { CONSOLE_CURSOR_INFO info; GetConsoleCursorInfo(h, &info); info.bVisible = false; SetConsoleCursorInfo(h, &info); return is; }

ostream& operator<<(ostream& os, const endlm& obj) { for (int i = 0; i < obj.n_; ++i) os << "\n"; return os; }
ostream& operator<<(ostream& os, const color& obj) { SetConsoleTextAttribute(h, obj.color_); return os; }
istream& operator>>(istream& is, const color& obj) { SetConsoleTextAttribute(h, obj.color_); return is; }
ostream& operator<<(ostream& os, const pos& obj) { SetConsoleCursorPosition(h, { obj.x_, obj.y_ }); return os; }
istream& operator>>(istream& is, const pos& obj) { SetConsoleCursorPosition(h, { obj.x_, obj.y_ }); return is; }
#pragma endregion


int getCurrentYear() {
    time_t t = time(nullptr);
    struct tm tm = *localtime(&t);
    return (tm.tm_year + 1900);
} // getCurrentYear
