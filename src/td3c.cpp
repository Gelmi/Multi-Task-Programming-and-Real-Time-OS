#include "mutex.h"
#include <iostream>
#include <memory>
#include "thread.h"

class IncrementThread : public Thread {
    public:
        IncrementThread(int id, volatile int* counter, const int n, std::shared_ptr<Mutex> mutex);
    private:
        std::shared_ptr<Mutex> mutex;
        volatile int* counter;
        const int n;
        void run() override;
};

IncrementThread::IncrementThread(int id, volatile int* counter, const int n, std::shared_ptr<Mutex> mutex) 
    : Thread(id), mutex(mutex), counter(counter), n(n){
};

void IncrementThread::run() {
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        try{
            //std::cout << "Trying to catch mutex" << std::endl;
            Mutex::Lock lock(*mutex);
            (*counter)++;
        }
        catch(const std::string& e)
        {
            std::cerr << e;
        }
    }
};

int main() {
    // ── Two threads incrementing a shared counter ──
    const int N = 100000;
    volatile int counter = 0;
    std::shared_ptr<Mutex> mutex = std::make_shared<Mutex>();
    try{
        IncrementThread t1 = IncrementThread(1, &counter, N, mutex);
        IncrementThread t2 = IncrementThread(2, &counter, N, mutex);
        IncrementThread t3 = IncrementThread(3, &counter, N, mutex);
        t1.start();
        t2.start();
        t3.start();
        t1.join();
        t2.join();
        t3.join();
    }
    catch(const std::string& e)
    {
        std::cerr << e;
    }  
    std::cout << "Counter = " << counter
              << " (expected " << 3 * N << ")\n";

    std::cout << "All tests passed.\n";
    return 0;
};
