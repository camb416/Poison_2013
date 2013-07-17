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
    vidFileName = "";
    imgFileName = "";
    mediaType = -1;
}
Media::~Media(){}

// Image only
void Media::setup(string mediaFile, float _x, float _y, string _tapId){
    
    imgFileName = mediaFile;
    setPosition(_x, _y);
    img.setup(mediaFile);
    hasVid = false;
    autoplay = -1;
    tapId = _tapId;
    mediaType = IMGMEDIA;

}

// Image and video
void Media::setup(string _imgFile, string _vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback){
    
    
    

    setPosition(_x, _y);
    
    
    
    
    tapId = _tapId;
    

    
    if (loopback == 0){
        vid.setLoopState(OF_LOOP_PALINDROME);
    } else {
        vid.setLoopState(OF_LOOP_NONE);
    }
    
    if(_imgFile.length()>3){
        if(_vidFile.length()>3){
            mediaType = DUALMEDIA;
        } else {
            mediaType = IMGMEDIA;
        }
        
    } else if(_vidFile.length()>3){
        mediaType = VIDMEDIA;
    } else {
        mediaType = UNKNOWNMEDIA;
    }
    
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA){
        vidFileName = _vidFile;
        hasVid = true;
        vidState = 0;
        vid.setup(_vidFile);
        autoplay = _autoplay;
        loopback = _loopback;
    }
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA){
        img.setup(_imgFile);
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
            vid.nextFrame();
            vid.play();
        }
    }
}

void Media::stopVid(){
    
    if (hasVid) {
        if (vid.isPlaying() == true){
            vid.stop();
            vid.setFrame(0);
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
        if (vidState == 0 && (tapId == "" || tapId == "K")){
            img.draw(x,y, img.width*scale, img.height*scale);
        }
        else if (vidState == 1) {
            vid.draw(x, y, vid.width*scale, vid.height*scale);
        }
        
        
    }

}
void Media::printInfo(){
    switch(mediaType){
        
        case 0:
            cout << "IMAGE MEDIA: "<< imgFileName << "." << endl;
            break;
        case 1:
            cout << "VIDEO MEDIA: " << vidFileName << "." << endl;
            break;
        case 2:
            cout << "DUAL MEDIA: " << imgFileName.length() << ": " << imgFileName << ", " << vidFileName << "." << endl;
            break;
        default:
            cout << "UNKNOWN MEDIA: ";
            break;
            
    }
    //cout << vidFileName << ", " << imgFileName << "." << endl;
}
