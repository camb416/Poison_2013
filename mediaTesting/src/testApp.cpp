#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    testImg.setup("poison.jpg", 0.0f, 0.0f);
    testVid.setup("skull.png", "skull.mov", 0.0f, 300.0f);
    
    testSlide.setup("perry.png");
    
    visable = true;
    testSlide.tweenSlide('L', 1000.0f, visable);
    ofSetFrameRate(60.0f);


}

//--------------------------------------------------------------
void testApp::update(){
    
    testImg.update();
    testVid.update();
    
    testSlide.update();


}

//--------------------------------------------------------------
void testApp::draw(){
    
    testImg.draw();
    testVid.draw();
    testSlide.tweenSlideDraw(600, 0);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key){
        case 'a':
        case 'A':
            visable = !visable;
            testSlide.tweenSlide('L', 1000.0f, visable);
            break;
        case 'b':
        case 'B':
            break;
    }
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