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
#include "OfFadeVideo.h"

class Media {
    
public:
    Media();
    ~Media();
    
    void setup(string mediaFile, float _x, float _y);
    void setup(string _imgFile, string vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback);
    void update();
    void draw(float scale=1.0f);
    void setPosition(float _x, float _y);
    ofPoint getPosition();
    string getFileName();
    
    void playVid();
    void pauseVid();
    
    void moveTo(int _x, int _y);
    
    void setDraggable(bool _bDrag);
    
    float x;
    float y;
    
    float vidX;
    float vidY;
    
    bool hasVid;
    bool vidState;
    
    int autoplay;
    string tapId;
    
    //TODO
    int mediaState;
    int loopCount;
    
    // -1 = no looping, 0 = loop from beginning, {positive number} = loop from that position
    float loopback = -1.0f;
    
    ofFadeImage img;
    ofFadeVideo vid;
    
private:
    bool isDraggable;
    bool isDragging;
    string imgFileName;
    string vidFileName;
    
    
};


#endif /* defined(__RFIDBook__Media__) */
