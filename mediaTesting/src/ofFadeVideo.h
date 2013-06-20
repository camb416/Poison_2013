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
class ofFadeVid : public ofVideoPlayer{
    
public:
    
    void setup(string filename_in);
    void update();
    void fadeIn();
    void fadeOut();
    void draw();
    void draw(int x_in, int y_in);
    void draw(int x_in, int y_in, int w_in, int h_in);
    
    float current_width;


    
    
    
private:
    
    float alpha;
    float alphaDest;

    bool visable;
    
};
#endif /* defined(__RFIDBook__ofFadeImage__) */
