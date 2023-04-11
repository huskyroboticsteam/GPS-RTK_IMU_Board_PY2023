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



#include "CANIMU.h"

void AssembleReadDataPacket (CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t dataType)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_READ_DATA;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_READ_DATA);
    packetToAssemble->data[nextByte] = dataType;

        
}

void AssembleSendDataPacket (CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t dataType,
    int32_t data) {

    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_DATA;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_DATA);
    packetToAssemble->data[nextByte] = dataType;  
    PackIntIntoDataMSBFirst(packetToAssemble->data, data, nextByte + 1);
        
}
    
uint8_t GetDataTypeFromReadPacket (CANPacket *packet) {
    
    if (packet->data[0] != ID_IMU_READ_DATA) {
     
        return 0;
        
    }
    
    return packet->data[1];
    
}

void AssembleReadOprModePacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial)
{

    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_READ_OPR_MODE;
    WritePacketIDOnly(packetToAssemble->data, ID_IMU_READ_OPR_MODE);
    
}

void AssembleWriteOprModePacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t operationMode) 

{
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_WRITE_OPR_MODE;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_WRITE_OPR_MODE);    
    packetToAssemble->data[nextByte] = operationMode;

}

void AssembleSendOprModePacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t operationMode) 

{
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_OPR_MODE;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_OPR_MODE);    
    packetToAssemble->data[nextByte] = operationMode;

}

uint8_t GetOprModeFromPacket(CANPacket *packet) {
 
    if (packet->data[0] != ID_IMU_READ_OPR_MODE) {
        
        return 0;
        
    }
    
    return packet->data[1];
    
}

void AssembleQueryCalibStatPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial)
{

    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_QUERY_CALIB_STAT;
    WritePacketIDOnly(packetToAssemble->data, ID_IMU_QUERY_CALIB_STAT);

}

void AssembleSendCalibStatPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    uint8_t calibStat) 
{
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_CALIB_STAT;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_CALIB_STAT);
    packetToAssemble->data[1] = calibStat;
        
}

uint8_t GetCalibStatFromPacket (CANPacket *packet)
{

    if (packet->data[0] != ID_IMU_QUERY_CALIB_STAT) {
     
        return 0;
        
    }
    
    return packet->data[1];
    
}

void AssembleReadAccOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial)
{
 
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_READ_ACC_OFFSET;
    WritePacketIDOnly(packetToAssemble->data, ID_IMU_READ_ACC_OFFSET);
    
}

void AssembleReadMagOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial)
{

    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_READ_MAG_OFFSET;
    WritePacketIDOnly(packetToAssemble->data, ID_IMU_READ_MAG_OFFSET);
    
}

void AssembleReadGyroOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_READ_GYRO_OFFSET;
    WritePacketIDOnly(packetToAssemble->data, ID_IMU_READ_GYRO_OFFSET);
    
}

void AssembleReadRadiusOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial)

{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_READ_RADIUS_OFFSET;
    WritePacketIDOnly(packetToAssemble->data, ID_IMU_READ_RADIUS_OFFSET);
    
}

void AssembleWriteAccOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_WRITE_ACC_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_WRITE_ACC_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, xOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, yOffset, nextByte + 2);
    PackShortIntoDataMSBFirst(packetToAssemble->data, zOffset, nextByte + 4);
    
}

void AssembleWriteMagOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_WRITE_MAG_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_WRITE_MAG_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, xOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, yOffset, nextByte + 2);
    PackShortIntoDataMSBFirst(packetToAssemble->data, zOffset, nextByte + 4);
    
}

void AssembleWriteGyroOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_WRITE_GYRO_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_WRITE_GYRO_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, xOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, yOffset, nextByte + 2);
    PackShortIntoDataMSBFirst(packetToAssemble->data, zOffset, nextByte + 4);
    
}

void AssembleWriteRadiusOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t accOffset,
    int16_t magOffset) 
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_WRITE_RADIUS_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_WRITE_RADIUS_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, accOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, magOffset, nextByte + 2);
    
}

void AssembleSendAccOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_ACC_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_ACC_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, xOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, yOffset, nextByte + 2);
    PackShortIntoDataMSBFirst(packetToAssemble->data, zOffset, nextByte + 4);
    
}

void AssembleSendMagOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_MAG_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_MAG_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, xOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, yOffset, nextByte + 2);
    PackShortIntoDataMSBFirst(packetToAssemble->data, zOffset, nextByte + 4);
    
}

void AssembleSendGyroOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t xOffset,
    int16_t yOffset,
    int16_t zOffset)
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_GYRO_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_GYRO_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, xOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, yOffset, nextByte + 2);
    PackShortIntoDataMSBFirst(packetToAssemble->data, zOffset, nextByte + 4);
    
}

void AssembleSendRadiusOffsetPacket(CANPacket *packetToAssemble,
    uint8_t targetGroup,
    uint8_t targetSerial,
    int16_t accOffset,
    int16_t magOffset) 
{
    
    packetToAssemble->id = ConstructCANID(PACKET_PRIORITY_NORMAL, targetGroup, targetSerial);
    packetToAssemble->dlc = DLC_IMU_SEND_RADIUS_OFFSET;
    int nextByte = WritePacketIDOnly(packetToAssemble->data, ID_IMU_SEND_RADIUS_OFFSET);
    PackShortIntoDataMSBFirst(packetToAssemble->data, accOffset, nextByte);
    PackShortIntoDataMSBFirst(packetToAssemble->data, magOffset, nextByte + 2);
    
}

IMUOffset GetOffsetFromPacket(CANPacket *packet)
{
    
    if (packet->data[0] != ID_IMU_READ_ACC_OFFSET && packet->data[0] != ID_IMU_READ_GYRO_OFFSET
        && packet->data[0] != ID_IMU_READ_MAG_OFFSET) {
            
        IMUOffset offset = {0, 0, 0};
  
        return offset;   
            
    }
    
    IMUOffset offsets;
    
    offsets.xOffset = (int16_t) DecodeBytesToIntMSBFirst(packet->data, 0, 1);
    offsets.yOffset = (int16_t) DecodeBytesToIntMSBFirst(packet->data, 2, 3);
    offsets.zOffset = (int16_t) DecodeBytesToIntMSBFirst(packet->data, 4, 5);
    
    return offsets;
    
}

IMURadiusOffset GetRadiusOffsetFromPacket(CANPacket *packet)
{
    
    if (packet->data[0] != ID_IMU_READ_RADIUS_OFFSET) {
     
        IMURadiusOffset offset = {0, 0};
        
        return offset;
        
    }

    IMURadiusOffset offsets;
    
    offsets.accOffset = (int16_t) DecodeBytesToIntMSBFirst(packet->data, 0, 1);
    offsets.magOffset = (int16_t) DecodeBytesToIntMSBFirst(packet->data, 2, 3);
    
    return offsets;
    
}


/* [] END OF FILE */