#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include "common.h"
#include "Utils.h"


class Assembler {
public:
	Assembler();
	void run(std::string input);

private:
	std::map<std::string, byte> instructionsMap;
	std::map<std::string, byte> registersMap;
	std::map<std::string, byte> labelsMap;
	std::vector<byte> programBuffer;

};
#endif // ASSEMBLER_H