//
//  ButtonController.h
//  buttonTesting
//
//  Created by Brett Peterson on 8/6/13.
//
//

#ifndef __buttonTesting__ButtonController__
#define __buttonTesting__ButtonController__

#include <iostream>
#include "TouchButton.h"
#include "ofMain.h"


class ButtonController {
    
public:
    
    ButtonController();
    void setup();
    void update();
    void draw();
    void touch(int _x, int _y);
    
    
private:
    
    vector<TouchButton> buttons;
    int padding = 10;   // forgiving close button presses
    
    
};





#endif /* defined(__buttonTesting__ButtonController__) */
