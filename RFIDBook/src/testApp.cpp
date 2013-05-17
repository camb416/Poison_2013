#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    devices.setup();
        devices.startThread(true,false);
    
    book.setup(&devices);
   // rfidsetup();
    tfield.setup();
    tfield.update("Magic Book", 16,360);
    debugState = 1;
    
    aValue = 0.5f;
    bar.setup("Page Confidence", &aValue, 600, 16);
    bar.setPosition(ofPoint(16,749));

    
    
    
}

//--------------------------------------------------------------
void testApp::update(){

  //  devices.report();

    devices.update();
    bar.update();
    if(book.isPageLanded()){
        // checks for three sensors active.
    }
    
    if(debugState>0){
        tfield.update("Magic Book \n" + book.getReport());
        if(ofGetMousePressed()){
            pos_ui.update();
            aValue = ofRandom(1.0f);
        }
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    if(debugState>0){
    devices.draw();
        tfield.draw();
        bar.draw();
        if(ofGetMousePressed()) pos_ui.draw();
        
    }
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