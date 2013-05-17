//
//  PositionUI.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/17/13.
//
//

#include "PositionUI.h"
PositionUI::PositionUI(){
    field.setup(12);
}
PositionUI::~PositionUI(){
    
}
void PositionUI::update(){
    stringstream ss;
    ss << ofGetMouseX() << ", " << ofGetMouseY();
    field.update(ss.str());
}
void PositionUI::draw(){
    ofPushMatrix();
    ofPoint pos = ofPoint(ofGetMouseX()+32,ofGetMouseY()+16);
    ofTranslate(pos);
    ofSetColor(255);
    field.draw();
    ofPopMatrix();
}