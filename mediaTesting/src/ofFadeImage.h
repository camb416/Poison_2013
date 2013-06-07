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
    
    void setup(string filename_in);
    void update();
    void fadeIn();
    void fadeOut();
    void draw();
    void draw(int x_in, int y_in);
    void draw(int x_in, int y_in, int w_in, int h_in);
    
private:
    
    float alpha;
    float alphaDest;
    
    
};
#endif /* defined(__RFIDBook__ofFadeImage__) */
