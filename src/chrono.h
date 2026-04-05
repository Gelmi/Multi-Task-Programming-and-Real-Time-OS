#ifndef chrono_h_INCLUDED
#define chrono_h_INCLUDED

#include<time.h>

class Chrono {
    private:
        timespec m_startTime;
        timespec m_stopTime;
    public:
        Chrono();
        void restart();
        timespec stop();
        bool isActive() const;
        timespec lap() const;
        double lap_ms() const;
};

#endif
