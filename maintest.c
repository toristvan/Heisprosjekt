#include "elev.h"
#include "queue.h"
#include <stdio.h>


int main() {
    // Initialize hardware
    if (!elev_init()) { //skrur av alle lysene
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");
    while(elev_get_floor_sensor_signal()!=0){ //initialiserer
      elev_set_motor_direction(DIRN_DOWN);
    }
    elev_set_motor_direction(DIRN_STOP);
    currentFloor=1;
    int temp;
    while (1) {
      temp=elev_get_floor_sensor_signal();
      if(temp>-1){
          //printf("ja                 ");
          currentFloor =  temp+1;
          elev_set_floor_indicator(currentFloor);
          }

      newOrder();
      if (elev_get_stop_signal()) { //endra
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
            elev_init();
            queueInit(); //tror dette funker
            if(elev_get_floor_sensor_signal()!=-1){
              elev_set_door_open_lamp(1);
            }
            while(elev_get_stop_signal()){
              //stanser alt av dynamikk mens knapp holdes inne
            }
            elev_set_door_open_lamp(0);
            elev_set_stop_lamp(0);

            break;
          }

      if(checkTimerFinished()){
          elev_set_door_open_lamp(0);
          executeOrder();
          }
          //denne funker ikke
      if(queue[0].etasjestopp[currentFloor-1] || (io_read_bit(MOTOR)==0 && elev_get_obstruction_signal())){
          printf("currentFloor: %d\n", currentFloor);
          stopElev();
          }
      //stopElev();
      if(orderFinished() && queue[0].valid && checkTimerFinished()){//endret her
          //printf("order finsihed");
          removeOrder(0);
          //elev_set_motor_direction(queue[0].order.dir);
          }

          printf("MOTORDIR %d\n", io_read_bit(MOTORDIR));
      }
      //print valid
      printf("valid %d\n", queue[0].valid);
      printf("currentFloor: %d\n", currentFloor);
      printf("etasjestopp[0]: %d\n", queue[0].etasjestopp[0]);
      printf("etasjestopp[1]: %d\n", queue[0].etasjestopp[1]);
      printf("etasjestopp[2]: %d\n", queue[0].etasjestopp[2]);
      printf("etasjestopp[3]: %d\n", queue[0].etasjestopp[3]);
      printf("order.dir queue[0]: %d\n", queue[0].order.dir);
      printf("order.dir queue[1]: %d\n", queue[1].order.dir);






    return 0;
}
