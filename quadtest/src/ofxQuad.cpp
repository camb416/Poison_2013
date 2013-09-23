//
//  ofxQuad.cpp
//  QuadCropperApp
//
//  Created by Cameron Browning on 9/16/13.
//
//

#include "ofxQuad.h"

ofxQuad::ofxQuad(){
    for(int i=0;i<NUM_POINTS;i++){
        points[i] = ofPoint();
    }
    nearestPoint = -1;
    selectedPoint = -1;
    isDragging = false;
    
    isActive = false;
    pos.set(0,0);
    bAlign = false;
    contextDimensions.set(640,480);
    reset();
}
ofxQuad::~ofxQuad(){
    
}

void ofxQuad::setup(){
    reset();
}

void ofxQuad::setup(int _contextW, int _contextH){
    contextDimensions.set(_contextW,_contextH);

}
/*
void ofxQuad::setup(int _x, int _y, int _width, int _height){
    pos.set(_x, _y);
    size.set(_width,_height);
}
*/
void ofxQuad::update(){
    points[4] = getCenter();
}
/*
void ofxQuad::draw(ofPoint _pos, ofPoint _size){
    if(isActive){
        for(int i=0;i<NUM_POINTS;i++){
            if(i==selectedPoint){
                ofSetColor(255,0,0);
            } else {
                ofSetColor(255,255,255);
            }
            ofCircle(points[i].x*_size.x+_pos.x,points[i].y*_size.y+_pos.y,10);
        }
        ofBeginShape();
        ofNoFill();
        ofSetColor(255,255,255);
        for(int i=0;i<NUM_POINTS;i++){
            ofVertex(points[i].x*_size.x+_pos.x,points[i].y*_size.y+_pos.y);
        }
        ofEndShape(OF_CLOSE);
    }
}

void ofxQuad::draw(int _width, int _height){
    
    
}
*/
void ofxQuad::draw(){

    if(isActive){
        for(int i=0;i<NUM_POINTS;i++){
            if(i==selectedPoint){
                ofSetColor(255,0,0);
            } else {
                ofSetColor(255,255,255);
            }
            ofCircle(points[i].x*contextDimensions.x,points[i].y*contextDimensions.y,10);
        }
        ofBeginShape();
        ofNoFill();
        ofSetColor(255,255,255);
        for(int i=0;i<4;i++){
            ofVertex(points[i].x*contextDimensions.x,points[i].y*contextDimensions.y);
        }
        ofEndShape(OF_CLOSE);
    }
    
}

int ofxQuad::loadFromFile(string _file){
    //TODO: error checking here. Not enough points in XML crashes it.
    try{
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
    } catch(exception e){
        ofLogWarning() << "caught an exception when loading XML.";
        return -1;
    }
    
}

void ofxQuad::report(){
    for(int i=0;i<NUM_POINTS;i++){
        ofLogNotice() << points[i].x << "," << points[i].y;
    }
    ofLogNotice() << "selected: " << selectedPoint;
}



int ofxQuad::saveToFile(string _file){
    updateXmlObject();
    string message;
    xml.copyXmlToString(message);
    ofLogNotice() << message;
    
    xml.saveFile(_file);
    ofLogNotice()<< "saving " << _file;
    return 0;
    // TODO: check for errors in this and return -1;
}

void ofxQuad::updateXmlObject(){
    ofxXmlSettings newXml;
    newXml.addTag("quad");
    newXml.pushTag("quad");
    for(int i=0;i<4;i++){
        newXml.addTag("pt");
        newXml.setAttribute("pt","x",points[i].x,i);
        newXml.setAttribute("pt","y",points[i].y,i);
    }
    xml = newXml;
}

void ofxQuad::randomize(){
    // helper script for testing
    for(int i=0;i<NUM_POINTS;i++){
        points[i].x = ofRandom(0.0f,1.0f);
        points[i].y = ofRandom(0.0f,1.0f);
    }
}
void ofxQuad::reset(){
    ofLogNotice() << "resetting quad.";
    points[0].set(0.0f,0.0f);
    points[1].set(1.0f,0.0f);
    points[2].set(1.0f,1.0f);
    points[3].set(0.0f,1.0f);
    points[4].set(0.5f,0.5f);
}

int ofxQuad::getNearest(ofPoint _mousePos){
    float rolloverThreshold =20;
    
    float nearestDist = rolloverThreshold;
    int whichSelected = -1;
    
    for(int i=0;i<NUM_POINTS;i++){
        float thisDist = ofDist(_mousePos.x,_mousePos.y,points[i].x*contextDimensions.x,points[i].y*contextDimensions.y);
        if (thisDist<nearestDist){
            nearestDist = thisDist;
            whichSelected = i;
            
        }
    }
    return whichSelected;
}

void ofxQuad::setAlign(bool _align){
    bAlign = _align;
}
bool ofxQuad::getAlign(){
    return bAlign;
}

void ofxQuad::mouseMoved(int _x, int _y){
    if(isActive) selectedPoint = getNearest(ofPoint(_x,_y));
    // ofLogNotice() << "mouseMoved";
    
}
void ofxQuad::mousePressed(int _x, int _y){
    if(isActive) isDragging = true;
    //   ofLogNotice() << "mousePressed";
}
void ofxQuad::mouseDragged(int _x, int _y){
    if(isActive){
        if(selectedPoint>-1){
            float newX = ((float)_x)/ (float) contextDimensions.x;
            float newY = ((float)_y)/ (float) contextDimensions.y;
            ofPoint translation;
            translation.set(newX - points[selectedPoint].x, newY - points[selectedPoint].y);
            
            
            points[selectedPoint].set(newX,newY);
            
            if(bAlign){
                switch(selectedPoint){
                    case 0:
                        points[3].x = newX;
                        points[1].y = newY;
                        break;
                    case 1:
                        points[2].x = newX;
                        points[0].y = newY;
                        break;
                    case 2:
                        points[1].x = newX;
                        points[3].y = newY;
                        break;
                    case 3:
                        points[0].x = newX;
                        points[2].y = newY;
                        break;
                }
            }
            if(selectedPoint==4){
                // dragging the center;
                
                for(int i=0;i<4;i++){
                    points[i] += translation;
                }
                /*
                points[0].x = points[4].x-0.5f*getPctWidth();
                points[0].y = points[4].y-0.5f*getPctHeight();
                
                points[1].x = points[4].x+0.5f*getPctWidth();
                points[1].y = points[4].y-0.5f*getPctHeight();
                
                points[2].x = points[4].x+0.5f*getPctWidth();
                points[2].y = points[4].y+0.5f*getPctHeight();
                
                points[3].x = points[4].x-0.5f*getPctWidth();
                points[3].y = points[4].y+0.5f*getPctHeight();
                */
                
            }
            
        }
    }
    //   ofLogNotice() << "mouseDragged";
}
void ofxQuad::mouseReleased(int _x, int _y){
    selectedPoint = -1;
}

bool ofxQuad::getActive(){
    return isActive;
}
int ofxQuad::activate(){
    if(isActive){
        return -1;
    } else {
        isActive = true;
        return 0;
    }
}
int ofxQuad::deactivate(){
    if(!isActive){
        return -1;
    } else {
        isActive = false;
        return 0;
    }
}

int ofxQuad::showDragUI(){
    return activate();
}

int ofxQuad::hideDragUI(){
    return deactivate();
}

ofPoint ofxQuad::getTopLeft(){
    ofPoint topLeft;
    topLeft.set(points[0].x*contextDimensions.x,points[0].y*contextDimensions.y);
    return topLeft;
}
ofPoint ofxQuad::getSize(){

    ofPoint mySize;
    
    mySize.x = points[2].x-points[0].x;
    mySize.y = points[2].y - points[0].y;
    //mySize *= contextDimensions;
    
    return mySize;
    /*
    float largestX = -999.99f;
    int whichPoint = -1;
    for(int i=0;i<NUM_POINTS;i++){
        if(points[i].x>largestX){
            whichPoint = i;
            largestX = points[i].x;
        }
    }
    if(whichPoint>-1 && whichPoint<NUM_POINTS){
        return points[whichPoint];
    } else {
        ofPoint dummyVal;
        ofLogWarning() << "something is failing in ofxQuad::getSize()";
        return dummyVal;
    }*/
}


float ofxQuad::getPctWidth(){
    return getSize().x;
}
float ofxQuad::getPctHeight(){
    return getSize().y;
}


float ofxQuad::getWidth(){
    return getSize().x*contextDimensions.x;
}
float ofxQuad::getHeight(){
    return getSize().y*contextDimensions.y;
}
ofPoint ofxQuad::getCenter(){
    ofPoint returnVal;
    returnVal = (points[2]-points[0])/2+points[0];
    return returnVal;
}
