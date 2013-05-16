//
//  DeviceController.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/7/13.
//
//

#include "DeviceController.h"

using namespace std;



void DeviceController::setup(){
    cycleTime = 100; // ms to cycle the RFID antennae
    numSensors = 6;
    
    inactive_img.loadImage("radio_inactive.png");
    active_img.loadImage("radio_active.png");
    selected_img.loadImage("radio_selected.png");
    
    for(int i=0;i<numSensors;i++){
        rfids.push_back(RFIDDevice());
        if(i%2==0){
            leftSensors.push_back(&(rfids.at(i)));
        } else {
            rightSensors.push_back(&(rfids.at(i)));
        }
    }
    
    timer.start();
    rfids.at(0).setup("left-top",this);
    rfids.at(1).setup("right-top",this);
    rfids.at(2).setup("left-middle",this);
    rfids.at(3).setup("right-middle",this);
    rfids.at(4).setup("left-bottom",this);
    rfids.at(5).setup("right-bottom",this);
    //rfidLeft.setup(this);
    //rfidRight.setup(this);
    rfids.at(0).connect(112512);
    rfids.at(1).connect(309045);
//    rfidLeft.connect(112512);
 //   rfidRight.connect(309045);
    lastTime = 0;
    curSensor = 0;
}
void DeviceController::doSomething(){
    cout << "do something here when you get a tag." << endl;
}
void DeviceController::update(){

    for(int i=0;i<numSensors;i++){
        if(rfids.at(i).isAttached()){
            if(rfids.at(i).hasTag()){
                rfids.at(i).confidence = 1.0f;
            } else {
               rfids.at(i).confidence_dest = 0.0f;
            }
        } else {
            rfids.at(i).confidence_dest = 0.0f;
        }
        rfids.at(i).confidence += (rfids.at(i).confidence_dest- rfids.at(i).confidence)/256.0f;
        rfids.at(i).confidence = MAX(0.0f,MIN(rfids.at(i).confidence,1.0f));
        // cout << rfids.at(i).title << ": " << rfids.at(i).isAttached() << ", " << rfids.at(i).hasTag() << endl;
    }
}

int DeviceController::getSensorId(string idLookup){
    int idToReturn = -1;
    for(int i=0;i<numSensors;i++){
        cout << rfids.at(i).title << endl;
        if(idLookup.compare(rfids.at(i).title)==0){
            idToReturn = i;
        }
    }
    return idToReturn;
}

int DeviceController::getLeftSensorCount(){
    int activeCount = 0;
       // cout << leftSensors.size() << " elems in leftSensors." << endl;
    for(int i=0;i<leftSensors.size();i++){
      //  cout << leftSensors.at(i)->isConfident();
        if(leftSensors.at(i)->isConfident()){
            activeCount++;
        }
    }
    return activeCount;
}
int DeviceController::getRightSensorCount(){
    int activeCount = 0;
    //cout << rightSensors.size() << " elems in rightSensors." << endl;
    for(int i=0;i<rightSensors.size();i++){
      //   cout << rightSensors.at(i)->isConfident();
        if(rightSensors.at(i)->isConfident()){
            activeCount++;
        }
    }
    return activeCount;
}

int DeviceController::getActiveSensorCount(){
    int activeCount = 0;
    for(int i=0;i<numSensors;i++){
        if(rfids.at(i).isConfident()){
            activeCount++;
        }
    }
    return activeCount;

}

void DeviceController::draw(){
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    for(int i=0;i<numSensors;i++){
        if(rfids.at(i).getListening()){
            ofSetColor(255,128,128);
        } else {
            ofSetColor(255,255,255);
        }
        
        if(rfids.at(i).isAttached()){
            if(rfids.at(i).hasTag()){
                selected_img.draw(0,i*53);
            } else {
                active_img.draw(0,i*53);
            }
        } else {
            inactive_img.draw(0,i*53);

        }
        ofSetColor(255,255,255,64);
        ofRectRounded(53-5,i*53+10-5,rfids.at(i).confidence*246.0f+32+10,53-20+10,16+5);
        if(rfids.at(i).confidence<0.5f){
            ofSetColor(128,16,32);
        } else {
            ofSetColor(128,256,212);
        }

        ofRectRounded(53,i*53+10,rfids.at(i).confidence*246.0f+32,53-20,16);
        
       // cout << rfids.at(i).confidence << endl;
       // cout << rfids.at(i).title << ": " << rfids.at(i).isAttached() << ", " << rfids.at(i).hasTag() << endl;
    }
}

void DeviceController::report(){
    lock();
  //  for(int i=0;i<numSensors;i++){
        
        cout << getActiveSensorCount() << " sensors active, " << getLeftSensorCount() << " on the left, and " << getRightSensorCount() << " on the right" << endl;
    //for(int i=0;i<numSensors;i++){
       // cout << rfids.at(i).title << ": " << rfids.at(i).isAttached() << ", " << rfids.at(i).hasTag() << endl;
  //  }
    
    //int activeCount = 0;
    // cout << leftSensors.size() << " elems in leftSensors." << endl;
    cout << "left sensors: " ;
    for(int i=0;i<leftSensors.size();i++){
        //  cout << leftSensors.at(i)->isConfident();
        cout << leftSensors.at(i)->confidence << ", ";
    }
    cout << endl;
    
    cout << "right sensors: " ;
    for(int i=0;i<rightSensors.size();i++){
        //  cout << leftSensors.at(i)->isConfident();
        cout << rightSensors.at(i)->confidence << ", ";
    }
    cout << endl;

    
    unlock();
}