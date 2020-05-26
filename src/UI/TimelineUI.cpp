//
// Created by Jur de Vries on 16/04/2020.
//

#include "TimelineUI.h"

TimelineUIRef TimelineUI::create(Timeline &timeline, bool &recording)
{
    return TimelineUIRef(new TimelineUI(timeline, recording));
}

void TimelineUI::drawUi(int top) {
    ImGui::Begin("Simple overlay", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(0, top), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(ofGetCurrentWindow()->getWidth(), 20), ImGuiCond_Always);
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
        }
        ImGui::SameLine(0.f, 4.f);
        static std::string stopText;
        stopText = playing ? "Stop" : "Rewind";
        if (ImGui::Button(stopText.c_str())) {
            if (!playing) {
                timeline.reset();
            }
            timeline.stop();
            recording = false;
        }
        ImGui::SameLine(0.f, 4.f);
        static ImVec4 recordingColor;
        recordingColor = recording ? ImVec4(0.8f, 0.0f, 0.0f, 1.0f) : ImVec4(0.2f, 0.0f, 0.0f, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Button, recordingColor);
        if (ImGui::Button("Record")) {
            if (!recording) {
                recording = true;
                timeline.start();
            }
        }
        ImGui::PopStyleColor(1);
    }
    ImGui::SameLine(0.f, 4.f);
    ImGui::Text(timeline.timecode().c_str());
    ImGui::SameLine(0.f, 10.f);
    std::string inputMessageString = "Last input osc message: ";
    inputMessageString += Utils::oscMessageToString(inputMessage);
    ImGui::Text(inputMessageString.c_str());
    ImGui::SameLine(0.f, 4.f);
    std::string outputMessageString = "Last output osc message: ";
    outputMessageString += Utils::oscMessageToString(outputMessage);
    ImGui::Text(outputMessageString.c_str());
    ImGui::End();
}

TimelineUI::TimelineUI(Timeline &timeline, bool &recording)
:timeline(timeline), recording(recording)
{
    inputMessage = ofxOscMessage();
}

void TimelineUI::setInputMessage(ofxOscMessage message) {
    inputMessage = message;
}

void TimelineUI::setOutputMessage(ofxOscMessage &outputMessage) {
    TimelineUI::outputMessage = outputMessage;
}
