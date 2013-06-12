//
//  LanguageModel.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 6/11/13.
//
//

#include "LanguageModel.h"

LanguageModel::LanguageModel(string _xmlfile){
    
    currentLanguageIndex = 0;
    
    // TODO: Add error correction on loading this file
    xml.loadFile(_xmlfile);
    
    
    // load the xml, make some Language structs
    numLanguages = xml.getNumTags("language");
    

    // parse the file, build a vector of structs.
    xml.pushTag("languages");
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