#pragma once

// Allow use of some legacy C functions (e.g., sprintf)
#define _CRT_SECURE_NO_WARNINGS

// enable math constants
#include <corecrt_math_defines.h>

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <sstream>
#include <fstream>

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Code page used by console (1251 = Windows-1251)
constexpr auto CODE_PAGE = 1251;