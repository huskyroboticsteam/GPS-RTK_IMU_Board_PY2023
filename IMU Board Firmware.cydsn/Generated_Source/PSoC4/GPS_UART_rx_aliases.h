/*******************************************************************************
* File Name: GPS_UART_rx.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_GPS_UART_rx_ALIASES_H) /* Pins GPS_UART_rx_ALIASES_H */
#define CY_PINS_GPS_UART_rx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define GPS_UART_rx_0			(GPS_UART_rx__0__PC)
#define GPS_UART_rx_0_PS		(GPS_UART_rx__0__PS)
#define GPS_UART_rx_0_PC		(GPS_UART_rx__0__PC)
#define GPS_UART_rx_0_DR		(GPS_UART_rx__0__DR)
#define GPS_UART_rx_0_SHIFT	(GPS_UART_rx__0__SHIFT)
#define GPS_UART_rx_0_INTR	((uint16)((uint16)0x0003u << (GPS_UART_rx__0__SHIFT*2u)))

#define GPS_UART_rx_INTR_ALL	 ((uint16)(GPS_UART_rx_0_INTR))


#endif /* End Pins GPS_UART_rx_ALIASES_H */


/* [] END OF FILE */
