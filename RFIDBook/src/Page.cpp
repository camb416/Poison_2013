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
    // stuff that has to fade out for a video to play
    // touchMedia0 is for page 0
    // each int in the vector refers to the id of the media to
    // fade out
    //
    //
    // TODO: make this a vector to vectors 
    //
    // for page 0
    touchMedia0.push_back(5);
    touchMedia0.push_back(6);
    touchMedia0.push_back(7);
    touchMedia0.push_back(9);
    // for pages 1-3
    touchMedia1.push_back(1);
    touchMedia2.push_back(1);
    touchMedia3.push_back(1);
    //
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
            
            // TODO: HARDCODE EACH MEDIA ELEMENT THAT NEEDS TO FADE OUT OR PLAY ON TOUCH
                
            if (pageNum_in == 0){
                
                if (touchId_in != currentTouch && touchActive == false){
                    // Fade out elements that are in the way
                    for (int i=0; i < touchMedia0.size(); i++){
                        media.at(touchMedia0[i])->img.fadeOut();
                        media.at(touchMedia0[i])->vid.fadeOut();
                    }

                    // Left touch sensor pressed
                    if (touchId_in == 'H'){
                        currentTouch = 'H';
                        activeMedia = 12;
                    }
                    // Right touch sensor pressed
                    else if (touchId_in == 'J') {
                        currentTouch = 'J';
                        activeMedia = 13;
                    }
                    
                    // Error catching in case hardcoded activeMedia from XML file are invalid
                    try {
                        touchActive = true;
                        media.at(activeMedia)->playVid();
                        media.at(activeMedia)->vid.fadeIn();
                    } catch (...) {
                        touchActive = false;
                        ofLogError() << "Error playing media number " << activeMedia << " on page " << pageNum_in;
                    }
                    
                }
                
                // QUESTION: Should this go in the update loop instead?
                if (touchActive){
                    if (currentTouch == 'H' || currentTouch == 'J' || currentTouch == 'R'){
                        
                        int currentFrame = media.at(activeMedia)->vid.getCurrentFrame();
                        int lastFrame = media.at(activeMedia)->vid.getTotalNumFrames();
                        
                        if (currentFrame == lastFrame){
                            media.at(activeMedia)->vid.fadeOut();
                            media.at(activeMedia)->pauseVid();
                            media.at(activeMedia)->vidState = 0;
                            
                            for (int i=0; i < touchMedia0.size(); i++){
                                media.at(touchMedia0[i])->img.fadeIn();
                                media.at(touchMedia0[i])->vid.fadeIn();
                            }
                            touchActive = false;
                            currentTouch = 'R';
                        }
             
                }
            } else if (pageNum_in == 1){

                
            
            
            } else if (pageNum_in == 2){
                
               
            
            
            } else if (pageNum_in == 3){
                
              
            
            }
        }

    currentTouch = touchId_in;
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



