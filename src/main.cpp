#include "timer.h"
#include "looper.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "nLoops argument missing" << std::endl;
    }
    double nLoops = (double) atoi(argv[1]);
    Looper loop;
};
