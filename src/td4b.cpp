#include "semaphore.h"
#include "thread.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

class TokenProducer : public Thread {
    private:
        int nToken;
        std::shared_ptr<Semaphore> semaphore;
        void run() override;

    public:
        int producedToken;
        TokenProducer(int id, int nToken, std::shared_ptr<Semaphore> semaphore) : 
            Thread(id), nToken(nToken), semaphore(semaphore) {
                producedToken = 0;
            };
};

void TokenProducer::run() {
    for(int i = 0; i < nToken; i++) {
        //std::cout << "Thread " << id << " generating one token" << std::endl;
        semaphore->give();
        producedToken++;
    }
}

class TokenConsummer : public Thread {
    private:
        std::shared_ptr<Semaphore> semaphore;
        void run() override;

    public:
        int consummedToken;
        TokenConsummer(int id, std::shared_ptr<Semaphore> semaphore) :
            Thread(id), semaphore(semaphore) {
            consummedToken=0;
        };
};

void TokenConsummer::run() {
    bool b;
    do {
        b = semaphore->take(500);
        if(b) {
            //std::cout << "Thread " << id << " consumming one token" << std::endl;
            consummedToken++;
        }
    }
    while(b);
}

int main(int argc, char** argv){
    if(argc != 4) {
        std::cout << "Missing mandatory parameters" << std::endl;
        return 1;
    }
    int nOfConsummers = atoi(argv[1]);
    int nOfProducers = atoi(argv[2]);
    int nToken = atoi(argv[3]);
    std::vector<std::unique_ptr<TokenConsummer>> consummers;
    std::vector<std::unique_ptr<TokenProducer>> producers;
    std::shared_ptr<Semaphore> semaphore = std::make_shared<Semaphore>();
    for(int i = 0; i < nOfConsummers; i++) {
        consummers.push_back(std::make_unique<TokenConsummer>(i, semaphore));
    }
    for(int i = 0; i < nOfProducers; i++) {
        producers.push_back(std::make_unique<TokenProducer>(i+nOfConsummers, nToken, semaphore));
    }
    for(int i = 0; i < nOfConsummers; i++) {
        consummers[i]->start();
    }
    for(int i = 0; i < nOfProducers; i++) {
        producers[i]->start();
    }    
    for(int i = 0; i < nOfConsummers; i++) {
        consummers[i]->join();
    }
    for(int i = 0; i < nOfProducers; i++) {
        producers[i]->join();
    }    
    for(int i = 0; i < nOfConsummers; i++) {
        std::cout << "Thread " << i << " consummed: " << consummers[i]->consummedToken << std::endl;
    }
    for(int i = 0; i < nOfProducers; i++) {
        std::cout << "Thread " << i << " produced: " << producers[i]->producedToken << std::endl;
    }    
    return 0;
}
