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
            case(PULL_ACC):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, IMU_ACC);
                SendCANPacket( &send );
                state = WAIT;
                break;
                
            case(PULL_ANGVEL):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, IMU_ANGVEL);
                SendCANPacket( &send );
                state = WAIT;
                break;
            case(PULL_MAGF):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, IMU_MAGF);
                SendCANPacket( &send) ;
                state = WAIT;
                break;
            case(PULL_TEMP):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, IMU_TEMP);
                SendCANPacket( &send) ;
                state = WAIT;
                break;                
            case(PULL_VEL):
                AssembleTelemetryPullPacket(&send, DEVICE_GROUP_TELEMETRY, DEVICE_SERIAL_TELEM_LOCALIZATION, IMU_VEL);
                SendCANPacket( &send) ;
                state = WAIT;
                break;
                
            case(WAIT):
                if (PollAndReceiveCANPacket( &receive ) == ERROR_NONE)
                {
                    //Print("Packet Found!\r\n");
                    if (DecodeTelemetryType( &receive ) == IMU_ACC)
                    {
                        /*
                        Print("LONGITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n\r\n");
                        */
                        state = PULL_ACC;
                    }
                    else if (DecodeTelemetryType ( &receive ) == IMU_ANGVEL)
                    {
                        /*
                        Print("LATITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n");
                        */
                        state = PULL_ANGVEL;
                    }
                    else if (DecodeTelemetryType ( &receive ) == IMU_MAGF)
                    {
                        /*
                        Print("LATITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n");
                        */
                        state = PULL_MAGF;
                    }
                    else if (DecodeTelemetryType ( &receive ) == IMU_TEMP)
                    {
                        /*
                        Print("LATITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n");
                        */
                        state = PULL_TEMP;
                    }
                    else if (DecodeTelemetryType ( &receive ) == IMU_VEL)
                    {
                        /*
                        Print("LATITUDE: ");
                        PrintInt(DecodeTelemetryDataSigned( &receive ));
                        Print("\r\n");
                        */
                        state = PULL_VEL;
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
