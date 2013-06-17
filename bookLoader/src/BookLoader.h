//
//  BookLoader.h
//  bookLoader
//
//  Created by Brett Peterson on 6/12/13.
//
//

#ifndef __bookLoader__BookLoader__
#define __bookLoader__BookLoader__

#include <iostream>
#include "ofMain.h"
#include "ofxXmlSettings.h"


struct Page {
    vector<string> media;
    vector<ofVec2f> position;
    
};

class BookLoader{
    
public:
  
    BookLoader();
    ~BookLoader();

    void load();

    ofxXmlSettings bookElements;

    string fileName = "settings/book.xml";
    
    vector<Page> pages;


};

#endif /* defined(__bookLoader__BookLoader__) */
