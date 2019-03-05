#ifndef KNUTH_MORRIS_PRATT_H
#define KNUTH_MORRIS_PRATT_H

/*
 * KnuthMorrisPratt.h
 * Header file for the Knuth-Morris-Pratt algorithm that matches two strings: a pattern p with a text t
 * Returns a vector of the indices in t that start a complete match, or an empty vector if there are no matches
 * 
 * Intuition: a proper prefix or suffix is one that is neither the empty string nor the complete string. 
 * KMP preprocesses the pattern to produce a table that, for each index in pattern, stores the length
 * of the longest proper suffix of pattern(0:index) that is also a proper prefix of pattern. This lookup
 * is useful because if there is a partial match of pattern with text, the lookup tells you how many characters
 * you know you can shift pattern by because they are guaranteed to match after the skip. Why? Because up until the
 * first mismatch, a proper suffix of the pattern matched the text, and if that proper suffix is a proper prefix of
 * the pattern you can skip to it. This also doesn't skip too far because 
 * A match is detected when the length of the 
 *
 * Complexity: O(p + t), preprocessing pattern takes p time, scanning text with help of the lookup table takes t time
 * because redudant comparisons are skipped over.
 *
 * Alexander Gonsalves
 * 26/Feb/2019
 */

#include <iostream>
#include <string>
#include <vector>

class KnuthMorrisPratt {
	std::string pattern;
	std::string text;
	std::vector <size_t> z_array; // adapted from Z.cpp
	std::vector <size_t> sp_array; // preprossed pattern: suffix-prefix values for each index
	std::vector <size_t> match_locations;

	void ComputeZArray (); // z values are used to compute sp values
	void ComputeSPArray (); // computes sp values for each index in pattern
	void ComputeMatchLocations ();
public:
	// constructor
	KnuthMorrisPratt (const std::string& p, const std::string& t);
	// printer and getter for sp_array for match locations
	void PrintSPArray ();
	std::vector <size_t> FetchSPArray ();
	// printer and getter for match_locations
	void PrintMatchLocations ();
	std::vector <size_t> FetchMatchLocations ();
};

 #include "KnuthMorrisPratt.cpp"
 #endif