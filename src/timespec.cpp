#include "timespec.h"
#include <ctime>
#include <time.h>
#include <iostream>

bool XOR(bool a, bool b){
    return ((a && !b) || (!b && a));
}

double timespec_to_ms(const timespec& time_ts) {
    double time_ms = 0;
    time_ms += time_ts.tv_sec * 1000;
    time_ms += time_ts.tv_nsec / 1000000.0;
    return time_ms;
}

timespec timespec_from_ms(double time_ms) {
    timespec time_ts;
    int seconds = time_ms / 1000;
    int nanoseconds = (time_ms - (seconds * 1000)) * 1000000;
    if(seconds < 0) {
        time_ts.tv_sec = seconds - 1;
        time_ts.tv_nsec = 1000000000 + nanoseconds;
        if(time_ts.tv_nsec == 1000000000) {
            time_ts.tv_sec += 1;
            time_ts.tv_nsec = 0;
        }
   } else {
        time_ts.tv_sec = seconds;
        time_ts.tv_nsec = nanoseconds;
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
    out_time_ts.tv_sec = -1 * seconds - 1;
    out_time_ts.tv_nsec = 1000000000 - time_ts.tv_nsec;
    if(out_time_ts.tv_nsec == 1000000000) {
        out_time_ts.tv_sec += 1;
        out_time_ts.tv_nsec = 0;
    }
    return out_time_ts;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts) {
    timespec time_ts;
    int temp = time1_ts.tv_nsec + time2_ts.tv_nsec;
    int division = (int) temp / 1000000000;
    time_ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec + division;
    time_ts.tv_nsec = temp - (1000000000 * division);
    return time_ts;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts){
    timespec time_ts = time2_ts;
    if(XOR(time1_ts.tv_sec < 0, time2_ts.tv_sec < 0)) {
        time_ts = timespec_negate(time2_ts);
    }
    time_ts.tv_sec = time1_ts.tv_sec - time_ts.tv_sec;
    time_ts.tv_nsec = time1_ts.tv_nsec - time_ts.tv_nsec;
    if(time_ts.tv_nsec < 0) {
        time_ts.tv_nsec += 1000000000;
        time_ts.tv_sec -= 1;
    }
    return time_ts; 
}

void timespec_wait(const timespec& delay_ts){
    timespec rem;
    int err = nanosleep(&delay_ts, &rem);
    if(err == -1){
        timespec_wait(rem);
    }
}

timespec operator- (const timespec& time_ts){
    return timespec_negate(time_ts);
}

timespec operator+ (const timespec& time1_ts, const timespec& time2_ts){
    return timespec_add(time1_ts, time2_ts);
}

timespec operator- (const timespec& time1_ts, const timespec& time2_ts){
    return timespec_subtract(time1_ts, time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts){
    time_ts = timespec_add(time_ts, delay_ts);
    return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts){
    time_ts = timespec_subtract(time_ts, delay_ts);
    return time_ts;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts){
    return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts){
    return (time1_ts.tv_sec != time2_ts.tv_sec) || (time1_ts.tv_nsec != time2_ts.tv_nsec);
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts){
    timespec time_ts = time2_ts;
    if(XOR(time1_ts.tv_sec < 0, time2_ts.tv_sec < 0)) {
        time_ts = timespec_negate(time2_ts);
    }
    return (time1_ts.tv_sec < time2_ts.tv_sec) || 
        (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec < time2_ts.tv_nsec);
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts){
    timespec time_ts = time2_ts;
    if(XOR(time1_ts.tv_sec < 0, time2_ts.tv_sec < 0)) {
        time_ts = timespec_negate(time2_ts);
    }
    return (time1_ts.tv_sec > time2_ts.tv_sec) || 
        (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec > time2_ts.tv_nsec);
}
