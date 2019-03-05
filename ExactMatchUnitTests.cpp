/*
 * ExactMatchUnitTests.cpp
 * Unit tests for the correctness of string matching algorithms.
 * Alexander Gonsalves
 * 11/Feb/2019
 */

#include "catch_main.cpp"
#include <iostream>
#include <string>

#include "BoyerMoore.h"
#include "KnuthMorrisPratt.h"
#include "Naive.h"
#include "Z.h"

TEST_CASE ("a in a") {
	std::string p = "a";
	std::string t = "a";
	std::vector <size_t> answer = {0};

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("a in b") {
	std::string p = "a";
	std::string t = "b";
	std::vector <size_t> answer = {};

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("a in aaaaa") {
	std::string p = "a";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 1, 2, 3, 4};

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("abab in babababab") {
	std::string p = "ab";
	std::string t = "babababab";
	std::vector <size_t> answer = {1, 3, 5, 7};

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("b in aaaaa") {
	std::string p = "b";
	std::string t = "aaaaa";
	std::vector <size_t> answer;

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("empty string in aaaaa") {
	std::string p = "";
	std::string t = "aaaaa";
	std::vector <size_t> answer;

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("a in empty string") {
	std::string p = "a";
	std::string t = "";
	std::vector <size_t> answer;

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("empty string in empty string") {
	std::string p = "";
	std::string t = "";
	std::vector <size_t> answer;

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("ababcx in ababcxababcyababcx") {
	std::string p = "ababcx";
	std::string t = "ababcxababcyababcx";
	std::vector <size_t> answer = {0, 12};

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

TEST_CASE ("abababca in babababca") {
	std::string p = "abababca";
	std::string t = "babababca";
	std::vector <size_t> answer = {1};

	// test Naive matcher
	Naive naive_matcher = Naive (p, t);
	REQUIRE (naive_matcher.FetchMatchLocations () == answer);

	// test Z matcher
	Z z_matcher = Z (p, t);
	REQUIRE (z_matcher.FetchMatchLocations () == answer);

	// test Boyer Moore matcher
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);

	// test KMP matcher
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	REQUIRE (kmp_matcher.FetchMatchLocations () == answer);
}

