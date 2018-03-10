#include "elev.h"
#include "io.h"
#include "channels.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>


double get_time(void);
//global variables:
//endtime used to determine if timer is finished
static double endtime;
//to keep track of current and recent floor
int currentFloor;
//to determine previous direction in case of emergency stop
int prevdir;
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

//each element in the queue array is an internal_order.
 struct internal_order{
   struct order_type order;
   int etasjestopp[4];
   int valid;
 };

//queue array
 struct internal_order queue[10];

//deaclaring functions
 double get_time(void);
 void startTimer(double dur);
 int checkTimerFinished();
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
