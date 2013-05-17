//
//  BarGraph.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/17/13.
//
//

#include "BarGraph.h"
BarGraph::BarGraph(){}
BarGraph::~BarGraph(){}

void BarGraph::setup(string label_in, float * value_ptr_in, float multiplier_in,int thickness_in){
    label = label_in;
    value_ptr = value_ptr_in;
    thickness = thickness_in;
    tfield.setup(12);
    multiplier = multiplier_in;
    tfield.update(label);
    
}
void BarGraph::setPosition(ofPoint pos_in){
    pos = pos_in;
}
void BarGraph::update(){
    barWidth = multiplier * (*value_ptr);
}
void BarGraph::draw(){
    ofSetColor(0);
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    tfield.draw();
    ofRect(0,0,barWidth,thickness);
    ofPopMatrix();
}