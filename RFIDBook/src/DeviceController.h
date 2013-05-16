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

class DeviceController : public ofThread{
public:
    void draw();
    void update();
    void report();
    int curSensor;
    
    // all the sensors
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
    int getActiveSensorCount();
    int getLeftSensorCount();
    int getRightSensorCount();
    
    ofImage inactive_img;
    ofImage active_img;
    ofImage selected_img;
    
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
