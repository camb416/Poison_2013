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
    isBusy = true;
    touchPromptVisible = false;
    whichTouchPromptIsVisible = -1;
    bSuppressTouchPrompt = false;
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
    isBusy = false;

}
void BookView::update(){
    
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

// this is called on every update. Badly named perhaps.
    
    if(pagenum_in != currentPage){
        
        touchPrompt(-1); // resets the touchprompt

        
            ofLogNotice() << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> activating page::: " << pagenum_in;
        
        if(currentPage>-1 && currentPage<mediaPages.size())
            mediaPages.at(currentPage)->fade(-1);
        
        if(pagenum_in>-1 && pagenum_in<mediaPages.size())
            mediaPages.at(pagenum_in)->fade(1);
        
    }
    
    currentPage = pagenum_in;

}


void BookView::deactivate(){
    activate(-1);
}

void BookView::savePageLayout(){
    
    //ofLogError() << "saving XML temporarily disabled. re-enable this when the TOUCHVIDEO functionality is back.";
    
    // temporarily adding this back in...
    
    ofBuffer buff;
    string wholeXML_str = "<Book>\n\r";
    
    ofxXmlSettings wholeXML_xml;
    wholeXML_xml.addTag("Book");
    wholeXML_xml.setAttribute("Book", "promptTimeout", 30.0f,0); // touch prompt timeout (in seconds)
    wholeXML_xml.setAttribute("Book", "promptDuration", 3.0f,0); // touch prompt duration (in seconds)
    wholeXML_xml.setAttribute("Book", "numPrompts", 3.0f,0);
    
    
    ofFile outFile;
    
    for(int i=0;i<mediaPages.size();i++){
        string myString;
        ofxXmlSettings xml = mediaPages.at(i)->getXML();
        xml.copyXmlToString(myString);
        wholeXML_str += myString;
    }
    wholeXML_str += "\n\r</Book>";
    cout << wholeXML_str << endl;
    
    buff.set(wholeXML_str);
    
    bool written = ofBufferToFile("settings/book.xml", buff);
    
    if (written) {
        ofLogNotice() << "Media object positions saved to book.xml";
    }
    else {
        ofLogNotice() << "Error writing media object positions to positions.xml";
    }
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
    
    //CHECKBUSY
    
    isBusy = true;
    int returnVal = 0;
    if(currentPage>=0){
    
    vector<Media*> mediaToHide = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    
    for(int i=0;i<mediaToHide.size();i++){
        if(mediaToHide.at(i)->getHidden()==true){
            returnVal = -1;
            isBusy = false;
            return -1;
        }
    
    }
    
    if(returnVal==0){
        for(int i=0;i<mediaToHide.size();i++){
            mediaToHide.at(i)->hide();
        }
    }
    
    isBusy = false;
    } else {
        returnVal = -1;
    }
    return returnVal;
}
int BookView::showCurrentMediaByClassName(string _classname){
    int returnVal = 0;
    if(currentPage>=0){
    vector<Media*> mediaToShow = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    for(int i=0;i<mediaToShow.size();i++){
        if(mediaToShow.at(i)->show()!=0){
            returnVal = -1;
        }
    }
     
    } else {
        returnVal = -1;
    }
    return returnVal;
}

int BookView::showCurrentMediaByClassName(string _classname,string _showWhenDone){
    int returnVal = 0;
        if(currentPage>=0){
    vector<Media*> mediaToShow = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    for(int i=0;i<mediaToShow.size();i++){
        if(mediaToShow.at(i)->show()!=0){
            returnVal = -1;
        }
        mediaToShow.at(i)->showWhenDone(_showWhenDone);
    }
        } else {
            returnVal = -1;
        }
    return returnVal;
}

void BookView::playSegmentedVideo(){
    vector<Media*> segmentedVideoToActivate = mediaPages.at(currentPage)->getSegmentedMedia();
    
    for (int i=0; i<segmentedVideoToActivate.size(); i++){
        segmentedVideoToActivate.at(i)->segVid->touch();
    }
}

void BookView::playVideoByClassName(string _classname){
    vector<Media*> mediaToPlay = mediaPages.at(currentPage)->getMediaByClassName(_classname);
    for(int i=0;i<mediaToPlay.size();i++){
        mediaToPlay.at(i)->playVid();
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
                    if(hideCurrentMediaByClassName("rhp")==0){
                        ofLogNotice() << "success. showing the rhp media.";
                       showCurrentMediaByClassName("0","rhp"); 
                    } else {
                        ofLogNotice() << "failed. not showing the rhp media";
                    }
                    break;
                case 1:
                    if(hideCurrentMediaByClassName("rhp")==0) showCurrentMediaByClassName("1","rhp");
                    break;
                case 2:
                    playSegmentedVideo();
                    hideCurrentMediaByClassName("lhp");
                    break;
                case 3:
                    playVideoByClassName("3");
                    break;
                case 4:
                    if(lang->toggleLanguage()){
                     ofLogWarning() << "loading pages...";
                        loadPages();
                    } else {
                        ofLogWarning() << "toggle language unsuccessful. You might need to wait 5s for the previous language to load first.";
                    }
                    break;
                case 9:
                    playVideoByClassName("othervideo");
                    ofLogNotice() << "trying to play the video";
                    break;
                case 8:
                    playVideoByClassName("heartvid");
                    break;
            }
            break;
    }
    // should the success of showing or hiding bubble up and return?
    // doesn't now...
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

int BookView::touchPrompt(int _whichPrompt){
    
    if(!bSuppressTouchPrompt){
    
    string newPromptClass = "";
    string oldPromptClass= "";
    
    newPromptClass = "touch" + ofToString(_whichPrompt);
    if(touchPromptVisible && whichTouchPromptIsVisible>=0) oldPromptClass = "touch" + ofToString(whichTouchPromptIsVisible);

    
    if(touchPromptVisible && oldPromptClass!="") hideCurrentMediaByClassName(oldPromptClass);

    
    if(_whichPrompt>=0){
        showCurrentMediaByClassName(newPromptClass);
        touchPromptVisible = true;
        whichTouchPromptIsVisible = _whichPrompt;
    } else {
        touchPromptVisible = false;
        whichTouchPromptIsVisible = -1;
        for(int i=1;i<4;i++){
            string imgclass = "touch" + ofToString(i);
            hideCurrentMediaByClassName(imgclass);
        }
    }
    
    return 0;
    } else {
        // touchprompts are being suppressed,
        // don't do ANYTHING. It's probably because
        // the videos are playing or something.
        return -1;
    }
    
}
int BookView::suppressTouch(bool _bSuppress){
    // TODO: IMplement this functionality for the
    // videos to suppress the prompts.
    bSuppressTouchPrompt = _bSuppress;
    
    return -1;
}
