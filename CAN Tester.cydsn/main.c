
#include "main.h"


void PrintCanPacket(CANPacket receivedPacket){
    for(int i = 0; i < receivedPacket.dlc; i++ ) {
        sprintf(txData,"Byte%d %x   ", i, receivedPacket.data[i]);
        Print(txData);
    }

    sprintf(txData,"ID:%x %x %x\r\n",receivedPacket.id >> 10, 
        (receivedPacket.id >> 6) & 0xF , receivedPacket.id & 0x3F);
    Print(txData);
}

int main(void)
{
    CyGlobalIntEnable;
    
    DEBUG_Start();
    InitCAN(DEVICE_GROUP_JETSON, DEVICE_SERIAL_JETSON);

    state = PULL_LAT;
    
    Print("\r\n***TESTING CAN COMMUNICATION WITH IMU BOARD***\r\n\r\n");
    
    for(;;)
    {
        switch(state)
        {
            case(PULL_LAT):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, GPS_LAT);
                SendCANPacket( &send );
                state = WAIT;
                break;
                
            case(PULL_LON):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, GPS_LON);
                SendCANPacket( &send );
                state = WAIT;
                break;
                
            case(WAIT):
                if (PollAndReceiveCANPacket( &receive ) == ERROR_NONE)
                {
                    Print("Packet Found!\r\n");
                    if (DecodeTelemetryType( &receive ) == GPS_LON)
                    {
                        Print("LONGITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n\r\n");
                        state = PULL_LAT;
                    }
                    else if (DecodeTelemetryType ( &receive ) == GPS_LAT)
                    {
                        Print("LATITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n");
                        state = PULL_LON;
                    }
                    else {
                        Print("BAD PACKET\r\n");
                        PrintInt(DecodeTelemetryType( &receive ));
                        Print("\r\n");
                        PrintInt(GetSenderDeviceGroupCode( &receive ));
                        Print("\r\n");
                        Print("\r\n");
                    }  
                }
            
                break;
        
        }
        
    }
}


