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
}
Media::~Media(){}

// Image only
void Media::setup(string mediaFile, float _x, float _y, string _tapId, bool _isHidden){
    
    
    showWhenDone_str = "";
    imgFileName = mediaFile;
    setPosition(_x, _y);
    
    isHidden = isHiddenByDefault = _isHidden;
    
    //hasVid = false;
    autoplay = -1;
    mClass = _tapId;
    mediaType = IMGMEDIA;
    
    img = new ofFadeImage();
    
    // check for image not found
    if (ofFile::doesFileExist(imgFileName) == true){
        img->setup(mediaFile);
    }
    else{
        img->setup(notFoundImgFile);
    }
    
    img->fadeOut();

}

// Image and video
void Media::setup(string _imgFile, string _vidFile, float _x, float _y, int _autoplay, string _tapId, int _loopback, bool _isHidden){
 
    
    showWhenDone_str = "";
    setPosition(_x, _y);
    
    mClass = _tapId;
    isHidden = isHiddenByDefault = _isHidden;
    
    
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
    
    if(mediaType==VIDMEDIA){
        
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
    
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA){
        vidFileName = _vidFile;
       // hasVid = true;
        vidState = 0;
        
        // check for video not found
        if (ofFile::doesFileExist(_vidFile) == true){
            vid->setup(_vidFile);
        }
        else{
            vid->setup(notFoundVidFile);
        }
        
        autoplay = _autoplay;
        loopback = _loopback;
           vid->fadeOut(-1);
    }
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA){
        // check for image not found
        if (ofFile::doesFileExist(imgFileName) == true){
            img->setup(_imgFile);
        }
        else{
            img->setup(notFoundImgFile);
        }
        
        img->fadeOut(-1);
    }
    
}

// Setup segmented video
void Media::setup(string _vidFile, float _x, float _y){
    segVid = new SegmentedVideo();
    vidFileName = _vidFile;
    vidState = 0;
    
    segVid->setup(_vidFile);
    setPosition(_x, _y);
    mediaType = SEGMEDIA;
    
    autoplay = 1;
    isHidden = isHiddenByDefault = false;
    //segVid->fadeOut(-1);
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
    
    if (mediaType==DUALMEDIA || mediaType == VIDMEDIA || mediaType == SEGMEDIA){
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

    if(mediaType==VIDMEDIA){
        if(vid->isPlaying()==true){
            vid->stop();
            vid->setFrame(0);
            loopCount = 0;
        }
    }
    if(mediaType==SEGMEDIA){
        if(segVid->isPlaying()==true){
            segVid->stop();
            segVid->setFrame(0);
            loopCount = 0;
        }
    }

}

void Media::update(){
    
    //TODO check mediaState to see what to do
    
    if(mediaType==IMGMEDIA){
        img->update();
        img->getAlpha()<0.01f ? isHidden = true : isHidden = false;
    }
    if (mediaType==VIDMEDIA) {
      
            int currentFrame = vid->getCurrentFrame();
            int lastFrame = vid->getTotalNumFrames();
        
            if (currentFrame == lastFrame && vid->isPlaying()){
                if(loopback>0){
                vid->setFrame(loopback);
                } else if(loopback<0){
                    hide();
                    vid->stop();
                    if(showWhenDone_str.length()>0){
                        viewRef->showCurrentMediaByClassName("rhp");
                        showWhenDone_str = "";
                    }
                    
                }
//                ofLogNotice() << "current frame: " << currentFrame;
            }
        
        vid->update();
        vid->getAlpha()<0.01f ? isHidden = true : isHidden = false;

    }
    
    if (mediaType == SEGMEDIA) {
        segVid->update();
        segVid->getAlpha()<0.01f ? isHidden = true : isHidden = false;
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
    if(mediaType==SEGMEDIA) segVid->setBorder(isDraggable);

    
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
    else if(mediaType == SEGMEDIA){
        segVid->draw(x, y, segVid->width*scale, segVid->height*scale);
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
        default:
            ofLogNotice() << "UNKNOWN MEDIA: ";
            break;
            
    }
    //cout << vidFileName << ", " << imgFileName << "." << endl;
}

void Media::setBorder(bool _showBorder){
    if(mediaType==IMGMEDIA || mediaType==DUALMEDIA) img->setBorder(_showBorder);
    if(mediaType==VIDMEDIA || mediaType==DUALMEDIA) vid->setBorder(_showBorder);
    if(mediaType==SEGMEDIA) segVid->setBorder(_showBorder);
}

int Media::hide(){
    
    if(isHidden){
        ofLogWarning() << "already hidden, can't hide it";
        return -1;
    } else {
    
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
    
int Media::show(){
    if(!isHidden){
        ofLogWarning() << "already showing, can't show it";
        return -1;
    } else {
        isHidden = false;
        if(mediaType==IMGMEDIA){
            img->fadeIn();
        } else if(mediaType==VIDMEDIA){
            vid->fadeIn();
            playVid();
        } else if(mediaType==SEGMEDIA){
            segVid->fadeIn();
            playVid();
        } else {
            ofLogWarning() << "Media::show not supported for mediaType==" << mediaType;
            return -1;
        }
        return 0;
    }
}
