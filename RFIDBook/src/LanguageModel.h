//
//  LanguageModel.h
//  RFIDBook
//
//  Created by Cameron Browning on 6/11/13.
//
//

#ifndef __RFIDBook__LanguageModel__
#define __RFIDBook__LanguageModel__

#include "ofxXmlSettings.h"
#include <iostream>

class LanguageModel{
public:
    LanguageModel(string _xmlfile);
    ~LanguageModel();
    
private:
    ofxXmlSettings xml;
    
    
};

#endif /* defined(__RFIDBook__LanguageModel__) */
