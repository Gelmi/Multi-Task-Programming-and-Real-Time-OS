#include<iostream>
#include<vector>
#include "counter.h"
#include "chrono.h"
#include "timespec.h"

int parsePolicy(const char* str) {
    std::string s(str);
    if(s == "SCHED_RR")    return SCHED_RR;
    if(s == "SCHED_FIFO")  return SCHED_FIFO;
    if(s == "SCHED_OTHER") return SCHED_OTHER;
    // fallback: try to parse as integer
    return atoi(str);
}

int main(int argc, char** argv){
    if(argc < 3) {
        std::cout << "Missing mandatory parameters" << std::endl;
        return 1;
    }
    double nLoops = atof(argv[1]);
    int nTasks = atoi(argv[2]);
    bool protect = false;
    int policy;
    if(argc > 3) {
        protect = atoi(argv[3]);
    }
    if(argc > 4) {
        policy = parsePolicy(argv[4]);
        Thread::setMainSched(policy);
    } 
    auto counter = std::make_unique<Counter>(protect);
    std::vector<std::unique_ptr<Incrementer>> incrementors;
    auto chrono = std::make_unique<Chrono>();
    for(auto i = 0; i < nTasks; i++){
        incrementors.push_back(std::make_unique<Incrementer>(i, *counter, nLoops));
        incrementors[i]->start();
    }
    for(auto i = 0; i < nTasks; i++){
        incrementors[i]->join();
    }
    double time = timespec_to_ms(chrono->stop());
    std::cout << "Expected: " << nLoops * nTasks << " Got: " << counter->value() << std::endl; 
    std::cout << "Main execution time: " << time << std::endl;
    for(auto i = 0; i < nTasks; i++){
        std::cout << "Thread " << i << " execution time: " << incrementors[i]->duration_ms() << std::endl;
    }
    return 0;
}
