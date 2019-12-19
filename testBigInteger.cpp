#define CATCH_CONFIG_MAIN
#ifndef _TM_DEFINED 
#define _TM_DEFINED
#include "../catch.hpp"
#include "BigInt.h"


TEST_CASE("contructors")
{
	SECTION("test 1")
	{
		BigInt x;
		REQUIRE(x.toString() == "0");
	}
	SECTION("test 2")
	{
		BigInt x("-1000");
		std::vector<int64_t> v = x.toVector();
		std::string r = "";
		for(int i = 0; i < v.size(); ++i)
			r += std::to_string(v[i]);
		REQUIRE(r == "1000");
	}
}

TEST_CASE("Arithmetic operations +")
{
	REQUIRE(BigInt("2") == BigInt("2"));
	REQUIRE((BigInt("3") + BigInt("2")) == BigInt("5"));
	REQUIRE((BigInt("5") + BigInt("5")) == BigInt("10"));
	REQUIRE((BigInt("100000000000000000000") + BigInt("100000000000000000000"))
	== BigInt("200000000000000000000"));
	REQUIRE((BigInt("-3") + BigInt("2")) == BigInt("-1"));
	REQUIRE((BigInt("-3") + BigInt("-2")) == BigInt("-5"));
	REQUIRE((BigInt("3") + BigInt("-2")) == BigInt("1"));
	REQUIRE((BigInt("99999999999999999999999999999") + BigInt("1"))
	== BigInt("100000000000000000000000000000"));
	
}
#endif