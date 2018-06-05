#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp/driver.h"
#include "bsp/delay.h"
#include "bsp/sonar.h"
#include "bsp/Bumper.h"
#include "bsp/io.h"
#include "utils/uartstdio.h"
#include "PG2Slave.h"
#include "canfestival.h"

volatile int nodeId = 0x21;

int main()
{
    driver_init_hardware();
    driver_init_system();
    UARTprintf("\n\nInit System!\n");
    UARTprintf("Address:%d!\n", driver_get_address());

	setNodeId(&TestSlave_Data, nodeId);
	setState(&TestSlave_Data, Initialisation);     // Init the state
    driver_start_tick();

    while(1)
    {
		bumper_process();
        delay_ms(5);
    }
    return 1;
}
