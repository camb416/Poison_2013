//
//  PositionUI.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/17/13.
//
//

#ifndef __RFIDBook__PositionUI__
#define __RFIDBook__PositionUI__


#include "ofMain.h"
#include "TextField.h"
#include <iostream>

class PositionUI{

public:
    PositionUI();
    ~PositionUI();
    void draw();
    void update();
    
private:
    TextField field;
};
#endif /* defined(__RFIDBook__PositionUI__) */
