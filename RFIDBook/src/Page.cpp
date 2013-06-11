//
//  Page.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/10/13.
//
//

#include "Page.h"

Page::Page(){}
Page::~Page(){}

void Page::setup(){
    
    validInputs.push_back('A');
    validInputs.push_back('B');
    validInputs.push_back('C');
    validInputs.push_back('D');
    
}

void Page::update(){
    
}

void Page::draw(){
    
}

void Page::addMedia(string fileName, ofVec2f position){
    
    Media newMedia;
    
    string sub = fileName.substr(fileName.length()-3,3);
    if (sub == "png") {
        
        // run the setup for a media element that is just an image
        newMedia.setup(fileName, position.x, position.y);
        
    }
    else if (sub == "mov"){
        
        // Run the setup for a media element that is a video and an image
        string imageFile = fileName.replace(fileName.length() -3, 3, "png");
        newMedia.setup(imageFile, fileName, position.x, position.y);
        
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
        media.at(position).playPause();
    }
    else {
        std::cout << "no media element found for character " << input;
    }

}




