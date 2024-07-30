#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <regex>

class StringCalculator {
public:
    int add(const std::string& numbers);

private:
    bool isCustomDelimiter(const std::string& numbers);
    void parseCustomDelimiter(const std::string& numbers, std::string& delimiters, std::string& numbersWithoutDelimiters);
    std::vector<int> split(const std::string& str, const std::string& delimiters);
    int calculateSum(const std::vector<int>& nums);
    void throwNegativeNumbersException(const std::vector<int>& negativeNumbers);
};

#endif // STRING_CALCULATOR_H
