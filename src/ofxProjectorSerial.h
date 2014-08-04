//
//  ofxProjectorSerial.h
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#pragma once

#include "ofMain.h"

class ofxProjectorSerial : public ofSerial {
public:
    
    bool setup(string portName, int baudrate, bool flowcontrol = false);
    void enableFlowcontrol(bool enable);

    static vector<string> getPortNames();
    
    void write(string str);
    string read(int timeout = 1000);

private:
};