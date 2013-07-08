#include "BookApp.h"

BookApp::BookApp(){
    isSetup = false;
}

//--------------------------------------------------------------
void BookApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    lang.load("settings/languages.xml");
    
    bookView.setup();
    
    // I think we're done with these
    bookView.addBackplate(lang.resolvePath("assets/backplate.png"));
    
    // Load Book XML
    vector<XmlPage> pages = loader.load("settings/book.xml");
    
    for (int i = 0; i < pages.size(); i++) {
        bookView.addPage(pages.at(i).media, pages.at(i).position, pages.at(i).autoplay, pages.at(i).tapId, pages.at(i).loopback);
    }
    
    // Set up RFID & touch
    devices.setup();
        devices.startThread(true,false);
    
    book.setup(&devices,&bookView);
   // rfidsetup();

    debugState = 1;
    updateDebug();
    dui.setup(&devices, &book, &bookView, &loader);
    
    
    isSetup = true;

    cout << "setup complete." << endl;
    
    
}

//--------------------------------------------------------------
void BookApp::update(){
    ofEnableAlphaBlending();
    ofSetFullscreen(book.toggleFullScreen);
    
  //  devices.report();
    if(isSetup){
        devices.update();
        bookView.update();
        
            if(book.isPageLanded()){
                    // checks for three sensors active.
            }
    
        book.update();
        
    }
    dui.update();
    
    // Test output of the touch sensor
//    if (devices.kit.getBool(276576, 0)){
//        ofLogNotice() << "touched!";
//    }
//    
}

//--------------------------------------------------------------
void BookApp::draw(){
    ofEnableAlphaBlending();
  //  if(debugState>0){

  //  } else {
        bookView.draw(0,0);
   // }
    dui.draw();
    
}

//--------------------------------------------------------------
void BookApp::keyPressed(int key){
    switch(key){
            case 'a': 
            case 'A':
            
            book.forcedPage('A');

            break;
            
            case 'b':
            case 'B':
            
            book.forcedPage('B');
            break;
            
            case 'c':
            case 'C':
            
            book.forcedPage('C');
            break;
            
            case 'd':
            case 'D':
            
            book.forcedPage('D');
            break;
            
            case 'e':
            case 'E':
            
            book.forcedPage('E');
            break;
            
            case 'f':
            case 'F':
            
            book.forcedPage('F');
            break;
            
            // toggle keyboard mode on or off
            case 'x':
            case 'X':
            
            book.forcedPage('X');
            break;
            
            // toggle debug mode on or off
            case 'z':
            case 'Z':
            
            toggleDebug();
            break;
            
            case 's':
            case 'S':
            bookView.savePageLayout();
            break;
            
            // Fake touch input
            case 'h':
            case 'H':
            
            book.forcedPage('H');
            break;

            case 'j':
            case 'J':
            
            book.forcedPage('J');
            break;

            case '`':
            case '~':
            dui.toggle();
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
     //   ofSetFullscreen(true);
    } else {
        ofBackground(192);
    //    ofSetFullscreen(false);
    }
}

//void BookApp::sendInput(char touchId){
//    book.receiveInput(touchId);
//    ofLogNotice() << "received touch input";
//}


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
    
    // only send it if the debug ui's not up
    if(!dui.getIsVisible()) book.mousePressed();
}

//--------------------------------------------------------------
void BookApp::mouseReleased(int x, int y, int button){
    
    // only send it if the debug ui's not up
    if(!dui.getIsVisible()) book.mouseReleased();
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
