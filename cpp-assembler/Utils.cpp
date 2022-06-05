#include "Utils.h"

bool Utils::isValidIdentifier(std::string identifier) {
    // If first character is invalid
    if (!((identifier[0] >= 'a' && identifier[0] <= 'z')
        || (identifier[0] >= 'A' && identifier[0] <= 'Z')
        || identifier[0] == '_'))
        return false;

    // Traverse the string for the rest of the characters
    for (int i = 1; i < identifier.length(); i++) {
        if (!((identifier[i] >= 'a' && identifier[i] <= 'z')
            || (identifier[i] >= 'A' && identifier[i] <= 'Z')
            || (identifier[i] >= '0' && identifier[i] <= '9')
            || identifier[i] == '_'))
            return false;
    }

    return true;
}

bool Utils::isNumber(std::string numberString)
{
    return !numberString.empty() && std::find_if(numberString.begin(),
        numberString.end(), [](unsigned char c) { return !std::isdigit(c); }) == numberString.end();
}