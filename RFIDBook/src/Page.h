//
//  Page.h
//  RFIDBook
//
//  Created by Brett Peterson on 6/10/13.
//
//

#ifndef __RFIDBook__Page__
#define __RFIDBook__Page__

#include "ofMain.h"
#include "Media.h"
#include "ofxXmlSettings.h"
#include <iostream>

class Page {
    
public:
    Page();
    ~Page();
    
    void setup(); 
    void update();
    void dragUpdate();
    void draw(float originX, float originY, float scale);
    
    void addMedia(string fileName, ofVec2f position);
    
    void setDrag(bool _doDrag);
    
    void receiveInput(char input);
    
    void fade(int dir);
    
    vector<Media*> media;
    vector<char> validInputs;
    Media* selectedMedia;
    
    ofxXmlSettings getXML();
    
    
private:
    bool doDrag;
    

};

#endif /* defined(__RFIDBook__Page__) */
