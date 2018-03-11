#include "elev.h"
#include "io.h"
#include "channels.h"
#include "timer.h"
#include "eventmanager.h"
#include <stdio.h>
#include <string.h>

//direction of order
//we chose not to use elev_motor_direction_t here because we believe it is more accurate
//that an order direction is different than a motor direction,
//especially since order_dir_t=0 means no specific direction, and
//elev_motor_direction_t=0 means stop.
//Has equal values, so we can use them in place of each other.
//gives warning in code, but will not lead to error.
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


//declaring functions
 int order_typeEqual(struct order_type order_1, struct order_type order_2);
 int external_orderEqual(struct external_order ext_order_1,struct external_order ext_order_2);
 void queueInit();
 void addExternalOrder(struct order_type neworder);
 void addInternalOrder(int floor);
 int orderFinished();
 void removeOrder(int index);
 void newOrder();
 void optimizeQueue();
