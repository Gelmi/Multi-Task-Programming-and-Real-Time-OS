#include "chrono.h"
#include "timespec.h"

Chrono::Chrono(){
    Chrono::restart();
}

void Chrono::restart(){
    this->m_startTime = timespec_now();
    this->m_stopTime = this->m_startTime;
}

timespec Chrono::stop(){
    this->m_stopTime = timespec_now();
    return this->m_stopTime - this->m_startTime;
}

bool Chrono::isActive() const{
    return this->m_startTime == this->m_stopTime;
}

timespec Chrono::lap() const{
    if(this->isActive()){
        return timespec_now() - this->m_startTime;
    } else {
        return this->m_stopTime - this->m_startTime;
    }
}

double Chrono::lap_ms() const{
    return timespec_to_ms(this->lap());
}

