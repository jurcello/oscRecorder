//
// Created by Jur de Vries on 30/04/2020.
//

#ifndef OSCRECORDER_RULERDATA_H
#define OSCRECORDER_RULERDATA_H


#include <string>

struct RulerData {
    RulerData(int pixels, std::string text);

    int x;
    std::string text;
};


#endif //OSCRECORDER_RULERDATA_H
