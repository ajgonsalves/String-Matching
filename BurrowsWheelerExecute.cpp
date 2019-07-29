/*
 * BurrowsWheelerExecute.cpp
 * Simple main to execute encode and decode functions of BurrowsWheeler.cpp
 * Alexander Gonsalves
 * 29/July/2019
 */

#include <iostream>
#include <string>
#include "BurrowsWheeler.h"

std::string Encode (std::string s) {
	BurrowsWheeler encoder = BurrowsWheeler (s);
	return encoder.getEncoded();
}

std::string Decode (std::string s) {
	// check that the s has a '$' character
	size_t i = 0;
	for (; i < s.size(); ++i) {
		if (s[i] == '$')
			break;
	}
	if (i == s.size())
		throw "No '$' character in string meant for decoding.\n";

	BurrowsWheeler decoder = BurrowsWheeler (s, false);
	return decoder.getDecoded();
}

int main() {
	std::string user_choice, user_string;

	while (user_choice != "e" && user_choice != "d" && user_choice != "q") {
		std::cout << "type 'e' to encode, 'd' to decode, or 'q' to quit.\n";
		std::cin >> user_choice;
	}

	if (user_choice != "q") {
		std::cout << "Input target string:\n";
		std::cin.ignore();
		std::getline(std::cin, user_string);

		if (user_choice == "e")
			std::cout << Encode (user_string) << std::endl;
		else {
			try {
				std::cout << Decode (user_string) << std::endl;
			} catch (const char* msg) {
				std::cerr << msg << std::endl;
			}
		}
	}

	return 0;
}