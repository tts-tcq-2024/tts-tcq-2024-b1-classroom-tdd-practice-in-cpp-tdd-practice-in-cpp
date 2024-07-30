#include "StringCalculator.h"

int StringCalculator::add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }
    
    std::string delimiters = ",\n";
    std::string numbersWithoutDelimiters = numbers;

    if (isCustomDelimiter(numbers)) {
        parseCustomDelimiter(numbers, delimiters, numbersWithoutDelimiters);
    }

    std::vector<int> nums = split(numbersWithoutDelimiters, delimiters);
    return calculateSum(nums);
}

bool StringCalculator::isCustomDelimiter(const std::string& numbers) {
    return numbers.substr(0, 2) == "//";
}

void StringCalculator::parseCustomDelimiter(const std::string& numbers, std::string& delimiters, std::string& numbersWithoutDelimiters) {
    size_t delimiterEnd = numbers.find('\n');
    if (numbers[2] == '[' && numbers[delimiterEnd - 1] == ']') {
        delimiters += numbers.substr(3, delimiterEnd - 4);
    } else {
        delimiters += numbers.substr(2, delimiterEnd - 2);
    }
    numbersWithoutDelimiters = numbers.substr(delimiterEnd + 1);
}

std::vector<int> StringCalculator::split(const std::string& str, const std::string& delimiters) {
    std::vector<int> result;
    std::regex delimiterRegex("[" + delimiters + "]+");
    std::sregex_token_iterator iter(str.begin(), str.end(), delimiterRegex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        if (!iter->str().empty()) {
            result.push_back(std::stoi(iter->str()));
        }
        ++iter;
    }
    return result;
}

int StringCalculator::calculateSum(const std::vector<int>& nums) {
    int sum = 0;
    std::vector<int> negativeNumbers;

    for (int num : nums) {
        if (num < 0) {
            negativeNumbers.push_back(num);
        }
        if (num <= 1000) {
            sum += num;
        }
    }

    if (!negativeNumbers.empty()) {
        throwNegativeNumbersException(negativeNumbers);
    }

    return sum;
}

void StringCalculator::throwNegativeNumbersException(const std::vector<int>& negativeNumbers) {
    std::ostringstream oss;
    oss << "Negatives not allowed: ";
    for (size_t i = 0; i < negativeNumbers.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << negativeNumbers[i];
    }
    throw std::runtime_error(oss.str());
}
