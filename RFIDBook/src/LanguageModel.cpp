//
//  LanguageModel.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 6/11/13.
//
//

#include "LanguageModel.h"

LanguageModel::LanguageModel(string _xmlfile){
    xml.loadFile(_xmlfile);
    string xmlToPrint;
    xml.copyXmlToString(xmlToPrint);
    cout << "PRINTING XML::: " << xmlToPrint;
    xml.pushTag("languages");
    // load the xml, make some Language structs
    int numLanguages = xml.getNumTags("language");
    
    for(int i=0;i<numLanguages;i++){
        //string ident = xml.getValue("language",0,i);
        string ident = xml.getAttribute("language", "id", "",i);
        string langName = xml.getAttribute("language","name","",i);
        
        int howManyAttributes = xml.getNumAttributes("language",i);
        cout << howManyAttributes << ". ident: " << ident << endl;
        
    }
    
    cout << ""; // for breakpoint debugging

                                    xml.popTag();
    
    
}

LanguageModel::~LanguageModel(){
    // empty destructor
}