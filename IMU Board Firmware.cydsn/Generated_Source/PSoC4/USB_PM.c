/***************************************************************************//**
* \file USB_PM.c
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

#include "USB.h"
#include "USB_PVT.h"

#if(USB_SCB_MODE_I2C_INC)
    #include "USB_I2C_PVT.h"
#endif /* (USB_SCB_MODE_I2C_INC) */

#if(USB_SCB_MODE_EZI2C_INC)
    #include "USB_EZI2C_PVT.h"
#endif /* (USB_SCB_MODE_EZI2C_INC) */

#if(USB_SCB_MODE_SPI_INC || USB_SCB_MODE_UART_INC)
    #include "USB_SPI_UART_PVT.h"
#endif /* (USB_SCB_MODE_SPI_INC || USB_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(USB_SCB_MODE_UNCONFIG_CONST_CFG || \
   (USB_SCB_MODE_I2C_CONST_CFG   && (!USB_I2C_WAKE_ENABLE_CONST))   || \
   (USB_SCB_MODE_EZI2C_CONST_CFG && (!USB_EZI2C_WAKE_ENABLE_CONST)) || \
   (USB_SCB_MODE_SPI_CONST_CFG   && (!USB_SPI_WAKE_ENABLE_CONST))   || \
   (USB_SCB_MODE_UART_CONST_CFG  && (!USB_UART_WAKE_ENABLE_CONST)))

    USB_BACKUP_STRUCT USB_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: USB_Sleep
****************************************************************************//**
*
*  Prepares the USB component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the USB_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void USB_Sleep(void)
{
#if(USB_SCB_MODE_UNCONFIG_CONST_CFG)

    if(USB_SCB_WAKE_ENABLE_CHECK)
    {
        if(USB_SCB_MODE_I2C_RUNTM_CFG)
        {
            USB_I2CSaveConfig();
        }
        else if(USB_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            USB_EzI2CSaveConfig();
        }
    #if(!USB_CY_SCBIP_V1)
        else if(USB_SCB_MODE_SPI_RUNTM_CFG)
        {
            USB_SpiSaveConfig();
        }
        else if(USB_SCB_MODE_UART_RUNTM_CFG)
        {
            USB_UartSaveConfig();
        }
    #endif /* (!USB_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        USB_backup.enableState = (uint8) USB_GET_CTRL_ENABLED;

        if(0u != USB_backup.enableState)
        {
            USB_Stop();
        }
    }

#else

    #if (USB_SCB_MODE_I2C_CONST_CFG && USB_I2C_WAKE_ENABLE_CONST)
        USB_I2CSaveConfig();

    #elif (USB_SCB_MODE_EZI2C_CONST_CFG && USB_EZI2C_WAKE_ENABLE_CONST)
        USB_EzI2CSaveConfig();

    #elif (USB_SCB_MODE_SPI_CONST_CFG && USB_SPI_WAKE_ENABLE_CONST)
        USB_SpiSaveConfig();

    #elif (USB_SCB_MODE_UART_CONST_CFG && USB_UART_WAKE_ENABLE_CONST)
        USB_UartSaveConfig();

    #else

        USB_backup.enableState = (uint8) USB_GET_CTRL_ENABLED;

        if(0u != USB_backup.enableState)
        {
            USB_Stop();
        }

    #endif /* defined (USB_SCB_MODE_I2C_CONST_CFG) && (USB_I2C_WAKE_ENABLE_CONST) */

#endif /* (USB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: USB_Wakeup
****************************************************************************//**
*
*  Prepares the USB component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the USB_Wakeup() function without first calling the 
*   USB_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void USB_Wakeup(void)
{
#if(USB_SCB_MODE_UNCONFIG_CONST_CFG)

    if(USB_SCB_WAKE_ENABLE_CHECK)
    {
        if(USB_SCB_MODE_I2C_RUNTM_CFG)
        {
            USB_I2CRestoreConfig();
        }
        else if(USB_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            USB_EzI2CRestoreConfig();
        }
    #if(!USB_CY_SCBIP_V1)
        else if(USB_SCB_MODE_SPI_RUNTM_CFG)
        {
            USB_SpiRestoreConfig();
        }
        else if(USB_SCB_MODE_UART_RUNTM_CFG)
        {
            USB_UartRestoreConfig();
        }
    #endif /* (!USB_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != USB_backup.enableState)
        {
            USB_Enable();
        }
    }

#else

    #if (USB_SCB_MODE_I2C_CONST_CFG  && USB_I2C_WAKE_ENABLE_CONST)
        USB_I2CRestoreConfig();

    #elif (USB_SCB_MODE_EZI2C_CONST_CFG && USB_EZI2C_WAKE_ENABLE_CONST)
        USB_EzI2CRestoreConfig();

    #elif (USB_SCB_MODE_SPI_CONST_CFG && USB_SPI_WAKE_ENABLE_CONST)
        USB_SpiRestoreConfig();

    #elif (USB_SCB_MODE_UART_CONST_CFG && USB_UART_WAKE_ENABLE_CONST)
        USB_UartRestoreConfig();

    #else

        if(0u != USB_backup.enableState)
        {
            USB_Enable();
        }

    #endif /* (USB_I2C_WAKE_ENABLE_CONST) */

#endif /* (USB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
