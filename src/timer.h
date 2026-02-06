#ifndef timer_h_INCLUDED
#define timer_h_INCLUDED

#include <signal.h>
#include <time.h>
#include <iostream>

void myHandler(int sig, siginfo_t* si, void*);

class Timer {
    private:
        timer_t tid;
        struct sigaction sa;
        struct sigevent sev;

    public:
        Timer();
        ~Timer();
        void start(timespec duration, bool isPeriodic);
        void start_ms(double duration_ms, bool isPeriodic);
        void stop();
        virtual void callback() = 0;
        static void call_callback(int sig, siginfo_t* si, void*);
};

class CountDown : public Timer {
    private:
        volatile int counter;

    public:
        void callback() override;
        CountDown(int max); 
        int get_counter();
};

#endif
