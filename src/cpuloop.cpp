#include "cpuloop.h"
#include "chrono.h"

CpuLoop::CpuLoop(Calibrator& calibrator) : calibrator(calibrator){
    looper = Looper();
}

double CpuLoop::runTime(double duration_ms) {
    double loops = calibrator.nLoops(duration_ms);

    Chrono chrono;
    chrono.restart();
    looper.runLoop(loops);
    chrono.stop();

    double measured_ms = chrono.lap_ms();

    return (measured_ms - duration_ms) / duration_ms;
}

