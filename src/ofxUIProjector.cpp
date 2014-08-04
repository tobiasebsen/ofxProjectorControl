//
//  ofxUIProjector.cpp
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#include "ofxUIProjector.h"
#include "ofxProjectorSerial.h"

ofxUIProjector::ofxUIProjector() : ofxUISuperCanvas("PROJECTOR", 20, 20, 200, 200) {
    setup();
}

ofxUIProjector::ofxUIProjector(string _label, float x, float y, float w, float h, int _size) : ofxUISuperCanvas(_label, x, y, w, h, _size) {
    setup();
}

void ofxUIProjector::setup() {
    
    ofxUISuperCanvas::addSpacer();
    vector<string> ports = ofxProjectorSerial::getPortNames();
    ofxUISuperCanvas::addDropDownList("port", ports);
    ofxUISuperCanvas::addSpacer();
    
    ofxUISuperCanvas::addLabel("power", "Power: ")->setFont(this->getFontSmall());
    ofxUISuperCanvas::setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    powerLabel = ofxUISuperCanvas::addLabel("power_status", "-");
    powerLabel->setFont(this->getFontSmall());
    ofxUISuperCanvas::setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    ofxUISuperCanvas::addLabel("lampn", "Lamp hours (normal): ")->setFont(this->getFontSmall());
    ofxUISuperCanvas::setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUISuperCanvas::addLabel("lamp_norm", "-")->setFont(this->getFontSmall());
    ofxUISuperCanvas::setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    ofxUISuperCanvas::addLabel("lampe", "Lamp hours (eco): ")->setFont(this->getFontSmall());
    ofxUISuperCanvas::setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUISuperCanvas::addLabel("lamp_eco", "-")->setFont(this->getFontSmall());
    ofxUISuperCanvas::setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    ofxUISuperCanvas::addSpacer();
    ofxUISuperCanvas::addLabelButton("poweron", false)->setLabelText("Turn On");
    ofxUISuperCanvas::addLabelButton("poweroff", false)->setLabelText("Turn Off");
    ofxUISuperCanvas::autoSizeToFitWidgets();
    
    ofAddListener(this->newGUIEvent, this, &ofxUIProjector::uiEvent);
}

void ofxUIProjector::setController(ofxProjectorControl* controller) {
    this->controller = controller;
}

void ofxUIProjector::threadedFunction() {

    while (isThreadRunning()) {

        if (controller != NULL) {

            bool power = controller->isPowerOn();
            powerLabel->setLabel(power ? "ON" : "OFF");
            
            int lampn = controller->getLampHours();
            ((ofxUILabel*)getWidget("lamp_norm"))->setLabel(ofToString(lampn));

            int lampe = controller->getLampHoursEco();
            ((ofxUILabel*)getWidget("lamp_eco"))->setLabel(ofToString(lampe));
        }
        
        ofSleepMillis(500);
    }
}

void ofxUIProjector::uiEvent(ofxUIEventArgs & args) {

    if (args.getName() == "poweron" && args.getButton()->getValue() && controller != NULL) {
        controller->setPowerOn(true);
    }
    if (args.getName() == "poweroff" && args.getButton()->getValue() && controller != NULL) {
        controller->setPowerOn(false);
    }
}