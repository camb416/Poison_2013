//
//  DebugUI.cpp
//  RFIDBook
//
//  Created by Cameron Browning on 6/14/13.
//
//

#include "DebugUI.h"

DebugUI::DebugUI(){
    bDragUIcheckbox = bDragUIcheckbox_prev = false;
    saveXMLbtn = false;
    loadXMLbtn = false;
    defaultXMLbtn = false;
    isVisible = false;
    bFullScreencheckbox = bFullScreencheckbox_prev = false;
    bQuadCropperEdit = bQuadCropperEdit_prev = false;
    loadCropBtn = saveCropBtn = false;
    
    bShowCursor = false;
}
DebugUI::~DebugUI(){
    
}

bool DebugUI::getIsVisible(){
    return isVisible;
}

void DebugUI::setup(DeviceController * _devices, BookController * _book, LanguageController * _lang, BookView * _bookView, BookLoader * _loader, ofxQuadCrop * _cropper, ofxQuadImage * _quadImage){
    
    quadImage = _quadImage;
    cropper = _cropper;
    devices = _devices;
    book = _book;
    lang = _lang;
    bookView = _bookView;
    loader = _loader;
    
    tfield.setup();
    tfield.update("Magic Book", 16,760);
    
    gui.hide();

    gui.addTitle("Image Crop").setNewColumn(true);
    gui.addToggle("EDIT IMAGE",bQuadImageEdit);
    gui.addToggle("Loose Dragging",bLooseDrag);
    gui.addButton("LOAD IMAGE",loadQuadImageBtn);
    gui.addButton("SAVE IMAGE",saveQuadImageBtn);
    
    gui.addTitle("Quad Crop").setNewColumn(true);
    gui.addToggle("EDIT CROP",bQuadCropperEdit);
    gui.addButton("LOAD CROP",loadCropBtn);
    gui.addButton("SAVE CROP",saveCropBtn);
    
    gui.addTitle("Magic Book");
    gui.addToggle("EDIT BOOK",bDragUIcheckbox);
    gui.addButton("DEFAULT BOOK", defaultXMLbtn);
    gui.addButton("LOAD BOOK", loadXMLbtn);
    gui.addButton("SAVE BOOK", saveXMLbtn);
    
    gui.addTitle("View").setNewColumn(true);
    gui.addToggle("FULLSCREEN", bFullScreencheckbox);
    gui.addToggle("SHOW CURSOR", bShowCursor);
    
    gui.setAlignRight(true);
    
    gui.loadFromXML();
    
    if(!bShowCursor) hideCursor();
    
    if(bFullScreencheckbox) ofSetFullscreen(true);
    
}
void DebugUI::update(){
    
    tfield.update("Magic Book \n" + book->getReport() + "\n" + book->whatSituation());
    
    
    if(loadCropBtn){
       cropper->loadFromFile();
        loadCropBtn = false;
    }
    if(saveCropBtn){
        cropper->saveToFile();
        saveCropBtn = false;
    }
    if(bQuadCropperEdit!=bQuadCropperEdit_prev){
        bQuadCropperEdit ? cropper->showDragUI() : cropper->hideDragUI();
        bQuadCropperEdit_prev = bQuadCropperEdit;
    }
    
    if(loadQuadImageBtn){
        quadImage->loadFromFile("settings/pages_mask.xml");
        loadQuadImageBtn = false;
    }
    if(saveQuadImageBtn){
        quadImage->saveToFile("settings/pages_mask.xml");
        saveQuadImageBtn = false;
    }
    if(bQuadImageEdit!=bQuadImageEdit_prev){
        bQuadImageEdit ? quadImage->showDragUI() : quadImage->hideDragUI();
        bQuadImageEdit_prev = bQuadImageEdit;
    }
    if(bLooseDrag != bLooseDrag_prev){
        quadImage->setLooseDrag(bLooseDrag);
        bLooseDrag_prev = bLooseDrag;
    }
    
    
    if(ofGetMousePressed()) pos_ui.update();
    
    if(bDragUIcheckbox!=bDragUIcheckbox_prev){
        bDragUIcheckbox ? bookView->showDragUI() : bookView->hideDragUI();
        bDragUIcheckbox_prev = bDragUIcheckbox;
    }
    
    if(bFullScreencheckbox!=bFullScreencheckbox_prev){
        ofSetFullscreen(bFullScreencheckbox);
        bFullScreencheckbox_prev = bFullScreencheckbox;
    }

    // Load in default XML file
    if(defaultXMLbtn){
        bookView->clearPages();
        vector< vector<MediaModel> > pages = loader->load("settings/book.default", *lang);
        for (int i = 0; i < pages.size(); i++) bookView->addPage(pages.at(i));
    }
    
    if(saveXMLbtn) bookView->savePageLayout();
    
    // Load in custom XML file
    if(loadXMLbtn){
        bookView->clearPages();
        vector< vector<MediaModel> > pages = loader->load("settings/book.xml", *lang);
        for (int i = 0; i < pages.size(); i++) bookView->addPage(pages.at(i));
    }
}

bool DebugUI::getDragSetting(){
    return bDragUIcheckbox;
}

void DebugUI::draw(){
    
    if(isVisible){

        ofEnableAlphaBlending();
        ofSetColor(255,255,255,128);
        ofFill();
        ofRect(0,0,ofGetWidth(),ofGetHeight());
        ofPushMatrix();
        ofTranslate(150,0);
        ofSetColor(255,255,255,255);
        devices->draw(10,300);
        tfield.draw();
        
         ofPopMatrix();
        if(ofGetMousePressed()) pos_ui.draw();
        gui.draw();
       
    }
}

void DebugUI::toggleFullScreen(){
    bFullScreencheckbox = !bFullScreencheckbox;
}

void DebugUI::show(){
    gui.show();
    showCursor();
}
void DebugUI::hide(){
    gui.hide();
    if(!bShowCursor) hideCursor();
}
void DebugUI::toggle(){
    
    isVisible = !isVisible;
    
    if(isVisible){
        show();
        showCursor();
    } else{
        hide();
        if(!bShowCursor) hideCursor();
    }
    
}

bool DebugUI::toggleCursor(){
    bShowCursor = !bShowCursor;
    if(bShowCursor){
        ofShowCursor();
    } else {
        ofHideCursor();
    }
    return bShowCursor;
}

bool DebugUI::showCursor(){
    ofShowCursor();
}

bool DebugUI::hideCursor(){
    ofHideCursor();
}
