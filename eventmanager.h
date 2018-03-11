#include "elev.h"

//global variables:
//to keep track of current and recent floor
int currentFloor;
//to determine previous direction in case of emergency stop
elev_motor_direction_t prevDir;
//to check if elevator is at floor or in between floors
int floorValid;

//declaring functions
void updateFloor();
void executeOrder();
void stopElev();
void emergencyStop();
