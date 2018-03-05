
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

internal_order order[10];
void orderInit(internal_order order){
  for(int i=0;i<order.length();i++){
  order[i].order.dir=0; order[i].order.floor=0;order[i].valid=0;order[i].etasjestopp=[0,0,0,0];
  }
}
void addOrder(order_type neworder){
  for (int i=0;i<order.length();i++){
    if (!order[i].valid){
      order[i].order=neworder;
      order[i].etasjestopp[neworder.floor-1]=1;
      order[i].valid=1;
      break;
    }
    if(neworder==order[i].order){
      break;
    }
    if neworder.dir==order[i].order.dir{
      if (neworder.dir==up && neworder.floor<=order[i].order.floor &&currentFloor<neworder.floor){
          order[i].etasjestopp[neworder.floor-1]=1;
          break;
      }
      else if (neworder.dir==down && neworder.floor>=order[i].order.floor && currentFloor>neworder.floor){
          order[i].etasjestopp[neworder.floor-1]=1;
          break;
      }
    }
  }
}

void orderExecuted(){
  if (order[0].etasjestopp==[0,0,0,0]){
    for (int i=1;i<order.length();i++){
      order[i-1]=order[i];
    }
    order[i].order.dir=00; order[i].order.floor=0;order[i].valid=0;
  }
}

void executeOrder(){
  while()
  for (int i=0;i<4;i++){          //evt while;
    if(order[0].etasjestopp[i]){
      break;
    }
    orderExecuted();
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

}
