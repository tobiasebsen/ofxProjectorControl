//
//  ofxProjectorSerial.cpp
//  greveBord
//
//  Created by Tobias Ebsen on 21/07/14.
//
//

#include "ofxProjectorSerial.h"

bool ofxProjectorSerial::setup(string portName, int baudrate, bool flowcontrol) {
    bool success = ofSerial::setup(portName, baudrate);
    if (success)
        enableFlowcontrol(flowcontrol);
    return success;
}

vector<string> ofxProjectorSerial::getPortNames() {
    vector<string> names;
    ofSerial serial;
    vector<ofSerialDeviceInfo> list = serial.getDeviceList();
    vector<ofSerialDeviceInfo>::iterator it = list.begin();
    for (; it!=list.end(); ++it) {
        names.push_back(it->getDeviceName());
    }
    return names;
}

void ofxProjectorSerial::enableFlowcontrol(bool enable) {

    struct termios options;
    tcgetattr(fd, &options);

    if (enable) {
        options.c_iflag |= (IXON | IXOFF);
        options.c_lflag |= (ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        options.c_cflag |= CRTSCTS;
    } else {
        // Disable hardware flow control
        options.c_iflag &= ~(IXON | IXOFF);
        options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        options.c_cflag &= ~CRTSCTS;
    }
    tcsetattr(fd, TCSANOW, &options);
}

void ofxProjectorSerial::write(string str) {
    ofSerial::writeBytes((uint8_t*)str.data(), str.length());
}

string ofxProjectorSerial::read(int timeout) {
    stringstream ss;
    string s;
    if (timeout > 0) {
        unsigned long long time = ofGetElapsedTimeMillis();
        while (ofSerial::available() == 0 && ofGetElapsedTimeMillis() - time < timeout) {
            ofSleepMillis(1);
        }
    }
    while (ofSerial::available() > 0) {
        s.reserve(ofSerial::available());
        int n = ofSerial::readBytes((uint8_t*)s.data(), s.capacity());
        ss.write(s.data(), n);
    }
    return ss.str();
}