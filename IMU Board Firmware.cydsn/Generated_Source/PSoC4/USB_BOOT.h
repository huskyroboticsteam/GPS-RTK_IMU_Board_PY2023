/***************************************************************************//**
* \file USB_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_USB_H)
#define CY_SCB_BOOT_USB_H

#include "USB_PVT.h"

#if (USB_SCB_MODE_I2C_INC)
    #include "USB_I2C.h"
#endif /* (USB_SCB_MODE_I2C_INC) */

#if (USB_SCB_MODE_EZI2C_INC)
    #include "USB_EZI2C.h"
#endif /* (USB_SCB_MODE_EZI2C_INC) */

#if (USB_SCB_MODE_SPI_INC || USB_SCB_MODE_UART_INC)
    #include "USB_SPI_UART.h"
#endif /* (USB_SCB_MODE_SPI_INC || USB_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define USB_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USB) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (USB_SCB_MODE_I2C_INC)
    #define USB_I2C_BTLDR_COMM_ENABLED     (USB_BTLDR_COMM_ENABLED && \
                                                            (USB_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             USB_I2C_SLAVE_CONST))
#else
     #define USB_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (USB_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (USB_SCB_MODE_EZI2C_INC)
    #define USB_EZI2C_BTLDR_COMM_ENABLED   (USB_BTLDR_COMM_ENABLED && \
                                                         USB_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define USB_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (USB_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (USB_SCB_MODE_SPI_INC)
    #define USB_SPI_BTLDR_COMM_ENABLED     (USB_BTLDR_COMM_ENABLED && \
                                                            (USB_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             USB_SPI_SLAVE_CONST))
#else
        #define USB_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (USB_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (USB_SCB_MODE_UART_INC)
       #define USB_UART_BTLDR_COMM_ENABLED    (USB_BTLDR_COMM_ENABLED && \
                                                            (USB_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (USB_UART_RX_DIRECTION && \
                                                              USB_UART_TX_DIRECTION)))
#else
     #define USB_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (USB_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define USB_BTLDR_COMM_MODE_ENABLED    (USB_I2C_BTLDR_COMM_ENABLED   || \
                                                     USB_SPI_BTLDR_COMM_ENABLED   || \
                                                     USB_EZI2C_BTLDR_COMM_ENABLED || \
                                                     USB_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void USB_I2CCyBtldrCommStart(void);
    void USB_I2CCyBtldrCommStop (void);
    void USB_I2CCyBtldrCommReset(void);
    cystatus USB_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus USB_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (USB_SCB_MODE_I2C_CONST_CFG)
        #define USB_CyBtldrCommStart   USB_I2CCyBtldrCommStart
        #define USB_CyBtldrCommStop    USB_I2CCyBtldrCommStop
        #define USB_CyBtldrCommReset   USB_I2CCyBtldrCommReset
        #define USB_CyBtldrCommRead    USB_I2CCyBtldrCommRead
        #define USB_CyBtldrCommWrite   USB_I2CCyBtldrCommWrite
    #endif /* (USB_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void USB_EzI2CCyBtldrCommStart(void);
    void USB_EzI2CCyBtldrCommStop (void);
    void USB_EzI2CCyBtldrCommReset(void);
    cystatus USB_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus USB_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (USB_SCB_MODE_EZI2C_CONST_CFG)
        #define USB_CyBtldrCommStart   USB_EzI2CCyBtldrCommStart
        #define USB_CyBtldrCommStop    USB_EzI2CCyBtldrCommStop
        #define USB_CyBtldrCommReset   USB_EzI2CCyBtldrCommReset
        #define USB_CyBtldrCommRead    USB_EzI2CCyBtldrCommRead
        #define USB_CyBtldrCommWrite   USB_EzI2CCyBtldrCommWrite
    #endif /* (USB_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void USB_SpiCyBtldrCommStart(void);
    void USB_SpiCyBtldrCommStop (void);
    void USB_SpiCyBtldrCommReset(void);
    cystatus USB_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus USB_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (USB_SCB_MODE_SPI_CONST_CFG)
        #define USB_CyBtldrCommStart   USB_SpiCyBtldrCommStart
        #define USB_CyBtldrCommStop    USB_SpiCyBtldrCommStop
        #define USB_CyBtldrCommReset   USB_SpiCyBtldrCommReset
        #define USB_CyBtldrCommRead    USB_SpiCyBtldrCommRead
        #define USB_CyBtldrCommWrite   USB_SpiCyBtldrCommWrite
    #endif /* (USB_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void USB_UartCyBtldrCommStart(void);
    void USB_UartCyBtldrCommStop (void);
    void USB_UartCyBtldrCommReset(void);
    cystatus USB_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus USB_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (USB_SCB_MODE_UART_CONST_CFG)
        #define USB_CyBtldrCommStart   USB_UartCyBtldrCommStart
        #define USB_CyBtldrCommStop    USB_UartCyBtldrCommStop
        #define USB_CyBtldrCommReset   USB_UartCyBtldrCommReset
        #define USB_CyBtldrCommRead    USB_UartCyBtldrCommRead
        #define USB_CyBtldrCommWrite   USB_UartCyBtldrCommWrite
    #endif /* (USB_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_BTLDR_COMM_ENABLED)
    #if (USB_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void USB_CyBtldrCommStart(void);
        void USB_CyBtldrCommStop (void);
        void USB_CyBtldrCommReset(void);
        cystatus USB_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus USB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (USB_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USB)
        #define CyBtldrCommStart    USB_CyBtldrCommStart
        #define CyBtldrCommStop     USB_CyBtldrCommStop
        #define CyBtldrCommReset    USB_CyBtldrCommReset
        #define CyBtldrCommWrite    USB_CyBtldrCommWrite
        #define CyBtldrCommRead     USB_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USB) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (USB_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define USB_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define USB_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define USB_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define USB_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef USB_SPI_BYTE_TO_BYTE
    #define USB_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef USB_UART_BYTE_TO_BYTE
    #define USB_UART_BYTE_TO_BYTE  (175u)
#endif /* USB_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_USB_H) */


/* [] END OF FILE */
