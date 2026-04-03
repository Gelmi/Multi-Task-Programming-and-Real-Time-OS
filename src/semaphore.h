#ifndef semaphore_h_INCLUDED
#define semaphore_h_INCLUDED

#include "monitor.h"
#include <memory>
#include <limits>

class Semaphore {
    private:
        std::shared_ptr<Mutex> m;
        std::unique_ptr<Monitor> notEmpty;
        using CountType = unsigned long;
        CountType counter;
        CountType maxCount;

    public:
        Semaphore(CountType initValue=0, CountType maxValue=std::numeric_limits<CountType>::max());
        void give();
        void take();
        bool take(long timeout_ms);
};

#endif
