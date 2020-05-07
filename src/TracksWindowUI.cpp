//
// Created by Jur de Vries on 30/04/2020.
//

#include "TracksWindowUI.h"
#include "ofxImGui.h"

void TracksWindowUI::draw() {
    ImGui::SetNextWindowContentSize(ImVec2(1200.f, 100.f));
    ImGui::Begin("Track window", NULL, ImGuiWindowFlags_HorizontalScrollbar);
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    auto p = ImGui::GetWindowPos() - ImVec2(ImGui::GetScrollX(), 0.f);
    drawList->AddRectFilled(ImVec2(20.f, 20.f) + p, ImVec2(1000.f, 40.f) + p, ImColor(255,0,0,100));
    drawList->AddRect(ImVec2(20.f, 20.f) + p, ImVec2(1000.f, 40.f) + p, ImColor(255,0,0,255));
    ImGui::End();
}
