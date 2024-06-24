
#include <iostream>
#include <cassert>

#include "../include/Utils.h"

void TestSplitStringWithNewLineDelimiterAndSingleNewLineInStr() {
	std::string str = "line1\nline2";
	char deli = '\n';

	Utils utils;
	std::vector<std::string>* output = utils.Split(str, deli);

	std::string actual = utils.ConvertVectorToString(*output);
	std::string expected = "line1 line2";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);

	delete output;
}

void TestSplitStringWithNewLineDelimiterAndNewLineAtStartAndNewLineAtEndStr() {
	std::string str = "\nline1\n";
	char deli = '\n';

	Utils utils;
	std::vector<std::string>* output = utils.Split(str, deli);

	std::string actual = utils.ConvertVectorToString(*output);
	std::string expected = "line1";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);

	delete output;
}

void TestSplitStringWithNewLineDelimiterAndMultipleSubsequentNewLines() {
	std::string str = "line1\n\n\nline2\n";
	char deli = '\n';

	Utils utils;
	std::vector<std::string>* output = utils.Split(str, deli);

	std::string actual = utils.ConvertVectorToString(*output);
	std::string expected = "line1 line2";

	std::cout << "actual: " << actual << ", expected: " << expected << std::endl;
	assert(actual == expected);

	delete output;
}

int main() {
	std::cout << "TestSplitStringWithNewLineDelimiterAndSingleNewLineInStr:" << std::endl;
	TestSplitStringWithNewLineDelimiterAndSingleNewLineInStr();
	std::cout << "TestSplitStringWithNewLineDelimiterAndNewLineAtStartAndNewLineAtEndStr:" << std::endl;
	TestSplitStringWithNewLineDelimiterAndNewLineAtStartAndNewLineAtEndStr();
	std::cout << "TestSplitStringWithNewLineDelimiterAndMultipleSubsequentNewLines" << std::endl;
	TestSplitStringWithNewLineDelimiterAndMultipleSubsequentNewLines();
}