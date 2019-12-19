#include <iostream>
#include <sstream>
#include <string>
#include "BigInt.h"

using namespace std;

bool parseExpr(const string& line, BigInt& a, char& op, BigInt& b);
void computeAndShow(const BigInt& a, char op, const BigInt& b);
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
			char op;
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

bool parseExpr(const string& line, BigInt& a, char& op, BigInt& b)
{
    const string operations = "+-*:<>=#";

    istringstream sinp(line);
    if (!(sinp >> a))
    {
        return false;
    }
    if (!(sinp >> op) || operations.find(op) == string::npos)
    {
        return false;
    }

    char c;
    if (!(sinp >> b) || sinp >> c)
    {
        return false;
    }

    return true;
}

void computeAndShow(const BigInt& a, char op, const BigInt& b)
{
    switch (op)
    {
    case '+':
        showResult(a + b);
        break;
	case '-':
		showResult(a - b);
		break;
	case '*':
		showResult(a * b);
		break;
	case '=':
		cout << (a == b) << endl;
		break;
	case '>':
		cout << (a > b) << endl;
		break;
	case '<':
		cout << (a < b) << endl;
		break;
    }
}

void showResult(const BigInt& r)
{
    cout << "Result: " << r << endl;
}
