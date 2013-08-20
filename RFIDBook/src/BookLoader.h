//
//  BookLoader.h
//  RFIDBook
//
//  Created by Brett Peterson on 6/18/13.
//
//

#ifndef __RFIDBook__BookLoader__
#define __RFIDBook__BookLoader__

#include <iostream>
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "LanguageController.h"


struct MediaModel{
    string src;
    ofVec2f pos;
    int autoPlay;
    string mClass;
    int loopback;
    bool isHidden;
    int offset;
    int pulseType;
    int mediaType;
};

// parsing into MediaModel struct instead
// of XmlPage... it seemed confusing

//struct XmlPage {
 //   vector<MediaModel> medias;
/*    vector<string> media;
    vector<ofVec2f> position;
    vector<int> autoplay;
    vector<string> tapId;
    vector<int> loopback;
  */  
//};

class BookLoader{
    
public:
    
    BookLoader();
    ~BookLoader();
    
    vector< vector<MediaModel> > load(string fileName, LanguageController lang);
    
    ofxXmlSettings bookElements;
    
    //string fileName = "settings/book.xml";
    
    vector< vector<MediaModel> > pages;
    
    //LanguageController lang;
    
    
};

#endif /* defined(__RFIDBook__BookLoader__) */
