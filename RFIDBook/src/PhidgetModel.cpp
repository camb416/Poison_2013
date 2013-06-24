//
//  PhidgetModel.cpp
//  CinderProject
//
//  Created by Cameron Browning on 7/11/12.
//  Copyright (c) 2012 American Museum of Natural History. All rights reserved.
//

#include <iostream>
#include "PhidgetModel.h"

// get a value as an int
int IFKitModel::getSensorVal(int whichSensor){
    
    if(whichSensor>-1 && whichSensor<numSensors) {
        return sensors[whichSensor];
    } else {
        return -1;
    }
    
}

// get value as a bool
bool IFKitModel::getSensorBool(int whichSensor){
    if(getSensorVal(whichSensor)>500){
        return true;
    } else {
        return false;
    }
}

// log all the values
void IFKitModel::print(){
    cout << "sensor id: " << serial << endl;
    for(int i=0;i<numSensors;i++){
        
        sensors[i]>-1 ? cout << i << ": " << sensors[i] << endl : cout << i << ": no data received (yet)." << endl;
    }
}
// get the serial number
int IFKitModel::getSerial(){
    return serial;
}

// constructor
IFKitModel::IFKitModel(int serial_in, int numSensors_in){
    numSensors = numSensors_in;
    sensors = new int[numSensors];
    serial = serial_in;
    for(int i=0;i<numSensors;i++){
        sensors[i] = -1;
    }
}
// set the value of the sensor (in the model.. not on the hardware)
int IFKitModel::setSensorVal(int whichSensor, int whatValue){
    /* 
     time_t rawtime;
     struct tm * timeinfo;
     
     time ( &rawtime );
     timeinfo = localtime ( &rawtime );
     printf ( "Current local time and date: %s", asctime (timeinfo) );
     */  
    if(whichSensor<numSensors && whichSensor>=0){
        sensors[whichSensor] = whatValue;
        // cout << "set sensor " << whichSensor << " to: " << whatValue << "." << endl;
        return 0;
    } else {
        cout << "error setting sensor model value" << endl;
        return -1;
        
    }
}

// return the number of sensors
int IFKitModel::getNumSensors(){
    return numSensors;
}

