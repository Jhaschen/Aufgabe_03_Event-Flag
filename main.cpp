/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>


DigitalOut led1(LED1); // led port zuweisung
DigitalOut led2(LED2);
DigitalOut led3(LED3);

//------------------------------------------------------------------------------
#define Flag_1 0x1
#define Flag_2 0x2
#define Flag_3 0x3

EventFlags event_flag;






void Task_1(void)
{
    while(1)
    {
    event_flag.set(Flag_1);   
    ThisThread::sleep_for(1000ms);
    event_flag.set(Flag_2);   
    ThisThread::sleep_for(2000ms);
    event_flag.set(Flag_3);   
    ThisThread::sleep_for(3000ms);
    
    }
}

void Task_2(void)
    {

        uint32_t flag_read=0;
    while(1)
        {   
            flag_read=event_flag.wait_any(Flag_1|Flag_2|Flag_3); // 0b00001110  oder 0x07 oder 0x01|0x02|0x03// Warte bis ein Flag gesetzt ist

            switch (flag_read) {
            case Flag_1: led1=!led1; break;
	        case Flag_2: led2=!led2; break;
	        case Flag_3: led3=!led3; break;
	        default: break;
            }
            

           // ThisThread::sleep_for(200ms);
        }    
    }



int main() {
        Thread t_task_1(osPriorityNormal,OS_STACK_SIZE,NULL,NULL);
        t_task_1.start(Task_1);
        
        Thread t_task_2(osPriorityNormal,OS_STACK_SIZE,NULL,NULL);
        t_task_2.start(Task_2);

  
       
        while(true)
        {
           // tue nichts
           ThisThread::sleep_for(2000ms);
        }

        //oder
       // t_task_1.join();
     //t_task_2.join();
       
    }

