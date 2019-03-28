#ifndef TIMER_H
#define TIMER_H

#include<time.h>
#include<cstdio>

class Timer
{
    public:
        Timer();
        virtual ~Timer();
        static char* timers(char* timer);
		static time_t timers(void);
    protected:

    private:
};

#endif // TIME_H
