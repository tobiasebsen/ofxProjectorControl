//
//  ofxUIProjector.h
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#pragma once

#include "ofxUI.h"
#include "ofxProjectorControl.h"

class ofxUIProjector : public ofxUISuperCanvas, public ofThread {
public:
    ofxUIProjector();
    ofxUIProjector(string _label, float x, float y, float w, float h, int _size = OFX_UI_FONT_MEDIUM);
    
    void setup();
    
    void setController(ofxProjectorControl* controller);
    
    void threadedFunction();
    
    void uiEvent(ofxUIEventArgs & args);
    
private:
    ofxUILabel *powerLabel;
    ofxProjectorControl* controller;
};