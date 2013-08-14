//
//  ofFadeImage.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#include "ofFadeImage.h"

ofFadeImage::ofFadeImage(){
    pulseType = 0;
    showBorder = false;
    tweenDivisor = 8.0f;
    pulseOrigin = ofRandomuf()*TWO_PI;
}

void ofFadeImage::setBorder(bool _showBorder){
    showBorder = _showBorder;
}

void ofFadeImage::setup(string filename_in){
    alpha = 0.0f;
    alphaDest = 1.0f;
    loadImage(filename_in);
    setAnchorPercent(0.5f, 0.5f);
    path = filename_in;
}
void ofFadeImage::update(){
    if(pulseType>0){
        pulseVal = pulseOrigin+ofGetElapsedTimef()*2.0f;
        
    } else {
        pulseVal = 0.0f;
    }
    alpha += (alphaDest-alpha)/tweenDivisor;
}
void ofFadeImage::draw(){
    draw(0,0);
}
void ofFadeImage::draw(int x_in, int y_in){
    
    float myscale = (alpha - 1.0f)/(-2.0f)+1.0f+sin(pulseVal)*2.0f;
    
    if(alpha>0.05){
        ofSetColor(255,255,255,alpha*255);
        //ofSetColor(0,0,0,alpha*255);
        ofImage::draw(x_in, y_in,myscale*getWidth(),myscale*getHeight());
    }
    if(showBorder){
        ofSetColor(255,0,0,alpha*255);
        ofNoFill();
        ofRect(x_in, y_in, myscale*getWidth(), myscale*getHeight());
        ofFill();
        ofSetColor(0,0,0);
        ofRect(x_in, y_in, myscale*getWidth(), myscale*getHeight());
        ofDrawBitmapString(path,x_in,y_in);
    }
}
void ofFadeImage::draw(int x_in, int y_in, int w_in, int h_in){
//    ofPoint centerPoint = ofPoint(x_in+w_in/2.0f, y_in+h_in/2.0f);
    
    float myscaleX, myscaleY;
    
    // if pulsetype is 1 or 2, do the throbbing
    switch(pulseType){
    
        case 1:
        case 2:
            myscaleX = (alpha - 1.0f)/(-16.0f)+1.0f+sin(pulseVal)*0.05f;
            myscaleY = (alpha - 1.0f)/(-16.0f)+1.0f+cos(pulseVal)*0.05f;
            break;
        default:
            myscaleX = myscaleY = (alpha - 1.0f)/(-16.0f)+1.0f;
            break;
            
    }
    float wOffset = 0.5f*myscaleX*w_in;
    float hOffset = 0.5f*myscaleY*h_in;
    if(alpha>0.05){
        switch(pulseType){
            case 2:
            case 3:
                ofSetColor(255,255,255,(alpha*(sin(pulseVal)*0.33f+0.5f))*255.0f);
                break;
            default:
                ofSetColor(255,255,255,alpha*255);
                break;
        }
        
       
        // ofSetColor(0,0,0,alpha*255);
        ofPushMatrix();
        //ofTranslate(centerPoint);
        ofImage::draw(x_in, y_in, w_in*myscaleX, h_in*myscaleY);
        if(showBorder){
            ofSetColor(255,0,0,alpha*255);
            ofNoFill();
            ofRect(x_in-wOffset, y_in-hOffset, w_in*myscaleX, h_in*myscaleY);
            ofLine(x_in-wOffset, y_in-hOffset, x_in-wOffset+w_in*myscaleX,  y_in-hOffset + h_in*myscaleY);
            ofLine(x_in+wOffset, y_in-hOffset, x_in+wOffset-w_in*myscaleX,  y_in-hOffset + h_in*myscaleY);
            ofFill();
            stringstream ss;
            ss << x_in << ", " << y_in << " : " << x_in-wOffset << " , " <<  y_in-hOffset;
            
            ofDrawBitmapString(ss.str(), x_in-wOffset, y_in-hOffset+20);
            //ofSetColor(0,0,0);
            //ofRect(x_in, y_in, myscale*getWidth(), myscale*getHeight());
            ofDrawBitmapString(path,x_in-wOffset, y_in-hOffset+40);

        }
        ofPopMatrix();
    }
    
} 
void ofFadeImage::fadeIn(float _tweenD){ // use -1 for immediate fade
    if(_tweenD<0.0f){
        alpha = alphaDest = 1.0f;
    } else {
    tweenDivisor = _tweenD;

    alphaDest = 1.0f;
    }
}


void ofFadeImage::fadeOut(float _tweenD){
    if(_tweenD<0.0f){
        alpha = alphaDest = 0.0f;
    } else {
        tweenDivisor = _tweenD;
        alphaDest = 0.0f;
    }
}

