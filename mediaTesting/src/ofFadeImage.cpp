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
    ofEnableAlphaBlending();
}

void ofFadeImage::update(){

    alpha += (alphaDest-alpha)/8.0f;
}

void ofFadeImage::draw(){
    draw(0,0);
}

void ofFadeImage::draw(int x_in, int y_in){

    float myscale = (alpha - 1.0f)/(-2.0f)+1.0f;
    
    if(alpha>0.05){
        ofSetColor(255,255,255,alpha*255);
        ofImage::draw(x_in, y_in,myscale*getWidth(),myscale*getHeight());
    }
}

void ofFadeImage::draw(int x_in, int y_in, int w_in, int h_in){
    ofPoint centerPoint = ofPoint(x_in+w_in/2.0f, y_in+h_in/2.0f);
    
    float myscale = (alpha - 1.0f)/(-16.0f)+1.0f;
    float wOffset = 0.5f*myscale*w_in;
    float hOffset = 0.5f*myscale*h_in;
    if(alpha>0.05){
        ofSetColor(255,255,255,alpha*255);
        ofPushMatrix();
        ofTranslate(centerPoint);
        ofImage::draw(x_in-wOffset, y_in-hOffset, w_in*myscale, h_in*myscale);
        ofPopMatrix();
    }
}

void ofFadeImage::tweenSlide(char direction_in, float duration_in, bool visable_in){
    
    if (visable_in == true){
        tweenslide.setParameters(easingcubic, ofxTween::easeIn, 0, getWidth(), duration_in, 0);
        tweenalpha.setParameters(easingcubic, ofxTween::easeIn, 0, 255, duration_in, 0);
    }
    else if (visable_in == false){
        tweenslide.setParameters(easingcubic, ofxTween::easeIn, getWidth(), 0, duration_in, 0);
        tweenalpha.setParameters(easingcubic, ofxTween::easeIn, 255, 0, duration_in, 0);
    }
    else {
        ofLog(OF_LOG_WARNING, "You're not doing this right");
    }

    
}

void ofFadeImage::tweenSlideDraw(int x_in, int y_in){
    
    ofSetColor(255,255,255,tweenalpha.update());
    ofImage::draw(x_in, y_in, tweenslide.update(), getHeight());
    
    
}

void ofFadeImage::fadeIn(){
    alphaDest = 1.0f;
}
void ofFadeImage::fadeOut(){
    alphaDest = 0.0f;
}
