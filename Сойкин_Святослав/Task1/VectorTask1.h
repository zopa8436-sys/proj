#pragma once

#include <vector>
#include <string>

class VectorProcessor {
public:
    explicit VectorProcessor(std::vector<float> data);

    void saveToBinary(const std::string &filePath) const;
    static std::vector<float> loadFromBinary(const std::string &filePath);

    std::size_t countNegative() const;
    std::size_t countOutsideInterval(float a, float b) const;
    float sumBeforeFirstMin() const;
    float sumBetweenFirstMinAndFirstMax() const;

    std::vector<float> selectNegatives() const;
    std::vector<float> selectOutsideInterval(float a, float b) const;

    void sortDescending();
    void sortByAbsAscending();
    void moveOutsideIntervalToEnd(float a, float b);

    const std::vector<float>& data() const noexcept;

private:
    std::vector<float> m_data;
};
