#include "timer.h"
double get_time(void){
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec*.000001;
}
static bool run;
static double endtime;

void startTimer(double dur){
	endtime=get_time()+dur;
}

bool checkTimerFinished(){
	if(get_time()<endtime){
	return false;
	}
	return true;
}
