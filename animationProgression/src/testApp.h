#pragma once

#include "ofMain.h"
#include "SegmentedVideo.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		  
        SegmentedVideo vid;
    
};
