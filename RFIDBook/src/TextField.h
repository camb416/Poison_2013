//
//  TextField.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/17/13.
//
//

#ifndef __RFIDBook__TextField__
#define __RFIDBook__TextField__
#include "ofMain.h"
#include <iostream>
class TextField{

public:
    TextField();
    ~TextField();
    void setup(int fontsize = 32);
    void update(string text_in);
    void update(string text_in, int x_in, int y_in);
    void setPosition(ofPoint pos_in);
    void setPosition(int x_in, int y_in);
    float getWidth();
    float getHeight();
    void draw(int x_in,int y_in);
    void draw();
    
private:
    ofTrueTypeFont font;
    string text;
    ofPoint pos;

};
#endif /* defined(__RFIDBook__TextField__) */
