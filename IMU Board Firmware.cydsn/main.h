#include "project.h"
#include "GPS.h"
#include "IMUDriver.h"
#include "CANLibrary.h"
#include "CANIMU.h"


#define CHIP_TYPE CHIP_TYPE_PSOC_CY8C4248AZI_L485


//Debugging macros
#define Print(message) DBG_UART_UartPutString(message)
#define PrintChar(character) DBG_UART_UartPutChar(character)
#define PrintInt(integer) DBG_UART_UartPutString(itoa(integer, debugOutput, 10))
#define PrintIntBin(integer) DBG_UART_UartPutString(itoa(integer, debugOutput, 2))
#define BlinkDBG() DBG_Write( ! DBG_Read() )

char debugOutput[32];


//Switch values for FSM states
#define IDLE         0
#define CHECK_CAN    1
#define SEND_CAN     2
#define READ_SENSORS 3
#define STORE_DATA   4

int state = IDLE;


//Switch values for info request
#define ANG_POS 0x04

#define GPS_LAT 0x05
#define GPS_LON 0x06

#define ACCEL_X 0x08
#define ACCEL_Y 0x09
#define ACCEL_Z 0x0A

#define GYRO_X  0x0B
#define GYRO_Y  0x0C
#define GYRO_Z  0x0D

#define QUAT_W  0x12
#define QUAT_X  0x13
#define QUAT_Y  0x14
#define QUAT_Z  0x15


//Structs for holding GPS data
struct GPS_Str_Data gpsRawData;
struct GPS_Data gpsData;


//Global CAN related variables
CANPacket send;
CANPacket receive;


//Take a wild guess at what this function does
int getSerialAddress();


//Sends CAN packet with data that the TTC calls for
void sendRequestedData();


// IMU Packet Handling

void readOperationMode();

void writeOperationMode(uint8_t mode);

void queryCalibrationStatus();

void readAccOffset();

void readMagOffset();

void readGyroOffset();

void readRadiusOffset();

void writeAccOffset(int16_t xOffset, int16_t yOffset, int16_t zOffset);

void writeMagOffset(int16_t xOffset, int16_t yOffset, int16_t zOffset);

void writeGyroOffset(int16_t xOffset, int16_t yOffset, int16_t zOffset);

void writeRadiusOffset(int16_t accOffset, int16_t magOffset);

