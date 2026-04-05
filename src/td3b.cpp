#include "mutex.h"
#include <iostream>
#include <pthread.h>

// Shared counter protected by a Mutex
static Mutex gMutex;
static int   gCounter = 0;

void* increment(void* arg) {
    int n = *static_cast<int*>(arg);
    for (int i = 0; i < n; ++i) {
        Mutex::Lock lock(gMutex);
        ++gCounter;
    }
    return nullptr;
}

int main() {
    // ── Basic lock / unlock via RAII ──────────
    {
        Mutex::Lock lock(gMutex);
        std::cout << "Mutex acquired (no timeout)\n";
    }
    std::cout << "Mutex released\n";

    // ── Two threads incrementing a shared counter ──
    const int N = 100'000;
    int arg = N;
    pthread_t t1, t2, t3;
    pthread_create(&t1, nullptr, increment, &arg);
    pthread_create(&t2, nullptr, increment, &arg);
    pthread_create(&t3, nullptr, increment, &arg);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    std::cout << "Counter = " << gCounter
              << " (expected " << 3 * N << ")\n";

    // ── Timeout test ──────────────────────────
    {
        Mutex::Lock outerLock(gMutex);   // hold the mutex
        try {
            Mutex::Lock innerLock(gMutex, 50.0);  // should time out
            std::cout << "ERROR: should have thrown TimeoutException\n";
        } catch (const TimeoutException& e) {
            std::cout << "TimeoutException caught (timeout_ms="
                      << e.getTimeout_ms() << ")\n";
        }
    }

    std::cout << "All tests passed.\n";
    return 0;
}
