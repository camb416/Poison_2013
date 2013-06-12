//
//  LanguageController.h
//  LanguageTester
//
//  Created by Cameron Browning on 6/12/13.
//
//

#ifndef __LanguageTester__LanguageController__
#define __LanguageTester__LanguageController__

#include <iostream>
#include "LanguageModel.h"
#include "ofMain.h"

class LanguageController{
public:
    LanguageController();
    ~LanguageController();
    
    bool load(string settingsfile="settings/languages.xml");
    bool toggleLanguage();
    bool setLanguage(string _ident);
    string resolvePath(string _filepath);
    
private:
    LanguageModel model;
    
};

#endif /* defined(__LanguageTester__LanguageController__) */
