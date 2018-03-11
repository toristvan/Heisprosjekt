#include "timer.h"

double getTime(void){
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec*.000001;
}


void startTimer(double dur){
	endTime=getTime()+dur;
}

int checkTimerFinished(){
	if(getTime()<endTime){
	return 0;
	}
	return 1;
}
