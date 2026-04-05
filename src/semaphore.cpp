#include "semaphore.h"
#include "timespec.h"

Semaphore::Semaphore(CountType initValue, CountType maxValue) : counter(initValue), maxCount(maxValue){
    m = std::make_shared<Mutex>();
    notEmpty = std::make_unique<Monitor>(*m);
}

void Semaphore::give(){
    Monitor::Lock lock(*notEmpty);
    counter++;
    notEmpty->notifyAll();
}

void Semaphore::take(){
    Monitor::Lock lock(*notEmpty);
    while(counter == 0) lock.wait();
    counter--;
}

bool Semaphore::take(long timeout_ms){
    Monitor::Lock lock(*notEmpty);
    if(counter == 0) lock.wait(timeout_ms);
    if(counter > 0){
        counter--;
        return true;
    } else {
        return false;
    }
}
