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
#include <iostream>

class Page {
    
public:
    Page();
    ~Page();
    
    void setup();
    void update();
    void draw();
    
    void addMedia(string fileName, ofVec2f);
    void receiveInput(char input);
    
    vector<Media> media;
    vector<char> validInputs;
    

};

#endif /* defined(__RFIDBook__Page__) */
