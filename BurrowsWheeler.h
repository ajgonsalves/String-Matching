#ifndef BURROWS_WHEELER_H
#define BURROWS_WHEELER_H

/*
 * BurrowsWheeler.h
 * Header file for the BurrowsWheeler class which is capable of taking a string and applying the Burrows-Wheeler Transform to it,
 * as well as inverting a BWT-string to the original string.
 * 
 * The use of BWT is to reduce the entropy of strings, allowing for better compression. 
 * 
 * Alexander Gonsalves
 * 9/June/2019
 */

#include <map>
#include <queue>
#include <string>
#include <vector>

class BurrowsWheeler {
	std::string encoded;
	std::string decoded;
	bool encode_polarity; // true - encode, false - decode
	std::vector <int> suffix_array;

	// nested struct to represent a character, for example: a0 is the first instance of the character 'a'
	struct Occurrence {
		char ch;
		int occ;
		Occurrence (const char& c, const int& o): ch(c), occ(o) {}; // l-value constructor
		Occurrence (char&& c, int&& o): ch(c), occ(o) {}; // r-value constructor
		bool operator== (const Occurrence& rhs) {if (rhs.ch == ch && rhs.occ == occ) return true; else return false;}; // overloaded == operator
		bool operator!= (const Occurrence& rhs) {if (rhs.ch != ch || rhs.occ != occ) return true; else return false;} // overloaded != operator
		bool operator< (const Occurrence& rhs) {if (ch < rhs.ch || (ch == rhs.ch && occ < rhs.occ)) return true; else return false;}; // overloaded < operator
	};

	void preprocessOriginal (std::string& user_input); // replaces '$' characters with 'D' characters'
	void radixSortIteration (const std::string& s, std::queue <int>& indices, int iteration); // helper method for encodeString()
	std::string encodeString (std::string& s);
	std::string decodeString (std::string& t);
public:
	// constructor
	BurrowsWheeler (std::string user_input, bool encode_flag);
	// accessors
	std::string getEncoded ();
	std::string getDecoded ();
};

#include "BurrowsWheeler.cpp"
#endif