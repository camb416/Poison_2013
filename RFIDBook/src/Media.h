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
#define TOUCHVIDEO 4

class BookView;

class Media {
    
public:
    Media();
    ~Media();

    // setup methods
    void setupImage(MediaModel _mm);
    void setupVideo(MediaModel _mm);
    void setupSegVideo(MediaModel _mm);
    void setupTouchVid(MediaModel _mm);
    
    void update();
    void draw(float scale=1.0f);
    
    // video-specific
    void playVid();
    void stopVid();

    // pointers to the visual objects
    ofFadeImage * img;
    ofFadeVideo * vid;
    SegmentedVideo * segVid;
    
    
    void moveTo(int _x, int _y);
    void printInfo();
    

    /////////////////////////////////////////////////////////
    // hide and show media
    //
    // these return -1 if it's already hidden or shown,
    // or 0 if everything looks okay.
    // Keep in mind though that if you need to check multiple
    // it is better to use getHiddden() as hide() and show()
    // will hide and show half of the ones you're trying to check
    int hide();
    int show(float _fadeVal = 8.0f, bool _useOffset = false);
    /////////////////////////////////////////////////////////

    
    /////////////////////////////////////////////////////////
    // getters //////////////////////////////////////////////
    int getMediaType(){ return mediaType; }
    int getFlipMode(){ return flipMode; }
    bool getHidden(){ return isHidden; }
    int getOffset(){ return offset; }
    int getIsHiddenByDefault(){ return isHiddenByDefault; }
    string getClass(){ return mClass; }
    int getAutoPlay(){ return autoplay; }
    float getLoopBack(){ return loopback; }
    string getPath();
    string getFileName();
    float getAlpha();
    int getPulseType();
    ofPoint getPosition();
    /////////////////////////////////////////////////////////
    
    
    /////////////////////////////////////////////////////////
    // setters //////////////////////////////////////////////
    void setBlend(ofBlendMode _blendMode){ blendMode = _blendMode; }
    void setLoopCount(int _loopCount){ loopCount = _loopCount; }
    void setFlipMode(int _flipMode){ flipMode = _flipMode; }
    void setBorder(bool _showBorder);
    void setDraggable(bool _bDrag);
    void setPosition(float _x, float _y);
    
    void registerView(BookView * _viewRef){ viewRef = _viewRef; }
    int showWhenDone(string _showWhenDone){ showWhenDone_str = _showWhenDone; }
    
    /////////////////////////////////////////////////////////
    
private:
    
    int mediaType;
    
    int loopCount;
    int curLoopCount;
    ofBlendMode blendMode;
    string showWhenDone_str;
    bool isDraggable;
    bool isDragging;
    string imgFileName;
    string vidFileName;
    
    bool lastSegButtonState = false;
    
    string notFoundImgFile = "assets/notfound.png";
    string notFoundVidFile = "assets/notfound.mov";
    
    int flipMode;
    
    bool isHidden;
    bool isHiddenByDefault;
    
    int offset;
    int fadeInOffset;
    int whenToShow;
    float fadeVal;
    
    bool vidState;
    
    int autoplay;
    string mClass;
    
    float x;
    float y;
    
    BookView * viewRef;
    
    // -1 = no looping, 0 = loop from beginning, {positive number} = loop from that position
    float loopback = -1.0f;

    
    // below are the old constructors, that are used internally. Ideally this should
    // be something more generic...
    //TODO: deprecate this
    void setupSegVideo(string _vidFile, float _x, float _y);
    // TODO: the standard, though once the new jam
    // doesn't need it, we'll ditch it.
    void setup(string mediaFile, float _x, float _y, string _tapId, bool _isHidden, int _offset, int _pulseType = 0);
    
    // TODO: deprecate me...
    void setup(string _imgFile, string vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback, bool _isHidden, int _offset);

    
    
};


#endif /* defined(__RFIDBook__Media__) */
