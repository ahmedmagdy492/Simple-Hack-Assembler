#pragma once

#include <iostream>
#include <vector>
#include <cctype>
#include <cmath>

inline bool StringEndsWith(const std::string& str, char c) {
	return str[str.length() - 1] == c;
}

class Utils {
public:
	std::vector<std::string>* Split(std::string& str, char delim) const;
	std::string ConvertVectorToString(const std::vector<std::string>& vec) const;
	std::string TrimString(const std::string& str) const;
	bool ContainsLettersOnly(const std::string& str, char exceptChar = '\0') const;
	bool IsStringUpperCase(const std::string& str) const;
	bool IsStringAlphNumeric(const std::string& str) const;
	std::string ReadFile(const std::string& path);
	bool IsStrContainsNumbersOnly(const std::string& str);
	std::string TrimEnd(const std::string& str);
	std::string& RevStr(std::string& str);
	void WriteToFile(const std::string& path, const std::string& content);
};