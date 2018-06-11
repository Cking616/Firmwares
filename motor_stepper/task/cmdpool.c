/*
 * cmdpool.c
 *
 *  Created on: 2018Äê5ÔÂ2ÈÕ
 *      Author: Administrator
 */

#include "cmdpool.h"
#include "../bsp/can.h"

void cmd_thread(int addr)
{
    unsigned int Cmd;
    unsigned int L;
    int dir;
    if(g_bRXFlag)
    {
        // Clear the pending message flag
        if (                            (CanRXAd & 0x1F) == addr+8  ||  // 8,9,10,11,
            ( addr <= 3               && (CanRXAd & 0x1F) == 16 ) ||
            ( (addr == 2 || addr == 3) && (CanRXAd & 0x1F) == 17 ) ||
            ( (addr == 4 || addr == 5) && (CanRXAd & 0x1F) == 18) ) {

            // CanMsgIn[31..0]: Cmd[7..4] are the 4 top most bits
            // 0 - nothing
            // 1 - MoveMotor   Cmd[3]=0 go, 1=brake, =1 encoder, Cmd[2..0]=power, CanMsgIn[0][24]=0|1 Fwd or Back
            // 2 - MoveStepper Cmd[3]=0 time, =1 encoder, Cmd[1]=Stepper 0 or 1  CanMsgIn[0][24]=0|1 Fwd or Back
            // 3 - StopMotor now
            // 4 - get info, Cmd[2..0] = device ID,
            //     CanMsgIn[7..0]: 1 - get Position
            // 5 - turn GPIOS: Cmd[3]=0: On/Off LED, Cmd[3]=Red.  Cmd[2]:Gren
            //                 Cmd[3]=1  GPIO PA0 and PA1 : Cmd[2..1]=00:PA0 or 01:PA1, 10:TBreak  Cmd[0]=0 or 1
            // 6 - Zero Stepper
            // f -
            Cmd = (CanMsgIn[0] >> 24) & 0xFF;
            //UARTprintf("CMD Recive:%d\n", Cmd);
            switch ( Cmd & 0xF0) {
            case 0x10: // MoveMotor
                dir = (CanMsgIn[0] & 0x800000)==0? 0 : 1;
                // gMotorUseTime[0] = 1;
                // gTimeMotorToOff[0] = gTick_ms + (CanMsgIn[0] & 0xFFFF);
                // gMotorOn[0] = 1;
                // LedGreen(1);
                L = (CanMsgIn[0] >> 16) & 0x7F;
                if ((Cmd & 0x08) != 0 )
                {
                    //speed_controller_set_speed(0);
                }
                else
                {
                    if(!dir) L = -L;
                    if(addr == 2) L = -L;

                    //UARTprintf("Set Speed:%d\n", L);
                    //speed_controller_set_speed(L);
                }
                break;

            case 0x30:
                //speed_controller_set_speed(0);
                break;

            case 0x40:
                if ( ( Cmd & 1 ) == 0 ) {
                    //int speed = speed_controller_get_speed() * 100;
                    //can_write(addr, speed_controller_get_encoder(), speed);
                }
                //else {
                    // 6.M1PWM0 = PG2
                    // 8.AIN7=PD0
                    // PHA1 = PC5 J6.3
                    // PHB0 = PF1 J7.3
                    //I = (GPIOPinRead( GPIO_PORTG_BASE, GPIO_PIN_2)==0? 1 : 0 ) |
                    //    (GPIOPinRead( GPIO_PORTD_BASE, GPIO_PIN_0)==0? 2 : 0 ) |
                    //    (GPIOPinRead( GPIO_PORTC_BASE, GPIO_PIN_5)==0? 4 : 0 ) |
                    //    (GPIOPinRead( GPIO_PORTF_BASE, GPIO_PIN_1)==0? 8 : 0 );
                    //CANSendToControl( I, 0 );
                //}
                break;

            case 0x50:
                if ( Cmd & 0x80 ) {
                    //LedRed((Cmd >> 3) & 1);
                    //LedGreen((Cmd >> 2) & 1);
                }
                else {  // PA0 or PA1
                    //if ( (Cmd & 0x06) == 0x00 )  // PA0
                    //    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_0, (Cmd & 1) == 0 ? 0 : GPIO_PIN_0 );
                    //else if ( (Cmd & 0x06) == 0x02 )  // PA1
                    //    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_1, (Cmd & 1) == 0 ? 0 : GPIO_PIN_1 );
                    //if ( (Cmd & 0x06) == 0x04 )  // Brake Motor
                    //{
                        //if(Cmd & 1)
                            //speed_controller_set_speed(0);
                    //}
                    //    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, (Cmd & 1) == 0 ? 0 : GPIO_PIN_2 );
                }
                break;
            }
            CanMsgIn[0] = 0;
        }
        g_bRXFlag = 0;
    }
}
