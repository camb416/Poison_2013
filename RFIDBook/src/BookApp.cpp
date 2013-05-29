#include "BookApp.h"

BookApp::BookApp(){
    isSetup = false;
}

//--------------------------------------------------------------
void BookApp::setup(){
    bookView.setup();
    bookView.addBackplate("backplate.jpg");
    bookView.addPage("0.png");
    bookView.addPage("1.png");
    bookView.addPage("2.png");
    bookView.addPage("3.png");
    devices.setup();
        devices.startThread(true,false);
    
    book.setup(&devices,&bookView);
   // rfidsetup();
    tfield.setup();
    tfield.update("Magic Book", 16,360);
    debugState = 1;
    
    aValue = 0.5f;
    bar.setup("Page Confidence", &aValue, 600, 16);
    bar.setPosition(ofPoint(16,749));
    isSetup = true;
    
    ofSetFrameRate(60);
    updateDebug();
    ofSetVerticalSync(true);
    
    
    
}

//--------------------------------------------------------------
void BookApp::update(){

  //  devices.report();
    if(isSetup){
    devices.update();
    bar.update();
        bookView.update();
    if(book.isPageLanded()){
        // checks for three sensors active.
    }
    
        
        book.update();
    
        
    if(debugState>0){

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
void BookApp::draw(){
    if(debugState>0){
    devices.draw();
        tfield.draw();
        bar.draw();
        if(ofGetMousePressed()) pos_ui.draw();
        bookView.draw(16,450,debugState);
    } else {
        bookView.draw(0,0);
    }
    
}

//--------------------------------------------------------------
void BookApp::keyPressed(int key){
    switch(key){
            case 'd':
            case 'D':
            
            toggleDebug();
            break;
            //case default:
            
            //break;
    }
}

void BookApp::toggleDebug(){
    debugState++;
    if(debugState>1){
    debugState = 0;    
    }
    updateDebug();
}
void BookApp::updateDebug(){
    if(debugState==0){
        ofSetFullscreen(true);
    } else {
        ofBackground(192);
        ofSetFullscreen(false);
    }
}

//--------------------------------------------------------------
void BookApp::keyReleased(int key){

}

//--------------------------------------------------------------
void BookApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void BookApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void BookApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void BookApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void BookApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void BookApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void BookApp::dragEvent(ofDragInfo dragInfo){ 

}