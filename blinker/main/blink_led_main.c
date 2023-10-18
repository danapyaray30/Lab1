#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include <stdio.h>
 #include <ctype.h>
 #include <unistd.h>
 #include <sys/times.h>	// gcc cyclicx.c-o cyclicx						
 #define SLOTX 4
 #define CYCLEX 5  // 5 sec slot time
 #define SLOT_T 5000

 	int tps, cycle=0, slot=0;
 	clock_t now, then;
 	struct tms n;

 	void one() {				// task code
 		printf("task 1 running\n");
		esp_deep_sleep(1000);
 	}
 	void two() {
 		printf("task 2 running\n");
 		esp_deep_sleep(2000);
	}
 	void three() {
 		printf("task 3 running\n");
 		esp_deep_sleep(3000);
	}
	void four() {
 		printf("task 4 running\n");
 		esp_deep_sleep(4000);
 	}
 	void five() {
 		printf("task 5 running\n");
 		esp_deep_sleep(5000);
 	}
 	void burn() {
 		TickType_t bstart = xTaskGetTickCount();
		printf ("%2.2d\n\n", bstart);
		while (((now = xTaskGetTickCount())-then)<SLOT_T*tps/1000) 
 		printf("burn time = %2.2ld\n\n", (times(&n)-bstart)*
 			1000/tps);
 		then = now;
 		cycle = CYCLEX;
 	}
 	void (*ttable[SLOTX][CYCLEX])() = {
 		{one, two, burn, burn, burn},
 		{one, three, burn, burn, burn},
 		{one, four, burn, burn, burn},
 		{burn, burn, burn, burn, burn}
	};

	void app_main () {
		//configTICK_TYPE_WIDTH_IN_bITS() = TICK_TYPE_WIDTH
 		tps = portTICK_RATE_MS;
 		printf("clock ticks/sec = %d\n\n", tps);
		while (1) {
			for(slot=0; slot<SLOTX; slot++)
 			   for(cycle=0; cycle<CYCLEX; cycle++)
	    		      (*ttable[slot][cycle])();  //dispatch next
						        //task from table
		}
 	}