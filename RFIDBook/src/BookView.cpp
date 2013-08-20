//
//  BookView.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#include "BookView.h"
#include "Page.h"

BookView::BookView(){
    currentPage = -1;
    bShowDragUI = false;
    isSetup = false;
    cout << "OKAY, THE BOOKVIEW EXISTS... HERE'S THE CONSTRUCTOR TO PROVE IT" << endl;
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
        for(int i=0; i < mediaPages.size(); i++){
            mediaPages.at(i)->hideAllBorders();
        }
        
    }

}

void BookView::setup(LanguageController * _lang, string _xmlFile){
    lang = _lang;
    xmlFile = _xmlFile;

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
// TODO: DEPRECATE ME
void BookView::addPage(vector<string> mediaFiles, vector<ofVec2f> positions, vector<int> autoplay, vector<string> tapId, vector<int> loopback){
    
    ofLogWarning() << "ADDING page with legacy method. Don't do it.";
    /*
    Page * newPage = new Page();
    newPage->setup();
    
    // Add the media objects using the filename and positions from xml
    for (int i = 0; i < mediaFiles.size(); i++) {

        newPage->addMedia(mediaFiles.at(i), positions.at(i), autoplay.at(i), tapId.at(i), loopback.at(i));
        
        // Add touch media for left and right & media to be faded out when touch is active
        if (ofIsStringInString(tapId.at(i), "H")) {
            newPage->touchMediaMatrix[0].push_back(i);
        } else if (ofIsStringInString(tapId.at(i), "J")) {
            newPage->touchMediaMatrix[1].push_back(i);
        } else if (ofIsStringInString(tapId.at(i), "K")) { // media to be faded out
            newPage->touchMediaMatrix[2].push_back(i);
        }
        else{
        }
    }
    
    mediaPages.push_back(newPage);
    ofLogNotice() << "added new page. total pages: " << mediaPages.size();
     */
    
}

void BookView::addPage(vector < MediaModel> medias){

    Page * newPage = new Page();
    newPage->registerView(this);
    newPage->setup();
    
    
    for (int i = 0; i < medias.size(); i++) {
        MediaModel thisMedia = medias.at(i);
        //newPage->addMedia(thisMedia.src,thisMedia.pos,thisMedia.autoPlay,thisMedia.mClass,thisMedia.loopback, thisMedia.isHidden,thisMedia.offset);
        newPage->addMedia(thisMedia);
    }
    
    mediaPages.push_back(newPage);
    //ofLogNotice() << "added new page. total pages: " << mediaPages.size();
    
}

// Remove all pages to load new ones.
void BookView::clearPages(){
    
    mediaPages.clear();
    
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


    if(pagenum_in != currentPage){
        for(int i=0;i<mediaPages.size();i++){
           
            if(i==pagenum_in){
                mediaPages.at(i)->fade(1);
            } else {
                mediaPages.at(i)->fade(-1);
                try {
                    if (mediaPages.at(currentPage)->touchActive == true){
                        mediaPages.at(currentPage)->pageReset = true;
                    }
                } catch (...) {
                    
                }
                
            }
        }
    }
    
    currentPage = pagenum_in;
}


void BookView::deactivate(){
    activate(-1);
}

void BookView::savePageLayout(){
    
    ofLogError() << "saving XML temporarily disabled. re-enable this when the TOUCHVIDEO functionality is back.";
    /*
    ofBuffer buff;
    string wholeXML;
    ofFile outFile;
    
    for(int i=0;i<mediaPages.size();i++){
        string myString;
        ofxXmlSettings xml = mediaPages.at(i)->getXML();
        xml.copyXmlToString(myString);
        wholeXML += myString;
    }
    cout << wholeXML << endl;
    
    buff.set(wholeXML);
    
    bool written = ofBufferToFile("settings/book.xml", buff);
    
    if (written) {
        ofLogNotice() << "Media object positions saved to book.xml";
    }
    else {
        ofLogNotice() << "Error writing media object positions to positions.xml";
    }
     */
}

void BookView::printCurrentMedia(){
    ofLogNotice() << "printing current media.";
    mediaPages.at(currentPage)->printCurrentMedia();
}
void BookView::printCurrentMediaByClassName(string _id){
    ofLogNotice() << "printing current media with id: " <<  _id << ".";
    mediaPages.at(currentPage)->printCurrentMediaByClassName(_id);
}

int BookView::hideCurrentMediaByClassName(string _classname){
    int returnVal = 0;
    // TODO: there's a bug here.... mediaToHide == 0 when you are on an interstitial!!!!....
    vector<Media*> mediaToHide = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    for(int i=0;i<mediaToHide.size();i++){
        if(mediaToHide.at(i)->hide()!=0){
            returnVal = -1;
        }
    }
    return returnVal;
}
int BookView::showCurrentMediaByClassName(string _classname){
    int returnVal = 0;
    vector<Media*> mediaToShow = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    for(int i=0;i<mediaToShow.size();i++){
        if(mediaToShow.at(i)->show()!=0){
            returnVal = -1;
        }
    }
    return returnVal;
}

int BookView::showCurrentMediaByClassName(string _classname,string _showWhenDone){
    int returnVal = 0;
    vector<Media*> mediaToShow = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    for(int i=0;i<mediaToShow.size();i++){
        if(mediaToShow.at(i)->show()!=0){
            returnVal = -1;
        }
        mediaToShow.at(i)->showWhenDone(_showWhenDone);
    }
    return returnVal;
}

void BookView::playSegmentedVideo(){
//    int returnVal = 0;
    vector<Media*> segmentedVideoToActivate = mediaPages.at(currentPage)->getSegmentedMedia();
    
    for (int i=0; i<segmentedVideoToActivate.size(); i++){
        segmentedVideoToActivate.at(i)->segVid->touch();
    }
}

int BookView::touch(int _whichSensor){
    ofLogNotice() << "BookView received a touch on sensor: " << _whichSensor;
    switch(currentPage){
        case 0:
        case 1:
        case 2:
        case 3:
            switch(_whichSensor){
                case 0:
                    if(hideCurrentMediaByClassName("rhp")==0) showCurrentMediaByClassName("0","rhp");
                    break;
                case 1:
                    if(hideCurrentMediaByClassName("rhp")==0) showCurrentMediaByClassName("1","rhp");
                    break;
                case 2:
                    playSegmentedVideo();
                    hideCurrentMediaByClassName("seg");
                    break;
                case 3:
                    // TODO: add conditional
                    if(lang->toggleLanguage()){
                     ofLogWarning() << "loading pages...";
                        loadPages();
                    } else {
                        ofLogWarning() << "toggle language unsuccessful. You might need to wait 5s for the previous language to load first.";
                    }
                    break;
            }
            
            break;
    }
    
    
    
    return -1;
}

int BookView::getCurrentPage(){
    return currentPage;
    
}
int BookView::release(int _whichSensor){
    ofLogNotice() << "BookView received a release on sensor: " << _whichSensor;
    return -1;
}

void BookView::loadPages(){
    
    // this implementation is garbage. Why not create the Media Objects right away, and pass pointers to them
    // to real Pages, and skip the vector to a vector to a vector to a vector (turtles all the way down) method.
    // ultimately, we seriously need to ditch the really stupid and unreadable overloaded setup methods on media and
    // just give up and call them something else in the XML!
    
    deactivate();
    clearPages();
    
    vector< vector<MediaModel> > pages = loader.load(xmlFile, * lang);
    
    for (int i = 0; i < pages.size(); i++) {
        addPage(pages.at(i));
    }

    activate(currentPage);

}