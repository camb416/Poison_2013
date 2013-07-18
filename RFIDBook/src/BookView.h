//
//  BookView.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#ifndef __RFIDBook__BookView__
#define __RFIDBook__BookView__
#include "ofMain.h"
#include "ofFadeImage.h"
#include "ofxXmlSettings.h"
#include "BookLoader.h"
#include "Page.h"
#include <iostream>
class BookView{
    
public:
    BookView();
    ~BookView();
    void setup();
    void update();
    void draw();
    void draw(int x_in, int y_in, int debugState=0);
    void addPage(vector<string> mediaFiles, vector<ofVec2f> positions, vector<int> autoplay, vector<string> tapId, vector<int> loopback);
    
    void addPage(vector<MediaModel> medias);
    
    void clearPages();
    void addBackplate(string platename_in);
    void activate(int pagenum_in);
    void deactivate();
    void mousePressed();
    void mouseReleased();
    void savePageLayout();
    
    void showDragUI();
    void hideDragUI();
    
    vector<Page*> mediaPages;
    
    void printCurrentMedia(){
        ofLogNotice() << "printing current media.";
        mediaPages.at(currentPage)->printCurrentMedia();
    }
    void printCurrentMediaByClassName(string _id){
        ofLogNotice() << "printing current media with id: " <<  _id << ".";
       mediaPages.at(currentPage)->printCurrentMediaByClassName(_id);
    }
    
    void hideCurrentMediaByClassName(string _classname){
        vector<Media*> mediaToHide = mediaPages.at(currentPage)->getMediaByClassName(_classname);
        for(int i=0;i<mediaToHide.size();i++){
            mediaToHide.at(i)->hide();
        }
    }
    void showCurrentMediaByClassName(string _classname){
        vector<Media*> mediaToShow = mediaPages.at(currentPage)->getMediaByClassName(_classname);
        for(int i=0;i<mediaToShow.size();i++){
            // TODO: implement show();
            //mediaToShow.at(i)->show();
        }
    }
    

    
private:
    
    ofImage backplate;
    int currentPage;
    
    bool bShowDragUI;
    bool isSetup;
    

};
#endif /* defined(__RFIDBook__BookView__) */
