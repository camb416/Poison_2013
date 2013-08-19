#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "DeviceController.h"
#include "BookController.h"
#include "TextField.h"
#include "PositionUI.h"
#include "BarGraph.h"
#include "BookView.h"
#include "LanguageController.h"
#include "DebugUI.h"
#include "BookLoader.h"

class BookApp : public ofBaseApp{

	public:
    BookApp();
    ~BookApp();
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
    
        void toggleDebug();
        void updateDebug();
    
        void sendInput(char touchId);

        LanguageController lang;
    
        DeviceController devices;
        BookController book;
        float aValue;
    
        BookView bookView;
    
        int debugState;
    
        bool isSetup;
    
        DebugUI dui;
    
        BookLoader loader;
    
        bool useRFID;
        bool useTouch;
		
};
