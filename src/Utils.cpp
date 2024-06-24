#include "include/Utils.h"
#include <fstream>
#include <sstream>


std::vector<std::string>* Utils::Split(std::string& inputStr, char delim) const
{
	std::vector<std::string>* output = new std::vector<std::string>();

	std::string outputStr;

	for (int i = 0; i < inputStr.length(); ++i) {
		if (inputStr[i] != delim) {
			outputStr += inputStr[i];
		}
		else {
			if (!outputStr.empty()) {
				output->push_back(outputStr);
				outputStr.clear();
			}
		}
	}

	if (!outputStr.empty()) {
		output->push_back(outputStr);
	}

	return output;
}

std::string Utils::ConvertVectorToString(const std::vector<std::string>& vec) const
{
	std::string output;
	size_t vecSize = vec.size();

	for (size_t i = 0; i < vecSize; ++i) {
		if (i < (vecSize - 1)) {
			output.append(vec[i]);
			output.append(" ");
		}
		else {
			output.append(vec[i]);
		}
	}

	return output;
}

std::string Utils::TrimString(const std::string& str) const {
	std::string outStr;
	bool encounteredNonEmptyChar = false;

	for (int i = 0; i < str.length(); ++i) {
		if (!encounteredNonEmptyChar) {
			if (str[i] == ' ' || str[i] == '\t') {
				continue;
			}
			else {
				encounteredNonEmptyChar = true;
				outStr += str[i];
			}
		}
		else {
			outStr += str[i];
		}
	}

	return outStr;
}

bool Utils::ContainsLettersOnly(const std::string& str, char exceptChar) const {
	if (exceptChar == '\0') {
		for (auto& letter : str) {
			if (!isalpha(letter))
				return false;
		}
	}
	else {
		for (auto& letter : str) {
			if (!isalpha(letter) && letter != exceptChar)
				return false;
		}
	}

	return true;
}

bool Utils::IsStringUpperCase(const std::string& str) const {
	for (auto& letter : str) {
		if (!isupper(letter))
			return false;
	}

	return true;
}

bool Utils::IsStringAlphNumeric(const std::string& str) const {
	for (auto& c : str) {
		if (!std::isalnum(c)) {
			return false;
		}
	}

	return true;
}

std::string Utils::ReadFile(const std::string& path) {
	std::fstream file;

	file.open(path);

	if (!file.is_open()) {
		std::stringstream strStream;
		strStream << "Failed to open file " << path << std::endl;
		throw strStream.str();
	}

	std::stringstream fileContent;

	fileContent << file.rdbuf();

	file.close();

	return fileContent.str();
}

bool Utils::IsStrContainsNumbersOnly(const std::string& str) {
	for (auto& c : str) {
		if (!std::isdigit(c))
			return false;
	}

	return true;
}

std::string& Utils::RevStr(std::string& str) {
	size_t strLen = str.length();

	for (int i = 0, j = strLen - 1; i < j; ++i, --j) {
		char temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}

	return str;
}

std::string Utils::TrimEnd(const std::string& str) {
	std::string outStr;
	bool encounteredNonEmptyChar = false;
	size_t strLen = str.length();

	for (int i = strLen - 1; i >= 0; --i) {
		if (!encounteredNonEmptyChar) {
			if (str[i] == ' ' || str[i] == '\t') {
				continue;
			}
			else {
				encounteredNonEmptyChar = true;
				outStr += str[i];
			}
		}
		else {
			outStr += str[i];
		}
	}

	return RevStr(outStr);
}

void Utils::WriteToFile(const std::string& path, const std::string& content) {
	std::ofstream file(path);

	if (!file.is_open()) {
		std::stringstream strStream;
		strStream << "Failed to open file for writing " << path << std::endl;
		throw strStream.str();
	}

	file << content;
	file.close();
}