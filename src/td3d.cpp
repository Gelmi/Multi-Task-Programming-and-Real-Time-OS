#include<iostream>
#include<vector>
#include "counter.h"

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
        policy = atoi(argv[4]);
    } 
    auto counter = std::make_unique<Counter>(protect);
    std::vector<std::unique_ptr<Incrementer>> incrementors;
    for(auto i = 0; i < nTasks; i++){
        std::cout << "Tentando criar tarefa " << i << std::endl;
        incrementors.push_back(std::make_unique<Incrementer>(i, (Counter&) counter, nLoops));
        std::cout << "Criei tarefa " << i << std::endl;
        incrementors[i]->start();
        std::cout << "Startei tarefa " << i << std::endl;
    }
    for(auto i = 0; i < nTasks; i++){
        incrementors[i]->join();
    }
    std::cout << "Expected: " << nLoops * nTasks << " Got: " << counter->value() << std::endl;
    return 0;
}
