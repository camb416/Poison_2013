//
//  SegmentedVideo.h
//  animationProgression
//
//  Created by Brett Peterson on 7/25/13.
//
//

#ifndef __animationProgression__SegmentedVideo__
#define __animationProgression__SegmentedVideo__

#include <iostream>
#include "ofMain.h"
#include "ofFadeVideo.h"

#define NOGATE -1
#define CLOSEDGATE 0
#define OPENGATE 1

struct cue {
    int frame;
    int gate;
    int loopbackCue;
};

class SegmentedVideo : public ofFadeVideo{
    
    public:
        SegmentedVideo();
        ~SegmentedVideo();
    
        void setup(string fileName);
        void update();
        //void draw(float x, float y);
        void touch();
        bool showButton = false;
    
        //ofVideoPlayer player;
        //string animFile = "belladona.mov";
        
        vector<cue> cues;
};

#endif /* defined(__animationProgression__SegmentedVideo__) */
