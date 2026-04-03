#include "thread.h"
#include <bits/types/struct_sched_param.h>
#include <pthread.h>
#include <sched.h>
#include <iostream>
#include "chrono.h"

Thread::Thread(int id) : id(id){
    pthread_attr_init(&this->posixThreadAttrId);
    this->started = false;
}

Thread::~Thread(){
}

void* Thread::call_run(void* v_thread){
    Thread* thread = (Thread*)v_thread;
    Chrono chrono = Chrono();
    chrono.restart();
    thread->run();
    thread->duration = chrono.lap_ms();
    return v_thread;
}

void Thread::start(int priority){
    sched_param schedParams{};
    schedParams.sched_priority = priority;
    pthread_attr_setschedparam(&this->posixThreadAttrId, &schedParams);
    pthread_create(&this->posixThreadId, &this->posixThreadAttrId, call_run, this);
    this->started = true;
    pthread_attr_destroy(&this->posixThreadAttrId);
}

void Thread::join(){
    if(isStarted()) {
        pthread_join(this->posixThreadId, NULL);
        this->started = false;
    }
}

bool Thread::isStarted(){
    return this->started;
}

long Thread::duration_ms(){
    if(!isStarted()){
        return duration;
    }
    return 0;
}

int Thread::getId() const{
    return this->id;
}

int Thread::getMaxPrio(int policy){
    return sched_get_priority_max(policy);
}

int Thread::getMinPrio(int policy){
    return sched_get_priority_min(policy);
}

void Thread::setMainSched(int policy){
    sched_param schedParam{};
    pthread_setschedparam(pthread_self(), policy, &schedParam);
}

int Thread::getMainSched(){
    int policy;
    sched_param schedParam;
    pthread_getschedparam(pthread_self(), &policy, &schedParam);
    return policy;
}
