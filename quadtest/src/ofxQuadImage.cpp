//
//  ofxQuadImage.cpp
//  quadtest
//
//  Created by Cameron Browning on 9/18/13.
//
//

#include "ofxQuadImage.h"

void ofxQuadImage::setup(int _w, int _h, string _filepath){
    imgPath = _filepath;
    ofxQuad::setup(_w,_h);
    load(imgPath);
}


void ofxQuadImage::load(string _filepath){
    img.loadImage(_filepath);
}

void ofxQuadImage::draw(){

    ofSetColor(255);
    ofEnableAlphaBlending();
    img.draw(getTopLeft().x,
             getTopLeft().y,
             getWidth(),
             getHeight()
             );

    ofxQuad::draw();

    
    
}