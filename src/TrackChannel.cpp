//
// Created by Jur de Vries on 14/04/2020.
//

#include "TrackChannel.h"

TrackChannel::TrackChannel() {
    track = OscTrackRef(new OscTrack);
    player = OscTrackPlayerRef(new OscTrackPlayer(track.get()));
    recorder = OscTrackRecorderRef(new OscTrackRecorder(track.get()));
}
