#include <iostream>
#include <string>

#include "./helpers/LabelExtractor.hpp"
#include "./helpers/CodeExtractor.hpp"
#include "./helpers/SymbolsResolver.hpp"
#include "./helpers/InstructionParser.hpp"

#define DEBUG

int main(int argc, char* argv[]) {

	#ifndef DEBUG
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " <input_file_path.asm>" << std::endl;
		return 1;
	}
	std::string filePath = argv[1];
	#else
	std::string filePath = "D:\\Books\\Malware Analysis\\Reverse Engineering\\Computer Arch\\nand2tetris\\nand2tetris\\projects\\6\\max\\max.asm";
	#endif
	
	try {
		Utils utils;
		std::string content = utils.ReadFile(filePath);

		CodeExtractor codeExtractor;
		std::string codeExtractorOutput = codeExtractor.Extract(content);

		LabelExtractor lblExtractor;
		std::string lblExtractorOutput = lblExtractor.Extract(codeExtractorOutput);

		SymbolsResolver symbolsResolver;
		std::string symbolsResolverOutput = symbolsResolver.Resolve(lblExtractorOutput);

		InstructionParser instructionParser;
		std::string instructionParserOutput = instructionParser.Parse(symbolsResolverOutput);

		std::cout << instructionParserOutput << std::endl;

		std::string outputFile = "out.hack";
		utils.WriteToFile(outputFile, instructionParserOutput);
	}
	catch (std::string msg) {
		std::cout << "Error occured while trying to parse the file: " << msg << std::endl;
		return 1;
	}
}