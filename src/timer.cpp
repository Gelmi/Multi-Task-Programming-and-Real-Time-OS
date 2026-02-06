#include "timer.h"
#include <signal.h>
#include <iostream>
#include "timespec.h"

Timer::Timer() {
    this->sa.sa_flags = SA_SIGINFO;
    this->sa.sa_sigaction = this->call_callback;
    sigemptyset(&this->sa.sa_mask);
    sigaction(SIGRTMIN, &this->sa, nullptr);

    this->sev.sigev_notify = SIGEV_SIGNAL;
    this->sev.sigev_signo = SIGRTMIN;
    this->sev.sigev_value.sival_ptr = (void *) this;

    timer_create(CLOCK_REALTIME, &this->sev, &this->tid);
}

Timer::~Timer() {
    timer_delete(this->tid);
}

void Timer::start(timespec duration, bool isPeriodic) {
    itimerspec its;
    its.it_value.tv_sec = duration.tv_sec;
    its.it_value.tv_nsec = duration.tv_nsec;
    its.it_interval.tv_sec = isPeriodic ? duration.tv_sec : 0;
    its.it_interval.tv_nsec = isPeriodic ? duration.tv_nsec : 0;
    timer_settime(this->tid, 0, &its, nullptr);
}

void Timer::start_ms(double duration_ms, bool isPeriodic) {
    this->start(timespec_from_ms(duration_ms), isPeriodic);
}

void Timer::stop() {
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime(this->tid, 0, &its, nullptr);
}

void Timer::call_callback(int, siginfo_t *si, void *) { 
    Timer* timer = (Timer*)si->si_value.sival_ptr;
    timer->callback();
}

CountDown::CountDown(int max) : Timer(){
    this->counter = max;
}

void CountDown::callback() { 
    std::cout << this->counter << std::endl;
    this->counter -= 1;
    if(this->counter < 0) this->stop();
}

int CountDown::get_counter(){
    return this->counter;
}
