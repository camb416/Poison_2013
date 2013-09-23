//
//  ofxQuadImage.h
//  quadtest
//
//  Created by Cameron Browning on 9/18/13.
//
//

#ifndef __quadtest__ofxQuadImage__
#define __quadtest__ofxQuadImage__

#include "ofxQuad.h"
#include <iostream>

class ofxQuadImage : public ofxQuad{
    
    
public:
   // void draw(int _screenW, int _screenH);
    void draw();
    void setup(int _w, int _h, string _filepath);
    
private:
    ofImage img;
    string imgPath;
    
    void load(string _filepath);
    
    
};

#endif /* defined(__quadtest__ofxQuadImage__) */
