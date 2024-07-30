#include <gtest/gtest.h>
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    std::string input = "";
    StringCalculator objUnderTest;
    int result = objUnderTest.add(input);

    ASSERT_EQ(result, 0);
}

TEST(StringCalculatorAddTests, ExpectValueForSingleNumber) {
    std::string input = "1";
    StringCalculator objUnderTest;
    int result = objUnderTest.add(input);

    ASSERT_EQ(result, 1);
}

TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    std::string input = "1,2";
    StringCalculator objUnderTest;
    int result = objUnderTest.add(input);

    ASSERT_EQ(result, 3);
}

TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    std::string input = "1\n2,3";
    StringCalculator objUnderTest;
    int result = objUnderTest.add(input);

    ASSERT_EQ(result, 6);
}

TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    std::string input = "2,1001";
    StringCalculator objUnderTest;
    int result = objUnderTest.add(input);

    ASSERT_EQ(result, 2);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    std::string input = "//;\n1;2";
    StringCalculator objUnderTest;
    int result = objUnderTest.add(input);

    ASSERT_EQ(result, 3);
}

TEST(StringCalculatorAddTests, ExpectExceptionForNegativeNumbers) {
    ASSERT_THROW({
        std::string input = "-1,2";
        StringCalculator objUnderTest;
        objUnderTest.add(input);
    }, std::runtime_error);
}

TEST(StringCalculatorAddTests, ExpectExceptionForMultipleNegativeNumbers) {
    ASSERT_THROW({
        std::string input = "-1,-2,3";
        StringCalculator objUnderTest;
        objUnderTest.add(input);
    }, std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
