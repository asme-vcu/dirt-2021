# FSAE-DIRT-2021
VCU FSAE D.I.R.T. Competition Github (Power Systems Team) 2020-2021

# Layout

This project will be made of submodules, each with their own class and header.
The coding style for each submodule should be as consistent as possible, try to follow
what is already here.

# Quick style guide

Module interfaces should be created like this:

`module.h`
```c++
#ifndef MODULE_H
#define MODULE_H

class Module {
  public:
    Module(byte pin1, byte pin2);
    
    void setup();
    void run();
    
    long getVal();
    void setVal(long val);
    void printDebug();

  private:
    byte _pin1, _pin2;
    long _val, _timer;
    const static long _TIMER_LIMIT;
    
    void doStuff();
    long helper(long val);
    bool checkTimer();
};

#endif
```

Module implementations like this:

`module.cpp`
```c++
#include"module.h"

Module::Module(byte pin1, byte pin2) {
  _pin1 = _pin1;
  _pin2 = _pin2;
}

void Module::setup() {
  _timer = millis();
  _val = analogRead(_pin1);
  pinMode(_pin2, OUTPUT);
}

void Module::run() {
  // main loop code here
  if(checkTimer) doStuff();
  digitalWrite(_pin2, helper(_val) > 2500);
}

long Module::getVal() {
  return _val;
}

void Module::setVal(long val) {
  _timer = millis();
  _val = val;
}

void printDebug() {
#ifdef DEBUG_ENABLED
  if(Serial) {
    Serial.println("Debug here!");
  }
#endif
}

Module::_TIMER_LIMIT = 2000; // timer goes off every 2 seconds

void Module::doStuff() {
  // do some weird cryptic stuff every _TIMER_LIMIT milliseconds
}

long Module::helper(long val) {
  // do some complicated calculation using this value that's only useful for this module alone
  return (val << 16) + (val >> 16);
}

bool Module::checkTimer() {
  if(millis() - _timer >= _TIMER_LIMIT) {
    _timer = millis();
    return true;
  }
  return false;
}
```

And lastly there should be ONE SINGLE `main.ino` file
```c++
#define DEBUG_ENABLED
#define PIN1 10
#define PIN2 11
#define START_VAL 1234

#include"module.h"

Module module(10, 11);

void setup() {
  module.setup();
  module.setVal(START_VAL);
}

void loop() {
  module.run();
  
  module.printDebug();
}
```
