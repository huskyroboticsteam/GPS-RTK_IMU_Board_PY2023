/***************************************************************************//**
* \file DEBUG.c
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

#include "DEBUG_PVT.h"

#if (DEBUG_SCB_MODE_I2C_INC)
    #include "DEBUG_I2C_PVT.h"
#endif /* (DEBUG_SCB_MODE_I2C_INC) */

#if (DEBUG_SCB_MODE_EZI2C_INC)
    #include "DEBUG_EZI2C_PVT.h"
#endif /* (DEBUG_SCB_MODE_EZI2C_INC) */

#if (DEBUG_SCB_MODE_SPI_INC || DEBUG_SCB_MODE_UART_INC)
    #include "DEBUG_SPI_UART_PVT.h"
#endif /* (DEBUG_SCB_MODE_SPI_INC || DEBUG_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 DEBUG_scbMode = DEBUG_SCB_MODE_UNCONFIG;
    uint8 DEBUG_scbEnableWake;
    uint8 DEBUG_scbEnableIntr;

    /* I2C configuration variables */
    uint8 DEBUG_mode;
    uint8 DEBUG_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * DEBUG_rxBuffer;
    uint8  DEBUG_rxDataBits;
    uint32 DEBUG_rxBufferSize;

    volatile uint8 * DEBUG_txBuffer;
    uint8  DEBUG_txDataBits;
    uint32 DEBUG_txBufferSize;

    /* EZI2C configuration variables */
    uint8 DEBUG_numberOfAddr;
    uint8 DEBUG_subAddrSize;
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** DEBUG_initVar indicates whether the DEBUG 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the DEBUG_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  DEBUG_Init() function can be called before the 
*  DEBUG_Start() or DEBUG_Enable() function.
*/
uint8 DEBUG_initVar = 0u;


#if (! (DEBUG_SCB_MODE_I2C_CONST_CFG || \
        DEBUG_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * DEBUG_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent DEBUG_Enable() call.
    */
    uint16 DEBUG_IntrTxMask = 0u;
#endif /* (! (DEBUG_SCB_MODE_I2C_CONST_CFG || \
              DEBUG_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (DEBUG_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_DEBUG_CUSTOM_INTR_HANDLER)
    void (*DEBUG_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_DEBUG_CUSTOM_INTR_HANDLER) */
#endif /* (DEBUG_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void DEBUG_ScbEnableIntr(void);
static void DEBUG_ScbModeStop(void);
static void DEBUG_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: DEBUG_Init
****************************************************************************//**
*
*  Initializes the DEBUG component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  DEBUG_I2CInit, DEBUG_SpiInit, 
*  DEBUG_UartInit or DEBUG_EzI2CInit.
*
*******************************************************************************/
void DEBUG_Init(void)
{
#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DEBUG_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (DEBUG_SCB_MODE_I2C_CONST_CFG)
    DEBUG_I2CInit();

#elif (DEBUG_SCB_MODE_SPI_CONST_CFG)
    DEBUG_SpiInit();

#elif (DEBUG_SCB_MODE_UART_CONST_CFG)
    DEBUG_UartInit();

#elif (DEBUG_SCB_MODE_EZI2C_CONST_CFG)
    DEBUG_EzI2CInit();

#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DEBUG_Enable
****************************************************************************//**
*
*  Enables DEBUG component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  DEBUG_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The DEBUG configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured DEBUG”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void DEBUG_Enable(void)
{
#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        DEBUG_CTRL_REG |= DEBUG_CTRL_ENABLED;

        DEBUG_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        DEBUG_ScbModePostEnable();
    }
#else
    DEBUG_CTRL_REG |= DEBUG_CTRL_ENABLED;

    DEBUG_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    DEBUG_ScbModePostEnable();
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DEBUG_Start
****************************************************************************//**
*
*  Invokes DEBUG_Init() and DEBUG_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  DEBUG_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void DEBUG_Start(void)
{
    if (0u == DEBUG_initVar)
    {
        DEBUG_Init();
        DEBUG_initVar = 1u; /* Component was initialized */
    }

    DEBUG_Enable();
}


/*******************************************************************************
* Function Name: DEBUG_Stop
****************************************************************************//**
*
*  Disables the DEBUG component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function DEBUG_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void DEBUG_Stop(void)
{
#if (DEBUG_SCB_IRQ_INTERNAL)
    DEBUG_DisableInt();
#endif /* (DEBUG_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    DEBUG_ScbModeStop();

    /* Disable SCB IP */
    DEBUG_CTRL_REG &= (uint32) ~DEBUG_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    DEBUG_SetTxInterruptMode(DEBUG_NO_INTR_SOURCES);

#if (DEBUG_SCB_IRQ_INTERNAL)
    DEBUG_ClearPendingInt();
#endif /* (DEBUG_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DEBUG_SetRxFifoLevel
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
void DEBUG_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = DEBUG_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~DEBUG_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (DEBUG_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DEBUG_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: DEBUG_SetTxFifoLevel
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
void DEBUG_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = DEBUG_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~DEBUG_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (DEBUG_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    DEBUG_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (DEBUG_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: DEBUG_SetCustomInterruptHandler
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
    void DEBUG_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_DEBUG_CUSTOM_INTR_HANDLER)
        DEBUG_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_DEBUG_CUSTOM_INTR_HANDLER) */
    }
#endif /* (DEBUG_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: DEBUG_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void DEBUG_ScbEnableIntr(void)
{
#if (DEBUG_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != DEBUG_scbEnableIntr)
        {
            DEBUG_EnableInt();
        }

    #else
        DEBUG_EnableInt();

    #endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (DEBUG_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: DEBUG_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void DEBUG_ScbModePostEnable(void)
{
#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!DEBUG_CY_SCBIP_V1)
    if (DEBUG_SCB_MODE_SPI_RUNTM_CFG)
    {
        DEBUG_SpiPostEnable();
    }
    else if (DEBUG_SCB_MODE_UART_RUNTM_CFG)
    {
        DEBUG_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!DEBUG_CY_SCBIP_V1) */

#elif (DEBUG_SCB_MODE_SPI_CONST_CFG)
    DEBUG_SpiPostEnable();

#elif (DEBUG_SCB_MODE_UART_CONST_CFG)
    DEBUG_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: DEBUG_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void DEBUG_ScbModeStop(void)
{
#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    if (DEBUG_SCB_MODE_I2C_RUNTM_CFG)
    {
        DEBUG_I2CStop();
    }
    else if (DEBUG_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DEBUG_EzI2CStop();
    }
#if (!DEBUG_CY_SCBIP_V1)
    else if (DEBUG_SCB_MODE_SPI_RUNTM_CFG)
    {
        DEBUG_SpiStop();
    }
    else if (DEBUG_SCB_MODE_UART_RUNTM_CFG)
    {
        DEBUG_UartStop();
    }
#endif /* (!DEBUG_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (DEBUG_SCB_MODE_I2C_CONST_CFG)
    DEBUG_I2CStop();

#elif (DEBUG_SCB_MODE_EZI2C_CONST_CFG)
    DEBUG_EzI2CStop();

#elif (DEBUG_SCB_MODE_SPI_CONST_CFG)
    DEBUG_SpiStop();

#elif (DEBUG_SCB_MODE_UART_CONST_CFG)
    DEBUG_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: DEBUG_SetPins
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
    void DEBUG_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[DEBUG_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!DEBUG_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!DEBUG_CY_SCBIP_V1) */
        
        uint32 hsiomSel[DEBUG_SCB_PINS_NUMBER] = 
        {
            DEBUG_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            DEBUG_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (DEBUG_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (DEBUG_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < DEBUG_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = DEBUG_PIN_DM_ALG_HIZ;
        }

        if ((DEBUG_SCB_MODE_I2C   == mode) ||
            (DEBUG_SCB_MODE_EZI2C == mode))
        {
        #if (DEBUG_RX_SCL_MOSI_PIN)
            hsiomSel[DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_PIN_DM_OD_LO;
        #elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = DEBUG_PIN_DM_OD_LO;
        #else
        #endif /* (DEBUG_RX_SCL_MOSI_PIN) */
        
        #if (DEBUG_TX_SDA_MISO_PIN)
            hsiomSel[DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_PIN_DM_OD_LO;
        #endif /* (DEBUG_TX_SDA_MISO_PIN) */
        }
    #if (!DEBUG_CY_SCBIP_V1)
        else if (DEBUG_SCB_MODE_SPI == mode)
        {
        #if (DEBUG_RX_SCL_MOSI_PIN)
            hsiomSel[DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (DEBUG_RX_SCL_MOSI_PIN) */
        
        #if (DEBUG_TX_SDA_MISO_PIN)
            hsiomSel[DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (DEBUG_TX_SDA_MISO_PIN) */
        
        #if (DEBUG_CTS_SCLK_PIN)
            hsiomSel[DEBUG_CTS_SCLK_PIN_INDEX] = DEBUG_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (DEBUG_CTS_SCLK_PIN) */

            if (DEBUG_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;
                pinsDm[DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                pinsDm[DEBUG_CTS_SCLK_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;

            #if (DEBUG_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[DEBUG_RTS_SS0_PIN_INDEX] = DEBUG_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [DEBUG_RTS_SS0_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;
            #endif /* (DEBUG_RTS_SS0_PIN) */

            #if (DEBUG_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= DEBUG_TX_SDA_MISO_PIN_MASK;
            #endif /* (DEBUG_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                pinsDm[DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;
                pinsDm[DEBUG_CTS_SCLK_PIN_INDEX] = DEBUG_PIN_DM_STRONG;

            #if (DEBUG_RTS_SS0_PIN)
                hsiomSel [DEBUG_RTS_SS0_PIN_INDEX] = DEBUG_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [DEBUG_RTS_SS0_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                pinsInBuf |= DEBUG_RTS_SS0_PIN_MASK;
            #endif /* (DEBUG_RTS_SS0_PIN) */

            #if (DEBUG_SS1_PIN)
                hsiomSel [DEBUG_SS1_PIN_INDEX] = DEBUG_SS1_HSIOM_SEL_SPI;
                pinsDm   [DEBUG_SS1_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                pinsInBuf |= DEBUG_SS1_PIN_MASK;
            #endif /* (DEBUG_SS1_PIN) */

            #if (DEBUG_SS2_PIN)
                hsiomSel [DEBUG_SS2_PIN_INDEX] = DEBUG_SS2_HSIOM_SEL_SPI;
                pinsDm   [DEBUG_SS2_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                pinsInBuf |= DEBUG_SS2_PIN_MASK;
            #endif /* (DEBUG_SS2_PIN) */

            #if (DEBUG_SS3_PIN)
                hsiomSel [DEBUG_SS3_PIN_INDEX] = DEBUG_SS3_HSIOM_SEL_SPI;
                pinsDm   [DEBUG_SS3_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                pinsInBuf |= DEBUG_SS3_PIN_MASK;
            #endif /* (DEBUG_SS3_PIN) */

                /* Disable input buffers */
            #if (DEBUG_RX_SCL_MOSI_PIN)
                pinsInBuf |= DEBUG_RX_SCL_MOSI_PIN_MASK;
            #elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= DEBUG_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (DEBUG_RX_SCL_MOSI_PIN) */

            #if (DEBUG_CTS_SCLK_PIN)
                pinsInBuf |= DEBUG_CTS_SCLK_PIN_MASK;
            #endif /* (DEBUG_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (DEBUG_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (DEBUG_TX_SDA_MISO_PIN)
                hsiomSel[DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_PIN_DM_OD_LO;
            #endif /* (DEBUG_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (DEBUG_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (DEBUG_RX_SCL_MOSI_PIN)
                    hsiomSel[DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DEBUG_RX_SCL_MOSI_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;
                #elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;
                #else
                #endif /* (DEBUG_RX_SCL_MOSI_PIN) */
                }

                if (0u != (DEBUG_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (DEBUG_TX_SDA_MISO_PIN)
                    hsiomSel[DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [DEBUG_TX_SDA_MISO_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= DEBUG_TX_SDA_MISO_PIN_MASK;
                #endif /* (DEBUG_TX_SDA_MISO_PIN) */
                }

            #if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
                if (DEBUG_UART_MODE_STD == subMode)
                {
                    if (0u != (DEBUG_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (DEBUG_CTS_SCLK_PIN)
                        hsiomSel[DEBUG_CTS_SCLK_PIN_INDEX] = DEBUG_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [DEBUG_CTS_SCLK_PIN_INDEX] = DEBUG_PIN_DM_DIG_HIZ;
                    #endif /* (DEBUG_CTS_SCLK_PIN) */
                    }

                    if (0u != (DEBUG_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (DEBUG_RTS_SS0_PIN)
                        hsiomSel[DEBUG_RTS_SS0_PIN_INDEX] = DEBUG_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [DEBUG_RTS_SS0_PIN_INDEX] = DEBUG_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= DEBUG_RTS_SS0_PIN_MASK;
                    #endif /* (DEBUG_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */
            }
        }
    #endif /* (!DEBUG_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (DEBUG_RX_SCL_MOSI_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_RX_SCL_MOSI_HSIOM_REG,
                                       DEBUG_RX_SCL_MOSI_HSIOM_MASK,
                                       DEBUG_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[DEBUG_RX_SCL_MOSI_PIN_INDEX]);

        DEBUG_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[DEBUG_RX_SCL_MOSI_PIN_INDEX]);

        #if (!DEBUG_CY_SCBIP_V1)
            DEBUG_SET_INP_DIS(DEBUG_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         DEBUG_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & DEBUG_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!DEBUG_CY_SCBIP_V1) */
    
    #elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       DEBUG_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       DEBUG_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DEBUG_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        DEBUG_SET_INP_DIS(DEBUG_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     DEBUG_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & DEBUG_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        DEBUG_SET_INCFG_TYPE(DEBUG_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        DEBUG_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (DEBUG_RX_WAKE_SCL_MOSI_PIN) */

    #if (DEBUG_TX_SDA_MISO_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_TX_SDA_MISO_HSIOM_REG,
                                       DEBUG_TX_SDA_MISO_HSIOM_MASK,
                                       DEBUG_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[DEBUG_TX_SDA_MISO_PIN_INDEX]);

        DEBUG_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[DEBUG_TX_SDA_MISO_PIN_INDEX]);

    #if (!DEBUG_CY_SCBIP_V1)
        DEBUG_SET_INP_DIS(DEBUG_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     DEBUG_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & DEBUG_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!DEBUG_CY_SCBIP_V1) */
    #endif /* (DEBUG_RX_SCL_MOSI_PIN) */

    #if (DEBUG_CTS_SCLK_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_CTS_SCLK_HSIOM_REG,
                                       DEBUG_CTS_SCLK_HSIOM_MASK,
                                       DEBUG_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[DEBUG_CTS_SCLK_PIN_INDEX]);

        DEBUG_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[DEBUG_CTS_SCLK_PIN_INDEX]);

        DEBUG_SET_INP_DIS(DEBUG_uart_cts_spi_sclk_INP_DIS,
                                     DEBUG_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & DEBUG_CTS_SCLK_PIN_MASK)));
    #endif /* (DEBUG_CTS_SCLK_PIN) */

    #if (DEBUG_RTS_SS0_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_RTS_SS0_HSIOM_REG,
                                       DEBUG_RTS_SS0_HSIOM_MASK,
                                       DEBUG_RTS_SS0_HSIOM_POS,
                                       hsiomSel[DEBUG_RTS_SS0_PIN_INDEX]);

        DEBUG_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[DEBUG_RTS_SS0_PIN_INDEX]);

        DEBUG_SET_INP_DIS(DEBUG_uart_rts_spi_ss0_INP_DIS,
                                     DEBUG_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & DEBUG_RTS_SS0_PIN_MASK)));
    #endif /* (DEBUG_RTS_SS0_PIN) */

    #if (DEBUG_SS1_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_SS1_HSIOM_REG,
                                       DEBUG_SS1_HSIOM_MASK,
                                       DEBUG_SS1_HSIOM_POS,
                                       hsiomSel[DEBUG_SS1_PIN_INDEX]);

        DEBUG_spi_ss1_SetDriveMode((uint8) pinsDm[DEBUG_SS1_PIN_INDEX]);

        DEBUG_SET_INP_DIS(DEBUG_spi_ss1_INP_DIS,
                                     DEBUG_spi_ss1_MASK,
                                     (0u != (pinsInBuf & DEBUG_SS1_PIN_MASK)));
    #endif /* (DEBUG_SS1_PIN) */

    #if (DEBUG_SS2_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_SS2_HSIOM_REG,
                                       DEBUG_SS2_HSIOM_MASK,
                                       DEBUG_SS2_HSIOM_POS,
                                       hsiomSel[DEBUG_SS2_PIN_INDEX]);

        DEBUG_spi_ss2_SetDriveMode((uint8) pinsDm[DEBUG_SS2_PIN_INDEX]);

        DEBUG_SET_INP_DIS(DEBUG_spi_ss2_INP_DIS,
                                     DEBUG_spi_ss2_MASK,
                                     (0u != (pinsInBuf & DEBUG_SS2_PIN_MASK)));
    #endif /* (DEBUG_SS2_PIN) */

    #if (DEBUG_SS3_PIN)
        DEBUG_SET_HSIOM_SEL(DEBUG_SS3_HSIOM_REG,
                                       DEBUG_SS3_HSIOM_MASK,
                                       DEBUG_SS3_HSIOM_POS,
                                       hsiomSel[DEBUG_SS3_PIN_INDEX]);

        DEBUG_spi_ss3_SetDriveMode((uint8) pinsDm[DEBUG_SS3_PIN_INDEX]);

        DEBUG_SET_INP_DIS(DEBUG_spi_ss3_INP_DIS,
                                     DEBUG_spi_ss3_MASK,
                                     (0u != (pinsInBuf & DEBUG_SS3_PIN_MASK)));
    #endif /* (DEBUG_SS3_PIN) */
    }

#endif /* (DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: DEBUG_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void DEBUG_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (DEBUG_CTRL_REG & DEBUG_CTRL_EC_AM_MODE)) &&
            (0u == (DEBUG_I2C_CTRL_REG & DEBUG_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            DEBUG_CTRL_REG &= ~DEBUG_CTRL_EC_AM_MODE;
            DEBUG_CTRL_REG |=  DEBUG_CTRL_EC_AM_MODE;
        }

        DEBUG_I2C_SLAVE_CMD_REG = DEBUG_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */


/* [] END OF FILE */
