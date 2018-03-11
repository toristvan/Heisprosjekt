#include "elev.h"
#include "io.h"
#include "channels.h"
#include "timer.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>


double get_time(void);
//global variables:
//endTime used to determine if timer is finished
static double endTime;
//to keep track of current and recent floor
int currentFloor;
//to determine previous direction in case of emergency stop
elev_motor_direction_t prevDir;
//to check if elevator is at floor or in between floors
int floorValid;

//direction of order
typedef enum tag_order_dir{
  DOWN=-1,
  NONE=0,
  UP=1
}order_dir_t;

//order type with direction and floor
struct order_type{
   order_dir_t dir;
   int floor;
 };

//each element in the queue array is an external_order.
 struct external_order{
   struct order_type order;
   int floorstop[4];
   int valid;
 };

//queue array
 struct external_order queue[10];

//deaclaring functions
 double get_time(void);
 void startTimer(double dur);
 int checkTimerFinished();
 int order_typeEqual(struct order_type order_1, struct order_type order_2);
 int external_orderEqual(struct external_order ext_order_1,struct external_order ext_order_2);
 void queueInit();
 void addExternalOrder(struct order_type neworder);
 void addInternalOrder(int floor);
 int orderFinished();
 void removeOrder(int index);
 void executeOrder();
 void stopElev();
 void newOrder();
 void optimizeQueue();
 void print_Orders();
 void emergencyStop();
