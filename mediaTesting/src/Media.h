//
//  Media.h
//  RFIDBook
//
//  Created by Brett Peterson on 6/7/13.
//
//

#ifndef __RFIDBook__Media__
#define __RFIDBook__Media__

#include <iostream>
#include "ofMain.h"
#include "ofFadeImage.h"
#include "ofFadeVideo.h"

class Media {
    
public:
    Media();
    ~Media();
    
    void setup(string imgFile, float _x, float _y);
    void setup(string imgFile, string vidFile, float _x, float _y);
    void update();
    void draw();
    void setPosition(float _x, float _y);
    void tap();
        
    float x;
    float y;
    
    bool hasVid;
    bool vidState;
    
    //TODO
    int mediaState;
    int loopCount;
    
    // -1 = no looping, 0 = loop from beginning, {positive number} = loop from that position
    float loopback = -1.0f;
    
    ofFadeImage img;
    ofFadeVid vid;
    
    
};


#endif /* defined(__RFIDBook__Media__) */
