#include <fstream>
#include <string>
#include <algorithm>
#include "Assembler.h"
#include <iostream>
#include <vector>

Assembler::Assembler() {
this->instructionsMap = {
        {"mov",byte("00000011")},

        {"add",byte("00000000")},
        {"sub",byte("00000001")},
        {"and",byte("00000010")},
        {"orr",byte("00000011")},
        {"not",byte("00000100")},
        {"xor",byte("00000101")},

        {"eql",byte("00100000")},
        {"neq",byte("00100001")},
        {"les",byte("00100010")},
        {"loe",byte("00100011")},
        {"mor",byte("00100100")},
        {"moe",byte("00100101")},
};

this->registersMap = {
        {"input",byte("00000000")},
        {"output",byte("00000001")},

        {"r0",byte("00000000")}, {"register0",byte("00000000")}, {"reg0",byte("00000000")},
        {"r1",byte("00000001")}, {"register1",byte("00000001")}, {"reg1",byte("00000001")},
        {"r2",byte("00000010")}, {"register2",byte("00000010")}, {"reg2",byte("00000010")},
        {"r3",byte("00000011")}, {"register3",byte("00000011")}, {"reg3",byte("00000011")},
        {"r4",byte("00000100")}, {"register4",byte("00000100")}, {"reg4",byte("00000100")},
        {"r5",byte("00000101")}, {"register5",byte("00000101")}, {"reg5",byte("00000101")},
        {"r6",byte("00000110")}, {"register6",byte("00000110")}, {"reg6",byte("00000110")},
        {"r7",byte("00000111")}, {"register7",byte("00000111")}, {"reg7",byte("00000111")},
        {"r8",byte("00001000")}, {"register8",byte("00001000")}, {"reg8",byte("00001000")},
        {"r9",byte("00001001")}, {"register9",byte("00001001")}, {"reg9",byte("00001001")},
        {"r10",byte("00001010")}, {"register10",byte("00001010")}, {"reg10",byte("00001010")},
        {"r11",byte("00001011")}, {"register11",byte("00001011")}, {"reg11",byte("00001011")},
        {"r12",byte("00001100")}, {"register12",byte("00001100")}, {"reg12",byte("00001100")},
        {"r13",byte("00001101")}, {"register13",byte("00001101")}, {"reg13",byte("00001101")},
        {"r14",byte("00001110")}, {"register14",byte("00001110")}, {"reg14",byte("00001110")},
};
}


enum instruct{mov, add, orr, sub};

void Assembler::run(std::string fileName) {
    int lineIndex = 0;
    int instructionIndex = 0;
    std::string content;
    std::ifstream configFile;
    std::pair<std::string, char> key, value;
    configFile.open(fileName);
    int n = 0;

    // Reading file line by line
    while (getline(configFile, content)) {
        lineIndex++;
        //Ignore if line is empty or comment
        bool isLineEmpty = content.length() == 0;
        bool isComment = (content[0] == '/' && content[1] == '/') || content[0] == '#';
        if (isLineEmpty || isComment) {
            continue;
        }

        // Remove spaces from the start
        while (content[0] == ' ') {
            content.erase(0, 1);
        }
        std::cout << content << std::endl;

        std::string instruction = content.substr(0, 3);
        std::transform(instruction.begin(), instruction.end(), instruction.begin(), ::tolower);
        std::string label = content.substr(0, 5);
        std::transform(label.begin(), label.end(), label.begin(), ::tolower);
        bool isInstruction = this->instructionsMap.count(instruction);
        bool isLabel = label == "label";

        if (isLabel) {
            // Remove 'label' word and spaces
            content.erase(0, 5);
            while (content[0] == ' ') {
                content.erase(0, 1);
            }
            while (content[content.size()-1] == ' ') {
                content.pop_back();
            }

            if (Utils::isValidIdentifier(content)) {
                bool isLabelExist = this->labelsMap.count(content);
                
                if (!isLabelExist) {
                    this->labelsMap[content] = instructionIndex;
                }
                else {
                    throw std::invalid_argument("Label '"+content + "' is already exists.");
                }
            }
            else {
                throw std::invalid_argument("'"+content + "' is not a identifier.");
            }
            std::cout << content << std::endl;
        }
        else if (isInstruction) {
            byte operation, argument1, argument2, resultAddress;
            std::string delimiter, argument1Content, argument2Content, resultAddressContent;
            bool isRegister;
            std::cout << instruction << std::endl;
            std::cout << this->instructionsMap[instruction] << std::endl;
            operation = this->instructionsMap[instruction];

            if (instruction != "jmp") {
                ///// Argument 1

                // Remove instruction and spaces
                content.erase(0, 3);
                while (content[0] == ' ') {
                    content.erase(0, 1);
                };

                delimiter = ',';
                int delimiterIndex = content.find(delimiter);
                if (delimiterIndex != -1) {
                    argument1Content = content.substr(0, delimiterIndex);
                    std::cout << argument1Content << std::endl;
                    content.erase(0, delimiterIndex + 1);
                    std::cout << content << std::endl;
                }
                else {
                    throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
                }

                // Remove spaces from end
                while (argument1Content[argument1Content.size() - 1] == ' ') {
                    argument1Content.pop_back();
                }

                //To lower case
                std::transform(argument1Content.begin(), argument1Content.end(), argument1Content.begin(), ::tolower);

                isRegister = this->registersMap.count(argument1Content);
                if (isRegister) {
                    argument1 = this->registersMap[argument1Content];
                }
                else if (Utils::isNumber(argument1Content)) {
                    argument1 = stoi(argument1Content);
                    // Change byte which indicates whether argument1 is immediate or not
                    operation[7] = 1;
                }
                else {
                    throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
                }


                ///// Argument 2
                if (instruction != "mov" && instruction != "not")
                {
                    while (content[0] == ' ') {
                        content.erase(0, 1);
                    };

                    delimiter = ','; // when MOV
                    delimiterIndex = content.find(delimiter);
                    if (delimiterIndex != -1) {
                        argument2Content = content.substr(0, delimiterIndex);
                        std::cout << argument2Content << std::endl;
                        content.erase(0, delimiterIndex + 1);
                        std::cout << content << std::endl;
                    }
                    else {
                        throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
                    }

                    // Remove spaces from end
                    while (argument2Content[argument2Content.size() - 1] == ' ') {
                        argument2Content.pop_back();
                    }

                    //To lower case
                    std::transform(argument2Content.begin(), argument2Content.end(), argument2Content.begin(), ::tolower);

                    isRegister = this->registersMap.count(argument2Content);
                    if (isRegister) {
                        argument2 = this->registersMap[argument2Content];
                    }
                    else if (Utils::isNumber(argument2Content)) {
                        argument2 = stoi(argument2Content);
                        // Change byte which indicates whether argument2 is immediate or not
                        operation[6] = 1;
                    }
                    else {
                        throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
                    }
                }
                else {
                    argument2 = 0;
                    operation[6] = 1;
                }

            }
            else {
                argument1 = 0;
                argument2 = 0;
            }

                ////// Result Address
                while (content[0] == ' ') {
                    content.erase(0, 1);
                };
                while (content.size() && content[content.size() - 1] == ' ') {
                    content.pop_back();
                }
                resultAddressContent = content;

                //To lower case
                std::transform(resultAddressContent.begin(), resultAddressContent.end(), resultAddressContent.begin(), ::tolower);

                if (operation[5]) { // On conditional mode the resultAddress must be a label
                    bool isLabelValid = this->labelsMap.count(resultAddressContent);

                    if (isLabelValid) {
                        resultAddress = this->labelsMap[resultAddressContent];
                    }
                    else {
                        throw std::invalid_argument("Label '" + resultAddressContent + "' can not be found!");
                    }
                }
                else { // On ALU mode the resultAddress must be a register
                    isRegister = this->registersMap.count(resultAddressContent);

                    if (isRegister) {
                        resultAddress = this->registersMap[resultAddressContent];
                    }
                    else {
                        throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
                    }
                }

            std::cout << operation << " " << argument1 << " " << argument2 << " " << resultAddress << std::endl;
            this->programBuffer.push_back(operation);
            this->programBuffer.push_back(argument1);
            this->programBuffer.push_back(argument2);
            this->programBuffer.push_back(resultAddress);
            instructionIndex+=4;
        }
        else {
            throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
        }
    }

    configFile.close();


    std::fstream file("program.bin", std::ios_base::out | std::ios_base::binary);
    if (!file.is_open())
    {
        std::cout << "Unable to open the file\n";
        return;
    }

    for (int i = 0; i < this->programBuffer.size();i++) {
        file.put(this->programBuffer[i].to_ulong());
    }
    
    file.close();

}