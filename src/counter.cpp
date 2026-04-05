#include "counter.h"

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
    Mutex::Lock lock(*this->p_mutex);
    this->m_value += 1.0;
    return this->m_value;
}

double Counter::incrNoProtect() {
    this->m_value += 1.0;
    return this->m_value;
}

double Counter::increment(){
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
        r_counter.increment();
    }
}
