class TimeoutException 
{
public:
    const long timeout_ms;
    TimeoutException(long timeout_ms);
};