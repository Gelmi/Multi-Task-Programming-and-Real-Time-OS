#ifndef mutex_h_INCLUDED
#define mutex_h_INCLUDED

#include<pthread.h>

class Mutex {
    private:
        pthread_mutex_t posixMutexId;
        pthread_mutexattr_t posixMutexAttrId;

        void lock();
        bool lock(double timeout_ms);
        void unlock();

    public:
        class Lock;
        Mutex(bool isInversionSafe = false);
        ~Mutex(); 
};

class Mutex::Lock {
    public:
        Lock(Mutex& mutex);
        Lock(Mutex& mutex, double timeout_ms);
        ~Lock();

    protected:
        pthread_mutex_t* getPosixMutexId();

    private:
        Mutex& mutex;
};

class TimeoutException {
    private:
        const long timeout_ms;

    public:
        TimeoutException(long timeout_ms) : timeout_ms(timeout_ms) {} ;
        long getTimeout_ms() const;
};
#endif
