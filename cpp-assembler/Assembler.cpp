#include <fstream>
#include <string>
#include <algorithm>
#include "Assembler.h"
#include <iostream>
#include <vector>

Assembler::Assembler() {
this->instructionsMap = {
        {"mov",byte("00000001")},

        {"orr",byte("00000000")},
        {"nnd",byte("00000001")},
        {"nor",byte("00000010")},
        {"and",byte("00000011")},
        {"add",byte("00000100")},
        {"sub",byte("00000101")},

        {"eql",byte("00100000")},
        {"neq",byte("00100001")},
        {"les",byte("00100010")},
        {"loe",byte("00100011")},
        {"mor",byte("00100100")},
        {"moe",byte("00100101")},
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


        //Remove spaces
        //content.erase(remove_if(content.begin(), content.end(), isspace), content.end());


        // To lower case
        //std::transform(content.begin(), content.end(), content.begin(), ::tolower);


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
        else if(isInstruction) {
            byte operation, argument1, argument2, resultAdress;
                std::cout << instruction << std::endl;
                std::cout << this->instructionsMap[instruction] << std::endl;

                operation = this->instructionsMap[instruction];
            //instructionIndex++
        }
        else {
            throw std::invalid_argument("Syntax error: unexpected keyword on line: " + std::to_string(lineIndex));
        }
    }

    configFile.close();


    /*std::fstream file("program.bin", std::ios_base::out | std::ios_base::binary);
    if (!file.is_open())
    {
        std::cout << "Unable to open the file\n";
        return;
    }
    byte a("11110000");
    file.put(a.to_ulong());
    file.close();*/

}