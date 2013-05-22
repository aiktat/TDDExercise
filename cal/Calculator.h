#pragma once

#include <string>
#include <stack>
#include <vector>

class Calculator
{
public:
	Calculator(void);
	~Calculator(void);

public:
	bool   parse(std::string str);
    double compute();

public:  // supposedly to be protected and probably no test cases is needed
	double      eval(std::string str);
    double      eval(double d) { return d;}
	std::string convert( double );

    double consolidate();
	
	std::string add( std::string a, std::string b);
	std::string sub( std::string a, std::string b);
	std::string mul( std::string a, std::string b);
	std::string div( std::string a, std::string b);
	
	double      add( double, double);
	double      sub( double, double);
	double      mul( double, double);
	double      div( double, double);

	void                     add_arg(std::string str);
	std::vector<std::string> get_args();

protected:
    bool is_operator(std::string str);
    bool is_muldiv  (int op);

    bool is_higher_or_equal_precedence(int, int);
    std::string extract_number( unsigned &start, std::string &str, unsigned &end );
    std::string extract_operator( unsigned &start, std::string &str, unsigned &end );

    std::string trim(std::string&);


private:
	std::stack<double>      val_stack;
	std::stack<int>	        op_stack;

public:

	std::vector<std::string> input_arg;
};

