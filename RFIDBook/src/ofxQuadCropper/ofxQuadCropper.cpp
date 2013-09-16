//
//  ofxQuadCropper.cpp
//  QuadCropperApp
//
//  Created by Cameron Browning on 9/16/13.
//
//

#include "ofxQuadCropper.h"

ofxQuadCropper::ofxQuadCropper(){
    for(int i=0;i<NUM_POINTS;i++){
        points[i] = ofPoint();
    }
    nearestPoint = -1;
    selectedPoint = -1;
    isDragging = false;
    reset();
    isActive = false;
}
ofxQuadCropper::~ofxQuadCropper(){
    
}

void ofxQuadCropper::setup(int _screenW, int _screenH){
    screenW = _screenW;
    screenH = _screenH;
}
void ofxQuadCropper::update(){

}
void ofxQuadCropper::draw(int _screenW, int _screenH){
    
    
    ofSetColor(0,0,0);
    ofFill();
    ofBeginShape();
    ofVertex(0,0);
    ofVertex(points[0].x*_screenW,points[0].y*_screenH);
    ofVertex(points[1].x*_screenW,points[1].y*_screenH);
    ofVertex(_screenW,0);
    ofEndShape();
    ofBeginShape();
    ofVertex(_screenW,0);
    ofVertex(points[1].x*_screenW,points[1].y*_screenH);
    ofVertex(points[2].x*_screenW,points[2].y*_screenH);
    ofVertex(_screenW,_screenH);
    ofEndShape();
    ofBeginShape();
    ofVertex(_screenW,_screenH);
    ofVertex(points[2].x*_screenW,points[2].y*_screenH);
    ofVertex(points[3].x*_screenW,points[3].y*_screenH);
    ofVertex(0,_screenH);
    ofEndShape();
    ofBeginShape();
    ofVertex(0,_screenH);
    ofVertex(points[3].x*_screenW,points[3].y*_screenH);
    ofVertex(points[0].x*_screenW,points[0].y*_screenH);
    ofVertex(0,0);
    ofEndShape();
    
    if(isActive){
        for(int i=0;i<NUM_POINTS;i++){
            if(i==selectedPoint){
                ofSetColor(255,0,0);
            } else {
                ofSetColor(255,255,255);
            }
            ofCircle(points[i].x*_screenW,points[i].y*_screenH,10);
        }
        ofBeginShape();
        ofNoFill();
        ofSetColor(255,255,255);
        for(int i=0;i<NUM_POINTS;i++){
            ofVertex(points[i].x*_screenW,points[i].y*_screenH);
        }
        ofEndShape();
    }
    
    
}
void ofxQuadCropper::draw(){
    draw(screenW,screenH);
    
}

int ofxQuadCropper::loadFromFile(string _file){
    if(xml.loadFile(_file)){
        ofLogNotice() << _file << " loaded successfully.";
        
        xml.pushTag("quad");
        int numPoints = xml.getNumTags("pt");
        ofLogNotice() << numPoints << " points loaded.";
        
        int maxLoop = MIN(numPoints,NUM_POINTS);
        for(int i=0;i<maxLoop;i++){
            ofPoint * thisPoint = &points[i];
            
            float thisX = xml.getAttribute("pt","x",0.0f,i);
            float thisY = xml.getAttribute("pt","y",0.0f,i);
            
            points[i].set(thisX,thisY);
            
            ofLogNotice() << "loaded a point at: " << thisX << ", " << thisY;
            
        }
        
        
        xml.popTag();
        return 0;
    } else {
        ofLogWarning() << _file << " didn't load successfully.";
        return -1;
    }
    
}

void ofxQuadCropper::report(){
    for(int i=0;i<NUM_POINTS;i++){
        ofLogNotice() << points[i].x << "," << points[i].y;
    }
    ofLogNotice() << "selected: " << selectedPoint;
}

int ofxQuadCropper::saveToFile(string _file){
    updateXmlObject();
    xml.saveFile(_file);
    ofLogNotice()<< "saving " << _file;
    return 0;
    // TODO: check for errors in this and return -1;
}

void ofxQuadCropper::updateXmlObject(){
    ofxXmlSettings newXml;
    newXml.addTag("quad");
    newXml.pushTag("quad");
    for(int i=0;i<NUM_POINTS;i++){
        newXml.addTag("pt");
        newXml.setAttribute("pt","x",points[i].x,i);
        newXml.setAttribute("pt","y",points[i].y,i);
    }
    xml = newXml;
}

void ofxQuadCropper::randomize(){
    // helper script for testing
    for(int i=0;i<NUM_POINTS;i++){
        points[i].x = ofRandom(0.0f,1.0f);
        points[i].y = ofRandom(0.0f,1.0f);
    }
}
void ofxQuadCropper::reset(){
    ofLogNotice() << "resetting quad.";
    points[0].set(0,0);
    points[1].set(1.0f,0);
    points[2].set(1.0f,1.0f);
    points[3].set(0.0f,1.0f);
}

int ofxQuadCropper::getNearest(ofPoint _mousePos){
    float rolloverThreshold = 200;
    
    float nearestDist = rolloverThreshold;
    int whichSelected = -1;
    
    for(int i=0;i<NUM_POINTS;i++){
        float thisDist = ofDist(_mousePos.x,_mousePos.y,points[i].x*screenW,points[i].y*screenH);
        if (thisDist<nearestDist){
            nearestDist = thisDist;
            whichSelected = i;
            
        }
    }
    return whichSelected;
}

void ofxQuadCropper::mouseMoved(int _x, int _y){
   if(isActive) selectedPoint = getNearest(ofPoint(_x,_y));
   // ofLogNotice() << "mouseMoved";
    
}
void ofxQuadCropper::mousePressed(int _x, int _y){
   if(isActive) isDragging = true;
     //   ofLogNotice() << "mousePressed";
}
void ofxQuadCropper::mouseDragged(int _x, int _y){
    if(isActive){
    if(selectedPoint>-1){
        float newX = (float)_x / (float) screenW;
        float newY = (float)_y / (float) screenH;
        points[selectedPoint].set(newX,newY);
    }
    }
     //   ofLogNotice() << "mouseDragged";
}
void ofxQuadCropper::mouseReleased(int _x, int _y){
    selectedPoint = -1;
  //  ofLogNotice() << "mouseReleased";
}

bool ofxQuadCropper::getActive(){
    return isActive;
}
int ofxQuadCropper::activate(){
    if(isActive){
        return -1;
    } else {
        isActive = true;
        return 0;
    }
}
int ofxQuadCropper::deactivate(){
    if(!isActive){
        return -1;
    } else {
        isActive = false;
        return 0;
    }
}

int ofxQuadCropper::showDragUI(){
    return activate();
}

int ofxQuadCropper::hideDragUI(){
    return deactivate();
}


