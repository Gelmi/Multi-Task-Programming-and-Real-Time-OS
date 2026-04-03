#include <iostream>
#include <vector>
#include "Looper.h"
#include "Timer.h"

class Calibrator : public Timer
{
private:
    double a;
    double b;
    std::vector<double> samples;
    Looper looper;
public:
    Calibrator(double samplingPeriod, unsigned nSamples);
    double nLoops(double duration_ms);
protected:
    void callback();
}