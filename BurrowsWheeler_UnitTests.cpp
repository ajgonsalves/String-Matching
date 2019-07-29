/*
 * BurrowsWheeler_UnitTests.cpp
 * Alexander Gonsalves, 15/July/2019
 */

#include "BurrowsWheeler.cpp"
#include "catch_main.cpp"
#include <iostream>
#include <string>

TEST_CASE ("encode: a") {
	std::string s = "a";
	std::string t = "a$";

	BurrowsWheeler encoder = BurrowsWheeler (s);
	REQUIRE (encoder.getEncoded() == t);
}

TEST_CASE ("encode: ab") {
	std::string s = "ab";
	std::string t = "b$a";

	BurrowsWheeler encoder = BurrowsWheeler (s);
	REQUIRE (encoder.getEncoded() == t);
}

TEST_CASE ("encode: banana") {
	std::string s = "banana";
	std::string t = "annb$aa";

	BurrowsWheeler encoder = BurrowsWheeler (s);
	REQUIRE (encoder.getEncoded() == t);
}

TEST_CASE ("encode: panamabananas") {
	std::string s = "panamabananas";
	std::string t = "smnpbnnaaaaa$a";

	BurrowsWheeler encoder = BurrowsWheeler (s);
	REQUIRE (encoder.getEncoded() == t);
}

TEST_CASE ("decode: a$") {
	std::string s = "a$";
	std::string t = "a";

	BurrowsWheeler decoder = BurrowsWheeler (s, false);
	REQUIRE (decoder.getDecoded() == t);
}

TEST_CASE ("decode: b$a") {
	std::string s = "b$a";
	std::string t = "ab";

	BurrowsWheeler decoder = BurrowsWheeler (s, false);
	REQUIRE (decoder.getDecoded() == t);
}

TEST_CASE ("decode: annb$aa") {
	std::string s = "annb$aa";
	std::string t = "banana";

	BurrowsWheeler decoder = BurrowsWheeler (s, false);
	REQUIRE (decoder.getDecoded() == t);
}

TEST_CASE ("decode: smnpbnnaaaaa$a") {
	std::string s = "smnpbnnaaaaa$a";
	std::string t = "panamabananas";

	BurrowsWheeler decoder = BurrowsWheeler (s, false);
	REQUIRE (decoder.getDecoded() == t);
}

TEST_CASE ("decode(encode(panamabananas))") {
	std::string s = "panamabananas";
	BurrowsWheeler reversible = BurrowsWheeler (s);
	std::string encoded = reversible.getEncoded();
	BurrowsWheeler restored = BurrowsWheeler (encoded, false);
	REQUIRE (restored.getDecoded() == s);
}

TEST_CASE ("decode(encode(It was Professor McGonnagall, and her mouth was the thinnest of thin lines.))") {
	std::string s = "It was Professor McGonnagall, and her mouth was the thinnest of thin lines.";
	BurrowsWheeler reversible = BurrowsWheeler (s);
	std::string encoded = reversible.getEncoded();
	BurrowsWheeler restored = BurrowsWheeler (encoded, false);
	REQUIRE (restored.getDecoded() == s);
}