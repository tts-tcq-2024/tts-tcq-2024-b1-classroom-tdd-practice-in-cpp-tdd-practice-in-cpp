#include "StringCalculator.hpp"
#include <sstream>
#include <algorithm>
#include <stdexcept>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = ",";
    std::string numbersPart = numbers;

    if (numbers.substr(0, 2) == "//") {
        size_t pos = numbers.find('\n');
        delimiter = numbers.substr(2, pos - 2);
        numbersPart = numbers.substr(pos + 1);
    }

    std::replace(numbersPart.begin(), numbersPart.end(), '\n', ',');
    std::vector<int> nums = splitNumbers(numbersPart, delimiter);
    std::vector<int> negatives;
    int sum = 0;

    for (const auto& num : nums) {
        if (num < 0) {
            negatives.push_back(num);
        } else if (num <= 1000) {
            sum += num;
        }
    }

    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (const auto& num : negatives) {
            oss << num << " ";
        }
        throw std::runtime_error(oss.str());
    }

    return sum;
}

std::vector<int> StringCalculator::splitNumbers(const std::string& numbers, const std::string& delimiter) {
    std::vector<int> nums;
    std::stringstream ss(numbers);
    std::string item;

    while (std::getline(ss, item, ',')) {
        nums.push_back(std::stoi(item));
    }

    return nums;
}

