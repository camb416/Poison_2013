#include "BookApp.h"

BookApp::BookApp(){
    isSetup = false;
}

//--------------------------------------------------------------
void BookApp::setup(){
    

    
    lang.load("settings/languages.xml");
    
    bookView.setup();
    
    // I think we're done with these
    bookView.addBackplate(lang.resolvePath("assets/backplate.png"));

    // Media elements for each page. Will later be taken from XML
    vector<string> pageFiles;
    vector<ofVec2f> pagePositions;
    pageFiles.push_back(lang.resolvePath("assets/0.png"));
    pageFiles.push_back(lang.resolvePath("assets/assassin.png"));
    pageFiles.push_back(lang.resolvePath("assets/cerberus-open.png"));
    pageFiles.push_back(lang.resolvePath("assets/folios.png"));
    pageFiles.push_back(lang.resolvePath("assets/howitworks.png"));
    pageFiles.push_back(lang.resolvePath("assets/identify.png"));
    pageFiles.push_back(lang.resolvePath("assets/main.png"));
    pageFiles.push_back(lang.resolvePath("assets/map-open.png"));
    pageFiles.push_back(lang.resolvePath("assets/parts.png"));
    pageFiles.push_back(lang.resolvePath("assets/plant.png"));
    pageFiles.push_back(lang.resolvePath("assets/wolfsbane-open.png"));

    pagePositions.push_back(ofVec2f(0, 0));

    
    
    // Add pages of media to bookview
    bookView.addPage(pageFiles, pagePositions);
    pageFiles.at(0) = lang.resolvePath("assets/1.png");
    bookView.addPage(pageFiles, pagePositions);
        pageFiles.at(0) = lang.resolvePath("assets/2.png");
    bookView.addPage(pageFiles, pagePositions);
        pageFiles.at(0) = lang.resolvePath("assets/3.png");
    bookView.addPage(pageFiles, pagePositions);
    
    
    
    devices.setup();
        devices.startThread(true,false);
    
    book.setup(&devices,&bookView);
   // rfidsetup();

    debugState = 1;
    
   
        isSetup = true;
    
    ofSetFrameRate(60);
    updateDebug();
    ofSetVerticalSync(true);
    
    dui.setup(&devices, &book, &bookView);

    
    cout << "setup complete." << endl;
    
    
}

//--------------------------------------------------------------
void BookApp::update(){

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
}

//--------------------------------------------------------------
void BookApp::draw(){
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