#include "VectorTask1.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iterator>
#include <numeric>
#include <stdexcept>

VectorProcessor::VectorProcessor(std::vector<float> data)
    : m_data(std::move(data))
{
}

void VectorProcessor::saveToBinary(const std::string &filePath) const
{
    std::ofstream out(filePath, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot open file for writing: " + filePath);
    std::size_t size = m_data.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (size)
        out.write(reinterpret_cast<const char*>(m_data.data()), size * sizeof(float));
}

std::vector<float> VectorProcessor::loadFromBinary(const std::string &filePath)
{
    std::ifstream in(filePath, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot open file for reading: " + filePath);
    std::size_t size = 0;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<float> v;
    if (size) {
        v.resize(size);
        in.read(reinterpret_cast<char*>(v.data()), size * sizeof(float));
    }
    return v;
}

std::size_t VectorProcessor::countNegative() const
{
    return static_cast<std::size_t>(std::count_if(m_data.begin(), m_data.end(), [](float x){ return x < 0.0f; }));
}

std::size_t VectorProcessor::countOutsideInterval(float a, float b) const
{
    if (a > b) throw std::invalid_argument("Invalid interval: a > b");
    return static_cast<std::size_t>(std::count_if(m_data.begin(), m_data.end(), [a,b](float x){ return x < a || x > b; }));
}

float VectorProcessor::sumBeforeFirstMin() const
{
    if (m_data.empty()) return 0.0f;
    auto itMin = std::min_element(m_data.begin(), m_data.end());
    return std::accumulate(m_data.begin(), itMin, 0.0f);
}

float VectorProcessor::sumBetweenFirstMinAndFirstMax() const
{
    if (m_data.empty()) return 0.0f;
    auto itMin = std::min_element(m_data.begin(), m_data.end());
    auto itMax = std::max_element(m_data.begin(), m_data.end());
    if (itMin == itMax) return 0.0f;
    if (itMin < itMax) return std::accumulate(itMin + 1, itMax, 0.0f);
    return std::accumulate(itMax + 1, itMin, 0.0f);
}

std::vector<float> VectorProcessor::selectNegatives() const
{
    std::vector<float> result;
    std::copy_if(m_data.begin(), m_data.end(), std::back_inserter(result), [](float x){ return x < 0.0f; });
    return result;
}

std::vector<float> VectorProcessor::selectOutsideInterval(float a, float b) const
{
    if (a > b) throw std::invalid_argument("Invalid interval: a > b");
    std::vector<float> result;
    std::copy_if(m_data.begin(), m_data.end(), std::back_inserter(result), [a,b](float x){ return x < a || x > b; });
    return result;
}

void VectorProcessor::sortDescending()
{
    std::sort(m_data.begin(), m_data.end(), std::greater<float>());
}

void VectorProcessor::sortByAbsAscending()
{
    std::sort(m_data.begin(), m_data.end(), [](float lhs, float rhs){ return std::fabs(lhs) < std::fabs(rhs); });
}

void VectorProcessor::moveOutsideIntervalToEnd(float a, float b)
{
    if (a > b) throw std::invalid_argument("Invalid interval: a > b");
    std::stable_partition(m_data.begin(), m_data.end(), [a,b](float x){ return x >= a && x <= b; });
}

const std::vector<float>& VectorProcessor::data() const noexcept
{
    return m_data;
}
