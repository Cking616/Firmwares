#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "bsp/sonar.h"
#include "bsp/Bumper.h"
#include "bsp/io.h"
#include "utils/uartstdio.h"



int main()
{
    driver_init_hardware();
    driver_init_system();
    UARTprintf("\n\nInit System!\n");
    UARTprintf("Address:%d!\n", driver_get_address());
    driver_start_tick();

    while(1)
    {
        bumper_print();
        io_manager_test();
        delay_ms(1000);
    }
    return 1;
}
