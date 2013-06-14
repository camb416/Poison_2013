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
    void addPage(string pagename_in);
    void addMediaPage(vector<string> mediaFiles, vector<ofVec2f> positions);
    void addBackplate(string platename_in);
    void activate(int pagenum_in);
    void deactivate();
    void mousePressed();
    void mouseReleased();
    
private:
    vector<ofFadeImage*> pages;
    
    // TODO - Change mediaPages to pages
    vector<Page*> mediaPages;
    ofImage backplate;
    int currentPage;
    

};
#endif /* defined(__RFIDBook__BookView__) */
