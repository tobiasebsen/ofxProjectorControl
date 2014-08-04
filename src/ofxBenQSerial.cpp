//
//  ofxBenQSerial.cpp
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#include "ofxBenQSerial.h"

bool ofxBenQSerial::setup(string portName) {
    return ofxProjectorSerial::setup(portName, 115200, false);
}

bool ofxBenQSerial::isPowerOn() {
    return readCommand("pow") == "ON";
}

void ofxBenQSerial::setPowerOn(bool on) {
    writeCommand("pow", on ? "on" : "off");
    string ret = ofxProjectorSerial::read();
}

int ofxBenQSerial::getLampHours() {
    return ofToInt( readCommand("lnor") );
}

int ofxBenQSerial::getLampHoursEco() {
    return ofToInt( readCommand("ltim") );
}

bool ofxBenQSerial::isLampEco() {
    return readCommand("lampm") == "eco";
}

void ofxBenQSerial::setLampEco(bool eco) {
    if (eco)
        writeCommand("lampm", "eco");
    else
        writeCommand("lampm", "lnor");
    string ret = ofxProjectorSerial::read();
}

string ofxBenQSerial::getModelName() {
    return readCommand("modelname");
}

void ofxBenQSerial::writeCommand(string cmd, string value) {
    ofxProjectorSerial::write("\r*" + cmd + "=" + value + "#\r");
    ofSleepMillis(10);
}

string ofxBenQSerial::readCommand(string cmd) {
    writeCommand(cmd, "?");
    string ret = ofxProjectorSerial::read();
    cout << ret << endl;
    int a = ret.find_last_of('=');
    int b = ret.find_last_of('#');
    if (a != -1 && b!= -1)
        return ret.substr(a+1, b-a-1);
    else
        return "";
}