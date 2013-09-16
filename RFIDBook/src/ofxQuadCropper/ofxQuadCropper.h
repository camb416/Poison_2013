//
//  ofxQuadCropper.h
//  QuadCropperApp
//
//  Created by Cameron Browning on 9/16/13.
//
//

#ifndef __QuadCropperApp__ofxQuadCropper__
#define __QuadCropperApp__ofxQuadCropper__

#include <iostream>
#include "ofMain.h"
#include "ofxXmlSettings.h"

#define NUM_POINTS 4
#define DEFAULT_FILENAME "settings/quad.xml"

class ofxQuadCropper{
  
public:
    
    ofxQuadCropper();
    ~ofxQuadCropper();
    
    void setup(int _screenW, int _screenH);
    void update();
    void draw();

    int loadFromFile(string _file = DEFAULT_FILENAME);
    int saveToFile(string _file = DEFAULT_FILENAME);
    
    void reset();
    
    void mouseMoved(int _x, int _y);
    void mousePressed(int _x, int _y);
    void mouseDragged(int _x, int _y);
    void mouseReleased(int _x, int _y);
    
    int activate();
    int deactivate();
    bool getActive();
    
private:
    
    bool isActive;
    
    void draw(int _screenW, int _screenH);
    
    ofPoint points[4];
    ofxXmlSettings xml;
    
    void updateXmlObject();
    void randomize();
    void report();
    
    int screenW;
    int screenH;
    
    int nearestPoint;
    int getNearest(ofPoint _mousePos);
    int selectedPoint;
    
    bool isDragging;
    
    
    
};


#endif /* defined(__QuadCropperApp__ofxQuadCropper__) */
