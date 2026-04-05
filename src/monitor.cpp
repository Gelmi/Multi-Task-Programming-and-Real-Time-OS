#include "monitor.h"
#include "timespec.h"

Monitor::Monitor(Mutex& mutex) : mutex(mutex) {
    pthread_cond_init(&posixCondId, nullptr);
}

void Monitor::notify(){
    pthread_cond_signal(&posixCondId);
}

void Monitor::notifyAll(){
    pthread_cond_broadcast(&posixCondId);
}

Monitor::Lock::Lock(Monitor& monitor) : Mutex::Lock(monitor.mutex), monitor(monitor){
}

Monitor::Lock::Lock(Monitor& monitor, double timeout_ms) : Mutex::Lock(monitor.mutex, timeout_ms), monitor(monitor){
}

void Monitor::Lock::wait(){
    pthread_cond_wait(&monitor.posixCondId, getPosixMutexId());
}

void Monitor::Lock::wait(double timeout_ms){
    timespec abstime = timespec_now();
    abstime += timespec_from_ms(timeout_ms);
    pthread_cond_timedwait(&monitor.posixCondId, getPosixMutexId(), &abstime); 
}
