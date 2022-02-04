/* Simple LED class */

#ifndef LED_H
#define LED_H

class LED {
    public:
        enum status{on, off, blink};

        LED(uint32_t);
        
        // setters
        void setOn();
        void setOff();
        void setBlink();

        // reverses state (for implementing blinking)
        void toggle();

        // getter
        status getStatus();

        void printDebug();

    private:

        uint32_t _pin;  // pin the LED is on
        status _status; // what should the LED be doing
        bool _state;    // what the LED is actually doing
};

#endif
