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

int main(int argc, char* argv[]) {
	std::string filePath = "D:\\Books\\Malware Analysis\\Reverse Engineering\\Computer Arch\\nand2tetris\\nand2tetris\\projects\\6\\max\\max.asm";

	const int screenWidth = 1024;
	const int screenHeight = 768;

	InitWindow(screenWidth, screenHeight, "Simple Hack Assembler");
	SetTargetFPS(60);

	GuiLoadStyleTerminal();

	const char* items[] = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "Item 6", "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" , "Item 6" };
	int itemCount1 = sizeof(items) / sizeof(items[0]);
	int listViewActive1 = -1, scrollIndex1 = 0, focus1 = 0;

	int itemCount2 = sizeof(items) / sizeof(items[0]);
	int listViewActive2 = -1, scrollIndex2 = 0, focus2 = 0;

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		if (GuiButton({ 24, 24, 120, 30 }, "Load File")) {
			Utils utils;
			std::string content = utils.ReadFile(filePath);

			std::string assembledCode = AssembleCode(content);
		}

		if (GuiButton({ 120+44, 24, 170, 30 }, "Export As a Hack File")) {
			//TODO ExportToHackFile();
		}

		GuiListViewEx({ 50, 90, (screenWidth / 2) - 100, screenHeight - 120 }, items, itemCount1, &scrollIndex1, &listViewActive1, &focus1);

		if (GuiButton({ (screenWidth / 2) -20, screenHeight / 2, 50, 30 }, ">>")) {

		}

		GuiListViewEx({ (screenWidth / 2)+50, 90, (screenWidth / 2) - 100, screenHeight - 120 }, items, itemCount2, &scrollIndex2, &listViewActive2, &focus2);

		EndDrawing();
	}

	CloseWindow();
}