#include <time.h>
#include <signal.h>
#include "TimespecOps.h"

class Chrono {
private:
    timespec m_startTime;
    timespec m_stopTime;
public:
    Chrono();
    ~Chrono();
    timespec stop();
    void restart();
    bool isActive();
    timespec lap();
    double lap_ms();
};