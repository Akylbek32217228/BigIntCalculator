#include "BigInt.h"
#include <iostream>
#include <algorithm>

using namespace std;

BigInt::BigInt(string mS)
	:s(mS)
{
	mIsNegative = isNegative();
	mDigits = toVector();
}

BigInt::BigInt(vector<int64_t> vc, bool isNegative)
	:mDigits(vc)
	,mIsNegative(isNegative)
{
	s = toString();
}

std::string BigInt::toString() const
{
	std::string r;
	if(mIsNegative)
	{
		r += '-';
	}
	
	for(auto d : mDigits)
	{
		r += char(d + '0');
	}
	
	return r;
}

istream& operator>>(istream& inp, BigInt& res)
{
    string str;

    if (!(inp >> str))
    {
        return inp;
    }
	res = BigInt(str);
    /*if (inp.eof())
    {
        res = str;
        return inp;
    }*/

    /*if (!inp.get(ch))
    {
        return inp;
    }

    if (!(ch == '+' || ch == '-' || isdigit(ch)))
    {
        inp.setstate(ios_base::failbit);
        return inp;
    }*/

    /*inp.unget();

    if (!(inp >> den))
    {
        return inp;
    }

    r = Rational(num, den);*/

    return inp;
}

vector<int64_t> BigInt::toVector() const
{
	vector<int64_t> v;
	v.reserve(s.size());
	if(mIsNegative)
	{
		for(int i = 1; i < s.size(); ++i)
		{
			char ch = s[i];
			v.push_back(ch - '0');
		}
	} else 
	{
		for(auto ch : s)
		{
			v.push_back(ch - '0');
		}		
	}
    return v;
}

bool BigInt::isNegative()
{
	if(s[0] == '-')
		return true;
	else 
		return false;
}

BigInt operator+(const BigInt& t1, const BigInt& t2)
{
	bool isNegA = t1.mIsNegative;
	bool isNegB = t2.mIsNegative;
	vector<int64_t> vc;
	int x = compare(t1.mDigits, t2.mDigits);
	if((!isNegA && !isNegB) || (isNegA && isNegB))
	{
		vc = add(t1.mDigits, t2.mDigits);
	} else if((!isNegA && isNegB) || (isNegA && !isNegB))
	{
		if(x == 1 || x == 3)
		{
			vc = subtract(t1.mDigits, t2.mDigits);
		} else if(x == 2)
		{
			vc = subtract(t2.mDigits, t1.mDigits);
		}
	}
	return BigInt(vc, addMinus(isNegA, isNegB, x));
}

BigInt operator-(const BigInt& a, const BigInt& b)
{
	bool isNegA = a.mIsNegative;
	bool isNegB = b.mIsNegative;
	int x = compare(a.mDigits, b.mDigits);
	vector<int64_t> vc;
	if((!isNegA && !isNegB) || (isNegA && isNegB) )
	{
		if(x == 1 || x == 3)
		{
			vc = subtract(a.mDigits, b.mDigits);
		}
		else if(x == 2)
		{
			vc = subtract(b.mDigits,a.mDigits);
		}
	} else if((isNegA && !isNegB && (x == 1 || x == 3)) 
		|| (isNegA && !isNegB && x == 2) 
		|| (!isNegA && isNegB && (x == 1 || x == 3))
		|| (!isNegA && isNegB && x == 2))
	{
		vc = add(a.mDigits,b.mDigits);
	}
	return BigInt(vc, subtractMinus(isNegA, isNegB,x));
}

BigInt operator*(const BigInt& a, const BigInt& b)
{
	bool isNegA = a.mIsNegative;
	bool isNegB = b.mIsNegative;
	if((!isNegA && !isNegB) || (isNegA && isNegB))
	{
		return BigInt(multiply(a.mDigits, b.mDigits), false);
	} else if((!isNegA && isNegB) || (isNegA && !isNegB)) 
	{
		return BigInt(multiply(a.mDigits, b.mDigits), true);
	}
	return BigInt("0");
}

BigInt operator/(const BigInt& a, const BigInt& b)
{
	bool isNegA = a.mIsNegative;
	bool isNegB = b.mIsNegative;
	
	if((!isNegA && !isNegB) || (isNegA && isNegB))
	{
		return BigInt(divide(a.mDigits, b.mDigits), false);
	} else 
	{
		return BigInt(divide(a.mDigits, b.mDigits), true);
	}
	return BigInt("0");
}

BigInt operator%(const BigInt& a, const BigInt& b)
{
	bool isNegA = a.mIsNegative;
	bool isNegB = b.mIsNegative;
	
	if((!isNegA && !isNegB) || (!isNegA && isNegB))
	{
		return BigInt(remainder(a.mDigits, b.mDigits), false);
	} else if((isNegA && isNegB) || (isNegA && !isNegB))
	{
		return BigInt(remainder(a.mDigits, b.mDigits), true);
	}
	return BigInt("0");
}

bool operator==(const BigInt& a, const BigInt& b)
{
	int x = compare(a.mDigits, b.mDigits);
	bool c;
	if(a.mIsNegative == b.mIsNegative)
	{
		c = true;
	} else 
	{
		c = false;
	}
	return (x == 3 && c == true ? true : false);
}

bool operator>(const BigInt& a, const BigInt& b)
{
	int x = compare(a.mDigits, b.mDigits);
	bool c = !a.mIsNegative;
	bool d = !b.mIsNegative;
	if(x == 1)
	{
		if(c && d)
			return true;
		else if(!c && !d)
			return false;
		else if(!c && d)
			return false;
		else 
			return true;
	} else if(x == 2 || x == 3)
	{
		if(c && d)
			return false;
		else if(!c && !d)
			return true;
		else if(!c && d)
			return false;
		else 
			return true;
	}
	return false;
}

bool operator<(const BigInt& a, const BigInt& b)
{
	int x = compare(b.mDigits, a.mDigits);
	bool c = !b.mIsNegative;
	bool d = !a.mIsNegative;
	if(x == 1)
	{
		if(c && d)
			return true;
		else if(!c && !d)
			return false;
		else if(!c && d)
			return false;
		else 
			return true;
	} else if(x == 2 || x == 3)
	{
		if(c && d)
			return false;
		else if(!c && !d)
			return true;
		else if(!c && d)
			return false;
		else 
			return true;
	}
	return false;
}

bool operator<=(const BigInt& a, const BigInt& b)
{
	int x = compare(b.mDigits, a.mDigits);
	bool c = !b.mIsNegative;
	bool d = !a.mIsNegative;
	if(x == 1 || x == 3)
	{
		if(c && d)
			return true;
		else if(!c && !d)
			return false;
		else if(!c && d)
			return false;
		else 
			return true;
	} else if(x == 2)
	{
		if(c && d)
			return false;
		else if(!c && !d)
			return true;
		else if(!c && d)
			return false;
		else 
			return true;
	}
	return false;
}

bool operator>=(const BigInt& a, const BigInt& b)
{
	int x = compare(a.mDigits, b.mDigits);
	bool c = !a.mIsNegative;
	bool d = !b.mIsNegative;
	if(x == 1 || x == 3)
	{
		if(c && d)
			return true;
		else if(!c && !d)
			return false;
		else if(!c && d)
			return false;
		else 
			return true;
	} else if(x == 2)
	{
		if(c && d)
			return false;
		else if(!c && !d)
			return true;
		else if(!c && d)
			return false;
		else 
			return true;
	}
	return false;
}

int compare(const vector<int64_t>& vc1, const vector<int64_t>& vc2)
{
	int x = 2;
	if(vc1.size() > vc2.size())
	{
		x = 1;
	} else if(vc1.size() < vc2.size())
	{
		x = 2;
	} else 
	{
		for(int i = 0; i < vc1.size(); ++i)
		{
			if ((vc1[i] - '0') < (vc2[i] - '0'))
			{ 
				x = 2;
				break; 
			} else if ((vc1[i] - '0') > (vc2[i] - '0'))
			{
				x = 1;
				break;
			} else 
			{
				x = 3;
			}
		}		
	}
	return x;
}

bool addMinus(const bool& isNegA,const bool& isNegB, const int& x)
{
	if(isNegA && isNegB)
		return true;
	if(!isNegA && !isNegB)
		return false;
	
	if((isNegA && !isNegB && x == 2) || (!isNegA && isNegB && x == 1))
		return false;
	else if((isNegA && !isNegB && x == 1) || (!isNegA && isNegB && x == 2))
		return true;
	return false;
}

bool subtractMinus(const bool& isNegA,const bool& isNegB, const int& x)
{
	
	if(!isNegA && !isNegB && x == 1)
		return false;
	else if(!isNegA && !isNegB && x == 2)
		return true;
	
	if(isNegA && isNegB && x == 1)
		return true;
	else if(isNegA && isNegB && x == 2)
		return false;
	
	if((isNegA && !isNegB && x == 1) || (isNegA && !isNegB && x == 2))
		return true;
	else if((!isNegA && isNegB && x == 1) || (!isNegA && isNegB && x == 2))
		return false;
	return false;
}

vector<int64_t> add(const vector<int64_t>& vc, const vector<int64_t>& vc2)
{
    vector<int64_t> newV;
    newV.resize(max(vc.size(), vc2.size()) + 1, 0);
    int j = vc.size() - 1;
    int g = vc2.size() - 1;
    int k = newV.size() - 1;
    int carry = 0;
    while( j != -1 || g != -1)
    {
        int sum = 0;
        if( j != -1)
        {
            sum += vc[j];
            --j;
        }
        if(g != -1)
        {
            sum += vc2[g];
            --g;
        }
        
        sum += carry;
        newV[k] = sum % 10;
        --k;
        carry = sum / 10; 
    }
    
    if(carry == 0)
    {
        newV.erase(newV.begin());
    } else 
    {
        newV[0] = carry;
        
    }
    return newV;
}

vector<int64_t> subtract(const vector<int64_t>& vc1,const vector<int64_t>& vc2) 
{
	vector<int64_t> newV;
    newV.resize(max(vc1.size(), vc2.size()), 0);
    int j = vc1.size() - 1;
    int g = vc2.size() - 1;
    int k = newV.size() - 1;
    int carry = 0;
	int res = 0;
    while( (j != -1) || (g != -1))
    {
		bool b = false;
        if( j != -1)
        {
			
			res = vc1[j];
			if(carry == 1 && res == 0)
				b = true;
			res += 10;
			res -= carry;
			
            --j;
        }
        if(g != -1)
        {
			if(res%10 < vc2[g] || b)
			{
				res -= vc2[g];
				carry = 1;
			} else 
			{
				res -= vc2[g];
				carry = 0;
			}
            --g;
        }
		b = false;
        newV[k] = res%10;
        --k; 
    }
    
	for(int i = 0; i < newV.size(); ++i)
	{
		if(newV[i] == 0)
		{
			newV.erase(newV.begin());
			--i;
		} else 
		{
			break;
		}
	}
	
	if(newV.size() == 0)
		newV.push_back(0);	
	
    return newV;
}

vector<int64_t> multiply(const vector<int64_t>& vc1,const vector<int64_t>& vc2)
{
	vector<int64_t> newV;
    newV.resize(max(vc1.size(), vc2.size()) * 2, 0);
    int j = vc1.size() - 1;
    int k = newV.size() - 1;
    int carry = 0;
	int zeros = -1;
    while( j != -1 )
    {
		int a = vc1[j];
		int g = vc2.size() - 1;
		vector<int64_t> newV2;
		newV2.resize(vc2.size() + 1, 0);
		int k2 = newV2.size() - 1;
		int carry2 = 0;
		while(g != -1)
		{
			int x = a * vc2[g] + carry2;
			newV2[k2] = x % 10;
			--k2;
			carry2 = x / 10;
			--g;
		}
		
		if(carry2 == 0)
		{
			newV2.erase(newV2.begin());
		} else 
		{
			newV2[0] = carry2;
		}
		++zeros;
		for(int i = 0; i < zeros; ++i)
		{
			newV2.push_back(0);
		}
		newV = add(newV, newV2);
		--j;
    }
	for(int i = 0; i < newV.size(); ++i)
	{
		if(newV[i] == 0)
		{
			newV.erase(newV.begin());
			--i;
		} else 
		{
			break;
		}
	}
	
	
    return newV;
}

vector<int64_t> divide(const vector<int64_t>& vc1, const vector<int64_t>& vc2)
{
	vector<int64_t> newV;
	vector<int64_t> dividend = vc1;
	newV.reserve(max(vc1.size(), vc2.size()));
	int x = compare(vc1, vc2);
	
	if(x == 1)
	{
		vector<vector<int64_t>> vectors = getNewVectors(dividend, vc2);
		vector<int64_t> vc3 = vectors.back();
		vectors.pop_back();
		while(vectors.size() != 0) {
			
			vector<int64_t> vc4 = {0};
			int count = 0;
			int g = x;
			int t = x;
			while(g == 1)
			{
				vc4 = add(vc4,vc2);
				++count;
				g = compare(vc3,vc4);				
				if(g == 3)
					g = 1;
 			}
			if(count > 0)
			{
				--count;
				vc4 = subtract(vc4, vc2);				
			}
			if(t == 3)
			{
				++count;
				vc4 = add(vc4,vc2);
			}

			newV.push_back(count);
			
			vector<int64_t> vc5 = subtract(vc3, vc4);
			
			if(compare(vc5, vc2) == 2 && vectors.size() != 0)
			{
				if(vc5.back() == 0)
				{
					if(compare(vectors.back(), vc2) == 2)
					{
						vc3 = vectors.back();
						vectors.pop_back();
					} else 
					{
						vc3 = vectors.back();
						vectors.pop_back();
					}
				} else 
				{
					int c = 0;
					while(compare(vc5, vc2) == 2)
					{
						vc5.insert(vc5.end(), vectors.back().begin(), 
						vectors.back().end());
						vectors.pop_back();	
						++c;
						if(c == 1)
						{
							break;
						}
					}
					vc3 = vc5;
				}
					
			}
			x = compare(vc3, vc2);
		}
		
		vector<int64_t> vc4 = {0};
		int count = 0;
		int g = x;
		int t = x;
		while(g == 1)
		{
			vc4 = add(vc4,vc2);
			++count;
			g = compare(vc3,vc4);
			if(g == 3)
					g = 1;
		}
		if(count > 0)
		{
			--count;
			vc4 = subtract(vc4, vc2);				
		}
		if(t == 3)
		{
			++count;
		}

		newV.push_back(count);
		
	} else if(x == 3)
	{
		return vector<int64_t> {1};
	} else 
	{
		return vector<int64_t> {0};
	}
	
	
	return newV;
}

vector<vector<int64_t>> getNewVectors(vector<int64_t>& vc1, const vector<int64_t>& vc2)
{
	
	vector<int64_t> newVector;
	vector<vector<int64_t>> newVectors;
	int divSize = vc2.size();
	newVector.reserve(divSize + 1);
	newVectors.reserve(vc1.size());
	for(int i = 0; i < divSize; ++i)
	{
		newVector.push_back(vc1[i]);
	}
	
	vc1.erase(vc1.begin(), vc1.begin() + divSize);
	
	int x = compare(newVector, vc2);
	if(x == 2)
	{
		newVector.push_back(vc1[0]);
		vc1.erase(vc1.begin(), vc1.begin() + 1);
		newVectors.push_back(newVector);
	} else 
	{
		newVectors.push_back(newVector);
	}
	
	while(vc1.size() != 0)
	{
		vector<int64_t> vc = {vc1[0]};
		vc1.erase(vc1.begin(), vc1.begin() + 1);
		newVectors.push_back(vc);
	}
	reverse(newVectors.begin(), newVectors.end());
	
	return newVectors;
}

vector<int64_t> remainder(const vector<int64_t>& vc1, const vector<int64_t>& vc2)
{
	vector<int64_t> newV;
	vector<int64_t> dividend = vc1;
	newV.reserve(max(vc1.size(), vc2.size()));
	int x = compare(vc1, vc2);
	
	if(x == 1)
	{
		vector<vector<int64_t>> vectors = getNewVectors(dividend, vc2);
		vector<int64_t> vc3 = vectors.back();
		vectors.pop_back();
		while(vectors.size() != 0) {
			
			vector<int64_t> vc4 = {0};
			int count = 0;
			int g = x;
			int t = x;
			while(g == 1)
			{
				vc4 = add(vc4,vc2);
				++count;
				g = compare(vc3,vc4);				
				if(g == 3)
					g = 1;
 			}
			if(count > 0)
			{
				--count;
				vc4 = subtract(vc4, vc2);				
			}
			if(t == 3)
			{
				++count;
				vc4 = add(vc4,vc2);
			}

			
			vector<int64_t> vc5 = subtract(vc3, vc4);
			
			if(compare(vc5, vc2) == 2 && vectors.size() != 0)
			{
				if(vc5.back() == 0)
				{
					if(compare(vectors.back(), vc2) == 2)
					{
						vc3 = vectors.back();
						vectors.pop_back();
					} else 
					{
						vc3 = vectors.back();
						vectors.pop_back();
					}
				} else 
				{
					int c = 0;
					while(compare(vc5, vc2) == 2)
					{
						vc5.insert(vc5.end(), vectors.back().begin(), 
						vectors.back().end());
						vectors.pop_back();	
						++c;
						if(c == 1)
						{
							break;
						}
					}
					vc3 = vc5;
				}
					
			}
			x = compare(vc3, vc2);
		}
		
		vector<int64_t> vc4 = {0};
		int count = 0;
		int g = x;
		int t = x;
		while(g == 1)
		{
			vc4 = add(vc4,vc2);
			++count;
			g = compare(vc3,vc4);
			if(g == 3)
					g = 1;
		}
		if(count > 0)
		{
			--count;
			vc4 = subtract(vc4, vc2);				
		}
		if(t == 3)
		{
			++count;
		}
		
		vector<int64_t> vc5 = subtract(vc3, vc4);

		newV = vc5;
	} else if(x == 3)
	{
		return vector<int64_t>{0};
	} else if(x == 2)
	{
		newV = vc1;
	}
	
	return newV;
}


