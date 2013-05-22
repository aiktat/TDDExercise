#include "CppUTest/TestHarness.h"
#include "stringCalculator.h"
#include <vector>
#include <string>

TEST_GROUP(StringCalculator)
{
  stringCalculator calculator;
};

TEST(StringCalculator, TestAdditionOf2Numbers)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"2");
  inputString.push_back(L"+");
  inputString.push_back(L"3");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(5,numericResult,0);
}

TEST(StringCalculator, TestAdditionOf3Numbers)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"2");
  inputString.push_back(L"+");
  inputString.push_back(L"3");
  inputString.push_back(L"+");
  inputString.push_back(L"4");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(9,numericResult,0);
}

TEST(StringCalculator, TestMulitplicationOf2Numbers)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"2");
  inputString.push_back(L"*");
  inputString.push_back(L"3");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(6,numericResult,0);
}

TEST(StringCalculator, TestMulitplicationFollowedByAddition)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"2");
  inputString.push_back(L"*");
  inputString.push_back(L"3");
  inputString.push_back(L"+");
  inputString.push_back(L"4");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(10,numericResult,0);
}

TEST(StringCalculator, TestMulitplicationShouldHandledFirstFollowedByAddition)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"2");
  inputString.push_back(L"+");
  inputString.push_back(L"3");
  inputString.push_back(L"*");
  inputString.push_back(L"4");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(14,numericResult,0);
}
TEST(StringCalculator, TestDivisionOf2Numbers)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"3");
  inputString.push_back(L"/");
  inputString.push_back(L"2");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(1.5, numericResult,0);
}

TEST(StringCalculator, TestMultiplicationIsCalculatedFirstThenDivisionThenAddition)
{
  std::list<std::wstring> inputString;
  wstring::size_type stringTypeSize;
  inputString.push_back(L"3");
  inputString.push_back(L"/");
  inputString.push_back(L"2");
  inputString.push_back(L"+");
  inputString.push_back(L"3");
  inputString.push_back(L"*");
  inputString.push_back(L"11");
  wstring result = calculator.calculate(inputString);
  long double numericResult = stod(result,  &stringTypeSize);
  DOUBLES_EQUAL(34.5, numericResult,0);
}