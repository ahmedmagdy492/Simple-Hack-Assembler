#pragma once

#include <iostream>
#include <unordered_map>
#include <cassert>

namespace SymbolsTable {
	std::unordered_map<std::string, int> symbolsTable;

	void AddSymbol(std::string key, int value) {
		symbolsTable.insert({ key, value });
	}

	bool ContainsSymbol(std::string& key) {
		return symbolsTable.find(key) != symbolsTable.end();
	}

	int GetValue(const std::string& key) {
		assert(symbolsTable.find(key) != symbolsTable.end());

		return symbolsTable[key];
	}
}