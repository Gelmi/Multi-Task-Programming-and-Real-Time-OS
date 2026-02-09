#include "timespec.h"
#include <ctime>
#include <iostream>

double timespec_to_ms(const timespec& time_ts) {
    double time_ms = 0;
    time_ms += time_ts.tv_sec * 1000000;
    time_ms += time_ts.tv_nsec / 1000.0;
    return time_ms;
}

timespec timespec_from_ms(double time_ms) {
    timespec time_ts;
    int seconds = time_ms / 1000000;
    int milliseconds = (time_ms - (seconds * 1000000)) * 1000;
    if(seconds < 0) {
        time_ts.tv_sec = seconds - 1;
        time_ts.tv_nsec = 1000000000 + milliseconds;
        if(time_ts.tv_nsec == 1000000000) {
            time_ts.tv_sec += 1;
            time_ts.tv_nsec = 0;
        }
   } else {
        time_ts.tv_sec = seconds;
        time_ts.tv_nsec = milliseconds;
    }
    return time_ts;
}

timespec timespec_now(){
    timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);
    return abstime;
}

timespec timespec_negate(const timespec& time_ts){
    timespec out_time_ts;
    int seconds = time_ts.tv_sec;
    out_time_ts.tv_sec = -1 * seconds;
    out_time_ts.tv_nsec = 1000000000 - time_ts.tv_nsec;
    if(out_time_ts.tv_nsec == 1000000000) {
        out_time_ts.tv_sec += 1;
        out_time_ts.tv_nsec = 0;
    }
    return out_time_ts;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts) {
    timespec time_ts;
    time_ts.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    time_ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec + (time_ts.tv_nsec % 1000000000);
    time_ts.tv_nsec = time_ts.tv_nsec - (1000000000 * (time_ts.tv_nsec % 1000000000));
    return time_ts;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts){
    timespec time_ts;
    return time_ts;
};
