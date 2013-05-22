#pragma once

#include "ofMain.h"
#include "DeviceController.h"
#include "BookController.h"
#include "TextField.h"
#include "PositionUI.h"
#include "BarGraph.h"
#include "BookModel.h"

class testApp : public ofBaseApp{

	public:
    testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    DeviceController devices;
    BookController book;
    TextField tfield;
    PositionUI pos_ui;
    BarGraph bar;
    float aValue;
    
    BookModel bookModel;
    
    int debugState;
    
    bool isSetup;
    

		
};
