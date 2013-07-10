//
//  Media.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/7/13.
//
//

#include "Media.h"

Media::Media(){
    isDraggable = true;
    isDragging = false;
}
Media::~Media(){}

// Image only
void Media::setup(string mediaFile, float _x, float _y){
    
    imgFileName = mediaFile;
    setPosition(_x, _y);
    img.setup(mediaFile);
    hasVid = false;
    autoplay = -1;
    tapId = "";

}

// Image and video
void Media::setup(string _imgFile, string _vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback){
    
    
    vidFileName = _vidFile;
    setPosition(_x, _y);
    img.setup(_imgFile);
    
    
    autoplay = _autoplay;
    string tapId;
    hasVid = true;
    vidState = 0;
    vid.setup(_vidFile);
    loopback = _loopback;
    
    if (loopback == 0){
        vid.setLoopState(OF_LOOP_PALINDROME);
    } else {
        vid.setLoopState(OF_LOOP_NONE);
    }
    
}

void Media::setPosition(float _x, float _y){
    x = _x;
    y = _y;
}

ofPoint Media::getPosition(){
    ofPoint returnVal = ofPoint(x,y);
    return returnVal;
}

string Media::getFileName(){
    if (hasVid == true){
        return vidFileName;
    } else {
        return imgFileName;
    }
}


void Media::playVid(){

    
    if (hasVid) {
        if (vid.isPlaying() == false) {
            vidState = 1;
            vid.setFrame(0);
            vid.play();
        }
    }
}

void Media::pauseVid(){
    
    if (hasVid) {
        if (vid.isPlaying() == true){
            vid.stop();
            loopCount = 0;
        }

    }

}

void Media::update(){
    
    //TODO check mediaState to see what to do
    
    img.update();
    
    if (hasVid) {
      
            int currentFrame = vid.getCurrentFrame();
            int lastFrame = vid.getTotalNumFrames();
        
            if (currentFrame == lastFrame && loopback > 0){
                vid.setFrame(loopback);
//                ofLogNotice() << "current frame: " << currentFrame;
            }
        
        vid.update();

    }
    

}

void Media::moveTo(int _x, int _y){
    // eventually, this should tween.
    x = _x;
    y = _y;
}

void Media::setDraggable(bool _bDrag){
    isDraggable = _bDrag;

    img.setBorder(isDraggable);
    vid.setBorder(isDraggable);

    
}

void Media::draw(float scale){
    
    if (hasVid == false){
        img.draw(x,y, img.width*scale, img.height*scale);
    }
    else {
        if (vidState == 0){
            img.draw(x,y, img.width*scale, img.height*scale);
        }
        else {
            vid.draw(x, y, vid.width*scale, vid.height*scale);
        }
    }

}
