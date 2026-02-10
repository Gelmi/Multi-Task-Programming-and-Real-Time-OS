#include "TimespecOps.h"

double TimespecOps::timespec_to_ms(const timespec& time_ts)
{
    double time_ms = time_ts.tv_sec*1000;
    time_ms = time_ms + time_ts.tv_nsec/1000000;
    return time_ms;
}

timespec TimespecOps::timespec_from_ms(double time_ms)
{
    timespec time_ts;
    if(time_ms < 0)
    {
        time_ts.tv_sec = (time_ms/1000)-1;
        time_ts.tv_nsec = -((time_ts.tv_sec*1000) - time_ms)*1000000;
        if(time_ts.tv_nsec == 1000000000)
        {
            time_ts.tv_sec = time_ts.tv_sec +1;
            time_ts.tv_nsec = 0;
        }
    }
    else
    {
        time_ts.tv_sec = (time_ms/1000);
        time_ts.tv_nsec = (time_ms - (time_ts.tv_sec*1000))*1000000;
    }
    return time_ts;
}

timespec TimespecOps::timespec_now() 
{
    timespec time_ts;
    timespec_get(&time_ts, TIME_UTC);
    return time_ts;
}

timespec TimespecOps::timespec_negate(const timespec& time_ts)
{
    timespec neg_time;
    neg_time.tv_sec = -(time_ts.tv_sec+1);
    neg_time.tv_nsec = 1000000000-time_ts.tv_nsec;
    if(time_ts.tv_nsec == 0)
    {
        neg_time.tv_sec += 1;
        neg_time.tv_nsec = 0;

    }
    return neg_time;
}

timespec TimespecOps::timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec result;
    result.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    result.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    if(result.tv_nsec >= 1000000000)
    {
        result.tv_nsec -= 1000000000;
        result.tv_sec += 1;
    }
    return result;
}

timespec TimespecOps::timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec result;
    timespec neg_value = timespec_negate(time2_ts);
    result.tv_sec = time1_ts.tv_sec + neg_value.tv_sec;
    result.tv_nsec = time1_ts.tv_nsec + neg_value.tv_nsec;
    if(result.tv_nsec >= 1000000000)
    {
        result.tv_nsec = 0;
        result.tv_sec += 1;
    }
    return result;
}

void TimespecOps::timespec_wait(const timespec& delay_ts)
{
    nanosleep(&delay_ts, nullptr);
}

timespec  operator- (const timespec& time_ts)
{
    return TimespecOps::timespec_negate(time_ts);
}
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
    return TimespecOps::timespec_add(time1_ts, time2_ts);
}
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
    return TimespecOps::timespec_subtract(time1_ts, time2_ts);
}
timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
    time_ts = TimespecOps::timespec_add(time_ts, delay_ts);
    return time_ts;
}
timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
    time_ts = TimespecOps::timespec_subtract(time_ts, delay_ts);
    return time_ts;
}
bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
    return time1_ts.tv_sec==time2_ts.tv_sec && time1_ts.tv_nsec==time2_ts.tv_nsec;
}
bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
    return !(time1_ts.tv_sec==time2_ts.tv_sec && time1_ts.tv_nsec==time2_ts.tv_nsec);
}
bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
    return TimespecOps::timespec_to_ms(time1_ts) < TimespecOps::timespec_to_ms(time2_ts);
}
bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
    return TimespecOps::timespec_to_ms(time1_ts) > TimespecOps::timespec_to_ms(time2_ts);
}