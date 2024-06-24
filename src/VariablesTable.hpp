#pragma once

#include <iostream>
#include <unordered_map>
#include <cassert>

namespace VariablesTable {
	std::unordered_map<std::string, int> variablesTable;
	const int startingVariablesAddress = 16;
	int lastVariableAddress = startingVariablesAddress;

	int AddVariable(std::string variableName) {
		variablesTable.insert({ variableName, lastVariableAddress });
		return lastVariableAddress++;
	}

	bool ContainsVariable(std::string& variableName) {
		return variablesTable.find(variableName) != variablesTable.end();
	}

	int GetValue(const std::string& variableName) {
		assert(variablesTable.find(variableName) != variablesTable.end());

		return variablesTable[variableName];
	}
}