#ifndef Z_H
#define Z_H

/* 
 * Z.h
 * Header file for Z-algorithm that matches two strings: a pattern p with a text t
 * Returns a vector of the indices in t that start a complete match, or an empty vector if there are no matches
 *
 * Intuition: z_string is pattern concatenated with "$" token concatenated with text
 * z_array computes, for each index after 0, the length of substring starting at that index that matches a prefix of the pattern
 * since "$" does not appear in either pattern nor text, indices with z_array values of |pattern| are matches
 *
 * Complexity:
 * 
 * Alexander Gonsalves
 * 11/Feb/2019
 */

#include <string>
#include <vector>

class Z {
	std::string pattern;
	std::string text;
	std::string z_string; // pattern $ text
	std::vector <size_t> z_array; // for each index of z_string, stores the length of matching substring starting at that index that matches a prefix of the Z_string
	std::vector <size_t> match_locations; // empty if there are no matches

	void ComputeZArray ();
	void SearchZArrayForMatches ();
public:
	Z (std::string& p, std::string& t);
	std::vector <size_t> FetchMatchLocations ();
	std::vector <size_t> FetchZArray ();
};

#include "Z.cpp"
#endif