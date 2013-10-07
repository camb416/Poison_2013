#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
   
    cropper.setup(1024,768);
    if(cropper.loadFromFile("quad.xml")!=0){
        cropper.saveToFile("quad.xml");
        cropper.loadFromFile("quad.xml");
    }
    cropper.activate();
    
    
    
    genericQuad.setup();
   
    if(genericQuad.loadFromFile("quad2.xml")!=0){
        genericQuad.saveToFile("quad2.xml");
        genericQuad.loadFromFile("quad2.xml");
    }
    
    
    
    genericQuad.setAlign(true);
    genericQuad.activate();
    
    imgQuad.setup(300,300,"pages_mask.png");
    if(imgQuad.loadFromFile("quad3.xml")!=0){
        imgQuad.saveToFile("quad3.xml");
        imgQuad.loadFromFile("quad3.xml");
    }
    imgQuad.setAlign(true);
    imgQuad.activate();
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    //cropper.update();
   // genericQuad.update();
    imgQuad.update();
}

//--------------------------------------------------------------
void testApp::draw(){
  //  cropper.draw();
  //  genericQuad.draw();
   imgQuad.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    genericQuad.saveToFile("quad2.xml");
    imgQuad.saveToFile("quad3.xml");
    cropper.saveToFile("quad.xml");
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    cropper.mouseMoved(x,y);
    genericQuad.mouseMoved(x,y);
    imgQuad.mouseMoved(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    cropper.mouseDragged(x,y);
    genericQuad.mouseDragged(x,y);
    imgQuad.mouseDragged(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    cropper.mousePressed(x,y);
    genericQuad.mousePressed(x,y);
    imgQuad.mousePressed(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    cropper.mouseReleased(x,y);
    genericQuad.mouseReleased(x,y);
    imgQuad.mouseReleased(x,y);
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