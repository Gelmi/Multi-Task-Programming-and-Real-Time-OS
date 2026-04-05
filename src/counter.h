#ifndef counter_h_INCLUDED
#define counter_h_INCLUDED

#include <memory>

#include "mutex.h"
#include "thread.h"

class Counter {
    private:
        double m_value;
        std::unique_ptr<Mutex> p_mutex;
        double incrDoProtect();
        double incrNoProtect();
        double (Counter::*incrProtect)();
        bool protect;

    public:
        Counter(bool protect);
        ~Counter() {};
        double increment();
        double value();
        bool isProtected();
};

class Incrementer : public Thread {
    private:
        double nLoops;
        Counter& r_counter;
        void run() override;

    public:
        Incrementer(int id, Counter& counter, double nLoops)
            : Thread(id), nLoops(nLoops), r_counter(counter) {};
        ~Incrementer() {};
};

#endif
