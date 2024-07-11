#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "StringCalculator.h"

std::string StringCalculator::replaceWithCommas(const std::string& input, const std::string& delimiter) {
    std::string numbersStr = input;
    std::replace_if(numbersStr.begin(), numbersStr.end(), [&](char c) {
        return c == '\n' || delimiter.find(c) != std::string::npos;
    }, ',');
    return numbersStr;
}

std::string StringCalculator::findDelimiter(const std::string& input) {
    std::string delimiter = ",";
    std::string numbersStr = input;

    if (input.substr(0, 2) == "//") {
        size_t delimiterPos = input.find("\n");
        if (delimiterPos != std::string::npos) {
            delimiter = input.substr(2, delimiterPos - 2);
            numbersStr = input.substr(delimiterPos + 1);
        }
    }
    return replaceWithCommas(numbersStr, delimiter);
}

void StringCalculator::findNegatives(const std::string& updatedInput) {
    std::stringstream strstream(updatedInput);
    std::string segment;

    while (std::getline(strstream, segment, ',')) {
        if (std::stoi(segment) < 0) {
            throw std::runtime_error("negatives not allowed");
        }
    }
}

int StringCalculator::findSum(const std::string& updatedInput) {
    std::stringstream strstream(updatedInput);
    std::string segment;
    int sum = 0;

    while (std::getline(strstream, segment, ',')) {
        int number = std::stoi(segment);
        if (number <= 1000) {
            sum += number;
        }
    }
    return sum;
}

int StringCalculator::add(const std::string& input) {
    if (input.empty()) {
        return 0;
    }
    std::string updatedInput = findDelimiter(input);
    findNegatives(updatedInput);
    return findSum(updatedInput);
}

int main() {
    StringCalculator calculator;

    try {
        std::cout << calculator.add("1,2,5") << std::endl; // Outputs: 8
        std::cout << calculator.add("//;\n1;2") << std::endl; // Outputs: 3
        std::cout << calculator.add("1\n2,3") << std::endl; // Outputs: 6
        std::cout << calculator.add("1001,2") << std::endl; // Outputs: 2
        std::cout << calculator.add("1,-2,3") << std::endl; // Throws exception: negatives not allowed
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
