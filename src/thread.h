#ifndef thread_h_INCLUDED
#define thread_h_INCLUDED

#include <pthread.h>

class Thread {
    private:
        pthread_t posixThreadId;
        pthread_attr_t posixThreadAttrId;
        const int id;
        static void* call_run(void* v_thread);
        bool started;
        long duration;

    protected:
        virtual void run() = 0;

    public:
        Thread(int id);
        ~Thread();
        void start(int priority = 0);
        void join();
        bool isStarted();
        long duration_ms();
        int getId() const;
        static int getMaxPrio(int policy);
        static int getMinPrio(int policy);
        static void setMainSched(int policy);
        static int getMainSched();
};

#endif
