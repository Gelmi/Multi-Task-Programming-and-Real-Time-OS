#include <iostream>
#include <iomanip>
#include <cmath>
#include "calibrator.h"
#include "chrono.h"   // Chrono from TD1 — provides start()/stop()/elapsed_ms()
#include "looper.h"

// ---------------------------------------------------------------------------
// Helper: run a Looper for exactly nLoops iterations and measure the wall time
// using Chrono. Returns measured duration in ms.
// ---------------------------------------------------------------------------
static double measureDuration(double nLoopsTarget) {
    Looper looper;
    Chrono chrono;
    chrono.restart();
    looper.runLoop(nLoopsTarget);   // blocks for nLoopsTarget iterations
    chrono.stop();
    return chrono.lap_ms();
}

int main() {
    // ---- Calibration parameters ----
    const double samplingPeriod_ms = 200.0;  // sample every 200 ms
    const unsigned nSamples        = 10;     // collect 10 samples

    std::cout << "Calibrating (period=" << samplingPeriod_ms
              << " ms, nSamples=" << nSamples << ") ...\n";

    Calibrator cal(samplingPeriod_ms, nSamples);

    std::cout << "Calibration done.\n\n";

    // ---- Verification: test durations from 500 ms to 10 000 ms by 200 ms ----
    std::cout << std::left
              << std::setw(20) << "Requested (ms)"
              << std::setw(20) << "Measured (ms)"
              << std::setw(20) << "Error (ms)"
              << std::setw(10) << "Error (%)"
              << "\n";
    std::cout << std::string(70, '-') << "\n";

    for (double target_ms = 500.0; target_ms <= 10000.0; target_ms += 200.0) {
        double loops   = cal.nLoops(target_ms);
        double measured = measureDuration(loops);
        double err     = measured - target_ms;
        double errPct  = 100.0 * std::abs(err) / target_ms;

        std::cout << std::left
                  << std::setw(20) << std::fixed << std::setprecision(1) << target_ms
                  << std::setw(20) << measured
                  << std::setw(20) << err
                  << std::setw(10) << std::setprecision(2) << errPct
                  << "\n";
    }

    return 0;
}
