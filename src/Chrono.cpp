#include "Chrono.h"
#include "TimespecOps.h"
#include <cstdio>

Chrono::Chrono() {}

Chrono::~Chrono() {}

timespec Chrono::stop() {
    timespec_get(&m_stopTime, TIME_UTC);
    return m_stopTime - m_startTime;
}

void Chrono::restart() {
    timespec_get(&m_startTime, TIME_UTC);
    m_stopTime = m_startTime;
}

bool Chrono::isActive() {
    return m_startTime == m_stopTime;
}

timespec Chrono::lap() {
    if(m_startTime == m_stopTime){
        timespec lap_time;
        timespec_get(&lap_time, TIME_UTC);
        return lap_time - m_startTime;
    }
    else {
        return m_stopTime - m_startTime;
    }
}

double Chrono::lap_ms() {
    timespec spec_time = lap();
    return TimespecOps::timespec_to_ms(spec_time);
}