#ifndef BOYER_MOORE_CPP
#define BOYER_MOORE_CPP

/*
 * BoyerMoore.h
 * Implementation file for the Boyer-Moore algorithm that matches two strings: a pattern p with a text t
 * Returns a vector of the indices in t that start a complete match, or an empty vector if there are no matches
 * 
 * Boyer-Moore preprocesses the pattern according to two rules: the good suffix rule and the bad character rule
 * https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm
 *
 * Complexity: O(p + t) , pattern and text lengths
 * 
 * Alexander Gonsalves
 * 19/Feb/2019
 */

#include "BoyerMoore.h"
#include <iostream>
#include <string>
#include <vector>

// helper method that returns true if a CharIndices object exists for "c" in char_lookup, or false otherwise
bool BoyerMoore::CharExists (const char& c) {
	for (size_t i = 0; i < char_lookup.size (); ++i) {
		if (char_lookup [i].ch == c)
			return true;
	}
	return false;
}

// helper method that returns the index in char_lookup of the CharExists indices object for "c", or the char_lookup.size () otherwise
size_t BoyerMoore::CharLoc (const char& c) {
	size_t i = 0;
	
	for (; i < char_lookup.size (); ++i) {
		if (char_lookup [i].ch == c)
			break;
	}
	return i;
}

// helper method that pushes back "loc" in the indices member of the CharIndices object at index "ch" in char_lookup
void BoyerMoore::AddEntry (const char& ch, const size_t& loc) {
	size_t index = CharLoc (ch);

	// if ch isn't currently in the list, add a CharIndices object for ch at the end of char_lookup
	if (index == char_lookup.size ()) {
		char_lookup.emplace_back (CharIndices (ch));
	}

	// push_back loc
	char_lookup [index].indices.push_back (loc);
}

void BoyerMoore::BoyerMoorePreprocessing (const std::string& str) {
	// empty pattern exception
	if (str.empty ())
		return;

	char c;
	for (size_t i = str.length () - 1; i >= 0;) {
		c = str [i];
		AddEntry (c, i);

		// size_t can never be negative
		if (i > 0)
			--i;
		else
			break;
	}
}

int BoyerMoore::BadCharacterRule (const size_t& pattern_index, const size_t& text_index) {
	int previous_occurrence = pattern_index - 1; // the index in pattern where the previous occurrence of text [text_index] occurs
	
	// is there a mismatch?
	if (pattern [pattern_index] != text [text_index]) {
		previous_occurrence = 0; // if we don't find a previous occurence in pattern, we'll shift by the entirety of remaining pattern
		// does pattern have an occurence of text [text_index]?
		if (CharExists (text [text_index])) {
			// iterate through char_lookup [char_index] to find a previous occurrence of text [text_index]
			size_t char_index = CharLoc (text [text_index]);
			for (size_t i = 0; i < char_lookup [char_index].indices.size (); ++i) {
				if (char_lookup [char_index].indices [i] < pattern_index) {
					previous_occurrence = char_lookup [char_index].indices [i];
					break;
				}
			}
		}
	}

	return previous_occurrence;
}

void BoyerMoore::ComputeMatchLocations () {
	// empty string exception
	if (pattern.empty () || text.empty ())
		return;

	// pattern length exceeds text length exception
	if (pattern.length () > text.length ())
		return;

	size_t text_index = pattern.length() - 1;

	while (text_index < text.length ()) {
		size_t pattern_index = pattern.length () - 1; // right to left scan
		int bad_character_shift; // how far along we jump, if this is more than 1, it's because there was a mismatch
		bool mismatch_found = false;
		
		while (pattern_index > 0) {
			size_t matching_text_index = text_index + pattern_index + 1 - pattern.length ();
			// if the characters match, just keep going
			if (pattern [pattern_index] == text [matching_text_index])
				--pattern_index;
			// otherwise, calculate how much to shift the pattern by, and start the right-to-left scan over again
			else {
				bad_character_shift = pattern_index - BadCharacterRule (pattern_index, matching_text_index);
				text_index += bad_character_shift;
				mismatch_found = true;
				break;
			}
		}
		// was there a complete match?
		if (mismatch_found == false) {
			if (pattern_index == 0 && text [text_index + 1 - pattern.length ()] == pattern [0])
				match_locations.push_back (text_index + 1 - pattern.length ());
			++text_index;
		}
	}
}

BoyerMoore::BoyerMoore (const std::string& p, const std::string t) {
	pattern = p;
	text = t;
	BoyerMoorePreprocessing (p);
	ComputeMatchLocations ();
}

std::vector <size_t> BoyerMoore::FetchMatchLocations () {
	return match_locations;
}

void BoyerMoore::PrintBadCharacterLookup () {
	for (size_t i = 0; i < char_lookup.size (); ++i) {
		std::cout << char_lookup [i].ch << ": ";
		for (size_t j = 0; j < char_lookup [i].indices.size (); ++j) {
			std::cout << char_lookup [i].indices [j] << " ";
		}
		std::cout << "\n";
	}
}

void BoyerMoore::PrintMatchLocations () {
	for (size_t i = 0; i < match_locations.size (); ++i) {
		std::cout << match_locations [i] << " ";
	}
	std::cout << "\n";
}

#endif