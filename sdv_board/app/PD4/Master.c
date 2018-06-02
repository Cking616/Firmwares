/*
This file is part of CanFestival, a library implementing CanOpen Stack. 

Copyright (C): Edouard TISSERANT and Francis DUPIN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "Master.h"
#include "canfestival.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"  
#include "task.h"  
#include "queue.h" 
#include "semphr.h"

extern xQueueHandle g_Slave_Queue;
extern SemaphoreHandle_t g_SDO_Semaphore;
extern SemaphoreHandle_t g_SDO_Mutex;
static int __init_step;

void CanOpen_setMaster(CO_Data* d, UNS8 nodeId)
{
	UNS32 PDO1_COBID = 0x0180 + nodeId;
	UNS32 PDO2_COBID = 0x0200 + nodeId;
	UNS32 size = sizeof(UNS32);

	/*****************************************
	* Define RPDOs to match slave ID=2 TPDOs*
	*****************************************/
	writeLocalDict(d, /*CO_Data* d*/
		0x1400 + nodeId - 1, /*UNS16 index*/
		0x01, /*UNS8 subind*/
		&PDO1_COBID, /*void * pSourceData,*/
		&size, /* UNS8 * pExpectedSize*/
		RW);  /* UNS8 checkAccess */

	writeLocalDict(d, /*CO_Data* d*/
		0x1800 + nodeId - 1, /*UNS16 index*/
		0x01, /*UNS8 subind*/
		&PDO2_COBID, /*void * pSourceData,*/
		&size, /* UNS8 * pExpectedSize*/
		RW);  /* UNS8 checkAccess */
}

static void CheckSDOAndContinue(CO_Data* d, UNS8 nodeId)
{
	UNS32 abortCode;
	if (getWriteResultNetworkDict(d, nodeId, &abortCode) != SDO_FINISHED)
		UARTprintf("Master : Failed in initializing slave %X, AbortCode :%X, Step:%d\n", nodeId, abortCode, __init_step);

	/* Finalise last SDO transfer with this node */
	closeSDOtransfer(&TestMaster_Data, nodeId, SDO_CLIENT);

	xSemaphoreGiveFromISR(g_SDO_Semaphore, NULL);
}

void PD4Master_writeSlaveParam(CO_Data* d, UNS8 nodeId, UNS16 index,
							UNS8 subindex, UNS8 count, 
							UNS8 dataType, void *data)
{
	xSemaphoreTake(g_SDO_Mutex, 0xffff);
	taskDISABLE_INTERRUPTS();
	writeNetworkDictCallBack(d, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		index, /*UNS16 index*/
		subindex, /*UNS16 index*/
		count, /*UNS8 count*/
		dataType, /*UNS8 dataType*/
		data,/*void *data*/
		CheckSDOAndContinue, /*SDOCallback_t Callback*/
		0); /* use block mode */
	taskENABLE_INTERRUPTS();
	__init_step++;
	xSemaphoreTake(g_SDO_Semaphore, 0xffff);
	xSemaphoreGive(g_SDO_Mutex);
}

void CanOpen_Reset_TPDO(CO_Data* d, UNS8 nodeId)
{
	const portTickType xDelay = pdMS_TO_TICKS(10);
	UNS8 data8 = 0x01;
	int32_t data = 0;

	data8 = 0x1;
	PD4Master_writeSlaveParam(d, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		0x1800, /*UNS16 index*/
		0x02, /*UNS8 subindex*/
		1, /*UNS8 count*/
		0, /*UNS8 dataType*/
		&data8); /* use block mode */

	data = 0x180 + nodeId;
	PD4Master_writeSlaveParam(d, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		0x1800, /*UNS16 index*/
		0x01, /*UNS16 index*/
		4, /*UNS8 count*/
		uint32, /*UNS8 dataType*/
		&data); /* use block mode */
}

void CanOpen_Change_Param(CO_Data* d, UNS8 nodeId)
{
	UNS8 data8 = 0x01;
	int32_t data = 0;

	data = 3000;
	PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		0x6081, /*UNS16 index*/
		0x00, /*UNS16 index*/
		4, /*UNS8 count*/
		uint32, /*UNS8 dataType*/
		&data); /* use block mode */

    data = 800000;
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
        0x607a, /*UNS16 index*/
        0x00, /*UNS16 index*/
        4, /*UNS8 count*/
        int32, /*UNS8 dataType*/
        &data); /* use block mode */

	data = 1;
	PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		0x3202, /*UNS16 index*/
		0x00, /*UNS16 index*/
		4, /*UNS8 count*/
		uint32, /*UNS8 dataType*/
		&data); /* use block mode */

	data8 = 1;
	PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		0x6060, /*UNS16 index*/
		0x00, /*UNS16 index*/
		1, /*UNS8 count*/
		0, /*UNS8 dataType*/
		&data); /* use block mode */
}

void CanOpen_Reset_RPDO(CO_Data* d, UNS8 nodeId)
{
	int32_t data;
	UNS8 data8;
    const portTickType xDelay = pdMS_TO_TICKS(300);

    vTaskDelay(xDelay);
	data = 0x200 + nodeId;
	PD4Master_writeSlaveParam(d, /*CO_Data* d*/
		nodeId, /*UNS8 nodeId*/
		0x1400, /*UNS16 index*/
		0x01, /*UNS16 index*/
		4, /*UNS8 count*/
		uint32, /*UNS8 dataType*/
		&data); /* use block mode */

    data8 = 0xFF;
    PD4Master_writeSlaveParam(d, /*CO_Data* d*/
        nodeId, /*UNS8 nodeId*/
        0x1400, /*UNS16 index*/
        0x02, /*UNS8 subindex*/
        1, /*UNS8 count*/
        0, /*UNS8 dataType*/
        &data8); /* use block mode */
}

/*****************************************************************************/
void PD4Master_heartbeatError(CO_Data* d, UNS8 heartbeatID)
{
	UARTprintf("PD4Master_heartbeatError %d\n", heartbeatID);
}

/********************************************************
 * ConfigureSlaveNode is responsible to
 *  - setup master RPDO 1 to receive TPDO 1 from id 2
 *  - setup master RPDO 2 to receive TPDO 2 from id 2
 ********************************************************/
void PD4Master_initialisation(CO_Data* d)
{
	//UARTprintf("PD4Master_initialisation\n");

	/*****************************************
	 * Define RPDOs to match slave ID=2 TPDOs*
	 *****************************************/
    //masterSendNMTstateChange(&TestMaster_Data, 0x04, NMT_Enter_PreOperational);
    //masterSendNMTstateChange(&TestMaster_Data, 0x03, NMT_Enter_PreOperational);
}

/********************************************************
 * ConfigureSlaveNode is responsible to
 *  - setup slave TPDO 1 transmit type
 *  - setup slave TPDO 2 transmit type
 *  - switch to operational mode
 *  - send NMT to slave
 ********************************************************
 * This an example of :
 * Network Dictionary Access (SDO) with Callback 
 * Slave node state change request (NMT) 
 ********************************************************
 * This is called first by PD4Master_post_SlaveBootup
 * then it called again each time a SDO exchange is
 * finished.
 ********************************************************/
 
void PD4Master_confSlaveNode(CO_Data* d, UNS8 nodeId)
{
	/* Master configure heartbeat producer time at 1000 ms 
	 * for slave node-id 0x02 by DCF concise */
    __init_step = 0;
	//UARTprintf("Master : ConfigureSlaveNode %X\n", nodeId);
	CanOpen_setMaster(d, nodeId);
	if(nodeId == 3)
	{
	    CanOpen_Reset_TPDO(d, nodeId);
	    CanOpen_Change_Param(d, nodeId);
	    CanOpen_Reset_RPDO(d, nodeId);
	}
	/* Put the master in operational mode */
	//setState(d, Operational);
	//Contolword2 = 0x86;
	/* Ask slave node to go in operational mode */
	//masterSendNMTstateChange (d, nodeId, NMT_Start_Node);
}


void PD4Master_preOperational(CO_Data* d)
{
	//UARTprintf("PD4Master_preOperational\n");
}

void PD4Master_operational(CO_Data* d)
{
	//UARTprintf("PD4Master_operational\n");
}

void PD4Master_stopped(CO_Data* d)
{
	//UARTprintf("PD4Master_stopped\n");
}

void PD4Master_post_sync(CO_Data* d)
{
}

void PD4Master_post_emcy(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg)
{
	UARTprintf("Master received EMCY message. Node: %X  ErrorCode: %X  ErrorRegister: %X\n", nodeID, errCode, errReg);
}

void PD4Master_post_TPDO(CO_Data* d)
{
}

void PD4Master_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState)
{
    //UARTprintf("slave %x, state %x\n", nodeId, newNodeState);
	switch (newNodeState)
	{
	case Initialisation:
		masterSendNMTstateChange(&TestMaster_Data, nodeId, NMT_Enter_PreOperational);
		break;
	case Pre_operational:
		xQueueSendToBackFromISR( g_Slave_Queue, ( void* )&nodeId, 0 );
	    break;
	default:
		break;
	}
}
