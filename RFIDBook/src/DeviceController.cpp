//
//  DeviceController.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/7/13.
//
//

#include "DeviceController.h"

using namespace std;

void DeviceController::loadDeviceDetails(){
    ///////////////////////////////////////////////////////////////////////////
    //////////////////// rfid-devices.xml /////////////////////////////////////
    /* ////////////////////////////////////////////////////////////////////////
     
     <!-- keep the xml elements in this order, only change the serial numbers -->
     <devices>
        <device>
            <location>top-left</location>
            <serial>335342</serial>
        </device>
         <device>
             <location>top-right</location>
             <serial>335300</serial>
         </device>
         <device>
             <location>middle-left</location>
             <serial>335334</serial>
         </device>
         <device>
             <location>middle-right</location>
             <serial>335095</serial>
         </device>
         <device>
             <location>bottom-left</location>
             <serial>335113</serial>
         </device>
         <device>
             <location>bottom-right</location>
             <serial>335290</serial>
         </device>
     </devices>
     */

    ///////////////////////////////////////////////////////////////////////////
    //////////////////// //////////////// /////////////////////////////////////
    
    // 1. load an XML
    device_xml.loadFile("settings/rfid-devices.xml");
    device_xml.pushTag("devices");
    
    int numDeviceElems = device_xml.getNumTags("device");
    
    if(numDeviceElems!=6){
        cout << "only found " << numDeviceElems << ". There should be six";
    } else {
        // 2. loop through the xml objects...
        for(int i=0;i<numDeviceElems;i++){
            device_xml.pushTag("device",i);
            // 3. for each xml object
            string location_str = device_xml.getValue("location","notfound");
            int serial_int = device_xml.getValue("serial",-1);
            cout << "tag element: " << location_str << " : " << serial_int << endl;
            // 4. push back a new RFIDDevice
            RFIDDevice * aDevice = new RFIDDevice();
            rfids.push_back(aDevice);
            if(i%2==0){
                leftSensors.push_back(aDevice);
            } else {
                rightSensors.push_back(aDevice);
            }
            rfids.at(i)->setup(location_str,this);
            rfids.at(i)->connect(serial_int);

            
            device_xml.popTag();
        }
    }
}

void DeviceController::setup(){
    bSeenRFID = false;
    cycleTime = 125; // ms to cycle the RFID antennae
    numSensors = 6;
    
    inactive_img.loadImage("assets/common/radio_inactive.png");
    active_img.loadImage("assets/common/radio_active.png");
    selected_img.loadImage("assets/common/radio_selected.png");
    
    timer.start();
    
    // loading RFID details from XML...
    loadDeviceDetails();
    
    // hard-coded RFID details...
    /*
    for(int i=0;i<numSensors;i++){
        RFIDDevice * aDevice = new RFIDDevice();
        rfids.push_back(aDevice);
        if(i%2==0){
            leftSensors.push_back(aDevice);
        } else {
            rightSensors.push_back(aDevice);
        }
    }
    
    
    rfids.at(0)->setup("top-left",this);
    rfids.at(1)->setup("top-right",this);
    rfids.at(2)->setup("middle-left",this);
    rfids.at(3)->setup("middle-right",this);
    rfids.at(4)->setup("bottom-left",this);
    rfids.at(5)->setup("bottom-right",this);

    rfids.at(0)->connect(335342);
    rfids.at(1)->connect(335300);
    rfids.at(2)->connect(335334);
    rfids.at(3)->connect(335095);
    rfids.at(4)->connect(335113);
    rfids.at(5)->connect(335290);

    */
    
    lastTime = 0;
    curSensor = 0;
    
    // Set up touch controller
    kit.useEvents(false);
    serialId = -1;
    bool isKitConnected = kit.connect(serialId);    // Serial ID of phidget connector
    if (isKitConnected == true){
        kit.print(-1);
    }
    else {
        kitConnected = false;
    }

}

bool DeviceController::hasSeenRFID(){
    return bSeenRFID;
}


void DeviceController::update(){

    
    for(int i=0;i<numSensors;i++){
        if(rfids.at(i)->isAttached()){
            bSeenRFID = true;
            if(rfids.at(i)->hasTag()){
                rfids.at(i)->confidence = 1.0f;
            } else {
               rfids.at(i)->confidence = 0.0f;
                //rfids.at(i)->confidence_dest = 0.0f;
            }
        } else {
            rfids.at(i)->confidence = 0.0f;
        }
        rfids.at(i)->confidence -= 0.002f;
        rfids.at(i)->confidence = MAX(0.0f,MIN(rfids.at(i)->confidence,1.0f));
    }
    
    if (kitConnected == true){
        kit.updateKits();
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
    for(int i=0;i<leftSensors.size();i++){
        if(leftSensors.at(i)->isConfident()){
            activeCount++;
        }
    }
    return activeCount;
}
int DeviceController::getRightSensorCount(){
    int activeCount = 0;
    for(int i=0;i<rightSensors.size();i++){
        if(rightSensors.at(i)->isConfident()){
            activeCount++;
        }
    }
    return activeCount;
}

int DeviceController::getActiveSensorCount(){
    int activeCount = 0;
    for(int i=0;i<numSensors;i++){
        if(rfids.at(i)->isConfident()) activeCount++;
    }
    return activeCount;

}

void DeviceController::draw(int _x, int _y){
    
    ofPushMatrix();
    ofTranslate(_x, _y);
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
    }
    ofSetColor(0,0,0);
    ofDrawBitmapString("interface kit touch sensors", 0, 340);
    ofDrawBitmapString(ofToString(serialId), 250, 340);
    for (int i=0; i<8; i++){
        ofSetColor(0,0,0);
        bool sensorVal = hasTouch(i);
        ofDrawBitmapString(ofToString(i), i*53+20, 400);
        ofSetColor(255,255,255);
        if (sensorVal == true){
            selected_img.draw(i*53,345);
            
        } else {
            active_img.draw(i*53,345);
        }
    }
    ofPopMatrix();
}

void DeviceController::report(){
    lock();
    cout << getActiveSensorCount() << " sensors active, " << getLeftSensorCount() << " on the left, and " << getRightSensorCount() << " on the right" << endl;
    unlock();
}

bool DeviceController::hasTouch(int sensorID){
    bool touchState = false;
    
    if (kitConnected == true) {
        touchState = kit.getBool(serialId, sensorID);
    }
    
    return touchState;
}

void DeviceController::printTouchSensors(){
    kit.print();
}

//int DeviceController::touchSensor(string sensor){
//    int sensorID;
//    
//    if (sensor == "left"){
//        sensorID = 0;
//    } else if (sensor == "right"){
//        sensorID = 1;
//    } else{
//        ofLogWarning() << "invalid touch sensor request: " << sensor;
//    }
//
//    return sensorID;
//}

bool DeviceController::getTouchBool(int _whichSensor, int _whichKit){
    if(_whichKit!=-1) ofLogWarning() << "using DeviceController::getTouchBool to specify an IFKit not supported...yet.";
    return kit.getBool(_whichKit, _whichSensor);
}
