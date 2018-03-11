//#include "elev.h"
#include "queue.h"
//#include <stdio.h>


int main() {
    // Initialize hardware.
    //Turn off all lights.
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    printf("Press STOP button to stop elevator and exit program.\n");
    while(elev_get_floor_sensor_signal()!=0){
      elev_set_motor_direction(DIRN_DOWN);
    }
    elev_set_motor_direction(DIRN_STOP);
    //initializing variables.
    currentFloor=1;
    prevDir=DIRN_STOP;
    //The main elevetaor sequence begins here.
    while (1) {
        //contionously updating currentFloor and floor indicators.
      floorValid=elev_get_floor_sensor_signal();
      if(floorValid>-1){
        prevDir=DIRN_STOP;
        currentFloor =  floorValid+1;
        elev_set_floor_indicator(currentFloor-1);
        }

        //checking for pressed buttons, adding orders to queue and optimizing queue.
        newOrder();
        optimizeQueue();

        //handling emergency stop button pressed.
        if (elev_get_stop_signal()) {
            emergencyStop();
        }

        //checking if timer set by stopping at floor is finished.
        if(checkTimerFinished()){
            elev_set_door_open_lamp(0);
            executeOrder();
        }
        //stopping elevator when ordered floor is reached, and reactivates in case of obstruction.
        if((queue[0].floorstop[currentFloor-1] && prevDir==DIRN_STOP)
            ||(elev_get_obstruction_signal() && !checkTimerFinished())){
            stopElev();
            optimizeQueue();
        }
        //checking if timer and order is finished. If so removes order and optimizes queue.
        if(orderFinished() && queue[0].valid && checkTimerFinished()){
            removeOrder(0);
            optimizeQueue();
          }
    }
    return 0;
}
