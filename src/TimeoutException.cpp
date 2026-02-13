#include "TimeoutException.h"
#include "TimespecOps.h"

TimeoutException::TimeoutException(long timeout_ms) : timeout_ms(timeout_ms)
{

}
