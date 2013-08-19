//
//  LanguageController.cpp
//  LanguageTester
//
//  Created by Cameron Browning on 6/12/13.
//
//

#include "LanguageController.h"

LanguageController::LanguageController(){
    lastLanguageChanged = ofGetElapsedTimef();
}
LanguageController::~LanguageController(){
    
}
bool LanguageController::load(string settingsfile){
    return model.load(settingsfile);
}
bool LanguageController::toggleLanguage(){
    if(model.getNumLanguages()>1 && (ofGetElapsedTimef() - lastLanguageChanged)>5.0f){
        ofLogWarning() << "toggle languages unsuccessful";
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

    string langSpec_str;
    string common_str;
    
    string prefix ="assets/";
    string filePath;
    
    int slashIndex = _filepath.find_last_of("/");
    
    if(slashIndex<0){
    
        langSpec_str = model.getCurrentLanguageId() + "/" + _filepath;
        common_str = "assets/common/" + _filepath;
        filePath = _filepath;
    
    } else if(slashIndex==0){
        // slash is the first char
        langSpec_str = model.getCurrentLanguageId()  + _filepath;
        common_str = "assets/common" + _filepath;
        filePath = _filepath;

        
    } else {
        // has a slash
        //prefix += _filepath.substr(0,slashIndex+1);
        filePath = _filepath.substr(slashIndex+1);
        
        langSpec_str = prefix + model.getCurrentLanguageId() + "/" + _filepath;
        common_str = prefix + "common/" + filePath;
        
    }
    
    bool isLanguageSpecific = ofFile::doesFileExist(langSpec_str);
    bool isAtOrigin = ofFile::doesFileExist(prefix+filePath);
    bool isInCommon= ofFile::doesFileExist(common_str);
    
    if(isLanguageSpecific && isAtOrigin){
        cout << "WARNING: You have duplicate files at: " << langSpec_str << " and " << _filepath << "." << endl;
        return langSpec_str;
    } else if(isLanguageSpecific){
        return langSpec_str;
    } else if(isInCommon){
        return common_str;
    } else if(isAtOrigin){
        return (prefix+filePath);
    } else {
        cout << "file not found: " << _filepath << endl;
        return "FILE NOT FOUND";
    }
}