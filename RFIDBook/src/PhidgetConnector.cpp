//
//  PhidgetConnector.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/11/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>
#include "PhidgetConnector.h"


// constructor
PhidgetConnector::PhidgetConnector(){
    bUseEvents = true;
}

// destructor
PhidgetConnector::~PhidgetConnector(){
    cout << "closing Phidgets..." << endl;
    for(int i=0;i<ifkits.size();i++){
        CPhidget_close((CPhidgetHandle)*ifkits.at(i));
    }
    ifkits.clear();
    ifKitModels.clear();
}

// reset
void PhidgetConnector::reset(){
    cout << "closing Phidgets..." << endl;
    for(int i=0;i<ifkits.size();i++){
        CPhidget_close((CPhidgetHandle)*ifkits.at(i));
    }
    cout << "opening them back up..." << endl;
    for(int i=0;i<ifkits.size();i++){
        //   CPhidget_close((CPhidgetHandle)*ifkits.at(i));
        int mySerial = ifKitModels.at(i)->getSerial();
        //CPhidget_getSerialNumber((CPhidgetHandle)*ifkits.at(i), &mySerial);
        cout << "whats the frequency, Kenneth? " << mySerial;
        CPhidgetHandle thisIFKit = (CPhidgetHandle)ifkits.at(i);
        CPhidget_open(thisIFKit, mySerial);
        cout << "attempting to reopen... " << endl;
    }
}

// return a given ifkit sensor value as a bool.
bool PhidgetConnector::getBool(int serial_in, int index_in){
    if(getVal(serial_in, index_in)<500){
        return false;
    } else {
        return true;
    }
}

// setter for whether to bother with the sensorchanged events
bool PhidgetConnector::useEvents(bool bUseEvents_in){
    bUseEvents = bUseEvents_in;
    return bUseEvents;
}

// return a given sensor value as an int
int PhidgetConnector::getVal(int serial_in,int index_in){
    IFKitModel * theKit = getIFKit(serial_in);
    if(theKit != NULL){
        return theKit->getSensorVal(index_in);
    } else {
        return -1;
    }
    
}

// print the sensor values for a given ifkit device (by serial)
// -1 to print them all!
void PhidgetConnector::print(int serial_in){
    cout << "Models: " << endl;
    if(ifKitModels.size()>0){
        
        for(int i=0;i<ifKitModels.size();i++){
            IFKitModel * thisKit = (IFKitModel *)ifKitModels.at(i);
            if(serial_in == -1 || serial_in == thisKit->getSerial()) thisKit->print();
        }
    } else {
        cout << "there doesn't seem to be any devices successfully connected with which to print." << endl;
    }
    cout << "hardware devices: " << endl;
    for(int j=0;j<ifkits.size();j++){
        int serialNo;
        CPhidget_getSerialNumber((CPhidgetHandle)*ifkits.at(j), &serialNo);
        int whichKit = getIFKitModelID(serialNo);
        if(whichKit>-1){
            IFKitModel * desiredKit = ifKitModels.at(whichKit);
            cout << "serial: " << desiredKit->getSerial() << endl;
            for(int i=0;i<desiredKit->getNumSensors();i++){
                int sensorVal;
                CPhidgetInterfaceKit_getSensorValue(*ifkits.at(j), i, &sensorVal);
                cout << i << ": " << sensorVal << endl;
                // desiredKit->setSensorVal(i,sensorVal);
            }
        }
    }
    
}

// this updates all the kit models without relying on the sensorchanged event callbacks.
void PhidgetConnector::updateKits(){
    // updating the kits manually through the API.
    for(int j=0;j<ifkits.size();j++){
        int serialNo;
        CPhidget_getSerialNumber((CPhidgetHandle)*ifkits.at(j), &serialNo);
        int whichKit = getIFKitModelID(serialNo);
        if(whichKit>-1){
            IFKitModel * desiredKit = ifKitModels.at(whichKit);
            for(int i=0;i<desiredKit->getNumSensors();i++){
                int sensorVal;
                CPhidgetInterfaceKit_getSensorValue(*ifkits.at(j), i, &sensorVal);
                desiredKit->setSensorVal(i,sensorVal);
            }
        }
    }
}

// get the IFKit Model by serial number
IFKitModel * PhidgetConnector::getIFKit(int serial_in){
    int whichDeviceID = getIFKitModelID(serial_in);
    if(whichDeviceID>-1 && whichDeviceID<ifKitModels.size()){
        return (IFKitModel*)ifKitModels.at(whichDeviceID);
    } else {
        return NULL;
    }
}

// get the IFKit Model's vector id by serial.
int PhidgetConnector::getIFKitModelID(int serial_in){
    for(int i=0; i < ifKitModels.size(); i++){
        IFKitModel * thisKit = (IFKitModel*) ifKitModels.at(i);
        if(thisKit->getSerial() == serial_in) return i;
    }
    return -1;
}

// connect to a device. Use -1 for first available device
void PhidgetConnector::connect(int serial_in, int _timeOut){
    cout << "attempting connection to board #" << serial_in << "... " ;

    CPhidgetInterfaceKitHandle * thisIFKIT = new CPhidgetInterfaceKitHandle();
    ifkits.push_back(thisIFKIT);
    CPhidgetInterfaceKit_create(thisIFKIT);
    
    if(bUseEvents){   
        cout << "using events..." << endl;
        CPhidget_set_OnError_Handler((CPhidgetHandle)*thisIFKIT, ErrorHandler, this);
        CPhidgetInterfaceKit_set_OnSensorChange_Handler(*thisIFKIT, SensorChangeHandler, this);
    } else {
        cout << "not using events..." << endl;
    }
    CPhidget_open((CPhidgetHandle)*thisIFKIT, serial_in);
    printf("Waiting for interface kit to be attached....");
    int result;
    const char *err;
    
    int timeOut = 30000;
    if(_timeOut>0) timeOut = _timeOut * 1000;
    if((result = CPhidget_waitForAttachment((CPhidgetHandle)*thisIFKIT, timeOut))){
        CPhidget_getErrorDescription(result, &err);
        printf("Problem waiting for attachment %s\n", err);
    } else {
        printf("sensor opened okay.");
        display_properties(*thisIFKIT);
    }
}

//C callback
int  SensorChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value){
    //Retrieve the class reference and call it's sensorChanged method
    PhidgetConnector *phidgetInstance = (PhidgetConnector *)usrptr;
    phidgetInstance->sensorChanged(IFK, Index, Value);
    return 0;
}

int ErrorHandler(CPhidgetHandle IFK, void *usrtpr, int ErrorCode, const char * ErrorDescription){
    cout << "ERROR: " << ErrorCode << ", " << ErrorDescription << ".";
    return 0;
}

// the class method for the sensorchanged event callback.
// it would be awesome if this bubbled the event up to the app.
void PhidgetConnector::sensorChanged (CPhidgetInterfaceKitHandle IFK, int index, int value) {
    time_t rawtime;
    struct tm * timeinfo;
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    //printf ( "Current local time and date: %s", asctime (timeinfo) );
    cout << "received event: " << index << ", " << value << endl;
    
    int serialNo;
    CPhidget_getSerialNumber((CPhidgetHandle)IFK, &serialNo);
    int whichKit = getIFKitModelID(serialNo);
    if(whichKit>-1){
        IFKitModel * desiredKit = ifKitModels.at(whichKit);
        desiredKit->setSensorVal(index,value);
        // cout << "setting sensor: " << index << ", " << value << endl;
    }
    
}

// display the properties and create the ifkit model. Should really refactor...
int PhidgetConnector::display_properties(CPhidgetInterfaceKitHandle phid){
    
	int serialNo, version, numInputs, numOutputs, numSensors, triggerVal, ratiometric, i;
	const char* ptr;
    
	CPhidget_getDeviceType((CPhidgetHandle)phid, &ptr);
	CPhidget_getSerialNumber((CPhidgetHandle)phid, &serialNo);
	CPhidget_getDeviceVersion((CPhidgetHandle)phid, &version);
    
	CPhidgetInterfaceKit_getInputCount(phid, &numInputs);
	CPhidgetInterfaceKit_getOutputCount(phid, &numOutputs);
	CPhidgetInterfaceKit_getSensorCount(phid, &numSensors);
	CPhidgetInterfaceKit_getRatiometric(phid, &ratiometric);
    ifKitModels.push_back(new IFKitModel(serialNo, numSensors));
    
    
    
	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("# Digital Inputs: %d\n# Digital Outputs: %d\n", numInputs, numOutputs);
	printf("# Sensors: %d\n", numSensors);
	printf("Ratiometric: %d\n", ratiometric);
    
	for(i = 0; i < numSensors; i++){
        CPhidgetInterfaceKit_setSensorChangeTrigger(phid, i, 0);
		CPhidgetInterfaceKit_getSensorChangeTrigger (phid, i, &triggerVal);
		printf("Sensor#: %d > Sensitivity Trigger: %d\n", i, triggerVal);
	}
    
	return 0;
}

