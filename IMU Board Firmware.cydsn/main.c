
/*
Davis Sauer
Husky Robotics
2021
This program continuously checks the GPS and IMU sensors for sensor data
and then reports that information when requested over CAN
*/

/* 
Terence Sinn
Husky Robotics
2022-2023
Added functionality to control calibration, operation modes, and sensor offset data.
*/

#include "main.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    DBG_UART_Start();
    InitCAN(DEVICE_GROUP_IMU, getSerialAddress() );
    gps_init();    
    imu_init();
           
    Print("\r\n");
    Print("\r\n***************\r\nIMU BOARD INITIALIZED\n\r***************\r\n");
    
    writeAccOffset(1, 2, 3);
    writeMagOffset(4, 5, 6);
    
    int i;
    
    for (i = 1; i <= 5; i++) {
   
        writeRadiusOffset(i * 10, i * 10);
        readRadiusOffset();
        
    }
    
    int status;
    
    for(;;)
    {
    /*    
        switch(state)
        {
            //Checks for can packet addressed to this board
            //if found, send requested data then read sensors, if not, read sensors
            case(IDLE):
            
                //sendRequestedData(TTC);
                if (PollAndReceiveCANPacket( &receive ) == ERROR_NONE)
                {
                    Print("Packet Found!\r\n");
                    
                    int packetID = GetPacketID( &receive );
                    
                    switch (packetID)
                    {
        
                        // Deprecated
                        case(ID_TELEMETRY_PULL):
                        {
                        
                            uint8_t TTC = DecodeTelemetryType( &receive );
                            Print("Sending CAN Packet...\r\n");      
                            sendRequestedData(TTC); 
                            break;
                            
                        }
        
                        case (ID_IMU_READ_DATA):
                        
                        {
        
                            uint8_t dataType = GetDataTypeFromReadPacket( &receive );
                            sendRequestedData(dataType);
        
                            break;
        
                        }
                        
                        case(ID_IMU_READ_OPR_MODE):
                        {
                         
                            readOperationMode();
                            break;
                            
                        }
                        
                        case(ID_IMU_WRITE_OPR_MODE):
                        {
                            
                            writeOperationMode(GetOprModeFromPacket(&receive));
                            break;
                            
                        }
                        
                        case(ID_IMU_QUERY_CALIB_STAT):
                        {
                         
                            queryCalibrationStatus();
                            break;
                            
                        }
                        
                        case(ID_IMU_READ_ACC_OFFSET):
                        {
                         
                            readAccOffset();
                            break;
                            
                        }
                        
                        case(ID_IMU_READ_MAG_OFFSET):
                        {
                         
                            readMagOffset();
                            break;
                            
                        }
                        
                        case(ID_IMU_READ_GYRO_OFFSET):
                        {
                         
                            readGyroOffset();
                            break;
                            
                        }
                        
                        case(ID_IMU_READ_RADIUS_OFFSET):
                        {
                         
                            readRadiusOffset();
                            break;
                            
                        }
                        
                        case (ID_IMU_WRITE_ACC_OFFSET):
                        {
                         
                            IMUOffset offset = GetOffsetFromPacket(&receive);
                            writeAccOffset(offset.xOffset, offset.yOffset, offset.zOffset);
                            break;
                            
                        }
                        
                        case (ID_IMU_WRITE_MAG_OFFSET):
                        {
                         
                            IMUOffset offset = GetOffsetFromPacket(&receive);
                            writeMagOffset(offset.xOffset, offset.yOffset, offset.zOffset);
                            break;
                            
                        }
                        
                        case (ID_IMU_WRITE_GYRO_OFFSET):
                        {
                         
                            IMUOffset offset = GetOffsetFromPacket(&receive);
                            writeGyroOffset(offset.xOffset, offset.yOffset, offset.zOffset);
                            break;
                            
                        }
                        
                        case (ID_IMU_WRITE_RADIUS_OFFSET):
                        {
                         
                            IMURadiusOffset offset = GetRadiusOffsetFromPacket(&receive);
                            writeRadiusOffset(offset.accOffset, offset.magOffset);
                            break;
                            
                        }
                                        
                    }
                    
                }
                
                //flip between checking can and checking sensors
                state = READ_SENSORS;
            
                break;
            
            //Polls GPS and IMU for current sensor data
            case(READ_SENSORS):
                
                //Checking if packet from gps is location info                
        	    if (gps_getData( &gpsRawData ))
                {
                    //Parse string data into ints and floats
        	        gpsData = gps_parseData( &gpsRawData );  
                }
                
                //use the provided api to read data
                bno055_data_readout_template(); 
                
                
                
                //print out values from gps data
                Print("\r\n");
                Print("\n\rFix: ");
                PrintInt((gpsData.fix));
                Print("\n\rLatitude: ");
                PrintInt((gpsData.latitude));
                Print("\n\rLongitude: ");
                PrintInt((gpsData.longitude));
                Print("\r\n\r\n");
                
                //print out values from imu data
                Print("\r\n");
                Print("\n\rLinear Accel x: ");
                PrintInt((d_linear_accel_datax));
                Print("\n\rLinear Accel y: ");
                PrintInt((d_linear_accel_datay));
                Print("\n\rLinear Accel z: ");
                PrintInt((d_linear_accel_dataz));
                
                Print("\r\n");
                Print("\n\rGyro Veloc x: ");
                PrintInt((int)(d_gyro_datax));
                Print("\n\rGyro Veloc y: ");
                PrintInt((int)(d_gyro_datay));
                Print("\n\rGyro Veloc z: ");
                PrintInt((int)(d_gyro_dataz));
                
                Print("\r\n");
                Print("\n\rYaw: ");
                PrintInt((int)(d_euler_data_h));
                Print("\n\rPitch: ");
                PrintInt((int)(d_euler_data_p));
                Print("\n\rRoll: ");
                PrintInt((int)(d_euler_data_r));
                
                Print("\r\n");
                Print("\n\rQuat w: ");
                PrintInt((int)(quaternion_data_w));
                Print("\n\rQuat x: ");
                PrintInt((int)(quaternion_data_x));
                Print("\n\rQuat y: ");
                PrintInt((int)(quaternion_data_y));
                Print("\n\rQuat z: ");
                PrintInt((int)(quaternion_data_z));
                Print("\r\n\r\n");
                
               
                
                state = IDLE;
                break;
                
        }
        
        */
    }
}

//Reads dip switches to calculate the serial address
int getSerialAddress()
{
    int address = 0;
    if (DIP1_Read()==0)
        address += 1;
  
    if (DIP2_Read()==0)
        address += 2;

    if (DIP3_Read()==0)
        address += 4;

    if (DIP4_Read()==0)
        address += 8;
    
    if (address == 0)
        address = DEVICE_SERIAL_TELEM_LOCALIZATION;
    
    return address;
}

//Using the Telemetry Type Code (TTC), sends appropriate data to respond
//to a telemetry request

void sendRequestedData(int TTC)
{
    int32_t data = 0;
    
    switch(TTC)
    {
        case(ANG_POS):
            //int32 (signed). Reading in degrees * 1000
            data = (int32_t) d_euler_data_h * 1000;
            break;
        
        case(GPS_LAT):
            data = (uint32_t)(gpsData.latitude + 90) * 10000000;
            break;
        
        case(GPS_LON):
            data = (uint32_t)(gpsData.longitude + 180) * 10000000;
            break;
            
        case(ACCEL_X):
            //int32 (signed). Acceleration in m/s/s * 1000
            data = (int32_t) (linear_accel_data_x * 1000);
            break;
        
        case(ACCEL_Y):
            //int32 (signed). Acceleration in m/s/s * 1000
            data = (int32_t) (linear_accel_data_y * 1000);
            break;
        
        case(ACCEL_Z):
            //int32 (signed). Acceleration in m/s/s * 1000
            data = (int32_t) (linear_accel_data_z * 1000);
            break;
        
        case(GYRO_X):
            //int32 (signed). Degrees per second * 1000
            data = (int32_t) d_gyro_datax * 1000;
            break;
        
        case(GYRO_Y):
            //int32 (signed). Degrees per second * 1000
            data = (int32_t) d_gyro_datax * 1000;
            break;
        
        case(GYRO_Z):
            //int32 (signed). Degrees per second * 1000
            data = (int32_t) d_gyro_datax * 1000;
            break;
        
        case(QUAT_W):
            data = (int32_t) quaternion_data_w;
            break;
            
        case(QUAT_X):
            data = (int32_t) quaternion_data_x;
            break;
            
        case(QUAT_Y):
            data = (int32_t) quaternion_data_y;
            break;
            
        case(QUAT_Z):
            data = (int32_t) quaternion_data_z;
            break;
        default:
            Print("Cannot Send That Data Type!\n\r");
    }   
    
    CANPacket send;
    
    AssembleSendDataPacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, TTC, data);
    int check = SendCANPacket( &send );
    
    if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
    }
}

void readOperationMode () 
{
    uint8_t mode;
    
    if (!bno055_get_operation_mode(&mode)) {
     
        Print("Operation Mode: ");
        PrintInt(mode);
        Print("\r\n\r\n");
        
        /*
        
        CANPacket send;
        
        AssembleSendOprModePacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, mode);
        
        int check = SendCANPacket (&send);

        if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
        }
        
        */
    
    }
    
}

void writeOperationMode (uint8_t mode)
{
    
    Print("Writing Operation Mode\r\n\r\n");
    
    if(bno055_set_operation_mode(mode)) {
     
        BlinkDBG();
        CyDelay(50);
        
    }
    
}

void queryCalibrationStatus()
{
    
    uint8_t calibStat;
    
    if (!bno055_get_sys_calib_stat(&calibStat)) {
     
        Print("CalibStat: ");
        PrintInt(calibStat);
        Print("\r\n\r\n");
        
        /*
        
        CANPacket send;
        
        AssembleSendCalibStatPacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, calibStat);
        
        int check = SendCANPacket (&send);

        if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
        }
        
        */
    
    }
    
    
}

void readAccOffset()
{
    struct bno055_accel_offset_t offset;
    
    if (!bno055_read_accel_offset(&offset)) {
        
        Print("Acceleration Offset\r\n");
        Print("X Offset: ");
        PrintInt(offset.x);
        Print(", Y Offset: ");
        PrintInt(offset.y);
        Print(", Z Offset: ");
        PrintInt(offset.z);
        Print("\r\n\r\n");
        
        /*
        
        CANPacket send;
        
        AssembleSendAccOffsetPacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, offset.x, offset.y, offset.z);
        
        int check = SendCANPacket (&send);

        if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
        }
        
        */
        
    }
    
}



void readMagOffset()
{

    struct bno055_mag_offset_t offset;
    
    if (!bno055_read_mag_offset(&offset)) {
     
        Print("Magnetometer Offset\r\n");
        Print("X Offset: ");
        PrintInt(offset.x);
        Print(", Y Offset: ");
        PrintInt(offset.y);
        Print(", Z Offset: ");
        PrintInt(offset.z);
        Print("\r\n\r\n");
        
        /*
        
        CANPacket send;
        
        AssembleSendMagOffsetPacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, offset.x, offset.y, offset.z);
        
        int check = SendCANPacket (&send);

        if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
        }
        
        */
        
    }
    
}


void readGyroOffset()
{

    struct bno055_gyro_offset_t offset;
    
    if (!bno055_read_gyro_offset(&offset)) {
     
        Print("Gyro Offset\r\n");
        Print("X Offset: ");
        PrintInt(offset.x);
        Print(", Y Offset: ");
        PrintInt(offset.y);
        Print(", Z Offset: ");
        PrintInt(offset.z);
        Print("\r\n\r\n");
        
        /*
        
        CANPacket send;
        
        AssembleSendGyroOffsetPacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, offset.x, offset.y, offset.z);
        
        int check = SendCANPacket (&send);

        if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
        }
        
        */
        
    }
    
}


void readRadiusOffset()
{

    struct bno055_accel_offset_t accOffset;
    struct bno055_mag_offset_t magOffset;
    
    if (!bno055_read_accel_offset(&accOffset) && !bno055_read_mag_offset(&magOffset)) {
     
        Print("Radius Offset\r\n");
        
        Print("AccOffset: ");
        PrintInt(accOffset.r);
        Print(", MagOffset: ");
        PrintInt(magOffset.r);
        Print("\r\n\r\n");
        
        
        /*
        
        CANPacket send;
        
        AssembleSendRadiusOffsetPacket(&send, DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON, accOffset.r, magOffset.r);
        
        int check = SendCANPacket (&send);

        if (check == ERROR_NONE){
        BlinkDBG();
        CyDelay(50);
        }
        
        */
        
    }
    
}


void writeAccOffset(int16_t xOffset, int16_t yOffset, int16_t zOffset)
{
    
    struct bno055_accel_offset_t offset;
    
    Print("Writing Acceleration Offset\r\n\r\n");
    
    if (!bno055_read_accel_offset(&offset)) {
     
        offset.x = xOffset;
        offset.y = yOffset;
        offset.z = zOffset;
        
        if (bno055_write_accel_offset(&offset)) {
         
            BlinkDBG();
            CyDelay(50);
            
        }
        
    }
    
}

void writeMagOffset(int16_t xOffset, int16_t yOffset, int16_t zOffset)
{
    
    Print("Writing Mag Offset\r\n\r\n");
    
    struct bno055_mag_offset_t offset;
    
    if (!bno055_read_mag_offset(&offset)) {
     
        offset.x = xOffset;
        offset.y = yOffset;
        offset.z = zOffset;
        
        if (bno055_write_mag_offset(&offset)) {
         
            BlinkDBG();
            CyDelay(50);
            
        }
        
    }
    
}

void writeGyroOffset(int16_t xOffset, int16_t yOffset, int16_t zOffset)
{

    Print("Writing Gyro Offset\r\n\r\n");
    
    struct bno055_gyro_offset_t offset = {xOffset, yOffset, zOffset};
    
    if (bno055_write_gyro_offset(&offset)) {
     
        BlinkDBG();
        CyDelay(50);
        
    }
    
}


void writeRadiusOffset(int16_t accOffset, int16_t magOffset)
{
    
    struct bno055_accel_offset_t acc;
    
    struct bno055_mag_offset_t mag;
    
    Print("Writing Radius Offset\r\n\r\n");
    
    if (!bno055_read_accel_offset(&acc) && !bno055_read_mag_offset(&mag)) {
        
        acc.r = accOffset;
        mag.r = magOffset;
        
        Print("Acc Offset\r\n");
        Print("X Offset: ");
        PrintInt(acc.x);
        Print(", Y Offset: ");
        PrintInt(acc.y);
        Print(", Z Offset: ");
        PrintInt(acc.z);
        Print(", R Offset: ");
        PrintInt(acc.r);
        Print("\r\n\r\n");
        
        Print("Mag Offset\r\n");
        Print("X Offset: ");
        PrintInt(mag.x);
        Print(", Y Offset: ");
        PrintInt(mag.y);
        Print(", Z Offset: ");
        PrintInt(mag.z);
        Print(", R Offset: ");
        PrintInt(mag.r);
        Print("\r\n\r\n"); 
        
        if (bno055_write_accel_offset(&acc)) {
         
            BlinkDBG();
            CyDelay(50);
            
        }
        
        readAccOffset();
        
        if (bno055_write_mag_offset(&mag)) {
         
            BlinkDBG();
            CyDelay(50);
            
        }
        
        readMagOffset();
        
    }
    
}

