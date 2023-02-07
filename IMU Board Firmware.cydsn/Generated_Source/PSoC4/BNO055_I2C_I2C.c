/***************************************************************************//**
* \file BNO055_I2C_I2C.c
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

#include "BNO055_I2C_PVT.h"
#include "BNO055_I2C_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 BNO055_I2C_state;  /* Current state of I2C FSM */

#if(BNO055_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const BNO055_I2C_I2C_INIT_STRUCT BNO055_I2C_configI2C =
    {
        BNO055_I2C_I2C_MODE,
        BNO055_I2C_I2C_OVS_FACTOR_LOW,
        BNO055_I2C_I2C_OVS_FACTOR_HIGH,
        BNO055_I2C_I2C_MEDIAN_FILTER_ENABLE,
        BNO055_I2C_I2C_SLAVE_ADDRESS,
        BNO055_I2C_I2C_SLAVE_ADDRESS_MASK,
        BNO055_I2C_I2C_ACCEPT_ADDRESS,
        BNO055_I2C_I2C_WAKE_ENABLE,
        BNO055_I2C_I2C_BYTE_MODE_ENABLE,
        BNO055_I2C_I2C_DATA_RATE,
        BNO055_I2C_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: BNO055_I2C_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the BNO055_I2C for I2C operation.
    *
    *  This function is intended specifically to be used when the BNO055_I2C 
    *  configuration is set to “Unconfigured BNO055_I2C” in the customizer. 
    *  After initializing the BNO055_I2C in I2C mode using this function, 
    *  the component can be enabled using the BNO055_I2C_Start() or 
    * BNO055_I2C_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void BNO055_I2C_I2CInit(const BNO055_I2C_I2C_INIT_STRUCT *config)
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
            BNO055_I2C_SetPins(BNO055_I2C_SCB_MODE_I2C, BNO055_I2C_DUMMY_PARAM,
                                     BNO055_I2C_DUMMY_PARAM);

            /* Store internal configuration */
            BNO055_I2C_scbMode       = (uint8) BNO055_I2C_SCB_MODE_I2C;
            BNO055_I2C_scbEnableWake = (uint8) config->enableWake;
            BNO055_I2C_scbEnableIntr = (uint8) BNO055_I2C_SCB_IRQ_INTERNAL;

            BNO055_I2C_mode          = (uint8) config->mode;
            BNO055_I2C_acceptAddr    = (uint8) config->acceptAddr;

        #if (BNO055_I2C_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            BNO055_I2C_SET_I2C_CFG_SDA_FILT_TRIM(BNO055_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (BNO055_I2C_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((BNO055_I2C_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= BNO055_I2C_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (BNO055_I2C_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                BNO055_I2C_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = BNO055_I2C_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                BNO055_I2C_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = BNO055_I2C_DIGITAL_FILTER_ENABLE;
            }

        #if (!BNO055_I2C_CY_SCBIP_V0)
            locEnableWake = (BNO055_I2C_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!BNO055_I2C_CY_SCBIP_V0) */

            /* Configure I2C interface */
            BNO055_I2C_CTRL_REG     = BNO055_I2C_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            BNO055_I2C_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            BNO055_I2C_GET_CTRL_EC_AM_MODE (locEnableWake);

            BNO055_I2C_I2C_CTRL_REG = BNO055_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    BNO055_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    BNO055_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    BNO055_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            BNO055_I2C_RX_CTRL_REG      = BNO055_I2C_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                BNO055_I2C_I2C_RX_CTRL;
            BNO055_I2C_RX_FIFO_CTRL_REG = BNO055_I2C_CLEAR_REG;

            /* Set default address and mask */
            BNO055_I2C_RX_MATCH_REG    = ((BNO055_I2C_I2C_SLAVE) ?
                                                (BNO055_I2C_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 BNO055_I2C_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (BNO055_I2C_CLEAR_REG));


            /* Configure TX direction */
            BNO055_I2C_TX_CTRL_REG      = BNO055_I2C_I2C_TX_CTRL;
            BNO055_I2C_TX_FIFO_CTRL_REG = BNO055_I2C_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (BNO055_I2C_ISR_NUMBER);
            CyIntSetPriority(BNO055_I2C_ISR_NUMBER, BNO055_I2C_ISR_PRIORITY);
            (void) CyIntSetVector(BNO055_I2C_ISR_NUMBER, &BNO055_I2C_I2C_ISR);

            /* Configure interrupt sources */
        #if(!BNO055_I2C_CY_SCBIP_V1)
            BNO055_I2C_INTR_SPI_EC_MASK_REG = BNO055_I2C_NO_INTR_SOURCES;
        #endif /* (!BNO055_I2C_CY_SCBIP_V1) */

            BNO055_I2C_INTR_I2C_EC_MASK_REG = BNO055_I2C_NO_INTR_SOURCES;
            BNO055_I2C_INTR_RX_MASK_REG     = BNO055_I2C_NO_INTR_SOURCES;
            BNO055_I2C_INTR_TX_MASK_REG     = BNO055_I2C_NO_INTR_SOURCES;

            BNO055_I2C_INTR_SLAVE_MASK_REG  = ((BNO055_I2C_I2C_SLAVE) ?
                            (BNO055_I2C_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             BNO055_I2C_I2C_INTR_SLAVE_MASK) : (BNO055_I2C_CLEAR_REG));

            BNO055_I2C_INTR_MASTER_MASK_REG = BNO055_I2C_NO_INTR_SOURCES;

            /* Configure global variables */
            BNO055_I2C_state = BNO055_I2C_I2C_FSM_IDLE;

            /* Internal slave variables */
            BNO055_I2C_slStatus        = 0u;
            BNO055_I2C_slRdBufIndex    = 0u;
            BNO055_I2C_slWrBufIndex    = 0u;
            BNO055_I2C_slOverFlowCount = 0u;

            /* Internal master variables */
            BNO055_I2C_mstrStatus     = 0u;
            BNO055_I2C_mstrRdBufIndex = 0u;
            BNO055_I2C_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: BNO055_I2C_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void BNO055_I2C_I2CInit(void)
    {
    #if(BNO055_I2C_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        BNO055_I2C_SET_I2C_CFG_SDA_FILT_TRIM(BNO055_I2C_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (BNO055_I2C_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        BNO055_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        BNO055_I2C_CTRL_REG     = BNO055_I2C_I2C_DEFAULT_CTRL;
        BNO055_I2C_I2C_CTRL_REG = BNO055_I2C_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        BNO055_I2C_RX_CTRL_REG      = BNO055_I2C_I2C_DEFAULT_RX_CTRL;
        BNO055_I2C_RX_FIFO_CTRL_REG = BNO055_I2C_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        BNO055_I2C_RX_MATCH_REG     = BNO055_I2C_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        BNO055_I2C_TX_CTRL_REG      = BNO055_I2C_I2C_DEFAULT_TX_CTRL;
        BNO055_I2C_TX_FIFO_CTRL_REG = BNO055_I2C_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (BNO055_I2C_ISR_NUMBER);
        CyIntSetPriority(BNO055_I2C_ISR_NUMBER, BNO055_I2C_ISR_PRIORITY);
    #if(!BNO055_I2C_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(BNO055_I2C_ISR_NUMBER, &BNO055_I2C_I2C_ISR);
    #endif /* (BNO055_I2C_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!BNO055_I2C_CY_SCBIP_V1)
        BNO055_I2C_INTR_SPI_EC_MASK_REG = BNO055_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!BNO055_I2C_CY_SCBIP_V1) */

        BNO055_I2C_INTR_I2C_EC_MASK_REG = BNO055_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK;
        BNO055_I2C_INTR_SLAVE_MASK_REG  = BNO055_I2C_I2C_DEFAULT_INTR_SLAVE_MASK;
        BNO055_I2C_INTR_MASTER_MASK_REG = BNO055_I2C_I2C_DEFAULT_INTR_MASTER_MASK;
        BNO055_I2C_INTR_RX_MASK_REG     = BNO055_I2C_I2C_DEFAULT_INTR_RX_MASK;
        BNO055_I2C_INTR_TX_MASK_REG     = BNO055_I2C_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        BNO055_I2C_state = BNO055_I2C_I2C_FSM_IDLE;

    #if(BNO055_I2C_I2C_SLAVE)
        /* Internal slave variable */
        BNO055_I2C_slStatus        = 0u;
        BNO055_I2C_slRdBufIndex    = 0u;
        BNO055_I2C_slWrBufIndex    = 0u;
        BNO055_I2C_slOverFlowCount = 0u;
    #endif /* (BNO055_I2C_I2C_SLAVE) */

    #if(BNO055_I2C_I2C_MASTER)
    /* Internal master variable */
        BNO055_I2C_mstrStatus     = 0u;
        BNO055_I2C_mstrRdBufIndex = 0u;
        BNO055_I2C_mstrWrBufIndex = 0u;
    #endif /* (BNO055_I2C_I2C_MASTER) */
    }
#endif /* (BNO055_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: BNO055_I2C_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void BNO055_I2C_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    BNO055_I2C_I2C_MASTER_CMD_REG = 0u;
    BNO055_I2C_I2C_SLAVE_CMD_REG  = 0u;
    
    BNO055_I2C_state = BNO055_I2C_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: BNO055_I2C_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void BNO055_I2C_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    BNO055_I2C_CTRL_REG &= (uint32) ~BNO055_I2C_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    BNO055_I2C_I2C_MASTER_CMD_REG = 0u;
    BNO055_I2C_I2C_SLAVE_CMD_REG  = 0u;

    BNO055_I2C_DISABLE_AUTO_DATA;

    BNO055_I2C_SetTxInterruptMode(BNO055_I2C_NO_INTR_SOURCES);
    BNO055_I2C_SetRxInterruptMode(BNO055_I2C_NO_INTR_SOURCES);
    
#if(BNO055_I2C_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    BNO055_I2C_ClearTxInterruptSource    (BNO055_I2C_INTR_TX_ALL);
    BNO055_I2C_ClearRxInterruptSource    (BNO055_I2C_INTR_RX_ALL);
    BNO055_I2C_ClearSlaveInterruptSource (BNO055_I2C_INTR_SLAVE_ALL);
    BNO055_I2C_ClearMasterInterruptSource(BNO055_I2C_INTR_MASTER_ALL);
#endif /* (BNO055_I2C_CY_SCBIP_V0) */

    BNO055_I2C_state = BNO055_I2C_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    BNO055_I2C_CTRL_REG |= (uint32) BNO055_I2C_CTRL_ENABLED;
}


#if(BNO055_I2C_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: BNO055_I2C_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables BNO055_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void BNO055_I2C_I2CSaveConfig(void)
    {
    #if (!BNO055_I2C_CY_SCBIP_V0)
        #if (BNO055_I2C_I2C_MULTI_MASTER_SLAVE_CONST && BNO055_I2C_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (BNO055_I2C_CTRL_REG & BNO055_I2C_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                BNO055_I2C_Stop();
                BNO055_I2C_CTRL_REG |= BNO055_I2C_CTRL_EC_AM_MODE;
                BNO055_I2C_Enable();
            }
        #endif /* (BNO055_I2C_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (BNO055_I2C_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            BNO055_I2C_SCBCLK_Stop();
        #endif /* (BNO055_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!BNO055_I2C_CY_SCBIP_V0) */

        BNO055_I2C_SetI2CExtClkInterruptMode(BNO055_I2C_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: BNO055_I2C_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables BNO055_I2C_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void BNO055_I2C_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        BNO055_I2C_SetI2CExtClkInterruptMode(BNO055_I2C_NO_INTR_SOURCES);

    #if (!BNO055_I2C_CY_SCBIP_V0)
        #if (BNO055_I2C_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            BNO055_I2C_SCBCLK_Start();
        #endif /* (BNO055_I2C_SCB_CLK_INTERNAL) */
    #endif /* (!BNO055_I2C_CY_SCBIP_V0) */
    }
#endif /* (BNO055_I2C_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
