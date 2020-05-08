//
// Created by Jur de Vries on 30/04/2020.
//

#include "TracksWindowUI.h"
#include "ofxImGui.h"

void TracksWindowUI::draw() {
    drawerHelper.setMaxTimeMillis(70*1000);
    drawerHelper.setPixelsPerSecond(20.f);
    ImGui::SetNextWindowContentSize(ImVec2(drawerHelper.getContentSize(), 100.f));
    ImGui::Begin("Track window", NULL, ImGuiWindowFlags_HorizontalScrollbar);
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    auto p = ImGui::GetWindowPos() - ImVec2(ImGui::GetScrollX(), 0.f);
    drawRuler(drawList, p, 20.f, 20.f);

    drawList->AddRectFilled(ImVec2(20.f, 60.f) + p, ImVec2(1000.f, 60.f + 30.f) + p, ImColor(255,0,0,100));
    drawList->AddRect(ImVec2(20.f, 60.f) + p, ImVec2(1000.f, 60.f + 30.f) + p, ImColor(255,0,0,255));
    ImGui::End();
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
