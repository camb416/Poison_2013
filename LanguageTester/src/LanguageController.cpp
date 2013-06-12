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
    return false;
}