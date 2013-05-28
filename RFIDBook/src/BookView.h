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
#include <iostream>
class BookView{
    
public:
    BookView();
    ~BookView();
    void setup();
    void update();
    void draw();
    void draw(int x_in, int y_in);
    void addPage(string pagename_in);
    void activate(int pagenum_in);
    void deactivate();
private:
    vector<ofFadeImage*> pages;

};
#endif /* defined(__RFIDBook__BookView__) */
