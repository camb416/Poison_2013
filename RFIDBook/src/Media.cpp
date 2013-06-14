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
Media::~Media(){

}

// Image only
void Media::setup(string imgFile, float _x, float _y){
    
    setPosition(_x, _y);
    img.setup(imgFile);
    
    hasVid = false;
}

// Image and video
void Media::setup(string imgFile, string vidFile, float _x, float _y){
    
    setPosition(_x, _y);
    img.setup(imgFile);
    
    hasVid = true;
    vidState = 0;
    vid.loadMovie(vidFile);
    
}

void Media::setPosition(float _x, float _y){
    x = _x;
    y = _y;
}
ofPoint Media::getPosition(){
    ofPoint returnVal = ofPoint(x,y);
}


void Media::playPause(){
    
    //TODO check mediaState
    
    if (hasVid) {
        if (vidState == 0) {
            vidState = 1;
            vid.play();
        } else {
            vidState = 0;
            vid.stop();
        }
    }
    
}

void Media::update(){
    
    //TODO check mediaState to see what to do
    
    img.update();
    //vid.update();
    if(isDraggable){
        img.setBorder(true);
        
    }
    
    
}

void Media::moveTo(int _x, int _y){
    // eventually, this should tween.
    x = _x;
    y = _y;
}

void Media::setDraggable(bool _bDrag){
    isDraggable = _bDrag;
}

void Media::draw(){

    if (hasVid == false) {
        img.draw(x,y);
    }
    else {
    
        if (vidState == 0){
            img.draw(x,y);
        }
        else {
            vid.draw(x, y);
        }
    }
    
}

void Media::drawScaled(float scale){
    
    if (hasVid == false){
        img.draw(x,y, img.width*scale, img.height*scale);
    }
    else {
        if (vidState == 0 || hasVid == false){
            img.draw(x,y, img.width*scale, img.height*scale);
        }
        else {
            vid.draw(x, y, vid.width*scale, vid.width*scale);
        }
    }

}
