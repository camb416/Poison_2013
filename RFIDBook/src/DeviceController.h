//
//  DeviceController.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/7/13.
//
//

#ifndef __RFIDBook__DeviceController__
#define __RFIDBook__DeviceController__


#include "ofMain.h"
#include <iostream>
#include "RFIDDevice.h"
#include "Reporter.h"
#include <time.h>  
#include "MSATimer.h"
#include "PhidgetConnector.h"
#include "ofxXmlSettings.h"

class DeviceController : public ofThread{

private:
    void loadDeviceDetails(); // use this for putting the details in XML.
    ofxXmlSettings device_xml;
    
public:
    
    void setup();
    void draw(int _x = 0, int _y = 0);
    void update();
    void report();

    
    
    //////////////////////////////////////////
    // Interface Kit /////////////////////////
    //////////////////////////////////////////
    PhidgetConnector kit;
    int serialId = -1; //275939
    int touchSensor(string sensor);
    bool kitConnected = true;
    bool hasTouch(int sensorID);
    void printTouchSensors();
    bool getTouchBool(int whichSensor, int whichKit = -1);
    //////////////////////////////////////////

    //////////////////////////////////////////
    // RFID Sensors //////////////////////////
    //////////////////////////////////////////
    vector<RFIDDevice*> rfids;
    // pointers to the lefts and the rights;
    vector<RFIDDevice*> leftSensors;
    vector<RFIDDevice*> rightSensors;
    int getSensorId(string idLookup);
    int getTouchSensor(string idLookup);
    RFIDDevice * getSensor(string idLookup);
    int getActiveSensorCount();
    int getLeftSensorCount();
    int getRightSensorCount();
    bool hasSeenRFID();
    bool bSeenRFID;
    int curSensor;
    time_t lastTimeRun;
    double lastTime;
    msa::Timer timer;
    float cycleTime;
    int numSensors;
    // for debug UI
    ofImage inactive_img;
    ofImage active_img;
    ofImage selected_img;
    
    bool doublecheck(int sensor){
        bool returnval;
        int * sensorState = new int();
        CPhidgetRFID_getTagStatus(rfids.at(sensor)->rfid,sensorState);
        if(*sensorState==1){
            returnval = true;
        } else {
            returnval = false;
        }
        delete sensorState;
        return returnval;
    }
    
    void threadedFunction(){
        while(isThreadRunning()){
            lock();
            if(ofGetElapsedTimeMillis()>lastTime+cycleTime){ // has it been 10ms since last time?
                // check the last sensor (that has been on for a few ms
                int prevSensor = curSensor-1;
                if(prevSensor<0) prevSensor=numSensors-1;
                int * prevSensorState = new int();
                CPhidgetRFID_getTagStatus(rfids.at(prevSensor)->rfid,prevSensorState);
                char * tagToSend = new char[1];
                if(*prevSensorState==1 && doublecheck(prevSensor)){
                    *tagToSend = 'O';
                } else {
                    *tagToSend = 'x';
                    if(prevSensor%2==1){
                        // for error checking
                    }
                }
                
                rfids.at(prevSensor)->update(rfids.at(prevSensor)->bIsAttached,tagToSend);                
                delete tagToSend;
                delete prevSensorState;
                
                // cycle the sensor antennae
                int sensorState;
                for(int i=0;i<numSensors;i++){
                    if(i!=curSensor){
                        sensorState = 0;
                    } else {
                        sensorState = 1;
                    }
                    rfids.at(i)->setListening(sensorState);
                    CPhidgetRFID_setAntennaOn(rfids.at(i)->rfid, sensorState);
                    CPhidgetRFID_setLEDOn(rfids.at(i)->rfid, sensorState);
                    rfids.at(i)->update();
                }
                curSensor++;
                if(curSensor >=numSensors) curSensor = 0;
                lastTime = ofGetElapsedTimeMillis();
            }
            unlock();
        }
    }
    /////////////////////
    
};

#endif /* defined(__RFIDBook__DeviceController__) */
