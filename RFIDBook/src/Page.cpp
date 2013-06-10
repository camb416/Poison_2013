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




