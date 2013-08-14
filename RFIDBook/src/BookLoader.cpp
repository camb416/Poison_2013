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
vector< vector<MediaModel> > BookLoader::load(string fileName, LanguageController lang){
    
    cout << " -------- LOADING BOOK XML --------" << "\n";
    
    vector< vector<MediaModel> > allMedia;
    
    if (bookElements.loadFile(fileName)){
        
        pages.clear();
        
        bookElements.pushTag("Book");
        
        int numPages = bookElements.getNumTags("Page");
        ofLogNotice() << "Found " << numPages << " pages";
        
        for (int i = 0; i < numPages; i++){
            
            //XmlPage newPage;
            vector<MediaModel> thisPage;
            
            
            bookElements.pushTag("Page", i);
            
            int numMedia = bookElements.getNumTags("Media");
            ofLogNotice() << "loading " << numMedia << " media elements for page "<< i;
            
            for (int i=0; i<numMedia; i++){
                
                string mediaFileName;
                ofVec2f mediaPos;
                int autoplay = 0;
                string tapId;
                int loopback = 0;
                int pulse_int = 0;
                bool isHidden;
                
                MediaModel thisMedia;
                
                int offset;
                
                mediaFileName = bookElements.getAttribute("Media", "src", "", i);
                offset = bookElements.getAttribute("Media", "offset", 0, i);
                
                // If file isn't found, preserve the file path to save back to the XML
                if (mediaFileName == "FILE NOT FOUND"){
                    mediaFileName = bookElements.getAttribute("Media", "src", "", i);
                }

                mediaPos.x = ofToFloat(bookElements.getAttribute("Media", "x", "0", i));
                mediaPos.y = ofToFloat(bookElements.getAttribute("Media", "y", "0", i));
                

                if (bookElements.attributeExists("Media", "auto", i)) {
                    // set autoplay to true
                    autoplay = ofToInt(bookElements.getAttribute("Media", "auto", "0", i));
                }
                
                
                if (bookElements.attributeExists("Media", "class", i)) {
                    tapId = bookElements.getAttribute("Media", "class", "0", i);
                }
                else {
                    tapId = "";
                }
                
                if (bookElements.attributeExists("Media", "loopback", i)) {
                    loopback = bookElements.getAttribute("Media", "loopback", 0, i);
                }
                else {
                    loopback = -1;
                }
                if (bookElements.attributeExists("Media", "pulse", i)) {
                    pulse_int = bookElements.getAttribute("Media", "pulse", 0, i);
                }
                else {
                    pulse_int = -1;
                }
                if (bookElements.attributeExists("Media", "hidden", i)) {
                    string hiddenString = bookElements.getAttribute("Media", "hidden", "0", i);
                    if(hiddenString.compare("1")==0 || hiddenString.compare("true")==0 || hiddenString.compare("yes")==0){
                        isHidden = true;
                    } else {
                        isHidden = false;
                    }
                    
                }
                else {
                    isHidden = false;
                }
                
                
                
                ofLogNotice() << "Loaded " << mediaFileName << " at position " << mediaPos.x << " : " << mediaPos.y;
                
                thisMedia.src = mediaFileName;
                thisMedia.pos = mediaPos;
                thisMedia.autoPlay = autoplay;
                thisMedia.mClass = tapId;
                thisMedia.loopback = loopback;
                thisMedia.isHidden = isHidden;
                thisMedia.offset = offset;
                thisMedia.pulse = (pulse_int>0) ? true : false;
                /*
                if(thisMedia.pulse){
                    ofLogWarning() << "PULSE IS TRUE";
                } else {
                    ofLogWarning() << "PULSE IS FALSE";
                }
                 */
                /*
                newPage.media.push_back(mediaFileName);
                newPage.position.push_back(mediaPos);
                newPage.autoplay.push_back(autoplay);
                //newPage.tapId.push_back(tapId);
                newPage.loopback.push_back(loopback);
                */
                thisPage.push_back(thisMedia);
            }
            
            bookElements.popTag();
            //pages.push_back(newPage);
            allMedia.push_back(thisPage);
        }

        
    }
    else {
        ofLogError() << "Book XML did not load properly";
    }
    
    cout << " ------------------------" << "\n";
    
    return allMedia;
}