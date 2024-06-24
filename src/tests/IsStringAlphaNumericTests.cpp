
#include <iostream>
#include <cassert>

#include "../include/Utils.h"

void TestIsStringAlphNumericWithNonAlphaNumInput() {
	std::string input = "ahmed@sayded";

	Utils utils;
	bool actual = utils.IsStringAlphNumeric(input);
	bool expected = false;

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestIsStringAlphNumericWithAlphaNumInput() {
	std::string input = "ahmed1234";

	Utils utils;
	bool actual = utils.IsStringAlphNumeric(input);
	bool expected = true;

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestIsStringAlphNumericWithNonAlphaNumInput" << std::endl;
	TestIsStringAlphNumericWithNonAlphaNumInput();
	std::cout << "TestIsStringAlphNumericWithAlphaNumInput" << std::endl;
	TestIsStringAlphNumericWithAlphaNumInput();
}