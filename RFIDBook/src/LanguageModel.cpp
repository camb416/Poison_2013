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
}

LanguageModel::~LanguageModel(){
    // empty destructor
}