#include "GPS.h"
#include "project.h"

#define GPS_Send GPS_UART_UartPutString
#define DEBUG_Send USB_DEBUG_UartPutString


//  =========================================================
//  ||                       gps_init				 	   ||
//  =========================================================
void gps_init( void )
{
    UART_CLOCK_Start();
    GPS_UART_Start(); //initializes the UART communications
    
	GPS_Send(PMTK_CMD_HOT_START); //Initializes GPS into "hot start" mode
    GPS_Send(PMTK_SET_NMEA_UPDATE_10HZ); //sets transmission rate to 10Hz
    GPS_Send(PMTK_SET_NMEA_OUTPUT_GGAONLY); //sets custom output parameters to shorten packet size
    
    GPS_Send(PMTK_SET_NMEA_BAUD_57600); //increases baudrate of GPS to turbocharge the data transfer
    UART_CLOCK_SetDivider(416); //sets baudrate of UART to match GPS
}


//  =========================================================
//  ||                      gps_parseHex			 	   ||
//  =========================================================
char gps_parseHex(char c) 
{
    if ( c < '0' )
      return 0;
    if ( c <= '9' )
      return c - '0';
    if ( c < 'A' )
       return 0;
    if ( c <= 'F' )
       return ( c - 'A' ) + 10;
	return 0;
}


//  =========================================================
//  ||                   gps_parseChecksum				   ||
//  =========================================================
char gps_parseChecksum( char* checksum )
{
	char hex = 0;
	hex += 16 * gps_parseHex( checksum[0] );
	hex += gps_parseHex( checksum[1] );
	return hex;
}


//  =========================================================
//  ||                 gps_calcNMEAChecksum				   ||
//  =========================================================
char gps_calcNMEAChecksum( char* str )
{
	int len, sum, i;
	
	sum = 0;
	len = strlen( str );
	for ( i = 0; i < len - 4; i++ )
		sum ^= str[ i + 1 ];
	return sum;	
}


//  =========================================================
//  ||                   gps_validateNMEA				   ||
//  =========================================================
int gps_validateNMEA( char* nmea )
{
	char targetChecksum = gps_parseChecksum( nmea + ( strlen(nmea) - 2 ) );

	if ( targetChecksum == gps_calcNMEAChecksum( nmea ) )
		return 1;
	return 0;
}


//  =========================================================
//  ||                    gps_parseNMEA				   ||
//  =========================================================
int gps_parseNMEA( char* nmea, struct GPS_Str_Data *gps )
{
	char *ptr, *nmeaStart;

	// Validate NMEA sentence header
	if ( ( nmeaStart = strstr ( nmea, "$GPGGA" ) ) == NULL )
		return 0;
    
	// validate Checksum
	if (!gps_validateNMEA( nmeaStart ) )
		return 0;

	// Separate the sentence by commas	
	ptr = strtok ( nmeaStart, "," );

	// FastFwd to latitude
	ptr = strtok ( NULL, "," );
	ptr = strtok ( NULL, "," );
	strcpy( gps->latitude, ptr );

	// Latitude cardinal
	ptr = strtok ( NULL, "," );
	strcpy( gps->latCardinal, ptr );

	// Longitude
	ptr = strtok ( NULL, "," );
	strcpy( gps->longitude, ptr );
    
	// Longitude cardinal
	ptr = strtok ( NULL, "," );
	strcpy( gps->lonCardinal, ptr );
    
	// Fix
	ptr = strtok ( NULL, "," );
	strcpy( gps->fix, ptr );
	return 1;
}


//  =========================================================
//  ||                    gps_parseData					   ||
//  =========================================================
struct GPS_Data gps_parseData( struct GPS_Str_Data *strData )
{
	// Convert the struct of strings to a struct of integral types
	struct GPS_Data gpsData;
	
	// ===== Latitude =====
	gpsData.latitude = atof( strData->latitude );
	// Negate if Southern hempisphere	
	if ( strData->latCardinal[0] == 'S' )
		gpsData.latitude *= -1;

	// Convert from NMEA Minute form to pure decimal
	gpsData.latitude =  gps_minsToDec( gpsData.latitude );

	// ===== Longitude =====
	gpsData.longitude = atof( strData->longitude );
	// Negate if Western hempisphere	
	if ( strData->lonCardinal[0] == 'W' )
		gpsData.longitude *= -1;

	// Convert from NMEA Minute form to pure decimal
	gpsData.longitude =  gps_minsToDec( gpsData.longitude );

	gpsData.fix = atoi( strData->fix );
	return gpsData;
}



//  =========================================================
//  ||                    gps_getData 					   ||
//  =========================================================
int gps_getData( struct GPS_Str_Data *gpsData )
{
	// result will be summed with any successful NMEA parses	
	int result = 0;
	char string[255];

	while (GPS_UART_SpiUartGetRxBufferSize()) //checks through all bytes in the buffer
	{	
        GPS_Recv(string, 255);		                //packet is stored in string array
		result += gps_parseNMEA( string, gpsData ); //if packet has location info result will store 1
        if (result)
        {
            break;
        }
	}
	return result;
}



//  =========================================================
//  ||                    gps_minsToDec					   ||
//  =========================================================
// Convert the GPS lat/lon format from DDMM.MMMM to decimal
double gps_minsToDec(double coord)
{
	int degree = coord / 100;
	return (coord - degree * 100) / 60 + degree;
}

//  =========================================================
//  ||                    GPS_Recv      				   ||
//  =========================================================
//Parses incoming data from the GPS
void GPS_Recv(char myString[], int maxLength) 
{
  char response;
  int i;
  i = 0;
    
  while (i < (maxLength - 1)) /* prevent over-runs */
  {                   
    response = GPS_UART_UartGetByte();
    
    if (response == '\r') /* enter marks the end */
    {                     
      break;
    }
    else if (!((response >= ' ') && (response <= '~'))){
        //Not an ASCII character that we care about
    }
    else 
    {
      myString[i] = response;                       /* add in a letter */
      i++;
    }
  }
  myString[i] = 0;                          /* terminal NULL character */
}




