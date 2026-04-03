#include "Calibrator.h"

Calibrator::Calibrator(double samplingPeriod, unsigned nSamples)
{
    start_ms(samplingPeriod);
    looper.runLoop();
    while(this.samples.size() < nSamples)
    {
        continue;
    }
    stop();

    double sumLoopsTimesT = sumT = sumLoops = sumTSquare = 0;
    
    for(int i = 0; i < nSamples)
    {
        sumLoopsTimesT += samplingPeriod*samples[i];
        sumT += samplingPeriod;
        sumLoops += samples[i];
        sumTSquare += samplingPeriod*samplingPeriod;
    }

    a = (nSamples*sumLoopsTimesT-sumT*sumLoops)/(nSamples*sumTSquare-sumT*sumT)

    b = (sumLoops-a*sumT)/nSamples



}

double Calibrator::nLoops(double duration_ms)
{
    this.start_ms(duration_ms);
    this.looper.runLoop();
    while(this.samples.size() < 1)
    {
        continue;
    }
    this.stop();
    return samples[0]
}

void Calibrator::callback() override
{
    samples.push_back(looper.getSample())
}