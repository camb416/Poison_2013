//
//  BookView.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#include "BookView.h"
BookView::BookView(){
    
}
BookView::~BookView(){
    
}
void BookView::setup(){
    
}
void BookView::update(){
    for(int i=0;i<pages.size();i++){
        pages.at(i)->update();
    }
}
void BookView::draw(){
    draw(0,0,0);
}
void BookView::draw(int x_in, int y_in, int debugState){
    if(debugState>0){
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(x_in,y_in);
    for(int i=0;i<pages.size();i++){
        pages.at(i)->draw(0,0,160,120);
        ofTranslate(25,25);
    }
    ofPopMatrix();
    } else {
        ofSetColor(255);
        backplate.draw(0,0,ofGetWidth(),ofGetHeight());
        ofPushMatrix();
        ofTranslate(x_in,y_in);
        for(int i=0;i<pages.size();i++){
            pages.at(i)->draw(0,0,ofGetWidth(),ofGetHeight());
            //ofTranslate(25,25);
        }
        ofPopMatrix();
    }
}
void BookView::addPage(string pagename_in){
    ofFadeImage * newPage = new ofFadeImage();
    newPage->setup(pagename_in);

    pages.push_back(newPage);
}
void BookView::addBackplate(string platename_in){
    backplate.loadImage(platename_in);
}
void BookView::activate(int pagenum_in){
for(int i=0;i<pages.size();i++){
    if(i==pagenum_in){
        pages.at(i)->fadeIn();
    } else {
        pages.at(i)->fadeOut();
    }
}
}
void BookView::deactivate(){
    activate(-1);
}
