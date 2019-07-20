#ifndef BURROWS_WHEELER_CPP
#define BURROWS_WHEELER_CPP

#include "BurrowsWheeler.h"
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

BurrowsWheeler::BurrowsWheeler (std::string user_input, bool encode_flag = true) {
	encode_polarity = encode_flag;

	if (encode_polarity) {
		decoded = user_input;
		preprocessOriginal (user_input);
		encoded = encodeString (user_input);
	}
	else {
		encoded = user_input;
		decoded = decodeString (user_input);
	}
}

void BurrowsWheeler::preprocessOriginal (std::string& s) {
	for (char c: s) {
		if (c == '$')
			c = 'D';
	}
	s.push_back('$');
	return;
}

void BurrowsWheeler::radixSortIteration (const std::string& s, std::queue <int>& indices, int iteration) {
	// exception: invalid iteration value
	if (iteration < 0 || iteration >= s.size())
		return;

	// initialize important variables
	std::map <int, std::queue<int>> radix;
	int m = s.size();
	int index; // index where the cyclic rotation of the string begins
	int end_index; // index where the cyclic rotation of the string ends
	int charValue;

	// add indices to the radix
	while (!indices.empty()) {
		index = indices.front();
		end_index = (index + m - iteration) % m; 
		
		// ascertain the charValue
		if (s[end_index] == '$')
			charValue = -1;
		else
			charValue = int (s[end_index]);

		// add this index to the radix
		if (radix.count (charValue) == 0)
			radix.emplace (charValue, std::queue <int>());
		radix[charValue].push (index);

		indices.pop();
	}

	// reconstruct indices from radix
	for (auto map_iter = radix.begin(); map_iter != radix.end(); ++map_iter) {	
		while (!map_iter->second.empty()) {
			indices.push(map_iter->second.front());
			map_iter->second.pop();
		}
	}
	return;
}

std::string BurrowsWheeler::encodeString (std::string& s) {
	// empty string exception
	if (s.empty())
		return "";

	// initialize indices
	std::queue<int> indices;
	for (int i = 0; i < s.size(); ++i) {
		indices.push(i);
	}

	// radix sort
	for (int i = 0; i < s.size(); ++i) {
		radixSortIteration (s, indices, i);
	}

	// reconstruct last column as a string
	std::string last_column;
	int end_index;

	while (!indices.empty()) {
		end_index = (indices.front() + s.size()) % s.size();
		last_column += s[end_index];
		indices.pop();
	}

	return last_column;
}

std::string BurrowsWheeler::decodeString (std::string& s) {
	std::vector <Occurrence> first_column; // includes everything in s in sorted order
	std::vector <Occurrence> last_column; // includes everything in s, and is not sorted at all
	std::map <char, int> num_occurrences; // how many times each character has appeared
	int m = s.size();

	// populate last_column and num_occurrences
	for (int i = 0; i < m; ++i) {
		if (num_occurrences.count (s[i]) == 0)
			num_occurrences.emplace (std::pair <char, int> (s[i], 0));

		last_column.emplace_back (Occurrence (s[i], num_occurrences[s[i]]));
		num_occurrences[s[i]] += 1;
	}

	// populate first_column
	first_column.emplace_back (Occurrence ('$', 0));
	for (auto iter = num_occurrences.begin(); iter != num_occurrences.end(); ++iter) {
		if (iter->first != '$') {
			for (int i = 0; i < iter->second; ++i) {
				first_column.emplace_back (Occurrence (iter->first, i));
			}
		}
	}

	// construct original (decoded) string with the left shift technique
	// https://www.youtube.com/watch?v=DqdjbK68l3s
	Occurrence current_occurrence = Occurrence ('$', 0);
	char original[m];
	original[m - 1] = '\0';

	for (int i = m - 2; i >= 0; --i) {
		int j = 0;

		while (j < m && first_column[j] != current_occurrence)
			++j;

		original[i] = last_column[j].ch;
		current_occurrence = last_column[j];
	}

	return (std::string (original));
}

std::string BurrowsWheeler::getEncoded () {
	return encoded;
}

std::string BurrowsWheeler::getDecoded () {
	return decoded;
}

#endif