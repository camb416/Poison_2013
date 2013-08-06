//
//  TouchButton.cpp
//  ButtonTesting
//
//  Created by Brett Peterson on 8/6/13.
//
//

#include "TouchButton.h"


TouchButton::TouchButton(){
    
}

void TouchButton::setup(string _active, string _inactive, long _timeout, int _x, int _y){
    
    activeImg.loadImage(_active);
    inactiveImg.loadImage(_inactive);
    timeout = _timeout;
    x = _x;
    y = _y;
    width = activeImg.getWidth();
    height = activeImg.getHeight();
    
    // set state to active
    state = ACTIVE;
    lastPressed = 0;
    
}

void TouchButton::update(){
    // check state
    if (state == INACTIVE) {
        long currTime = ofGetElapsedTimeMillis();
        
        if (currTime >= lastPressed + timeout){
            state = ACTIVE;
        }
    }
}

void TouchButton::draw(){
    //check state
    if (state == ACTIVE) {
        activeImg.draw(x, y);
    }
    else {
        inactiveImg.draw(x,y);
    }
	// draw according to state
    
}

void TouchButton::press(){
    // change state to inactive
    // record last pressed
    if (state == ACTIVE){
        state = INACTIVE;
        lastPressed = ofGetElapsedTimeMillis();
    }
    
   
    
}