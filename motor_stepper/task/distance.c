/*
 * distance.c
 *
 *  Created on: 2018Äê5ÔÂ15ÈÕ
 *      Author: cking
 */

#include "../bsp/sonar.h"

// unit: cm
int cur_dis = 300;


void distance_thread(void)
{
    //Checks if a pulse read is in progress
    if(sonar_get_echo_wait() != 1){
      //Does the required pulse of 10uS
       sonar_send_pulse();

      /*
        This makes the code wait for a reading to finish
        You can omit this part if you want the code to be non-blocking but
        reading is only ready when echowait=0.
      */
      while(sonar_get_echo_wait() != 0);

      //Converts the counter value to cm.
      cur_dis = sonar_get_dis();
    }
}

int distance_get_dis(void)
{
    return cur_dis;
}
