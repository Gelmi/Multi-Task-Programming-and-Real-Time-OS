#include <time.h>
#include <signal.h>

class Timer {
private:
    timer_t tid;
public:
    Timer();
    ~Timer();
    void start(timespec duration, bool isPeriodic);
    void start_ms(double duration_ms, bool isPeriodic);
    void stop();
    virtual void callback() = 0;
private:
    static void call_callback([[maybe_unused]]int signo, siginfo_t* si, void*);
};