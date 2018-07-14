/*
 * drv8308.c
 *
 *  Created on: 2018/5/17
 *      Author: cking
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "inc/hw_ssi.h"
#include "inc/hw_timer.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "driverlib/ssi.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/systick.h"
#include "driverlib/rom_map.h"
#include "drv8308.h"

// for 3Phase ONLY
#define MRESET_A GPIO_PORTN_BASE
#define MRESET_B GPIO_PIN_1
#define MENABLE_A GPIO_PORTF_BASE
#define MENABLE_B GPIO_PIN_4
#define MDIR0_A GPIO_PORTF_BASE
#define MDIR0_B GPIO_PIN_5
#define MBRAKE0_A GPIO_PORTG_BASE
#define MBRAKE0_B GPIO_PIN_6
#define SSI0_CS_A GPIO_PORTA_BASE
#define SSI0_CS_B GPIO_PIN_3
#define MFAULT0_A GPIO_PORTG_BASE
#define MFAULT0_B GPIO_PIN_7
#define MDIR1_A GPIO_PORTN_BASE
#define MDIR1_B GPIO_PIN_2
#define MBRAKE1_A GPIO_PORTK_BASE
#define MBRAKE1_B GPIO_PIN_3
#define SSI1_CS_A GPIO_PORTF_BASE
#define SSI1_CS_B GPIO_PIN_3
#define MFAULT1_A GPIO_PORTK_BASE
#define MFAULT1_B GPIO_PIN_2

// ************************************************************************************************************
// ************************************************************************************************************
uint16_t ReadDrv( int Num, int Ad )
{
    uint32_t D[3];
    if ( Num == 0 ) {
        MAP_GPIOPinWrite( SSI0_CS_A, SSI0_CS_B, SSI0_CS_B );
        MAP_SysCtlDelay( 26 ); //1uSec
        MAP_SSIDataPut(SSI0_BASE, 0x80 + Ad  );  // read address
        MAP_SSIDataPut(SSI0_BASE, 0  );
        SSIAdvDataPutFrameEnd( SSI0_BASE,  0 );
        while(SSIBusy(SSI0_BASE)) {   MAP_SysCtlDelay(1); }
        MAP_SysCtlDelay( 26 ); //1uSec
        MAP_GPIOPinWrite( SSI0_CS_A, SSI0_CS_B, 0 );
        MAP_SSIDataGet(SSI0_BASE, &D[0]);
        MAP_SSIDataGet(SSI0_BASE, &D[1]);
        MAP_SSIDataGet(SSI0_BASE, &D[2]);
    }
    else {
        MAP_GPIOPinWrite( SSI1_CS_A, SSI1_CS_B, SSI1_CS_B );
        MAP_SysCtlDelay( 26 ); //1uSec
        MAP_SSIDataPut(SSI1_BASE, 0x80 + Ad  );  // read address
        MAP_SSIDataPut(SSI1_BASE, 0  );
        MAP_SSIAdvDataPutFrameEnd( SSI1_BASE,  0 );
        while(SSIBusy(SSI1_BASE)) {   MAP_SysCtlDelay(1); }
        SysCtlDelay( 26 ); //1uSec
        MAP_GPIOPinWrite( SSI1_CS_A, SSI1_CS_B, 0 );
        MAP_SSIDataGet(SSI1_BASE, &D[0]);
        MAP_SSIDataGet(SSI1_BASE, &D[1]);
        MAP_SSIDataGet(SSI1_BASE, &D[2]);
    }
    MAP_SysCtlDelay( 26 ); //1uSec
    return ((D[1] & 0xFF) << 8) | (D[2] & 0xFF);
}

// ************************************************************************************************************
// ************************************************************************************************************
void WriteDrv( int Num, int Ad, uint16_t Data )
{
    uint32_t D[3];
     if ( Num == 0 ) {
         GPIOPinWrite( SSI0_CS_A, SSI0_CS_B, SSI0_CS_B );
         SysCtlDelay( 26 ); //1uSec
         SSIDataPut(SSI0_BASE, Ad  );  // write address
         SSIDataPut(SSI0_BASE, (Data >> 8) & 0xFF );
         SSIAdvDataPutFrameEnd( SSI0_BASE,  Data & 0xFF );
         while(SSIBusy(SSI0_BASE)) {  SysCtlDelay(1); }
         SysCtlDelay( 26 ); //1uSec
         GPIOPinWrite( SSI0_CS_A, SSI0_CS_B, 0 );
         SSIDataGet(SSI0_BASE, &D[0]);
         SSIDataGet(SSI0_BASE, &D[1]);
         SSIDataGet(SSI0_BASE, &D[2]);
     }
     else {
         GPIOPinWrite( SSI1_CS_A, SSI1_CS_B, SSI1_CS_B );
         SysCtlDelay( 26 ); //1uSec
         SSIDataPut(SSI1_BASE, Ad  );  // write address
         SSIDataPut(SSI1_BASE, (Data >> 8) & 0xFF );
         SSIAdvDataPutFrameEnd( SSI1_BASE,  Data & 0xFF );
         while(SSIBusy(SSI1_BASE)) {  SysCtlDelay(1); }
         SysCtlDelay( 26 ); //1uSec
         GPIOPinWrite( SSI1_CS_A, SSI1_CS_B, 0 );
         SSIDataGet(SSI1_BASE, &D[0]);
         SSIDataGet(SSI1_BASE, &D[1]);
         SSIDataGet(SSI1_BASE, &D[2]);
     }

     SysCtlDelay( 26 ); //1uSec

}

void drv8308_init(void)
{
    uint32_t I;

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);

    // MOTORS-3P
    MAP_GPIOPinTypeGPIOOutput( MRESET_A,   MRESET_B );
    MAP_GPIOPinTypeGPIOOutput( MENABLE_A,  MENABLE_B );
    MAP_GPIOPinTypeGPIOOutput( MDIR0_A,    MDIR0_B );
    MAP_GPIOPinTypeGPIOOutput( MDIR1_A,    MDIR1_B );
    MAP_GPIOPinTypeGPIOOutput( MBRAKE0_A,  MBRAKE0_B );
    MAP_GPIOPinTypeGPIOOutput( MBRAKE1_A,  MBRAKE1_B );
    MAP_GPIOPinWrite( MRESET_A,   MRESET_B,  0 );
    MAP_GPIOPinWrite( MENABLE_A,  MENABLE_B, 0 );
    MAP_GPIOPinWrite( MDIR0_A,    MDIR0_B,    0 );
    MAP_GPIOPinWrite( MDIR1_A,    MDIR1_B,    0 );
    MAP_GPIOPinWrite( MBRAKE0_A,  MBRAKE0_B,  0 );
    MAP_GPIOPinWrite( MBRAKE1_A,  MBRAKE1_B,  0 );

    MAP_GPIOPinWrite( MRESET_A,   MRESET_B,  MRESET_B );
    MAP_SysCtlDelay(26600);
    MAP_GPIOPinWrite( MRESET_A,   MRESET_B,  0 );

    MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);             // PA2 - SSI0CLK
    MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX);              // PA4 - SSI0Rx
    MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX);              // PA5 - SSI0Tx
    MAP_GPIOPinTypeGPIOOutput( SSI0_CS_A, SSI0_CS_B );  // PA3 - SSI0Fss
    MAP_GPIOPinWrite( SSI0_CS_A, SSI0_CS_B, 0 );
    MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2);
    MAP_SSIConfigSetExpClk(SSI0_BASE, MAP_SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER, 1000000, 8);
    MAP_SSIEnable(SSI0_BASE);
    while(MAP_SSIDataGetNonBlocking( SSI0_BASE, &I)) { MAP_SysCtlDelay(1); }  // Read any residual data from the SSI port.

    MAP_GPIOPinConfigure(GPIO_PF2_SSI1CLK);
    MAP_GPIOPinConfigure(GPIO_PF0_SSI1RX);
    MAP_GPIOPinConfigure(GPIO_PF1_SSI1TX);
    MAP_GPIOPinTypeGPIOOutput( SSI1_CS_A, SSI1_CS_B );
    MAP_GPIOPinWrite( SSI1_CS_A, SSI1_CS_B, 0 );
    MAP_GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
    MAP_SSIConfigSetExpClk(SSI1_BASE, MAP_SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,SSI_MODE_MASTER, 1000000, 8);
    MAP_SSIEnable(SSI1_BASE);
    while(MAP_SSIDataGetNonBlocking( SSI1_BASE, &I)) { MAP_SysCtlDelay(1); }  // Read any residual data from the SSI port.

     int N = 0;
     for ( N = 0 ; N < 2 ; N++ ) {
         WriteDrv(N,0x2A, 0);  // clear errors
         WriteDrv(N,0x00,0x0021); // AG_SETPT[15:12]=191hz, SYNRECT[8]=1 PWMF[7:6]=50khz SPDMODE[5:4]=Clock Freq RETRY[0]=1
         WriteDrv(N,0x01,0);
         WriteDrv(N,0x02,0xff00);  // SPDREVS[15:8]=4 period before lock, MINSPD[7:0] min period x 2,56msec=450mSec, 25.6mSec = 39hz
         WriteDrv(N,0x03,0xe800);  // SPEEDTH[14:12]=1.56% MOD120=3970 scale  input dutt cycle
    //        WriteDrv(0x04,0x40d2);  // ESINE[8] TDRIVE[7:6]=5uS DTIME[5:3]=240nS IDRIVE[2:0]=10mA
         WriteDrv(N,0x04,0x41d2);  // ESINE[8] TDRIVE[7:6]=5uS DTIME[5:3]=240nS IDRIVE[2:0]=10mA
         WriteDrv(N,0x05,0x0000);  // INTCLK[14:12]=6.3Mhz SPDGAI?N [11:0] speed compensator gain
         WriteDrv(N,0x06,0x0000);  // HALLPOL[15] FILK1[11:0]
         WriteDrv(N,0x07,0x0000);  // FILK2[11:0]
         WriteDrv(N,0x08,0x0000);  // COMPK1[11:0]
         WriteDrv(N,0x09,0x0000);  // COMPK2[11:0]
         WriteDrv(N,0x0A,0x3000);  // OCPDEG[15:14]=5uS,6uS OCPTH[13:12]=1V LOOPGAIN[9:0]
     }
}

void drv8308_set_pwm(int num, int speed)
{
    // at least 3
    if(speed > 3970)
        speed = 3970;
    WriteDrv( num, 0x0B, speed );
}

void drv8308_enable(int on)
{
    MAP_GPIOPinWrite( MENABLE_A, MENABLE_B, on? MENABLE_B : 0 );
}

void drv8308_set_dir(int num, int dir)
{
    if(num == 0)
        MAP_GPIOPinWrite( MDIR0_A,    MDIR0_B,    dir? MDIR0_B: 0);
    else
        MAP_GPIOPinWrite( MDIR1_A,    MDIR1_B,    dir? MDIR1_B: 0);
}

void drv8308_set_brake(int num, int on)
{
    if(num == 0)
        MAP_GPIOPinWrite( MBRAKE0_A,  MBRAKE0_B,  on? MBRAKE0_B: 0);
    else
        MAP_GPIOPinWrite( MBRAKE1_A,  MBRAKE1_B,  on? MBRAKE1_B: 0);
}
