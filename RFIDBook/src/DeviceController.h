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

class DeviceController : public ofThread{
public:
    void draw(int _x = 0, int _y = 0);
    void update();
    void report();
    int curSensor;

    // Interface Kit
    PhidgetConnector kit;
    int serialId = 276576;
    int touchSensor(string sensor);
    bool hasTouch(int sensorID);

    // RFID Sesnsors
    vector<RFIDDevice*> rfids;
    // pointers to the lefts and the rights;
    vector<RFIDDevice*> leftSensors;
    vector<RFIDDevice*> rightSensors;
    
    //RFIDDevice rfidLeft;
    //RFIDDevice rfidRight;
    Reporter reporter;
    void setup();
    void doSomething();
    time_t lastTimeRun;
    double lastTime;
    msa::Timer timer;
    float cycleTime;
    int numSensors;
    
    int getSensorId(string idLookup);
    int getTouchSensor(string idLookup);
    RFIDDevice * getSensor(string idLookup);
    int getActiveSensorCount();
    int getLeftSensorCount();
    int getRightSensorCount();
    
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
            
            // has it been 10ms since last time?
            // time_t curTime = time(NULL);
            lock();
            if(ofGetElapsedTimeMillis()>lastTime+cycleTime){
                //double lastSeconds = timer.getSecondsSinceLastCall();
                //cout << ofGetElapsedTimeMillis() << endl;
               // cout << curSensor << endl;
                // DO THE THING!
                
                // turn the others off
                
                int prevSensor = curSensor-1;
                if(prevSensor<0) prevSensor=numSensors-1;
                int * prevSensorState = new int();
                CPhidgetRFID_getTagStatus(rfids.at(prevSensor)->rfid,prevSensorState);
                //cout << *(prevSensorState) << endl;
                char * tagToSend = new char[1];
                if(*prevSensorState==1 && doublecheck(prevSensor)){
                    *tagToSend = 'O';
                    
                } else {
                    *tagToSend = 'x';
                    if(prevSensor%2==1){
                        //breakpoint
                        // I think this shouldn't happen.
                        //cout << "" << endl;
                    }
                }
                
                rfids.at(prevSensor)->update(true,tagToSend);
                
                delete tagToSend;
                delete prevSensorState;
                
                
                
                
                
                
                
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
                if(curSensor >=numSensors) curSensor = 0;;
                
                
                // turn a sensor on
                
                
                
                // pick next sensor
                
                
                lastTime = ofGetElapsedTimeMillis();
                
            }
            unlock();
            // if yes: 
            
                
            
            
            
        }
    }
};

#endif /* defined(__RFIDBook__DeviceController__) */
