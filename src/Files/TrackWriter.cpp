//
// Created by Jur de Vries on 25/05/2020.
//

#include "TrackWriter.h"
#include "ofxJSON.h"

TrackWriter::TrackWriter(OscTrackRef track)
:track(track)
{
}

void TrackWriter::write(std::string path) {
    ofxJSON json;
    for (auto event: *(track)) {
        ofxJSON messageJson = messageToJson(event);
        json["messages"].append(messageJson);
    }
    json.save(path, false);
}

ofxJSON TrackWriter::messageToJson(const TrackEvent<ofxOscMessage> &event) const {
    ofxJSON messageJson;
    messageJson["time"] = event.millis;
    messageJson["address"] = event.message.getAddress();
    messageJson["args"] = argsToJson(event.message);
    return messageJson;
}

ofxJSON TrackWriter::argsToJson(const ofxOscMessage &m) const {
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
