/*
 * cmd_task.c
 *
 *  Created on: 2018Äê6ÔÂ18ÈÕ
 *      Author: cking
 */

#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"
#include "cmd_task.h"
#include "utils/cmdline.h"


#define APP_INPUT_BUF_SIZE 64
//*****************************************************************************
//
// Input buffer for the command line interpreter.
//
//*****************************************************************************
static char g_cInput[APP_INPUT_BUF_SIZE];

void cmd_task_period()
{
    int i32CommandStatus;


    //
    // Peek to see if a full command is ready for processing
    //
    if(UARTPeek('\r') == -1)
    {
        return;
    }
    //
    // a '\r' was detected get the line of text from the user.
    //
    UARTgets(g_cInput,sizeof(g_cInput));

    //
    // Pass the line from the user to the command processor.
    // It will be parsed and valid commands executed.
    //
    i32CommandStatus = CmdLineProcess(g_cInput);

    //
    // Handle the case of bad command.
    //
    if(i32CommandStatus == CMDLINE_BAD_CMD)
    {
        UARTprintf("Bad command!\n");
    }

    //
    // Handle the case of too many arguments.
    //
    else if(i32CommandStatus == CMDLINE_TOO_MANY_ARGS)
    {
        UARTprintf("Too many arguments for command processor!\n");
    }

    UARTprintf("\n>");
}
