#ifndef cpuloop_h_INCLUDED
#define cpuloop_h_INCLUDED

#include "calibrator.h"
#include "looper.h"

class CpuLoop {
    private:
        Calibrator& calibrator;
        Looper looper;

    public:
        CpuLoop(Calibrator& calibrator); 
        double runTime(double duration_ms);
};

#endif
