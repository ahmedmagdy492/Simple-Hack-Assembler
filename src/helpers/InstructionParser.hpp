#pragma once

#include "../include/Utils.h"

#include <sstream>
#include <bitset>

enum CinstructionFormat {
	DestCompJmp, // dest=comp;jmp
	CompJmp,     // comp;jmp
	ZeroJmp,     // 0;jmp
	DestComp     // dest=comp
};

class CompInstructions {
private:
	CompInstructions() {}
public:
	// Predefined Comps with a bit field = 0
	static const unsigned short ZERO_VALUE = 0b0000101010000000;
	static const unsigned short ONE_VALUE = 0b0000111111000000;
	static const unsigned short MINUS_ONE_VALUE = 0b0000111010000000;
	static const unsigned short D_VALUE = 0b0000001100000000;
	static const unsigned short A_VALUE = 0b0000110000000000;
	static const unsigned short NOT_D_VALUE = 0b0000001101000000;
	static const unsigned short NOT_A_VALUE = 0b0000110001000000;
	static const unsigned short MINUS_D_VALUE = 0b0000001111000000;
	static const unsigned short MINUS_A_VALUE = 0b0000110011000000;
	static const unsigned short D_PLUS_ONE = 0b0000011111000000;
	static const unsigned short A_PLUS_ONE = 0b0000110111000000;
	static const unsigned short D_MINUS_ONE = 0b0000001110000000;
	static const unsigned short A_MINUS_ONE = 0b0000110010000000;
	static const unsigned short D_PLUS_A = 0b0000000010000000;
	static const unsigned short D_MINUS_A = 0b0000010011000000;
	static const unsigned short A_MINUS_D = 0b0000000111000000;
	static const unsigned short D_AND_A = 0b0000000000000000;
	static const unsigned short D_OR_A = 0b0000010101000000;

	// Predefined Comps with a bit field = 1
	static const unsigned short M_VALUE = 0b0001110000000000;
	static const unsigned short NOT_M_VALUE = 0b0001110001000000;
	static const unsigned short MINUS_M_VALUE = 0b0001110011000000;
	static const unsigned short M_PLUS_ONE = 0b0001110111000000;
	static const unsigned short M_MINUS_ONE = 0b0001110010000000;
	static const unsigned short D_PLUS_M = 0b0001000010000000;
	static const unsigned short D_MINUS_M = 0b0001010011000000;
	static const unsigned short M_MINUS_D = 0b0001000111000000;
	static const unsigned short D_AND_M = 0b0001000000000000;
	static const unsigned short D_OR_M = 0b0001010101000000;
};

class DestInstructions {
private:
	DestInstructions() {}
public:
	// Predefined Destinations
	static const unsigned short MDest = 0b0000000000001000;
	static const unsigned short DDest = 0b0000000000010000;
	static const unsigned short ADest = 0b0000000000100000;
};

class JmpInstructions {
private:
	JmpInstructions() {}
public:
	// Predefined JMPs
	static const unsigned short JGT = 0b0000000000000001;
	static const unsigned short JEQ = 0b0000000000000010;
	static const unsigned short JGE = 0b0000000000000011;
	static const unsigned short JLT = 0b0000000000000100;
	static const unsigned short JNE = 0b0000000000000101;
	static const unsigned short JLE = 0b0000000000000110;
	static const unsigned short JMP = 0b0000000000000111;
};

class InstructionParser {
private:
	/// <summary>
	/// A C-Instruction can be valid only in one of the following formats:
	///	 - dest=comp;jmp
	///  - comp;jmp
	///  - 0;jmp
	///  - dest=comp
	/// </summary>
	/// <param name="cInst"></param>
	/// <returns></returns>
	CinstructionFormat DetermineCInstFormat(std::string& cInst) {
		if (cInst.find("=") != std::string::npos && cInst.find(";") != std::string::npos) {
			return CinstructionFormat::DestCompJmp;
		}
		else if (cInst.find(";") != std::string::npos && cInst.find("=") == std::string::npos) {
			if (cInst[0] != '0') {
				return CinstructionFormat::CompJmp;
			}
			else {
				return CinstructionFormat::ZeroJmp;
			}
		}
		else if (cInst.find("=") != std::string::npos && cInst.find(";") == std::string::npos) {
			return CinstructionFormat::DestComp;
		}
		else {
			std::stringstream msg;
			msg << "Invalid c instruction format " << cInst << std::endl;
			throw msg.str();
		}
	}

	unsigned short ValidateAndParseDestPart(const std::string& destPart) {
		unsigned short result = 0b1110000000000000;

		if (destPart == "0" || destPart == "null") {
			return result;
		}
		else if (destPart == "M") {
			return (result | DestInstructions::MDest);
		}
		else if (destPart == "D") {
			return (result | DestInstructions::DDest);
		}
		else if (destPart == "MD") {
			return (result | DestInstructions::MDest | DestInstructions::DDest);
		}
		else if (destPart == "A") {
			return (result | DestInstructions::ADest);
		}
		else if (destPart == "AM") {
			return (result | DestInstructions::ADest | DestInstructions::MDest);
		}
		else if (destPart == "AD") {
			return (result | DestInstructions::ADest | DestInstructions::DDest);
		}
		else if (destPart == "AMD") {
			return (result | DestInstructions::ADest | DestInstructions::MDest | DestInstructions::DDest);
		}
		else {
			std::stringstream msg;
			msg << "Unknwon destination part in c instruction " << destPart << std::endl;
			throw msg.str();
		}
	}

	unsigned short ValidateAndParseJMPPart(std::string& jmpPart) {
		unsigned short result = 0b1110000000000000;

		if (jmpPart == "0" || jmpPart == "null") {
			return result;
		}
		else if (jmpPart == "JGT") {
			return (result | JmpInstructions::JGT);
		}
		else if (jmpPart == "JEQ") {
			return (result | JmpInstructions::JEQ);
		}
		else if (jmpPart == "JGE") {
			return (result | JmpInstructions::JGE);
		}
		else if (jmpPart == "JLT") {
			return (result | JmpInstructions::JLT);
		}
		else if (jmpPart == "JNE") {
			return (result | JmpInstructions::JNE);
		}
		else if (jmpPart == "JLE") {
			return (result | JmpInstructions::JLE);
		}
		else if (jmpPart == "JMP") {
			return (result | JmpInstructions::JMP);
		}
		else {
			std::stringstream msg;
			msg << "Unknwon JMP part in c instruction " << jmpPart << std::endl;
			throw msg.str();
		}
	}

	unsigned short ValidateAndParseCompPart(std::string& compPart) {
		unsigned short result = 0b1110000000000000;

		if (compPart == "null") {
			return result;
		}
		else if (compPart == "0") {
			return (result | CompInstructions::ZERO_VALUE);
		}
		else if (compPart == "1") {
			return (result | CompInstructions::ONE_VALUE);
		}
		else if (compPart == "-1") {
			return (result | CompInstructions::MINUS_ONE_VALUE);
		}
		else if (compPart == "D") {
			return (result | CompInstructions::D_VALUE);
		}
		else if (compPart == "A") {
			return (result | CompInstructions::A_VALUE);
		}
		else if (compPart == "!D") {
			return (result | CompInstructions::NOT_D_VALUE);
		}
		else if (compPart == "!A") {
			return (result | CompInstructions::NOT_A_VALUE);
		}
		else if (compPart == "-D") {
			return (result | CompInstructions::MINUS_D_VALUE);
		}
		else if (compPart == "-A") {
			return (result | CompInstructions::MINUS_A_VALUE);
		}
		else if (compPart == "D+1") {
			return (result | CompInstructions::D_PLUS_ONE);
		}
		else if (compPart == "A+1") {
			return (result | CompInstructions::A_PLUS_ONE);
		}
		else if (compPart == "D-1") {
			return (result | CompInstructions::D_MINUS_ONE);
		}
		else if (compPart == "A-1") {
			return (result | CompInstructions::A_MINUS_ONE);
		}
		else if (compPart == "D+A") {
			return (result | CompInstructions::D_PLUS_A);
		}
		else if (compPart == "D-A") {
			return (result | CompInstructions::D_MINUS_A);
		}
		else if (compPart == "A-D") {
			return (result | CompInstructions::A_MINUS_D);
		}
		else if (compPart == "D&A") {
			return (result | CompInstructions::D_AND_A);
		}
		else if (compPart == "D|A") {
			return (result | CompInstructions::D_OR_A);
		}
		else if (compPart == "M") {
			return (result | CompInstructions::M_VALUE);
		}
		else if (compPart == "!M") {
			return (result | CompInstructions::NOT_M_VALUE);
		}
		else if (compPart == "-M") {
			return (result | CompInstructions::MINUS_M_VALUE);
		}
		else if (compPart == "M+1") {
			return (result | CompInstructions::M_PLUS_ONE);
		}
		else if (compPart == "M-1") {
			return (result | CompInstructions::M_MINUS_ONE);
		}
		else if (compPart == "D+M") {
			return (result | CompInstructions::D_PLUS_M);
		}
		else if (compPart == "D-M") {
			return (result | CompInstructions::D_MINUS_M);
		}
		else if (compPart == "M-D") {
			return (result | CompInstructions::M_MINUS_D);
		}
		else if (compPart == "D&M") {
			return (result | CompInstructions::D_AND_M);
		}
		else if (compPart == "D|M") {
			return (result | CompInstructions::D_OR_M);
		}
		else {
			std::stringstream msg;
			msg << "Unknwon Computation part in c instruction " << compPart << std::endl;
			throw msg.str();
		}
	}

	unsigned short CreateDestPart(std::string& cInst) {
		Utils utils;
		std::vector<std::string>* instParts = utils.Split(cInst, '=');

		if ((*instParts).size() != 2) {
			delete instParts;
			std::stringstream msg;
			msg << "Incompelete c instruction " << cInst << std::endl;
			throw msg.str();
		}
		
		try {
			std::string destPart = (*instParts)[0];
			unsigned short binaryOut = ValidateAndParseDestPart(destPart);
			delete instParts;
			return binaryOut;
		}
		catch (std::string msg) {
			delete instParts;
			throw msg;
		}
	}

	unsigned short CreateJmpPart(std::string& cInst) {
		Utils utils;
		std::vector<std::string>* instParts = utils.Split(cInst, ';');

		if ((*instParts).size() != 2) {
			delete instParts;
			std::stringstream msg;
			msg << "Incompelete c instruction " << cInst << std::endl;
			throw msg.str();
		}

		try {
			std::string jmpPart = (*instParts)[1];
			unsigned short binaryOut = ValidateAndParseJMPPart(jmpPart);
			delete instParts;
			return binaryOut;
		}
		catch (std::string msg) {
			delete instParts;
			throw msg;
		}
	}

	unsigned short CreateCompPart(std::string& cInst, CinstructionFormat cInstFormat) {
		char deliChar = ';';
		int compIndex = 0;
		Utils utils;

		if (cInstFormat == CinstructionFormat::CompJmp || cInstFormat == CinstructionFormat::ZeroJmp) {
			deliChar = ';';
			compIndex = 0;
		}
		else if (cInstFormat == CinstructionFormat::DestComp || cInstFormat == CinstructionFormat::DestCompJmp) {
			deliChar = '=';
			compIndex = 1;
		}

		std::vector<std::string>* instParts = utils.Split(cInst, deliChar);

		if ((*instParts).size() != 2) {
			delete instParts;
			std::stringstream msg;
			msg << "Incompelete c instruction " << cInst << std::endl;
			throw msg.str();
		}

		try {
			std::string compPart = (*instParts)[compIndex];
			unsigned short binaryOut = ValidateAndParseCompPart(compPart);
			delete instParts;
			return binaryOut;
		}
		catch (std::string msg) {
			delete instParts;
			throw msg;
		}
	}

	std::string AssembleCinstruction(std::string& cInst) {
		CinstructionFormat cinstructionFormat = DetermineCInstFormat(cInst);
		std::string finalOutput = "";
		
		switch (cinstructionFormat)
		{
		case CinstructionFormat::DestCompJmp: {
			unsigned short destResult = CreateDestPart(cInst);
			unsigned short jmpResult = CreateJmpPart(cInst);
			unsigned short compResult = CreateCompPart(cInst, cinstructionFormat);
			unsigned short finalResult = destResult | compResult | jmpResult;
			return std::bitset<16>(finalResult).to_string();
		}
		case CinstructionFormat::CompJmp:
		case CinstructionFormat::ZeroJmp: {
			unsigned short jmpResult = CreateJmpPart(cInst);
			unsigned short compResult = CreateCompPart(cInst, cinstructionFormat);
			unsigned short finalResult = compResult | jmpResult;
			return std::bitset<16>(finalResult).to_string();
		}
		case CinstructionFormat::DestComp: {
			unsigned short destResult = CreateDestPart(cInst);
			unsigned short compResult = CreateCompPart(cInst, cinstructionFormat);
			unsigned short finalResult = compResult | destResult;
			return std::bitset<16>(finalResult).to_string();
		}
		}

		return finalOutput;
	}

public:
	std::string Parse(std::string& code) {
		Utils utils;

		std::vector<std::string>* lines = utils.Split(code, '\n');
		size_t linesCount = (*lines).size();
		std::stringstream outputCode;

		for (int i = 0; i < linesCount; ++i) {
			std::string line = (*lines)[i];
			short currentInstruction = 0;

			if (line[0] == '@') {
				// A-Instruction
				std::string instructionValue = line.substr(1);
				if (utils.IsStrContainsNumbersOnly(instructionValue)) {
					// constant value
					int value = std::stoi(instructionValue);
					outputCode << std::bitset<16>(currentInstruction | value) << '\n';
				}
				else {
					std::stringstream msg;
					msg << "Unresolved symbol for an A-Instruction " << instructionValue << " on line " << i << std::endl;
					throw msg.str();
				}
			}
			else {
				// C-Instruction
				std::string assembledCInst = AssembleCinstruction(line);
				outputCode << assembledCInst << '\n';
			}
		}

		delete lines;
		return outputCode.str();
	}
};