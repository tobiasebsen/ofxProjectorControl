//
//  ofxBenQSerial.h
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#include "ofxProjectorSerial.h"
#include "ofxProjectorControl.h"

class ofxBenQSerial : public ofxProjectorSerial, public ofxProjectorControl {
public:

    bool setup(string portName);
    
    bool isPowerOn();
    void setPowerOn(bool on);
    
    int getLampHours();
    int getLampHoursEco();

    bool isLampEco();
    void setLampEco(bool eco);
    
    string getModelName();

protected:
    void writeCommand(string cmd, string value);
    string readCommand(string cmd);
};