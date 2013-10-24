#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // 1. load an XML
    device_xml.loadFile("rfid-devices.xml");
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

            device_xml.popTag();
        }
    }
    

    

    

    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}