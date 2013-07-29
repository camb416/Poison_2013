#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){
    
    vid.update();
    int currentTime = ofGetElapsedTimeMillis() / 1000;
}

//--------------------------------------------------------------
void testApp::draw(){
    
    vid.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    // toggle looping stage
    if (key == '1'){
        vid.touch();
    }

}