/*
 * user_cmd.c
 *
 *  Created on: 2018Äê6ÔÂ18ÈÕ
 *      Author: cking
 */

#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include "utils/cmdline.h"
#include "cmd_task.h"
#include "../PD4/Master.h"
#include "bsp/MA3encoder.h"

int CMD_help(int argc, char **argv);
int CMD_set_speed(int argc, char **argv);
int CMD_set_pos(int argc, char **argv);
int CMD_set_stop(int argc, char **argv);
int CMD_get_encoder(int argc, char **argv);
//*****************************************************************************
//
// Table of valid command strings, callback functions and help messages.  This
// is used by the cmdline module.
//
//*****************************************************************************
tCmdLineEntry g_psCmdTable[] =
{
    {"help",     CMD_help,           " : Display list of commands" },
    {"sp",       CMD_set_speed,      " : Set speed of PD4 motor" },
    {"ep",       CMD_set_stop,       " : Stop PD4 motor" },
    {"so",       CMD_set_pos,        " : Set position of PD4 motor" },
    {"pe",       CMD_get_encoder,    " : Get Encoder of Y" },
    { 0, 0, 0 }
};

//*****************************************************************************
//
// Command: help
//
// Print the help strings for all commands.
//
//*****************************************************************************
int
CMD_help(int argc, char **argv)
{
    int32_t i32Index;

    (void)argc;
    (void)argv;

    //
    // Start at the beginning of the command table
    //
    i32Index = 0;

    //
    // Get to the start of a clean line on the serial output.
    //
    UARTprintf("\nAvailable Commands\n------------------\n\n");

    //
    // Display strings until we run out of them.
    //
    while(g_psCmdTable[i32Index].pcCmd)
    {
      UARTprintf("%17s %s\n", g_psCmdTable[i32Index].pcCmd,
                 g_psCmdTable[i32Index].pcHelp);
      i32Index++;
    }

    //
    // Leave a blank line after the help strings.
    //
    UARTprintf("\n");

    return (0);
}

int
CMD_set_speed(int argc, char **argv)
{
    uint8_t  NodeId;
    uint32_t Speed;

    //
    // This command requires one parameter.
    //
    if(argc == 3)
    {
        //
        // Extract the required color from the command line parameter.
        //
        NodeId = ustrtoul(argv[1], 0, 0);
        Speed = ustrtoul(argv[2], 0, 16);
        PD4Master_set_speed(NodeId, Speed);
    }

    return (0);

}

int
CMD_set_pos(int argc, char **argv)
{
    uint8_t  NodeId;
    int      pos;

    //
    // This command requires one parameter.
    //
    if(argc == 3)
    {
        //
        // Extract the required color from the command line parameter.
        //
        NodeId = ustrtoul(argv[1], 0, 0);
        pos = ustrtoul(argv[2], 0, 16);
        PD4Master_set_pos(NodeId, pos);
    }

    return (0);

}


int
CMD_set_stop(int argc, char **argv)
{
    uint8_t  NodeId;

    //
    // This command requires one parameter.
    //
    if(argc == 2)
    {
        //
        // Extract the required color from the command line parameter.
        //
        NodeId = (uint8_t)ustrtoul(argv[1], 0, 0);
        PD4Master_stop(NodeId);
    }

    return (0);

}


int
CMD_get_encoder(int argc, char **argv)
{
    MA3_encoder_print_value();
    return (0);
}
