//
//  Media.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/7/13.
//
//

#include "Media.h"

Media::Media(){}
Media::~Media(){}

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
    vid.setup(vidFile);
    
    hasVid = true;
    vidState = 1;

    vid.play();

}

void Media::setPosition(float _x, float _y){
    x = _x;
    y = _y;
}


void Media::tap(){
    
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
    vid.update();
    

    
}

void Media::draw(){
    
    //TODO check mediaState
    
    if (vidState == 0){
        img.draw(x,y);
    }
    else {
        vid.draw(x, y);
    }
    
}
