//
//  BookView.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#include "BookView.h"
BookView::BookView(){
    currentPage = -1;
    bShowDragUI = false;
    isSetup = false;
    cout << "OKAY, THE BOOKVIEW EXISTS... HERE THE CONSTRUCTOR TO PROVE IT" << endl;
}
BookView::~BookView(){
    
}

void BookView::showDragUI(){

    bShowDragUI = true;

}
void BookView::hideDragUI(){

    bShowDragUI = false;
    if(currentPage>=0){
        mediaPages.at(currentPage)->hideAllBorders();
    }
    
}

void BookView::setup(){
    
}
void BookView::update(){
    /*for(int i=0;i<pages.size();i++){
        pages.at(i)->update();
    }
    */
    if(currentPage>=0 && bShowDragUI) mediaPages.at(currentPage)->dragUpdate();
    for(int i=0;i<mediaPages.size();i++){
        mediaPages.at(i)->update();
    }
    
}
void BookView::draw(){
    ofEnableAlphaBlending();
    draw(0,0,0);
}
void BookView::draw(int x_in, int y_in, int debugState){
    
    // Debug draw
    if(debugState>0){
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(x_in,y_in);
        

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

        // Draw media pages
        for(int i=0;i<mediaPages.size();i++){
            mediaPages.at(i)->draw(0,0,1.0f);
        }
        ofPopMatrix();
    }
}

// Add all media elements and add to page
void BookView::addPage(vector<string> mediaFiles, vector<ofVec2f> positions){
    
    Page * newPage = new Page();
    newPage->setup();
    
    ofPoint pt;
    
    for (int i = 0; i < mediaFiles.size(); i++) {
        if(i < 0 || i>=positions.size()){
            pt = ofPoint(0,0);
        } else {
            pt = positions.at(i);
        }
        newPage->addMedia(mediaFiles.at(i), pt);
        
    }
    
    mediaPages.push_back(newPage);
    ofLogNotice() << "added new page. total pages: " << mediaPages.size();
    
}

void BookView::addBackplate(string platename_in){
    backplate.loadImage(platename_in);
}

void BookView::mousePressed(){
    if(currentPage>=0){
        mediaPages.at(currentPage)->setDrag(true);
    }
}
void BookView::mouseReleased(){
    if(currentPage>=0){
        mediaPages.at(currentPage)->setDrag(false);
    }
}

// Activate the current page
void BookView::activate(int pagenum_in){
/*
    for(int i=0;i<pages.size();i++){
    if(i==pagenum_in){
        pages.at(i)->fadeIn();
    } else {
        pages.at(i)->fadeOut();
    }
}
*/
    // mediaPage
   // if(pagenum_in!=currentPage)
     if(pagenum_in != currentPage){
    for(int i=0;i<mediaPages.size();i++){
       
        if(i==pagenum_in){
            mediaPages.at(i)->fade(1);
        } else {
            mediaPages.at(i)->fade(-1);
        }
        }
    }
    
    currentPage = pagenum_in;
}


void BookView::deactivate(){
    activate(-1);
}

void BookView::savePageLayout(){
    for(int i=0;i<mediaPages.size();i++){
        string myString;
        ofxXmlSettings xml = mediaPages.at(i)->getXML();
        xml.copyXmlToString(myString);
        cout << myString << endl;
    }
}
