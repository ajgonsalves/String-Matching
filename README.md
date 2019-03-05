# String-Matching
Implementations and unit testing of common string matching algorithms

Given two strings: pattern and text, these algorithms return all indices in text where a complete match with pattern is found.

The goal of this repository is ultimately to implement a suite of classic string matching algorithms,
and compare their performance across a variety of use cases (are both strings known completely in advance? are their sizes comparable? etc.)

To run an individual algorithm, simply include its header file and create an object of that algorithms class

Example:
#include "BoyerMoore.h"
BoyerMoore bm_matcher = BoyerMoore(pattern, string);
bm_matcher.FetchMatchLocations ();

To run unit tests of the algorithms included so far in the repo, simply compile and run one of the unit testing files.
The main testing file is: ExactMatchUnitTests.cpp
