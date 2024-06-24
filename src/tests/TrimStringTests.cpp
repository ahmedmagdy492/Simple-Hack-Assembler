
#include <iostream>
#include <cassert>

#include "../include/Utils.h"

void TestTrimStringWithEmptyBeginOfStr() {
	std::string input = "	ahmed mohamed";
	
	Utils utils;

	std::string actual = utils.TrimString(input);
	std::string expected = "ahmed mohamed";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestTrimStringWithMultipleEmptyBeginOfStr() {
	std::string input = "	    ahmed mohamed";

	Utils utils;

	std::string actual = utils.TrimString(input);
	std::string expected = "ahmed mohamed";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestTrimStringWithWhiteSpacesLine() {
	std::string input = "	    ";

	Utils utils;

	std::string actual = utils.TrimString(input);
	std::string expected = "";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestTrimStringWithEmptyBeginOfStr" << std::endl;
	TestTrimStringWithEmptyBeginOfStr();
	std::cout << "TestTrimStringWithMultipleEmptyBeginOfStr" << std::endl;
	TestTrimStringWithMultipleEmptyBeginOfStr();
	std::cout << "TestTrimStringWithWhiteSpacesLine" << std::endl;
	TestTrimStringWithWhiteSpacesLine();
}