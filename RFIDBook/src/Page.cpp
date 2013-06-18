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
Page::~Page(){}

void Page::setup(){
    
    validInputs.push_back('A');
    validInputs.push_back('B');
    validInputs.push_back('C');
    validInputs.push_back('D');
    
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
        // cout << this;
        ofPoint mousePos = ofPoint(ofGetMouseX(),ofGetMouseY());
        float nearestDist = 99999;
        int nearestID = -1;
        for (int i = 0; i < media.size(); i++) {
            ofPoint thisOrigin = media.at(i)->getPosition();
           // cout << thisOrigin.x << ", " << thisOrigin.y << endl;
            float thisDist = ofDist(thisOrigin.x,thisOrigin.y,mousePos.x,mousePos.y);
           // cout << "this dist is: " << thisDist << endl;
            if(thisDist<nearestDist){
                nearestID = i;
                nearestDist = thisDist;
            }
            media.at(i)->setDraggable(false);
        }
       // cout << "nearest dist is: " << nearestDist << endl;
        if(nearestID>-1){
            media.at(nearestID)->setDraggable(true);
            selectedMedia = media.at(nearestID);
        }
    } else {
      //  cout << "I am dragging now." << endl;
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

void Page::addMedia(string fileName, ofVec2f position){
    
    Media * newMedia = new Media();
    
    string sub = fileName.substr(fileName.length()-3,3);
    if (sub == "png") {
        
        // run the setup for a media element that is just an image
        newMedia->setup(fileName, position.x, position.y);
        
    }
    else if (sub == "mov"){
        
        // Run the setup for a media element that is a video and an image
        string imageFile = fileName.replace(fileName.length() -3, 3, "png");
        newMedia->setup(imageFile, fileName, position.x, position.y);
        
    }
    else {
        
        ofLogNotice() << "unrecognized media file extension: " << fileName;
    
    }
    
    media.push_back(newMedia);
    ofLogNotice() << "Added new media element " << fileName << " to page at position " << position.x << "," << position.y;
    
}

void Page::receiveInput(char input ){

    int position = -1;
    
    // Look for character in valid inputs vector
    for (int i = 0; i < validInputs.size(); i++) {

        if (validInputs.at(i) == input){
            position = i;
        }
    }
    
    // If the input character is found, send the touch event to the corresponding media object
    if (position != -1){
        media.at(position)->playPause();
    }
    else {
        std::cout << "no media element found for character " << input;
    }

}

void Page::fade(int dir){
    
    // Loop through media elements and fade them in or out
    // TODO - add the randomized load in here
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
        }
    }
    else {
        for (int i = 0; i < media.size(); i++) {
            // TODO - handle video fade in as well
           
            float fadeVal = ofRandomuf()*(maxFadeOut-minFadeOut)+minFadeOut;
            // cout << fadeVal << endl;
            media.at(i)->img.fadeOut(fadeVal);
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
        
        
    }
    return xml;
}



