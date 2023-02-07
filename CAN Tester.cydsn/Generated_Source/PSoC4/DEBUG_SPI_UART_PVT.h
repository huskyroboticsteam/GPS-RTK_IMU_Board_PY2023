/***************************************************************************//**
* \file DEBUG_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_DEBUG_H)
#define CY_SCB_SPI_UART_PVT_DEBUG_H

#include "DEBUG_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (DEBUG_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  DEBUG_rxBufferHead;
    extern volatile uint32  DEBUG_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   DEBUG_rxBufferOverflow;
    /** @} globals */
#endif /* (DEBUG_INTERNAL_RX_SW_BUFFER_CONST) */

#if (DEBUG_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  DEBUG_txBufferHead;
    extern volatile uint32  DEBUG_txBufferTail;
#endif /* (DEBUG_INTERNAL_TX_SW_BUFFER_CONST) */

#if (DEBUG_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 DEBUG_rxBufferInternal[DEBUG_INTERNAL_RX_BUFFER_SIZE];
#endif /* (DEBUG_INTERNAL_RX_SW_BUFFER) */

#if (DEBUG_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 DEBUG_txBufferInternal[DEBUG_TX_BUFFER_SIZE];
#endif /* (DEBUG_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void DEBUG_SpiPostEnable(void);
void DEBUG_SpiStop(void);

#if (DEBUG_SCB_MODE_SPI_CONST_CFG)
    void DEBUG_SpiInit(void);
#endif /* (DEBUG_SCB_MODE_SPI_CONST_CFG) */

#if (DEBUG_SPI_WAKE_ENABLE_CONST)
    void DEBUG_SpiSaveConfig(void);
    void DEBUG_SpiRestoreConfig(void);
#endif /* (DEBUG_SPI_WAKE_ENABLE_CONST) */

void DEBUG_UartPostEnable(void);
void DEBUG_UartStop(void);

#if (DEBUG_SCB_MODE_UART_CONST_CFG)
    void DEBUG_UartInit(void);
#endif /* (DEBUG_SCB_MODE_UART_CONST_CFG) */

#if (DEBUG_UART_WAKE_ENABLE_CONST)
    void DEBUG_UartSaveConfig(void);
    void DEBUG_UartRestoreConfig(void);
#endif /* (DEBUG_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in DEBUG_SetPins() */
#define DEBUG_UART_RX_PIN_ENABLE    (DEBUG_UART_RX)
#define DEBUG_UART_TX_PIN_ENABLE    (DEBUG_UART_TX)

/* UART RTS and CTS position to be used in  DEBUG_SetPins() */
#define DEBUG_UART_RTS_PIN_ENABLE    (0x10u)
#define DEBUG_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define DEBUG_SpiUartEnableIntRx(intSourceMask)  DEBUG_SetRxInterruptMode(intSourceMask)
#define DEBUG_SpiUartEnableIntTx(intSourceMask)  DEBUG_SetTxInterruptMode(intSourceMask)
uint32  DEBUG_SpiUartDisableIntRx(void);
uint32  DEBUG_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_DEBUG_H) */


/* [] END OF FILE */
