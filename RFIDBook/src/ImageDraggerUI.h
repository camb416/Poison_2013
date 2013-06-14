//
//  ImageDraggerUI.h
//  RFIDBook
//
//  Created by Cameron Browning on 6/14/13.
//
//

#ifndef __RFIDBook__ImageDraggerUI__
#define __RFIDBook__ImageDraggerUI__

#include "ofMain.h"
#include "Media.h"
#include <iostream>

class ImageDraggerUI{
  
    
public:
    ImageDraggerUI();
    ~ImageDraggerUI();
    void setup();
    void update();
    void draw();
    void registerElements(vector<ofPoint> points);
    void deregisterElements();

};

#endif /* defined(__RFIDBook__ImageDraggerUI__) */
