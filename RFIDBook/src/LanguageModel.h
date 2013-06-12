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

struct Language {
    string ident;
    string name;
};

class LanguageModel{
public:
    LanguageModel(string _xmlfile);
    ~LanguageModel();
    void report();
    Language getCurrentLanguage();
    string getCurrentLanguageName();
    string getCurrentLanguageId();
    
private:
    ofxXmlSettings xml;
    vector<Language> languages;
    int currentLanguageIndex;
    int numLanguages;
    
    
};

#endif /* defined(__RFIDBook__LanguageModel__) */
