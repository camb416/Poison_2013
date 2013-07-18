//
//  Media.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/7/13.
//
//

#include "Media.h"

Media::Media(){
    isDraggable = true;
    isDragging = false;
    vidFileName = "";
    imgFileName = "";
    mediaType = -1;
}
Media::~Media(){}

// Image only
void Media::setup(string mediaFile, float _x, float _y, string _tapId, bool _isHidden){
    
    imgFileName = mediaFile;
    setPosition(_x, _y);
    
    isHidden = _isHidden;
    //hasVid = false;
    autoplay = -1;
    mClass = _tapId;
    mediaType = IMGMEDIA;
    
    img = new ofFadeImage();
    img->setup(mediaFile);

}

// Image and video
void Media::setup(string _imgFile, string _vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback, bool _isHidden){
 
    setPosition(_x, _y);
    
    mClass = _tapId;
    isHidden = _isHidden;
    
    
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
    
    if(mediaType==VIDMEDIA) vid = new ofFadeVideo();
    if(mediaType==IMGMEDIA) img = new ofFadeImage();
    if(mediaType==UNKNOWNMEDIA) ofLogWarning() << "UNKNOWN MEDIA NOT SUPPORTED";
    if(mediaType==DUALMEDIA) ofLogWarning() << "DUAL MEDIA NOT SUPPORTED";
    
    
    if (loopback == 0){
        vid->setLoopState(OF_LOOP_PALINDROME);
    } else {
        vid->setLoopState(OF_LOOP_NONE);
    }
    
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA){
        vidFileName = _vidFile;
       // hasVid = true;
        vidState = 0;
        vid->setup(_vidFile);
        autoplay = _autoplay;
        loopback = _loopback;
    }
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA){
        img->setup(_imgFile);
    }
    
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
    
    if (mediaType==DUALMEDIA || mediaType == VIDMEDIA){
        return vidFileName;
    } else {
        return imgFileName;
    }
}


void Media::playVid(){

    if(mediaType==VIDMEDIA){
        if(vid->isPlaying()==false){
            vidState = 1;
            vid->setFrame(0);
            vid->nextFrame();
            vid->play();
        }
    }

}

void Media::stopVid(){

    if(mediaType==VIDMEDIA){
        if(vid->isPlaying()==true){
            vid->stop();
            vid->setFrame(0);
            loopCount = 0;
        }
    }

}

void Media::update(){
    
    //TODO check mediaState to see what to do
    
    if(mediaType==IMGMEDIA) img->update();
    
    if (mediaType==VIDMEDIA) {
      
            int currentFrame = vid->getCurrentFrame();
            int lastFrame = vid->getTotalNumFrames();
        
            if (currentFrame == lastFrame && loopback > 0){
                vid->setFrame(loopback);
//                ofLogNotice() << "current frame: " << currentFrame;
            }
        
        vid->update();

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
   if(mediaType==VIDMEDIA) vid->setBorder(isDraggable);

    
}

void Media::draw(float scale){
    
    if (mediaType==IMGMEDIA){
        img->draw(x,y, img->width*scale, img->height*scale);
    } else if(mediaType==VIDMEDIA){
       // if (vidState == 0 && (mClass == "" || mClass == "K")){
            //img->draw(x,y, img->width*scale, img->height*scale);
       // }
       // else if (vidState == 1) {
            vid->draw(x, y, vid->width*scale, vid->height*scale);
        }

}
void Media::printInfo(){
    switch(mediaType){
        
        case 0:
            ofLogNotice() << "IMAGE MEDIA: "<< imgFileName << ".";
            break;
        case 1:
            ofLogNotice() << "VIDEO MEDIA: " << vidFileName << ".";
            break;
        case 2:
            ofLogNotice() << "DUAL MEDIA: " << imgFileName.length() << ": " << imgFileName << ", " << vidFileName << ".";
            break;
        default:
            ofLogNotice() << "UNKNOWN MEDIA: ";
            break;
            
    }
    //cout << vidFileName << ", " << imgFileName << "." << endl;
}

void Media::setBorder(bool _showBorder){
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA) img->setBorder(_showBorder);
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA) vid->setBorder(_showBorder);
}

void Media::hide(){
    if(mediaType==IMGMEDIA){
        img->fadeOut();
    } else if(mediaType==VIDMEDIA){
        vid->fadeOut();
    } else {
        ofLogWarning() << "Media::hide not supported for mediaType==" << mediaType;
    }
}
