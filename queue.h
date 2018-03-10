#include "elev.h"
#include "io.h"
#include "channels.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>


double get_time(void);

int currentFloor;
int prevdir;
typedef enum tag_order_dir{
  DOWN=-1,
  NONE=0,
  UP=1
}order_dir_t;

struct order_type{ //typedef struct
   order_dir_t dir;
   int floor;
 };

 struct internal_order{
   struct order_type order;
   int etasjestopp[4];
   int valid;
 };

 struct internal_order queue[10];

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
