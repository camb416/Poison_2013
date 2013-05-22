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
}
BookController::~BookController(){
    
}

void BookController::setup(DeviceController * deviceController_in, BookModel * bookModel_in){
    deviceController = deviceController_in;
    bookModel = bookModel_in;
    isSetup = true;
}
void BookController::update(){
    // do something to update here
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
    
    if(deviceController->getSensor("top-right")->hasTag()){
        // if page one is there, then it's definitely on a page...
        returnval_str = "A";
        bookModel->activate(0);
    } else if(deviceController->getSensor("middle-right")->hasTag()){
        // page one not down, but page 2 is.
        if(deviceController->getSensor("top-left")->hasTag()){
            returnval_str = "B";
            bookModel->activate(1);
        } else {
            returnval_str = "AB";
        }
    } else if(deviceController->getSensor("bottom-right")->hasTag()){
        // first two pages are not on the right, but the third is.
        if(deviceController->getSensor("middle-left")->hasTag()){
            returnval_str = "C";
            bookModel->activate(2);
        } else if(deviceController->getSensor("top-left")->hasTag()){
            returnval_str = "BC";
        }
    } else if(deviceController->getSensor("bottom-left")->hasTag()){
        returnval_str = "D";
        bookModel->activate(3);
    } else if(deviceController->getSensor("middle-left")->hasTag()){
        returnval_str = "CD";
    } else if(deviceController->getSensor("top-left")->hasTag()){
        returnval_str = "BD";
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