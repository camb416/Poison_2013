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
#include <iostream>
class ofFadeImage : public ofImage{

public:
    
    ofFadeImage();
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
    void setPulse(int _pulseType){
        pulseType = _pulseType;
        ofLogWarning() << "setting the pulse type to: " << pulseType;
    }
    
private:
    
    int pulseType;
    float pulseVal;
    float pulseOrigin;
    
    float alpha;
    float alphaDest;
    float tweenDivisor;
    bool showBorder;
    string path;
    
    
    
};
#endif /* defined(__RFIDBook__ofFadeImage__) */
