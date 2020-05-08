//
// Created by Jur de Vries on 30/04/2020.
//

#ifndef OSCRECORDER_TRACKSWINDOWUI_H
#define OSCRECORDER_TRACKSWINDOWUI_H

#include "TrackDrawerHelper.h"
#include "imgui.h"

class TracksWindowUI {
public:
    void draw();

private:
    TrackDrawerHelper drawerHelper;

    void drawRuler(ImDrawList *drawList, ImVec2 windowPos, float offsetTop, float lineLength);
};

#endif //OSCRECORDER_TRACKSWINDOWUI_H
