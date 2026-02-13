#include "Timer.h"



Timer::Timer() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);
}

Timer::~Timer() {
    timer_delete(this->tid);
}

void Timer::start(timespec duration, bool isPeriodic) {
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = this;

    timer_create(CLOCK_REALTIME, &sev, &this->tid);
    itimerspec its;
    its.it_value = duration;
    if(isPeriodic){
        its.it_interval = duration;
    }
    timer_settime(this->tid, 0, &its, nullptr);
}

void Timer::start_ms(double duration_ms, bool isPeriodic) {
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = this;

    timer_create(CLOCK_REALTIME, &sev, &this->tid);
    itimerspec its;
    if(duration_ms < 0)
    {
        its.it_value.tv_sec = (duration_ms/1000)-1;
        its.it_value.tv_nsec = -((its.it_value.tv_sec*1000) - duration_ms)*1000000;
        if(its.it_value.tv_nsec == 1000000000)
        {
            its.it_value.tv_sec = its.it_value.tv_sec +1;
            its.it_value.tv_nsec = 0;
        }
    }
    else
    {
        its.it_value.tv_sec = (duration_ms/1000);
        its.it_value.tv_nsec = (duration_ms - (its.it_value.tv_sec*1000))*1000000;
    }
    
    if(isPeriodic){
        its.it_interval.tv_sec = its.it_value.tv_sec;
        its.it_interval.tv_nsec = its.it_value.tv_nsec;
    }
    timer_settime(this->tid, 0, &its, nullptr);
}

void Timer::stop() {
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    timer_settime(this->tid, 0, &its, nullptr);
}

void Timer::call_callback([[maybe_unused]]int signo, siginfo_t* si, void*) {
    Timer* p = (Timer*)(si->si_value.sival_ptr);
    p->callback();
}
