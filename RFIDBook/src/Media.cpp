//
//  Media.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/7/13.
//
//

#include "Media.h"
#include "BookView.h"

Media::Media(){
    isDraggable = true;
    isDragging = false;
    vidFileName = "";
    imgFileName = "";
    mediaType = -1;
    whenToShow = -1;
    fadeVal = 8.0f;
    blendMode = OF_BLENDMODE_DISABLED;
}
Media::~Media(){}

// Image only
void Media::setup(string mediaFile, float _x, float _y, string _tapId, bool _isHidden, int _offset, int _pulseType){
    
    offset = _offset;
    
    showWhenDone_str = "";
    imgFileName = mediaFile;
    setPosition(_x, _y);
    
    isHidden = true;
    isHiddenByDefault = _isHidden;
    
    //hasVid = false;
    autoplay = -1;
    mClass = _tapId;
    mediaType = IMGMEDIA;
    
    img = new ofFadeImage();
    img->setPulseType(_pulseType);
        
    // check for image not found
    string resolvedPath = viewRef->lang->resolvePath(imgFileName);
    if (ofFile::doesFileExist(resolvedPath) == true){
        img->setup(resolvedPath);
    } else {
        img->setup(notFoundImgFile);
    }
    
    img->fadeOut();

}

void Media::setupImage(MediaModel _mm){
    setup(_mm.src,_mm.pos.x, _mm.pos.y, _mm.mClass, _mm.isHidden, _mm.offset, _mm.pulseType);
}
void Media::setupVideo(MediaModel _mm){
       setup("",_mm.src,_mm.pos.x, _mm.pos.y, _mm.autoPlay, _mm.mClass, _mm.loopback, _mm.isHidden, _mm.offset);
        setFlipMode(_mm.flip);
}


void Media::setupTouchVid(MediaModel _mm){
    if(_mm.mediaType!=4){
        ofLogError() << "setting up touch vid with a MediaModel that's not a touchvid";
    } else {
        ofLogNotice() << "pause here for a sec.";
        mediaType = TOUCHVIDEO;
        setup("",_mm.src,_mm.pos.x,_mm.pos.y,0,_mm.mClass,-1,_mm.isHidden,0);
    }
}

// Image and video
void Media::setup(string _imgFile, string _vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback, bool _isHidden, int _offset){
 
    
    offset = _offset;
    
    showWhenDone_str = "";
    setPosition(_x, _y);
    
    mClass = _tapId;
    isHidden = isHiddenByDefault = _isHidden;
    
    if(mediaType<0){
        if(_imgFile.length()>3){
            if(_vidFile.length()>3){
                mediaType = DUALMEDIA;

                
            } else {
                mediaType = IMGMEDIA;
                
            }
            
        } else if(_vidFile.length()>3){
            mediaType = VIDMEDIA;

        } else {
            mediaType = UNKNOWNMEDIA;
        }
    }
    
    if(mediaType==VIDMEDIA || mediaType == TOUCHVIDEO){
        vid = new ofFadeVideo();
    }
    if(mediaType==IMGMEDIA){
        img = new ofFadeImage();

    }
    
    if(mediaType==UNKNOWNMEDIA) ofLogWarning() << "UNKNOWN MEDIA NOT SUPPORTED";
    if(mediaType==DUALMEDIA) ofLogWarning() << "DUAL MEDIA NOT SUPPORTED";
    
    
    if(loopback<0){
        vid->setLoopState(OF_LOOP_NONE);
    }else if (loopback == 0){
        vid->setLoopState(OF_LOOP_PALINDROME);
    } else {
        // loop to a partial point...
        //vid->setLoopState(OF_LOOP_NONE);
    }
    
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA || mediaType == TOUCHVIDEO){
        vidFileName = _vidFile;
       // hasVid = true;
        vidState = 0;
        
        // check for video not found
        string resolvedPath = viewRef->lang->resolvePath(vidFileName);
        if (ofFile::doesFileExist(resolvedPath) == true){
            vid->setup(resolvedPath);
        }
        else{
            vid->setup(notFoundVidFile);
        }
        
        autoplay = _autoplay;
        loopback = _loopback;
           vid->fadeOut(-1);
    }
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA){
        imgFileName = _imgFile;
        // check for image not found
        string resolvedPath = viewRef->lang->resolvePath(imgFileName);
        if (ofFile::doesFileExist(resolvedPath) == true){
            img->setup(resolvedPath);
        }
        else{
            img->setup(notFoundImgFile);
        }
        
        img->fadeOut(-1);
    }
    
}

void Media::setupSegVideo(MediaModel _mm){
    setupSegVideo(_mm.src, _mm.pos.x, _mm.pos.y);
    setFlipMode(_mm.flip);
}

// Setup segmented video
void Media::setupSegVideo(string _vidFile, float _x, float _y){
    segVid = new SegmentedVideo();
    vidFileName = _vidFile;
    vidState = 0;
    offset = 0;
    
    segVid->setup(viewRef->lang->resolvePath(vidFileName));
    setPosition(_x, _y);
    mediaType = SEGMEDIA;
    
    autoplay = 1;
    isHidden = isHiddenByDefault = false;
    
    //segVid->fadeOut(-1);
}

int Media::getPulseType(){
    int returnVal = 0;
    if(mediaType==IMGMEDIA){
        returnVal = img->getPulseType();
    } else {
        returnVal = 0;
    }
    return returnVal;
}


void Media::setPosition(float _x, float _y){
    x = _x;
    y = _y;
}

ofPoint Media::getPosition(){
    ofPoint returnVal = ofPoint(x,y);
    return returnVal;
}

string Media::getFileName(){
    
    if (mediaType== TOUCHVIDEO || mediaType==DUALMEDIA || mediaType == VIDMEDIA || mediaType == SEGMEDIA){
        return vidFileName;
    } else {
        return imgFileName;
    }
}


void Media::playVid(){

    if(mediaType==VIDMEDIA || mediaType == TOUCHVIDEO){
        if(vid->isPlaying()==false){
            vidState = 1;
            vid->setFrame(0);
            vid->nextFrame();
            vid->play();
            curLoopCount = 0;
        }
    }
    if(mediaType==SEGMEDIA){
        if(segVid->isPlaying()==false){
            vidState = 1;
            segVid->setFrame(0);
            segVid->nextFrame();
            segVid->play();
        }
    }

}

void Media::stopVid(){

    if(mediaType==VIDMEDIA || mediaType == TOUCHVIDEO){
        if(vid->isPlaying()==true){
            vid->stop();
            vid->setFrame(0);
            curLoopCount = 0;
        }
    }
    if(mediaType==SEGMEDIA){
        if(segVid->isPlaying()==true){
            segVid->stop();
            segVid->setFrame(0);
        }
    }

}

void Media::update(){
    
    //TODO check mediaState to see what to do
    
    if(mediaType==IMGMEDIA){
        img->update();
        img->getAlpha()<0.01f ? isHidden = true : isHidden = false;
    } else if (mediaType==VIDMEDIA || mediaType == TOUCHVIDEO) {
      
            int currentFrame = vid->getCurrentFrame();
            int lastFrame = vid->getTotalNumFrames();

            if (currentFrame == lastFrame && vid->isPlaying()){
                if(mediaType==VIDMEDIA || mediaType == TOUCHVIDEO){
                
                    bool doLoop = false;
                    if(curLoopCount<loopCount) doLoop = true;
                    if(loopCount<0) doLoop = true;
                    

                    if(doLoop){
                        // loop
                        int frameToLoopTo = 1;
                        if(loopback>=0) frameToLoopTo = loopback;
                        vid->setFrame(frameToLoopTo);
                        curLoopCount++;
                    } else {
                        if(mediaType==VIDMEDIA) hide();
                        vid->stop();
                        if(showWhenDone_str.length()>0){
                            viewRef->showCurrentMediaByClassName(showWhenDone_str);
                            showWhenDone_str = "";
                        }
  
                    }
                    /*
                    if(loopback>0 && curLoopCount>0){
                        vid->setFrame(loopback);
                        curLoopCount--;
                    } else if(loopback<0){
                        hide();
                        vid->stop();
                        if(showWhenDone_str.length()>0){
                            viewRef->showCurrentMediaByClassName(showWhenDone_str);
                            showWhenDone_str = "";
                        }
                    } else if(loopback==0 && curLoopCount<1){
                        vid->stop();
                        vid->setFrame(1);
                    } else if(curLoopCount>0){
                        vid->setFrame(1);
                        vid->play();
                    }
*/
                    
                    
                } /*else if(mediaType == TOUCHVIDEO){

                    vid->setFrame(0);
                    
                    if(curLoopCount--<1) vid->stop();
                        

                }*/
                
//                ofLogNotice() << "current frame: " << currentFrame;
            }
        
        vid->update();
        vid->getAlpha()<0.01f ? isHidden = true : isHidden = false;

    } else if (mediaType == SEGMEDIA) {
        segVid->update();
        // check whether to show the button
        bool currSegButtonState = segVid->showButton;
        if (currSegButtonState == true && lastSegButtonState == false){
            viewRef->showCurrentMediaByClassName("seg");
        }
        segVid->getAlpha()<0.01f ? isHidden = true : isHidden = false;
        lastSegButtonState = currSegButtonState;
    }
    
    if(whenToShow>0){
        if(ofGetElapsedTimeMillis()>whenToShow){
            whenToShow = -1;
            show();
        }
    }
}

void Media::moveTo(int _x, int _y){
    // eventually, this should tween.
    x = _x;
    y = _y;
}

void Media::setDraggable(bool _bDrag){
    isDraggable = _bDrag;

    if(mediaType==IMGMEDIA) img->setBorder(isDraggable);
    if(mediaType==VIDMEDIA || mediaType == TOUCHVIDEO) vid->setBorder(isDraggable);
    if(mediaType==SEGMEDIA) segVid->setBorder(isDraggable);


    
}

void Media::draw(float scale){
    
    ofEnableBlendMode(blendMode);
    
    if (mediaType==IMGMEDIA){
        img->draw(x,y, img->width*scale, img->height*scale);
    } else if(mediaType==VIDMEDIA || mediaType == TOUCHVIDEO){
        
      //  if(mediaType==TOUCHVIDEO) ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        
            vid->draw(x, y, vid->width*scale, vid->height*scale);
        
      //  if(mediaType==TOUCHVIDEO) ofDisableBlendMode();
        
        
        }
    else if(mediaType == SEGMEDIA){
        if(flipMode>0){
            segVid->draw(x, y, segVid->width*scale*-1, segVid->height*scale);
        } else {
            segVid->draw(x, y, segVid->width*scale, segVid->height*scale);
        }
    }

}
void Media::printInfo(){
    switch(mediaType){
        
        case 0:
            ofLogNotice() << "IMAGE MEDIA: "<< imgFileName <<  ", isHidden: " << isHiddenByDefault << ":" << isHidden << ".";
            break;
        case 1:
            ofLogNotice() << "VIDEO MEDIA: " << vidFileName << ", isHidden: " << isHiddenByDefault << ":" << isHidden << ".";
            break;
        case 2:
            ofLogNotice() << "DUAL MEDIA: " << imgFileName.length() << ": " << imgFileName << ", " << vidFileName << ", isHidden: " << isHiddenByDefault << ".";
            break;
        case 3:
                       ofLogNotice() << "SEG VIDEO: " << imgFileName.length() << ": " << imgFileName << ", " << vidFileName << ", isHidden: " << isHiddenByDefault << "."; 
            break;
        case 4:
                                   ofLogNotice() << "TOUCH VIDEO: " << imgFileName.length() << ": " << imgFileName << ", " << vidFileName << ", isHidden: " << isHiddenByDefault << "."; 
            break;
        default:
            ofLogNotice() << "UNKNOWN MEDIA: ";
            break;
            
    }
    //cout << vidFileName << ", " << imgFileName << "." << endl;
}

void Media::setBorder(bool _showBorder){
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA) img->setBorder(_showBorder);
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA || mediaType==TOUCHVIDEO) vid->setBorder(_showBorder);
    if(mediaType==SEGMEDIA) segVid->setBorder(_showBorder);
}

int Media::hide(){
    whenToShow = -1;
    if(isHidden){
        ofLogWarning() << imgFileName << " already hidden, can't hide it";
        return -1;
    } else {
        isHidden = true;
        if(mediaType==IMGMEDIA){
            img->fadeOut();
        } else if(mediaType==VIDMEDIA){
            vid->fadeOut();
        } else if(mediaType==SEGMEDIA){
            segVid->fadeOut();
        } else {
            ofLogWarning() << "Media::hide not supported for mediaType==" << mediaType;
            return -1;
        }
        return 0;
    }
}

int Media::show(float _fadeVal, bool _useOffset){


    fadeVal = _fadeVal;
    if(!isHidden){
        ofLogWarning() << "already showing, can't show it";
        return -1;
    } else if(offset<=0 || _useOffset == false){
        isHidden = false;
        if(mediaType==IMGMEDIA){
            img->fadeIn(fadeVal);
        } else if(mediaType==VIDMEDIA){
            vid->fadeIn(fadeVal);
            vid->setFrame(1);
            playVid();
        } else if(mediaType==SEGMEDIA){
            segVid->fadeIn(fadeVal);
                        vid->setFrame(1);
            playVid();
        } else if (mediaType==TOUCHVIDEO){
            vid->fadeIn(fadeVal);
                        vid->setFrame(1);
            playVid();
        
        } else {
            ofLogWarning() << "Media::show not supported for mediaType==" << mediaType;
            return -1;
        }
        return 0;
    } else {
        if(whenToShow<0){
            whenToShow = ofGetElapsedTimeMillis()+offset;
        }
        return 0;
    }
    
}
