#include <pthread.h>
#include <time.h>
#include <cerrno>
#include "TimespecOps.h"


class Mutex
{
private:
    pthread_mutex_t posixMutexId;
public:
    Mutex();
    ~Mutex();
    class Lock;
private:
    void lock();
    bool lock(double timeout_ms);
    void unlock();
};

class Mutex::Lock
{
private:
    Mutex& mutex;
public:
    Lock(Mutex& mutex);
    Lock(Mutex& mutex, double timeout_ms);
    ~Lock();
};