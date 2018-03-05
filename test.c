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
main(){

elev_Init();

while(1){

if(elev_get_button_signal()){
	new_order();
}
if(elev_get_floor_sensor_signal()>-1){
	currentfloor = 	elev_get_floor_sensor_signal()+1;
	elev_set_floor_indicator()
}
	
if(orderfinished()){ 
	remove_order();
	elev_set_motor_direction(Queue[0].dir);
}
if (elev_get_stop_signal()) {
        elev_set_motor_direction(DIRN_STOP);
	queueInit();
	   
            break;
}
if(checktimer()){
	elev_set_door_open_lamp(0);
	executeorder();
}

if(Queue[0].etasjestopp[currentfloor-1] || (MOTORDIR == DIRN_STOP && elev_get_obstruction_signal())){
	 stopElev();
	}
}





