#ifndef looper_h_INCLUDED
#define looper_h_INCLUDED
#include<cfloat>

class Looper {
    private:
        volatile bool doStop;
        volatile double iLoop;

    private:
        double runLoop(double nLoops = DBL_MAX);
        double getSample();
        double stopLoop();
};

#endif
