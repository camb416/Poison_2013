//
//  Page.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/10/13.
//
//

#include "Page.h"
#include "BookView.h"

Page::Page(){
    doDrag = false;
}
Page::~Page(){
    media.clear();
}

void Page::setup(){
  
    //
    // Media involved in left & right touch events & media faded out when touch active
    //
    touchMediaMatrix.resize(3);
}

void Page::setDrag(bool _doDrag){
    doDrag = _doDrag;
}

// Update all media elements on page

void Page::hideAllBorders(){
    for (int i = 0; i < media.size(); i++) {
        media.at(i)->setDraggable(false);
    }
}

void Page::dragUpdate(){

    // add toggleable draggy stuff
    if(!doDrag){
        ofPoint mousePos = ofPoint(ofGetMouseX(),ofGetMouseY());
        float nearestDist = 99999;
        int nearestID = -1;
        for (int i = 0; i < media.size(); i++) {
            ofPoint thisOrigin = media.at(i)->getPosition();
            float thisDist = ofDist(thisOrigin.x,thisOrigin.y,mousePos.x,mousePos.y);
            if(thisDist<nearestDist){
                nearestID = i;
                nearestDist = thisDist;
            }
            media.at(i)->setDraggable(false);
        }
        if(nearestID>-1){
            media.at(nearestID)->setDraggable(true);
            selectedMedia = media.at(nearestID);
        }
    } else {
        if(selectedMedia!=NULL){
            selectedMedia->moveTo(ofGetMouseX(),ofGetMouseY());
        }
    }
}
void Page::update(){
    for (int i = 0; i < media.size(); i++) {
        media.at(i)->update();
    }
    
}

void Page::draw(float originX, float originY, float scale){
    
    if (scale == 1.0f) {
        
        // Run the normal draw method for each media element
        for (int i = 0; i < media.size(); i++) {
            if(!media.at(i)->isHidden) media.at(i)->draw();
        }
        
    }
    else {
        // Run the scaled draw method for each media element
        for (int i = 0; i < media.size(); i++) {
            if(!media.at(i)->isHidden) media.at(i)->draw(scale);
        }
    }
    
}
void Page::addMedia(MediaModel _mm){

    Media * newMedia = new Media();
    newMedia->registerView(viewRef);
    
    string sub = _mm.src.substr(_mm.src.length()-3,3);
    if (sub == "png") {
        
        // run the setup for a media element that is just an image
        newMedia->setup(_mm);
//        newMedia->setup(_mm.src, _mm.pos.x, _mm.pos.y, _mm.mClass, _mm.isHidden, _mm.offset);
        
    }
    else if (sub == "mov"){
        
        // Check if video is a segmented one
        if (isSegVid(_mm.src) == true){
            newMedia->setup(_mm.src, _mm.pos.x, _mm.pos.y);
        }
        else {
            
            // Run the setup for a media element that is a video and an image
            string imageFile = _mm.src;
            imageFile.replace(_mm.src.length() -3, 3, "png");
            newMedia->setup(_mm.src, _mm.pos.x, _mm.pos.y, _mm.mClass, _mm.isHidden, _mm.offset);
        }
        
    }
    else {
        
        ofLogNotice() << "unrecognized media file extension: " << _mm.src;
        
    }
    
    media.push_back(newMedia);
}


// TODO: deprecate this
void Page::addMedia(string fileName, ofVec2f position, int autoplay, string tapId, int loopback, bool _isHidden, int _offset){
    
    Media * newMedia = new Media();
    newMedia->registerView(viewRef);
    
    string sub = fileName.substr(fileName.length()-3,3);
    if (sub == "png") {
        
        // run the setup for a media element that is just an image
        newMedia->setup(fileName, position.x, position.y, tapId, _isHidden,_offset);
        
    }
    else if (sub == "mov"){
        
        // Check if video is a segmented one
        if (isSegVid(fileName) == true){
            newMedia->setup(fileName, position.x, position.y);
        }
        else {
        
            // Run the setup for a media element that is a video and an image
            string imageFile = fileName;
            imageFile.replace(fileName.length() -3, 3, "png");
            // newMedia->setup(imageFile, fileName, position.x, position.y, autoplay, tapId, loopback);
            newMedia->setup("", fileName, position.x, position.y, autoplay, tapId, loopback, _isHidden, _offset);
            //newMedia->setBorder(true);
        }
        
    }
    else {
        
        ofLogNotice() << "unrecognized media file extension: " << fileName;
    
    }
    
    media.push_back(newMedia);
    //ofLogNotice() << "Added new media element " << fileName << " to page at position " << position.x << "," << position.y;
    
}

bool Page::isSegVid(string _fileName){
    if (_fileName.find("SEG") != string::npos){
        return true;
    } else {
        return false;
    }
}

void Page::receiveInput(char touchId_in, int pageNum_in){
/*
    int position = -1;
    
    // Look for character in valid inputs vector
    for (int i = 0; i < validInputs.size(); i++) {

        // Hide and elements according to which page we're on and which sensor was touched.
        
        if (validInputs.at(i) == touchId_in){
        
            if (touchId_in != currentTouch && touchActive == false){
                // Fade out elements that are in the way
                                
                try {
                    touchActive = true;
                    
                    // fade out media already live on page, marked with 'K' as touch ID
                    int size = touchMediaMatrix[2].size();
                    for (int i=0; i < size; i++){
                        media.at(touchMediaMatrix[2][i])->img.fadeOut();
                        media.at(touchMediaMatrix[2][i])->vid.fadeOut();
                        media.at(touchMediaMatrix[2][i])->stopVid();
                    }
                    
                    if (touchId_in == 'H'){
                        media.at(touchMediaMatrix[0][0])->playVid();
                        media.at(touchMediaMatrix[0][0])->vid.fadeIn();
                    } else if (touchId_in == 'J'){
                        media.at(touchMediaMatrix[1][0])->playVid();
                        media.at(touchMediaMatrix[1][0])->vid.fadeIn();
                    }
                } catch (...) {
                    touchActive = false;
                    ofLogError() << "Error playing media" << " on page " << pageNum_in;
                }

    currentTouch = touchId_in;
    }
    }
}
 */
}




void Page::fade(int dir){
    
    // Loop through media elements and fade them in or out
    float minFadeIn = 4.0f;
    float maxFadeIn = 64.0f;
    float minFadeOut = 2.0f;
    float maxFadeOut = 8.0f;
    
    if (dir == 1) {
        for (int i = 0; i < media.size(); i++) {
            if(!media.at(i)->isHiddenByDefault){
            
                float fadeVal = ofRandomuf()*(maxFadeIn-minFadeIn)+minFadeIn;
               // int offsetVal = ofRandomuf()*5000;
                if(media.at(i)->mediaType==IMGMEDIA  ){
                    media.at(i)->show(fadeVal,true);
//                    media.at(i)->img->fadeIn(fadeVal);
                }
                
            
                // If autoplay is on for the video, start playing
                
                if (media.at(i)->mediaType == VIDMEDIA){
                    //TODO: update this
                    if (media.at(i)->autoplay == 1){
                        media.at(i)->playVid();
                    }
                    media.at(i)->vid->fadeIn(fadeVal);
                }
                // TODO: updatethis
                if (media.at(i)->mediaType == SEGMEDIA){
                    if (media.at(i)->autoplay == 1){
                        media.at(i)->playVid();
                    }
                    media.at(i)->segVid->fadeIn(fadeVal);
                    media.at(i)->segVid->showButton = false;
                }
                }
        }
    }
    else {
        for (int i = 0; i < media.size(); i++) {
            // TODO - handle video fade out as well
           
            float fadeVal = ofRandomuf()*(maxFadeOut-minFadeOut)+minFadeOut;
            // cout << fadeVal << endl;
            
            if(media.at(i)->mediaType==IMGMEDIA) media.at(i)->hide();
            if(media.at(i)->mediaType==VIDMEDIA) {
                media.at(i)->vid->fadeOut(fadeVal);
                media.at(i)->vidState = 0;
                // TODO: debug this! stop all video
                media.at(i)->stopVid();
            }
            if(media.at(i)->mediaType==SEGMEDIA) {
                media.at(i)->segVid->fadeOut(fadeVal);
                media.at(i)->vidState = 0;
                // TODO: debug this! stop all video
                media.at(i)->stopVid();
            }
        }
    }
    
}
ofxXmlSettings Page::getXML(){
    ofxXmlSettings xml;
    xml.addTag("Page");
    xml.pushTag("Page");
    for(int i=0;i<media.size();i++){
        xml.addTag("Media");
        ofPoint pt = media.at(i)->getPosition();
        xml.setAttribute("Media", "x", (int)pt.x,i);
        xml.setAttribute("Media", "y", (int)pt.y,i);
        xml.setAttribute("Media", "src", media.at(i)->getFileName(),i);
        xml.setAttribute("Media", "auto", (int)media.at(i)->autoplay, i);
        xml.setAttribute("Media", "class", (string)media.at(i)->mClass, i);
        xml.setAttribute("Media", "loopback", (int)media.at(i)->loopback, i);
        xml.setAttribute("Media", "hidden", (int)media.at(i)->isHiddenByDefault, i);
        xml.setAttribute("Media", "offset", (int)media.at(i)->offset, i);
    }
    return xml;
}

void Page::printCurrentMedia(){
    for(int i=0;i<media.size();i++){
        media.at(i)->printInfo();
        //cout << "a media element." << endl;
    }
}

void Page::printCurrentMediaByClassName(string _id){
    vector<Media*> mediaToPrint;
    mediaToPrint = getMediaByClassName(_id);
    
    for(int i=0;i<mediaToPrint.size();i++){
        mediaToPrint.at(i)->printInfo();
    }
    
}
vector<Media*> Page::getMediaByClassName(string _id){
    vector<Media*> returnVal;
    
    // TODO: search through and return Media pointers
    // done?
    
    for(int i=0;i<media.size();i++){
       
        if(media.at(i)->mClass.compare(_id)==0){
            returnVal.push_back(media.at(i));
            Media * thisMedia = (Media*) media.at(i);
            //thisMedia->setBorder(true);
        }

    }
    
    
    return returnVal;
    
}

vector<Media*> Page::getSegmentedMedia(){
    
    vector<Media*> returnVal;
    
    for(int i=0;i<media.size();i++){
        
        if(isSegVid(media.at(i)->getFileName())==1){
            returnVal.push_back(media.at(i));
            Media * thisMedia = (Media*) media.at(i);
            //thisMedia->setBorder(true);
        }
        
    }
    
    
    return returnVal;
}

