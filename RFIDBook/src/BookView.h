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
#include "LanguageController.h"
#include <iostream>

class Page;
class BookView{
    
public:
    BookView();
    ~BookView();
    void setup(LanguageController * _lang, string _xmlFile);
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
    
    int touch(int _whichSensor);
    int release(int _whichSensor);
    
    vector<Page*> mediaPages;
    
    void printCurrentMedia();
    void printCurrentMediaByClassName(string _id);
    int hideCurrentMediaByClassName(string _classname);
    int showCurrentMediaByClassName(string _classname);
    int showCurrentMediaByClassName(string _classname,string _showWhenDone);
    void playVideoByClassName(string _classname);
    
    void playSegmentedVideo();
    
    void loadPages();

    int getCurrentPage();
    
    LanguageController * lang;
    
private:
    
    ofImage backplate;
    int currentPage;
    
    bool bShowDragUI;
    bool isSetup;
    
    string xmlFile;
    BookLoader loader;
    
    

};
#endif /* defined(__RFIDBook__BookView__) */
