
/* File generated by gen_cfile.py. Should not be modified. */

#include "PG2Slave.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
UNS8 Input1 = 0x0;		/* Mapped at index 0x2000, subindex 0x00 */
UNS8 Output1 = 0x0;		/* Mapped at index 0x2001, subindex 0x00 */
UNS32 Bumper1 = 0x0;		/* Mapped at index 0x2002, subindex 0x00 */
UNS32 Bumper2 = 0x0;		/* Mapped at index 0x2004, subindex 0x00 */
INTEGER32 YEncoder = 0x0;		/* Mapped at index 0x2006, subindex 0x00 */

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 TestSlave_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 TestSlave_bDeviceNodeId = 0x00;

/**************************************************************************/
/* Array of message processing information */

const UNS8 TestSlave_iam_a_slave = 1;

TIMER_HANDLE TestSlave_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 TestSlave_obj1000 = 0x12D;	/* 301 */
                    subindex TestSlave_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 TestSlave_obj1001 = 0x0;	/* 0 */
                    subindex TestSlave_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_obj1001 }
                     };

/* index 0x1003 :   Pre-defined Error Field. */
                    UNS8 TestSlave_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1003[] = 
                    {
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0,	/* 0 */
                      0x0	/* 0 */
                    };
                    ODCallback_t TestSlave_Index1003_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1003 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[0] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[1] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[2] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[3] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[4] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[5] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[6] },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1003[7] }
                     };

/* index 0x1005 :   SYNC COB ID. */
                    UNS32 TestSlave_obj1005 = 0x80;	/* 128 */
                    ODCallback_t TestSlave_Index1005_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index1005[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1005 }
                     };

/* index 0x1006 :   Communication / Cycle Period. */
                    UNS32 TestSlave_obj1006 = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1006_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index1006[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1006 }
                     };

/* index 0x100C :   Guard Time */ 
                    UNS16 TestSlave_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 TestSlave_obj100D = 0x0;   /* 0 */

/* index 0x1010 :   Store parameters. */
                    UNS8 TestSlave_highestSubIndex_obj1010 = 4; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1010_Save_All_Parameters = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1010_Save_Communication_Parameters = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1010_Save_Application_Parameters = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1010_Save_Manufacturer_Parameters_1 = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1010_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index1010[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1010 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1010_Save_All_Parameters },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1010_Save_Communication_Parameters },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1010_Save_Application_Parameters },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1010_Save_Manufacturer_Parameters_1 }
                     };

/* index 0x1011 :   Restore Default Parameters. */
                    UNS8 TestSlave_highestSubIndex_obj1011 = 4; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1011_Restore_All_Default_Parameters = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1011_Restore_Communication_Default_Parameters = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1011_Restore_Application_Default_Parameters = 0x0;	/* 0 */
                    UNS32 TestSlave_obj1011_Restore_Manufacturer_Defined_Default_Parameters_1 = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1011_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestSlave_Index1011[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1011 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1011_Restore_All_Default_Parameters },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1011_Restore_Communication_Default_Parameters },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1011_Restore_Application_Default_Parameters },
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1011_Restore_Manufacturer_Defined_Default_Parameters_1 }
                     };

/* index 0x1014 :   Emergency COB ID. */
                    UNS32 TestSlave_obj1014 = 0x80;	/* 128 */
                    subindex TestSlave_Index1014[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&TestSlave_obj1014 }
                     };

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 TestSlave_highestSubIndex_obj1016 = 0;
                    UNS32 TestSlave_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    UNS16 TestSlave_obj1017 = 0x0;	/* 0 */
                    ODCallback_t TestSlave_Index1017_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestSlave_Index1017[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&TestSlave_obj1017 }
                     };

/* index 0x1018 :   Identity. */
                    UNS8 TestSlave_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1018_Vendor_ID = 0x12345678;	/* 305419896 */
                    UNS32 TestSlave_obj1018_Product_Code = 0x90123456;	/* 2417112150 */
                    UNS32 TestSlave_obj1018_Revision_Number = 0x78901234;	/* 2022707764 */
                    UNS32 TestSlave_obj1018_Serial_Number = 0x56789012;	/* 1450741778 */
                    subindex TestSlave_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1018_Serial_Number }
                     };

/* index 0x1200 :   Server SDO Parameter. */
                    UNS8 TestSlave_highestSubIndex_obj1200 = 2; /* number of subindex - 1*/
                    UNS32 TestSlave_obj1200_COB_ID_Client_to_Server_Receive_SDO = 0x600;	/* 1536 */
                    UNS32 TestSlave_obj1200_COB_ID_Server_to_Client_Transmit_SDO = 0x580;	/* 1408 */
                    subindex TestSlave_Index1200[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestSlave_highestSubIndex_obj1200 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1200_COB_ID_Client_to_Server_Receive_SDO },
                       { RO, uint32, sizeof (UNS32), (void*)&TestSlave_obj1200_COB_ID_Server_to_Client_Transmit_SDO }
                     };

/* index 0x2000 :   Mapped variable Input1 */
                    subindex TestSlave_Index2000[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Input1 }
                     };

/* index 0x2001 :   Mapped variable Output1 */
                    subindex TestSlave_Index2001[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&Output1 }
                     };

/* index 0x2002 :   Mapped variable Bumper1 */
                    subindex TestSlave_Index2002[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&Bumper1 }
                     };

/* index 0x2004 :   Mapped variable Bumper2 */
                    subindex TestSlave_Index2004[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&Bumper2 }
                     };

/* index 0x2006 :   Mapped variable YEncoder */
                    subindex TestSlave_Index2006[] = 
                     {
                       { RW, int32, sizeof (INTEGER32), (void*)&YEncoder }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable TestSlave_objdict[] = 
{
  { (subindex*)TestSlave_Index1000,sizeof(TestSlave_Index1000)/sizeof(TestSlave_Index1000[0]), 0x1000},
  { (subindex*)TestSlave_Index1001,sizeof(TestSlave_Index1001)/sizeof(TestSlave_Index1001[0]), 0x1001},
  { (subindex*)TestSlave_Index1003,sizeof(TestSlave_Index1003)/sizeof(TestSlave_Index1003[0]), 0x1003},
  { (subindex*)TestSlave_Index1005,sizeof(TestSlave_Index1005)/sizeof(TestSlave_Index1005[0]), 0x1005},
  { (subindex*)TestSlave_Index1006,sizeof(TestSlave_Index1006)/sizeof(TestSlave_Index1006[0]), 0x1006},
  { (subindex*)TestSlave_Index1010,sizeof(TestSlave_Index1010)/sizeof(TestSlave_Index1010[0]), 0x1010},
  { (subindex*)TestSlave_Index1011,sizeof(TestSlave_Index1011)/sizeof(TestSlave_Index1011[0]), 0x1011},
  { (subindex*)TestSlave_Index1014,sizeof(TestSlave_Index1014)/sizeof(TestSlave_Index1014[0]), 0x1014},
  { (subindex*)TestSlave_Index1017,sizeof(TestSlave_Index1017)/sizeof(TestSlave_Index1017[0]), 0x1017},
  { (subindex*)TestSlave_Index1018,sizeof(TestSlave_Index1018)/sizeof(TestSlave_Index1018[0]), 0x1018},
  { (subindex*)TestSlave_Index1200,sizeof(TestSlave_Index1200)/sizeof(TestSlave_Index1200[0]), 0x1200},
  { (subindex*)TestSlave_Index2000,sizeof(TestSlave_Index2000)/sizeof(TestSlave_Index2000[0]), 0x2000},
  { (subindex*)TestSlave_Index2001,sizeof(TestSlave_Index2001)/sizeof(TestSlave_Index2001[0]), 0x2001},
  { (subindex*)TestSlave_Index2002,sizeof(TestSlave_Index2002)/sizeof(TestSlave_Index2002[0]), 0x2002},
  { (subindex*)TestSlave_Index2004,sizeof(TestSlave_Index2004)/sizeof(TestSlave_Index2004[0]), 0x2004},
  { (subindex*)TestSlave_Index2006,sizeof(TestSlave_Index2006)/sizeof(TestSlave_Index2006[0]), 0x2006},
};

const indextable * TestSlave_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1003: i = 2;*callbacks = TestSlave_Index1003_callbacks; break;
		case 0x1005: i = 3;*callbacks = TestSlave_Index1005_callbacks; break;
		case 0x1006: i = 4;*callbacks = TestSlave_Index1006_callbacks; break;
		case 0x1010: i = 5;*callbacks = TestSlave_Index1010_callbacks; break;
		case 0x1011: i = 6;*callbacks = TestSlave_Index1011_callbacks; break;
		case 0x1014: i = 7;break;
		case 0x1017: i = 8;*callbacks = TestSlave_Index1017_callbacks; break;
		case 0x1018: i = 9;break;
		case 0x1200: i = 10;break;
		case 0x2000: i = 11;break;
		case 0x2001: i = 12;break;
		case 0x2002: i = 13;break;
		case 0x2004: i = 14;break;
		case 0x2006: i = 15;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &TestSlave_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status TestSlave_PDO_status[1] = {s_PDO_status_Initializer};

const quick_index TestSlave_firstIndex = {
  10, /* SDO_SVR */
  0, /* SDO_CLT */
  0, /* PDO_RCV */
  0, /* PDO_RCV_MAP */
  0, /* PDO_TRS */
  0 /* PDO_TRS_MAP */
};

const quick_index TestSlave_lastIndex = {
  10, /* SDO_SVR */
  0, /* SDO_CLT */
  0, /* PDO_RCV */
  0, /* PDO_RCV_MAP */
  0, /* PDO_TRS */
  0 /* PDO_TRS_MAP */
};

const UNS16 TestSlave_ObjdictSize = sizeof(TestSlave_objdict)/sizeof(TestSlave_objdict[0]); 

CO_Data TestSlave_Data = CANOPEN_NODE_DATA_INITIALIZER(TestSlave);

