#include "PD4Master.h"

void TestMaster_heartbeatError(CO_Data* d, UNS8);

UNS8 TestMaster_canSend(Message *);

void TestMaster_initialisation(CO_Data* d);
void TestMaster_preOperational(CO_Data* d);
void TestMaster_operational(CO_Data* d);
void TestMaster_stopped(CO_Data* d);

void TestMaster_post_sync(CO_Data* d);
void TestMaster_post_TPDO(CO_Data* d);
void TestMaster_post_emcy(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg);
void TestMaster_post_SlaveBootup(CO_Data* d, UNS8 nodeid);
void TestMaster_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState);
void ConfigureSlaveNode(CO_Data* d, UNS8 nodeId);
void readSlaveNode(CO_Data* d, UNS8 nodeId);
void confMaster(CO_Data* d, UNS8 nodeId);
void PD4Master_set_speed(UNS8 nodeID, int speed);
void PD4Master_set_pos(UNS8 nodeID, int pos);
void PD4Master_stop(unsigned char nodeID);
int PD4Master_get_encoder(unsigned char nodeID);
unsigned char PD4Master_get_flag(unsigned char nodeID);

