/* ===========================================
 * Davis Sauer, Husky Robotics 2021
 *
 * UART INSTANCE NAME MUST BE "GPS_UART"
 * IN THE TOP DESIGN FILE AND SET BAUDRATE
 * TO 9600
 *
 * This file is a sample of how to initialize
 * the gps and then read from it when it has
 * new data. The use of the second UART is 
 * soley for debugging purposes.
 *
 * Since most of this code was "stolen" from
 * Joseph Fortune's github, under the beerware
 * licensing agreement, usage of this code
 * will cost you one drink if you are to ever 
 * meet Mr. Fortune in person. 
 * ===========================================
*/

#include "project.h"
#include "GPS.h"

int main(void)
{
    USB_DEBUG_UartPutString("***************\r\nGPS INITIALIZED\n\r***************\r\n");
    USB_DEBUG_Start(); 
    gps_init(); //initializes both UART communication and the GPS module
    struct GPS_Str_Data gpsRawData; // Data in string form
    struct GPS_Data gpsData; // Converted data

    for(;;)
    {   
	    //Checking if packet from gps is location info
	    if (gps_getData( &gpsRawData ))
        {
            //Parse string data into ints and floats
	        gpsData = gps_parseData( &gpsRawData );  
        }
        
        //Since the same struct is used every time, the gps fix will still be set to 1
        //with old data stored in the longitude and latitude fields. To only read new data
        //points from the gps, set fix to 0 after location data has been used.
        if (gpsData.fix)
        {
            //do stuff with gps data    
            USB_DEBUG_UartPutString("\n\rFix Found\n\r");
            
            USB_DEBUG_UartPutString("Lat = ");
            USB_DEBUG_UartPutString(gpsRawData.latitude);
            USB_DEBUG_UartPutString(" ");
            USB_DEBUG_UartPutString(gpsRawData.latCardinal);
            USB_DEBUG_UartPutCRLF(1);
            
            USB_DEBUG_UartPutString("Lon = ");
            USB_DEBUG_UartPutString(gpsRawData.longitude);
            USB_DEBUG_UartPutString(" ");
            USB_DEBUG_UartPutString(gpsRawData.lonCardinal);
            USB_DEBUG_UartPutCRLF(1);
            
            gpsData.fix = 0;
        }
        
    }
}



