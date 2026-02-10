#include "timer.h"

int main(){
    CountDown jorge = CountDown(15);
    jorge.start({1, 0}, true);
    while(jorge.get_counter()>=0);
    return 0;
}
