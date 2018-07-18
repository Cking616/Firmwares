#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "bsp/stepmotor.h"
#include "task/distance.h"
#include "task/stepperctrl.h"
#include "utils/uartstdio.h"
#include "TestSlave.h"
#include "task/blinky.h"

int main()
{
    driver_init_hardware();
    setNodeId(&ObjDict_Data, 0x4);
    setState(&ObjDict_Data, Initialisation);     // Init the state
    driver_init_system();

    //UARTprintf("\n\nInit System!\n");
    //UARTprintf("Address:%d!\n", driver_get_address());
    int target_pos = 0;
    //step_motor_set_speed(0, -500, 1750);
    //step_motor_set_speed(1, -500, 1750);
    while(1)
    {
        if(target_pos != step_pos)
        {
            stepperctrl_set_speed(step_speed);
            if(stepperctrl_set_pos(target_pos))
            {
                target_pos = step_pos;
            }
        }
        //distance_thread();
        //Prints out the distance measured.
        //UARTprintf("dis: %2dcm \n" , distance_get_dis());

        //wait about 10ms until the next reading.
        delay_ms(10);
    }
    return 1;
}
