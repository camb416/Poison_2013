//
//  ofxQuad.h
//  quadtest
//
//  Created by Cameron Browning on 9/18/13.
//
//

#ifndef __quadtest__Quad__
#define __quadtest__Quad__

#include <iostream>

#include "ofMain.h"
#include "ofxXmlSettings.h"

#define NUM_POINTS 5
#define DEFAULT_FILENAME "quad.xml"

class ofxQuad{
    
public:
    
    ofxQuad();
    ~ofxQuad();
    
    void setup();
    void setup(int _contextW, int _contextH);
   // void setup(int _x, int _y, int _width, int _height);
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
    
    int showDragUI();
    int hideDragUI();
    
    void setAlign(bool _align);
    bool getAlign();
    
    ofPoint getTopLeft();
    float getWidth();
    float getHeight();
    ofPoint getSize();
    ofPoint getCenter();
    float getPctWidth();
    float getPctHeight();
    
protected:
    
    bool isActive;
    
    bool bAlign;
    
    
    //void draw(int _screenW, int _screenH);
    //void draw(ofPoint _pos, ofPoint _size);
    
    ofPoint points[NUM_POINTS];
    ofxXmlSettings xml;
    
    void updateXmlObject();
    void randomize();
    void report();
    
    ofPoint size;
    ofPoint contextDimensions;
    ofPoint pos;
    
    int nearestPoint;
    int getNearest(ofPoint _mousePos);
    int selectedPoint;
    
    bool isDragging;
    
    
    
};



#endif /* defined(__quadtest__Quad__) */
