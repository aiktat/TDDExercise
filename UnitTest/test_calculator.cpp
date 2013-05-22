#include "CppUTest/TestHarness.h"
#include "Calculator.h"
#include <vector>  // primitive obsessive?

using namespace std;

TEST_GROUP(Calculator)
{
	Calculator c;


	void setup()
	{
		// Init stuff
		//c.parse("12+34*2/4");
	}

	void teardown()
	{
		// unit stuff
	}
};


TEST(Calculator, TestCalculatorEvalReturnNumericNumberOfInputString)
{
    LONGS_EQUAL( 1, c.eval("1"));
    LONGS_EQUAL( 1, c.eval(" 1"));
    LONGS_EQUAL( 12, c.eval("12 "));
    LONGS_EQUAL( 12, c.eval(" 12 "));
    LONGS_EQUAL( -1, c.eval("-1"));
    LONGS_EQUAL( -1, c.eval("-1 "));
    LONGS_EQUAL( -1, c.eval(" -1"));
    LONGS_EQUAL( -1, c.eval(" -1 "));
}

TEST(Calculator, TestNumericToStringConversion)
{
	CHECK_TRUE( c.convert(6) == "6");
	CHECK_TRUE( c.convert(3.2) == "3.2");
}

TEST(Calculator, TestStringComputation)
{
	CHECK_TRUE( c.add( "4", "2") == "6" );
	CHECK_TRUE( c.sub( "4", "2") == "2");
	CHECK_TRUE( c.mul( "4", "2") == "8");
	CHECK_TRUE( c.div( "4", "2") == "2");
	CHECK_TRUE( c.div( "10.0", "4") == "2.5");
	CHECK_TRUE( c.add( "1.0", "2.5") == "3.5");
}

/*
TEST(Calculator, TestAddArg)
{
	CHECK_TRUE(c.input_arg[0] == "4");
	CHECK_TRUE(c.input_arg[1] == "/");
	CHECK_TRUE(c.input_arg[2] == "2");
}
*/

TEST(Calculator, TestSimpleCalculation)
{
	c.parse("9*8");
	DOUBLES_EQUAL( 9*8, c.compute(), 0);

	c.parse("1");
	DOUBLES_EQUAL( 1, c.compute(), 0);

	c.parse("1+2");
	DOUBLES_EQUAL( 1+2, c.compute(), 0);

    c.parse("1/3");
    DOUBLES_EQUAL( 1/3.0, c.compute(), 0.000001);

 
}

TEST(Calculator, TestParser)
{
	c.parse(" 12 +   34*2/4");
	vector<string> input_arg = c.get_args();
    STRCMP_EQUAL ("12", input_arg[0].c_str());
	STRCMP_EQUAL ("+",  input_arg[1].c_str());
	STRCMP_EQUAL ("34", input_arg[2].c_str());
	STRCMP_EQUAL ("*",  input_arg[3].c_str());
	STRCMP_EQUAL ("2",  input_arg[4].c_str());
	STRCMP_EQUAL ("/",  input_arg[5].c_str());
	STRCMP_EQUAL ("4",  input_arg[6].c_str());
}


TEST(Calculator, TestNumericCalculation)
{
	DOUBLES_EQUAL( 5.0, c.add(3.0, 2), 0);
	DOUBLES_EQUAL( 2.5, c.sub(3.0, 0.5), 0);
	DOUBLES_EQUAL( 4.6, c.mul(2.3, 2), 0);
	DOUBLES_EQUAL( 3.5, c.div(7, 2), 0);
}

TEST(Calculator, TestLeftToRightAndMDAS)
{
    c.parse("3/3*2+1");
    DOUBLES_EQUAL( 3/3*2+1.0, c.compute(), 0);

    c.parse("12*2/3");
    DOUBLES_EQUAL( 12*2/3, c.compute(), 0);

    c.parse("1+12*2/3");
    DOUBLES_EQUAL( 1+12*2/3, c.compute(), 0);
}

TEST(Calculator, TestErrorousScenarioWithExtraOperator)
{
    c.parse("+3+3");
    DOUBLES_EQUAL( 3+3, c.compute(), 0);

    c.parse("+3+3+");
    DOUBLES_EQUAL( 3+3, c.compute(), 0);
}

IGNORE_TEST(Calculator, TestInputArgumentHasSpacesInBetweenDigits)
{
    c.parse("1 2 3 + 3");
    DOUBLES_EQUAL( 123+3, c.compute(), 0);
}


