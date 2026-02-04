#pragma once
#include "pch.h"

class App {
    vector<float> v_;
    string binFile_;

    float readFloatFromCin(const string &prompt);

    void saveToBinary() const;
    void loadFromBinary();

public:
    App();
    void run();
};
