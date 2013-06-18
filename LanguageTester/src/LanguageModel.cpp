//
//  LanguageModel.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 6/11/13.
//
//

#include "LanguageModel.h"

LanguageModel::LanguageModel(){
    
}

bool LanguageModel::load(string _xmlfile){
    cout << "trying to load: " << _xmlfile << endl;
    numLanguages = -1;
    currentLanguageIndex = 0;
    
    xml.loadFile(_xmlfile);
   
    // parse the file, build a vector of structs.
    xml.pushTag("languages");
    numLanguages = xml.getNumTags("language");
    
    for(int i=0;i<numLanguages;i++){
        Language lang;
        lang.ident = xml.getAttribute("language", "id", "",i);
        lang.name = xml.getAttribute("language","name","",i);
        int howManyAttributes = xml.getNumAttributes("language",i);
        languages.push_back(lang);
    }
    xml.popTag();
    
    // write a report to the console
    report();
    
    // return success
    if(numLanguages>0){
        return true;
    } else {
        return false;
    }
    

    
}

int LanguageModel::getCurrentLanguageNum(){
    return currentLanguageIndex;
}

int LanguageModel::getNumLanguages(){
    return numLanguages;
}

int LanguageModel::hasLanguage(string _ident){
    int desiredId = -1;
    for(int i=0;i<numLanguages;i++){
        if(languages.at(i).ident.compare(_ident)==0){
            desiredId = i;
            break;
        }
    }
    return desiredId;
}

bool LanguageModel::setCurrentLanguage(int _langid){
    currentLanguageIndex = _langid;
    cout << "language changed to: " << languages.at(currentLanguageIndex).name << "." << endl;;
}

string LanguageModel::getLanguageIdentAt(int _index){
    string returnVal = "";
    if(_index>-1 && _index < numLanguages){
        returnVal = languages.at(_index).ident;
    } else {
        cout << "error: language not found at index: " << _index << "." << endl;
    }
    return returnVal;
}

void LanguageModel::report(){
    cout << " --------- LANGUAGE REPORT ---------" << endl;
   for(int i=0;i<numLanguages;i++){
       
       cout << "Language: " << languages.at(i).name << ", id: " << languages.at(i).ident << ".";
       if(i == currentLanguageIndex) cout << " (CURRENT) ";
       cout << endl;
   }
    cout << "getcurrentlanguagename: " << getCurrentLanguageName() << endl;
    cout << "getcurrentlanguageid: " << getCurrentLanguageId() << endl;
    cout << "---------                ---------" << endl;
}

Language LanguageModel::getCurrentLanguage(){
    if(languages.size()>0 && currentLanguageIndex < languages.size()){
    return languages.at(currentLanguageIndex);
    } else {
        cout << "There was a problem in getCurrentLanguage";
        Language nullLang;
        return nullLang;
    }
}

string LanguageModel::getCurrentLanguageName(){
    return getCurrentLanguage().name;
}
string LanguageModel::getCurrentLanguageId(){
    return getCurrentLanguage().ident;
}


LanguageModel::~LanguageModel(){
    // empty destructor
}