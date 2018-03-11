#include "eventmanager.h"
#include "queue.h"

void updateFloor(){
  floorValid=elev_get_floor_sensor_signal();
  if(floorValid>-1){
    prevDir=DIRN_STOP;
    currentFloor =  floorValid+1;
    elev_set_floor_indicator(currentFloor-1);
  }
}

void executeOrder(){
  //Special case when emergency stop is activated in between floors
  if (prevDir!=DIRN_STOP){
    for (int i = 0; i <4; ++i){
      if (queue[0].floorstop[i]){
        if (((currentFloor==1) || (prevDir==DIRN_DOWN && currentFloor==2))&&(i>0)){ //between 1st and 2nd floor.
          elev_set_motor_direction(DIRN_UP);
          return;
        }else if (((prevDir==DIRN_UP && currentFloor==2) || (prevDir==DIRN_DOWN && currentFloor==3))&&(i>1)){//between 2nd and 3rd floor.
          elev_set_motor_direction(DIRN_UP);
          return;
        }else if (((currentFloor==4) || (prevDir==DIRN_UP && currentFloor==3))&&(i>2)){//between 3rd and 4th floor.
          elev_set_motor_direction(DIRN_UP);
          return;
        }else{
        elev_set_motor_direction(DIRN_DOWN);
          return;
        }
      }
    }
	}//special case end
  if(queue[0].floorstop[currentFloor-1]==1){
    elev_set_motor_direction(queue[0].order.dir);//warning: order_dir_t til elev_motor_direction_t. Works because equal values.
  }else{
    for (int i=0; i<4;i++){
      if (queue[0].floorstop[i]){
        if (i+1>currentFloor){
          elev_set_motor_direction(DIRN_UP);
          break;
        }else{
          elev_set_motor_direction(DIRN_DOWN);
          break;
        }
      }
    }
  }
}

void stopElev(){
  elev_set_motor_direction(DIRN_STOP);
  elev_set_door_open_lamp(1);
  startTimer(3);
  queue[0].floorstop[currentFloor-1]=0;
  if((queue[0].order.dir==-1&&(currentFloor)>1)){
    elev_set_button_lamp(BUTTON_CALL_DOWN,currentFloor-1,0);
  }else if((queue[0].order.dir==1)&&(currentFloor<4)){
    elev_set_button_lamp(BUTTON_CALL_UP,currentFloor-1,0);
  }
  elev_set_button_lamp(BUTTON_COMMAND,currentFloor-1,0);
}

void emergencyStop(){
	printf("--EMERGENCY STOP--\n");
	elev_set_stop_lamp(1);
	if((elev_get_floor_sensor_signal()==-1) && (prevDir==DIRN_STOP)){
  	if(io_read_bit(MOTORDIR)==0){
    	prevDir=DIRN_UP;
  	}else{
    	prevDir=DIRN_DOWN;
  	}
	}
	elev_set_motor_direction(DIRN_STOP);
	elev_init();
	queueInit();
	if(elev_get_floor_sensor_signal()!=-1){
  	elev_set_door_open_lamp(1);
	}
	while(elev_get_stop_signal()){
		//stanser alt av dynamikk mens knapp holdes inne
	}
	elev_set_door_open_lamp(0);
	elev_set_stop_lamp(0);
	elev_set_floor_indicator(currentFloor-1);
}
