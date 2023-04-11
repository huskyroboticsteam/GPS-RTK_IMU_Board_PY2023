
#include "project.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "Port.h"
#include "CANCommon.h"
#include "CANPacket.h"

#define CHIP_TYPE CHIP_TYPE_PSOC_CY8C4248AZI_L485

//Debugging macros
#define Print(message) DEBUG_UartPutString(message)
#define PrintChar(character) DEBUG_UartPutChar(character)
#define PrintInt(integer) DEBUG_UartPutString(itoa(integer, debugOutput, 10))
#define PrintIntBin(integer) DEBUG_UartPutString(itoa(integer, debugOutput, 2))

char debugOutput[32];

//Global CAN Packets
CANPacket send;
CANPacket receive;

//TTCs
#define GPS_LAT 0x05
#define GPS_LON 0x06

//switch cases
#define PULL_LAT 0
#define PULL_LON 1
#define WAIT     2
#define READ_LAT 3
#define READ_LON 4

int state;

char txData[4];