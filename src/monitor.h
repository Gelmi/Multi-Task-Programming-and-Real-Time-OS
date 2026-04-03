#ifndef monitor_h_INCLUDED
#define monitor_h_INCLUDED

#include<pthread.h>
#include "mutex.h"

class Monitor {
    private:
        pthread_cond_t posixCondId;
        Mutex& mutex;

    public:
        class Lock;
        Monitor(Mutex& mutex);
        void notify();
        void notifyAll();
};

class Monitor::Lock : public Mutex::Lock {
    private:
        Monitor& monitor;

    public:
        Lock(Monitor& monitor);
        Lock(Monitor& monitor, double timeout_ms);
        void wait();
        void wait(double timeout_ms);
};

#endif
