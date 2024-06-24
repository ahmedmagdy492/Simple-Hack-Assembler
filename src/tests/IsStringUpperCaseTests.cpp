
#include <iostream>
#include <cassert>

#include "../include/Utils.h"

void TestIsStringUpperCaseWithLowerCaseString() {
	std::string input = "ahmed";

	Utils utils;
	bool actual = utils.IsStringUpperCase(input);
	bool expected = false;

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestIsStringUpperCaseWithUpperCaseString() {
	std::string input = "AHMED";

	Utils utils;
	bool actual = utils.IsStringUpperCase(input);
	bool expected = true;

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestIsStringUpperCaseWithLowerCaseString" << std::endl;
	TestIsStringUpperCaseWithLowerCaseString();

	std::cout << "TestIsStringUpperCaseWithUpperCaseString" << std::endl;
	TestIsStringUpperCaseWithUpperCaseString();
}