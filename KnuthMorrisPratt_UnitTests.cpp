/*
 * KnuthMorrisPratt_UnitTests.cpp
 * Correctness tests for the sp_array in KnuthMorrisPratt.cpp
 * Alexander Gonsalves
 * 27/Feb/2019
 */

#include "catch_main.cpp"
#include "KnuthMorrisPratt.h"
#include <iostream>
#include <string>

TEST_CASE("abababca in babababca") {
	std::string p = "abababca";
	std::string t = "babababca";
	std::vector <size_t> sp_answer = {0, 0, 1, 2, 3, 4, 0, 1, 1};
	std::vector <size_t> answer = {1};

	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchSPArray () == sp_answer);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE("ab in ababab") {
	std::string p = "ab";
	std::string t = "ababab";
	std::vector <size_t> sp_answer = {0, 0, 0};
	std::vector <size_t> answer = {0, 2, 4};

	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchSPArray () == sp_answer);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE("aaa in aaaaa") {
	std::string p = "aaa";
	std::string t = "aaaaa";
	std::vector <size_t> sp_answer = {0, 1, 2, 2};
	std::vector <size_t> answer = {0, 1, 2};

	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchSPArray () == sp_answer);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE("b in aaaaa") {
	std::string p = "b";
	std::string t = "aaaaa";
	std::vector <size_t> sp_answer = {0, 0};
	std::vector <size_t> answer = {};

	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchSPArray () == sp_answer);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}