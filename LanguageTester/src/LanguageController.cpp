//
//  LanguageController.cpp
//  LanguageTester
//
//  Created by Cameron Browning on 6/12/13.
//
//

#include "LanguageController.h"

LanguageController::LanguageController(){

}
LanguageController::~LanguageController(){
    
}
bool LanguageController::load(string settingsfile){
    return model.load(settingsfile);
}
bool LanguageController::toggleLanguage(){
    if(model.getNumLanguages()>1){
        int newLanguage = model.getCurrentLanguageNum();
        newLanguage++;
        if(newLanguage>=model.getNumLanguages()){
            newLanguage = 0;
        }
        string identToSwap = model.getLanguageIdentAt(newLanguage);
        setLanguage(identToSwap);
    } else {
        return false;
    }
}
bool LanguageController::setLanguage(string _ident){
    bool returnVal = false;
    int desiredId = -1;
    if(_ident.length()==0){
        cout << "error: attempting to swap to a language that has no identifier" << endl;
    } else if(model.hasLanguage(_ident)>-1){
        desiredId = model.hasLanguage(_ident);
        returnVal = model.setCurrentLanguage(desiredId);
        
    } else {
        cout << "error: language \"" << _ident << "\" not found." << endl;
    }
    return returnVal;
}
string LanguageController::resolvePath(string _filepath){
    // TO DO... implement this.
    string langSpec_str;
    string default_str;
    langSpec_str = model.getCurrentLanguageId() + "/" + _filepath;
    default_str = "default/" + _filepath;
    
    cout << "resolving " << _filepath << " into " << langSpec_str << "." << endl;
    cout << "does it exist? " ;
    
    bool isLanguageSpecific = ofFile::doesFileExist(langSpec_str);
    bool isAtOrigin = ofFile::doesFileExist(_filepath);
    bool isInDefault = ofFile::doesFileExist(default_str);
    
    isLanguageSpecific ? cout << "YES." << endl : cout << "No." << endl;
    
    if(isLanguageSpecific && isAtOrigin){
        cout << "WARNING: You have duplicate files at: " << langSpec_str << " and " << _filepath << "." << endl;
    } else if(isLanguageSpecific){
        return langSpec_str;
    } else if(isInDefault){
        return default_str;
    }
    
    return return_str;
}