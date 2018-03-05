#include

typedef enum tag_order_dir{
  DOWN=-1,
  NONE=0,
  UP=1
}order_dir_t

struct order_type{
   order_dir_t dir;
   int floor;
 }

 struct internal_order{
   order_type order;
   bool etasjestopp[4];
   bool valid;
 }

internal_order queue[10];
void queueInit(){
  for(int i=0;i<queue.length();i++){
  queue[i].order.dir=0; queue[i].order.floor=0;queue[i].valid=0;queue[i].etasjestopp=[0,0,0,0];
  }
}
void addExternalOrder(order_type neworder){
  for (int i=0;i<queue.length();i++){
    if (!queue[i].valid){
      queue[i].order=neworder;
      queue[i].etasjestopp[neworder.floor-1]=1;
      queue[i].vaalid=1;
      return;
    }
    if(neworder==queue[i].order){
      return;
    }
    if (neworder.dir==queue[i].order.dir){
      if (neworder.dir==UP && neworder.floor<=queue[i].order.floor &&currentFloor<neworder.floor){
          queue[i].etasjestopp[neworder.floor-1]=1;
          return;
        }
        else if (neworder.dir==DOWN && neworder.floor>=queue[i].order.floor && currentFloor>neworder.floor){
          queue[i].etasjestopp[neworder.floor-1]=1;
          return;
        }
    }
}

void addInternalOrder(int floor){
  if (queue[0].dir==DOWN && floor>=currentFloor) {//assert
    return;
  }
  if (queue[0].dir==UP && floor<=currentFloor){
    return;
  }
  queue[0].etasjestopp[floor-1]=1;
}

bool orderFinished(){
  return (queue[0].etasjestopp==[0,0,0,0]);
}

void removeOrder(int index){
  for (int i=index+1;i<queue.length();i++){
    queue[i-1]=queue[i];
  }
  queue[i].order.dir=NONE; queue[i].order.floor=0;queue[i].valid=0;
}

//void executeOrderfail(){
/* while()
  for (int i=0;i<4;i++){          //evt while;
    if(order[0].etasjestopp[i]){
      break;
    }
    removeOrder();
    i=0;
  }
  if (i+1-currentFloor>0){
    elev_set_motor_direction(1);
  }
  else if(i+1-currentFloor<0){
    elev_set_motor_direction(-1);
  }
  else{
    elev_set_motor_direction(0);
    elev_set_door_open_lamp();
    //start_timer();
    //check_next_stop;
    //runstopproocedure;
  }
  if(etasjestopp[currentFloor-1]){
    elev_set_motor_direction(0);
    //runstopproocedure;
  }
  if(currentFloor==4){
    elev_set_motor_direction(-1);
  }
  if(currentFloor==1){
    elev_set_motor_direction(1);
  }

}*/

void executeOrder(){
  if(queue[0].etasjestopp[currentFloor-1]){
    elev_set_motor_direction(queue[0].order.dir)
  }
  else{
    for (int i=0; i<4;i++){
      if(queue[0].etasjestopp[i]){
        if (i+1>currentFloor){
          elev_set_motor_direction(1);
          break;
        }     //else if
        else{
          elev_set_motor_direction(-1);
          break;
        }
      }
    }
  }
}

void stopElev(
  if(queue[0].etasjestopp[currentFloor-1]){
    elev_set_motor_direction(0);
    elev_set_door_open_lamp(1);
    start_timer();
    queue[0].etasjestopp[currentFloor-1]=0;
    if(queue[0].order.dir==-1){
      elev_set_button_lamp(BUTTON_CALL_DOWN,currentFloor-1,0);
    }
    else if(queue[0].order.dir==1){
      elev_set_button_lamp(BUTTON_CALL_UP,currentFloor-1,0);
    }
    elev_set_button_lamp(BUTTON_COMMAND,currentFloor-1,0);
  }
)
void newOrder(){    //tar utgangspunkt i at kun én knapp trykkes inn om gangen.
  order_type new_order;
  for (int floor=0;floor<4;floor++){
    for (int button=0;button<3;button++){
      if(button_channel_matrix[floor][button]){
        io_set_bit(lamp_channel_matrix[floor][button])
        new_order.floor=floor+1;
        if(button==0){
          new_order.dir=UP;
          addExternalOrder(new_order);
          break;
        }
        else if(button==1){
          new_order.dir=DOWN;
          addExternalOrder(new_order);
          break;
        }else{
          new_order.dir=NONE;
          addInternalOrder(floor);
          break;
        }
      }
    }
  }

}


void optimizeQueue(){ //legg bare til i queue[0]
  for (int i=1;i<queue.length();i++){
    if(queue[0]==queue[i]){
    }
    if (queue[0].order.dir==queue[i].order.dir){
      if (queue[i].order.dir==UP && queue[i].order.floor<=queue[0].order.floor &&currentFloor<queue[i].floor){
                  queue[0].etasjestopp[queue[i].order.floor-1]=1;
          return;
        }
        else if (queue[i].order.dir==DOWN && queue[i].order.floor>=queue[0].order.floor && currentFloor>queue[i].order.floor){
          queue[0].etasjestopp[queue[i].order.floor-1]=1;
          return;
        }
    }
  }
}
