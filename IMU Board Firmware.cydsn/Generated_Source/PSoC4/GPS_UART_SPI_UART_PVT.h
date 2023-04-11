/***************************************************************************//**
* \file GPS_UART_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_GPS_UART_H)
#define CY_SCB_SPI_UART_PVT_GPS_UART_H

#include "GPS_UART_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (GPS_UART_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  GPS_UART_rxBufferHead;
    extern volatile uint32  GPS_UART_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   GPS_UART_rxBufferOverflow;
    /** @} globals */
#endif /* (GPS_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (GPS_UART_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  GPS_UART_txBufferHead;
    extern volatile uint32  GPS_UART_txBufferTail;
#endif /* (GPS_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#if (GPS_UART_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 GPS_UART_rxBufferInternal[GPS_UART_INTERNAL_RX_BUFFER_SIZE];
#endif /* (GPS_UART_INTERNAL_RX_SW_BUFFER) */

#if (GPS_UART_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 GPS_UART_txBufferInternal[GPS_UART_TX_BUFFER_SIZE];
#endif /* (GPS_UART_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void GPS_UART_SpiPostEnable(void);
void GPS_UART_SpiStop(void);

#if (GPS_UART_SCB_MODE_SPI_CONST_CFG)
    void GPS_UART_SpiInit(void);
#endif /* (GPS_UART_SCB_MODE_SPI_CONST_CFG) */

#if (GPS_UART_SPI_WAKE_ENABLE_CONST)
    void GPS_UART_SpiSaveConfig(void);
    void GPS_UART_SpiRestoreConfig(void);
#endif /* (GPS_UART_SPI_WAKE_ENABLE_CONST) */

void GPS_UART_UartPostEnable(void);
void GPS_UART_UartStop(void);

#if (GPS_UART_SCB_MODE_UART_CONST_CFG)
    void GPS_UART_UartInit(void);
#endif /* (GPS_UART_SCB_MODE_UART_CONST_CFG) */

#if (GPS_UART_UART_WAKE_ENABLE_CONST)
    void GPS_UART_UartSaveConfig(void);
    void GPS_UART_UartRestoreConfig(void);
#endif /* (GPS_UART_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in GPS_UART_SetPins() */
#define GPS_UART_UART_RX_PIN_ENABLE    (GPS_UART_UART_RX)
#define GPS_UART_UART_TX_PIN_ENABLE    (GPS_UART_UART_TX)

/* UART RTS and CTS position to be used in  GPS_UART_SetPins() */
#define GPS_UART_UART_RTS_PIN_ENABLE    (0x10u)
#define GPS_UART_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define GPS_UART_SpiUartEnableIntRx(intSourceMask)  GPS_UART_SetRxInterruptMode(intSourceMask)
#define GPS_UART_SpiUartEnableIntTx(intSourceMask)  GPS_UART_SetTxInterruptMode(intSourceMask)
uint32  GPS_UART_SpiUartDisableIntRx(void);
uint32  GPS_UART_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_GPS_UART_H) */


/* [] END OF FILE */
