#pragma once

// ���������� ��������� - ���� ����� � �������
const short BLACK   = 0b0000;
const short BLUE    = 0b0001;
const short GREEN   = 0b0010;
const short CYAN    = 0b0011;
const short RED     = 0b0100;
const short MAGENTA = 0b0101;
const short YELLOW  = 0b0110;
const short GRAY    = 0b0111;

const short LTBLACK   = 0b1000;
const short LTBLUE    = 0b1001;
const short LTGREEN   = 0b1010;
const short LTCYAN    = 0b1011;
const short LTRED     = 0b1100;
const short LTMAGENTA = 0b1101;
const short LTYELLOW  = 0b1110;
const short WHITE     = 0b1111;

// ����� �� ������ ����
const short BLACK_ON_BLACK     = BLACK   | BLACK << 4;
const short BLUE_ON_BLACK      = BLUE    | BLACK << 4;
const short GREEN_ON_BLACK     = GREEN   | BLACK << 4;
const short CYAN_ON_BLACK      = CYAN    | BLACK << 4;
const short RED_ON_BLACK       = RED     | BLACK << 4;
const short MAGENTA_ON_BLACK   = MAGENTA | BLACK << 4;
const short YELLOW_ON_BLACK    = YELLOW  | BLACK << 4;
const short GRAY_ON_BLACK      = GRAY    | BLACK << 4;

const short LTBLACK_ON_BLACK   = LTBLACK   | BLACK << 4;
const short LTBLUE_ON_BLACK    = LTBLUE    | BLACK << 4;
const short LTGREEN_ON_BLACK   = LTGREEN   | BLACK << 4;
const short LTCYAN_ON_BLACK    = LTCYAN    | BLACK << 4;
const short LTRED_ON_BLACK     = LTRED     | BLACK << 4;
const short LTMAGENTA_ON_BLACK = LTMAGENTA | BLACK << 4;
const short LTYELLOW_ON_BLACK  = LTYELLOW  | BLACK << 4;
const short WHITE_ON_BLACK     = WHITE     | BLACK << 4;

// ����� �� c���� ����
const short BLACK_ON_BLUE     = BLACK   | BLUE << 4;
const short BLUE_ON_BLUE      = BLUE    | BLUE << 4;
const short GREEN_ON_BLUE     = GREEN   | BLUE << 4;
const short CYAN_ON_BLUE      = CYAN    | BLUE << 4;
const short RED_ON_BLUE       = RED     | BLUE << 4;
const short MAGENTA_ON_BLUE   = MAGENTA | BLUE << 4;
const short YELLOW_ON_BLUE    = YELLOW  | BLUE << 4;
const short GRAY_ON_BLUE      = GRAY    | BLUE << 4;

const short LTBLACK_ON_BLUE   = LTBLACK   | BLUE << 4;
const short LTBLUE_ON_BLUE    = LTBLUE    | BLUE << 4;
const short LTGREEN_ON_BLUE   = LTGREEN   | BLUE << 4;
const short LTCYAN_ON_BLUE    = LTCYAN    | BLUE << 4;
const short LTRED_ON_BLUE     = LTRED     | BLUE << 4;
const short LTMAGENTA_ON_BLUE = LTMAGENTA | BLUE << 4;
const short LTYELLOW_ON_BLUE  = LTYELLOW  | BLUE << 4;
const short WHITE_ON_BLUE     = WHITE     | BLUE << 4;

// (file continues - palette constants)
