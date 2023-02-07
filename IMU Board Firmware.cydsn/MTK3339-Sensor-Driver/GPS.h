#ifndef GPS_H
#define GPS_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <GPS_UART.h>    


/* ========== Baud rate ========== */
#define PMTK_SET_NMEA_BAUD_4800 "$PMTK251,4800*14<CR><LF>"
#define PMTK_SET_NMEA_BAUD_9600 "$PMTK251,9600*17<CR><LF>"
#define PMTK_SET_NMEA_BAUD_57600 "$PMTK251,57600*2C<CR><LF>"

/* ========== Update rate ========== */
#define PMTK_SET_NMEA_UPDATE_10_SEC  "$PMTK220,10000*2F<CR><LF>" // Every 10 seconds 
#define PMTK_SET_NMEA_UPDATE_5_SEC  "$PMTK220,5000*1B<CR><LF>"  // Every 5 seconds
#define PMTK_SET_NMEA_UPDATE_1_SEC  "$PMTK220,1000*1F<CR><LF>" // Every second
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*1F<CR><LF>"   // Every 0.1 seconds

/* ========== System ========== */
#define PMTK_CMD_HOT_START "$PMTK101*32<CR><LF>" // Reboot
#define PMTK_CMD_COLD_START "$PMTK103*30<CR><LF>" //Start up
#define PMTK_CMD_STANDBY_MODE "$PMTK161,0*28<CR><LF>" // Standby


/* ========== Output format ========== */
/* Enable Recommended Minimum Sentence and GPS Fix data ( RMC and GGA )*/
#define PMTK_SET_NMEA_OUTPUT_DEFAULT "$PMTK314,-1*04<CR><LF>"
#define PMTK_SET_NMEA_OUTPUT_GGAONLY "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29<CR><LF>"
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28<CR><LF>"
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29<CR><LF>"
#define PMTK_SET_NMEA_OUTPUT_CUSTOM "$PMTK314,1,1,1,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0*2C<CR><LF>" 

#define PMTK_TEST_PACKET "$PMTK000*32<CR><LF>" 
    
#define DEG_PER_MIN .016666667f
struct GPS_Str_Data
{
	char latitude[16];
	char longitude[16];
	char latCardinal[2];
	char lonCardinal[2];	
	char fix[2];
};

struct GPS_Data
{
	float latitude;
	float longitude;
	int fix;
};


//Initializes the gps over UART. 
void gps_init( void );

//Parses character hex value
char gps_parseHex(char c);

//Parses GPS checksum
char gps_parseChecksum( char* checksum );

//Calculates NMEA checksum
char gps_calcNMEAChecksum( char* str );

//Returns 0 if NMEA packet isn't validated by checksum, 1 if it is validated
int gps_validateNMEA( char* nmea );

//Parses NMEA packet into GPS_Str_Data struct
int gps_parseNMEA( char* nmea, struct GPS_Str_Data *gps );

//Parses string gps data and returns GPS_Data containing float values of longitude and latitude
struct GPS_Data gps_parseData( struct GPS_Str_Data *strData );

//Attempts to add newest gps data to gpsData. Returns 1 on successs, 0 on failure
int gps_getData( struct GPS_Str_Data *gpsData );

//Converts the GPS lat/lon format from DDMM.MMMM to decimal
double gps_minsToDec(double coord);

//Stores data in the rx buffer into char myString[]
void GPS_Recv(char myString[], int maxLength);

#endif