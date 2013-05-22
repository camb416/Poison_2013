//
//  BookModel.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#ifndef __RFIDBook__BookModel__
#define __RFIDBook__BookModel__
#include "ofMain.h"
#include "ofFadeImage.h"
#include <iostream>
class BookModel{
    
public:
    BookModel();
    ~BookModel();
    void setup();
    void update();
    void draw();
    void draw(int x_in, int y_in);
    void addPage(string pagename_in);
    void activate(int pagenum_in);
private:
    vector<ofFadeImage*> pages;

};
#endif /* defined(__RFIDBook__BookModel__) */
