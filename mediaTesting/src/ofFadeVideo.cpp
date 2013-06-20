//
//  ofFadeVideo.cpp
//  mediaTesting
//
//  Created by Tom Arthur on 6/20/13.
//
//

#include "ofFadeVideo.h"

void ofFadeVid::setup(string filename_in){
    setPixelFormat(OF_PIXELS_RGBA);
    ofEnableAlphaBlending();
    alpha = 0.0f;
    alphaDest = 1.0f;
    loadMovie(filename_in);
}

void ofFadeVid::update(){

    alpha += (alphaDest-alpha)/8.0f;
    ofLog(OF_LOG_NOTICE) << "the alphavid dest is " << alphaDest;
    ofVideoPlayer::update();
}

void ofFadeVid::draw(){
    ofVideoPlayer::draw(0,0);
}

void ofFadeVid::draw(int x_in, int y_in){
    
    float myscale = (alpha - 1.0f)/(-2.0f)+1.0f;
    
    if(alpha>0.05){
        ofSetColor(255,255,255,alpha*255);
        ofVideoPlayer::draw(x_in, y_in,myscale*getWidth(),myscale*getHeight());
    }
}

void ofFadeVid::draw(int x_in, int y_in, int w_in, int h_in){
    ofPoint centerPoint = ofPoint(x_in+w_in/2.0f, y_in+h_in/2.0f);
    
    float myscale = (alpha - 1.0f)/(-16.0f)+1.0f;
    float wOffset = 0.5f*myscale*w_in;
    float hOffset = 0.5f*myscale*h_in;
    if(alpha>0.05){
        ofSetColor(255,255,255,alpha*255);
        ofPushMatrix();
        ofTranslate(centerPoint);
        ofVideoPlayer::play();
        ofVideoPlayer::draw(x_in-wOffset, y_in-hOffset, w_in*myscale, h_in*myscale);
        ofPopMatrix();
    }
} 


void ofFadeVid::fadeIn(){
    alphaDest = 1.0f;
}
void ofFadeVid::fadeOut(){
    alphaDest =  1.0f;
}
