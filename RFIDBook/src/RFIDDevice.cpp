//
//  RFIDDevice.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/7/13.
//
//

#include "RFIDDevice.h"

using namespace std;

RFIDDevice::RFIDDevice(){
    isSetup = false;
    isConnected = false;
    isListening = false;
    confidence = 0.0f;
}
bool RFIDDevice::isConfident(){

    if(confidence>0.5f){
     //       cout << confidence;
        return true;
    } else {
        return false;
    }
}
void RFIDDevice::setup(string title_in, void *context){
    title = title_in;


    strcpy(currentTag,"x");
    
    bIsAttached = false;
    bHasTag = false;
    isSetup = true;
}
void RFIDDevice::update(){
  /*
    if(hasTag()){
        confidence += (1.0f-confidence)/16.0f;
    } else {
        confidence += (0.0f-confidence)/16.0f;
    }
   */
}



int gotAttach(CPhidgetHandle phid, void *context) {
	
   // Reporter * c = static_cast<Reporter*>(context);
    //c->saySomething();
	//cout << "gotAttach" << endl;
    RFIDDevice * obj = (RFIDDevice*)context;
    char * nullchar = new char[1];
    *nullchar = 'x';
    obj->update(true,nullchar);
    delete nullchar;
    return 0;
}

int gotDetach(CPhidgetHandle phid, void *context) {
	//cout << "gotDetach" << endl;
    RFIDDevice * obj = (RFIDDevice*)context;
    char * nullchar = new char[1];
    *nullchar = 'x';
    obj->update(false,nullchar);
    delete nullchar;

	return 0;
}

int gotError(CPhidgetHandle phid, void *context, int errcode, const char *error) {
	cout << "gotError" << endl;
	return 0;
}


int gotTag(CPhidgetRFIDHandle phid, void *context, char *tag, CPhidgetRFID_Protocol proto) {
   // context->report();
   // currentTag = tag;
    RFIDDevice * obj = (RFIDDevice*)context;
    obj->update(true,tag);
	//cout << "gotTag: " << tag << endl;
	return 0;
}

int lostTag(CPhidgetRFIDHandle phid, void *context, char *tag, CPhidgetRFID_Protocol proto) {
    int * antennaState = new int();
    
    CPhidgetRFID_getAntennaOn(phid, antennaState);
  //  if(&antennaState!=0){
        //cout << "lostTag" << endl;
        RFIDDevice * obj = (RFIDDevice*)context;
        char * tagToSend = new char[1];
        *tagToSend = 'x';
        obj->update(true,tagToSend);
        delete tagToSend;
//	}
    delete antennaState;
    
    

    
    return 0;
}
void RFIDDevice::connect(int serialNumber){
    serial = serialNumber;
    if(!isSetup){
        cout << "running RFIDDevice::connect before RFIDDevice::setup(). Expect problems." << endl;
    }
    
    rfid=0;
    
    CPhidget_enableLogging(PHIDGET_LOG_VERBOSE, NULL);
	CPhidgetRFID_create(&rfid);
	
	CPhidgetRFID_set_OnTag2_Handler(rfid, gotTag, this);
	CPhidgetRFID_set_OnTagLost2_Handler(rfid, lostTag, this);
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)rfid, gotAttach, this);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)rfid, gotDetach, this);
	CPhidget_set_OnError_Handler((CPhidgetHandle)rfid, gotError, this);
    
    CPhidget_open((CPhidgetHandle)rfid, -1);
    isConnected = true;
}

void RFIDDevice::setListening(int listenValue){
    if(listenValue>0){
        isListening = true;
    } else {
        isListening = false;
    }

}
bool RFIDDevice::getListening(){
    return isListening;
}

void RFIDDevice::update(bool attached_in, char * tagName){
    bIsAttached = attached_in;
   // if(isListening){
        strcpy(currentTag,tagName);
   // }
}
bool RFIDDevice::isAttached(){
    return bIsAttached;
}
bool RFIDDevice::hasTag(){
    //cout << currentTag << endl;
    if(isSetup){
    if(strcmp(currentTag,"x") == 0 || strcmp(currentTag,"") == 0){
        return false;
    } else{
        return true;
    }
    } else {
        //cout << "RFID device is not setup. do not ask for tag from it" << endl;
        return false;
    }
}

void RFIDDevice::report(char * tag_in){
    strcpy(currentTag,tag_in);
    cout << title << ": " << currentTag << endl;
}