#include "thread.h"
#include "cpuloop.h"
#include "calibrator.h"
#include "mutex.h"
#include <memory>
#include <sched.h>
#include "timespec.h"

class Thread_A : public Thread {
    private:
        std::unique_ptr<CpuLoop> cpuLoop;
        std::shared_ptr<Mutex> mutex;
        void run() override;
        double tic_duration_ms;
    public:
        Thread_A(int id, double tic_duration_ms, std::shared_ptr<Calibrator> calibrator) : Thread(id){
            cpuLoop = std::make_unique<CpuLoop>(*calibrator);
            this->tic_duration_ms = tic_duration_ms;
        };
};

void Thread_A::run() {
    cpuLoop->runTime(tic_duration_ms);
    {
        Mutex::Lock lock(*mutex);
        cpuLoop->runTime(tic_duration_ms);
    }
    cpuLoop->runTime(2*tic_duration_ms);
};

class Thread_B : public Thread {
    private:
        std::unique_ptr<CpuLoop> cpuLoop;
        std::shared_ptr<Mutex> mutex;
        void run() override;
        double tic_duration_ms;
    public:
        Thread_B(int id, double tic_duration_ms, std::shared_ptr<Calibrator> calibrator) : Thread(id){
            cpuLoop = std::make_unique<CpuLoop>(*calibrator);
            this->tic_duration_ms = tic_duration_ms;
        };
};

void Thread_B::run() {
    cpuLoop->runTime(tic_duration_ms);
};

class Thread_C : public Thread {
    private:
        std::unique_ptr<CpuLoop> cpuLoop; 
        std::shared_ptr<Mutex> mutex;
        void run() override;
        double tic_duration_ms;
    public:
        Thread_C(int id, double tic_duration_ms, std::shared_ptr<Calibrator> calibrator) : Thread(id){
            cpuLoop = std::make_unique<CpuLoop>(*calibrator);
            this->tic_duration_ms = tic_duration_ms;
        };
};

void Thread_C::run() {
    cpuLoop->runTime(2*tic_duration_ms);
    {
        Mutex::Lock lock(*mutex);
        cpuLoop->runTime(2*tic_duration_ms);
    }
    cpuLoop->runTime(tic_duration_ms);
}

int main(int argc, char ** argv){
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

    double tic = 10;
    Thread::setMainSched(SCHED_RR);
    auto calibrator = std::make_shared<Calibrator>(200, 10);
    auto task_A = std::make_unique<Thread_A>(1, tic, calibrator);
    auto task_B = std::make_unique<Thread_B>(2, tic, calibrator);
    auto task_C = std::make_unique<Thread_C>(3, tic, calibrator);
}

