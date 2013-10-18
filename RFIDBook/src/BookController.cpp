//
//  BookController.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/16/13.
//
//

#include "BookController.h"


BookController::BookController(){
    isSetup = false;
    useRFID = true;
    forcedState = previousSituation = "A";
    //lastTouchPage = -1;
    checkedForRFIDTimeout = false;
    lastReceivedTouch = 0.0f;
    touchTimeOut = 5.0f;                 // TIMEOUT LENGTH
    timeBetweenPrompts = 2.0f;              // TIME BETWEEN THE TOUCH PROMPTS
    numTouchPrompts = 3;                    // how many touch prompts?
    promptCount = -1;
    for(int i=0;i<NUM_TOUCHES;i++){
        touchStates[i] = prevTouchStates[i] = false;
    }
}
BookController::~BookController(){
    
}

void BookController::resetTouchPrompt(){
    lastReceivedTouch = ofGetElapsedTimef();
    promptCount = -1;
    bookView->touchPrompt(-1);
}


void BookController::setup(DeviceController * deviceController_in, BookView * bookView_in){
    deviceController = deviceController_in;
    bookView = bookView_in;
    isSetup = true;
}

void BookController::mousePressed(){
    bookView->mousePressed();
}
void BookController::mouseReleased(){
    bookView->mouseReleased();
}

void BookController::update(){
    
    ///////////////////////////////////////////
    // RFID / Page turning stuff
    ///////////////////////////////////////////
    // if after a number of seconds defined in the header
    // don't use the RFID sensors (for testing).
    ///////////////////////////////////////////
    
    
    if(ofGetElapsedTimeMillis()>(RFID_TIMEOUT*1000) && !checkedForRFIDTimeout){
        if(!deviceController->hasSeenRFID()){
            ofLogWarning() << "Haven't seen the RFID sensors for " << RFID_TIMEOUT << " second(s). Using manual mode.";
            useRFID = false;
            checkedForRFIDTimeout = true;
        }
    }
    
    string currentSituation;
    currentSituation = whatSituation();
    
    if(currentSituation!=previousSituation){
        // something happened with the pages (momentary)
        resetTouchPrompt();
        previousSituation = currentSituation;
        
    }
    //currentTouch = touchSituation();
    
    if(currentSituation.length() == 1){
        // page is landed
        
        // take A-D and make 0-3
        char curSit_char = currentSituation[0];
        int whichPageNum = (int)curSit_char - 65;

        //bookView->mediaPages.at(whichPageNum)->receiveInput(currentTouch, whichPageNum);
        
        // send the view activation.
        bookView->activate(whichPageNum);
        
        } else if(currentSituation.length()==2){
            // you're on an interstitial
            bookView->deactivate();
            resetTouchPrompt();
        } else {
        // seems like an error...
        cout << "Error: Current Book Situation has a strange length: " << currentSituation.length() << endl;
    }
    //lastTouchPage = currentSitation;
    
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    
    
    //
    ///////////////////////////////////////////
    // TOUCH STUFF
    ///////////////////////////////////////////
    //
    for(int i=0;i<NUM_TOUCHES;i++){
        // Check for touches if the kit is connected
        if (deviceController->kitConnected == true){
            touchStates[i] = deviceController->getTouchBool(i);
            if(touchStates[i]!=prevTouchStates[i]){
                // a sensor changed.
                if(touchStates[i]){
                    // it was a touch
                    resetTouchPrompt();
                    bookView->touch(i);
                } else {
                    // it was a release
                    resetTouchPrompt();
                    bookView->release(i);
                }
            }
            prevTouchStates[i] = touchStates[i];
        }
    }

    if((ofGetElapsedTimef() - lastReceivedTouch) > touchTimeOut){
        
        
        if(promptCount==-1){
            // first prompt sent
            bookView->touchPrompt(++promptCount);

            lastSentPrompt = ofGetElapsedTimef();
        }else if((ofGetElapsedTimef() - lastSentPrompt) > timeBetweenPrompts){
            if(promptCount<(numTouchPrompts-1)){
                bookView->touchPrompt(++promptCount);

                lastSentPrompt = ofGetElapsedTimef();
            } else {
                // its over, send it a -1
                promptCount = -1;
                bookView->touchPrompt(promptCount);
                lastReceivedTouch = ofGetElapsedTimef();
            }
            
        } else {
            // outlier
            // ofLogNotice() << "outlier" ;
        }
        
    }

    


}
bool BookController::isPageLanded(){
   int howManyActive = deviceController->getActiveSensorCount();  
    
    if(howManyActive==3){
        return true;
    } else {
        return false;
    }
}
string BookController::whatSituation(){
    string returnval_str = "";

    if (useRFID){
        
        if(deviceController->getSensor("top-right")->hasTag()){
            // if page one is there, then it's definitely on a page...
            returnval_str = "A";
            //bookView->activate(0);
        } else if(deviceController->getSensor("middle-right")->hasTag()){
            // page one not down, but page 2 is.
            if(deviceController->getSensor("top-left")->hasTag()){
                returnval_str = "B";
                //bookView->activate(1);
            } else {
                returnval_str = "AB";
            }
        } else if(deviceController->getSensor("bottom-right")->hasTag()){
            // first two pages are not on the right, but the third is.
            if(deviceController->getSensor("middle-left")->hasTag()){
                returnval_str = "C";
               // bookView->activate(2);
            } else if(deviceController->getSensor("top-left")->hasTag()){
                returnval_str = "BC";
            } else {
                returnval_str = "AC";
            }
        } else if(deviceController->getSensor("bottom-left")->hasTag()){
            returnval_str = "D";
            //bookView->activate(3);
        } else if(deviceController->getSensor("middle-left")->hasTag()){
            returnval_str = "CD";
        } else if(deviceController->getSensor("top-left")->hasTag()){
            returnval_str = "BD";
        } else {
            returnval_str = "AD";
        }
    } else {
        returnval_str = forcedState;
    }
    
    return returnval_str;
}

char BookController::touchSituation(){
    char returnval_char = ' ';
    
    if (useRFID){
        if (deviceController->hasTouch(0) == true){
            returnval_char = 'H';
        } else if (deviceController->hasTouch(1) == true){
            returnval_char = 'J';
        } else {
            returnval_char = '0';

        }
    } else {
        returnval_char = forcedTouchState;
    }
    
    return returnval_char;
}

string BookController::getReport(){
    string report_str;
    if(isPageLanded()){
        report_str = "pages landed";
    } else {
        report_str = "fade out pages";
    }
    return report_str;
}

void BookController::turnPageLeft(){
    turnPage(-1);
}
void BookController::turnPageRight(){
    turnPage(1);
}

void BookController::turnPage(int _dir){
    // -1 go back
    // 1 go fwd
    // 0 refreshpage? no implemented.
    // sanitize this? use bool instead?
    
    ofLogNotice() << "whatSituation() returns: " << whatSituation() << ", forcedState: " << forcedState << ", getPageNumByStringState() returns: " << getPageNumByStringState(forcedState) << "." ;
    
    int currentPageThisMoment = getPageNumByStringState(forcedState);
    if(currentPageThisMoment>=0){
    ofLogNotice() << "you are currently on: " << currentPageThisMoment << ". You want to be on: " << (currentPageThisMoment+_dir);
        
        int destinationPage = currentPageThisMoment + _dir;
        
        if(destinationPage <0){
            destinationPage = 7;
        } else if(destinationPage>=8) {
            destinationPage = 0;
        }
        forcedState = pageIDs[destinationPage];
        ofLogNotice() << "setting the page state to: " << forcedState << ".";
        
    } else {
        ofLogWarning() << "can't tell which page the book is on to increment or decrement it.";
    }
}
int BookController::getPageNumByStringState(string _pageState){
    int returnVal = -1;
    for(int i=0;i<8;i++){
        if(pageIDs[i]==_pageState){
            returnVal = i;
        }
    }
    
    return returnVal;
}

void BookController::forcedInput(char _keypress){     //represent RFID actions with keypress
  
    switch(_keypress){
        case 'a':
        case 'A':
            
        forcedState = "A";
        break;
            
        case 'b':
        case 'B':
            
        forcedState = "B";
        break;
            
        case 'c':
        case 'C':
            
        forcedState = "C";
        break;
            
        case 'd':
        case 'D':
            
        forcedState = "D";
        break;
        
        case 'e':
        case 'E':
            
        forcedState = "AB";
            
        break;
            
        // Fake touch input
        case 'h':
        case 'H':

        forcedTouchState = 'H';
        break;
            
        case 'j':
        case 'J':
            
        forcedTouchState = 'J';
        break;

        
        case 'x':
        case 'X':
        forcedState = "AB";
        useRFID = !useRFID;
        break;

            
        
            
    }
}