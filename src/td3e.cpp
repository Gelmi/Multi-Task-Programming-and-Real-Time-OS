#include "thread.h"
#include "cpuloop.h"
#include "calibrator.h"
#include "mutex.h"
#include <memory>
#include <sched.h>
#include "timespec.h"
#include "chrono.h"

class TimedThread : public Timer {
    public:
        TimedThread(Thread* thread, int priority) : Timer(){
            this->thread = thread;
            this-> priority = priority;
        }

        void scheduleAt(double offset_ms) {
            this->start_ms(offset_ms, false);
        }

    private:
        Thread* thread;
        int priority;

        void callback() override {
            thread->start(priority);
        }
};

class Thread_A : public Thread {
    private:
        std::unique_ptr<CpuLoop> cpuLoop;
        std::shared_ptr<Mutex> mutex;
        void run() override;
        double tic_duration_ms;
    public:
        double lap_time_ms = 0;
        std::shared_ptr<Chrono> chrono;
        Thread_A(int id, double tic_duration_ms, std::shared_ptr<Calibrator> calibrator, std::shared_ptr<Mutex> mutex, std::shared_ptr<Chrono> chrono) : Thread(id){
            cpuLoop = std::make_unique<CpuLoop>(*calibrator);
            this->mutex = mutex;
            this->tic_duration_ms = tic_duration_ms;
            this->chrono = chrono;
        };
};

void Thread_A::run() {
    chrono->restart();
    cpuLoop->runTime(100*tic_duration_ms);
    {
        Mutex::Lock lock(*mutex);
        cpuLoop->runTime(100*tic_duration_ms);
    }
    cpuLoop->runTime(200*tic_duration_ms);
    lap_time_ms = chrono->lap_ms();
};

class Thread_B : public Thread {
    private:
        std::unique_ptr<CpuLoop> cpuLoop;
        std::shared_ptr<Mutex> mutex;
        void run() override;
        double tic_duration_ms;
    public:
        double lap_time_ms = 0;
        std::shared_ptr<Chrono> chrono;
        Thread_B(int id, double tic_duration_ms, std::shared_ptr<Calibrator> calibrator, std::shared_ptr<Mutex> mutex, std::shared_ptr<Chrono> chrono) : Thread(id){
            cpuLoop = std::make_unique<CpuLoop>(*calibrator);
            this->mutex = mutex;
            this->tic_duration_ms = tic_duration_ms;
            this->chrono = chrono;
        };
};

void Thread_B::run() {
    chrono->restart();
    cpuLoop->runTime(100*tic_duration_ms);
    lap_time_ms = chrono->lap_ms();
};

class Thread_C : public Thread {
    private:
        std::unique_ptr<CpuLoop> cpuLoop; 
        std::shared_ptr<Mutex> mutex;
        void run() override;
        double tic_duration_ms;
    public:
        double lap_time_ms = 0;
        std::shared_ptr<Chrono> chrono;
        Thread_C(int id, double tic_duration_ms, std::shared_ptr<Calibrator> calibrator, std::shared_ptr<Mutex> mutex, std::shared_ptr<Chrono> chrono) : Thread(id){
            cpuLoop = std::make_unique<CpuLoop>(*calibrator);
            this->mutex = mutex;
            this->tic_duration_ms = tic_duration_ms;
            this->chrono = chrono;
        };
};

void Thread_C::run() {
    chrono->restart();
    cpuLoop->runTime(200*tic_duration_ms);
    {
        Mutex::Lock lock(*mutex);
        cpuLoop->runTime(200*tic_duration_ms);
    }
    cpuLoop->runTime(100*tic_duration_ms);
    lap_time_ms = chrono->lap_ms();
}

int main(){
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

    double tic = 10;
    Thread::setMainSched(SCHED_RR);
    auto calibrator = std::make_shared<Calibrator>(200, 10);
    auto mutex = std::make_shared<Mutex>(true);

    auto chrono_A = std::make_shared<Chrono>();
    auto task_A = std::make_unique<Thread_A>(1, tic, calibrator, mutex, chrono_A);
    auto timer_A = std::make_unique<TimedThread>(task_A.get(), 99);

    auto chrono_B = std::make_shared<Chrono>();
    auto task_B = std::make_unique<Thread_B>(2, tic, calibrator, mutex, chrono_B);
    auto timer_B = std::make_unique<TimedThread>(task_B.get(), 98);

    auto chrono_C = std::make_shared<Chrono>();
    auto task_C = std::make_unique<Thread_C>(3, tic, calibrator, mutex, chrono_C);
    auto timer_C = std::make_unique<TimedThread>(task_C.get(), 97);

    timer_A->scheduleAt(300);
    timer_B->scheduleAt(300);
    timer_C->scheduleAt(0);
    
    task_A->join();
    task_B->join();
    task_C->join();

    std::cout << "Time A: " << task_A->lap_time_ms << std::endl;
    std::cout << "Time B: " << task_B->lap_time_ms << std::endl;
    std::cout << "Time C: " << task_C->lap_time_ms << std::endl;
}