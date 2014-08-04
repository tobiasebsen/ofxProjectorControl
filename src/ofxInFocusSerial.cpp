//
//  ofxInFocusSerial.cpp
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#include "ofxInFocusSerial.h"

bool ofxInFocusSerial::setup(string portName) {
    return ofxProjectorSerial::setup(portName, 19200, false);
}

bool ofxInFocusSerial::isPowerOn() {
    string pwr = readCommand("PWR");
    cout << pwr << endl;
    return pwr == "1";
}

void ofxInFocusSerial::setPowerOn(bool on) {
    writeCommand("PWR", on ? 1 : 0);
}

void ofxInFocusSerial::writeCommand(string cmd) {
    ofxProjectorSerial::write("(" + cmd + ")");
    ofSleepMillis(3);
}

void ofxInFocusSerial::writeCommand(string cmd, int value) {
    ofxProjectorSerial::write("(" + cmd + ofToString(value) + ")");
    ofSleepMillis(3);
}

string ofxInFocusSerial::readCommand(string cmd) {
    ofxProjectorSerial::write("(" + cmd + "?)");
    string ret = ofxProjectorSerial::read();
    int a = ret.find_last_of(',');
    int b = ret.find_last_of(')');
    if (a != -1 && b!= -1)
        return ret.substr(a+1, b-a-1);
    else
        return "";
}