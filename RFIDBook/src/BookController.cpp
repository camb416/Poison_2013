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
    forcedPageActive = false;
    forcedState = "";
}
BookController::~BookController(){
    
}

void BookController::setup(DeviceController * deviceController_in, BookView * bookView_in){
    deviceController = deviceController_in;
    bookView = bookView_in;
    isSetup = true;
}
void BookController::update(){
    // do something to update here
    
    string currentSitation;
    
    currentSitation = whatSituation();
    
    if(currentSitation.length() == 1){
        // page is landed
        
        // take A-D and make 0-3
        char curSit_char = currentSitation[0];
        int whichPageNum = (int)curSit_char - 65;
        
        // send the view activation.
        bookView->activate(whichPageNum);
        
    } else if(currentSitation.length()==2){
        // you're on an interstitial
        bookView->deactivate();
        
    } else {
        // seems like an error...
        cout << "Error: Current Book Situation has a strange length: " << currentSitation.length() << endl;
    }
   // cout << currentSitation << " " << currentSitation.length() << currentSitation.substr(0,1) << endl;
    
}
bool BookController::isPageLanded(){
   int howManyActive = deviceController->getActiveSensorCount();
  //  cout << "there are " << howManyActive << " sensors active at the moment: ";
    
    if(howManyActive==3){
//        cout << "pages landed." << endl;
        return true;
    } else {
  //      cout << "pages not laneded" << endl;
        return false;
    }
}
string BookController::whatSituation(){
    string returnval_str = "";

    if (forcedPageActive != true){
        
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
    }
    else {
        returnval_str = forcedState;
    }
    
    return returnval_str;
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

void BookController::forcedPage(char _keypress){     //represent RFID actions with keypress  
  
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
        
        case 'x':
        case 'X':
        forcedState = "A";
        forcedPageActive = !forcedPageActive;
        break;
            
    }
}