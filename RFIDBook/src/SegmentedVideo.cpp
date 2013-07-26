//
//  SegmentedVideo.cpp
//  animationProgression
//
//  Created by Brett Peterson on 7/25/13.
//
//

#include "SegmentedVideo.h"



SegmentedVideo::SegmentedVideo() {}
SegmentedVideo::~SegmentedVideo() {}


void SegmentedVideo::setup(string fileName){
    player.setPixelFormat(OF_PIXELS_RGBA);
    player.loadMovie(fileName);
    ofEnableAlphaBlending();
    
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
    flowerSway.frame = 150;
    flowerSway.gate = NOGATE;
    flowerSway.loopbackCue = -1;
    cues.push_back(flowerSway);
    
    
    // end sway
    cue endSway;
    endSway.frame = 330;
    endSway.gate = CLOSEDGATE;
    endSway.loopbackCue = 1;
    cues.push_back(endSway);
    
    
    // berries grow
    cue berries;
    berries.frame = 340;
    berries.gate = NOGATE;
    berries.loopbackCue = 1;
    cues.push_back(berries);
    
    // berries fall
    cue fall;
    fall.frame = 540;
    fall.gate = CLOSEDGATE;
    fall.loopbackCue = 3;
    cues.push_back(fall);
    
    // end
    cue end;
    end.frame = player.getTotalNumFrames() - 30;
    end.gate = CLOSEDGATE;
    end.loopbackCue = 1;
    cues.push_back(end);
    
    //////////////////////
    
    player.play();

}


void SegmentedVideo::update(){
    
    player.update();
    
    for (int i = 0; i < cues.size(); i++) {
        
        // If the current frame is an event cue, check gate
        if (player.getCurrentFrame() == cues.at(i).frame){
            cue currentCue = cues.at(i);
            
            // If the gate is closed, loop video to specified cue
            if (currentCue.gate == CLOSEDGATE) {
                player.setFrame(cues.at(currentCue.loopbackCue).frame);
            }
            
            // If the video has reached the last cue, reset the gates on the 2 loops
            if (i == cues.size() - 1) {
                cues.at(2).gate = CLOSEDGATE;
                cues.at(4).gate = CLOSEDGATE;
            }
        }
    }
    
}

void SegmentedVideo::draw(float x, float y){
    
    player.draw(x-player.width/2, y-player.height/2);
    
    // Debug messaging
//    ofDrawBitmapString("Press 1 to toggle flower and berry looping", 200, 20);
//    ofDrawBitmapString(ofToString(ofGetElapsedTimeMillis() / 1000), 780, 10);
//    ofDrawBitmapString(ofToString(player.getCurrentFrame()), 780, 20);
//    ofDrawBitmapString("Flower looping: ", 650, 40);
//    if (cues.at(2).gate == CLOSEDGATE) {
//        ofDrawBitmapString("ON", 780, 40);
//    }
//    else {
//        ofDrawBitmapString("OFF", 780, 40);
//    }
//    
//    ofDrawBitmapString("Berry looping: ", 650, 60);
//    if (cues.at(4).gate == CLOSEDGATE) {
//        ofDrawBitmapString("ON", 780, 60);
//    }
//    else {
//        ofDrawBitmapString("OFF", 780, 60);
//    }

    
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

