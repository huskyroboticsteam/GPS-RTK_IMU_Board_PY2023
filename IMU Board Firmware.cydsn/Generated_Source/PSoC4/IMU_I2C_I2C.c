/***************************************************************************//**
* \file IMU_I2C_I2C.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "IMU_I2C_PVT.h"
#include "IMU_I2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 IMU_I2C_state;  /* Current state of I2C FSM */

#if(IMU_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const IMU_I2C_I2C_INIT_STRUCT IMU_I2C_configI2C =
    {
        IMU_I2C_I2C_MODE,
        IMU_I2C_I2C_OVS_FACTOR_LOW,
        IMU_I2C_I2C_OVS_FACTOR_HIGH,
        IMU_I2C_I2C_MEDIAN_FILTER_ENABLE,
        IMU_I2C_I2C_SLAVE_ADDRESS,
        IMU_I2C_I2C_SLAVE_ADDRESS_MASK,
        IMU_I2C_I2C_ACCEPT_ADDRESS,
        IMU_I2C_I2C_WAKE_ENABLE,
        IMU_I2C_I2C_BYTE_MODE_ENABLE,
        IMU_I2C_I2C_DATA_RATE,
        IMU_I2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: IMU_I2C_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the IMU_I2C for I2C operation.
    *
    *  This function is intended specifically to be used when the IMU_I2C 
    *  configuration is set to “Unconfigured IMU_I2C” in the customizer. 
    *  After initializing the IMU_I2C in I2C mode using this function, 
    *  the component can be enabled using the IMU_I2C_Start() or 
    * IMU_I2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void IMU_I2C_I2CInit(const IMU_I2C_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            IMU_I2C_SetPins(IMU_I2C_SCB_MODE_I2C, IMU_I2C_DUMMY_PARAM,
                                     IMU_I2C_DUMMY_PARAM);

            /* Store internal configuration */
            IMU_I2C_scbMode       = (uint8) IMU_I2C_SCB_MODE_I2C;
            IMU_I2C_scbEnableWake = (uint8) config->enableWake;
            IMU_I2C_scbEnableIntr = (uint8) IMU_I2C_SCB_IRQ_INTERNAL;

            IMU_I2C_mode          = (uint8) config->mode;
            IMU_I2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (IMU_I2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            IMU_I2C_SET_I2C_CFG_SDA_FILT_TRIM(IMU_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (IMU_I2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((IMU_I2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= IMU_I2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (IMU_I2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                IMU_I2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = IMU_I2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                IMU_I2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = IMU_I2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!IMU_I2C_CY_SCBIP_V0)
            locEnableWake = (IMU_I2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!IMU_I2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            IMU_I2C_CTRL_REG     = IMU_I2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            IMU_I2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            IMU_I2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            IMU_I2C_I2C_CTRL_REG = IMU_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    IMU_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    IMU_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    IMU_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            IMU_I2C_RX_CTRL_REG      = IMU_I2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                IMU_I2C_I2C_RX_CTRL;
            IMU_I2C_RX_FIFO_CTRL_REG = IMU_I2C_CLEAR_REG;

            /* Set default address and mask */
            IMU_I2C_RX_MATCH_REG    = ((IMU_I2C_I2C_SLAVE) ?
                                                (IMU_I2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 IMU_I2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (IMU_I2C_CLEAR_REG));


            /* Configure TX direction */
            IMU_I2C_TX_CTRL_REG      = IMU_I2C_I2C_TX_CTRL;
            IMU_I2C_TX_FIFO_CTRL_REG = IMU_I2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (IMU_I2C_ISR_NUMBER);
            CyIntSetPriority(IMU_I2C_ISR_NUMBER, IMU_I2C_ISR_PRIORITY);
            (void) CyIntSetVector(IMU_I2C_ISR_NUMBER, &IMU_I2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!IMU_I2C_CY_SCBIP_V1)
            IMU_I2C_INTR_SPI_EC_MASK_REG = IMU_I2C_NO_INTR_SOURCES;
        #endif /* (!IMU_I2C_CY_SCBIP_V1) */

            IMU_I2C_INTR_I2C_EC_MASK_REG = IMU_I2C_NO_INTR_SOURCES;
            IMU_I2C_INTR_RX_MASK_REG     = IMU_I2C_NO_INTR_SOURCES;
            IMU_I2C_INTR_TX_MASK_REG     = IMU_I2C_NO_INTR_SOURCES;

            IMU_I2C_INTR_SLAVE_MASK_REG  = ((IMU_I2C_I2C_SLAVE) ?
                            (IMU_I2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             IMU_I2C_I2C_INTR_SLAVE_MASK) : (IMU_I2C_CLEAR_REG));

            IMU_I2C_INTR_MASTER_MASK_REG = IMU_I2C_NO_INTR_SOURCES;

            /* Configure global variables */
            IMU_I2C_state = IMU_I2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            IMU_I2C_slStatus        = 0u;
            IMU_I2C_slRdBufIndex    = 0u;
            IMU_I2C_slWrBufIndex    = 0u;
            IMU_I2C_slOverFlowCount = 0u;

            /* Internal master variables */
            IMU_I2C_mstrStatus     = 0u;
            IMU_I2C_mstrRdBufIndex = 0u;
            IMU_I2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: IMU_I2C_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void IMU_I2C_I2CInit(void)
    {
    #if(IMU_I2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        IMU_I2C_SET_I2C_CFG_SDA_FILT_TRIM(IMU_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (IMU_I2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        IMU_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        IMU_I2C_CTRL_REG     = IMU_I2C_I2C_DEFAULT_CTRL;
        IMU_I2C_I2C_CTRL_REG = IMU_I2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        IMU_I2C_RX_CTRL_REG      = IMU_I2C_I2C_DEFAULT_RX_CTRL;
        IMU_I2C_RX_FIFO_CTRL_REG = IMU_I2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        IMU_I2C_RX_MATCH_REG     = IMU_I2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        IMU_I2C_TX_CTRL_REG      = IMU_I2C_I2C_DEFAULT_TX_CTRL;
        IMU_I2C_TX_FIFO_CTRL_REG = IMU_I2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (IMU_I2C_ISR_NUMBER);
        CyIntSetPriority(IMU_I2C_ISR_NUMBER, IMU_I2C_ISR_PRIORITY);
    #if(!IMU_I2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(IMU_I2C_ISR_NUMBER, &IMU_I2C_I2C_ISR);
    #endif /* (IMU_I2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!IMU_I2C_CY_SCBIP_V1)
        IMU_I2C_INTR_SPI_EC_MASK_REG = IMU_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!IMU_I2C_CY_SCBIP_V1) */

        IMU_I2C_INTR_I2C_EC_MASK_REG = IMU_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        IMU_I2C_INTR_SLAVE_MASK_REG  = IMU_I2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        IMU_I2C_INTR_MASTER_MASK_REG = IMU_I2C_I2C_DEFAULT_INTR_MASTER_MASK;
        IMU_I2C_INTR_RX_MASK_REG     = IMU_I2C_I2C_DEFAULT_INTR_RX_MASK;
        IMU_I2C_INTR_TX_MASK_REG     = IMU_I2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        IMU_I2C_state = IMU_I2C_I2C_FSM_IDLE;

    #if(IMU_I2C_I2C_SLAVE)
        /* Internal slave variable */
        IMU_I2C_slStatus        = 0u;
        IMU_I2C_slRdBufIndex    = 0u;
        IMU_I2C_slWrBufIndex    = 0u;
        IMU_I2C_slOverFlowCount = 0u;
    #endif /* (IMU_I2C_I2C_SLAVE) */

    #if(IMU_I2C_I2C_MASTER)
    /* Internal master variable */
        IMU_I2C_mstrStatus     = 0u;
        IMU_I2C_mstrRdBufIndex = 0u;
        IMU_I2C_mstrWrBufIndex = 0u;
    #endif /* (IMU_I2C_I2C_MASTER) */
    }
#endif /* (IMU_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: IMU_I2C_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void IMU_I2C_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    IMU_I2C_I2C_MASTER_CMD_REG = 0u;
    IMU_I2C_I2C_SLAVE_CMD_REG  = 0u;
    
    IMU_I2C_state = IMU_I2C_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: IMU_I2C_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void IMU_I2C_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    IMU_I2C_CTRL_REG &= (uint32) ~IMU_I2C_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    IMU_I2C_I2C_MASTER_CMD_REG = 0u;
    IMU_I2C_I2C_SLAVE_CMD_REG  = 0u;

    IMU_I2C_DISABLE_AUTO_DATA;

    IMU_I2C_SetTxInterruptMode(IMU_I2C_NO_INTR_SOURCES);
    IMU_I2C_SetRxInterruptMode(IMU_I2C_NO_INTR_SOURCES);
    
#if(IMU_I2C_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    IMU_I2C_ClearTxInterruptSource    (IMU_I2C_INTR_TX_ALL);
    IMU_I2C_ClearRxInterruptSource    (IMU_I2C_INTR_RX_ALL);
    IMU_I2C_ClearSlaveInterruptSource (IMU_I2C_INTR_SLAVE_ALL);
    IMU_I2C_ClearMasterInterruptSource(IMU_I2C_INTR_MASTER_ALL);
#endif /* (IMU_I2C_CY_SCBIP_V0) */

    IMU_I2C_state = IMU_I2C_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    IMU_I2C_CTRL_REG |= (uint32) IMU_I2C_CTRL_ENABLED;
}


#if(IMU_I2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: IMU_I2C_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables IMU_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void IMU_I2C_I2CSaveConfig(void)
    {
    #if (!IMU_I2C_CY_SCBIP_V0)
        #if (IMU_I2C_I2C_MULTI_MASTER_SLAVE_CONST && IMU_I2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (IMU_I2C_CTRL_REG & IMU_I2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                IMU_I2C_Stop();
                IMU_I2C_CTRL_REG |= IMU_I2C_CTRL_EC_AM_MODE;
                IMU_I2C_Enable();
            }
        #endif /* (IMU_I2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (IMU_I2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            IMU_I2C_SCBCLK_Stop();
        #endif /* (IMU_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!IMU_I2C_CY_SCBIP_V0) */

        IMU_I2C_SetI2CExtClkInterruptMode(IMU_I2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: IMU_I2C_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables IMU_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void IMU_I2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        IMU_I2C_SetI2CExtClkInterruptMode(IMU_I2C_NO_INTR_SOURCES);

    #if (!IMU_I2C_CY_SCBIP_V0)
        #if (IMU_I2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            IMU_I2C_SCBCLK_Start();
        #endif /* (IMU_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!IMU_I2C_CY_SCBIP_V0) */
    }
#endif /* (IMU_I2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
