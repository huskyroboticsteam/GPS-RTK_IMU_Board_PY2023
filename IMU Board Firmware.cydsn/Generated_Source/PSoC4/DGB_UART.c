/***************************************************************************//**
* \file DGB_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#include "DGB_UART_PVT.h"

#if (DGB_UART_SCB_MODE_I2C_INC)
    #include "DGB_UART_I2C_PVT.h"
#endif /* (DGB_UART_SCB_MODE_I2C_INC) */

#if (DGB_UART_SCB_MODE_EZI2C_INC)
    #include "DGB_UART_EZI2C_PVT.h"
#endif /* (DGB_UART_SCB_MODE_EZI2C_INC) */

#if (DGB_UART_SCB_MODE_SPI_INC || DGB_UART_SCB_MODE_UART_INC)
    #include "DGB_UART_SPI_UART_PVT.h"
#endif /* (DGB_UART_SCB_MODE_SPI_INC || DGB_UART_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 DGB_UART_scbMode = DGB_UART_SCB_MODE_UNCONFIG;
    uint8 DGB_UART_scbEnableWake;
    uint8 DGB_UART_scbEnableIntr;

    /* I2C configuration variables */
    uint8 DGB_UART_mode;
    uint8 DGB_UART_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * DGB_UART_rxBuffer;
    uint8  DGB_UART_rxDataBits;
    uint32 DGB_UART_rxBufferSize;

    volatile uint8 * DGB_UART_txBuffer;
    uint8  DGB_UART_txDataBits;
    uint32 DGB_UART_txBufferSize;

    /* EZI2C configuration variables */
    uint8 DGB_UART_numberOfAddr;
    uint8 DGB_UART_subAddrSize;
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** DGB_UART_initVar indicates whether the DGB_UART 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the DGB_UART_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  DGB_UART_Init() function can be called before the 
*  DGB_UART_Start() or DGB_UART_Enable() function.
*/
uint8 DGB_UART_initVar = 0u;


#if (! (DGB_UART_SCB_MODE_I2C_CONST_CFG || \
        DGB_UART_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * DGB_UART_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent DGB_UART_Enable() call.
    */
    uint16 DGB_UART_IntrTxMask = 0u;
#endif /* (! (DGB_UART_SCB_MODE_I2C_CONST_CFG || \
              DGB_UART_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (DGB_UART_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DGB_UART_CUSTOM_INTR_HANDLER)
    void (*DGB_UART_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_DGB_UART_CUSTOM_INTR_HANDLER) */
#endif /* (DGB_UART_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void DGB_UART_ScbEnableIntr(void);
static void DGB_UART_ScbModeStop(void);
static void DGB_UART_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: DGB_UART_Init
****************************************************************************//**
*
*  Initializes the DGB_UART component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  DGB_UART_I2CInit, DGB_UART_SpiInit, 
*  DGB_UART_UartInit or DGB_UART_EzI2CInit.
*
*******************************************************************************/
void DGB_UART_Init(void)
{
#if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DGB_UART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DGB_UART_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (DGB_UART_SCB_MODE_I2C_CONST_CFG)
    DGB_UART_I2CInit();

#elif (DGB_UART_SCB_MODE_SPI_CONST_CFG)
    DGB_UART_SpiInit();

#elif (DGB_UART_SCB_MODE_UART_CONST_CFG)
    DGB_UART_UartInit();

#elif (DGB_UART_SCB_MODE_EZI2C_CONST_CFG)
    DGB_UART_EzI2CInit();

#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DGB_UART_Enable
****************************************************************************//**
*
*  Enables DGB_UART component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  DGB_UART_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The DGB_UART configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured DGB_UART”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void DGB_UART_Enable(void)
{
#if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!DGB_UART_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DGB_UART_CTRL_REG |= DGB_UART_CTRL_ENABLED;

        DGB_UART_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        DGB_UART_ScbModePostEnable();
    }
#else
    DGB_UART_CTRL_REG |= DGB_UART_CTRL_ENABLED;

    DGB_UART_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    DGB_UART_ScbModePostEnable();
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DGB_UART_Start
****************************************************************************//**
*
*  Invokes DGB_UART_Init() and DGB_UART_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  DGB_UART_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void DGB_UART_Start(void)
{
    if (0u == DGB_UART_initVar)
    {
        DGB_UART_Init();
        DGB_UART_initVar = 1u; /* Component was initialized */
    }

    DGB_UART_Enable();
}


/*******************************************************************************
* Function Name: DGB_UART_Stop
****************************************************************************//**
*
*  Disables the DGB_UART component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function DGB_UART_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void DGB_UART_Stop(void)
{
#if (DGB_UART_SCB_IRQ_INTERNAL)
    DGB_UART_DisableInt();
#endif /* (DGB_UART_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    DGB_UART_ScbModeStop();

    /* Disable SCB IP */
    DGB_UART_CTRL_REG &= (uint32) ~DGB_UART_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    DGB_UART_SetTxInterruptMode(DGB_UART_NO_INTR_SOURCES);

#if (DGB_UART_SCB_IRQ_INTERNAL)
    DGB_UART_ClearPendingInt();
#endif /* (DGB_UART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DGB_UART_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void DGB_UART_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = DGB_UART_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~DGB_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (DGB_UART_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DGB_UART_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: DGB_UART_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void DGB_UART_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = DGB_UART_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~DGB_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (DGB_UART_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DGB_UART_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (DGB_UART_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: DGB_UART_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void DGB_UART_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_DGB_UART_CUSTOM_INTR_HANDLER)
        DGB_UART_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_DGB_UART_CUSTOM_INTR_HANDLER) */
    }
#endif /* (DGB_UART_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: DGB_UART_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void DGB_UART_ScbEnableIntr(void)
{
#if (DGB_UART_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != DGB_UART_scbEnableIntr)
        {
            DGB_UART_EnableInt();
        }

    #else
        DGB_UART_EnableInt();

    #endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (DGB_UART_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DGB_UART_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void DGB_UART_ScbModePostEnable(void)
{
#if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!DGB_UART_CY_SCBIP_V1)
    if (DGB_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DGB_UART_SpiPostEnable();
    }
    else if (DGB_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DGB_UART_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!DGB_UART_CY_SCBIP_V1) */

#elif (DGB_UART_SCB_MODE_SPI_CONST_CFG)
    DGB_UART_SpiPostEnable();

#elif (DGB_UART_SCB_MODE_UART_CONST_CFG)
    DGB_UART_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DGB_UART_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void DGB_UART_ScbModeStop(void)
{
#if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DGB_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        DGB_UART_I2CStop();
    }
    else if (DGB_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DGB_UART_EzI2CStop();
    }
#if (!DGB_UART_CY_SCBIP_V1)
    else if (DGB_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DGB_UART_SpiStop();
    }
    else if (DGB_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DGB_UART_UartStop();
    }
#endif /* (!DGB_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (DGB_UART_SCB_MODE_I2C_CONST_CFG)
    DGB_UART_I2CStop();

#elif (DGB_UART_SCB_MODE_EZI2C_CONST_CFG)
    DGB_UART_EzI2CStop();

#elif (DGB_UART_SCB_MODE_SPI_CONST_CFG)
    DGB_UART_SpiStop();

#elif (DGB_UART_SCB_MODE_UART_CONST_CFG)
    DGB_UART_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: DGB_UART_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void DGB_UART_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[DGB_UART_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!DGB_UART_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!DGB_UART_CY_SCBIP_V1) */
        
        uint32 hsiomSel[DGB_UART_SCB_PINS_NUMBER] = 
        {
            DGB_UART_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            DGB_UART_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (DGB_UART_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (DGB_UART_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < DGB_UART_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = DGB_UART_PIN_DM_ALG_HIZ;
        }

        if ((DGB_UART_SCB_MODE_I2C   == mode) ||
            (DGB_UART_SCB_MODE_EZI2C == mode))
        {
        #if (DGB_UART_RX_SCL_MOSI_PIN)
            hsiomSel[DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_PIN_DM_OD_LO;
        #elif (DGB_UART_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DGB_UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DGB_UART_PIN_DM_OD_LO;
        #else
        #endif /* (DGB_UART_RX_SCL_MOSI_PIN) */
        
        #if (DGB_UART_TX_SDA_MISO_PIN)
            hsiomSel[DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_PIN_DM_OD_LO;
        #endif /* (DGB_UART_TX_SDA_MISO_PIN) */
        }
    #if (!DGB_UART_CY_SCBIP_V1)
        else if (DGB_UART_SCB_MODE_SPI == mode)
        {
        #if (DGB_UART_RX_SCL_MOSI_PIN)
            hsiomSel[DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (DGB_UART_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DGB_UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (DGB_UART_RX_SCL_MOSI_PIN) */
        
        #if (DGB_UART_TX_SDA_MISO_PIN)
            hsiomSel[DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (DGB_UART_TX_SDA_MISO_PIN) */
        
        #if (DGB_UART_CTS_SCLK_PIN)
            hsiomSel[DGB_UART_CTS_SCLK_PIN_INDEX] = DGB_UART_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (DGB_UART_CTS_SCLK_PIN) */

            if (DGB_UART_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;
                pinsDm[DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                pinsDm[DGB_UART_CTS_SCLK_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;

            #if (DGB_UART_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[DGB_UART_RTS_SS0_PIN_INDEX] = DGB_UART_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [DGB_UART_RTS_SS0_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;
            #endif /* (DGB_UART_RTS_SS0_PIN) */

            #if (DGB_UART_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= DGB_UART_TX_SDA_MISO_PIN_MASK;
            #endif /* (DGB_UART_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                pinsDm[DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;
                pinsDm[DGB_UART_CTS_SCLK_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;

            #if (DGB_UART_RTS_SS0_PIN)
                hsiomSel [DGB_UART_RTS_SS0_PIN_INDEX] = DGB_UART_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [DGB_UART_RTS_SS0_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                pinsInBuf |= DGB_UART_RTS_SS0_PIN_MASK;
            #endif /* (DGB_UART_RTS_SS0_PIN) */

            #if (DGB_UART_SS1_PIN)
                hsiomSel [DGB_UART_SS1_PIN_INDEX] = DGB_UART_SS1_HSIOM_SEL_SPI;
                pinsDm   [DGB_UART_SS1_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                pinsInBuf |= DGB_UART_SS1_PIN_MASK;
            #endif /* (DGB_UART_SS1_PIN) */

            #if (DGB_UART_SS2_PIN)
                hsiomSel [DGB_UART_SS2_PIN_INDEX] = DGB_UART_SS2_HSIOM_SEL_SPI;
                pinsDm   [DGB_UART_SS2_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                pinsInBuf |= DGB_UART_SS2_PIN_MASK;
            #endif /* (DGB_UART_SS2_PIN) */

            #if (DGB_UART_SS3_PIN)
                hsiomSel [DGB_UART_SS3_PIN_INDEX] = DGB_UART_SS3_HSIOM_SEL_SPI;
                pinsDm   [DGB_UART_SS3_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                pinsInBuf |= DGB_UART_SS3_PIN_MASK;
            #endif /* (DGB_UART_SS3_PIN) */

                /* Disable input buffers */
            #if (DGB_UART_RX_SCL_MOSI_PIN)
                pinsInBuf |= DGB_UART_RX_SCL_MOSI_PIN_MASK;
            #elif (DGB_UART_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= DGB_UART_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (DGB_UART_RX_SCL_MOSI_PIN) */

            #if (DGB_UART_CTS_SCLK_PIN)
                pinsInBuf |= DGB_UART_CTS_SCLK_PIN_MASK;
            #endif /* (DGB_UART_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (DGB_UART_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (DGB_UART_TX_SDA_MISO_PIN)
                hsiomSel[DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_PIN_DM_OD_LO;
            #endif /* (DGB_UART_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (DGB_UART_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (DGB_UART_RX_SCL_MOSI_PIN)
                    hsiomSel[DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DGB_UART_RX_SCL_MOSI_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;
                #elif (DGB_UART_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DGB_UART_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;
                #else
                #endif /* (DGB_UART_RX_SCL_MOSI_PIN) */
                }

                if (0u != (DGB_UART_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (DGB_UART_TX_SDA_MISO_PIN)
                    hsiomSel[DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [DGB_UART_TX_SDA_MISO_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= DGB_UART_TX_SDA_MISO_PIN_MASK;
                #endif /* (DGB_UART_TX_SDA_MISO_PIN) */
                }

            #if !(DGB_UART_CY_SCBIP_V0 || DGB_UART_CY_SCBIP_V1)
                if (DGB_UART_UART_MODE_STD == subMode)
                {
                    if (0u != (DGB_UART_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (DGB_UART_CTS_SCLK_PIN)
                        hsiomSel[DGB_UART_CTS_SCLK_PIN_INDEX] = DGB_UART_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [DGB_UART_CTS_SCLK_PIN_INDEX] = DGB_UART_PIN_DM_DIG_HIZ;
                    #endif /* (DGB_UART_CTS_SCLK_PIN) */
                    }

                    if (0u != (DGB_UART_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (DGB_UART_RTS_SS0_PIN)
                        hsiomSel[DGB_UART_RTS_SS0_PIN_INDEX] = DGB_UART_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [DGB_UART_RTS_SS0_PIN_INDEX] = DGB_UART_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= DGB_UART_RTS_SS0_PIN_MASK;
                    #endif /* (DGB_UART_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(DGB_UART_CY_SCBIP_V0 || DGB_UART_CY_SCBIP_V1) */
            }
        }
    #endif /* (!DGB_UART_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (DGB_UART_RX_SCL_MOSI_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_RX_SCL_MOSI_HSIOM_REG,
                                       DGB_UART_RX_SCL_MOSI_HSIOM_MASK,
                                       DGB_UART_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[DGB_UART_RX_SCL_MOSI_PIN_INDEX]);

        DGB_UART_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[DGB_UART_RX_SCL_MOSI_PIN_INDEX]);

        #if (!DGB_UART_CY_SCBIP_V1)
            DGB_UART_SET_INP_DIS(DGB_UART_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         DGB_UART_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & DGB_UART_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!DGB_UART_CY_SCBIP_V1) */
    
    #elif (DGB_UART_RX_WAKE_SCL_MOSI_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       DGB_UART_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       DGB_UART_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DGB_UART_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[DGB_UART_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DGB_UART_SET_INP_DIS(DGB_UART_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     DGB_UART_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & DGB_UART_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        DGB_UART_SET_INCFG_TYPE(DGB_UART_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        DGB_UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        DGB_UART_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        DGB_UART_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (DGB_UART_RX_WAKE_SCL_MOSI_PIN) */

    #if (DGB_UART_TX_SDA_MISO_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_TX_SDA_MISO_HSIOM_REG,
                                       DGB_UART_TX_SDA_MISO_HSIOM_MASK,
                                       DGB_UART_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[DGB_UART_TX_SDA_MISO_PIN_INDEX]);

        DGB_UART_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[DGB_UART_TX_SDA_MISO_PIN_INDEX]);

    #if (!DGB_UART_CY_SCBIP_V1)
        DGB_UART_SET_INP_DIS(DGB_UART_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     DGB_UART_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & DGB_UART_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!DGB_UART_CY_SCBIP_V1) */
    #endif /* (DGB_UART_RX_SCL_MOSI_PIN) */

    #if (DGB_UART_CTS_SCLK_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_CTS_SCLK_HSIOM_REG,
                                       DGB_UART_CTS_SCLK_HSIOM_MASK,
                                       DGB_UART_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[DGB_UART_CTS_SCLK_PIN_INDEX]);

        DGB_UART_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[DGB_UART_CTS_SCLK_PIN_INDEX]);

        DGB_UART_SET_INP_DIS(DGB_UART_uart_cts_spi_sclk_INP_DIS,
                                     DGB_UART_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & DGB_UART_CTS_SCLK_PIN_MASK)));
    #endif /* (DGB_UART_CTS_SCLK_PIN) */

    #if (DGB_UART_RTS_SS0_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_RTS_SS0_HSIOM_REG,
                                       DGB_UART_RTS_SS0_HSIOM_MASK,
                                       DGB_UART_RTS_SS0_HSIOM_POS,
                                       hsiomSel[DGB_UART_RTS_SS0_PIN_INDEX]);

        DGB_UART_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[DGB_UART_RTS_SS0_PIN_INDEX]);

        DGB_UART_SET_INP_DIS(DGB_UART_uart_rts_spi_ss0_INP_DIS,
                                     DGB_UART_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & DGB_UART_RTS_SS0_PIN_MASK)));
    #endif /* (DGB_UART_RTS_SS0_PIN) */

    #if (DGB_UART_SS1_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_SS1_HSIOM_REG,
                                       DGB_UART_SS1_HSIOM_MASK,
                                       DGB_UART_SS1_HSIOM_POS,
                                       hsiomSel[DGB_UART_SS1_PIN_INDEX]);

        DGB_UART_spi_ss1_SetDriveMode((uint8) pinsDm[DGB_UART_SS1_PIN_INDEX]);

        DGB_UART_SET_INP_DIS(DGB_UART_spi_ss1_INP_DIS,
                                     DGB_UART_spi_ss1_MASK,
                                     (0u != (pinsInBuf & DGB_UART_SS1_PIN_MASK)));
    #endif /* (DGB_UART_SS1_PIN) */

    #if (DGB_UART_SS2_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_SS2_HSIOM_REG,
                                       DGB_UART_SS2_HSIOM_MASK,
                                       DGB_UART_SS2_HSIOM_POS,
                                       hsiomSel[DGB_UART_SS2_PIN_INDEX]);

        DGB_UART_spi_ss2_SetDriveMode((uint8) pinsDm[DGB_UART_SS2_PIN_INDEX]);

        DGB_UART_SET_INP_DIS(DGB_UART_spi_ss2_INP_DIS,
                                     DGB_UART_spi_ss2_MASK,
                                     (0u != (pinsInBuf & DGB_UART_SS2_PIN_MASK)));
    #endif /* (DGB_UART_SS2_PIN) */

    #if (DGB_UART_SS3_PIN)
        DGB_UART_SET_HSIOM_SEL(DGB_UART_SS3_HSIOM_REG,
                                       DGB_UART_SS3_HSIOM_MASK,
                                       DGB_UART_SS3_HSIOM_POS,
                                       hsiomSel[DGB_UART_SS3_PIN_INDEX]);

        DGB_UART_spi_ss3_SetDriveMode((uint8) pinsDm[DGB_UART_SS3_PIN_INDEX]);

        DGB_UART_SET_INP_DIS(DGB_UART_spi_ss3_INP_DIS,
                                     DGB_UART_spi_ss3_MASK,
                                     (0u != (pinsInBuf & DGB_UART_SS3_PIN_MASK)));
    #endif /* (DGB_UART_SS3_PIN) */
    }

#endif /* (DGB_UART_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (DGB_UART_CY_SCBIP_V0 || DGB_UART_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: DGB_UART_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void DGB_UART_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (DGB_UART_CTRL_REG & DGB_UART_CTRL_EC_AM_MODE)) &&
            (0u == (DGB_UART_I2C_CTRL_REG & DGB_UART_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            DGB_UART_CTRL_REG &= ~DGB_UART_CTRL_EC_AM_MODE;
            DGB_UART_CTRL_REG |=  DGB_UART_CTRL_EC_AM_MODE;
        }

        DGB_UART_I2C_SLAVE_CMD_REG = DGB_UART_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (DGB_UART_CY_SCBIP_V0 || DGB_UART_CY_SCBIP_V1) */


/* [] END OF FILE */
