#pragma once

#include "../include/Utils.h"
#include "../SymbolsTable.hpp"

#include <sstream>


class LabelExtractor {

private:
	std::string ExtractLabelName(std::string& line) {
		std::string outStr;

		for (auto& c : line) {
			if (c != ':') {
				outStr += c;
			}
			else {
				break;
			}
		}

		return outStr;
	}

public:
	std::string Extract(std::string& code) {
		Utils utils;
		std::vector<std::string>* lines = utils.Split(code, '\n');
		size_t linesLength = (*lines).size();
		std::string outputCode;
		size_t linesAppended = 0;

		for (int i = 0; i < linesLength; ++i) {
			std::string line = (*lines)[i];
			if (line[0] == '(') {
				if (StringEndsWith(line, ')')) {
					std::string labelName = line.substr(1, line.length() - 2);
					if (SymbolsTable::ContainsSymbol(labelName)) {
						std::stringstream strStream;
						strStream << "Redefination of symbol " << labelName << " on line " << i << std::endl;
						throw strStream.str();
					}
					else {
						SymbolsTable::AddSymbol(labelName, linesAppended);
					}
				}
				else {
					std::stringstream strStream;
					strStream << "Missing closing paranthasis on line " << i << std::endl;
					throw strStream.str();
				}
			}
			else {
				if (i < (linesLength-1)) {
					outputCode.append(line);
					outputCode.append("\n");
				}
				else {
					outputCode.append(line);
				}
				++linesAppended;
			}
		}

		delete lines;
		return outputCode;
	}
};