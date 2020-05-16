//
// Created by Jur de Vries on 30/04/2020.
//

#ifndef OSCRECORDER_TRACKSWINDOWUI_H
#define OSCRECORDER_TRACKSWINDOWUI_H

#include "TrackDrawerHelper.h"
#include "imgui.h"
#include "timeline.h"

class TracksWindowUI {
public:
    void draw(Timeline &timeline);
    bool playing;
    bool following = true;

private:
    TrackDrawerHelper drawerHelper;
    void drawRuler(ImDrawList *drawList, ImVec2 windowPos, float offsetTop, float lineLength);
    void drawTracks(ImDrawList *drawList, const glm::vec2 &windowPos) const;
    void drawPlayHead(ImDrawList *drawList, const glm::vec2 &windowPos) const;
};

#endif //OSCRECORDER_TRACKSWINDOWUI_H
