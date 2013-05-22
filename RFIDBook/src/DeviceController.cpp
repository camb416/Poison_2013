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
    cycleTime = 120; // ms to cycle the RFID antennae
    numSensors = 6;
    
    inactive_img.loadImage("radio_inactive.png");
    active_img.loadImage("radio_active.png");
    selected_img.loadImage("radio_selected.png");
    
    for(int i=0;i<numSensors;i++){
        RFIDDevice * aDevice = new RFIDDevice();
        rfids.push_back(aDevice);
        if(i%2==0){
            leftSensors.push_back(aDevice);
        } else {
            rightSensors.push_back(aDevice);
        }
    }
    
    timer.start();
    rfids.at(0)->setup("top-left",this);
   rfids.at(1)->setup("top-right",this);
    rfids.at(2)->setup("middle-left",this);
    rfids.at(3)->setup("middle-right",this);
    rfids.at(4)->setup("bottom-left",this);
    rfids.at(5)->setup("bottom-right",this);

      rfids.at(0)->connect(308147);
     rfids.at(1)->connect(308137);
        rfids.at(2)->connect(309045);
        rfids.at(3)->connect(308150);
        rfids.at(4)->connect(112512);
    rfids.at(5)->connect(308152);






    lastTime = 0;
    curSensor = 0;
}
void DeviceController::doSomething(){
    // deprecated
    cout << "do something here when you get a tag." << endl;
}



void DeviceController::update(){

    for(int i=0;i<numSensors;i++){
        if(rfids.at(i)->isAttached()){
            if(rfids.at(i)->hasTag()){
                rfids.at(i)->confidence = 1.0f;
            } else {
               rfids.at(i)->confidence = 0.0f;
                //rfids.at(i)->confidence_dest = 0.0f;
            }
        } else {
            rfids.at(i)->confidence = 0.0f;
            //rfids.at(i)->confidence_dest = 0.0f;
        }
        //rfids.at(i)->confidence += (rfids.at(i)->confidence_dest- rfids.at(i)->confidence)/16.0f;
        rfids.at(i)->confidence -= 0.002f;
        rfids.at(i)->confidence = MAX(0.0f,MIN(rfids.at(i)->confidence,1.0f));
        // cout << rfids.at(i).title << ": " << rfids.at(i).isAttached() << ", " << rfids.at(i).hasTag() << endl;
    }
}

int DeviceController::getSensorId(string idLookup){
    int idToReturn = -1;
    for(int i=0;i<numSensors;i++){
        //cout << rfids.at(i)->title << endl;
        if(idLookup.compare(rfids.at(i)->title)==0){
            idToReturn = i;
        }
    }
    if(idToReturn == -1){
        cout << "WARNING: phidget not found: " << idLookup << "." << endl;
    }
    return idToReturn;
}
RFIDDevice * DeviceController::getSensor(string idLookup){
    RFIDDevice * returnVal = 0;
    int whatId = getSensorId(idLookup);
    if(whatId>=0 && whatId<rfids.size()){
    returnVal = rfids.at(whatId);
    }
    return returnVal;
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
        if(rfids.at(i)->isConfident()){
            activeCount++;
        }
    }
    return activeCount;

}

void DeviceController::draw(){
    
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    for(int i=0;i<numSensors;i++){
        if(rfids.at(i)->getListening()){
            ofSetColor(255,128,128);
        } else {
            ofSetColor(255,255,255);
        }
        
        if(rfids.at(i)->isAttached()){
            if(rfids.at(i)->hasTag()){
                selected_img.draw(0,i*53);
            } else {
                active_img.draw(0,i*53);
            }
        } else {
            inactive_img.draw(0,i*53);

        }
        ofSetColor(255,255,255,64);
        ofRectRounded(53-5,i*53+10-5,rfids.at(i)->confidence*246.0f+32+10,53-20+10,16+5);
        if(rfids.at(i)->confidence<0.5f){
            ofSetColor(128,16,32);
        } else {
            ofSetColor(128,256,212);
        }

        ofRectRounded(53,i*53+10,rfids.at(i)->confidence*246.0f+32,53-20,16);
        ofPoint p;
        p.x = 53+rfids.at(i)->confidence*246.0f+32 + 32;
        p.y = i*53+10+8;
        stringstream ss;//create a stringstream
        ss << rfids.at(i)->serial << "\n" << rfids.at(i)->currentTag;//add number to the stream
        ofDrawBitmapString(ss.str(), p);
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
    /*
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
*/
    
    unlock();
}