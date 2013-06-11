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
    void draw(float originX, float originY, float scale);
    
    void addMedia(string fileName, ofVec2f position);
    void receiveInput(char input);
    
    void fade(int dir);
    
    vector<Media*> media;
    vector<char> validInputs;
    

};

#endif /* defined(__RFIDBook__Page__) */
