/***************************************************************************//**
* \file IMU_I2C_BOOT.c
* \version 4.0
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
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

#include "IMU_I2C_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (IMU_I2C_BTLDR_COMM_ENABLED) && \
                                (IMU_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: IMU_I2C_CyBtldrCommStart
****************************************************************************//**
*
*  Starts IMU_I2C component. After this function call the component is 
*  ready for communication.
*
*******************************************************************************/
void IMU_I2C_CyBtldrCommStart(void)
{
    if (IMU_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        IMU_I2C_I2CCyBtldrCommStart();
    }
    else if (IMU_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        IMU_I2C_EzI2CCyBtldrCommStart();
    }
#if (!IMU_I2C_CY_SCBIP_V1)
    else if (IMU_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        IMU_I2C_SpiCyBtldrCommStart();
    }
    else if (IMU_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        IMU_I2C_UartCyBtldrCommStart();
    }
#endif /* (!IMU_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: IMU_I2C_CyBtldrCommStop
****************************************************************************//**
*
*  Stops IMU_I2C component.
*
*******************************************************************************/
void IMU_I2C_CyBtldrCommStop(void)
{
    if (IMU_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        IMU_I2C_I2CCyBtldrCommStop();
    }
    else if (IMU_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        IMU_I2C_EzI2CCyBtldrCommStop();
    }
#if (!IMU_I2C_CY_SCBIP_V1)
    else if (IMU_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        IMU_I2C_SpiCyBtldrCommStop();
    }
    else if (IMU_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        IMU_I2C_UartCyBtldrCommStop();
    }
#endif /* (!IMU_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: IMU_I2C_CyBtldrCommReset
****************************************************************************//**
*
*  Clears IMU_I2C component buffers.
*
*******************************************************************************/
void IMU_I2C_CyBtldrCommReset(void)
{
    if(IMU_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        IMU_I2C_I2CCyBtldrCommReset();
    }
    else if(IMU_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        IMU_I2C_EzI2CCyBtldrCommReset();
    }
#if (!IMU_I2C_CY_SCBIP_V1)
    else if(IMU_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        IMU_I2C_SpiCyBtldrCommReset();
    }
    else if(IMU_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        IMU_I2C_UartCyBtldrCommReset();
    }
#endif /* (!IMU_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: IMU_I2C_CyBtldrCommRead
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the 
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to storage for the block of data to be read from the
*   bootloader host.
*  \param size: Number of bytes to be read.
*  \param count: Pointer to the variable to write the number of bytes actually
*   read.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
* \return
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus IMU_I2C_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(IMU_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = IMU_I2C_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(IMU_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = IMU_I2C_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!IMU_I2C_CY_SCBIP_V1)
    else if(IMU_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = IMU_I2C_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(IMU_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        status = IMU_I2C_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!IMU_I2C_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: IMU_I2C_CyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to write data to the bootloader host (the host reads the 
*  data). The function does not use timeout and returns after data has been copied
*  into the slave read buffer. This data available to be read by the bootloader
*  host until following host data write.
*
*  \param pData: Pointer to the block of data to be written to the bootloader host.
*  \param size: Number of bytes to be written.
*  \param count: Pointer to the variable to write the number of bytes actually
*   written.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus IMU_I2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(IMU_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = IMU_I2C_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(IMU_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = IMU_I2C_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!IMU_I2C_CY_SCBIP_V1)
    else if(IMU_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = IMU_I2C_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(IMU_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        status = IMU_I2C_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!IMU_I2C_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (IMU_I2C_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
