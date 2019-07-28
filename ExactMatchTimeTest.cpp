/*
 * ExactMatchTimeTest.cpp
 * Tests execution time for the exact matching algorithms.
 * Alexander Gonsalves
 * 28/July/2019
 */

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "BoyerMoore.h"
#include "KnuthMorrisPratt.h"
#include "Z.h"

void ManyMatchesTest() {
	std::cout << "Test matching a in 10,000 a's:\n";

	std::string p = "a";
	std::string t = std::string (10000, 'a');

	auto Z_start = std::chrono::high_resolution_clock::now();
	Z z_matcher = Z (p, t);
	auto Z_stop = std::chrono::high_resolution_clock::now();
	auto Z_duration = std::chrono::duration_cast<std::chrono::microseconds> (Z_stop - Z_start);

	auto BM_start = std::chrono::high_resolution_clock::now();
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	auto BM_stop = std::chrono::high_resolution_clock::now();
	auto BM_duration = std::chrono::duration_cast<std::chrono::microseconds> (BM_stop	- BM_start);

	auto KMP_start = std::chrono::high_resolution_clock::now();
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	auto KMP_stop = std::chrono::high_resolution_clock::now();
	auto KMP_duration = std::chrono::duration_cast<std::chrono::microseconds> (KMP_stop - KMP_start);

	std::cout << "Z: " << Z_duration.count() << "\nBM: " << BM_duration.count() << "\nKMP: " << KMP_duration.count() << std::endl;
}

void ZeroMatchesTest() {
	std::cout << "Test matching b in 10,000 a's:\n";

	std::string p = "b";
	std::string t = std::string (10000, 'a');

	auto Z_start = std::chrono::high_resolution_clock::now();
	Z z_matcher = Z (p, t);
	auto Z_stop = std::chrono::high_resolution_clock::now();
	auto Z_duration = std::chrono::duration_cast<std::chrono::microseconds> (Z_stop - Z_start);

	auto BM_start = std::chrono::high_resolution_clock::now();
	BoyerMoore bm_matcher = BoyerMoore (p, t);
	auto BM_stop = std::chrono::high_resolution_clock::now();
	auto BM_duration = std::chrono::duration_cast<std::chrono::microseconds> (BM_stop	- BM_start);

	auto KMP_start = std::chrono::high_resolution_clock::now();
	KnuthMorrisPratt kmp_matcher = KnuthMorrisPratt (p, t);
	auto KMP_stop = std::chrono::high_resolution_clock::now();
	auto KMP_duration = std::chrono::duration_cast<std::chrono::microseconds> (KMP_stop - KMP_start);

	std::cout << "Z: " << Z_duration.count() << "\nBM: " << BM_duration.count() << "\nKMP: " << KMP_duration.count() << std::endl;
}



int main() {
	ManyMatchesTest();
	ZeroMatchesTest();
	return 0;
}