#include "elev.h"
#include "queue.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_STOP);

    while (1) {
      newOrder();
      if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
          }

      if(elev_get_floor_sensor_signal()>-1){
          printf("ja                 ");
          currentFloor =  elev_get_floor_sensor_signal()+1; //elev_set_floor_indicator()
          }
      if(checkTimerFinished()){
          elev_set_door_open_lamp(0);
          executeOrder();
          }
      //stopElev();
      if(orderFinished()){
          //printf("order finsihed");
          //removeOrder(0);
          //elev_set_motor_direction(queue[0].order.dir);
          }

      }
      printf("currentFloor: %d\n", currentFloor);
      printf("etasjestopp[0]: %d\n", queue[0].etasjestopp[0]);
      printf("etasjestopp[1]: %d\n", queue[0].etasjestopp[1]);
      printf("etasjestopp[2]: %d\n", queue[0].etasjestopp[2]);
      printf("etasjestopp[3]: %d\n", queue[0].etasjestopp[3]);
      printf("order.dir queue[0]: %d\n", queue[0].order.dir);
      printf("order.dir queue[1]: %d\n", queue[1].order.dir);






    return 0;
}
