//
//  TouchButton.h
//  ButtonTesting
//
//  Created by Brett Peterson on 8/6/13.
//
//

#ifndef __ButtonTesting__TouchButton__
#define __ButtonTesting__TouchButton__

#include <iostream>
#include "ofMain.h"

#define ACTIVE 1
#define INACTIVE 0


class TouchButton {
    
public:
    
    TouchButton();
    void setup(string _active, string _inactive, long _timeout, int _x, int _y);
    void update();
    void draw();
    void press();
    int x,y;
    int width,height;
    
private:
    ofImage activeImg;
    ofImage inactiveImg;
    long lastPressed;
    long timeout;
    bool state;
    

};

#endif /* defined(__ButtonTesting__TouchButton__) */

