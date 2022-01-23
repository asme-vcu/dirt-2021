#ifndef MODULE_H
#define MODULE_H

class Module {
    public:
        virtual void setup() = 0;
        virtual void run() = 0;
        virtual void printDebug() = 0;
};

#endif