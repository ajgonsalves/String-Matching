#ifndef NAIVE_MATCH_CPP
#define NAIVE_MATCH_CPP

/*
 * Naive.cpp
 * Implementation file for brute-force string matching.
 *
 * Returns all the indices in "text" where an exact match with "pattern" occurs.
 * Complexity: O(p * t)
 * 
 * Alexander Gonsalves
 * 09/Feb/2019
 */

#include "Naive.h"
#include <iostream>
#include <string>
#include <vector>

void Naive::FindMatches () {
	// empty pattern or empty text exception
	if (text == "" || pattern == "")
		return;
	
	// pattern longer than text exception
	if (text.length () - pattern.length () < 0)
		return;

	size_t final_comparison = text.length () - pattern.length ();
	
	for (size_t i = 0; i <= final_comparison; ++i) {
		size_t j = 0;
		for (; j < pattern.length (); ++j) {
			if (pattern [j] != text [i + j])
				break;
		}
		if (j == pattern.length ())
			match_locations.push_back (i);
	}
}

Naive::Naive (const std::string& p, const std::string& t) {
	pattern = p;
	text = t;
	FindMatches ();
}

std::vector <size_t> Naive::FetchMatchLocations () {
	return match_locations;
}

#endif