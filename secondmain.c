#include "queue.h"
#include <stdio.h>



int main(){

  if (!elev_init()) {
      printf("Unable to initialize elevator hardware!\n");
      return 1;
  }

  printf("Press STOP button to stop elevator and exit program.\n");

  elev_set_motor_direction(DIRN_UP);

  while(1){

    newOrder();

    if(elev_get_floor_sensor_signal()>-1){
	currentFloor = 	elev_get_floor_sensor_signal()+1;
	//elev_set_floor_indicator()
}

if(orderFinished()){
	removeOrder(0);
	elev_set_motor_direction(queue[0].order.dir);
}
if (elev_get_stop_signal()) {
        elev_set_motor_direction(DIRN_STOP);
	queueInit();

            break;
}
if(checkTimerFinished()){
	elev_set_door_open_lamp(0);
	executeOrder();
}

if(queue[0].etasjestopp[currentFloor-1] || (MOTORDIR == DIRN_STOP && elev_get_obstruction_signal())){
	 stopElev();
}
}
return 0;

}
