#include "elev.h"
#include <stdio.h>



int main(){

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


}
