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
	friend BigInt operator/(const BigInt& a, const BigInt& b);
	friend BigInt operator%(const BigInt& a, const BigInt& b);
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
std::vector<int64_t> divide(const std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);
std::vector<int64_t> remainder(const std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);
int compare(const std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);
bool addMinus(const bool& isNegA,const bool& isNegB, const int& x);
bool subtractMinus(const bool& isNegA,const bool& isNegB, const int& x);
std::vector<std::vector<int64_t>> getNewVectors(std::vector<int64_t>& vc1, const std::vector<int64_t>& vc2);

inline std::ostream& operator<<(std::ostream& out, const BigInt& r)
{
	return out << r.getString();
}

std::istream& operator>>(std::istream& in, BigInt& r);

