//
//  ofxQuadCrop.cpp
//  quadtest
//
//  Created by Cameron Browning on 9/18/13.
//
//

#include "ofxQuadCrop.h"

void ofxQuadCrop::draw(){
   

    
     ofSetColor(0,0,0);
     ofFill();
     ofBeginShape();
     ofVertex(0,0);
     ofVertex(points[0].x*contextDimensions.x,points[0].y*contextDimensions.y);
     ofVertex(points[1].x*contextDimensions.x,points[1].y*contextDimensions.y);
     ofVertex(contextDimensions.x,0);
     ofEndShape();
     ofBeginShape();
     ofVertex(contextDimensions.x,0);
     ofVertex(points[1].x*contextDimensions.x,points[1].y*contextDimensions.y);
     ofVertex(points[2].x*contextDimensions.x,points[2].y*contextDimensions.y);
     ofVertex(contextDimensions.x,contextDimensions.y);
     ofEndShape();
     ofBeginShape();
     ofVertex(contextDimensions.x,contextDimensions.y);
     ofVertex(points[2].x*contextDimensions.x,points[2].y*contextDimensions.y);
     ofVertex(points[3].x*contextDimensions.x,points[3].y*contextDimensions.y);
     ofVertex(0,contextDimensions.y);
     ofEndShape();
     ofBeginShape();
     ofVertex(0,contextDimensions.y);
     ofVertex(points[3].x*contextDimensions.x,points[3].y*contextDimensions.y);
     ofVertex(points[0].x*contextDimensions.x,points[0].y*contextDimensions.y);
     ofVertex(0,0);
     ofEndShape();
    
    ofxQuad::draw();
    
}