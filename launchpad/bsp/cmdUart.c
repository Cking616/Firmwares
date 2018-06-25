/*
 * cmdUart.c
 *
 *  Created on: 2018/5/31
 *      Author: cking
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "inc/hw_ints.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "cmdUart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

char g_cmd_uart_fifo[12];
char _start_flag = 0;
char _cur_pos = 0;
char _len = 0;

extern xQueueHandle g_cmd_Queue;
//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void cmd_uart_init_handler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = MAP_UARTIntStatus(UART3_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    MAP_UARTIntClear(UART3_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(MAP_UARTCharsAvail(UART3_BASE))
    {
        char _temp;
        _temp = UARTCharGetNonBlocking(UART3_BASE);
        if(_start_flag)
        {
			if (_cur_pos == 0)
			{
				_len = _temp;
				g_cmd_uart_fifo[_cur_pos] = _temp;
				_cur_pos++;
				if (_len > 12)
				{
					_len = 0;
					_cur_pos = 0;
					_start_flag = 0;
				}
			}
			else
			{
				g_cmd_uart_fifo[_cur_pos] = _temp;
				_cur_pos++;
				if (_cur_pos == _len)
				{
					_len = 0;
					_cur_pos = 0;
					_start_flag = 0;
					xQueueSendToFrontFromISR(g_cmd_Queue, (void*)g_cmd_uart_fifo, NULL);
				}
			}
        }
		else
		{
			if (_temp == '#')
			{
				_start_flag = 1;
			}
		}
    }
}

void cmd_uart_send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
	taskDISABLE_INTERRUPTS();
    MAP_UARTCharPutNonBlocking(UART3_BASE, '#');
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //

        MAP_UARTCharPutNonBlocking(UART3_BASE, *pui8Buffer++);
    }
	taskENABLE_INTERRUPTS();
}

void cmd_uart_init(void)
{
    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);

    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    MAP_GPIOPinConfigure(GPIO_PC6_U3RX);
    MAP_GPIOPinConfigure(GPIO_PC7_U3TX);
    MAP_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    UARTFIFOEnable(UART3_BASE);
    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    MAP_UARTConfigSetExpClk(UART3_BASE, MAP_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    UARTIntRegister(UART3_BASE, cmd_uart_init_handler);
    //
    // Enable the UART interrupt.
    //
    IntPrioritySet(INT_UART3, 0xD0);
    MAP_IntEnable(INT_UART3);
    MAP_UARTIntEnable(UART3_BASE, UART_INT_RX);
}

