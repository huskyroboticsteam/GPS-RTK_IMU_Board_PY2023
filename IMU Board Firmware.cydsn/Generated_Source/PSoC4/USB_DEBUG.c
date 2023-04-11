/***************************************************************************//**
* \file USB_DEBUG.c
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

#include "USB_DEBUG_PVT.h"

#if (USB_DEBUG_SCB_MODE_I2C_INC)
    #include "USB_DEBUG_I2C_PVT.h"
#endif /* (USB_DEBUG_SCB_MODE_I2C_INC) */

#if (USB_DEBUG_SCB_MODE_EZI2C_INC)
    #include "USB_DEBUG_EZI2C_PVT.h"
#endif /* (USB_DEBUG_SCB_MODE_EZI2C_INC) */

#if (USB_DEBUG_SCB_MODE_SPI_INC || USB_DEBUG_SCB_MODE_UART_INC)
    #include "USB_DEBUG_SPI_UART_PVT.h"
#endif /* (USB_DEBUG_SCB_MODE_SPI_INC || USB_DEBUG_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 USB_DEBUG_scbMode = USB_DEBUG_SCB_MODE_UNCONFIG;
    uint8 USB_DEBUG_scbEnableWake;
    uint8 USB_DEBUG_scbEnableIntr;

    /* I2C configuration variables */
    uint8 USB_DEBUG_mode;
    uint8 USB_DEBUG_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * USB_DEBUG_rxBuffer;
    uint8  USB_DEBUG_rxDataBits;
    uint32 USB_DEBUG_rxBufferSize;

    volatile uint8 * USB_DEBUG_txBuffer;
    uint8  USB_DEBUG_txDataBits;
    uint32 USB_DEBUG_txBufferSize;

    /* EZI2C configuration variables */
    uint8 USB_DEBUG_numberOfAddr;
    uint8 USB_DEBUG_subAddrSize;
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** USB_DEBUG_initVar indicates whether the USB_DEBUG 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the USB_DEBUG_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  USB_DEBUG_Init() function can be called before the 
*  USB_DEBUG_Start() or USB_DEBUG_Enable() function.
*/
uint8 USB_DEBUG_initVar = 0u;


#if (! (USB_DEBUG_SCB_MODE_I2C_CONST_CFG || \
        USB_DEBUG_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * USB_DEBUG_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent USB_DEBUG_Enable() call.
    */
    uint16 USB_DEBUG_IntrTxMask = 0u;
#endif /* (! (USB_DEBUG_SCB_MODE_I2C_CONST_CFG || \
              USB_DEBUG_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (USB_DEBUG_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_USB_DEBUG_CUSTOM_INTR_HANDLER)
    void (*USB_DEBUG_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_USB_DEBUG_CUSTOM_INTR_HANDLER) */
#endif /* (USB_DEBUG_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void USB_DEBUG_ScbEnableIntr(void);
static void USB_DEBUG_ScbModeStop(void);
static void USB_DEBUG_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: USB_DEBUG_Init
****************************************************************************//**
*
*  Initializes the USB_DEBUG component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  USB_DEBUG_I2CInit, USB_DEBUG_SpiInit, 
*  USB_DEBUG_UartInit or USB_DEBUG_EzI2CInit.
*
*******************************************************************************/
void USB_DEBUG_Init(void)
{
#if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    if (USB_DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        USB_DEBUG_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (USB_DEBUG_SCB_MODE_I2C_CONST_CFG)
    USB_DEBUG_I2CInit();

#elif (USB_DEBUG_SCB_MODE_SPI_CONST_CFG)
    USB_DEBUG_SpiInit();

#elif (USB_DEBUG_SCB_MODE_UART_CONST_CFG)
    USB_DEBUG_UartInit();

#elif (USB_DEBUG_SCB_MODE_EZI2C_CONST_CFG)
    USB_DEBUG_EzI2CInit();

#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: USB_DEBUG_Enable
****************************************************************************//**
*
*  Enables USB_DEBUG component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  USB_DEBUG_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The USB_DEBUG configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured USB_DEBUG”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void USB_DEBUG_Enable(void)
{
#if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!USB_DEBUG_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        USB_DEBUG_CTRL_REG |= USB_DEBUG_CTRL_ENABLED;

        USB_DEBUG_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        USB_DEBUG_ScbModePostEnable();
    }
#else
    USB_DEBUG_CTRL_REG |= USB_DEBUG_CTRL_ENABLED;

    USB_DEBUG_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    USB_DEBUG_ScbModePostEnable();
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: USB_DEBUG_Start
****************************************************************************//**
*
*  Invokes USB_DEBUG_Init() and USB_DEBUG_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  USB_DEBUG_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void USB_DEBUG_Start(void)
{
    if (0u == USB_DEBUG_initVar)
    {
        USB_DEBUG_Init();
        USB_DEBUG_initVar = 1u; /* Component was initialized */
    }

    USB_DEBUG_Enable();
}


/*******************************************************************************
* Function Name: USB_DEBUG_Stop
****************************************************************************//**
*
*  Disables the USB_DEBUG component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function USB_DEBUG_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void USB_DEBUG_Stop(void)
{
#if (USB_DEBUG_SCB_IRQ_INTERNAL)
    USB_DEBUG_DisableInt();
#endif /* (USB_DEBUG_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    USB_DEBUG_ScbModeStop();

    /* Disable SCB IP */
    USB_DEBUG_CTRL_REG &= (uint32) ~USB_DEBUG_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    USB_DEBUG_SetTxInterruptMode(USB_DEBUG_NO_INTR_SOURCES);

#if (USB_DEBUG_SCB_IRQ_INTERNAL)
    USB_DEBUG_ClearPendingInt();
#endif /* (USB_DEBUG_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: USB_DEBUG_SetRxFifoLevel
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
void USB_DEBUG_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = USB_DEBUG_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~USB_DEBUG_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (USB_DEBUG_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    USB_DEBUG_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: USB_DEBUG_SetTxFifoLevel
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
void USB_DEBUG_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = USB_DEBUG_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~USB_DEBUG_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (USB_DEBUG_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    USB_DEBUG_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (USB_DEBUG_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: USB_DEBUG_SetCustomInterruptHandler
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
    void USB_DEBUG_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_USB_DEBUG_CUSTOM_INTR_HANDLER)
        USB_DEBUG_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_USB_DEBUG_CUSTOM_INTR_HANDLER) */
    }
#endif /* (USB_DEBUG_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: USB_DEBUG_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void USB_DEBUG_ScbEnableIntr(void)
{
#if (USB_DEBUG_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != USB_DEBUG_scbEnableIntr)
        {
            USB_DEBUG_EnableInt();
        }

    #else
        USB_DEBUG_EnableInt();

    #endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (USB_DEBUG_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: USB_DEBUG_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void USB_DEBUG_ScbModePostEnable(void)
{
#if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!USB_DEBUG_CY_SCBIP_V1)
    if (USB_DEBUG_SCB_MODE_SPI_RUNTM_CFG)
    {
        USB_DEBUG_SpiPostEnable();
    }
    else if (USB_DEBUG_SCB_MODE_UART_RUNTM_CFG)
    {
        USB_DEBUG_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!USB_DEBUG_CY_SCBIP_V1) */

#elif (USB_DEBUG_SCB_MODE_SPI_CONST_CFG)
    USB_DEBUG_SpiPostEnable();

#elif (USB_DEBUG_SCB_MODE_UART_CONST_CFG)
    USB_DEBUG_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: USB_DEBUG_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void USB_DEBUG_ScbModeStop(void)
{
#if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    if (USB_DEBUG_SCB_MODE_I2C_RUNTM_CFG)
    {
        USB_DEBUG_I2CStop();
    }
    else if (USB_DEBUG_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        USB_DEBUG_EzI2CStop();
    }
#if (!USB_DEBUG_CY_SCBIP_V1)
    else if (USB_DEBUG_SCB_MODE_SPI_RUNTM_CFG)
    {
        USB_DEBUG_SpiStop();
    }
    else if (USB_DEBUG_SCB_MODE_UART_RUNTM_CFG)
    {
        USB_DEBUG_UartStop();
    }
#endif /* (!USB_DEBUG_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (USB_DEBUG_SCB_MODE_I2C_CONST_CFG)
    USB_DEBUG_I2CStop();

#elif (USB_DEBUG_SCB_MODE_EZI2C_CONST_CFG)
    USB_DEBUG_EzI2CStop();

#elif (USB_DEBUG_SCB_MODE_SPI_CONST_CFG)
    USB_DEBUG_SpiStop();

#elif (USB_DEBUG_SCB_MODE_UART_CONST_CFG)
    USB_DEBUG_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: USB_DEBUG_SetPins
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
    void USB_DEBUG_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[USB_DEBUG_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!USB_DEBUG_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!USB_DEBUG_CY_SCBIP_V1) */
        
        uint32 hsiomSel[USB_DEBUG_SCB_PINS_NUMBER] = 
        {
            USB_DEBUG_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            USB_DEBUG_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (USB_DEBUG_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (USB_DEBUG_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < USB_DEBUG_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = USB_DEBUG_PIN_DM_ALG_HIZ;
        }

        if ((USB_DEBUG_SCB_MODE_I2C   == mode) ||
            (USB_DEBUG_SCB_MODE_EZI2C == mode))
        {
        #if (USB_DEBUG_RX_SCL_MOSI_PIN)
            hsiomSel[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_PIN_DM_OD_LO;
        #elif (USB_DEBUG_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = USB_DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = USB_DEBUG_PIN_DM_OD_LO;
        #else
        #endif /* (USB_DEBUG_RX_SCL_MOSI_PIN) */
        
        #if (USB_DEBUG_TX_SDA_MISO_PIN)
            hsiomSel[USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_PIN_DM_OD_LO;
        #endif /* (USB_DEBUG_TX_SDA_MISO_PIN) */
        }
    #if (!USB_DEBUG_CY_SCBIP_V1)
        else if (USB_DEBUG_SCB_MODE_SPI == mode)
        {
        #if (USB_DEBUG_RX_SCL_MOSI_PIN)
            hsiomSel[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (USB_DEBUG_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = USB_DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (USB_DEBUG_RX_SCL_MOSI_PIN) */
        
        #if (USB_DEBUG_TX_SDA_MISO_PIN)
            hsiomSel[USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (USB_DEBUG_TX_SDA_MISO_PIN) */
        
        #if (USB_DEBUG_CTS_SCLK_PIN)
            hsiomSel[USB_DEBUG_CTS_SCLK_PIN_INDEX] = USB_DEBUG_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (USB_DEBUG_CTS_SCLK_PIN) */

            if (USB_DEBUG_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;
                pinsDm[USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                pinsDm[USB_DEBUG_CTS_SCLK_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;

            #if (USB_DEBUG_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[USB_DEBUG_RTS_SS0_PIN_INDEX] = USB_DEBUG_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [USB_DEBUG_RTS_SS0_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;
            #endif /* (USB_DEBUG_RTS_SS0_PIN) */

            #if (USB_DEBUG_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= USB_DEBUG_TX_SDA_MISO_PIN_MASK;
            #endif /* (USB_DEBUG_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                pinsDm[USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;
                pinsDm[USB_DEBUG_CTS_SCLK_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;

            #if (USB_DEBUG_RTS_SS0_PIN)
                hsiomSel [USB_DEBUG_RTS_SS0_PIN_INDEX] = USB_DEBUG_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [USB_DEBUG_RTS_SS0_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                pinsInBuf |= USB_DEBUG_RTS_SS0_PIN_MASK;
            #endif /* (USB_DEBUG_RTS_SS0_PIN) */

            #if (USB_DEBUG_SS1_PIN)
                hsiomSel [USB_DEBUG_SS1_PIN_INDEX] = USB_DEBUG_SS1_HSIOM_SEL_SPI;
                pinsDm   [USB_DEBUG_SS1_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                pinsInBuf |= USB_DEBUG_SS1_PIN_MASK;
            #endif /* (USB_DEBUG_SS1_PIN) */

            #if (USB_DEBUG_SS2_PIN)
                hsiomSel [USB_DEBUG_SS2_PIN_INDEX] = USB_DEBUG_SS2_HSIOM_SEL_SPI;
                pinsDm   [USB_DEBUG_SS2_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                pinsInBuf |= USB_DEBUG_SS2_PIN_MASK;
            #endif /* (USB_DEBUG_SS2_PIN) */

            #if (USB_DEBUG_SS3_PIN)
                hsiomSel [USB_DEBUG_SS3_PIN_INDEX] = USB_DEBUG_SS3_HSIOM_SEL_SPI;
                pinsDm   [USB_DEBUG_SS3_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                pinsInBuf |= USB_DEBUG_SS3_PIN_MASK;
            #endif /* (USB_DEBUG_SS3_PIN) */

                /* Disable input buffers */
            #if (USB_DEBUG_RX_SCL_MOSI_PIN)
                pinsInBuf |= USB_DEBUG_RX_SCL_MOSI_PIN_MASK;
            #elif (USB_DEBUG_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (USB_DEBUG_RX_SCL_MOSI_PIN) */

            #if (USB_DEBUG_CTS_SCLK_PIN)
                pinsInBuf |= USB_DEBUG_CTS_SCLK_PIN_MASK;
            #endif /* (USB_DEBUG_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (USB_DEBUG_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (USB_DEBUG_TX_SDA_MISO_PIN)
                hsiomSel[USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_PIN_DM_OD_LO;
            #endif /* (USB_DEBUG_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (USB_DEBUG_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (USB_DEBUG_RX_SCL_MOSI_PIN)
                    hsiomSel[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [USB_DEBUG_RX_SCL_MOSI_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;
                #elif (USB_DEBUG_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = USB_DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;
                #else
                #endif /* (USB_DEBUG_RX_SCL_MOSI_PIN) */
                }

                if (0u != (USB_DEBUG_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (USB_DEBUG_TX_SDA_MISO_PIN)
                    hsiomSel[USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [USB_DEBUG_TX_SDA_MISO_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= USB_DEBUG_TX_SDA_MISO_PIN_MASK;
                #endif /* (USB_DEBUG_TX_SDA_MISO_PIN) */
                }

            #if !(USB_DEBUG_CY_SCBIP_V0 || USB_DEBUG_CY_SCBIP_V1)
                if (USB_DEBUG_UART_MODE_STD == subMode)
                {
                    if (0u != (USB_DEBUG_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (USB_DEBUG_CTS_SCLK_PIN)
                        hsiomSel[USB_DEBUG_CTS_SCLK_PIN_INDEX] = USB_DEBUG_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [USB_DEBUG_CTS_SCLK_PIN_INDEX] = USB_DEBUG_PIN_DM_DIG_HIZ;
                    #endif /* (USB_DEBUG_CTS_SCLK_PIN) */
                    }

                    if (0u != (USB_DEBUG_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (USB_DEBUG_RTS_SS0_PIN)
                        hsiomSel[USB_DEBUG_RTS_SS0_PIN_INDEX] = USB_DEBUG_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [USB_DEBUG_RTS_SS0_PIN_INDEX] = USB_DEBUG_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= USB_DEBUG_RTS_SS0_PIN_MASK;
                    #endif /* (USB_DEBUG_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(USB_DEBUG_CY_SCBIP_V0 || USB_DEBUG_CY_SCBIP_V1) */
            }
        }
    #endif /* (!USB_DEBUG_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (USB_DEBUG_RX_SCL_MOSI_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_RX_SCL_MOSI_HSIOM_REG,
                                       USB_DEBUG_RX_SCL_MOSI_HSIOM_MASK,
                                       USB_DEBUG_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX]);

        USB_DEBUG_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[USB_DEBUG_RX_SCL_MOSI_PIN_INDEX]);

        #if (!USB_DEBUG_CY_SCBIP_V1)
            USB_DEBUG_SET_INP_DIS(USB_DEBUG_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         USB_DEBUG_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & USB_DEBUG_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!USB_DEBUG_CY_SCBIP_V1) */
    
    #elif (USB_DEBUG_RX_WAKE_SCL_MOSI_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       USB_DEBUG_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       USB_DEBUG_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        USB_DEBUG_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        USB_DEBUG_SET_INP_DIS(USB_DEBUG_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     USB_DEBUG_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & USB_DEBUG_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        USB_DEBUG_SET_INCFG_TYPE(USB_DEBUG_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        USB_DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        USB_DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        USB_DEBUG_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (USB_DEBUG_RX_WAKE_SCL_MOSI_PIN) */

    #if (USB_DEBUG_TX_SDA_MISO_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_TX_SDA_MISO_HSIOM_REG,
                                       USB_DEBUG_TX_SDA_MISO_HSIOM_MASK,
                                       USB_DEBUG_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[USB_DEBUG_TX_SDA_MISO_PIN_INDEX]);

        USB_DEBUG_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[USB_DEBUG_TX_SDA_MISO_PIN_INDEX]);

    #if (!USB_DEBUG_CY_SCBIP_V1)
        USB_DEBUG_SET_INP_DIS(USB_DEBUG_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     USB_DEBUG_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & USB_DEBUG_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!USB_DEBUG_CY_SCBIP_V1) */
    #endif /* (USB_DEBUG_RX_SCL_MOSI_PIN) */

    #if (USB_DEBUG_CTS_SCLK_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_CTS_SCLK_HSIOM_REG,
                                       USB_DEBUG_CTS_SCLK_HSIOM_MASK,
                                       USB_DEBUG_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[USB_DEBUG_CTS_SCLK_PIN_INDEX]);

        USB_DEBUG_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[USB_DEBUG_CTS_SCLK_PIN_INDEX]);

        USB_DEBUG_SET_INP_DIS(USB_DEBUG_uart_cts_spi_sclk_INP_DIS,
                                     USB_DEBUG_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & USB_DEBUG_CTS_SCLK_PIN_MASK)));
    #endif /* (USB_DEBUG_CTS_SCLK_PIN) */

    #if (USB_DEBUG_RTS_SS0_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_RTS_SS0_HSIOM_REG,
                                       USB_DEBUG_RTS_SS0_HSIOM_MASK,
                                       USB_DEBUG_RTS_SS0_HSIOM_POS,
                                       hsiomSel[USB_DEBUG_RTS_SS0_PIN_INDEX]);

        USB_DEBUG_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[USB_DEBUG_RTS_SS0_PIN_INDEX]);

        USB_DEBUG_SET_INP_DIS(USB_DEBUG_uart_rts_spi_ss0_INP_DIS,
                                     USB_DEBUG_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & USB_DEBUG_RTS_SS0_PIN_MASK)));
    #endif /* (USB_DEBUG_RTS_SS0_PIN) */

    #if (USB_DEBUG_SS1_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_SS1_HSIOM_REG,
                                       USB_DEBUG_SS1_HSIOM_MASK,
                                       USB_DEBUG_SS1_HSIOM_POS,
                                       hsiomSel[USB_DEBUG_SS1_PIN_INDEX]);

        USB_DEBUG_spi_ss1_SetDriveMode((uint8) pinsDm[USB_DEBUG_SS1_PIN_INDEX]);

        USB_DEBUG_SET_INP_DIS(USB_DEBUG_spi_ss1_INP_DIS,
                                     USB_DEBUG_spi_ss1_MASK,
                                     (0u != (pinsInBuf & USB_DEBUG_SS1_PIN_MASK)));
    #endif /* (USB_DEBUG_SS1_PIN) */

    #if (USB_DEBUG_SS2_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_SS2_HSIOM_REG,
                                       USB_DEBUG_SS2_HSIOM_MASK,
                                       USB_DEBUG_SS2_HSIOM_POS,
                                       hsiomSel[USB_DEBUG_SS2_PIN_INDEX]);

        USB_DEBUG_spi_ss2_SetDriveMode((uint8) pinsDm[USB_DEBUG_SS2_PIN_INDEX]);

        USB_DEBUG_SET_INP_DIS(USB_DEBUG_spi_ss2_INP_DIS,
                                     USB_DEBUG_spi_ss2_MASK,
                                     (0u != (pinsInBuf & USB_DEBUG_SS2_PIN_MASK)));
    #endif /* (USB_DEBUG_SS2_PIN) */

    #if (USB_DEBUG_SS3_PIN)
        USB_DEBUG_SET_HSIOM_SEL(USB_DEBUG_SS3_HSIOM_REG,
                                       USB_DEBUG_SS3_HSIOM_MASK,
                                       USB_DEBUG_SS3_HSIOM_POS,
                                       hsiomSel[USB_DEBUG_SS3_PIN_INDEX]);

        USB_DEBUG_spi_ss3_SetDriveMode((uint8) pinsDm[USB_DEBUG_SS3_PIN_INDEX]);

        USB_DEBUG_SET_INP_DIS(USB_DEBUG_spi_ss3_INP_DIS,
                                     USB_DEBUG_spi_ss3_MASK,
                                     (0u != (pinsInBuf & USB_DEBUG_SS3_PIN_MASK)));
    #endif /* (USB_DEBUG_SS3_PIN) */
    }

#endif /* (USB_DEBUG_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (USB_DEBUG_CY_SCBIP_V0 || USB_DEBUG_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: USB_DEBUG_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void USB_DEBUG_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (USB_DEBUG_CTRL_REG & USB_DEBUG_CTRL_EC_AM_MODE)) &&
            (0u == (USB_DEBUG_I2C_CTRL_REG & USB_DEBUG_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            USB_DEBUG_CTRL_REG &= ~USB_DEBUG_CTRL_EC_AM_MODE;
            USB_DEBUG_CTRL_REG |=  USB_DEBUG_CTRL_EC_AM_MODE;
        }

        USB_DEBUG_I2C_SLAVE_CMD_REG = USB_DEBUG_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (USB_DEBUG_CY_SCBIP_V0 || USB_DEBUG_CY_SCBIP_V1) */


/* [] END OF FILE */
