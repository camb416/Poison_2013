//
//  Page.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/10/13.
//
//

#include "Page.h"

Page::Page(){
    doDrag = false;
}
Page::~Page(){
    media.clear();
}

void Page::setup(){

    //
    // key press inputs for the pages
    //
    validInputs.push_back('H'); // touch sensor A (left)
    validInputs.push_back('J'); // touch sensor B (right)
    validInputs.push_back('R'); // running
    validInputs.push_back('C'); // clear all params
    //
    
    //
    // Media involved in left & right touch events & media faded out when touch active
    touchMediaMatrix.resize(3);
}

void Page::setDrag(bool _doDrag){
    doDrag = _doDrag;
}

// Update all media elements on page

void Page::hideAllBorders(){
    for (int i = 0; i < media.size(); i++) {
        media.at(i)->setDraggable(false);
    }
}

void Page::dragUpdate(){

    // add toggleable draggy stuff
    if(!doDrag){
        ofPoint mousePos = ofPoint(ofGetMouseX(),ofGetMouseY());
        float nearestDist = 99999;
        int nearestID = -1;
        for (int i = 0; i < media.size(); i++) {
            ofPoint thisOrigin = media.at(i)->getPosition();
            float thisDist = ofDist(thisOrigin.x,thisOrigin.y,mousePos.x,mousePos.y);
            if(thisDist<nearestDist){
                nearestID = i;
                nearestDist = thisDist;
            }
            media.at(i)->setDraggable(false);
        }
        if(nearestID>-1){
            media.at(nearestID)->setDraggable(true);
            selectedMedia = media.at(nearestID);
        }
    } else {
        if(selectedMedia!=NULL){
            selectedMedia->moveTo(ofGetMouseX(),ofGetMouseY());
        }
    }
}
void Page::update(){
    for (int i = 0; i < media.size(); i++) {
        media.at(i)->update();
    }
    
    if (touchActive){
        int currentFrame;
        int lastFrame;
        
        try {
            if (currentTouch == 'H'){
                currentFrame = media.at(touchMediaMatrix[0][0])->vid.getCurrentFrame();
                lastFrame = media.at(touchMediaMatrix[0][0])->vid.getTotalNumFrames();
            } else if (currentTouch == 'J'){
                currentFrame = media.at(touchMediaMatrix[1][0])->vid.getCurrentFrame();
                lastFrame = media.at(touchMediaMatrix[1][0])->vid.getTotalNumFrames();
            }
            
            if (currentFrame == lastFrame){
                
                if (currentTouch == 'H'){
                    media.at(touchMediaMatrix[0][0])->vid.fadeOut();
                    media.at(touchMediaMatrix[0][0])->pauseVid();
                    media.at(touchMediaMatrix[0][0])->vidState = 0;
                } else if (currentTouch == 'J'){
                    media.at(touchMediaMatrix[1][0])->vid.fadeOut();
                    media.at(touchMediaMatrix[1][0])->pauseVid();
                    media.at(touchMediaMatrix[1][0])->vidState = 0;
                }
                
                int size = touchMediaMatrix[2].size();
                for (int i=0; i < size; i++){
                    media.at(touchMediaMatrix[2][i])->img.fadeIn();
                    media.at(touchMediaMatrix[2][i])->vid.fadeIn();
                }
                
                touchActive = false;
                currentTouch = 'R';
            }
        }  catch (...) {
            touchActive = false;
            ofLogError() << "Error updating media ";
        }
    }



}

void Page::draw(float originX, float originY, float scale){
    
    if (scale == 1.0f) {
        
        // Run the normal draw method for each media element
        for (int i = 0; i < media.size(); i++) {
            media.at(i)->draw();
        }
        
    }
    else {
        // Run the scaled draw method for each media element
        for (int i = 0; i < media.size(); i++) {
            media.at(i)->draw(scale);
        }
    }
    
}

void Page::addMedia(string fileName, ofVec2f position, int autoplay, string tapId, int loopback){
    
    Media * newMedia = new Media();
    
    string sub = fileName.substr(fileName.length()-3,3);
    if (sub == "png") {
        
        // run the setup for a media element that is just an image
        newMedia->setup(fileName, position.x, position.y);
        
    }
    else if (sub == "mov"){
        
        // Run the setup for a media element that is a video and an image
        string imageFile = fileName;
        imageFile.replace(fileName.length() -3, 3, "png");
        newMedia->setup(imageFile, fileName, position.x, position.y, autoplay, tapId, loopback);
        
    }
    else {
        
        ofLogNotice() << "unrecognized media file extension: " << fileName;
    
    }
    
    media.push_back(newMedia);
    ofLogNotice() << "Added new media element " << fileName << " to page at position " << position.x << "," << position.y;
    
}

void Page::receiveInput(char touchId_in, int pageNum_in){

    int position = -1;
    
    // Look for character in valid inputs vector
    for (int i = 0; i < validInputs.size(); i++) {

        // Hide and elements according to which page we're on and which sensor was touched.
        
        if (validInputs.at(i) == touchId_in){
            
            if (touchId_in != currentTouch && touchActive == false){
                // Fade out elements that are in the way
                                
                try {
                    touchActive = true;
                    
                    // fade out media already live on page, marked with 'K' as touch ID
                    int size = touchMediaMatrix[2].size();
                    for (int i=0; i < size; i++){
                        media.at(touchMediaMatrix[2][i])->img.fadeOut();
                        media.at(touchMediaMatrix[2][i])->vid.fadeOut();
                    }
                    
                    if (touchId_in == 'H'){
                        media.at(touchMediaMatrix[0][0])->playVid();
                        media.at(touchMediaMatrix[0][0])->vid.fadeIn();
                    } else if (touchId_in == 'J'){
                        media.at(touchMediaMatrix[1][0])->playVid();
                        media.at(touchMediaMatrix[0][0])->vid.fadeIn();
                    }
                } catch (...) {
                    touchActive = false;
                    ofLogError() << "Error playing media" << " on page " << pageNum_in;
                }

    currentTouch = touchId_in;
    }
    }
}
}




void Page::fade(int dir){
    
    // Loop through media elements and fade them in or out
    float minFadeIn = 4.0f;
    float maxFadeIn = 64.0f;
    float minFadeOut = 2.0f;
    float maxFadeOut = 8.0f;
    
    if (dir == 1) {
        for (int i = 0; i < media.size(); i++) {
            // TODO - handle video fade in as well
            float fadeVal = ofRandomuf()*(maxFadeIn-minFadeIn)+minFadeIn;
            //cout << fadeVal << endl;
            media.at(i)->img.fadeIn(fadeVal);
            media.at(i)->vid.fadeIn(fadeVal);
            
            // If autoplay is on for the video, start playing
            
            if (media.at(i)->hasVid == true){
                if (media.at(i)->autoplay == 1){
                    media.at(i)->playVid();
                }
            }
        }
    }
    else {
        for (int i = 0; i < media.size(); i++) {
            // TODO - handle video fade out as well
           
            float fadeVal = ofRandomuf()*(maxFadeOut-minFadeOut)+minFadeOut;
            // cout << fadeVal << endl;
            
            media.at(i)->img.fadeOut(fadeVal);
            media.at(i)->vid.fadeOut(fadeVal);
            media.at(i)->vidState = 0;
            // stop all video
            media.at(i)->pauseVid();
        }
    }
    
}
ofxXmlSettings Page::getXML(){
    ofxXmlSettings xml;
    xml.addTag("Page");
    xml.pushTag("Page");
    for(int i=0;i<media.size();i++){
        xml.addTag("Media");
        ofPoint pt = media.at(i)->getPosition();
        xml.setAttribute("Media", "x", (int)pt.x,i);
        xml.setAttribute("Media", "y", (int)pt.y,i);
        xml.setAttribute("Media", "src", media.at(i)->getFileName(),i);
        xml.setAttribute("Media", "auto", (int)media.at(i)->autoplay, i);
        xml.setAttribute("Media", "tapId", (string)media.at(i)->tapId, i);
        xml.setAttribute("Media", "loopback", (int)media.at(i)->loopback, i);

        
        
    }
    return xml;
}

