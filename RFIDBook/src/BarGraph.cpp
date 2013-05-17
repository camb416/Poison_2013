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
    tweenVal = 0.0f;
    
}
void BarGraph::setPosition(ofPoint pos_in){
    pos = pos_in;
}
void BarGraph::update(){
    tweenVal += ((*value_ptr)-tweenVal)/64.0f;
    barWidth = multiplier * tweenVal;
}
void BarGraph::draw(){
    ofSetColor(0);
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    tfield.draw();
    ofRect(tfield.getWidth()+12,0.5f*thickness-tfield.getHeight(),barWidth,thickness);
    ofSetColor(0, 0, 0, 32);
    ofRect(tfield.getWidth()+12,0.5f*thickness-tfield.getHeight(),multiplier,thickness);
    ofPopMatrix();
}