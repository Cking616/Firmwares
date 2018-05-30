#include "PD4Master.h"

void PD4Master_heartbeatError(CO_Data* d, UNS8);

UNS8 PD4Master_canSend(Message *);

void PD4Master_initialisation(CO_Data* d);
void PD4Master_preOperational(CO_Data* d);
void PD4Master_operational(CO_Data* d);
void PD4Master_stopped(CO_Data* d);

void PD4Master_post_sync(CO_Data* d);
void PD4Master_post_TPDO(CO_Data* d);
void PD4Master_post_emcy(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg);
void PD4Master_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState);
void PD4Master_confSlaveNode(CO_Data* d, UNS8 nodeId);
void PD4Master_writeSlaveParam(CO_Data* d, UNS8 nodeId, UNS16 index,
	UNS8 subindex, UNS8 count,
	UNS8 dataType, void *data);
