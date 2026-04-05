#include<pthread.h>
#include<iostream>

struct Data {
    Data();
    volatile bool stop;
    volatile double counter;
    pthread_mutex_t mutex;
};

Data::Data(){
    this->stop = false;
    this->counter = 0.0;
    pthread_mutex_init(&this->mutex, nullptr);
}

void * incrementer(void* v_data) {
    Data* p_data = (Data*) v_data;
    while(not p_data->stop) {
        pthread_mutex_lock(&p_data->mutex);
        p_data->counter += 1.0;
        pthread_mutex_unlock(&p_data->mutex);
    }
    return v_data;
}

int main(){
    Data data = Data();
    pthread_t incrementThread[3];
    pthread_create(&incrementThread[0], nullptr, incrementer, (void*) &data);
    pthread_create(&incrementThread[1], nullptr, incrementer, (void*) &data);
    pthread_create(&incrementThread[2], nullptr, incrementer, (void*) &data);
    for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
        std::cout << "Type 's' to stop: " << std::flush;
    data.stop = true;
    std::cout << "Counter value = " << std::fixed << data.counter << std::endl;
    pthread_join(incrementThread[0], nullptr);
    pthread_join(incrementThread[1], nullptr);
    pthread_join(incrementThread[2], nullptr);
    pthread_mutex_destroy(&data.mutex);
    return 0;
}
