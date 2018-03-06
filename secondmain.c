#include "queue.h"
#include <stdio.h>



int main(){

elev_init();

while(1){

newOrder();

if(elev_get_floor_sensor_signal()>-1){
	currentFloor = 	elev_get_floor_sensor_signal()+1;
	//elev_set_floor_indicator()
}
	
if(orderfinished()){ 
	remove_order();
	elev_set_motor_direction(queue[0].order.dir);
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

if(queue[0].etasjestopp[currentFloor-1] || (MOTORDIR == DIRN_STOP && elev_get_obstruction_signal())){
	 stopElev();
	}
}
return 0;

}
}
