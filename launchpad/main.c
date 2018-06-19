#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "app/PD4/PD4_task.h"
#include "utils/uartstdio.h"
#include "canfestival.h"
#include "app/PD4/Master.h"
#include "utils/cmdline.h"
#include "app/CMD/cmd_task.h"

int main()
{
    driver_init_hardware();

    driver_init_system();
    driver_start_tick();
    PD4Master_taskInit();

    UARTprintf("\n>");
    while(1)
    {
        cmd_task_period();
        delay_ms(2);
    }
    return 1;
}
