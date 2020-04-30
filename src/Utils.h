//
// Created by Jur de Vries on 16/04/2020.
//

#ifndef OSCRECORDER_UTILS_H
#define OSCRECORDER_UTILS_H

#include "ofxOsc.h"


class Utils {
public:
    static std::string oscMessageToString(ofxOscMessage message);
};


#endif //OSCRECORDER_UTILS_H
