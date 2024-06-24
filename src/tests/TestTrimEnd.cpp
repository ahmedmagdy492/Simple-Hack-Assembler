#include "../include/Utils.h"

#include <iostream>
#include <cassert>

void TestTrimEndWithSimpleString() {
	std::string input = "@R0		";

	Utils utils;
 	std::string actual = utils.TrimEnd(input);
	std::string expected = "@R0";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;

	if (actual != expected) {
		assert(actual == expected);
	}
}

int main() {
	std::cout << "TestTrimEndWithSimpleString" << std::endl;
	TestTrimEndWithSimpleString();
}