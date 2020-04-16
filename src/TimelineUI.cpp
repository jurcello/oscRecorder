//
// Created by Jur de Vries on 16/04/2020.
//

#include "TimelineUI.h"

TimelineUIRef TimelineUI::create(Timeline &timeline) {
    return TimelineUIRef(new TimelineUI(timeline));
}

void TimelineUI::drawUi() {
    ImGui::Begin("Simple overlay", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(0,0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(ofGetCurrentWindow()->getWidth(), 100), ImGuiCond_Always);
    {
        bool playing = timeline.running();
        if (playing) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.5f, 0.f, 1.f));
        }
        if (ImGui::Button("Play")) {
            timeline.start();
        }
        if (playing) {
            ImGui::PopStyleColor(1);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.0f, 0.f, 1.f));
        }
        else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.0f, 0.f, 1.f));
        }
        ImGui::SameLine(0.f, 4.f);
        if (ImGui::Button("Stop")) {
            if (!playing) {
                timeline.reset();
            }
            timeline.stop();
        }
        ImGui::PopStyleColor(1);
    }
    ImGui::SameLine(0.f, 4.f);
    if (ImGui::Button("Rewind")) {
        timeline.reset();
    }
    ImGui::SameLine(0.f, 4.f);
    ImGui::Text(timeline.timecode().c_str());
    ImGui::End();
}

TimelineUI::TimelineUI(Timeline &timeline)
:timeline(timeline)
{
}
