#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    testImg.setup("poison.jpg", 0.0f, 0.0f);
    testVid.setup("poison.jpg", "poisonVid.mp4", 0.0f, 300.0f);
    
    ofSetFrameRate(60.0f);


}

//--------------------------------------------------------------
void testApp::update(){
    
    testImg.update();
    testVid.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    
    testImg.draw();
    testVid.draw();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 500, 500);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    
    testVid.tap();
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}