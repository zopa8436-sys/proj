#pragma once

// для использования старых, небезопасных функций, например sprintf()
#define _CRT_SECURE_NO_WARNINGS

// Кроссплатформенные заголовки
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#endif

using namespace std;

// объявление символической константы - кодовой страницы (для совместимости)
constexpr auto CODE_PAGE = 1251;