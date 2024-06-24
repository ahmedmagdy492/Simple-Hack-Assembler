
#include <iostream>
#include <cassert>

#include "../handlers/CodeExtractor.hpp"

void TestCodeExtractorWithCommentLine() {
	CodeExtractor codeExtractor;
	std::string code = "@12\n//adding 12 to A\n;JMP\n// unconditional jump";

	std::string actual = codeExtractor.Handle(code);
	std::string expected = "@12\n;JMP";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestCodeExtractorWithCommentLineAndEmptySpaceLine() {
	CodeExtractor codeExtractor;
	std::string code = "@12\n//adding 12 to A\n    \n;JMP\n// unconditional jump";

	std::string actual = codeExtractor.Handle(code);
	std::string expected = "@12\n;JMP";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestCodeExtractorWithCommentLine" << std::endl;
	TestCodeExtractorWithCommentLine();
	std::cout << "TestCodeExtractorWithCommentLineAndEmptySpaceLine" << std::endl;
	TestCodeExtractorWithCommentLineAndEmptySpaceLine();
}