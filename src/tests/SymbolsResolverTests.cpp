#include <iostream>
#include <cassert>

#include "../handlers/SymbolsResolver.hpp"

void TestSymbolsResolverWithVariableNameStartsWithNumbers() {
	
	std::string input = "@123sum\n";

	try {
		SymbolsResolver sr;
		sr.Handle(input);

		std::cout << "Test Failed" << std::endl;
	}
	catch (std::string ex) {
		std::cout << "Test Successeded" << std::endl;
		std::cout << ex << std::endl;
	}
}

void TestSymbolsResolverWithVariableNameContainsSpecialChars() {

	std::string input = "@sum*2\n";

	try {
		SymbolsResolver sr;
		sr.Handle(input);

		std::cout << "Test Failed" << std::endl;
	}
	catch (std::string ex) {
		std::cout << "Test Successeded" << std::endl;
		std::cout << ex << std::endl;
	}
}

void TestSymbolsResolverWithNormalVariableName() {

	std::string input = "START:\nD=M\n@sum\nM=D+M\n@i\nD=M";

	SymbolsResolver sr;
	std::string actual = sr.Handle(input);
	std::string expected = "START:\nD=M\n@16\nM=D+M\n@17\nD=M";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestSymbolsResolverWithVariableNameStartsWithNumbers" << std::endl;
	TestSymbolsResolverWithVariableNameStartsWithNumbers();
	std::cout << "TestSymbolsResolverWithVariableNameContainsSpecialChars" << std::endl;
	TestSymbolsResolverWithVariableNameContainsSpecialChars();
	std::cout << "TestSymbolsResolverWithNormalVariableName" << std::endl;
	TestSymbolsResolverWithNormalVariableName();
}