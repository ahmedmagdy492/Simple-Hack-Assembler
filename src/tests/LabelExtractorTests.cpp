
#include "../handlers/LabelExtractor.hpp"

void TestLabelExtractorWithMultipleLabelDefinations() {
	LabelExtractor lblExtractor;

	std::string input = "START:\n@12\nD=M\nSTART:\n@START\n;JMP";
	
	try {
		lblExtractor.Handle(input);

		std::cout << "Test Failed" << std::endl;
	}
	catch (std::string ex) {
		std::cout << "Success" << std::endl;
		std::cout << ex << std::endl;
	}
}

void TestLabelExtractorWithInvalidLabelDefination() {
	LabelExtractor lblExtractor;

	std::string input = "start:\n@12\nD=M\n@start\n;JMP";

	try {
		lblExtractor.Handle(input);

		std::cout << "Test Failed" << std::endl;
	}
	catch (std::string ex) {
		std::cout << "Success" << std::endl;
		std::cout << ex << std::endl;
	}
}

void TestLabelExtractorWithNormalOutput() {
	LabelExtractor lblExtractor;

	std::string input = "END:\n@12\nD=M\n@END\n;JMP";

	std::string actual = lblExtractor.Handle(input);
	std::string expected = "@12\nD=M\n@END\n;JMP";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

void TestLabelExtractorWithMultipleLabelsOutput() {
	LabelExtractor lblExtractor;

	std::string input = "LBL:\n@12\nD=M\nNEW:\n@LBL\n;JMP";

	std::string actual = lblExtractor.Handle(input);
	std::string expected = "@12\nD=M\n@LBL\n;JMP";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);
}

int main() {
	std::cout << "TestLabelExtractorWithMultipleLabelDefinations" << std::endl;
	TestLabelExtractorWithMultipleLabelDefinations();
	std::cout << "TestLabelExtractorWithInvalidLabelDefination" << std::endl;
	TestLabelExtractorWithInvalidLabelDefination();
	std::cout << "TestLabelExtractorWithNormalOutput" << std::endl;
	TestLabelExtractorWithNormalOutput();
	std::cout << "TestLabelExtractorWithMultipleLabelsOutput" << std::endl;
	TestLabelExtractorWithMultipleLabelsOutput();
}