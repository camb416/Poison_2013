#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    devices.setup();
        devices.startThread(true,false);
    
    book.setup(&devices);
   // rfidsetup();
}

//--------------------------------------------------------------
void testApp::update(){

  //  devices.report();

    devices.update();
    
    if(book.isPageLanded()){
        // checks for three sensors active.
    }

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