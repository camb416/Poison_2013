//
//  BookModel.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#include "BookModel.h"
BookModel::BookModel(){
    
}
BookModel::~BookModel(){
    
}
void BookModel::setup(){
    
}
void BookModel::update(){
    for(int i=0;i<pages.size();i++){
        pages.at(i)->update();
    }
}
void BookModel::draw(){
    draw(0,0);
}
void BookModel::draw(int x_in, int y_in){
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(x_in,y_in);
    for(int i=0;i<pages.size();i++){
        pages.at(i)->draw();
        ofTranslate(25,25);
    }
    ofPopMatrix();
}
void BookModel::addPage(string pagename_in){
    ofFadeImage * newPage = new ofFadeImage();
    newPage->setup(pagename_in);

    pages.push_back(newPage);
}
void BookModel::activate(int pagenum_in){
for(int i=0;i<pages.size();i++){
    if(i==pagenum_in){
        pages.at(i)->fadeIn();
    } else {
        pages.at(i)->fadeOut();
    }
}
}
