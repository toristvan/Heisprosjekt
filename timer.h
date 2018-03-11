#include <stdio.h>
#include <sys/time.h>
#include <string.h>

//endTime used to determine if timer is finished
static double endTime;

double getTime(void);
void startTimer(double dur);
int checkTimerFinished();
