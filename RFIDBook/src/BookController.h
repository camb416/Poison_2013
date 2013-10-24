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
#include "ofxXmlSettings.h"

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
    
    void turnPageLeft();
    void turnPageRight();
    
    //char currentTouch;
    
private:
    
    ofxXmlSettings prompts_xml;
    
    DeviceController * deviceController;
    BookView * bookView;
    bool isSetup;
    
    string forcedState;
    char forcedTouchState;
    //string lastTouchPage;
    
    bool touchStates[NUM_TOUCHES];
    bool prevTouchStates[NUM_TOUCHES];
    
    void turnPage(int _dir);
    string pageIDs[8] = {"A","AB","B","BC","C","CD","D","AD"};
    
    int getPageNumByStringState(string _pageState);
    
    float lastReceivedTouch;    // last got a touch (in seconds)
    float touchTimeOut;         // how long to wait
    float lastSentPrompt;       // last time we told the view to display a prompt
    int promptCount;            // how many prompts have been sent to the view
    float timeBetweenPrompts;   // time between the touch prompts
    int numTouchPrompts;        // how many unique prompts
    void resetTouchPrompt();
    
    string previousSituation;
};


#endif /* defined(__RFIDBook__BookController__) */
