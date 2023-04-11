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

#if !defined(CY_SCB_PVT_DGB_UART_H)
#define CY_SCB_PVT_DGB_UART_H

#include "DGB_UART.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define DGB_UART_SetI2CExtClkInterruptMode(interruptMask) DGB_UART_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define DGB_UART_ClearI2CExtClkInterruptSource(interruptMask) DGB_UART_CLEAR_INTR_I2C_EC(interruptMask)
#define DGB_UART_GetI2CExtClkInterruptSource()                (DGB_UART_INTR_I2C_EC_REG)
#define DGB_UART_GetI2CExtClkInterruptMode()                  (DGB_UART_INTR_I2C_EC_MASK_REG)
#define DGB_UART_GetI2CExtClkInterruptSourceMasked()          (DGB_UART_INTR_I2C_EC_MASKED_REG)

#if (!DGB_UART_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define DGB_UART_SetSpiExtClkInterruptMode(interruptMask) \
                                                                DGB_UART_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define DGB_UART_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                DGB_UART_CLEAR_INTR_SPI_EC(interruptMask)
    #define DGB_UART_GetExtSpiClkInterruptSource()                 (DGB_UART_INTR_SPI_EC_REG)
    #define DGB_UART_GetExtSpiClkInterruptMode()                   (DGB_UART_INTR_SPI_EC_MASK_REG)
    #define DGB_UART_GetExtSpiClkInterruptSourceMasked()           (DGB_UART_INTR_SPI_EC_MASKED_REG)
#endif /* (!DGB_UART_CY_SCBIP_V1) */

#if(DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void DGB_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (DGB_UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DGB_UART_CUSTOM_INTR_HANDLER)
    extern cyisraddress DGB_UART_customIntrHandler;
#endif /* !defined (CY_REMOVE_DGB_UART_CUSTOM_INTR_HANDLER) */
#endif /* (DGB_UART_SCB_IRQ_INTERNAL) */

extern DGB_UART_BACKUP_STRUCT DGB_UART_backup;

#if(DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 DGB_UART_scbMode;
    extern uint8 DGB_UART_scbEnableWake;
    extern uint8 DGB_UART_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 DGB_UART_mode;
    extern uint8 DGB_UART_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * DGB_UART_rxBuffer;
    extern uint8   DGB_UART_rxDataBits;
    extern uint32  DGB_UART_rxBufferSize;

    extern volatile uint8 * DGB_UART_txBuffer;
    extern uint8   DGB_UART_txDataBits;
    extern uint32  DGB_UART_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 DGB_UART_numberOfAddr;
    extern uint8 DGB_UART_subAddrSize;
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (DGB_UART_SCB_MODE_I2C_CONST_CFG || \
        DGB_UART_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 DGB_UART_IntrTxMask;
#endif /* (! (DGB_UART_SCB_MODE_I2C_CONST_CFG || \
              DGB_UART_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define DGB_UART_SCB_MODE_I2C_RUNTM_CFG     (DGB_UART_SCB_MODE_I2C      == DGB_UART_scbMode)
    #define DGB_UART_SCB_MODE_SPI_RUNTM_CFG     (DGB_UART_SCB_MODE_SPI      == DGB_UART_scbMode)
    #define DGB_UART_SCB_MODE_UART_RUNTM_CFG    (DGB_UART_SCB_MODE_UART     == DGB_UART_scbMode)
    #define DGB_UART_SCB_MODE_EZI2C_RUNTM_CFG   (DGB_UART_SCB_MODE_EZI2C    == DGB_UART_scbMode)
    #define DGB_UART_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (DGB_UART_SCB_MODE_UNCONFIG == DGB_UART_scbMode)

    /* Defines wakeup enable */
    #define DGB_UART_SCB_WAKE_ENABLE_CHECK       (0u != DGB_UART_scbEnableWake)
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!DGB_UART_CY_SCBIP_V1)
    #define DGB_UART_SCB_PINS_NUMBER    (7u)
#else
    #define DGB_UART_SCB_PINS_NUMBER    (2u)
#endif /* (!DGB_UART_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_DGB_UART_H) */


/* [] END OF FILE */
