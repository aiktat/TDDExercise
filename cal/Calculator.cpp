#include "Calculator.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

using namespace std;

Calculator::Calculator(void)
{
}

Calculator::~Calculator(void)
{
}

double Calculator::eval(string str)
{
	istringstream buffer(str);
	double value;

	buffer >> value;
	return value;
}


string  Calculator::add(string a, string b)
{
	return convert(eval(a) + eval(b));
}

string Calculator::sub(string a, string b)
{
	return convert(eval(a) - eval(b));
}

string Calculator::mul(string a, string b)
{
	return convert(eval(a) * eval(b));
}

string Calculator::div(string a, string b)
{
	assert( eval(b) != 0 );
	return convert(eval(a) / eval(b));
}

void Calculator::add_arg(string str)
{
	input_arg.push_back(str);
}

string Calculator::convert(double val)
{
	ostringstream ss;
	ss << val;
	return ss.str();
}

// takes two operands from operand stack
// takes one one operator from operator stack
// accumulate and return the result
//
// [before]
// operand : a b c d
// operator:  + - *
// 
// [after]
// operand : a b (e)		where e=c*d
// operator:  + -
//
double Calculator::consolidate()
{
	// processing
    double a, b;
	int op;

	if( val_stack.empty() ) return 0;
	b = val_stack.top() ; val_stack.pop();

	if( val_stack.empty() ) return 0;
	a = val_stack.top() ; val_stack.pop();
	
	if( op_stack.empty() ) return 0;	
	op = op_stack.top() ; op_stack.pop();

	// arithmetic
    double result;

	if(op == '+')
		result =  add(a, b) ;
	else if (op == '-')
		result =  sub(a, b) ;
	else if (op == '*')
		result = mul(a, b) ;
	else if (op == '/')
		result = div(a, b) ;

	return result;
}


// algo: 
// 1.  scan from left to right
// 2.  if numeric value is read, push to value_stack, 
// 2.1 if arg is operator, then check....
//     - if operator stack is empty, push to operator stack
//     - if top of stack is high precedence operator (* or /), consolidate then push the result back to value_stack
//     - default is just to push to operator_stack/ operand stack
// 3. continue consolidate stacks (both value and operator stack) till value_stack has one entry
// 4. top of value stack is the result
double Calculator::compute()
{
    vector<string>::iterator  i;

    for(i=input_arg.begin(); i != input_arg.end(); ++i){
		string str = *i;

		if( is_operator( str ) ){
			if( op_stack.empty() ){
				op_stack.push( str.c_str()[0] );

            }else if( is_higher_or_equal_precedence( op_stack.top(), str.c_str()[0]) ) {
                val_stack.push( consolidate() );
				op_stack.push( str.c_str()[0] );

			}else{
				op_stack.push( str.c_str()[0] );
			}
		}else{
            val_stack.push ( eval(str) );
		}
        cout << *i ;
	}
	// remaining operator should only be '+' or '-' now
	while( val_stack.size() >= 2){
		double val = consolidate();
        val_stack.push(val);
    }

	double final = eval(val_stack.top()); 
	val_stack.pop();
	
	cout << "= " << final << endl;
	return final;
}

bool Calculator::is_operator(string str)
{
	if( str.size() > 1) return false;

	if( str == "+" ) return true;
	if( str == "-" ) return true;
	if( str == "*" ) return true;
	if( str == "/" ) return true;

	return false;
}

bool Calculator::is_muldiv(int op)
{
	if( op == '*' ) return true;
	if( op == '/' ) return true;

	return false;
}

bool Calculator::is_higher_or_equal_precedence(int op1, int op2)
{
    if( is_muldiv(op1) && !is_muldiv(op2) ) {
        return true;
    }
    else if( is_muldiv(op1) && is_muldiv(op2)){
        return true;
    }
    else{
        return false;
    }
}

// basic logic:
// - split arguments into two types: numbers OR operator
// - [numbers][operator][numbers][operator]...
bool Calculator::parse(string str)
{
	input_arg.clear();

	unsigned start, end;

	start = end = 0;
	while( end  < str.length() ) 
	{
        string s;
        s =extract_number(start, str, end);
        input_arg.push_back( s );
		
		if(end >= str.length() ) break;

        s= extract_operator(start, str, end);
        input_arg.push_back( s );

		start++;
	}
	
	return true;
}

string Calculator::trim(string& s)
{
    //remove trailing and leading whitespace
	stringstream mt;

	mt << s;
	mt >> s;

    // todo: remove spaces in between

	return s;
}


// ugly getter is here.. can someone help to eliminate such need?
vector<string> Calculator::get_args()
{
	return input_arg;
}

double Calculator::add(double a, double b)
{
	return a+b;
}


double Calculator::sub(double a, double b)
{
	return a-b;
}

double Calculator::mul(double a, double b)
{
	return a*b;
}

double Calculator::div(double a, double b)
{
	return a/b;
}

string Calculator::extract_number( unsigned &start, string &str, unsigned &end )
{
    start = str.find_first_of("0123456789", start);
    end   = str.find_first_of("+-*/", start+1);

    return trim( str.substr(start, end-start) );
}


string Calculator::extract_operator( unsigned &start, string &str, unsigned &end )
{
    start = str.find_first_of("+-*/", start+1);
    end   = str.find_first_of("0123456789", start);

    return trim( str.substr(start, end-start) );
}

