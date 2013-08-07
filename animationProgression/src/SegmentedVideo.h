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

#define NOGATE -1
#define CLOSEDGATE 0
#define OPENGATE 1

struct cue {
    int frame;
    int gate;
    int loopbackCue;
};

class SegmentedVideo{
    
    public:
        SegmentedVideo();
        ~SegmentedVideo();
    
        void update();
        void draw();
    void touch();
    
        ofVideoPlayer player;
        string animFile = "belladonna_SEG.mov";
        
        vector<cue> cues;
};

#endif /* defined(__animationProgression__SegmentedVideo__) */
