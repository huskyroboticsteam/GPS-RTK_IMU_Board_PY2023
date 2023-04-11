/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#include "CANPacket.h"

typedef struct IMUOffset {
 
    int16_t xOffset;
    int16_t yOffset;
    int16_t zOffset;
    
} IMUOffset;

typedef struct IMURadiusOffest {
    
    int16_t accOffset;
    int16_t magOffset;
    
} IMURadiusOffset;


// Functions for creating packets for reading and sending data

void AssembleReadDataPacket (CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t dataType);

void AssembleSendDataPacket (CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t dataType,
    int32_t data);

uint8_t GetDataTypeFromReadPacket (CANPacket *packet);

// Functions for creating packets for reading, writing, and sending data 
// regarding the operation mode of the sensor

void AssembleReadOprModePacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial);

void AssembleWriteOprModePacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t operationMode);

void AssembleSendOprModePacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t operationMode);

uint8_t GetOprModeFromPacket(CANPacket *packet);


// Functions for creating packets for reading and sending data for the calibration status

void AssembleQueryCalibStatPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial);

void AssembleSendCalibStatPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t calibStat);

uint8_t GetCalibStatFromPacket (CANPacket *packet);


// Functions for creating packets for reading, writing, and sending sensor offset data

void AssembleReadAccOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial);

void AssembleReadMagOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial);

void AssembleReadGyroOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial);

void AssembleReadRadiusOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial);

void AssembleWriteAccOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset);

void AssembleWriteMagOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset);

void AssembleWriteGyroOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset);

void AssembleWriteRadiusOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t accOffset,
    int16_t magOffset);

void AssembleSendAccOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset);

void AssembleSendMagOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset);

void AssembleSendGyroOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset);

void AssembleSendRadiusOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t accOffset,
    int16_t magOffset);


// Reading xOffset, yOffset, zOffset data from offset packets except radius offset packets

IMUOffset GetOffsetFromPacket(CANPacket *packet);

// Reading accOffset and magOffset for radius offset packets

IMURadiusOffset GetRadiusOffsetFromPacket(CANPacket *packet);


// IMU Packet IDs

#define ID_IMU_READ_DATA            (uint8_t) 0x01
#define ID_IMU_SEND_DATA            (uint8_t) 0x02
#define ID_IMU_READ_OPR_MODE        (uint8_t) 0x11
#define ID_IMU_WRITE_OPR_MODE       (uint8_t) 0x12
#define ID_IMU_SEND_OPR_MODE        (uint8_t) 0x13
#define ID_IMU_QUERY_CALIB_STAT     (uint8_t) 0x14
#define ID_IMU_SEND_CALIB_STAT      (uint8_t) 0x15
#define ID_IMU_READ_ACC_OFFSET      (uint8_t) 0x21
#define ID_IMU_READ_MAG_OFFSET      (uint8_t) 0x22
#define ID_IMU_READ_GYRO_OFFSET     (uint8_t) 0x23
#define ID_IMU_READ_RADIUS_OFFSET   (uint8_t) 0x24
#define ID_IMU_WRITE_ACC_OFFSET     (uint8_t) 0x25
#define ID_IMU_WRITE_MAG_OFFSET     (uint8_t) 0x26
#define ID_IMU_WRITE_GYRO_OFFSET    (uint8_t) 0x27
#define ID_IMU_WRITE_RADIUS_OFFSET  (uint8_t) 0x28
#define ID_IMU_SEND_ACC_OFFSET      (uint8_t) 0x29
#define ID_IMU_SEND_MAG_OFFSET      (uint8_t) 0x2A
#define ID_IMU_SEND_GYRO_OFFSET     (uint8_t) 0x2B
#define ID_IMU_SEND_RADIUS_OFFSET   (uint8_t) 0x2C

// IMU Packet Data Length Codes

#define DLC_IMU_READ_DATA           (uint8_t) 0x02
#define DLC_IMU_SEND_DATA           (uint8_t) 0x05
#define DLC_IMU_READ_OPR_MODE       (uint8_t) 0x01
#define DLC_IMU_WRITE_OPR_MODE      (uint8_t) 0x02
#define DLC_IMU_SEND_OPR_MODE       (uint8_t) 0x02
#define DLC_IMU_QUERY_CALIB_STAT    (uint8_t) 0x01
#define DLC_IMU_SEND_CALIB_STAT     (uint8_t) 0x02
#define DLC_IMU_READ_ACC_OFFSET     (uint8_t) 0x01
#define DLC_IMU_READ_MAG_OFFSET     (uint8_t) 0x01
#define DLC_IMU_READ_GYRO_OFFSET    (uint8_t) 0x01
#define DLC_IMU_READ_RADIUS_OFFSET  (uint8_t) 0x01
#define DLC_IMU_WRITE_ACC_OFFSET    (uint8_t) 0x07
#define DLC_IMU_WRITE_MAG_OFFSET    (uint8_t) 0x07
#define DLC_IMU_WRITE_GYRO_OFFSET   (uint8_t) 0x07
#define DLC_IMU_WRITE_RADIUS_OFFSET (uint8_t) 0x05
#define DLC_IMU_SEND_ACC_OFFSET     (uint8_t) 0x07
#define DLC_IMU_SEND_MAG_OFFSET     (uint8_t) 0x07
#define DLC_IMU_SEND_GYRO_OFFSET    (uint8_t) 0x07
#define DLC_IMU_SEND_RADIUS_OFFSET  (uint8_t) 0x05


/* [] END OF FILE */