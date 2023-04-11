/***************************************************************************//**
* \file DEBUG_BOOT.h
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

#if !defined(CY_SCB_BOOT_DEBUG_H)
#define CY_SCB_BOOT_DEBUG_H

#include "DEBUG_PVT.h"

#if (DEBUG_SCB_MODE_I2C_INC)
    #include "DEBUG_I2C.h"
#endif /* (DEBUG_SCB_MODE_I2C_INC) */

#if (DEBUG_SCB_MODE_EZI2C_INC)
    #include "DEBUG_EZI2C.h"
#endif /* (DEBUG_SCB_MODE_EZI2C_INC) */

#if (DEBUG_SCB_MODE_SPI_INC || DEBUG_SCB_MODE_UART_INC)
    #include "DEBUG_SPI_UART.h"
#endif /* (DEBUG_SCB_MODE_SPI_INC || DEBUG_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define DEBUG_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUG) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (DEBUG_SCB_MODE_I2C_INC)
    #define DEBUG_I2C_BTLDR_COMM_ENABLED     (DEBUG_BTLDR_COMM_ENABLED && \
                                                            (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             DEBUG_I2C_SLAVE_CONST))
#else
     #define DEBUG_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (DEBUG_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (DEBUG_SCB_MODE_EZI2C_INC)
    #define DEBUG_EZI2C_BTLDR_COMM_ENABLED   (DEBUG_BTLDR_COMM_ENABLED && \
                                                         DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define DEBUG_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (DEBUG_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (DEBUG_SCB_MODE_SPI_INC)
    #define DEBUG_SPI_BTLDR_COMM_ENABLED     (DEBUG_BTLDR_COMM_ENABLED && \
                                                            (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             DEBUG_SPI_SLAVE_CONST))
#else
        #define DEBUG_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (DEBUG_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (DEBUG_SCB_MODE_UART_INC)
       #define DEBUG_UART_BTLDR_COMM_ENABLED    (DEBUG_BTLDR_COMM_ENABLED && \
                                                            (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (DEBUG_UART_RX_DIRECTION && \
                                                              DEBUG_UART_TX_DIRECTION)))
#else
     #define DEBUG_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (DEBUG_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define DEBUG_BTLDR_COMM_MODE_ENABLED    (DEBUG_I2C_BTLDR_COMM_ENABLED   || \
                                                     DEBUG_SPI_BTLDR_COMM_ENABLED   || \
                                                     DEBUG_EZI2C_BTLDR_COMM_ENABLED || \
                                                     DEBUG_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void DEBUG_I2CCyBtldrCommStart(void);
    void DEBUG_I2CCyBtldrCommStop (void);
    void DEBUG_I2CCyBtldrCommReset(void);
    cystatus DEBUG_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DEBUG_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (DEBUG_SCB_MODE_I2C_CONST_CFG)
        #define DEBUG_CyBtldrCommStart   DEBUG_I2CCyBtldrCommStart
        #define DEBUG_CyBtldrCommStop    DEBUG_I2CCyBtldrCommStop
        #define DEBUG_CyBtldrCommReset   DEBUG_I2CCyBtldrCommReset
        #define DEBUG_CyBtldrCommRead    DEBUG_I2CCyBtldrCommRead
        #define DEBUG_CyBtldrCommWrite   DEBUG_I2CCyBtldrCommWrite
    #endif /* (DEBUG_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void DEBUG_EzI2CCyBtldrCommStart(void);
    void DEBUG_EzI2CCyBtldrCommStop (void);
    void DEBUG_EzI2CCyBtldrCommReset(void);
    cystatus DEBUG_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DEBUG_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (DEBUG_SCB_MODE_EZI2C_CONST_CFG)
        #define DEBUG_CyBtldrCommStart   DEBUG_EzI2CCyBtldrCommStart
        #define DEBUG_CyBtldrCommStop    DEBUG_EzI2CCyBtldrCommStop
        #define DEBUG_CyBtldrCommReset   DEBUG_EzI2CCyBtldrCommReset
        #define DEBUG_CyBtldrCommRead    DEBUG_EzI2CCyBtldrCommRead
        #define DEBUG_CyBtldrCommWrite   DEBUG_EzI2CCyBtldrCommWrite
    #endif /* (DEBUG_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void DEBUG_SpiCyBtldrCommStart(void);
    void DEBUG_SpiCyBtldrCommStop (void);
    void DEBUG_SpiCyBtldrCommReset(void);
    cystatus DEBUG_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DEBUG_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (DEBUG_SCB_MODE_SPI_CONST_CFG)
        #define DEBUG_CyBtldrCommStart   DEBUG_SpiCyBtldrCommStart
        #define DEBUG_CyBtldrCommStop    DEBUG_SpiCyBtldrCommStop
        #define DEBUG_CyBtldrCommReset   DEBUG_SpiCyBtldrCommReset
        #define DEBUG_CyBtldrCommRead    DEBUG_SpiCyBtldrCommRead
        #define DEBUG_CyBtldrCommWrite   DEBUG_SpiCyBtldrCommWrite
    #endif /* (DEBUG_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void DEBUG_UartCyBtldrCommStart(void);
    void DEBUG_UartCyBtldrCommStop (void);
    void DEBUG_UartCyBtldrCommReset(void);
    cystatus DEBUG_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus DEBUG_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (DEBUG_SCB_MODE_UART_CONST_CFG)
        #define DEBUG_CyBtldrCommStart   DEBUG_UartCyBtldrCommStart
        #define DEBUG_CyBtldrCommStop    DEBUG_UartCyBtldrCommStop
        #define DEBUG_CyBtldrCommReset   DEBUG_UartCyBtldrCommReset
        #define DEBUG_CyBtldrCommRead    DEBUG_UartCyBtldrCommRead
        #define DEBUG_CyBtldrCommWrite   DEBUG_UartCyBtldrCommWrite
    #endif /* (DEBUG_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_BTLDR_COMM_ENABLED)
    #if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void DEBUG_CyBtldrCommStart(void);
        void DEBUG_CyBtldrCommStop (void);
        void DEBUG_CyBtldrCommReset(void);
        cystatus DEBUG_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus DEBUG_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUG)
        #define CyBtldrCommStart    DEBUG_CyBtldrCommStart
        #define CyBtldrCommStop     DEBUG_CyBtldrCommStop
        #define CyBtldrCommReset    DEBUG_CyBtldrCommReset
        #define CyBtldrCommWrite    DEBUG_CyBtldrCommWrite
        #define CyBtldrCommRead     DEBUG_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_DEBUG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define DEBUG_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define DEBUG_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define DEBUG_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define DEBUG_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef DEBUG_SPI_BYTE_TO_BYTE
    #define DEBUG_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef DEBUG_UART_BYTE_TO_BYTE
    #define DEBUG_UART_BYTE_TO_BYTE  (175u)
#endif /* DEBUG_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_DEBUG_H) */


/* [] END OF FILE */
