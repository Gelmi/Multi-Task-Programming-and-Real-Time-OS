#include "looper.h"
#include<iostream>

double Looper::runLoop(double nLoops) {
    this->doStop = false;
    this->iLoop = 0;
    while(!this->doStop && this->iLoop < nLoops){
        this->iLoop += 1.0;
    }
    return this->iLoop;
}

double Looper::getSample() const {
    return this->iLoop;
}

double Looper::stopLoop() {
    this->doStop = true;
    return this->iLoop;
}
