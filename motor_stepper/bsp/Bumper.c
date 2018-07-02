/*
 * Bumper.c
 *
 *  Created on: 2018/6/1
 *      Author: cking
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"


void bumper_init()
{
    //
    // The ADC0 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // ADC
    //GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3); // AIN0
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2); // AIN1
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1); // AIN2
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1); // AIN6
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0); // AIN6
    //GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0); // AIN3

    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    //ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 );
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH6);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 0);    // Since sample sequence 3 is now configured, it must be enabled.
    ADCIntClear(ADC0_BASE, 0);  // Clear the interrupt status flag.  This is done to make sure the interrupt flag is cleared before we sample.
}

void bumper_print()
{
    uint32_t pui32ADC0Value[4];
    //
    // Trigger the ADC conversion.
    //
    ADCProcessorTrigger(ADC0_BASE, 0);

    //
    // Wait for conversion to be completed.
    //
    while(!ADCIntStatus(ADC0_BASE, 0, false))
    {
    }

    //
    // Clear the ADC interrupt flag.
    //
    ADCIntClear(ADC0_BASE, 0);

    //
    // Read ADC Value.
    //
    ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC0Value);

    //
    // Display the AIN0 (PE3) digital value on the console.
    //
    UARTprintf("AIN1 = %4d\r", pui32ADC0Value[0]);
    UARTprintf("AIN2 = %4d\r", pui32ADC0Value[1]);
    UARTprintf("AIN6 = %4d\r", pui32ADC0Value[2]);
    UARTprintf("AIN7 = %4d\r", pui32ADC0Value[3]);
}

void bumper_process()
{
	uint32_t pui32ADC0Value[4];
	//
	// Trigger the ADC conversion.
	//
	ADCProcessorTrigger(ADC0_BASE, 0);

	//
	// Wait for conversion to be completed.
	//
	while (!ADCIntStatus(ADC0_BASE, 0, false))
	{
	}

	//
	// Clear the ADC interrupt flag.
	//
	ADCIntClear(ADC0_BASE, 0);

	//
	// Read ADC Value.
	//
	ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC0Value);

	//
	// Display the AIN0 (PE3) digital value on the console.
	//
}
