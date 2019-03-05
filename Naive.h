#ifndef NAIVE_MATCH_H
#define NAIVE_MATCH_H

/*
 * Naive.h
 * Header file for brute-force exact matching of a single pattern with a single text.
 * 
 * Alexander Gonsalves
 * 09/Feb/2019
 */

#include <iostream>
#include <string>
#include <vector>

class Naive {
	std::string pattern;
	std::string text;
	std::vector <size_t> match_locations;

	void FindMatches ();
public:
	Naive (const std::string& p, const std::string& t);
	std::vector <size_t> FetchMatchLocations ();
};

#include "Naive.cpp"
#endif