#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
class BigInt
{
	bool mIsNegative;
	std::vector<int64_t> mDigits;
	std::string s;

public:
	BigInt()
		:mIsNegative(false)
	{
		mDigits.push_back(0);
	}
	
	std::string getString() const
	{
		return s;
	}
	
	BigInt(std::string mS);
	BigInt(std::vector<int64_t> vc, bool isNegative);
	
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);
	friend bool operator>(const BigInt& a, const BigInt& b);
	friend bool operator<(const BigInt& a, const BigInt& b);
	friend bool operator>=(const BigInt& a, const BigInt& b);
	friend bool operator<=(const BigInt& a, const BigInt& b);
	std::string toString() const;
	std::vector<int64_t> toVector() const;
	bool isNegative();
	
	
};

std::vector<int64_t> add(const std::vector<int64_t>& vc, const std::vector<int64_t>& vc2);
std::vector<int64_t> subtract(const std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);
std::vector<int64_t> multiply(const std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);
int compare(const std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);
bool addMinus(const bool& isNegA,const bool& isNegB, const int& x);
bool subtractMinus(const bool& isNegA,const bool& isNegB, const int& x);

inline std::ostream& operator<<(std::ostream& out, const BigInt& r)
{
	return out << r.getString();
}

std::istream& operator>>(std::istream& in, BigInt& r);

/*inline Rational operator*(const Rational& r1, const Rational& r2)
{
    return Rational(r1.num() * r2.num(), r1.den() * r2.den());
}

inline Rational operator/(const Rational& r1, const Rational& r2)
{
    if (r2.num() == 0)
    {
        throw std::runtime_error("Rational: division by zero");
    }

    return Rational(r1.num() * r2.den(), r1.den() * r2.num());
}

inline Rational operator-(const Rational& r)
{
    return Rational(-r.num(), r.den());
}

inline Rational operator+(const Rational& r)
{
    return r;
}*/

/*inline bool operator!=(const Rational& r1, const Rational& r2)
{
    return !(r1 == r2);
}

inline bool operator<(const Rational& r1, const Rational& r2)
{
    return r1.num() * r2.den() < r1.den() * r2.num();
}

inline bool operator>(const Rational& r1, const Rational& r2)
{
    return r2 < r1;
}

inline bool operator<=(const Rational& r1, const Rational& r2)
{
    return !(r2 < r1);
}

inline bool operator>=(const Rational& r1, const Rational& r2)
{
    return !(r1 < r2);
}*/
