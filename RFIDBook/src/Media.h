//
//  Media.h
//  RFIDBook
//
//  Created by Brett Peterson on 6/7/13.
//
//

#ifndef __RFIDBook__Media__
#define __RFIDBook__Media__

#include <iostream>
#include "ofMain.h"
#include "ofFadeImage.h"
#include "OfFadeVideo.h"
#include "SegmentedVideo.h"
#include "LanguageController.h"
#include "BookLoader.h"


#define UNKNOWNMEDIA -1
#define IMGMEDIA 0
#define VIDMEDIA 1
#define DUALMEDIA 2
#define SEGMEDIA 3
#define TOUCHMEDIA 4

class BookView;

class Media {
    
public:
    Media();
    ~Media();
    
    BookView * viewRef;
    
    int mediaType;
    
    // TODO: the standard, though once the new jam
    // doesn't need it, we'll ditch it.
    void setup(string mediaFile, float _x, float _y, string _tapId, bool _isHidden, int _offset, int _pulseType = 0);
    
    // TODO: deprecate me...
    void setup(string _imgFile, string vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback, bool _isHidden, int _offset);
    
    // The new jam
    void setup(MediaModel _mm);
    
    // only for seg video
    void setup(string _vidFile, float _x, float _y);
    void update();
    void draw(float scale=1.0f);
    void setPosition(float _x, float _y);
    ofPoint getPosition();
    string getFileName();
    
    void playVid();
    void stopVid();
    
    void moveTo(int _x, int _y);
    
    void setDraggable(bool _bDrag);
    
    float x;
    float y;
    
    bool isHidden;
    bool isHiddenByDefault;

    int offset;
    int fadeInOffset;
    int whenToShow;
    float fadeVal;
    
    bool vidState;
    
    int autoplay;
    string mClass;
    
    int mediaState;
    int loopCount = 0;
    
    // -1 = no looping, 0 = loop from beginning, {positive number} = loop from that position
    float loopback = -1.0f;
    
    ofFadeImage * img;
    ofFadeVideo * vid;
    SegmentedVideo * segVid;
    
    void printInfo();
    
    void setBorder(bool _showBorder);
    
    // these return -1 if it's already hidden or shown,
    // or 0 if everything looks okay
    int hide();
    int show(float _fadeVal = 8.0f, bool _useOffset = false);
    
    int getPulseType();

    
    void registerView(BookView * _viewRef){
        viewRef = _viewRef;
    }
    
    int showWhenDone(string _showWhenDone){
        showWhenDone_str = _showWhenDone;
    }
    
private:
    
    string showWhenDone_str;
    bool isDraggable;
    bool isDragging;
    string imgFileName;
    string vidFileName;
    
    bool lastSegButtonState = false;
    
    string notFoundImgFile = "assets/notfound.png";
    string notFoundVidFile = "assets/notfound.mov";
    
    
};


#endif /* defined(__RFIDBook__Media__) */
