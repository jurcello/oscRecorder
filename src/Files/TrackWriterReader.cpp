//
// Created by Jur de Vries on 25/05/2020.
//

#include "TrackWriterReader.h"
#include "ofxJSON.h"

TrackWriterReader::TrackWriterReader(OscTrackRef track)
:track(track)
{
    recorder = OscTrackRecorderRef(new OscTrackRecorder(track.get()));
}

void TrackWriterReader::write(std::string path) {
    ofxJSON json;
    for (auto event: *(track)) {
        ofxJSON messageJson = messageToJson(event);
        json["messages"].append(messageJson);
    }
    json.save(path, false);
}

ofxJSON TrackWriterReader::messageToJson(const TrackEvent<ofxOscMessage> &event) const {
    ofxJSON messageJson;
    messageJson["time"] = event.millis;
    messageJson["address"] = event.message.getAddress();
    messageJson["args"] = argsToJson(event.message);
    return messageJson;
}

ofxJSON TrackWriterReader::argsToJson(const ofxOscMessage &m) const {
    int numArgs = static_cast<int>(m.getNumArgs());

    ofxJSON args;
    for(size_t i = 0; i < numArgs; i++){
        ofxJSON arg;
        int typeInt = m.getArgType(i);
        ofxOscArgType type = ofxOscArgType(typeInt);
        arg["type"] = (int)type;
        switch (type) {
            case OFXOSC_TYPE_INT32: arg["value"] = m.getArgAsInt(i); break;
            case OFXOSC_TYPE_INT64: arg["value"] = m.getArgAsInt64(i); break;
            case OFXOSC_TYPE_FLOAT: arg["value"] = m.getArgAsFloat(i); break;
            case OFXOSC_TYPE_DOUBLE: arg["value"] = m.getArgAsDouble(i); break;
            case OFXOSC_TYPE_STRING: arg["value"] = m.getArgAsString(i); break;
            case OFXOSC_TYPE_SYMBOL: arg["value"] = m.getArgAsSymbol(i); break;
            case OFXOSC_TYPE_CHAR: arg["value"] = char(m.getArgAsChar(i)); break;
            case OFXOSC_TYPE_MIDI_MESSAGE: arg["value"] = m.getArgAsMidiMessage(i); break;
            case OFXOSC_TYPE_TRUE: arg["value"] = m.getArgAsBool(i); break;
            case OFXOSC_TYPE_FALSE: arg["value"] = m.getArgAsBool(i); break;
            case OFXOSC_TYPE_TRIGGER: arg["value"] = m.getArgAsTrigger(i); break;
            case OFXOSC_TYPE_TIMETAG: arg["value"] = m.getArgAsTimetag(i); break;
            case OFXOSC_TYPE_RGBA_COLOR: arg["value"] = m.getArgAsRgbaColor(i); break;
            case OFXOSC_TYPE_NONE:
                break;
            case OFXOSC_TYPE_BLOB:
                break;
            case OFXOSC_TYPE_INDEXOUTOFBOUNDS:
                break;
        }
        args.append(arg);
    }
    return args;
}

void TrackWriterReader::readFromFile(std::string path) {
    emptyTrack();
    ofxJSON trackJson;
    if (trackJson.open(path)) {
        for (auto &messageJson: trackJson["messages"]) {
            u_int64_t millis = static_cast<u_int64_t>(messageJson["time"].asInt64());
            ofxOscMessage m = jsonToOscMessage(messageJson);
            recorder->recordMessage(millis, m);
        }
    }

}

ofxOscMessage TrackWriterReader::jsonToOscMessage(const ofxJSON &messageJson) {
    ofxOscMessage m;
    m.setAddress(messageJson["address"].asString());
    jsonArgsToOscMessage(m, messageJson["args"]);
    return m;
}

void TrackWriterReader::jsonArgsToOscMessage(ofxOscMessage &m, const Json::Value &jsonArgs) const {
    for (auto &arg : jsonArgs) {
        int typeInt = arg["type"].asInt();
        ofxOscArgType type = ofxOscArgType(typeInt);

        switch (type) {
            case OFXOSC_TYPE_INT32:
                m.addIntArg(arg["value"].asInt());
                break;
            case OFXOSC_TYPE_INT64:
                m.addInt64Arg(arg["value"].asInt64());
                break;
            case OFXOSC_TYPE_FLOAT:
                m.addFloatArg(arg["value"].asFloat());
                break;
            case OFXOSC_TYPE_DOUBLE:
                m.addDoubleArg(arg["value"].asDouble());
                break;
            case OFXOSC_TYPE_STRING:
                m.addStringArg(arg["value"].asString());
                break;
            case OFXOSC_TYPE_SYMBOL:
                m.addSymbolArg(arg["value"].asString());
                break;
            case OFXOSC_TYPE_CHAR:
                m.addCharArg(char(arg["value"].asInt()));
                break;
            case OFXOSC_TYPE_MIDI_MESSAGE:
                m.addIntArg(arg["value"].asInt());
                break;
            case OFXOSC_TYPE_TRUE:
                m.addBoolArg(arg["value"].asBool());
                break;
            case OFXOSC_TYPE_FALSE:
                m.addBoolArg(arg["value"].asBool());
                break;
            case OFXOSC_TYPE_TRIGGER:
                m.addBoolArg(arg["value"].asBool());
                break;
            case OFXOSC_TYPE_TIMETAG:
                m.addInt64Arg(arg["value"].asInt64());
                break;
            case OFXOSC_TYPE_RGBA_COLOR:
                m.addIntArg(arg["value"].asInt());
                break;
            case OFXOSC_TYPE_NONE:
                break;
            case OFXOSC_TYPE_BLOB:
                break;
            case OFXOSC_TYPE_INDEXOUTOFBOUNDS:
                break;
        }
    }
}

void TrackWriterReader::emptyTrack() const {
    recorder->clear();
}
