#include "queue.h"


double get_time(void){
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec + (double)time.tv_usec*.000001;
}
//static int run;
static double endtime;

void startTimer(double dur){
	endtime=get_time()+dur;
}

int checkTimerFinished(){
	if(get_time()<endtime){
	return 0;
	}
	return 1;
}

int orderEqual(struct order_type o1, struct order_type o2){
  if (o1.dir==o2.dir && o1.floor==o2.floor){
    return 1;
  } else{
    return 0;
  }
}

int queueEqual(struct internal_order q1,struct internal_order q2){
  if (orderEqual(q1.order,q2.order) && q1.etasjestopp==q2.etasjestopp){//evt valid.
    return 1;
  } else{
    return 0;
  }
}

void queueInit()
{
  int i=0;
  while(queue[i].valid){
  queue[i].order.dir=0; queue[i].order.floor=0;queue[i].valid=0;memset(queue[i].etasjestopp,0,sizeof(queue[i].etasjestopp));
  i++;
  }
}
void addExternalOrder(struct order_type neworder)
{
  //printf("addexternal \n");
  for (int i=0;i<sizeof(queue);i++){
    if (!queue[i].valid){
      queue[i].order=neworder;
      queue[i].etasjestopp[neworder.floor-1]=1;
      queue[i].valid=1;
      return;
    }
    if(neworder.dir==queue[i].order.dir && neworder.floor==queue[i].order.floor){ //orderEqual(neworder,queue[i])
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
}


void addInternalOrder(int floor) { // fiks dette, vil nå ikke lage ny ordre over, hvis retning ned. Sjekk heis kjører.
  if ((io_read_bit(MOTORDIR)==1 && floor>=currentFloor)&&(queue[0].valid)) {//assert
    return;
  }
  else if ((io_read_bit(MOTORDIR)==0 && floor<=currentFloor)&&(queue[0].valid)){
    return;
  }else{
  		queue[0].etasjestopp[floor-1]=1;
			if(!queue[0].valid){
				queue[0].valid=1;
				queue[0].order.floor=floor;
				if(floor>currentFloor){
					queue[0].order.dir=UP;
				}else if(floor<currentFloor){
					queue[0].order.dir=DOWN;
				}
			}
		}
}

int orderFinished()
{
  return (queue[0].etasjestopp[0]==0 && queue[0].etasjestopp[1]==0 && queue[0].etasjestopp[2]==0 && queue[0].etasjestopp[3]==0);
}

void removeOrder(int index)
{
  int j=0;
  int teller=1;
  if(!queue[1].valid){
    printf("ja");
    queue[j].order.dir=0; queue[j].order.floor=0;queue[j].valid=0;memset(queue[j].etasjestopp,0,sizeof(queue[j].etasjestopp));
  }else{
  while(queue[teller].valid){
    queue[teller-1].order.dir=queue[teller].order.dir;
    queue[teller-1].order.floor=queue[teller].order.floor;
    for (int k=0;k<4;k++){
      queue[teller-1].etasjestopp[k]=queue[teller].etasjestopp[k];
    }
    queue[teller-1].valid=queue[teller].valid;
    j=teller;
		teller++;
  }
  queue[j].order.dir=0; queue[j].order.floor=0;queue[j].valid=0;memset(queue[j].etasjestopp,0,sizeof(queue[j].etasjestopp));
}
}





/*

  for (int i=index+1;i<sizeof(queue);i++){
    queue[i-1].order.dir=queue[i].order.dir;
    queue[i-1].order.floor=queue[i].order.floor;
    for (int j=0;j<4;j++){
      queue[i-1].etasjestopp[j]=queue[i].etasjestopp[j];
    }
    queue[i-1].valid=queue[i].valid;
    j=i;
  }
  }
  queue[j].order.dir=0; queue[j].order.floor=0;queue[j].valid=0;memset(queue[j].etasjestopp,0,sizeof(queue[j].etasjestopp));
}
*/

void executeOrder()
{ 
  //Spesialtilfelle(Når heisen stoppes mellom etasjer)
  if (prevdir!=0)
  {
    for (int i = 0; i <4; ++i)
    {
      if (queue[0].etasjestopp[i])
      {
        if (((currentFloor==1) || (prevdir==-1 && currentFloor==2))&&(i>0))//Mellom 1. og 2. etasje
        {
          elev_set_motor_direction(1);
          printf("Case1; \n");
          return;
        }
        else if (((prevdir==1 && currentFloor==2) || (prevdir==-1 && currentFloor==3))&&(i>1))//Mellom 2. og 3. etasje
        {
          elev_set_motor_direction(1);
          printf("Case2; \n");
          return;
        }
        else if (((currentFloor==4) || (prevdir==1 && currentFloor==3))&&(i>2))//Mellom 3. og 4. etasje
        {
          elev_set_motor_direction(1);
          printf("Case3; \n");
          return;
        }else
        {
        elev_set_motor_direction(-1);
        printf("Case4; \n");
          return;
        }
      }
    }
}
  if(queue[0].etasjestopp[currentFloor-1]==1){ //endre order_dir_t til elev_motor_direction_t
    elev_set_motor_direction(queue[0].order.dir);
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

void stopElev()
{
  if(queue[0].etasjestopp[currentFloor-1]){
    elev_set_motor_direction(0);
    elev_set_door_open_lamp(1);
    startTimer(3);
    queue[0].etasjestopp[currentFloor-1]=0;
    if((queue[0].order.dir==-1&&(currentFloor)>1)){ //evt !=1 for debugging 
      elev_set_button_lamp(BUTTON_CALL_DOWN,currentFloor-1,0);
    }
    else if((queue[0].order.dir==1)&&(currentFloor<4)){    
      elev_set_button_lamp(BUTTON_CALL_UP,currentFloor-1,0);
    }
    elev_set_button_lamp(BUTTON_COMMAND,currentFloor-1,0);
  }
}
void newOrder()
{    //tar utgangspunkt i at kun én knapp trykkes inn om gangen.
  struct order_type new_order;
  for (int floor=0;floor<4;floor++){
    for (elev_button_type_t button=BUTTON_CALL_UP;button<=BUTTON_COMMAND;button++){
      if((button==BUTTON_CALL_DOWN&&floor==0)||(button==BUTTON_CALL_UP&&floor==3)){
        continue;
      }
      if(elev_get_button_signal(button,floor)){
				// printf("floor: %d\n",floor);
        elev_set_button_lamp(button,floor,1); //assert-fail, hvorfor får vi denne?
        new_order.floor=floor+1;
        if(button==0){
          new_order.dir=UP;
          addExternalOrder(new_order);
        }
        else if(button==1){
          new_order.dir=DOWN;
          addExternalOrder(new_order);
        }else{
          new_order.dir=NONE;
          addInternalOrder(new_order.floor);
        }
      }
    }
  }

}


void optimizeQueue()
{ //legg bare til i queue[0]
  for (int i=1;i<sizeof(queue);i++){
    if(queueEqual(queue[0],queue[i])){
      removeOrder(i);
      break;
    }
    if (queue[0].order.dir==queue[i].order.dir){
      if (queue[i].order.dir==UP && queue[i].order.floor<=queue[0].order.floor &&currentFloor<queue[i].order.floor){
          queue[0].etasjestopp[queue[i].order.floor-1]=1;
          removeOrder(i);
          break;
      }
      else if (queue[i].order.dir==DOWN && queue[i].order.floor>=queue[0].order.floor && currentFloor>queue[i].order.floor){
          queue[0].etasjestopp[queue[i].order.floor-1]=1;
          removeOrder(i);
          break;
      }
    }
  }
}

/*void emergencyStop(){
  elev_motor_direction_t prevDir=io_read_bit(MOTORDIR);
  elev_set_stop_lamp(); //fjern stopplys
  elev_set_motor_direction(0);
  queueInit();
  for (int floor=0;floor<4;floor++){
    for (elev_button_type_t button=BUTTON_CALL_UP; button<=BUTTON_COMMAND;button++){
      if((button==BUTTON_CALL_DOWN && floor==0)||(button==BUTTON_CALL_UP && floor==3)){
        continue;
      }
      elev_set_button_lamp(button, floor, 0);
    }
  }
  if(elev_get_floor_sensor_signal()>-1){
    elev_set_door_open_lamp();
  }
}*/
