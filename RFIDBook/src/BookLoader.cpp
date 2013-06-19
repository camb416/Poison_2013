//
//  BookLoader.cpp
//  RFIDBook
//
//  Created by Brett Peterson on 6/18/13.
//
//

#include "BookLoader.h"

BookLoader::BookLoader(){}
BookLoader::~BookLoader(){}


// Load each page from the book XML file
vector<XmlPage> BookLoader::load(string fileName){
    
    cout << " -------- LOADING BOOK XML --------" << "\n";
    
    if (bookElements.loadFile(fileName)){
        
        pages.clear();
        
        bookElements.pushTag("Book");
        
        int numPages = bookElements.getNumTags("Page");
        ofLogNotice() << "Found " << numPages << " pages";
        
        for (int i = 0; i < numPages; i++){
            
            XmlPage newPage;
            
            bookElements.pushTag("Page", i);
            
            int numMedia = bookElements.getNumTags("Media");
            ofLogNotice() << "loading " << numMedia << " media elements for page "<< i;
            
            for (int i=0; i<numMedia; i++){
                
                string mediaFileName;
                ofVec2f mediaPos;
                
                    
                mediaFileName = lang.resolvePath(bookElements.getAttribute("Media", "src", "", i));

                mediaPos.x = ofToFloat(bookElements.getAttribute("Media", "x", "0", i));
                mediaPos.y = ofToFloat(bookElements.getAttribute("Media", "y", "0", i));
                
                int autoplay = -1;
                string tapId = "";
                
                if (bookElements.attributeExists("Media", "auto", i)) {
                    // set autoplay to true
                    int autoplay = ofToInt(bookElements.getAttribute("Media", "auto", "0", i));
                }
                
                
                if (bookElements.attributeExists("Media", "tapId", i)) {
                    tapId = bookElements.getAttribute("Media", "tapId", "0", i);
                }
                else {
                    tapId = "";
                }
                
                ofLogNotice() << "Loaded " << mediaFileName << " at position " << mediaPos.x << " : " << mediaPos.y;
                
                newPage.media.push_back(mediaFileName);
                newPage.position.push_back(mediaPos);
                newPage.autoplay.push_back(autoplay);
                newPage.tapId.push_back(tapId);
                
            }
            
            bookElements.popTag();
            pages.push_back(newPage);
        }

        
    }
    else {
        ofLogNotice() << "Book XML did not load properly";
    }
    
    cout << " ------------------------" << "\n";
    
    return pages;
}