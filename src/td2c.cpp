#include<iostream>
#include<iomanip>
#include<string>
#include "looper.h"
#include "chrono.h"
#include "timespec.h"

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cout << "Need one and only one argument representing nLoops!" << std::endl;
        return 1;
    }
    double nLoops = std::stod(argv[1]);
    Looper looper = Looper();
    Chrono chrono = Chrono();
    looper.runLoop(nLoops);
    timespec execTime = chrono.stop();
    double execTimeSec = timespec_to_ms(execTime) / 1000;
    std::cout << std::fixed << nLoops << "," << std::setprecision(2) << execTimeSec << std::endl;
    return 0;
}
