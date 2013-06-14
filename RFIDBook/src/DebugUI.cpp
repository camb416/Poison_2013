//
//  DebugUI.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 6/14/13.
//
//

#include "DebugUI.h"

DebugUI::DebugUI(){
    bDragUIcheckbox = bDragUIcheckbox_prev = false;
    saveXMLbtn = false;
    loadXMLbtn = false;
    defaultXMLbtn = false;
    isVisible = false;
}
DebugUI::~DebugUI(){
    
}

bool DebugUI::getIsVisible(){
    return isVisible;
}

void DebugUI::setup(DeviceController * _devices, BookController * _book, BookView * _bookView){
    devices = _devices;
    book = _book;
    bookView = _bookView;
    
    tfield.setup();
    tfield.update("Magic Book", 16,660);
    
     aValue = 0.5f;
    bar.setup("Page Confidence", &aValue, 600, 16);
    bar.setPosition(ofPoint(16,749));

    
    gui.hide();
    gui.addTitle("Magic Book");
    gui.addToggle("Drag UI",bDragUIcheckbox);
    gui.addButton("default XML", defaultXMLbtn);
    gui.addButton("load XML", loadXMLbtn);
    gui.addButton("save XML", saveXMLbtn);
}
void DebugUI::update(){
    bar.update();
    
    tfield.update("Magic Book \n" + book->getReport() + "\n" + book->whatSituation());

    if(ofGetMousePressed()){
        pos_ui.update();
        aValue = ofRandom(1.0f);
    }
    
    if(bDragUIcheckbox!=bDragUIcheckbox_prev){
    
    if(bDragUIcheckbox){
        bookView->showDragUI();
    } else {
        bookView->hideDragUI();
    }
        bDragUIcheckbox_prev = bDragUIcheckbox;
    }
}
bool DebugUI::getDragSetting(){
    return bDragUIcheckbox;
}
void DebugUI::draw(){
    
    if(isVisible){
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,212);
        ofFill();
        ofRect(0,0,ofGetWidth(),ofGetHeight());
        ofSetColor(255,255,255,255);
        devices->draw(10,300);
        tfield.draw();
        bar.draw();
        if(ofGetMousePressed()) pos_ui.draw();
    
        gui.draw();
    }
}
void DebugUI::show(){
    gui.show();
}
void DebugUI::hide(){
    gui.hide();
}
void DebugUI::toggle(){
    isVisible = !isVisible;
    isVisible ? show() : hide();
}