#include "mutex.h"
#include "timespec.h"
#include <cerrno>
#include <pthread.h>
#include <string>

Mutex::Mutex(){
    int err = pthread_mutex_init(&this->posixMutexId, nullptr);
    if (err != 0) throw std::string("pthread_mutex_init failed: error ") + std::to_string(err);
}

Mutex::~Mutex(){
    pthread_mutex_destroy(&this->posixMutexId);
}

void Mutex::lock(){
    int err = pthread_mutex_lock(&this->posixMutexId);
    if (err != 0) throw std::string("pthread_mutex_lock failed: error ") + std::to_string(err);
}

bool Mutex::lock(double timeout_ms){
    timespec deadline = timespec_add(timespec_now(), timespec_from_ms(timeout_ms));
    int err = pthread_mutex_timedlock(&this->posixMutexId, &deadline);
    if (err == 0) return true;
    if (err == ETIMEDOUT) return false;
    throw std::string("pthread_mutex_timedlock failed: error ") + std::to_string(err);
}

void Mutex::unlock(){
    int err = pthread_mutex_unlock(&this->posixMutexId);
    if (err != 0) throw std::string("pthread_mutex_unlock failed: error ") + std::to_string(err);
}

Mutex::Lock::Lock(Mutex& mutex) : mutex(mutex){
    mutex.lock();
}

Mutex::Lock::Lock(Mutex& mutex, double timeout_ms) : mutex(mutex) {
    bool acquired = mutex.lock(timeout_ms);
    if(!acquired) throw TimeoutException(static_cast<long>(timeout_ms));
}

Mutex::Lock::~Lock(){
    mutex.unlock();
}

long TimeoutException::getTimeout_ms() const {
    return this->timeout_ms;
}
