#include <iostream>
#include <sstream>
#include <string>
#include "BigInt.h"

using namespace std;

bool parseExpr(const string& line, BigInt& a, string& op, BigInt& b);
void computeAndShow(const BigInt& a, string op, const BigInt& b);
void showResult(const BigInt& r);

int main()
{
	cout << boolalpha;
	
	string line;
	while(getline(cin, line))
	{
		try 
		{
			BigInt a;
			BigInt b;
			string op;
			if (!parseExpr(line, a, op, b))
            {
                cout << "Incorrect expression: " << line << endl;
            }
            else
            {
                computeAndShow(a, op, b);
            }
		}
		catch (runtime_error& e)
		{
			cout << e.what() << endl;
		}
		
	}
}

bool parseExpr(const string& line, BigInt& a, string& op, BigInt& b)
{
    const string operations = "+-*:<>=#/";
	
	const vector<string> ops = {"+", "-","/", "*", ">" , "<", 
	"+=", "-+", "*=", "/=",  "%", "!=", "=="};
	bool t = false;
	
	for(int i = 0; i < ops.size(); ++i)
	{
		if(ops[i] == op)
		{
			t = true;
			break;
		}
	}
    istringstream sinp(line);
    if (!(sinp >> a))
    {
        return false;
    }
	
	
    if (!(sinp >> op) || t)
    {
        return false;
    }
	
	if(sinp.eof() && (op == "++" || op == "--"))
	{
		b = BigInt("1");
		return true;
	}
	
    char c,l;
	sinp >> l;
	if(l == '0')
	{
		throw runtime_error("Error! division by zero!");
	} else 
	{
		sinp.unget();
	}
	
    if (!(sinp >> b) || sinp >> c)
    {
        return false;
    }
	
    return true;
}

void computeAndShow(const BigInt& a, string op, const BigInt& b)
{
	if(op == "+" || op == "+=")
	{
		showResult(a + b);
	} else if(op == "-" || op == "-=")
	{
		showResult(a - b);
	} else if(op == "*" || op == "*=")
	{
		showResult(a * b);
	} else if(op == "/" || op == "/=")
	{
		showResult(a / b);
	} else if(op == ">")
	{
		cout << (a > b) << endl;
	} else if(op == "<")
	{
		cout << (a < b) << endl;
	} else if(op == ">=")
	{
		cout << (a >= b) << endl;
	} else if(op == "<=")
	{
		cout << (a <= b) << endl;
	} else if(op == "%")
	{
		showResult(a % b);
	}else if( op == "++")
	{
		showResult(a + b);
	} else if( op == "--")
	{
		showResult(a - b);
	} else if( op == "=="){
		cout << (a == b) << endl;
	}
}

void showResult(const BigInt& r)
{
    cout << "Result: " << r << endl;
}
