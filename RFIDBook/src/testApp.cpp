#include "testApp.h"

testApp::testApp(){
    isSetup = false;
}

//--------------------------------------------------------------
void testApp::setup(){
    bookModel.setup();
    bookModel.addPage("0.jpg");
    bookModel.addPage("1.jpg");
    bookModel.addPage("2.jpg");
    bookModel.addPage("3.jpg");
    devices.setup();
        devices.startThread(true,false);
    
    book.setup(&devices,&bookModel);
   // rfidsetup();
    tfield.setup();
    tfield.update("Magic Book", 16,360);
    debugState = 1;
    
    aValue = 0.5f;
    bar.setup("Page Confidence", &aValue, 600, 16);
    bar.setPosition(ofPoint(16,749));
    isSetup = true;
    
    ofSetFrameRate(60);

    
    
    
}

//--------------------------------------------------------------
void testApp::update(){

  //  devices.report();
    if(isSetup){
    devices.update();
    bar.update();
        bookModel.update();
    if(book.isPageLanded()){
        // checks for three sensors active.
    }
    
    if(debugState>0){

        //TO DO: Implement this... whatSituation needs work! Currently has a vector out of range and/or bad access.
        tfield.update("Magic Book \n" + book.getReport() + "\n" + book.whatSituation());
        //tfield.update("Magic Book \n" + book.getReport());

        
        if(ofGetMousePressed()){
            pos_ui.update();
            aValue = ofRandom(1.0f);
        }
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
    bookModel.draw(16,450);
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