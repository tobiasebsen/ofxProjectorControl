//
//  ofxProjectorControl.h
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#pragma once

#include "ofMain.h"

class ofxProjectorControl {
public:

    virtual bool setup(string portName) = 0;
    
    virtual bool isPowerOn() = 0;
    virtual void setPowerOn(bool on) = 0;
    
    virtual int getLampHours() = 0;
    virtual int getLampHoursEco() = 0;
    
    virtual bool isLampEco() = 0;
    virtual void setLampEco(bool eco) = 0;
};
