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

void BookController::setup(DeviceController * deviceController_in){
    deviceController = deviceController_in;
    isSetup = true;
}
void BookController::update(){
    // do something to update here
}
bool BookController::isPageLanded(){
   int howManyActive = deviceController->getActiveSensorCount();
    cout << "there are " << howManyActive << " sensors active at the moment: ";
    
    if(howManyActive==3){
        cout << "pages landed." << endl;
        return true;
    } else {
        cout << "pages not laneded" << endl;
        return false;
    }
}