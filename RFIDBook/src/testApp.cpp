#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    devices.setup();
        devices.startThread(true,false);
   // rfidsetup();
}

//--------------------------------------------------------------
void testApp::update(){
// test
   // devices.lock();
    
    devices.report();
    
   // devices.unlock();
    devices.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    devices.draw();
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