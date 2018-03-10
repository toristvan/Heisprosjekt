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
    prevdir=0;
    int temp;
    while (1) {
        //printf("prevdir: %d ", prevdir);
      temp=elev_get_floor_sensor_signal();
      //printf("temp: %d ",temp);
      if(temp>-1){
        //printf("inne i temp \n");
        prevdir=0;
        currentFloor =  temp+1;
        elev_set_floor_indicator(currentFloor-1);
        }


        //printf("startneworder\n");
        newOrder();
        //printf("endneworder\n");
        if (elev_get_stop_signal()) { //endra
            printf("----------\n");
            elev_set_stop_lamp(1);
            if(elev_get_floor_sensor_signal()==-1){ // setter tilstand(3 tilstander)
                //printf(" i if1 \n");
                //printf(" MOTORDIR: %d\n", io_read_bit(MOTORDIR));
                if(io_read_bit(MOTORDIR)==0){
                    //printf(" i if2 \n");
                    prevdir=1;
                }else{
                    //printf(" i else2 \n");
                    prevdir=-1;
                }
            }
            //printf(" forbi if\n");
            //printf("prevdir: %d \n", prevdir);
            elev_set_motor_direction(DIRN_STOP);
            elev_init();
            queueInit(); //denne funker ikke!!!//Fiksa 08.03
            if(elev_get_floor_sensor_signal()!=-1){
            elev_set_door_open_lamp(1);
            }
            while(elev_get_stop_signal()){
            //stanser alt av dynamikk mens knapp holdes inne
            }
            elev_set_door_open_lamp(0);
            elev_set_stop_lamp(0);
            //printf("-------------- \n");
            //printf("prevdir2: %d \n", prevdir);

        }

        if(checkTimerFinished()){
            elev_set_door_open_lamp(0);
            //printf(" executeOrder\n");
            executeOrder();
        }
           //denne funker ikke
        if((queue[0].etasjestopp[currentFloor-1])&&(prevdir==0)){   // || (elev_get_obstruction_signal())
            //printf("currentFloor: %d\n", currentFloor);
            //printf("prevdir i stopp: %d \n", prevdir);
            printf("stopElevstart\n");
            stopElev();
            printf("stopElevEnd\n");
            printf("etasjestopp[0] %d\n", queue[0].etasjestopp[0]);
        }
        
        if(orderFinished() && queue[0].valid && checkTimerFinished()){//endret her
            //printf("order finsihed");
            printf("removeOrder");
            removeOrder(0);
            //printf("startOptimizequeue: \n");
            //optimizeQueue();
            //printf("endOptimizequeue: \n");
            //elev_set_motor_direction(queue[0].order.dir);
          }

            //printf("MOTORDIR %d\n", io_read_bit(MOTORDIR));
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


/*
Dette må fikses(08.03):
1. Intern bestillingsknapp når det ikke er lagt inn eksterne ordre
2. NED fra fjerde, Heis går opp, Trykker opp fra første, Trykker ned fra andre,
- Stopper ikke i andre på vei ned. Dette er kind off meningen, men ikke ideellt
3. Emergency stop. Dersom heis stopper mellom etasjer klarer den ikke gå
til den etasjen den var i sist. Må bruke en temp-variabel for å fortelle om vi er på oversiden eller undersiden.
4. Se på globale variabler
*/
