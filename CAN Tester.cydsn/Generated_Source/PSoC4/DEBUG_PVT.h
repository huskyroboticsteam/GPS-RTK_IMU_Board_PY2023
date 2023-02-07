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

#if !defined(CY_SCB_PVT_DEBUG_H)
#define CY_SCB_PVT_DEBUG_H

#include "DEBUG.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define DEBUG_SetI2CExtClkInterruptMode(interruptMask) DEBUG_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define DEBUG_ClearI2CExtClkInterruptSource(interruptMask) DEBUG_CLEAR_INTR_I2C_EC(interruptMask)
#define DEBUG_GetI2CExtClkInterruptSource()                (DEBUG_INTR_I2C_EC_REG)
#define DEBUG_GetI2CExtClkInterruptMode()                  (DEBUG_INTR_I2C_EC_MASK_REG)
#define DEBUG_GetI2CExtClkInterruptSourceMasked()          (DEBUG_INTR_I2C_EC_MASKED_REG)

#if (!DEBUG_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define DEBUG_SetSpiExtClkInterruptMode(interruptMask) \
                                                                DEBUG_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define DEBUG_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                DEBUG_CLEAR_INTR_SPI_EC(interruptMask)
    #define DEBUG_GetExtSpiClkInterruptSource()                 (DEBUG_INTR_SPI_EC_REG)
    #define DEBUG_GetExtSpiClkInterruptMode()                   (DEBUG_INTR_SPI_EC_MASK_REG)
    #define DEBUG_GetExtSpiClkInterruptSourceMasked()           (DEBUG_INTR_SPI_EC_MASKED_REG)
#endif /* (!DEBUG_CY_SCBIP_V1) */

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void DEBUG_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (DEBUG_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DEBUG_CUSTOM_INTR_HANDLER)
    extern cyisraddress DEBUG_customIntrHandler;
#endif /* !defined (CY_REMOVE_DEBUG_CUSTOM_INTR_HANDLER) */
#endif /* (DEBUG_SCB_IRQ_INTERNAL) */

extern DEBUG_BACKUP_STRUCT DEBUG_backup;

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 DEBUG_scbMode;
    extern uint8 DEBUG_scbEnableWake;
    extern uint8 DEBUG_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 DEBUG_mode;
    extern uint8 DEBUG_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * DEBUG_rxBuffer;
    extern uint8   DEBUG_rxDataBits;
    extern uint32  DEBUG_rxBufferSize;

    extern volatile uint8 * DEBUG_txBuffer;
    extern uint8   DEBUG_txDataBits;
    extern uint32  DEBUG_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 DEBUG_numberOfAddr;
    extern uint8 DEBUG_subAddrSize;
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (DEBUG_SCB_MODE_I2C_CONST_CFG || \
        DEBUG_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 DEBUG_IntrTxMask;
#endif /* (! (DEBUG_SCB_MODE_I2C_CONST_CFG || \
              DEBUG_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define DEBUG_SCB_MODE_I2C_RUNTM_CFG     (DEBUG_SCB_MODE_I2C      == DEBUG_scbMode)
    #define DEBUG_SCB_MODE_SPI_RUNTM_CFG     (DEBUG_SCB_MODE_SPI      == DEBUG_scbMode)
    #define DEBUG_SCB_MODE_UART_RUNTM_CFG    (DEBUG_SCB_MODE_UART     == DEBUG_scbMode)
    #define DEBUG_SCB_MODE_EZI2C_RUNTM_CFG   (DEBUG_SCB_MODE_EZI2C    == DEBUG_scbMode)
    #define DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (DEBUG_SCB_MODE_UNCONFIG == DEBUG_scbMode)

    /* Defines wakeup enable */
    #define DEBUG_SCB_WAKE_ENABLE_CHECK       (0u != DEBUG_scbEnableWake)
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!DEBUG_CY_SCBIP_V1)
    #define DEBUG_SCB_PINS_NUMBER    (7u)
#else
    #define DEBUG_SCB_PINS_NUMBER    (2u)
#endif /* (!DEBUG_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_DEBUG_H) */


/* [] END OF FILE */
