//
// Created by Jur de Vries on 30/04/2020.
//

#include "TracksWindowUI.h"
#include "ofxImGui.h"
#include "timeline.h"
#include "ofLog.h"

void TracksWindowUI::draw(Timeline &timeline, TrackChannel channel, int marginTop) {
    drawerHelper.setMaxTimeMillis(70*1000);
    drawerHelper.setPixelsPerSecond(60.f);
    drawerHelper.setCurrentTimeMillis(timeline.elapsedMillis());
    ImGui::SetNextWindowContentSize(ImVec2(drawerHelper.getContentSize(), 100.f));
    ImGui::Begin("Track window", NULL, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
    ImGui::SetWindowPos(ImVec2(0, marginTop), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(ofGetCurrentWindow()->getWidth(), height), ImGuiCond_Always);

    auto windowWidth = ImGui::GetWindowWidth();
    drawerHelper.setCurrentWindowWidth(static_cast<int>(windowWidth));
    if ((playing && following)) {
        ImGui::SetScrollX(drawerHelper.getScrollOffset());
    }
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    auto windowLeftTop = ImGui::GetWindowPos();
    auto windowBottomRight = windowLeftTop + ImGui::GetWindowSize();
    auto contentPosition = windowLeftTop - ImVec2(ImGui::GetScrollX(), 0.f);

    ImGuiIO& io = ImGui::GetIO();
    if (ImGui::IsMousePosValid()) {
        auto mousePos = io.MousePos;
        if (mouseIsInsideWindow(mousePos, windowLeftTop, windowBottomRight) && ImGui::IsMouseClicked(0))
        {
            auto mousePosInContent = mousePos - contentPosition;
            auto millisFromPixels = drawerHelper.getMillisFromPixels(mousePosInContent.x);
            timeline.setCurrentMillis(millisFromPixels);
            channel.player->seek(millisFromPixels);
        }
    }

    drawRuler(drawList, contentPosition, 20.f, 20.f);
    drawTracks(drawList, contentPosition, channel);
    drawPlayHead(drawList, contentPosition);

    ImGui::End();
}

bool TracksWindowUI::mouseIsInsideWindow(const ImVec2 &mousePos, const ImVec2 &windowLeftTop, const glm::vec2 &windowBottomRight) const {
    return (mousePos.x > windowLeftTop.x && mousePos.y > windowLeftTop.y) &&
                    (mousePos.x < windowBottomRight.x && mousePos.y < windowBottomRight.y);
}

void TracksWindowUI::drawPlayHead(ImDrawList *drawList, const glm::vec2 &windowPos) const {
    drawList->AddLine(ImVec2(drawerHelper.getTimeMarkerPosition(), 0.f) + windowPos, ImVec2(drawerHelper.getTimeMarkerPosition(), height) + windowPos, ImColor(255,255,255), 1.f);
}

void TracksWindowUI::drawTracks(ImDrawList *drawList, const glm::vec2 &windowPos, TrackChannel channel) const {
    if (channel.track->size() > 0) {
        auto offset = 0.f;
        auto trackSize = drawerHelper.getPixelsFromMillis(channel.player->timeLength());
        auto paddingTop = 60.f;
        auto trackHeight = 60.f;
        drawList->AddRectFilled(ImVec2(offset, paddingTop) + windowPos, ImVec2(offset + trackSize, paddingTop + trackHeight) + windowPos, ImColor(255, 0, 0, 100));
        drawList->AddRect(ImVec2(offset, paddingTop) + windowPos, ImVec2(offset + trackSize, paddingTop + trackHeight) + windowPos, ImColor(255, 0, 0, 255));
        // Draw float events assuming they are from 0 to 1.
        for (TrackEvent<ofxOscMessage> event : *(channel.track)) {
            if (event.message.getNumArgs() == 1 && event.message.getArgAsFloat(0)) {
                auto positionX = drawerHelper.getPixelsFromMillis(event.millis);
                auto messageValue = event.message.getArgAsFloat(0);
                auto positionY = (trackHeight - messageValue * trackHeight) + paddingTop;
                auto center = ImVec2(positionX, positionY) + windowPos;
                drawList->AddCircleFilled(center, 2.f, ImColor(255, 0, 0, 255));
            }
        }
    }
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

void TracksWindowUI::setHeight(int height) {
    TracksWindowUI::height = height;
}
