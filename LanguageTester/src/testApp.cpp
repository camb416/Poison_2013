#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    lang.load();
    
    // try this (seems to work)
    lang.toggleLanguage();
    lang.toggleLanguage();

    // then this... (seems to work)
    lang.setLanguage("fr");
    lang.setLanguage("en");
    
    cout << "myImage.jpg: " << lang.resolvePath("myImage.jpg") << endl;
    cout << "subdir/myImage.jpg: " << lang.resolvePath("subdir/myImage.jpg") << endl;

    img.loadImage(lang.resolvePath("assets/testImage.png"));

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    img.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    lang.setLanguage("en");
    img.loadImage(lang.resolvePath("assets/testImage.png"));
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
    lang.toggleLanguage();
    img.loadImage(lang.resolvePath("assets/testImage.png"));
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