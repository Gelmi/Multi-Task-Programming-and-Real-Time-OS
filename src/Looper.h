#include <time.h>
#include <signal.h>
#include <climits>

// #define DBL_MAX 100

class Looper {
private:
    volatile bool doStop;
    volatile double iLoop;
public:
    Looper();
    ~Looper();
    double runLoop(double nLoops);
    double getSample();
    double stoptLoop();
};