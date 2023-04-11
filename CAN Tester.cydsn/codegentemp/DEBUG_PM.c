/***************************************************************************//**
* \file DEBUG_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUG.h"
#include "DEBUG_PVT.h"

#if(DEBUG_SCB_MODE_I2C_INC)
    #include "DEBUG_I2C_PVT.h"
#endif /* (DEBUG_SCB_MODE_I2C_INC) */

#if(DEBUG_SCB_MODE_EZI2C_INC)
    #include "DEBUG_EZI2C_PVT.h"
#endif /* (DEBUG_SCB_MODE_EZI2C_INC) */

#if(DEBUG_SCB_MODE_SPI_INC || DEBUG_SCB_MODE_UART_INC)
    #include "DEBUG_SPI_UART_PVT.h"
#endif /* (DEBUG_SCB_MODE_SPI_INC || DEBUG_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG || \
   (DEBUG_SCB_MODE_I2C_CONST_CFG   && (!DEBUG_I2C_WAKE_ENABLE_CONST))   || \
   (DEBUG_SCB_MODE_EZI2C_CONST_CFG && (!DEBUG_EZI2C_WAKE_ENABLE_CONST)) || \
   (DEBUG_SCB_MODE_SPI_CONST_CFG   && (!DEBUG_SPI_WAKE_ENABLE_CONST))   || \
   (DEBUG_SCB_MODE_UART_CONST_CFG  && (!DEBUG_UART_WAKE_ENABLE_CONST)))

    DEBUG_BACKUP_STRUCT DEBUG_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: DEBUG_Sleep
****************************************************************************//**
*
*  Prepares the DEBUG component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the DEBUG_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void DEBUG_Sleep(void)
{
#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DEBUG_SCB_WAKE_ENABLE_CHECK)
    {
        if(DEBUG_SCB_MODE_I2C_RUNTM_CFG)
        {
            DEBUG_I2CSaveConfig();
        }
        else if(DEBUG_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DEBUG_EzI2CSaveConfig();
        }
    #if(!DEBUG_CY_SCBIP_V1)
        else if(DEBUG_SCB_MODE_SPI_RUNTM_CFG)
        {
            DEBUG_SpiSaveConfig();
        }
        else if(DEBUG_SCB_MODE_UART_RUNTM_CFG)
        {
            DEBUG_UartSaveConfig();
        }
    #endif /* (!DEBUG_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        DEBUG_backup.enableState = (uint8) DEBUG_GET_CTRL_ENABLED;

        if(0u != DEBUG_backup.enableState)
        {
            DEBUG_Stop();
        }
    }

#else

    #if (DEBUG_SCB_MODE_I2C_CONST_CFG && DEBUG_I2C_WAKE_ENABLE_CONST)
        DEBUG_I2CSaveConfig();

    #elif (DEBUG_SCB_MODE_EZI2C_CONST_CFG && DEBUG_EZI2C_WAKE_ENABLE_CONST)
        DEBUG_EzI2CSaveConfig();

    #elif (DEBUG_SCB_MODE_SPI_CONST_CFG && DEBUG_SPI_WAKE_ENABLE_CONST)
        DEBUG_SpiSaveConfig();

    #elif (DEBUG_SCB_MODE_UART_CONST_CFG && DEBUG_UART_WAKE_ENABLE_CONST)
        DEBUG_UartSaveConfig();

    #else

        DEBUG_backup.enableState = (uint8) DEBUG_GET_CTRL_ENABLED;

        if(0u != DEBUG_backup.enableState)
        {
            DEBUG_Stop();
        }

    #endif /* defined (DEBUG_SCB_MODE_I2C_CONST_CFG) && (DEBUG_I2C_WAKE_ENABLE_CONST) */

#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DEBUG_Wakeup
****************************************************************************//**
*
*  Prepares the DEBUG component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the DEBUG_Wakeup() function without first calling the 
*   DEBUG_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void DEBUG_Wakeup(void)
{
#if(DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)

    if(DEBUG_SCB_WAKE_ENABLE_CHECK)
    {
        if(DEBUG_SCB_MODE_I2C_RUNTM_CFG)
        {
            DEBUG_I2CRestoreConfig();
        }
        else if(DEBUG_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            DEBUG_EzI2CRestoreConfig();
        }
    #if(!DEBUG_CY_SCBIP_V1)
        else if(DEBUG_SCB_MODE_SPI_RUNTM_CFG)
        {
            DEBUG_SpiRestoreConfig();
        }
        else if(DEBUG_SCB_MODE_UART_RUNTM_CFG)
        {
            DEBUG_UartRestoreConfig();
        }
    #endif /* (!DEBUG_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != DEBUG_backup.enableState)
        {
            DEBUG_Enable();
        }
    }

#else

    #if (DEBUG_SCB_MODE_I2C_CONST_CFG  && DEBUG_I2C_WAKE_ENABLE_CONST)
        DEBUG_I2CRestoreConfig();

    #elif (DEBUG_SCB_MODE_EZI2C_CONST_CFG && DEBUG_EZI2C_WAKE_ENABLE_CONST)
        DEBUG_EzI2CRestoreConfig();

    #elif (DEBUG_SCB_MODE_SPI_CONST_CFG && DEBUG_SPI_WAKE_ENABLE_CONST)
        DEBUG_SpiRestoreConfig();

    #elif (DEBUG_SCB_MODE_UART_CONST_CFG && DEBUG_UART_WAKE_ENABLE_CONST)
        DEBUG_UartRestoreConfig();

    #else

        if(0u != DEBUG_backup.enableState)
        {
            DEBUG_Enable();
        }

    #endif /* (DEBUG_I2C_WAKE_ENABLE_CONST) */

#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
