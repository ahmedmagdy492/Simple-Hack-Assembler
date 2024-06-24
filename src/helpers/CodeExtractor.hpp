#pragma once

#include "../include/Utils.h"

class CodeExtractor {

public:
	std::string Extract(std::string& code) {
		Utils utils;
		char delim = '\n';

		std::vector<std::string>* lines = utils.Split(code, delim);
		std::string codeWithoutCommentsAndEmptyLines;
		size_t size = (*lines).size();

		for (int i = 0; i < size; ++i) {
			std::string trimmedLine = utils.TrimEnd(utils.TrimString((*lines)[i]));
			if (trimmedLine.empty()) {
				continue;
			}
			else if (trimmedLine[0] == '/' && trimmedLine[1] == '/') {
				continue;
			}
			else {
				codeWithoutCommentsAndEmptyLines.append(trimmedLine);
				if (i < (size-1)) {
					codeWithoutCommentsAndEmptyLines.append("\n");
				}
			}
		}

		delete lines;

		return codeWithoutCommentsAndEmptyLines;
	}
};