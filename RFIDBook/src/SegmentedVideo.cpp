//
//  SegmentedVideo.cpp
//  animationProgression
//
//  Created by Brett Peterson on 7/25/13.
//
//

#include "SegmentedVideo.h"



SegmentedVideo::SegmentedVideo() {
    ofFadeVideo::ofFadeVideo();
}
SegmentedVideo::~SegmentedVideo() {}


void SegmentedVideo::setup(string fileName){
    
    
    ofFadeVideo::setup(fileName);
    
    ////////////////////////
    /// LOAD IN CUE INFO ///
    ////////////////////////
    
    // draw in
    cue start;
    start.frame = 0;
    start.gate = NOGATE;
    start.loopbackCue = -1;
    cues.push_back(start);
    
    // start sway
    cue flowerSway;
    flowerSway.frame = 120;
    flowerSway.gate = NOGATE;
    flowerSway.loopbackCue = -1;
    cues.push_back(flowerSway);
    
    
    // end sway
    cue endSway;
    endSway.frame = 263;
    endSway.gate = CLOSEDGATE;
    endSway.loopbackCue = 1;
    cues.push_back(endSway);
    
    
    // berries grow
    cue berries;
    berries.frame = 288;
    berries.gate = NOGATE;
    berries.loopbackCue = 1;
    cues.push_back(berries);
    
    // berries fall
    cue fall;
    fall.frame = 431;
    fall.gate = CLOSEDGATE;
    fall.loopbackCue = 3;
    cues.push_back(fall);
    
    // end
    cue end;
    end.frame = 575;
    end.gate = CLOSEDGATE;
    end.loopbackCue = 1;
    cues.push_back(end);
    
    //////////////////////

}


void SegmentedVideo::update(){
    
    //player.update();
    ofFadeVideo::update();
    
    for (int i = 0; i < cues.size(); i++) {
        
        // If the current frame is an event cue, check gate
        if ( getCurrentFrame() == cues.at(i).frame){
            cue currentCue = cues.at(i);
            
            // If the gate is closed, loop video to specified cue
            if (currentCue.gate == CLOSEDGATE) {
                setFrame(cues.at(currentCue.loopbackCue).frame);
            }
            
            // If the video has reached the last cue, reset the gates on the 2 loops
            if (i == cues.size() - 1) {
                cues.at(2).gate = CLOSEDGATE;
                cues.at(4).gate = CLOSEDGATE;
            }
        }
    }
    
}

// Recieve touch input and open gates
void SegmentedVideo::touch(){
    
    if (cues.at(2).gate == CLOSEDGATE){
        cues.at(2).gate = OPENGATE;
    }
    else {
        cues.at(4).gate = OPENGATE;
    }
}

