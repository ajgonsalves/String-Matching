/*
 * Z_UnitTests.cpp
 * Tests that Z.cpp correctly computes z_array and therefore exact match locations.
 * Alexander Gonsalves
 * 12/Feb/2019
 */

#include "catch_main.cpp"
#include "Z.h"
#include <iostream>
#include <string>

TEST_CASE ("a in a") {
	std::string p = "a";
	std::string t = "a";
	std::vector <size_t> answer = {0, 0, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("a in aaaaa") {
	std::string p = "a";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 0, 1, 1, 1, 1, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("b in aaaaa") {
	std::string p = "b";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 0, 0, 0, 0, 0, 0};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("ab in ababab") {
	std::string p = "ab";
	std::string t = "ababab";
	std::vector <size_t> answer = {0, 0, 0, 2, 0, 2, 0, 2, 0};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("ab in bababab") {
	std::string p = "ab";
	std::string t = "bababab";
	std::vector <size_t> answer = {0, 0, 0, 0, 2, 0, 2, 0, 2, 0};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("ababcx in ababcxababcyababcx") {
	std::string p = "ababcx";
	std::string t = "ababcxababcyababcx";
	std::vector <size_t> answer = {0, 0, 2, 0, 0, 0, 0, 6, 0, 2, 0, 0, 0, 5, 0, 2, 0, 0, 0, 6, 0, 2, 0 ,0 ,0};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}