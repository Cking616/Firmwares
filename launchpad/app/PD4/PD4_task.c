/*
 * PD4_task.c
 *
 *  Created on: 2018/5/28
 *      Author: cking
 */

#include <stdbool.h>
#include <stdint.h>
#include "PD4Master.h"
#include "Master.h"
#include "PD4_task.h"
#include "utils/uartstdio.h"

int g_trip_bit[4] = {0, 0, 0, 0};
int PD4_bConnected[4] = {0, 0, 0, 0};
//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
void PD4Master_op_period(void)
{
    int _i = 0;

    for (_i = 0; _i < 4; _i++)
    {
        if (!PD4_bConnected[_i])
        {
            continue;
        }

        sendPDOrequest(&TestMaster_Data, 0x1400 + _i);
    }

    for (_i = 0; _i < 4; _i++)
    {
        if (!PD4_bConnected[_i])
        {
            continue;
        }

        if (PD4_Status[_i] & 0x40)
        {
            PD4_Controlword[_i] = 0x6;
        }
        else if (PD4_Status[_i] & 0x20)
        {
            if (PD4_Status[_i] & 0x2)
            {
                PD4_Controlword[_i] = 0xF;
            }
            else
            {
                PD4_Controlword[_i] = 0x7;
            }
        }

        if ((PD4_Status[_i] & 0x67) == 0x27)
        {
            if (g_trip_bit[_i])
            {
                PD4_Controlword[_i] = 0x3F;
                g_trip_bit[_i] = 0;
            }
            else
            {
                PD4_Controlword[_i] = 0x2F;
            }
        }
    }

    for (_i = 0; _i < 4; _i++)
    {
        if (!PD4_bConnected[_i])
        {
            continue;
        }
        sendOnePDOevent(&TestMaster_Data, _i);
    }
}

void PD4Master_preop_period(void)
{
	if (PD4_bConnected[1] && PD4_bConnected[2])
	{
		masterSendNMTstateChange(&TestMaster_Data, 0x2, NMT_Enter_PreOperational);
		masterSendNMTstateChange(&TestMaster_Data, 0x3, NMT_Start_Node);
		setState(&TestMaster_Data, Operational);
	}
}

void PD4Master_period(void)
{
    if(getState(&TestMaster_Data) == Operational)
    {
        PD4Master_op_period();
    }
    else
    {
		PD4Master_preop_period();
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
uint32_t
PD4Master_taskInit(void)
{
    TestMaster_Data.heartbeatError = TestMaster_heartbeatError;
    TestMaster_Data.initialisation = TestMaster_initialisation;
    TestMaster_Data.preOperational = TestMaster_preOperational;
    TestMaster_Data.operational = TestMaster_operational;
    TestMaster_Data.stopped = TestMaster_stopped;
    TestMaster_Data.post_sync = TestMaster_post_sync;
    TestMaster_Data.post_TPDO = TestMaster_post_TPDO;
    TestMaster_Data.post_emcy = TestMaster_post_emcy;
    TestMaster_Data.post_SlaveBootup=TestMaster_post_SlaveBootup;
    TestMaster_Data.post_SlaveStateChange = TestMaster_post_SlaveStateChange;
    setNodeId(&TestMaster_Data, 0x7F);
    setState(&TestMaster_Data, Initialisation);     // Init the state
    setState(&TestMaster_Data, Pre_operational);     // Init the state
    //
    // Success.
    //
    return(0);
}
