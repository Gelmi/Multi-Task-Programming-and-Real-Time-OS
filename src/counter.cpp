#include "counter.h"
#include<iostream>

Counter::Counter(bool protect) : m_value(0), protect(protect) {
    if(protect) {
        p_mutex = std::make_unique<Mutex>();
        this->incrProtect = &Counter::incrDoProtect;
    }
    else {
        p_mutex = nullptr;
        this->incrProtect = &Counter::incrNoProtect;
    }
}

double Counter::incrDoProtect() {
    std::cout << "Counter do protect" << std::endl;
    Mutex::Lock lock((Mutex&)this->p_mutex);
    this->m_value += 1.0;
    return this->m_value;
}

double Counter::incrNoProtect() {
    std::cout << "Counter no protect" << std::endl;
    this->m_value += 1.0;
    return this->m_value;
}

double Counter::increment(){
    std::cout << "Incrementando counter" << std::endl;
    return (this->*incrProtect)();
}

double Counter::value() {
    return this->m_value;
}

bool Counter::isProtected() {
    return this->protect;
}

void Incrementer::run() {
    for(auto i = 0; i < this->nLoops; i++){
        std::cout << this->getId() << " Trying to increment counter" << std::endl;
        r_counter.increment();
    }
}
