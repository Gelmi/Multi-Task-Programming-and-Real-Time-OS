#ifndef calibrator_h_INCLUDED
#define calibrator_h_INCLUDED

#include <vector>
#include "timer.h"
#include "looper.h"

class Calibrator : public Timer {
    private:
        double a, b;
        std::vector<double> samples;
        Looper looper;
        unsigned nSamples;

    public:
        Calibrator(double samplingPeriod_ms, unsigned nSamples);
        double nLoops(double duration_ms);
        void callback() override;
};

#endif
