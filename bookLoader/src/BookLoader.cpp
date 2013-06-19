//
//  BookLoader.cpp
//  bookLoader
//
//  Created by Brett Peterson on 6/12/13.
//
//

#include "BookLoader.h"

BookLoader::BookLoader(){}
BookLoader::~BookLoader(){}


void BookLoader::load(){
    
    if (bookElements.loadFile(fileName)){
        
        bookElements.pushTag("book");
        
        int numPages = bookElements.getNumTags("page");
        ofLogNotice() << "Found " << numPages << " pages";
        
        for (int i = 0; i < numPages; i++){
            
            Page newPage;
            
            bookElements.pushTag("page", i);
            
            int numMedia = bookElements.getNumTags("media");
            ofLogNotice() << "loading " << numMedia << " media elements for page "<< i;
            
            for (int i=0; i<numMedia; i++){
                bookElements.pushTag("media", i);
                
                string mediaFileName;
                ofVec2f mediaPos;
                
                int hasVideo = bookElements.getNumTags("video");
                
                // Current media element only has an image
                if (hasVideo == 0) {
                    
                    mediaFileName = bookElements.getAttribute("img", "src", "");
                }
                else {
                    mediaFileName = bookElements.getAttribute("video", "src", "");
                }
                
                mediaPos.x = bookElements.getAttribute(<#const string &tag#>, <#const string &attribute#>, <#int defaultValue#>)
                
                newPage.media.push_back(mediaFileName);
                
                bookElements.popTag();
                
            }
            
            bookElements.popTag();
        }
        
    }
    else {
        ofLogNotice() << "Book XML did not load properly";
    }
    
    
}