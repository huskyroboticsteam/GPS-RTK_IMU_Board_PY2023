/***************************************************************************//**
* \file USB_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_USB_H)
#define CY_SCB_SPI_UART_PVT_USB_H

#include "USB_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (USB_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  USB_rxBufferHead;
    extern volatile uint32  USB_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   USB_rxBufferOverflow;
    /** @} globals */
#endif /* (USB_INTERNAL_RX_SW_BUFFER_CONST) */

#if (USB_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  USB_txBufferHead;
    extern volatile uint32  USB_txBufferTail;
#endif /* (USB_INTERNAL_TX_SW_BUFFER_CONST) */

#if (USB_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 USB_rxBufferInternal[USB_INTERNAL_RX_BUFFER_SIZE];
#endif /* (USB_INTERNAL_RX_SW_BUFFER) */

#if (USB_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 USB_txBufferInternal[USB_TX_BUFFER_SIZE];
#endif /* (USB_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void USB_SpiPostEnable(void);
void USB_SpiStop(void);

#if (USB_SCB_MODE_SPI_CONST_CFG)
    void USB_SpiInit(void);
#endif /* (USB_SCB_MODE_SPI_CONST_CFG) */

#if (USB_SPI_WAKE_ENABLE_CONST)
    void USB_SpiSaveConfig(void);
    void USB_SpiRestoreConfig(void);
#endif /* (USB_SPI_WAKE_ENABLE_CONST) */

void USB_UartPostEnable(void);
void USB_UartStop(void);

#if (USB_SCB_MODE_UART_CONST_CFG)
    void USB_UartInit(void);
#endif /* (USB_SCB_MODE_UART_CONST_CFG) */

#if (USB_UART_WAKE_ENABLE_CONST)
    void USB_UartSaveConfig(void);
    void USB_UartRestoreConfig(void);
#endif /* (USB_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in USB_SetPins() */
#define USB_UART_RX_PIN_ENABLE    (USB_UART_RX)
#define USB_UART_TX_PIN_ENABLE    (USB_UART_TX)

/* UART RTS and CTS position to be used in  USB_SetPins() */
#define USB_UART_RTS_PIN_ENABLE    (0x10u)
#define USB_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define USB_SpiUartEnableIntRx(intSourceMask)  USB_SetRxInterruptMode(intSourceMask)
#define USB_SpiUartEnableIntTx(intSourceMask)  USB_SetTxInterruptMode(intSourceMask)
uint32  USB_SpiUartDisableIntRx(void);
uint32  USB_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_USB_H) */


/* [] END OF FILE */
