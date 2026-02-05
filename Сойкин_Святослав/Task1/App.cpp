#include "App.h"
#include "../Modules/Utils.h"
#include <iterator>

// App: реализация функций для задания 1

App::App() : binFile_("task1_vector.bin") {
    // создаём вектор размера [12,30] с псевдослучайными значениями
    int n = getRand(12, 30);
    v_.assign(n, 0.0f);
    generate(v_.begin(), v_.end(), []() { return getRand(-100.0f, 100.0f); });
}

// Чтение одного числа с проверкой формата ввода (согласно правилам)
float App::readFloatFromCin(const string &prompt) {
    showInputLine(prompt);
    float value;
    cin >> value;
    checkInputFormat(cin);
    return value;
}

void App::saveToBinary() const {
    ofstream out(binFile_, ios::binary | ios::out | ios::trunc);
    if (!out.is_open()) throw exception("Не удалось открыть файл для записи");

    size_t n = v_.size();
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    out.write(reinterpret_cast<const char*>(v_.data()), n * sizeof(float));
    if (out.fail()) throw exception("Ошибка записи в бинарный файл");
}

void App::loadFromBinary() {
    ifstream in(binFile_, ios::binary | ios::in);
    if (!in.is_open()) throw exception("Не удалось открыть файл для чтения");

    size_t n = 0;
    in.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (in.fail()) throw exception("Ошибка чтения размера из бинарного файла");

    vector<float> tmp(n);
    in.read(reinterpret_cast<char*>(tmp.data()), n * sizeof(float));
    if (in.fail()) throw exception("Ошибка чтения данных из бинарного файла");

    v_.swap(tmp);
}

void App::run() {
    // Сохраняем исходный вектор в бинарный файл перед обработками
    saveToBinary();

    // Ввод интервала [a,b]
    float a = readFloatFromCin("Введите a:");
    float b = readFloatFromCin("Введите b:");
    if (a > b) swap(a, b);

    // 1) количество отрицательных элементов
    const auto negCount = count_if(v_.begin(), v_.end(), [](float x){ return x < 0.0f; });

    // 2) количество элементов, не попадающих в [a,b]
    const auto notInInterval = count_if(v_.begin(), v_.end(), [a,b](float x){ return x < a || x > b; });

    // 3) сумма элементов перед первым минимальным элементом
    const auto itMin = min_element(v_.begin(), v_.end());
    const float sumBeforeMin = (itMin == v_.begin() || itMin == v_.end()) ? 0.0f : accumulate(v_.begin(), itMin, 0.0f);

    // 4) сумма между первым минимумом и первым максимумом (исключая их)
    const auto itMax = max_element(v_.begin(), v_.end());
    float sumBetween = 0.0f;
    if (itMin != v_.end() && itMax != v_.end() && itMin != itMax) {
        auto first = min(itMin, itMax);
        auto last = max(itMin, itMax);
        if (distance(first, last) > 1) sumBetween = accumulate(next(first), last, 0.0f);
    }

    // 5) отбор отрицательных элементов в отдельный вектор
    vector<float> negatives;
    negatives.reserve(negCount);
    copy_if(v_.begin(), v_.end(), back_inserter(negatives), [](float x){ return x < 0.0f; });

    // Вывод результатов напрямую через cout (одной цепочкой там, где возможно)
    cout << "Результаты обработки вектора (n=" << v_.size() << "):\n"
         << "Отрицательных элементов: " << negCount << " | "
         << "Не в [a,b]: " << notInInterval << " | "
         << "Сумма перед первым минимумом: " << sumBeforeMin << " | "
         << "Сумма между min и max: " << sumBetween << "\n";

    cout << "Отобранные отрицательные элементы (count=" << negatives.size() << "):\n";
    if (!negatives.empty()) {
        copy(negatives.begin(), negatives.end(), ostream_iterator<float>(cout, " "));
        cout << "\n";
    }

    // Восстанавливаем вектор из бинарного файла после обработок
    loadFromBinary();
    cout << "Вектор восстановлен из бинарного файла, размер=" << v_.size() << "\n";
}
