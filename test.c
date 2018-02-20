// Erlend tester

//Statemachine

// Må håndtere innkommende event: ORDER_PRESSED, STOP_PRESSED, NEW_DESTINATION, DESTINATION_REACHED
// Events kommer fra kontoll-manager
// Må sende ut en action som skal gjennomføres basert på innkommende event 
// EM bruker funskjoner til å finne ut hvilken av eventene den skal kalle på. Den kaller på det med FSM sin currentstate. Switch inni switch. 


enum States{Idle, CheckNext, MoveUp, Movedown, TempStop, Doorclose};
States Currentstate = Idle;

while(1){
switch(Currentstate) {

   case Idle :
      if(){ //boolsk funksjon som returnerer om det er bestillinger i køen
		Currentstate
	}
      break; /* optional */
	
   case CheckNext  :
      statement(s);
      break; /* optional */

   case MoveUp  :
      statement(s);
      break; /* optional */

   case Movedown  :
      statement(s);
      break; /* optional */

   case TempStop  :
      statement(s);
      break; /* optional */

   case Doorclose  :
      statement(s);
      break; /* optional */
  
   /* you can have any number of case statements */
   default : /* Optional */
   statement(s);
	}
}

//TIMER

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

// TIMER END 




