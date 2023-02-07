/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
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

#if !defined(CY_SCB_PVT_USB_DEBUG_H)
#define CY_SCB_PVT_USB_DEBUG_H

#include "USB_DEBUG.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define USB_DEBUG_SetI2CExtClkInterruptMode(interruptMask) USB_DEBUG_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define USB_DEBUG_ClearI2CExtClkInterruptSource(interruptMask) USB_DEBUG_CLEAR_INTR_I2C_EC(interruptMask)
#define USB_DEBUG_GetI2CExtClkInterruptSource()                (USB_DEBUG_INTR_I2C_EC_REG)
#define USB_DEBUG_GetI2CExtClkInterruptMode()                  (USB_DEBUG_INTR_I2C_EC_MASK_REG)
#define USB_DEBUG_GetI2CExtClkInterruptSourceMasked()          (USB_DEBUG_INTR_I2C_EC_MASKED_REG)

#if (!USB_DEBUG_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define USB_DEBUG_SetSpiExtClkInterruptMode(interruptMask) \
                                                                USB_DEBUG_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define USB_DEBUG_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                USB_DEBUG_CLEAR_INTR_SPI_EC(interruptMask)
    #define USB_DEBUG_GetExtSpiClkInterruptSource()                 (USB_DEBUG_INTR_SPI_EC_REG)
    #define USB_DEBUG_GetExtSpiClkInterruptMode()                   (USB_DEBUG_INTR_SPI_EC_MASK_REG)
    #define USB_DEBUG_GetExtSpiClkInterruptSourceMasked()           (USB_DEBUG_INTR_SPI_EC_MASKED_REG)
#endif /* (!USB_DEBUG_CY_SCBIP_V1) */

#if(USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void USB_DEBUG_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (USB_DEBUG_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_USB_DEBUG_CUSTOM_INTR_HANDLER)
    extern cyisraddress USB_DEBUG_customIntrHandler;
#endif /* !defined (CY_REMOVE_USB_DEBUG_CUSTOM_INTR_HANDLER) */
#endif /* (USB_DEBUG_SCB_IRQ_INTERNAL) */

extern USB_DEBUG_BACKUP_STRUCT USB_DEBUG_backup;

#if(USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 USB_DEBUG_scbMode;
    extern uint8 USB_DEBUG_scbEnableWake;
    extern uint8 USB_DEBUG_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 USB_DEBUG_mode;
    extern uint8 USB_DEBUG_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * USB_DEBUG_rxBuffer;
    extern uint8   USB_DEBUG_rxDataBits;
    extern uint32  USB_DEBUG_rxBufferSize;

    extern volatile uint8 * USB_DEBUG_txBuffer;
    extern uint8   USB_DEBUG_txDataBits;
    extern uint32  USB_DEBUG_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 USB_DEBUG_numberOfAddr;
    extern uint8 USB_DEBUG_subAddrSize;
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (USB_DEBUG_SCB_MODE_I2C_CONST_CFG || \
        USB_DEBUG_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 USB_DEBUG_IntrTxMask;
#endif /* (! (USB_DEBUG_SCB_MODE_I2C_CONST_CFG || \
              USB_DEBUG_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define USB_DEBUG_SCB_MODE_I2C_RUNTM_CFG     (USB_DEBUG_SCB_MODE_I2C      == USB_DEBUG_scbMode)
    #define USB_DEBUG_SCB_MODE_SPI_RUNTM_CFG     (USB_DEBUG_SCB_MODE_SPI      == USB_DEBUG_scbMode)
    #define USB_DEBUG_SCB_MODE_UART_RUNTM_CFG    (USB_DEBUG_SCB_MODE_UART     == USB_DEBUG_scbMode)
    #define USB_DEBUG_SCB_MODE_EZI2C_RUNTM_CFG   (USB_DEBUG_SCB_MODE_EZI2C    == USB_DEBUG_scbMode)
    #define USB_DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (USB_DEBUG_SCB_MODE_UNCONFIG == USB_DEBUG_scbMode)

    /* Defines wakeup enable */
    #define USB_DEBUG_SCB_WAKE_ENABLE_CHECK       (0u != USB_DEBUG_scbEnableWake)
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!USB_DEBUG_CY_SCBIP_V1)
    #define USB_DEBUG_SCB_PINS_NUMBER    (7u)
#else
    #define USB_DEBUG_SCB_PINS_NUMBER    (2u)
#endif /* (!USB_DEBUG_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_USB_DEBUG_H) */


/* [] END OF FILE */
