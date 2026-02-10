#include <ctime>
#include <signal.h>
#include <iostream>

void print_signal(int, siginfo_t* si, void*){
    int *signal = (int *) si->si_value.sival_ptr;
    std::cout << *signal << std::endl;
    *signal += 1;
}

int main(){
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = print_signal;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    int value = 0;
    sev.sigev_value.sival_ptr = (void *) &value;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 500000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 500000000;
    timer_settime(tid, 0, &its, nullptr);
    while(value < 15) {};
    timer_delete(tid);
    return 0;
}
