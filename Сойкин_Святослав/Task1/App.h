#pragma once
#include "pch.h"

class App {
    vector<float> v_;
    string binFile_;

    static float randFloat(float low, float high);
    static float readFloatFromCin(const string &prompt);

    void saveToBinary() const;
    void loadFromBinary();

public:
    App();
    void run();
};
