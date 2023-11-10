

#include <zephyr/kernel.h>
#include <zephyr/device.h> 

#include "../include/duck_thread_two.h"
#include "../include/main.h"

#define MY_STACK_SIZE 500

//get semaphore and order count 
extern struct k_sem duck_sem;
extern int order_count;

//defining thread
struct k_thread duck_thread_two;

//setting stack size
K_THREAD_STACK_DEFINE(duck_stack_two, MY_STACK_SIZE);

//setting up callback
static void (*callback)(void);


void duck_two_start(void) {
	while(1) {
		//take semaphore and check if it is your turn
		k_sem_take(&duck_sem, K_FOREVER)
		
		if (order_count == 1) {
			//duck 2 turn
			//wait 2 to 3 seconds	
			int delay = 2000 + (sys_rand32_get() % 1000);
			k_msleep(delay);
			printf("duck\n");

			callback();
		} else {
			//if not, give it back
			k_sem_give(&duck_sem);
		}

	}
}


//starting function for thread
void init_duck_thread_two(void (*callback_func)(void)) {
	
	callback = callback_func;

	//create thread
	k_tid_t my_tid = k_thread_create(&duck_thread_two, duck_stack_two, K_THREAD_STACK_SIZEOF(duck_stack_two),duck_two_start, NULL, NULL, NULL, 5, 0, K_NO_WAIT);



}
