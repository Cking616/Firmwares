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
#include "bsp/delay.h"

extern int g_trip_bit[4];
extern int PD4_bConnected[4];
UNS8 __is_sending = 0;
int _PD4_speed_tmp;
int _PD4_pos_tmp;

static void CheckSDOAndContinue(CO_Data* d, UNS8 nodeId)
{
	UNS32 abortCode;
	if (getWriteResultNetworkDict(d, nodeId, &abortCode) != SDO_FINISHED)
		UARTprintf("Master : Failed in initializing slave %X, AbortCode :%X \n", nodeId, abortCode);

	/* Finalise last SDO transfer with this node */
	closeSDOtransfer(&TestMaster_Data, nodeId, SDO_CLIENT);

	__is_sending = 0;
}

void PD4Master_writeSlaveParam(CO_Data* d, UNS8 nodeId, UNS16 index,
                            UNS8 subindex, UNS8 count,
                            UNS8 dataType, void *data)
{
    if(__is_sending) { return;}
    __is_sending = 1;
    writeNetworkDictCallBack(d, /*CO_Data* d*/
        nodeId, /*UNS8 nodeId*/
        index, /*UNS16 index*/
        subindex, /*UNS16 index*/
        count, /*UNS8 count*/
        dataType, /*UNS8 dataType*/
        data,/*void *data*/
        CheckSDOAndContinue, /*SDOCallback_t Callback*/
        0); /* use block mode */
    while (__is_sending) { delay_us(50); }
}

void PD4Master_set_speed(UNS8 nodeID, int speed)
{
    _PD4_speed_tmp = speed;
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x6081, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              4, /*UNS8 count*/
                              uint32, /*UNS8 dataType*/
                              &_PD4_speed_tmp); /* use block mode */
}

void PD4Master_set_ctrl(UNS8 nodeID, UNS16 word)
{
    PD4_Controlword[nodeID - 1] = word;
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x6040, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              2, /*UNS8 count*/
                              uint16, /*UNS8 dataType*/
                              &  PD4_Controlword[nodeID - 1]); /* use block mode */
}

void PD4Master_set_pos(UNS8 nodeID, int pos)
{
    _PD4_pos_tmp = pos;
    PD4Master_writeSlaveParam(&TestMaster_Data, /*CO_Data* d*/
                              nodeID, /*UNS8 nodeId*/
                              0x607a, /*UNS16 index*/
                              0x00, /*UNS16 index*/
                              4, /*UNS8 count*/
                              int32, /*UNS8 dataType*/
                              &_PD4_pos_tmp); /* use block mode */
    PD4Master_set_ctrl(nodeID, 0x3F);
    g_trip_bit[nodeID - 1] = 1;
}

unsigned char PD4Master_get_flag(unsigned char nodeID)
{
    unsigned char _flag = ((PD4_Status[nodeID - 1] & 0x67) == 0x27) ? 0x10 : 0;
    _flag |= (PD4_Status[nodeID - 1] & 0x400) ? 0x1 : 0;
    return _flag;
}

void PD4Master_stop(unsigned char nodeID)
{
    PD4Master_set_ctrl(nodeID, 0x2);
}

inline int PD4Master_get_encoder(unsigned char nodeID)
{
    return PD4_Position[nodeID - 1];
}

/*****************************************************************************/
void TestMaster_heartbeatError(CO_Data* d, UNS8 heartbeatID)
{
	UARTprintf("TestMaster_heartbeatError %d\n", heartbeatID);
}

/********************************************************
 * ConfigureSlaveNode is responsible to
 *  - setup master RPDO 1 to receive TPDO 1 from id 2
 *  - setup master RPDO 2 to receive TPDO 2 from id 2
 ********************************************************/
void TestMaster_initialisation(CO_Data* d)
{
	UARTprintf("TestMaster_initialisation\n");

	/*****************************************
	 * Define RPDOs to match slave ID=2 TPDOs*
	 *****************************************/
	masterSendNMTstateChange(d, 0x1, NMT_Reset_Node);
	masterSendNMTstateChange(d, 0x2, NMT_Reset_Node);
	masterSendNMTstateChange(d, 0x3, NMT_Reset_Node);
	masterSendNMTstateChange(d, 0x4, NMT_Reset_Node);
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
 * This is called first by TestMaster_post_SlaveBootup
 * then it called again each time a SDO exchange is
 * finished.
 ********************************************************/
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

void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId)
{
	/* Master configure heartbeat producer time at 1000 ms 
	 * for slave node-id 0x02 by DCF concise */
    masterSendNMTstateChange(d, 0x1, NMT_Enter_PreOperational);
    CanOpen_setMaster(d, nodeId);
	/* Ask slave node to go in operational mode */
	//masterSendNMTstateChange (d, nodeId, NMT_Start_Node);
    PD4_bConnected[nodeId - 1] = 1;
}

void TestMaster_preOperational(CO_Data* d)
{
	UARTprintf("TestMaster_preOperational\n");
}

void TestMaster_operational(CO_Data* d)
{
	UARTprintf("TestMaster_operational\n");
}

void TestMaster_stopped(CO_Data* d)
{
	UARTprintf("TestMaster_stopped\n");
}

void TestMaster_post_sync(CO_Data* d)
{
}

void TestMaster_post_emcy(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg)
{
	UARTprintf("Master received EMCY message. Node: %X  ErrorCode: %X  ErrorRegister: %X\n", nodeID, errCode, errReg);
}

void TestMaster_post_TPDO(CO_Data* d)
{
}

void TestMaster_post_SlaveBootup(CO_Data* d, UNS8 nodeid)
{
	UARTprintf("TestMaster_post_SlaveBootup %x\n", nodeid);
	ConfigureSlaveNode(d, nodeid);
}

void TestMaster_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState)
{
    UARTprintf("TestMaster_post_SlaveStateChange %x\n", nodeId);
}

void readSlaveNode(CO_Data* d, UNS8 nodeId)
{
	UNS32 data = 0;
	UNS32 size = 4;
	UNS32 abort;
	int i = 0;

	readNetworkDict(d, nodeId, 0x1600, 0, uint8, 0); // get the data index 1800 subindex 1 of node 5
	size = 1;
	while (getReadResultNetworkDict(d, nodeId, &data, &size, &abort) == SDO_UPLOAD_IN_PROGRESS) { delay_ms(2); }
	UARTprintf("RPDO:0x1600, num:0x%X\n", data);
	delay_ms(20);
	int num = data;
	for (i = 0; i < num; i++)
	{
		readNetworkDict(d, nodeId, 0x1600, i + 1, uint32, 0); // get the data index 1800 subindex 1 of node 5
		size = 4;
		while (getReadResultNetworkDict(d, nodeId, &data, &size, &abort) == SDO_UPLOAD_IN_PROGRESS) { delay_ms(2); }
		UARTprintf("RPDO:0x1600, sub:0x%X, data0x%X:\n", i + 1, data);
		delay_ms(20);
	}

	readNetworkDict(d, nodeId, 0x1A00, 0, uint8, 0); // get the data index 1800 subindex 1 of node 5
	size = 1;
	data = 0;
	while (getReadResultNetworkDict(d, nodeId, &data, &size, &abort) == SDO_UPLOAD_IN_PROGRESS) { delay_ms(2); }
	UARTprintf("TPDO:0x1A00, num:0x%X\n", data);
	delay_ms(20);
	num = data;
	for (i = 0; i < num; i++)
	{
		readNetworkDict(d, nodeId, 0x1A00, i + 1, uint32, 0); // get the data index 1800 subindex 1 of node 5
		size = 4;
		while (getReadResultNetworkDict(d, nodeId, &data, &size, &abort) == SDO_UPLOAD_IN_PROGRESS) { delay_ms(2); }
		UARTprintf("TPDO:0x1A00, sub:0x%X, data0x%X:\n", i + 1, data);
		delay_ms(20);
	}
}
