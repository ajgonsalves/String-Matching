#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

/*
 * BoyerMoore.h
 * Header file for the Boyer-Moore algorithm that matches two strings: a pattern p with a text t
 * Returns a vector of the indices in t that start a complete match, or an empty vector if there are no matches
 * 
 * Boyer-Moore preprocesses the pattern according to two rules: the good suffix rule and the bad character rule
 * https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm
 *
 * Complexity: O(p + t) pattern and text lengths
 * 
 * Alexander Gonsalves
 * 17/Feb/2019
 */

#include <vector>

class BoyerMoore {

	// nested struct - a vector containing all indices in pattern with character ch
	struct CharIndices {
		char ch;
		std::vector <size_t> indices;
		CharIndices (const char& c): ch {c} {}; // l-value constructor
		CharIndices (char&& c): ch {c} {}; // r-value constructor
	};

private:
	// key instance variables
	std::string pattern;
	std::string text;
	std::vector <CharIndices> char_lookup; // lookup table for bad character rule
	std::vector <size_t> match_locations;

	// Bad Character Rule
	bool CharExists (const char& c); // helper method that returns true if a CharIndices object exists for "c" in char_lookup, or false otherwise
	size_t CharLoc (const char& c); // helper method that returns the index in char_lookup of the CharExists indices object for "c", or the char_lookup.size () otherwise
	void AddEntry (const char& ch, const size_t& loc); // helper method that pushes back "loc" in the indices member of the CharIndices object at index "ch" in char_lookup
	void BoyerMoorePreprocessing (const std::string& str);
	int BadCharacterRule (const size_t& pattern_index, const size_t& text_index);
	void ComputeMatchLocations ();

public:
	// constructor
	BoyerMoore (const std::string& p, const std::string t);
	// match_locations accessor
	std::vector <size_t> FetchMatchLocations ();
	void PrintBadCharacterLookup (); // DEBUG
	void PrintMatchLocations (); // DEBUG
};

#include "BoyerMoore.cpp"
 #endif