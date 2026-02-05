�>>�#pragma once

// д�>>я испо�>>ьзования с�'ар�<х, не�+/-езопасн�<х функ�-ий, например sprintf()
#define _CRT_SECURE_NO_WARNINGS

// испо�>>ьзование ма�'ема�'ических конс�'ан�', современн�<й с�'и�>>ь
#include <corecrt_math_defines.h>

#include <iostream>  // э�'о�' фай�>> де�>>ае�' дос�'упн�<ми инженерн�<е функ�-ии  
#include <iomanip>   // д�>>я манипу�>>я�'оров в�<вода setw(), setprecision()
#include <Windows.h> // д�>>я испо�>>ьзования функ�-ий WinAPI
#include <conio.h>
#include <sstream>   // д�>>я о�+/-ъек�'а ostringstream
#include <fstream>

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// о�+/-ъяв�>>ение симво�>>ической конс�'ан�'�< - кодовой с�'рани�-�< (UTF-8)
constexpr auto CODE_PAGE = 65001;
