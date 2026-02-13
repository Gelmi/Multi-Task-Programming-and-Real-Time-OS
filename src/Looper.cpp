#include "Looper.h"

Looper::Looper(){
    doStop = true;
    iLoop = 0;
}

Looper::~Looper(){

}

double Looper::runLoop(double nLoops = DBL_MAX){
    iLoop = 0;
    doStop = false;
    while(iLoop<nLoops && !doStop) {
        iLoop += 1;
    }
    return iLoop;
}
double Looper::getSample(){
    return iLoop;
}

double Looper::stoptLoop(){
    doStop = true;
    return iLoop;
}