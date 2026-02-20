#include "calibrator.h"

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples) : Timer(){
    this->nSamples = nSamples;
    looper = Looper();
    this->start_ms(samplingPeriod_ms, true);
    looper.runLoop();  
    int n = (int)this->samples.size();

    double sum_x  = 0.0, sum_y  = 0.0;
    double sum_xx = 0.0, sum_xy = 0.0;

    for (int i = 0; i < n; i++) {
        double x = (i + 1) * samplingPeriod_ms;
        double y = samples[i];
        sum_x  += x;
        sum_y  += y;
        sum_xx += x * x;
        sum_xy += x * y;
    }

    double denom = n * sum_xx - sum_x * sum_x;
    this->a = (n * sum_xy - sum_x * sum_y) / denom;
    this->b = (sum_y - this->a * sum_x) / n;
}

void Calibrator::callback() {
    this->samples.push_back(this->looper.getSample());
    if(this->samples.size() >= nSamples){
        this->stop();
        looper.stopLoop();
    }
}

double Calibrator::nLoops(double duration_ms){
    return this->a * duration_ms + this->b; 
}
