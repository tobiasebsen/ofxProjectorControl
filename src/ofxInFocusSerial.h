//
//  ofxInFocusSerial.h
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#pragma once

#include "ofxProjectorSerial.h"
#include "ofxProjectorControl.h"

#define INFOCUS_SOURCE_VGA1     0
#define INFOCUS_SOURCE_VGA2     1
#define INFOCUS_SOURCE_HDMI     5
#define INFOCUS_SOURCE_COMP     12
#define INFOCUS_SOURCE_SVIDEO   13

#define INFOCUS_SYS_STANDBY     0
#define INFOCUS_SYS_STARTUP     2
#define INFOCUS_SYS_COOLING     12
#define INFOCUS_SYS_ERROR       18

#define INFOCUS_ERROR_NONE          0
#define INFOCUS_ERROR_LAMPNOTLIT    1
#define INFOCUS_ERROR_LAMPOUT       3
#define INFOCUS_ERROR_FAN           4
#define INFOCUS_ERROR_OVERHEAT      5
#define INFOCUS_ERROR_DMD           8
#define INFOCUS_ERROR_COLORWHEEL    9

class ofxInFocusSerial : public ofxProjectorSerial, public ofxProjectorControl {
public:

    bool setup(string portName);
    
    // 18
    int getSource();
    string getSourceDescription();
    void setSource(int source);
    
    // 27
    int getError();
    string getErrorDescription();
    
    // 62
    bool isLampEco();
    void setLampEco(bool eco);
    
    // 108
    bool isPowerOn();
    void setPowerOn(bool on);
    
    // 114
    string getFirmwareVersion();
    
    int getLampHoursNormal();   // 115
    int getLampHoursEco();      // 117
    
    // 155
    int getSystemState();
    string getSystemStateDescription();
    
protected:
    void writeCommand(string cmd);
    void writeCommand(string cmd, int value);
    string readCommand(string cmd);
};