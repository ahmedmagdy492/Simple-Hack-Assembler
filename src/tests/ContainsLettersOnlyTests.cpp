
#include <iostream>
#include <cassert>

#include "../include/Utils.h"

void TestContainsLettersOnlyWithNormalString() {
	std::string input = "ahmed:";

	Utils utils;
	bool actual = utils.ContainsLettersOnly(input, ':');
	bool expected = true;
	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestContainsLettersOnlyWithNonAlphaString() {
	std::string input = "ahm4ed3";

	Utils utils;
	bool actual = utils.ContainsLettersOnly(input);
	bool expected = false;
	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestContainsLettersOnlyWithNormalString" << std::endl;
	TestContainsLettersOnlyWithNormalString();

	std::cout << "TestContainsLettersOnlyWithNonAlphaString" << std::endl;
	TestContainsLettersOnlyWithNonAlphaString();
}