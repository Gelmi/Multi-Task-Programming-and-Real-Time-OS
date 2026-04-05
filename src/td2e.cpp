#include <iostream>
#include <iomanip>
#include <cmath>
#include "calibrator.h"
#include "cpuloop.h"

int main() {
    const double   samplingPeriod_ms = 200.0;  // sample every 200 ms
    const unsigned nSamples          = 10;     // 10 samples → ~2 s calibration

    std::cout << "Calibrating (period=" << samplingPeriod_ms
              << " ms, nSamples=" << nSamples << ") ...\n";

    Calibrator cal(samplingPeriod_ms, nSamples);

    std::cout << "Calibration complete.\n\n";

    CpuLoop cpuLoop(cal);

    std::cout << std::left
              << std::setw(22) << "Requested (ms)"
              << std::setw(22) << "Relative error (%)"
              << std::setw(12) << "Status"
              << "\n";
    std::cout << std::string(56, '-') << "\n";

    const double ERROR_THRESHOLD = 10.0; // percent
    int passed = 0, total = 0;

    for (double target_ms = 500.0; target_ms <= 10000.0; target_ms += 200.0) {
        double relErr    = cpuLoop.runTime(target_ms);   // ratio
        double relErrPct = relErr * 100.0;
        bool   ok        = std::abs(relErrPct) < ERROR_THRESHOLD;

        std::cout << std::left << std::fixed
                  << std::setw(22) << std::setprecision(1) << target_ms
                  << std::setw(22) << std::setprecision(3) << relErrPct
                  << std::setw(12) << (ok ? "OK" : "FAIL")
                  << "\n";

        if (ok) ++passed;
        ++total;
    }

    std::cout << std::string(56, '-') << "\n";
    std::cout << "\nPassed: " << passed << "/" << total
              << " tests within " << ERROR_THRESHOLD << "% error threshold.\n";

    return (passed == total) ? 0 : 1;
}
