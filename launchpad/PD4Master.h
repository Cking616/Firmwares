
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef PD4MASTER_H
#define PD4MASTER_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 TestMaster_valueRangeTest (UNS8 typeValue, void * value);
const indextable * TestMaster_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data TestMaster_Data;

extern UNS16 PD4_Controlword[4];		/* Mapped at index 0x2011, subindex 0x00*/
extern UNS16 PD4_Status[4];		/* Mapped at index 0x2012, subindex 0x00*/
extern UNS32 PD4_SubMode[4];		/* Mapped at index 0x2013, subindex 0x00*/
extern INTEGER8 PD4_Mode[4];		/* Mapped at index 0x2014, subindex 0x00*/
extern INTEGER32 PD4_Position[4];		/* Mapped at index 0x2015, subindex 0x00*/

#endif // PD4MASTER_H
