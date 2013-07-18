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
    
    void addMedia(string fileName, ofVec2f position, int autoplay, string tapId, int loopback, bool _isHidden);
    
    void setDrag(bool _doDrag);
    
    void receiveInput(char touchId_in, int pageNum_in);
    
    void fade(int dir);
    
    vector<Media*> media;
    vector<char> validInputs;
    Media* selectedMedia;
    
    ofxXmlSettings getXML();
    
    void hideAllBorders();
    
    bool touchActive;
    bool pageReset;

    int activeMedia;
    int activePage;
    char currentTouch;
    
    vector<vector<int> > touchMediaMatrix;
    
    void printCurrentMedia();
    void printCurrentMediaByClassName(string _id);
    vector<Media *> getMediaByClassName(string _id);
    
private:
    bool doDrag;
    
    int fadeOutMedia;
};

#endif /* defined(__RFIDBook__Page__) */
