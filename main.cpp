/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>


DigitalOut led1(LED1); // led port zuweisung
DigitalOut led2(D2);
DigitalOut led3(D3);

Mutex counter_mutex; // Mutex angelegen  !!Mutex muss immer an allen stellen der verwendeten Variable stehen.



uint16_t counter = 0; // shared mem

void Task_1(void)
{
    while(1)
    {
    ThisThread::sleep_for(200ms);
    counter_mutex.lock();
    counter++;
    counter_mutex.unlock();
    }
}

void Task_2(void)
    {
    while(1)
        {   
            counter_mutex.lock(); // mutex (counter) für andere Threads sperren
            if(counter % 3 == 0)
            {
                led2 = !led2;
              
            }     
           // ThisThread::sleep_for(5000ms); // thread schläft 5000ms  So nicht ! Alle TASKs warten auf Freigabe des Mutex !!!!
              counter_mutex.unlock(); // mutex freigeben 
            
        }    
    }

void Task_3(void)
    {
    while(1)
        {   
            counter_mutex.lock(); // mutex (counter) für andere Threads sperren
            if(counter % 7 == 0)
            {
                led3 = !led3;
                
            }     
            
             counter_mutex.unlock(); // mutex freigeben 
             
        }    
    }


int main() {
        Thread t_task_1(osPriorityNormal,OS_STACK_SIZE,NULL,NULL);
        t_task_1.start(Task_1);
        
        Thread t_task_2(osPriorityNormal,OS_STACK_SIZE,NULL,NULL);
        t_task_2.start(Task_2);

        Thread t_task_3(osPriorityNormal,OS_STACK_SIZE,NULL,NULL);
        t_task_3.start(Task_3);
        
        
       
        while(true)
        {
           led1 = !led1;
           ThisThread::sleep_for(2000ms);
        }
       
    }

