#include "BookApp.h"

BookApp::BookApp(){
    isSetup = false;
    showGrid_int = 0;

    grid_img.loadImage("assets/common/10pxgrid.png");

}



int BookApp::toggleGrid(){
    if(++showGrid_int >2){
        showGrid_int = 0;
    }
    
    return 0;
}




BookApp::~BookApp(){
    devices.stopThread();
    ofBaseApp::~ofBaseApp();
}

//--------------------------------------------------------------
void BookApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(false);
    
    lang.load("settings/languages.xml");
    
    bookView.setup(&lang, "settings/book.xml");
    
    // I think we're done with these
    bookView.addBackplate(lang.resolvePath("backplate.png"));
    
    // Load Book XML
    bookView.loadPages();
    
    // Set up RFID & touch
    devices.setup();
    devices.startThread(true,false);
    
    book.setup(&devices,&bookView);
   // rfidsetup();

    
    cropper.setup(1920,1200);
    cropper.loadFromFile();
    
    quadImage.setup(1920,1200,"assets/common/pages_mask.png");
    quadImage.setAlign(true);
    quadImage.loadFromFile("settings/pages_mask.xml");
    
    
    debugState = 1;
    updateDebug();
    dui.setup(&devices, &book, &lang, &bookView, &loader, &cropper, &quadImage);
    

    
    
    isSetup = true;

    cout << "setup complete." << endl;
    
    
}

//--------------------------------------------------------------
void BookApp::update(){

    ofEnableAlphaBlending();
    
    //TODO: fixthis
    //ofSetFullscreen(book.toggleFullScreen);
    
  //  devices.report();
    if(isSetup){
        devices.update();
        book.update();
        bookView.update();
    }
    dui.update();
    
    cropper.update();
    quadImage.update();

}

//--------------------------------------------------------------
void BookApp::draw(){
    
    
    ofEnableAlphaBlending();
   
    ofSetColor(255,255,255);
        if(showGrid_int==0) bookView.draw(0,0);
        if(showGrid_int!=0) grid_img.draw(0,0);
        if(showGrid_int!=1) cropper.draw();
        if(showGrid_int!=1) quadImage.draw();

    
    dui.draw();
    
    
    
}

//--------------------------------------------------------------
void BookApp::keyPressed(int key){
    switch(key){
            // pressing keys 0-7 simulates a touch event on
            // those sensors
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                bookView.touch(key-48); // send the int of the key
            break;
            
            case 'g':
            case 'G':
                toggleGrid();
            break;
            
            case 'm':
            case 'M':
                dui.toggleCursor();
            break;
            
            case 'a': 
            case 'A':
            
            book.forcedInput('A');

            break;
            
            case 'b':
            case 'B':
            
            book.forcedInput('B');
            break;
            
            case 'c':
            case 'C':
            
            book.forcedInput('C');
            break;
            
            case 'd':
            case 'D':
            
            book.forcedInput('D');
            break;
            
            case 'e':
            case 'E':
            
            book.forcedInput('E');
            break;
            
            case 'f':
            case 'F':
            
            dui.toggleFullScreen();
            break;
            
            // toggle keyboard mode on or off
            case 'x':
            case 'X':
            
            book.forcedInput('X');
            break;
            
            // toggle debug mode on or off
            case 'z':
            case 'Z':
            
            toggleDebug();
            break;
            
            case 's':
            case 'S':
            // bookView.savePageLayout(); // use the debug UI instead.
            break;
            
            /*
             // 
             // if this hasn't been deprecated, it certainly should have been!
             //
            // Fake touch input
            case 'h':
            case 'H':
            
            book.forcedInput('H');
            break;

            case 'j':
            case 'J':
            
            book.forcedInput('J');
            break;
             */
            
            case '`':
            case '~':
            dui.toggle();
            break;
            
            case 'p':
            case 'P':
            devices.printTouchSensors();
            break;
            
            // Toggle language
            case 'l':
            case 'L':
            lang.toggleLanguage();
            bookView.loadPages();
            break;


        case 358:
            // right arrow
            book.turnPageRight();
            break;
            
        case 356:
            // left arrow
            book.turnPageLeft();
            break;
        default:
            ofLogNotice() << "received an unknown keypress: " << key << ".";
            break;
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
    cropper.mouseMoved(x,y);
    quadImage.mouseMoved(x,y);
}

//--------------------------------------------------------------
void BookApp::mouseDragged(int x, int y, int button){
    cropper.mouseDragged(x,y);
    quadImage.mouseDragged(x,y);
}

//--------------------------------------------------------------
void BookApp::mousePressed(int x, int y, int button){
    
    // only send it if the debug ui's not up
    if(!dui.getIsVisible()) book.mousePressed();
    
        cropper.mousePressed(x,y);
    quadImage.mousePressed(x,y);
}

//--------------------------------------------------------------
void BookApp::mouseReleased(int x, int y, int button){
    
    // only send it if the debug ui's not up
    if(!dui.getIsVisible()) book.mouseReleased();
    
        cropper.mouseReleased(x,y);
    quadImage.mouseReleased(x,y);
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
