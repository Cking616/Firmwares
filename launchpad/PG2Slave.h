
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef PG2SLAVE_H
#define PG2SLAVE_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 TestSlave_valueRangeTest (UNS8 typeValue, void * value);
const indextable * TestSlave_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks);

/* Master node data struct */
extern CO_Data TestSlave_Data;

#endif // PG2SLAVE_H
