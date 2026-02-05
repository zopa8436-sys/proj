#pragma once
#include "pch.h"

// Note: common helper modules (Utils, Menu, Date, etc.) were moved to
// ../ModulesForNeeds to avoid duplication across tasks. If you need any
// of those modules, include them from that folder instead of keeping
// copies here.

class App {
    vector<float> v_;
    string binFile_;

    // steps of Task 1 implemented as separate functions
    void step_countNegative();
    void step_countOutsideInterval(float a, float b);
    void step_sumBeforeFirstMin();
    void step_sumBetweenFirstMinAndFirstMax();
    void step_selectNegatives();
    void step_selectOutsideInterval(float a, float b);
    void step_sortDescending();
    void step_sortByAbsAscending();
    void step_moveOutsideIntervalToEnd(float a, float b);

    float readFloatFromCin(const string &prompt);

    void saveToBinary() const;
    void loadFromBinary();

public:
    App();
    void run();
};
