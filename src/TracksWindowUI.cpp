//
// Created by Jur de Vries on 30/04/2020.
//

#include "TracksWindowUI.h"
#include "ofxImGui.h"
#include "timeline.h"
#include "ofLog.h"

void TracksWindowUI::draw(Timeline &timeline) {
    drawerHelper.setMaxTimeMillis(70*1000);
    drawerHelper.setPixelsPerSecond(60.f);
    drawerHelper.setCurrentTimeMillis(timeline.elapsedMillis());
    ImGui::SetNextWindowContentSize(ImVec2(drawerHelper.getContentSize(), 100.f));
    ImGui::Begin("Track window", NULL, ImGuiWindowFlags_HorizontalScrollbar);

    auto windowWidth = ImGui::GetWindowWidth();
    drawerHelper.setCurrentWindowWidth(static_cast<int>(windowWidth));
    if (playing && following) {
        ImGui::SetScrollX(drawerHelper.getScrollOffset());
    }
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    auto windowLeftTop = ImGui::GetWindowPos();
    auto windowBottomRight = windowLeftTop + ImGui::GetWindowSize();
    auto p = windowLeftTop - ImVec2(ImGui::GetScrollX(), 0.f);

    ImGuiIO& io = ImGui::GetIO();
    if (ImGui::IsMousePosValid()) {
        auto mousePos = io.MousePos;
        if (mouseIsInsideWindow(mousePos, windowLeftTop, windowBottomRight) && ImGui::IsMouseClicked(0))
        {
            auto mousePosInContent = mousePos - p;
            timeline.setCurrentMillis(drawerHelper.getMillisFromPixels(mousePosInContent.x));
        }
    }

    drawRuler(drawList, p, 20.f, 20.f);
    drawTracks(drawList, p);
    drawPlayHead(drawList, p);

    ImGui::End();
}

bool TracksWindowUI::mouseIsInsideWindow(const ImVec2 &mousePos, const ImVec2 &windowLeftTop, const glm::vec2 &windowBottomRight) const {
    return (mousePos.x > windowLeftTop.x && mousePos.y > windowLeftTop.y) &&
                    (mousePos.x < windowBottomRight.x && mousePos.y < windowBottomRight.y);
}

void TracksWindowUI::drawPlayHead(ImDrawList *drawList, const glm::vec2 &windowPos) const {
    drawList->AddLine(ImVec2(drawerHelper.getTimeMarkerPosition(), 0.f) + windowPos, ImVec2(drawerHelper.getTimeMarkerPosition(), 100.f) + windowPos, ImColor(255,255,255), 1.f);
}

void TracksWindowUI::drawTracks(ImDrawList *drawList, const glm::vec2 &windowPos) const {
    drawList->AddRectFilled(ImVec2(20.f, 60.f) + windowPos, ImVec2(1000.f, 60.f + 30.f) + windowPos, ImColor(255,0,0,100));
    drawList->AddRect(ImVec2(20.f, 60.f) + windowPos, ImVec2(1000.f, 60.f + 30.f) + windowPos, ImColor(255,0,0,255));
}

void TracksWindowUI::drawRuler(ImDrawList *drawList, ImVec2 windowPos, float offsetTop, float lineLength) {
    auto points = drawerHelper.getRulerData();
    auto color = ImColor(255, 255, 255);
    for (auto point : points) {
        if (point.hasText) {
            drawList->AddLine(ImVec2(point.x, offsetTop) + windowPos, ImVec2(point.x, offsetTop + lineLength) + windowPos, color, 2.f);
            drawList->AddText(NULL, 14.f, ImVec2(point.x - 17.f, offsetTop + lineLength + 4.f) + windowPos, color, point.text.c_str(), NULL);
        }
        else {
            drawList->AddLine(ImVec2(point.x, offsetTop) + windowPos, ImVec2(point.x, offsetTop + lineLength / 2) + windowPos, color, 2.f);
        }
    }
}
