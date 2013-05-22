#include "CppUTest/TestHarness.h"
#include "Calculator.h"

TEST_GROUP(Calculator)
{
  Calculator c;
};

TEST(Calculator, TestCaluculatorGetResultReturnResultInInteger)
{
  CHECK_TRUE( c.calculate("0")==0 );
}

TEST(Calculator, TestIfThereIsNoOperatorNumberIsReturned)
{
  LONGS_EQUAL( 1234, c.calculate("1234") );
}

TEST(Calculator, TestAdditionWithTwoOperands)
{
  LONGS_EQUAL( 2, c.calculate("1+1") );
}

TEST(Calculator, TestAdditionWithTwoOperandsWithSpaces)
{
  LONGS_EQUAL( 2, c.calculate(" 1 + 1 ") );
}

TEST(Calculator, ParserShouldReturn3WhenThereAre3tokens)
{
  LONGS_EQUAL( 3, c.parse(" 12 + 2 ")); 
}

TEST(Calculator, ParserShouldReturn5WhenThereAre5tokens)
{
  LONGS_EQUAL( 5, c.parse("  2 + 2 +1 "));
}

TEST(Calculator, ParserShouldHandlePlusMinusMultiplyDivide)
{
  LONGS_EQUAL( 9, c.parse("  2 * 2 / 1 + 30 - 888"));
}

TEST(Calculator, ParserShouldHandleNegativeNumber)
{
  LONGS_EQUAL( 3, c.parse("  -2 *   1 "));
}

IGNORE_TEST(Calculator, ParserShouldReturnInvalidIfStringHasSpaceBetween2Numbers)
{
  LONGS_EQUAL( -1, c.parse("12 3 + 1 "));
}

TEST(Calculator, ParserShouldStripWhiteSpacesIncludingTabAndNewLine)
{
  STRCMP_EQUAL( "2*4/5-1", c.stripWhiteSpaces("  2 *   4 \n / 5 \t  -  1 ").c_str());
}

TEST(Calculator, TestCalculatorReturnCorrectNumberToken)
{
  
  LONGS_EQUAL(5, c.returnNumberOfTokens(c.stripWhiteSpaces("1+2+3")));

}

TEST(Calculator, TestCalculatorReturnCorrectNumberToken2)
{

  LONGS_EQUAL(7, c.returnNumberOfTokens(c.stripWhiteSpaces(" 1+ 332*13/3")));
}

/*
TEST(Calculator, TestCalculatorHanldeSubtration)
{
	LONGS_EQUAL(4, "5-1");
}
*/