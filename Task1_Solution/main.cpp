#include "VectorTask1.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

static void printVectorOnce(const std::vector<float>& v, const std::string& title)
{
    std::ostringstream oss;
    oss << title << " (size=" << v.size() << "): ";
    for (std::size_t i = 0; i < v.size(); ++i) {
        oss << std::fixed << std::setprecision(3) << v[i];
        if (i + 1 < v.size()) oss << ", ";
    }
    std::cout << oss.str() << '\n';
}

int main()
{
    try {
        std::cout << "Task 1 — vector<float> processing (n in [12,30]) — automated run\n";

        // generate random n in [12,30] and random interval a<=b
        std::mt19937 rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution<int> distN(12, 30);
        int n = distN(rng);

        // choose a and b in range [-50,50]
        std::uniform_real_distribution<float> distInterval(-50.0f, 50.0f);
        float a = distInterval(rng);
        float b = distInterval(rng);
        if (a > b) std::swap(a, b);

        // generate random floats in [-100, 100]
        std::vector<float> data;
        data.reserve(static_cast<std::size_t>(n));
        std::uniform_real_distribution<float> dist(-100.0f, 100.0f);
        for (int i = 0; i < n; ++i) data.push_back(dist(rng));

        VectorProcessor vp(data);
        const std::string binFile = "vector_before.bin";
        vp.saveToBinary(binFile);
        std::cout << "Chosen n=" << n << ", interval a=" << a << ", b=" << b << "\n";
        printVectorOnce(vp.data(), "Initial vector (saved to binary)");

        std::cout << "Negative count: " << vp.countNegative() << '\n'
              << "Count outside [a,b]: " << vp.countOutsideInterval(a, b) << '\n'
              << "Sum before first minimal element: " << std::fixed << std::setprecision(6) << vp.sumBeforeFirstMin() << '\n'
              << "Sum between first minimal and first maximal: " << std::fixed << std::setprecision(6) << vp.sumBetweenFirstMinAndFirstMax() << '\n';

        auto negatives = vp.selectNegatives();
        printVectorOnce(negatives, "Negative elements (selected into another vector)");

        auto outside = vp.selectOutsideInterval(a, b);
        printVectorOnce(outside, "Elements outside [a,b] (selected into another vector)");

        // sorts and partitions - operate on the same processor object sequentially
        vp.sortDescending();
        printVectorOnce(vp.data(), "After sort by descending");

        // restore initial order from saved binary to demonstrate next operation from original data
        vp = VectorProcessor(VectorProcessor::loadFromBinary(binFile));

        vp.sortByAbsAscending();
        printVectorOnce(vp.data(), "After sort by ascending absolute values");

        // restore again and do partition
        vp = VectorProcessor(VectorProcessor::loadFromBinary(binFile));
        vp.moveOutsideIntervalToEnd(a, b);
        printVectorOnce(vp.data(), "After moving elements outside [a,b] to the end (inside-range kept at front)");

        // finally restore original vector from binary and show
        auto restored = VectorProcessor::loadFromBinary(binFile);
        printVectorOnce(restored, "Restored vector from binary (original)");

        return 0;
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 2;
    }
}
