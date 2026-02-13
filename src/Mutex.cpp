#include "Mutex.h"
#include "TimeoutException.h"

Mutex::Mutex()
{
    pthread_mutexattr_t mutexAttribute;
    pthread_mutexattr_init(&mutexAttribute);
    pthread_mutexattr_settype(&mutexAttribute, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, &mutexAttribute);
    pthread_mutexattr_destroy(&mutexAttribute);
    this->posixMutexId = mutex;
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&this->posixMutexId);
}

void Mutex::lock()
{
    pthread_mutex_lock(&this->posixMutexId);
}

bool Mutex::lock(double timeout_ms)
{
    timespec deadline;
    deadline = TimespecOps::timespec_now();
    deadline += TimespecOps::timespec_from_ms(timeout_ms);
    if (pthread_mutex_timedlock(&this->posixMutexId, &deadline) == ETIMEDOUT) {
        return false;
    }
    return true;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&this->posixMutexId);
}

Mutex::Lock::Lock(Mutex& mutex) : mutex(mutex)
{
    mutex.lock();
}

Mutex::Lock::Lock(Mutex& mutex, double timeout_ms) : mutex(mutex)
{
    if (!mutex.lock(timeout_ms)) {
        throw TimeoutException(timeout_ms);
    }
}

Mutex::Lock::~Lock()
{
    mutex.unlock();
}
