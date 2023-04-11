/***************************************************************************//**
* \file USB_DEBUG_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_USB_DEBUG_H)
#define CY_SCB_SPI_UART_PVT_USB_DEBUG_H

#include "USB_DEBUG_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (USB_DEBUG_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  USB_DEBUG_rxBufferHead;
    extern volatile uint32  USB_DEBUG_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   USB_DEBUG_rxBufferOverflow;
    /** @} globals */
#endif /* (USB_DEBUG_INTERNAL_RX_SW_BUFFER_CONST) */

#if (USB_DEBUG_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  USB_DEBUG_txBufferHead;
    extern volatile uint32  USB_DEBUG_txBufferTail;
#endif /* (USB_DEBUG_INTERNAL_TX_SW_BUFFER_CONST) */

#if (USB_DEBUG_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 USB_DEBUG_rxBufferInternal[USB_DEBUG_INTERNAL_RX_BUFFER_SIZE];
#endif /* (USB_DEBUG_INTERNAL_RX_SW_BUFFER) */

#if (USB_DEBUG_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 USB_DEBUG_txBufferInternal[USB_DEBUG_TX_BUFFER_SIZE];
#endif /* (USB_DEBUG_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void USB_DEBUG_SpiPostEnable(void);
void USB_DEBUG_SpiStop(void);

#if (USB_DEBUG_SCB_MODE_SPI_CONST_CFG)
    void USB_DEBUG_SpiInit(void);
#endif /* (USB_DEBUG_SCB_MODE_SPI_CONST_CFG) */

#if (USB_DEBUG_SPI_WAKE_ENABLE_CONST)
    void USB_DEBUG_SpiSaveConfig(void);
    void USB_DEBUG_SpiRestoreConfig(void);
#endif /* (USB_DEBUG_SPI_WAKE_ENABLE_CONST) */

void USB_DEBUG_UartPostEnable(void);
void USB_DEBUG_UartStop(void);

#if (USB_DEBUG_SCB_MODE_UART_CONST_CFG)
    void USB_DEBUG_UartInit(void);
#endif /* (USB_DEBUG_SCB_MODE_UART_CONST_CFG) */

#if (USB_DEBUG_UART_WAKE_ENABLE_CONST)
    void USB_DEBUG_UartSaveConfig(void);
    void USB_DEBUG_UartRestoreConfig(void);
#endif /* (USB_DEBUG_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in USB_DEBUG_SetPins() */
#define USB_DEBUG_UART_RX_PIN_ENABLE    (USB_DEBUG_UART_RX)
#define USB_DEBUG_UART_TX_PIN_ENABLE    (USB_DEBUG_UART_TX)

/* UART RTS and CTS position to be used in  USB_DEBUG_SetPins() */
#define USB_DEBUG_UART_RTS_PIN_ENABLE    (0x10u)
#define USB_DEBUG_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define USB_DEBUG_SpiUartEnableIntRx(intSourceMask)  USB_DEBUG_SetRxInterruptMode(intSourceMask)
#define USB_DEBUG_SpiUartEnableIntTx(intSourceMask)  USB_DEBUG_SetTxInterruptMode(intSourceMask)
uint32  USB_DEBUG_SpiUartDisableIntRx(void);
uint32  USB_DEBUG_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_USB_DEBUG_H) */


/* [] END OF FILE */
