//
//  ofFadeImage.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#include "ofFadeImage.h"

void ofFadeImage::setup(string filename_in){
    alpha = 0.0f;
    alphaDest = 1.0f;
    loadImage(filename_in);
}
void ofFadeImage::update(){
    alpha += (alphaDest-alpha)/8.0f;
}
void ofFadeImage::draw(){
    if(alpha>0.05){
        ofSetColor(255,255,255,alpha*255);
        ofImage::draw(0,0,160,120);
    }
}
void ofFadeImage::fadeIn(){
    alphaDest = 1.0f;
}
void ofFadeImage::fadeOut(){
    alphaDest = 0.0f;
}
