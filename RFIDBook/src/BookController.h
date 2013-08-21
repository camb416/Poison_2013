//
//  BookController.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/16/13.
//
//

#ifndef __RFIDBook__BookController__
#define __RFIDBook__BookController__

#include <iostream>
#include "BookView.h"
#include "DeviceController.h"

#define RFID_TIMEOUT 1
// TODO: CHANGE THIS BACK TO 4
#define NUM_TOUCHES 10

class BookController{
    
public:
    BookController();
    ~BookController();
    
    void setup(DeviceController * deviceController_in, BookView * bookView_in);
    void update();
    bool isPageLanded();
    string getReport();
    string whatSituation();
    char touchSituation();
    void forcedInput(char _keyStatus);
    void mousePressed();
    void mouseReleased();
    
    bool useRFID;
    bool checkedForRFIDTimeout;
    
    //char currentTouch;
    
private:
    DeviceController * deviceController;
    BookView * bookView;
    bool isSetup;
    
    string forcedState;
    char forcedTouchState;
    //string lastTouchPage;
    
    bool touchStates[NUM_TOUCHES];
    bool prevTouchStates[NUM_TOUCHES];
    
};


#endif /* defined(__RFIDBook__BookController__) */
