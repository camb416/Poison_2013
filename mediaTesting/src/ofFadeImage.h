//
//  ofFadeImage.h
//  RFIDBook
//
//  Created by Cameron Browning on 5/22/13.
//
//

#ifndef __RFIDBook__ofFadeImage__
#define __RFIDBook__ofFadeImage__

#include "ofMain.h"
#include "ofxTween.h"

#include <iostream>
class ofFadeImage : public ofImage{

public:
    
    void setup(string filename_in);
    void update();
    void fadeIn();
    void fadeOut();
    void draw();
    void draw(int x_in, int y_in);
    void draw(int x_in, int y_in, int w_in, int h_in);
    
    void tweenSlide(char direction_in, float duration_in, bool visable_in);
    void tweenSlideDraw(int x_in, int y_in);
    float current_width;

//    void slide(int x_in, int y_in, bool on_in, char direction_in, float duration_in);
    
    
    
private:
    
    float alpha;
    float alphaDest;
    bool visable;

    ofxTween tweenalpha;
    ofxTween tweenslide;
    ofxEasingCubic 	easingcubic;
};
#endif /* defined(__RFIDBook__ofFadeImage__) */
