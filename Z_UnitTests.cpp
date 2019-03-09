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

TEST_CASE ("aa in aaaaa") {
	std::string p = "aa";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 1, 0, 2, 2, 2, 2, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}


TEST_CASE ("aaa in aaaaa") {
	std::string p = "aaa";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 2, 1, 0, 3, 3, 3, 2, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("aaaa in aaaaa") {
	std::string p = "aaaa";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 3, 2, 1, 0, 4, 4, 3, 2, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}


TEST_CASE ("aaaaa in aaaaa") {
	std::string p = "aaaaa";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1};

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

TEST_CASE ("ab in abababa") {
	std::string p = "ab";
	std::string t = "abababa";
	std::vector <size_t> answer = {0, 0, 0, 2, 0, 2, 0, 2, 0, 1};

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

TEST_CASE ("ab in babababa") {
	std::string p = "ab";
	std::string t = "babababa";
	std::vector <size_t> answer = {0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("abc in abcabcabc") {
	std::string p = "abc";
	std::string t = "abcabcabc";
	std::vector <size_t> answer = {0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("abc in abcabcabca") {
	std::string p = "abc";
	std::string t = "abcabcabca";
	std::vector <size_t> answer = {0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 1};

	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchZArray () == answer);
}

TEST_CASE ("abc in abcabcabcab") {
	std::string p = "abc";
	std::string t = "abcabcabcab";
	std::vector <size_t> answer = {0, 0, 0, 0, 3, 0, 0, 3, 0, 0, 3, 0, 0, 2, 0};

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