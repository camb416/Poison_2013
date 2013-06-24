//  PhidgetConnector.h
//
// Created by Cameron Browning on 6/20/12.
// draws heavily from Patrick from this thread: http://www.phidgets.com/phorum/viewtopic.php?f=37&t=3472
// Copyright (c) 2012 Cameron Browning
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef PhidgetConnector_h
#define PhidgetConnector_h

#include "phidget21.h"
#include "PhidgetModel.h"
#include <iostream>
#include <vector>
using namespace std;

int  SensorChangeHandler(CPhidgetInterfaceKitHandle IFK, void *usrptr, int Index, int Value);
int ErrorHandler(CPhidgetHandle IFK, void *usrtpr, int ErrorCode, const char * ErrorDescription);

//Class definition
class PhidgetConnector {

public:

    vector <CPhidgetInterfaceKitHandle*> ifkits;
    vector <IFKitModel*> ifKitModels;
    CPhidgetInterfaceKitHandle ifkit;
    CPhidgetInterfaceKitHandle ifkit2;
    IFKitModel * getIFKit(int serial_in);
    vector<int> sensorVals;
    void connect(int serial_in = -1, int _timeOut = -1);
    void sensorChanged(CPhidgetInterfaceKitHandle IFK, int index, int value);
    void print(int serial_in = -1);
    int getVal(int serial_in, int index_in);
    bool getBool(int serial_in, int index_in);
    void updateKits();
    void reset();
    bool useEvents(bool bUseEvents_in);
    PhidgetConnector();
    ~PhidgetConnector();
    
private:
    bool bUseEvents;
    int state;
    int display_properties(CPhidgetInterfaceKitHandle phid);
    int getIFKitModelID(int serial_in);
    
};

#endif