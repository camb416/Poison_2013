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
    
    for(int i=0;i<mediaPages.size();i++){
        mediaPages.at(i)->update();
    }
    
}
void BookView::draw(){
    draw(0,0,0);
}
void BookView::draw(int x_in, int y_in, int debugState){
    
    // Debug draw
    if(debugState>0){
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(x_in,y_in);
//    for(int i=0;i<pages.size();i++){
//        pages.at(i)->draw(0,0,160,120);
//        ofTranslate(25,25);
//    }
        
    // Draw mediaPages
    for(int i=0;i<mediaPages.size();i++){
        // draw at 1/10th scale
        mediaPages.at(i)->draw(0,0,0.1f);
        ofTranslate(25,25);
    }
    ofPopMatrix();
    } else {
        ofSetColor(255);
        backplate.draw(0,0,ofGetWidth(),ofGetHeight());
        ofPushMatrix();
        ofTranslate(x_in,y_in);
//        for(int i=0;i<pages.size();i++){
//            pages.at(i)->draw(0,0,ofGetWidth(),ofGetHeight());
//            //ofTranslate(25,25);
//        }
        
        // Draw media pages
        for(int i=0;i<mediaPages.size();i++){
            mediaPages.at(i)->draw(0,0,1.0f);
        }
        ofPopMatrix();
    }
}
void BookView::addPage(string pagename_in){
    ofFadeImage * newPage = new ofFadeImage();
    newPage->setup(pagename_in);

    pages.push_back(newPage);
}


// Add all media elements and add to page
void BookView::addMediaPage(vector<string> mediaFiles, vector<ofVec2f> positions){
    
    Page * newPage = new Page();
    newPage->setup();
    
    for (int i = 0; i < mediaFiles.size(); i++) {
        
        newPage->addMedia(mediaFiles.at(i), positions.at(i));
        
    }
    
    mediaPages.push_back(newPage);
    ofLogNotice() << "added new page. total pages: " << mediaPages.size();
    
}

void BookView::addBackplate(string platename_in){
    backplate.loadImage(platename_in);
}

// Activate the current page
void BookView::activate(int pagenum_in){
for(int i=0;i<pages.size();i++){
    if(i==pagenum_in){
        pages.at(i)->fadeIn();
    } else {
        pages.at(i)->fadeOut();
    }
}

    // mediaPage
    for(int i=0;i<mediaPages.size();i++){
        if(i==pagenum_in){
            mediaPages.at(i)->fade(1);
        } else {
            mediaPages.at(i)->fade(-1);
        }
    }
}
void BookView::deactivate(){
    activate(-1);
}
