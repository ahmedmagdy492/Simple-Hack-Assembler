#include <iostream>
#include <string>

#include "./helpers/LabelExtractor.hpp"
#include "./helpers/CodeExtractor.hpp"
#include "./helpers/SymbolsResolver.hpp"
#include "./helpers/InstructionParser.hpp"

extern "C" {
	#include <raylib.h>

	#define RAYGUI_IMPLEMENTATION
	#include <raygui.h>
	#include <style_terminal.h>
}

void ExportToHackFile(const std::string& content) {
	Utils utils;
	std::string outputFile = "out.hack";
	utils.WriteToFile(outputFile, content);
}

std::string AssembleCode(std::string& content) {
	try {
		CodeExtractor codeExtractor;
		std::string codeExtractorOutput = codeExtractor.Extract(content);

		LabelExtractor lblExtractor;
		std::string lblExtractorOutput = lblExtractor.Extract(codeExtractorOutput);

		SymbolsResolver symbolsResolver;
		std::string symbolsResolverOutput = symbolsResolver.Resolve(lblExtractorOutput);

		InstructionParser instructionParser;
		return instructionParser.Parse(symbolsResolverOutput);
	}
	catch (std::string msg) {
		std::cout << "Error occured while trying to parse the file: " << msg << std::endl;
	}
	return "";
}

char** ConvertVectorToArray(std::vector<std::string>* vec) {
	size_t len = (*vec).size();
	char** arr = new char* [len];
	
	for (int i = 0; i < len; ++i) {
		std::string line = (*vec)[i];
		size_t lineLen = line.length();
		arr[i] = new char[lineLen+1];
		memset(arr[i], 0, lineLen+1);
		memcpy(arr[i], line.c_str(), lineLen);
	}

	return arr;
}

void DeallocMem(char** mem, size_t len) {
	for (int i = 0; i < len; ++i) {
		if (mem[i] != nullptr) {
			delete mem[i];
		}
	}

	delete mem;
}


int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <path-to-assembly-file.asm>" << std::endl;
		return 1;
	}

	const int screenWidth = 1280;
	const int screenHeight = 800;

	std::string filePath(argv[1]);

	InitWindow(screenWidth, screenHeight, "Simple Hack Assembler");
	SetTargetFPS(60);

	GuiLoadStyleTerminal();

	Font font = LoadFontEx("resources/Roboto-Bold.ttf", 48, 0, 250);

	GuiSetFont(font);

	char** items1 = nullptr;
	int itemCount1 = -1;
	int listViewActive1 = -1, scrollIndex1 = 0, focus1 = 0;

	char** items2 = nullptr;
	int itemCount2 = -1;
	int listViewActive2 = -1, scrollIndex2 = 0, focus2 = 0;

	bool isCodeLoaded = false, isCodeAssembled = false;
	std::string content;
	std::string assembledCode;

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		if (GuiButton({ 24, 24, 120, 30 }, "Load File")) {
			Utils utils;
			content = utils.ReadFile(filePath);
			isCodeLoaded = true;
			isCodeAssembled = false;

			std::vector<std::string>* lines = utils.Split(content, '\n');
			if (items1 != nullptr) {
				SymbolsTable::ClearAllSymbols();
				VariablesTable::ClearAllVariables();
				DeallocMem(items1, (*lines).size());
			}

			items1 = ConvertVectorToArray(lines);
			itemCount1 = (*lines).size();

			delete lines;
		}

		if (GuiButton({ 120 + 44, 24, 170, 30 }, "Export As a Hack File")) {
			if (isCodeLoaded && isCodeAssembled) {
				ExportToHackFile(assembledCode);
			}
		}

		GuiListViewEx({ 50, 90, (screenWidth / 2) - 100, screenHeight - 120 }, (const char**)items1, itemCount1, &scrollIndex1, &listViewActive1, &focus1);

		if (GuiButton({ (screenWidth / 2) - 20, screenHeight / 2, 50, 30 }, ">>")) {
			// assembling code
			if (isCodeLoaded) {
				SymbolsTable::ClearAllSymbols();
				VariablesTable::ClearAllVariables();
				assembledCode = AssembleCode(content);
				isCodeAssembled = true;
				Utils utils;
				
				std::vector<std::string>* lines = utils.Split(assembledCode, '\n');
				if (items2 != nullptr) {
					DeallocMem(items2, (*lines).size());
				}

				items2 = ConvertVectorToArray(lines);
				itemCount2 = (*lines).size();

				delete lines;
			}
		}

		GuiListViewEx({ (screenWidth / 2) + 50, 90, (screenWidth / 2) - 100, screenHeight - 120 }, (const char**)items2, itemCount2, &scrollIndex2, &listViewActive2, &focus2);

		EndDrawing();
	}

	if (items1 != nullptr) {
		DeallocMem(items1, itemCount1);
	}

	if (items2 != nullptr) {
		DeallocMem(items2, itemCount2);
	}

	UnloadFont(font);

	CloseWindow();
}