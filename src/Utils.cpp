//
// Created by Jur de Vries on 16/04/2020.
//

#include "Utils.h"

std::string Utils::oscMessageToString(ofxOscMessage message) {
    std::stringstream output;
    output << message;
    return output.str();
}
