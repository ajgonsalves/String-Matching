/*
 * BoyerMoore_UnitTests.cpp
 * Unit tests to check for correctness and debug BoyerMoore.cpp
 * Alexander Gonsalves
 * 19/Feb/2019
 */

#include <iostream>
#include <string>
#include <vector>

//#include "catch_main.cpp"
#include "BoyerMoore.h"

/*
TEST_CASE ("abcabxabc in zzabcabxabczz") {
	std::string p = "abcabxabc";
	std::string t = "zzabcabxabczz";
	std::vector <size_t> answer = {2};

	BoyerMoore bm_matcher = BoyerMoore (p, t);
	bm_matcher.PrintBadCharacterLookup ();
	bm_matcher.ComputeMatchLocations ();
	REQUIRE (bm_matcher.FetchMatchLocations () == answer);
}
*/

void abcabxabc () {
	std::string p = "abcabxabc";
	std::string t = "zzabcabxabczz";
	std::vector <size_t> answer = {2};

	BoyerMoore bm_matcher = BoyerMoore (p, t);
	bm_matcher.PrintMatchLocations ();
}

void a () {
	std::string p = "a";
	std::string t = "aaaaa";
	std::vector <size_t> answer = {0, 1, 2, 3, 4};

	BoyerMoore bm_matcher = BoyerMoore (p, t);
	bm_matcher.PrintMatchLocations ();
}

int main () {
	a ();
	abcabxabc ();
	return 0;
}