/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include "../include/duck_thread_one.h"
#include "../include/duck_thread_two.h"
#include "../include/duck_thread_three.h"
#include "../include/main.h"

// Blinky example was used as the base of the project - Ed

#define MY_STACK_SIZE 500

//define the semaphore
struct k_sem duck_sem;

//define the thread
struct k_thread main_thread;

//setting stack size
K_THREAD_STACK_DEFINE(main_stack, MY_STACK_SIZE);

int order_count = 0;


//callback function that the threads use
void thread_complete() {
	//update order count to signifiy that the next thread can go
	order_count++;
	k_sem_give(&duck_sem);
}


//code for the main thread
void main_thread_start(void) {
	while (1) {	
		
		//check to see if the semaphore is empty
		if (order_count == 3) {
			//resets the count so the threads can start again
			order_count = 0;
		}
	}

}


int main(void)
{	

	//init semphore 
	k_sem_init(&duck_sem, 0, 1);

	k_tid_t my_tid = k_thread_create(&main_thread, main_stack, K_THREAD_STACK_SIZEOF(main_stack),main_thread_start,NULL, NULL, NULL, 5, 0, K_NO_WAIT);
	
	//init threads with callbacks
	init_duck_thread_one(thread_complete);
	init_duck_thread_two(thread_complete);
	init_duck_thread_three(thread_complete);

	while(1) {

	}

	return 0;
}
