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


#define UNKNOWNMEDIA -1
#define IMGMEDIA 0
#define VIDMEDIA 1
#define DUALMEDIA 2

class BookView;

class Media {
    
public:
    Media();
    ~Media();
    
    BookView * viewRef;
    
    int mediaType;
    
    void setup(string mediaFile, float _x, float _y, string _tapId, bool _isHidden);
    void setup(string _imgFile, string vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback, bool _isHidden);
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
    
    //float vidX;
    //float vidY;
    
    //bool hasVid;
    bool vidState;
    
    int autoplay;
    string mClass;
    
    //TODO
    int mediaState;
    int loopCount = 0;
    
    // -1 = no looping, 0 = loop from beginning, {positive number} = loop from that position
    float loopback = -1.0f;
    
    ofFadeImage * img;
    ofFadeVideo * vid;
    
    void printInfo();
    
    void setBorder(bool _showBorder);
    
    // these return -1 if it's already hidden or shown,
    // or 0 if everything looks okay
    int hide();
    int show();
    
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
    
    
};


#endif /* defined(__RFIDBook__Media__) */
