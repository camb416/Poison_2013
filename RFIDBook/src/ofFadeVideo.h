//
//  ofFadeVideo.h
//  RFIDBook
//
//  Created by Tom Arthur on 6/20/13.
//
//

#ifndef __RFIDBook__ofFadeVideo__
#define __RFIDBook__ofFadeVideo__
#include "ofMain.h"
#include <iostream>
class ofFadeVideo : public ofVideoPlayer{
    
public:
    
    ofFadeVideo();
    void setup(string filename_in);
    void update();
    void fadeIn(float _tweenD = 8.0f);
    void fadeOut(float _tweenD = 8.0f);
    void draw();
    void setBorder(bool _showBorder);
    void draw(int x_in, int y_in);
    void draw(int x_in, int y_in, int w_in, int h_in);
    float getAlpha(){
        return alpha;
    }
    
private:
    
    float alpha;
    float alphaDest;

    bool visable;
    
    float tweenDivisor;
    bool showBorder;
    
};
#endif /* defined(__RFIDBook__ofFadeImage__) */
