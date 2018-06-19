#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "bsp/stepmotor.h"
#include "task/distance.h"

#include "utils/uartstdio.h"


int main()
{
    driver_init_hardware();

    driver_init_system();

    UARTprintf("\n\nInit System!\n");
    UARTprintf("Address:%d!\n", driver_get_address());

    while(1)
    {
        distance_thread();

        //Prints out the distance measured.
        //UARTprintf("dis: %2dcm \n" , distance_get_dis());

        //wait about 10ms until the next reading.
        delay_ms(10);
    }
    return 1;
}
