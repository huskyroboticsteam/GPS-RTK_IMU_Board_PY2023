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
#include "project.h"
#include "main.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    

    for(;;)
    {
        /* Place your application code here. */
        // this is already fully functional for the GPS?
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
                    //Print("Packet Found!\r\n");
                    if (DecodeTelemetryType( &receive ) == GPS_LON)
                    {
                        /*
                        Print("LONGITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n\r\n");
                        */
                        state = PULL_LAT;
                    }
                    else if (DecodeTelemetryType ( &receive ) == GPS_LAT)
                    {
                        /*
                        Print("LATITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n");
                        */
                        state = PULL_LON;
                    }
                    else {
                        /*
                        Print("BAD PACKET\r\n");
                        PrintInt(DecodeTelemetryType( &receive ));
                        Print("\r\n");
                        PrintInt(GetSenderDeviceGroupCode( &receive ));
                        Print("\r\n");
                        Print("\r\n");
                        */
                    }  
                }
            
                break;
        
        }
        
    }
}

/* [] END OF FILE */
