//
//  TextField.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/17/13.
//
//

#include "TextField.h"
TextField::TextField(){
// constructor
    text = "";
    pos = ofPoint(0,0);
}
TextField::~TextField(){
    // destructor
}
void TextField::setup(int fontsize){
    font.loadFont("fonts/Avenir.ttc",fontsize);
}
void TextField::update(string text_in){
    text = text_in;
}
void TextField::update(string text_in, int x_in, int y_in){
    pos.x = x_in;
    pos.y = y_in;
    text = text_in;
}
void TextField::setPosition(ofPoint pos_in){
    pos = pos_in;
}
void TextField::setPosition(int x_in, int y_in){
    pos.x = x_in;
    pos.y = y_in;
}

void TextField::draw(int x_in, int y_in){
    ofSetColor(0);
    font.drawString(text,x_in, y_in);
}
void TextField::draw(){
    draw(pos.x,pos.y);
}
float TextField::getWidth(){
    return font.stringWidth(text);
}
float TextField::getHeight(){
    return font.stringHeight(text);
}
