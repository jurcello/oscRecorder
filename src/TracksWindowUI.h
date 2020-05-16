//
// Created by Jur de Vries on 30/04/2020.
//

#ifndef OSCRECORDER_TRACKSWINDOWUI_H
#define OSCRECORDER_TRACKSWINDOWUI_H

#include "TrackDrawerHelper.h"
#include "imgui.h"
#include "timeline.h"
#include "TrackChannel.h"

class TracksWindowUI {
public:
    void draw(Timeline &timeline, TrackChannel channel);
    bool playing;
    bool following = true;

private:
    TrackDrawerHelper drawerHelper;
    void drawRuler(ImDrawList *drawList, ImVec2 windowPos, float offsetTop, float lineLength);
    void drawTracks(ImDrawList *drawList, const glm::vec2 &windowPos, TrackChannel channel) const;
    void drawPlayHead(ImDrawList *drawList, const glm::vec2 &windowPos) const;

    bool mouseIsInsideWindow(const ImVec2 &mousePos, const ImVec2 &windowLeftTop, const glm::vec2 &windowBottomRight) const;
};

#endif //OSCRECORDER_TRACKSWINDOWUI_H
