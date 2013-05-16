//
//  RFIDDevice.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/7/13.
//
//

#ifndef __RFIDBook__RFIDDevice__
#define __RFIDBook__RFIDDevice__

#include "Reporter.h"
#include <iostream>
#import <phidget21.h>
using namespace std;



class RFIDDevice{
    
public:
    
    CPhidgetRFIDHandle rfid;
    
    float confidence;
    float confidence_dest;
    
    RFIDDevice();
    void update();
    bool isSetup;
    bool isConnected;
    bool isListening;
    void setup(string title_in, void *context);
    void connect(int serialNumber = -1);
    void update(bool attached_in, char * tagName);
    string title;
    bool hasTag();
    bool isAttached();
    bool bIsAttached;
    bool bHasTag;
    void setListening(int listenValue=1);
    bool getListening();
    bool isConfident();
   //static int gotAttach(CPhidgetHandle phid, void *context);
    
   //static int gotDetach(CPhidgetHandle phid, void *context);
   //static int gotError(CPhidgetHandle phid, void *context, int errcode, const char *error);
   //static int gotTag(CPhidgetRFIDHandle phid, void *context, char *tag, CPhidgetRFID_Protocol proto);
   //static int lostTag(CPhidgetRFIDHandle phid, void *context, char *tag, CPhidgetRFID_Protocol proto);
    char currentTag[64];
    void report(char * tag_in);
};
#endif /* defined(__RFIDBook__RFIDDevice__) */
