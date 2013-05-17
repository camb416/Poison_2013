//
//  BarGraph.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/17/13.
//
//

#ifndef __RFIDBook__BarGraph__
#define __RFIDBook__BarGraph__
#include "ofMain.h"
#include "TextField.h"
#include <iostream>
class BarGraph{
public:
    BarGraph();
    ~BarGraph();
    void setup(string label_in, float * value_ptr_in, float multiplier_in, int thickness);
    void setPosition(ofPoint pos_in);
    void update();
    void draw();
    
private:
    ofPoint pos;
    int thickness;
    float multiplier;
    string label;
    float * value_ptr;
    TextField tfield;
    float barWidth;
    float tweenVal;
};

#endif /* defined(__RFIDBook__BarGraph__) */
