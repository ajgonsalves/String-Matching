#ifndef Z_CPP
#define Z_CPP

/* 
 * Z.cpp
 * Implementation file for Z-algorithm that matches two strings: a pattern p with a text t
 * Returns a vector of the indices in t that start a complete match, or an empty vector if there are no matches
 *
 * Alexander Gonsalves
 * 11/Feb/2019
 */

#include <string>
#include <vector>
#include "Z.h"


// default, parameterized constructor expects p and t to be devoid of any '$' characters
Z::Z (std::string& p, std::string& t) {
	pattern = p;
	text = t;
	z_string = p + "$" + t;

	z_array.resize (z_string.length ());
	z_array [0] = 0; // only proper prefixes will have a z_box value

	ComputeZArray ();
	SearchZArrayForMatches ();
}

void Z::ComputeZArray () {
	// empty pattern or text exception
	if (pattern.empty () || text.empty ())
		return;

	// pattern is larger than text exception
	if (pattern.length () > text.length ())
		return;

	// initialize variables
	size_t l = 0; // the left-most index of the furthest-reaching Z-box so far
	size_t r = 0; // the right-most index of the furthest reaching Z-box so far
	size_t k = 1; // the index of z_array we are computing at the moment

	// now inductively compute the z-boxes
	for (; k < z_string.length (); ++k) {
		// case 1: k is outside any z-box
		if (k > r) {
			// manually compare characters from k, checking for a prefix match
			size_t i = k;
			for (; i < z_string.length (); ++i) {
				if (z_string [i] != z_string [i - k])
					break;
			}
			// if there was a z_box, update l, r, and z_array [k]
			if (i > k) {
				z_array [k] = i - k; // i is the index of the first mismatch, so don't include it
				l = k;
				r = i - 1;
			}
		}
		// case 2: k is inside a z-box
		else {
			// case 2a: z of k' is within the bounds of the current z-box
			if (z_array [k - l] < (r - k + 1))
				z_array [k] = z_array [k - l];
			// case 2b: z of k' extends to the bounds of the current z-box (and therefore may extend even further)
			else {
				size_t k_extension = r + 1;
				for (; k_extension < z_string.length (); ++k_extension) {
					if (z_string [k_extension] != z_string [k_extension - l])
						break;
				}
				// if k_extension > r + 1, then we have to update the zbox parameters
				if (k_extension > r + 1) {
					r = k_extension - 1; // k_extension is the index of the first mismatch, so r is the index right before it
					l = k;
				}
				z_array [k] = k_extension - k; // we don't include z_string [k_extension] itself because k_extension is the index of the first mismatch
			}
		}
	}
}

void Z::SearchZArrayForMatches () {
	// empty pattern or text exception
	if (pattern.empty () || text.empty ())
		return;

	// pattern is larger than text exception
	if (pattern.length () > text.length ())
		return;

	for (size_t i = pattern.length () + 1; i < z_array.size (); ++i) {
		if (z_array [i] == pattern.length ())
			match_locations.push_back (i - (pattern.length () + 1));
	}
}

std::vector <size_t> Z::FetchMatchLocations () {
	return match_locations;
}

std::vector <size_t> Z::FetchZArray () {
	return z_array;
}

#endif