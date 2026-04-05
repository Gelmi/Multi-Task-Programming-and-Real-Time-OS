#include "monitor.h"

int main(){
    Mutex m = Mutex();
    Monitor mon = Monitor(m);
    return 0;
}

