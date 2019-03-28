#include "timer.h"

Timer::Timer()
{
    //ctor
}

Timer::~Timer()
{
    //dtor
}

char* Timer::timers(char* timer)
{
    time_t tt = time(NULL);
    tm* t= localtime(&tt);
    sprintf(timer,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year + 1900,t->tm_mon + 1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    return timer;
}

time_t Timer::timers()
{
	time_t tt=time(NULL);
	return tt;
}
