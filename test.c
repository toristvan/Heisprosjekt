void print_Orders(){
	int i=0;
	printf("Orders:\n");
	while(queue[i].valid){
  	printf("Queue[i]: i=%d\n", i);
  	printf("valid: %d\n", queue[i].valid);
  	printf("Order_Floor: %d\n", queue[i].order.floor);
  	printf("Order.dir: %d\n", queue[i].order.dir);
  	printf("floorstop[0]: %d\n", queue[i].floorstop[0]);
  	printf("floorstop[1]: %d\n", queue[i].floorstop[1]);
  	printf("floorstop[2]: %d\n", queue[i].floorstop[2]);
  	printf("floorstop[3]: %d\n", queue[i].floorstop[3]);
  	printf("\n");
  	i++;
	}
}
