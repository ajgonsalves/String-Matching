#ifndef KNUTH_MORRIS_PRATT_CPP
#define KNUTH_MORRIS_PRATT_CPP

/*
 * KnuthMorrisPratt.cpp
 * Implementation file for the Knuth-Morris-Pratt algorithm that matches two strings: a pattern p with a text t
 * Returns a vector of the indices in t that start a complete match, or an empty vector if there are no matches
 * 
 * Intuition: a proper prefix or suffix is one that is neither the empty string nor the complete string. 
 * KMP preprocesses the pattern to produce a table that, for each index in pattern, stores the length
 * of the longest proper suffix of pattern(0:index) that is also a proper prefix of pattern. This lookup
 * is useful because if there is a partial match of pattern with text, the lookup tells you how many characters
 * you know you can shift pattern by because they are guaranteed to match after the skip. Why? Because up until the
 * first mismatch, a proper suffix of the pattern matched the text, and if that proper suffix is a proper prefix of
 * the pattern you can skip to it. This also doesn't skip too far because the largest possible
 * suffix-prefix length is subtracted from the skip amount.
 *
 * Complexity: O(p + t), preprocessing pattern takes p time, scanning text with help of the lookup table takes t time
 * because redudant comparisons are skipped over.
 *
 * Alexander Gonsalves
 * 26/Feb/2019
 */

#include "KnuthMorrisPratt.h"
#include <iostream>
#include <string>
#include <vector>

// adapted from Z.cpp
void KnuthMorrisPratt::ComputeZArray () {
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
	for (; k < pattern.length (); ++k) {
		// case 1: k is outside any z-box
		if (k > r) {
			// manually compare characters from k, checking for a prefix match
			size_t i = k;
			for (; i < pattern.length (); ++i) {
				if (pattern [i] != pattern [i - k])
					break;
			}
			// if there was a z_box, update l, r, and z_array [k]
			if (i > k) {
				z_array [k] = i - k;
				l = k;
				r = i - 1;
			}
		}
		// case 2: k is inside a z-box
		else {
			// case 2a: z of k' is within the bounds of the current z-box
			if (z_array [k - l] < (r + 1 - k))
				z_array [k] = z_array [k - l];
			// case 2b: z of k' extends to the bounds of the current z-box (and therefore may extend even further)
			else {
				size_t k_extension = r + 1;
				for (; k_extension < pattern.length (); ++k_extension) {
					if (pattern [k_extension] != pattern [k_extension - k])
						break;
				}

				// k_extension is the index of the first mismatch
				z_array [k] = k_extension - k;
				l = k;
				r = k_extension - 1;
			}
		}
	}
}

void KnuthMorrisPratt::ComputeSPArray () {
	// empty pattern or text exception
	if (pattern.empty () || text.empty ())
		return;

	// pattern is larger than text exception
	if (pattern.length () > text.length ())
		return;

	// initialize all sp values to 0
	for (size_t i = 0; i < pattern.length (); ++i) {
		sp_array [i] = 0;
	}

	// sp' value of i is the distance to the left-end of the z_box ending at i
	for (int j = pattern.length () - 1; j > 0; --j) {
		int i = j + z_array [j] - 1;
		sp_array [i] = z_array [j];
	}
	sp_array [pattern.length ()] = sp_array [pattern.length () - 1];

	// sp value extends the sp' values by including the rest of the z-boxes, not just the right ends
	// note that conceptually, sp' values are just sp values with the added condition that p [i + 1] != p [i - j + 1]
	for (int i = pattern.length () - 2; i > 0; --i) {
		int prev_sp = sp_array [i + 1] - 1;
		if (prev_sp > (int) sp_array [i])
			sp_array [i] = (size_t) prev_sp;
	}
}

void KnuthMorrisPratt::PrintSPArray () {
	std::cout << "KMP SP: ";
	for (size_t i = 0; i < sp_array.size (); ++i) {
		std::cout << sp_array [i];
	}
	std::cout << "\n";
}

std::vector <size_t> KnuthMorrisPratt::FetchSPArray () {
	return sp_array;
}

void KnuthMorrisPratt::ComputeMatchLocations () {
	// empty pattern or text exception
	if (pattern.empty () || text.empty ())
		return;

	// pattern is larger than text exception
	if (pattern.length () > text.length ())
		return;

	size_t t_ind = 0; // index in the text we are currently examining
	size_t p_ind = 0; // index in the pattern we are currently examining

	while (t_ind + (pattern.length () - p_ind) <= text.length ()) {
		while (p_ind < pattern.length() && pattern [p_ind] == text [t_ind]) {
			p_ind++;
			t_ind++;
		}

		// complete match
		if (p_ind == pattern.length ())
			match_locations.push_back (t_ind - p_ind);

		// text [t_ind] doesn't appear in p at all
		if (p_ind == 0)
			t_ind++;
		// otherwise we can safely shift
		else 
			p_ind = sp_array [p_ind - 1];
	}
}

void KnuthMorrisPratt::PrintMatchLocations () {
	std::cout << "KMP matches: ";
	for (size_t i = 0; i < match_locations.size (); ++i) {
		std::cout << match_locations [i] << " ";
	}
	std::cout << "\n";
}

std::vector <size_t> KnuthMorrisPratt::FetchMatchLocations () {
	return match_locations;
}

KnuthMorrisPratt::KnuthMorrisPratt (const std::string& p, const std::string& t) {
	pattern = p;
	text = t;

	z_array.resize (pattern.length ());
	sp_array.resize (pattern.length () + 1); // we define an additional sp_value past the right end of pattern

	ComputeZArray ();
	ComputeSPArray ();
	ComputeMatchLocations ();
}

#endif