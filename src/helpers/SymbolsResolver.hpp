#pragma once

#include <sstream>

#include "../include/Utils.h"
#include "../SymbolsTable.hpp"
#include "../VariablesTable.hpp"

class SymbolsResolver {
public:
	
	std::string Resolve(std::string& code) {
		Utils utils;
		std::vector<std::string> *lines = utils.Split(code, '\n');
		size_t linesLength = (*lines).size();
		std::string outputCode;

		for (int i = 0; i < linesLength; ++i) {
			std::string line = (*lines)[i];
			if (line[0] == '@') {
				std::string symbolName = line.substr(1);

				if (SymbolsTable::ContainsSymbol(symbolName)) {
					// resolving labels to addresses
					int address = SymbolsTable::GetValue(symbolName);
					std::stringstream strStream;
					strStream << "@" << address << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "SP") {
					std::stringstream strStream;
					strStream << "@0" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "LCL") {
					std::stringstream strStream;
					strStream << "@1" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "ARG") {
					std::stringstream strStream;
					strStream << "@2" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "THIS") {
					std::stringstream strStream;
					strStream << "@3" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "THAT") {
					std::stringstream strStream;
					strStream << "@4" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "SCREEN") {
					std::stringstream strStream;
					strStream << "@16384" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName == "KBD") {
					std::stringstream strStream;
					strStream << "@24576" << "\n";
					outputCode.append(strStream.str());
				}
				else if (symbolName[0] == 'R') {
					// resolving predefined ram aliases
					int ramNo = std::stoi(symbolName.substr(1));
					if (ramNo < 0 || ramNo > 15) {
						std::stringstream strStream;
						strStream << "Invalid ram alias R" << ramNo << " on line " << i << std::endl;
						throw strStream.str();
					}

					std::stringstream strStream;
					strStream << "@" << ramNo << "\n";
					outputCode.append(strStream.str());
				}
				else if (utils.IsStrContainsNumbersOnly(symbolName)) {
					// the symbol is a constant value
					std::stringstream strStream;
					strStream << "@" << symbolName << "\n";
					outputCode.append(strStream.str());
				}
				else {
					// trying to resolve variables to addresses
					if (!isalpha(symbolName[0])) {
						std::stringstream strStream;
						strStream << "Variables should start with a letter error on line " << i << std::endl;
						throw strStream.str();
					}
					
					if (!utils.IsStringAlphNumeric(symbolName)) {
						std::stringstream strStream;
						strStream << "Variables should contain only letters or numbers on line " << i << std::endl;
						throw strStream.str();
					}

					int varAddress;
					if (!VariablesTable::ContainsVariable(symbolName)) {
						varAddress = VariablesTable::AddVariable(symbolName);
					}
					else {
					 	varAddress = VariablesTable::GetValue(symbolName);
					}

					std::stringstream strStream;
					strStream << "@" << varAddress << "\n";
					outputCode.append(strStream.str());
				}
			}
			else {
				if (i < (linesLength - 1)) {
					outputCode.append(line);
					outputCode.append("\n");
				}
				else {
					outputCode.append(line);
				}
			}
		}

		delete lines;
		return outputCode;
	}
};