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
    LanguageModel();
    ~LanguageModel();
    bool load(string _xmlfile);
    void report();
    Language getCurrentLanguage();
    string getCurrentLanguageName();
    string getCurrentLanguageId();
    int getNumLanguages();
    int getCurrentLanguageNum();
    string getLanguageIdentAt(int _index);
    int hasLanguage(string _ident);
    bool setCurrentLanguage(int _langid);
    
private:
    ofxXmlSettings xml;
    vector<Language> languages;
    int currentLanguageIndex;
    int numLanguages;
    
    
};

#endif /* defined(__RFIDBook__LanguageModel__) */
