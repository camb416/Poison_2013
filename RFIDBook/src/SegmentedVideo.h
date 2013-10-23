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

//class BookView;

struct cue {
    int frame;
    int gate;
    int loopbackCue;
};

class SegmentedVideo : public ofFadeVideo{
    
private:
    public:
        SegmentedVideo();
        ~SegmentedVideo();
    
        void setup(string fileName);
        void update();
        void touch();
        bool showButton = false;
    
        vector<cue> cues;
    
};

#endif /* defined(__animationProgression__SegmentedVideo__) */
