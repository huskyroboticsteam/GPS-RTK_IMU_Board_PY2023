/***************************************************************************//**
* \file USB_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
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

#include "USB_PVT.h"
#include "USB_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (USB_UART_WAKE_ENABLE_CONST && USB_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when USB_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 USB_skipStart = 1u;
    /** \} globals */
#endif /* (USB_UART_WAKE_ENABLE_CONST && USB_UART_RX_WAKEUP_IRQ) */

#if(USB_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const USB_UART_INIT_STRUCT USB_configUart =
    {
        USB_UART_SUB_MODE,
        USB_UART_DIRECTION,
        USB_UART_DATA_BITS_NUM,
        USB_UART_PARITY_TYPE,
        USB_UART_STOP_BITS_NUM,
        USB_UART_OVS_FACTOR,
        USB_UART_IRDA_LOW_POWER,
        USB_UART_MEDIAN_FILTER_ENABLE,
        USB_UART_RETRY_ON_NACK,
        USB_UART_IRDA_POLARITY,
        USB_UART_DROP_ON_PARITY_ERR,
        USB_UART_DROP_ON_FRAME_ERR,
        USB_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        USB_UART_MP_MODE_ENABLE,
        USB_UART_MP_ACCEPT_ADDRESS,
        USB_UART_MP_RX_ADDRESS,
        USB_UART_MP_RX_ADDRESS_MASK,
        (uint32) USB_SCB_IRQ_INTERNAL,
        USB_UART_INTR_RX_MASK,
        USB_UART_RX_TRIGGER_LEVEL,
        USB_UART_INTR_TX_MASK,
        USB_UART_TX_TRIGGER_LEVEL,
        (uint8) USB_UART_BYTE_MODE_ENABLE,
        (uint8) USB_UART_CTS_ENABLE,
        (uint8) USB_UART_CTS_POLARITY,
        (uint8) USB_UART_RTS_POLARITY,
        (uint8) USB_UART_RTS_FIFO_LEVEL,
        (uint8) USB_UART_RX_BREAK_WIDTH
    };


    /*******************************************************************************
    * Function Name: USB_UartInit
    ****************************************************************************//**
    *
    *  Configures the USB for UART operation.
    *
    *  This function is intended specifically to be used when the USB
    *  configuration is set to “Unconfigured USB” in the customizer.
    *  After initializing the USB in UART mode using this function,
    *  the component can be enabled using the USB_Start() or
    * USB_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void USB_UartInit(const USB_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (USB_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (USB_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */

            /* Configure pins */
            USB_SetPins(USB_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            USB_scbMode       = (uint8) USB_SCB_MODE_UART;
            USB_scbEnableWake = (uint8) config->enableWake;
            USB_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            USB_rxBuffer      =         config->rxBuffer;
            USB_rxDataBits    = (uint8) config->dataBits;
            USB_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            USB_txBuffer      =         config->txBuffer;
            USB_txDataBits    = (uint8) config->dataBits;
            USB_txBufferSize  =         config->txBufferSize;

            /* Configure UART interface */
            if(USB_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                USB_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (USB_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (USB_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                USB_CTRL_REG  = USB_GET_CTRL_OVS(config->oversample);
            }

            USB_CTRL_REG     |= USB_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             USB_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             USB_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            USB_UART_CTRL_REG = USB_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            USB_UART_RX_CTRL_REG = USB_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        USB_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        USB_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        USB_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        USB_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr)   |
                                        USB_GET_UART_RX_CTRL_BREAK_WIDTH(config->breakWidth);

            if(USB_UART_PARITY_NONE != config->parity)
            {
               USB_UART_RX_CTRL_REG |= USB_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    USB_UART_RX_CTRL_PARITY_ENABLED;
            }

            USB_RX_CTRL_REG      = USB_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                USB_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                USB_GET_UART_RX_CTRL_ENABLED(config->direction);

            USB_RX_FIFO_CTRL_REG = USB_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            USB_RX_MATCH_REG     = USB_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                USB_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            USB_UART_TX_CTRL_REG = USB_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                USB_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(USB_UART_PARITY_NONE != config->parity)
            {
               USB_UART_TX_CTRL_REG |= USB_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    USB_UART_TX_CTRL_PARITY_ENABLED;
            }

            USB_TX_CTRL_REG      = USB_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                USB_GET_UART_TX_CTRL_ENABLED(config->direction);

            USB_TX_FIFO_CTRL_REG = USB_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
            USB_UART_FLOW_CTRL_REG = USB_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            USB_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            USB_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            USB_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (USB_ISR_NUMBER);
            CyIntSetPriority(USB_ISR_NUMBER, USB_ISR_PRIORITY);
            (void) CyIntSetVector(USB_ISR_NUMBER, &USB_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(USB_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (USB_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(USB_RX_WAKE_ISR_NUMBER, USB_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(USB_RX_WAKE_ISR_NUMBER, &USB_UART_WAKEUP_ISR);
        #endif /* (USB_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            USB_INTR_I2C_EC_MASK_REG = USB_NO_INTR_SOURCES;
            USB_INTR_SPI_EC_MASK_REG = USB_NO_INTR_SOURCES;
            USB_INTR_SLAVE_MASK_REG  = USB_NO_INTR_SOURCES;
            USB_INTR_MASTER_MASK_REG = USB_NO_INTR_SOURCES;
            USB_INTR_RX_MASK_REG     = config->rxInterruptMask;
            USB_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Configure TX interrupt sources to restore. */
            USB_IntrTxMask = LO16(USB_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            USB_rxBufferHead     = 0u;
            USB_rxBufferTail     = 0u;
            USB_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            USB_txBufferHead = 0u;
            USB_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: USB_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void USB_UartInit(void)
    {
        /* Configure UART interface */
        USB_CTRL_REG = USB_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        USB_UART_CTRL_REG = USB_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        USB_UART_RX_CTRL_REG = USB_UART_DEFAULT_UART_RX_CTRL;
        USB_RX_CTRL_REG      = USB_UART_DEFAULT_RX_CTRL;
        USB_RX_FIFO_CTRL_REG = USB_UART_DEFAULT_RX_FIFO_CTRL;
        USB_RX_MATCH_REG     = USB_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        USB_UART_TX_CTRL_REG = USB_UART_DEFAULT_UART_TX_CTRL;
        USB_TX_CTRL_REG      = USB_UART_DEFAULT_TX_CTRL;
        USB_TX_FIFO_CTRL_REG = USB_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
        USB_UART_FLOW_CTRL_REG = USB_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(USB_SCB_IRQ_INTERNAL)
        CyIntDisable    (USB_ISR_NUMBER);
        CyIntSetPriority(USB_ISR_NUMBER, USB_ISR_PRIORITY);
        (void) CyIntSetVector(USB_ISR_NUMBER, &USB_SPI_UART_ISR);
    #endif /* (USB_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(USB_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (USB_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(USB_RX_WAKE_ISR_NUMBER, USB_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(USB_RX_WAKE_ISR_NUMBER, &USB_UART_WAKEUP_ISR);
    #endif /* (USB_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        USB_INTR_I2C_EC_MASK_REG = USB_UART_DEFAULT_INTR_I2C_EC_MASK;
        USB_INTR_SPI_EC_MASK_REG = USB_UART_DEFAULT_INTR_SPI_EC_MASK;
        USB_INTR_SLAVE_MASK_REG  = USB_UART_DEFAULT_INTR_SLAVE_MASK;
        USB_INTR_MASTER_MASK_REG = USB_UART_DEFAULT_INTR_MASTER_MASK;
        USB_INTR_RX_MASK_REG     = USB_UART_DEFAULT_INTR_RX_MASK;
        USB_INTR_TX_MASK_REG     = USB_UART_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        USB_IntrTxMask = LO16(USB_INTR_TX_MASK_REG);

    #if(USB_INTERNAL_RX_SW_BUFFER_CONST)
        USB_rxBufferHead     = 0u;
        USB_rxBufferTail     = 0u;
        USB_rxBufferOverflow = 0u;
    #endif /* (USB_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(USB_INTERNAL_TX_SW_BUFFER_CONST)
        USB_txBufferHead = 0u;
        USB_txBufferTail = 0u;
    #endif /* (USB_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (USB_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: USB_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void USB_UartPostEnable(void)
{
#if (USB_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (USB_TX_SDA_MISO_PIN)
        if (USB_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            USB_SET_HSIOM_SEL(USB_TX_SDA_MISO_HSIOM_REG, USB_TX_SDA_MISO_HSIOM_MASK,
                                           USB_TX_SDA_MISO_HSIOM_POS, USB_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (USB_TX_SDA_MISO_PIN_PIN) */

    #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
        #if (USB_RTS_SS0_PIN)
            if (USB_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                USB_SET_HSIOM_SEL(USB_RTS_SS0_HSIOM_REG, USB_RTS_SS0_HSIOM_MASK,
                                               USB_RTS_SS0_HSIOM_POS, USB_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (USB_RTS_SS0_PIN) */
    #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */

#else
    #if (USB_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        USB_SET_HSIOM_SEL(USB_TX_HSIOM_REG, USB_TX_HSIOM_MASK,
                                       USB_TX_HSIOM_POS, USB_TX_HSIOM_SEL_UART);
    #endif /* (USB_UART_TX_PIN) */

    #if (USB_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        USB_SET_HSIOM_SEL(USB_RTS_HSIOM_REG, USB_RTS_HSIOM_MASK,
                                       USB_RTS_HSIOM_POS, USB_RTS_HSIOM_SEL_UART);
    #endif /* (USB_UART_RTS_PIN) */
#endif /* (USB_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    USB_SetTxInterruptMode(USB_IntrTxMask);
}


/*******************************************************************************
* Function Name: USB_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void USB_UartStop(void)
{
#if(USB_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (USB_TX_SDA_MISO_PIN)
        if (USB_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            USB_SET_HSIOM_SEL(USB_TX_SDA_MISO_HSIOM_REG, USB_TX_SDA_MISO_HSIOM_MASK,
                                           USB_TX_SDA_MISO_HSIOM_POS, USB_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (USB_TX_SDA_MISO_PIN_PIN) */

    #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
        #if (USB_RTS_SS0_PIN)
            if (USB_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                USB_uart_rts_spi_ss0_Write(USB_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                USB_SET_HSIOM_SEL(USB_RTS_SS0_HSIOM_REG, USB_RTS_SS0_HSIOM_MASK,
                                               USB_RTS_SS0_HSIOM_POS, USB_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (USB_RTS_SS0_PIN) */
    #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */

#else
    #if (USB_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        USB_SET_HSIOM_SEL(USB_TX_HSIOM_REG, USB_TX_HSIOM_MASK,
                                       USB_TX_HSIOM_POS, USB_TX_HSIOM_SEL_GPIO);
    #endif /* (USB_UART_TX_PIN) */

    #if (USB_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        USB_rts_Write(USB_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        USB_SET_HSIOM_SEL(USB_RTS_HSIOM_REG, USB_RTS_HSIOM_MASK,
                                       USB_RTS_HSIOM_POS, USB_RTS_HSIOM_SEL_GPIO);
    #endif /* (USB_UART_RTS_PIN) */

#endif /* (USB_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (USB_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    USB_UART_RX_CTRL_REG &= (uint32) ~USB_UART_RX_CTRL_SKIP_START;
#endif /* (USB_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    USB_IntrTxMask = LO16(USB_GetTxInterruptMode() & USB_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: USB_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void USB_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = USB_RX_MATCH_REG;

    matchReg &= ((uint32) ~USB_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & USB_RX_MATCH_ADDR_MASK)); /* Set address  */

    USB_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: USB_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void USB_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = USB_RX_MATCH_REG;

    matchReg &= ((uint32) ~USB_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << USB_RX_MATCH_MASK_POS));

    USB_RX_MATCH_REG = matchReg;
}


#if(USB_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: USB_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check USB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 USB_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != USB_SpiUartGetRxBufferSize())
        {
            rxData = USB_SpiUartReadRxData();
        }

        if (USB_CHECK_INTR_RX(USB_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            USB_ClearRxInterruptSource(USB_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: USB_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - USB_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - USB_UART_RX_UNDERFLOW    Attempt to read from an empty
    *     receiver FIFO.
    *   - USB_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - USB_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check USB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 USB_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (USB_CHECK_RX_SW_BUFFER)
        {
            USB_DisableInt();
        }
        #endif

        if (0u != USB_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (USB_CHECK_RX_SW_BUFFER)
            {
                USB_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = USB_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = USB_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (USB_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                USB_ClearRxInterruptSource(USB_INTR_RX_NOT_EMPTY);

                USB_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (USB_GetRxInterruptSource() & USB_INTR_RX_ERR);
        USB_ClearRxInterruptSource(USB_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: USB_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - USB_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - USB_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void USB_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                USB_UART_FLOW_CTRL_REG |= (uint32)  USB_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                USB_UART_FLOW_CTRL_REG &= (uint32) ~USB_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: USB_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void USB_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = USB_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~USB_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (USB_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            USB_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */

#endif /* (USB_UART_RX_DIRECTION) */


#if(USB_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: USB_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void USB_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            USB_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: USB_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void USB_UartPutCRLF(uint32 txDataByte)
    {
        USB_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        USB_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        USB_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: USBSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void USB_UartEnableCts(void)
        {
            USB_UART_FLOW_CTRL_REG |= (uint32)  USB_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: USB_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void USB_UartDisableCts(void)
        {
            USB_UART_FLOW_CTRL_REG &= (uint32) ~USB_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: USB_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        * \param
        * polarity: Active polarity of CTS output signal.
        *   - USB_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - USB_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void USB_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                USB_UART_FLOW_CTRL_REG |= (uint32)  USB_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                USB_UART_FLOW_CTRL_REG &= (uint32) ~USB_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(USB_CY_SCBIP_V0 || USB_CY_SCBIP_V1) */


    /*******************************************************************************
    * Function Name: USB_UartSendBreakBlocking
    ****************************************************************************//**
    *
    * Sends a break condition (logic low) of specified width on UART TX line.
    * Blocks until break is completed. Only call this function when UART TX FIFO
    * and shifter are empty.
    *
    * \param breakWidth
    * Width of break condition. Valid range is 4 to 16 bits.
    *
    * \note
    * Before sending break all UART TX interrupt sources are disabled. The state
    * of UART TX interrupt sources is restored before function returns.
    *
    * \sideeffect
    * If this function is called while there is data in the TX FIFO or shifter that
    * data will be shifted out in packets the size of breakWidth.
    *
    *******************************************************************************/
    void USB_UartSendBreakBlocking(uint32 breakWidth)
    {
        uint32 txCtrlReg;
        uint32 txIntrReg;

        /* Disable all UART TX interrupt source and clear UART TX Done history */
        txIntrReg = USB_GetTxInterruptMode();
        USB_SetTxInterruptMode(0u);
        USB_ClearTxInterruptSource(USB_INTR_TX_UART_DONE);

        /* Store TX CTRL configuration */
        txCtrlReg = USB_TX_CTRL_REG;

        /* Set break width */
        USB_TX_CTRL_REG = (USB_TX_CTRL_REG & (uint32) ~USB_TX_CTRL_DATA_WIDTH_MASK) |
                                        USB_GET_TX_CTRL_DATA_WIDTH(breakWidth);

        /* Generate break */
        USB_TX_FIFO_WR_REG = 0u;

        /* Wait for break completion */
        while (0u == (USB_GetTxInterruptSource() & USB_INTR_TX_UART_DONE))
        {
        }

        /* Clear all UART TX interrupt sources to  */
        USB_ClearTxInterruptSource(USB_INTR_TX_ALL);

        /* Restore TX interrupt sources and data width */
        USB_TX_CTRL_REG = txCtrlReg;
        USB_SetTxInterruptMode(txIntrReg);
    }
#endif /* (USB_UART_TX_DIRECTION) */


#if (USB_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: USB_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be
    *  cleared by this API.
    *
    *******************************************************************************/
    void USB_UartSaveConfig(void)
    {
    #if (USB_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != USB_skipStart)
        {
            USB_UART_RX_CTRL_REG |= (uint32)  USB_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            USB_UART_RX_CTRL_REG &= (uint32) ~USB_UART_RX_CTRL_SKIP_START;
        }

        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        USB_CLEAR_UART_RX_WAKE_INTR;
        USB_RxWakeClearPendingInt();
        USB_RxWakeEnableInt();
    #endif /* (USB_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: USB_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void USB_UartRestoreConfig(void)
    {
    #if (USB_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        USB_RxWakeDisableInt();
    #endif /* (USB_UART_RX_WAKEUP_IRQ) */
    }


    #if (USB_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: USB_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(USB_UART_WAKEUP_ISR)
        {
        #ifdef USB_UART_WAKEUP_ISR_ENTRY_CALLBACK
            USB_UART_WAKEUP_ISR_EntryCallback();
        #endif /* USB_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            USB_CLEAR_UART_RX_WAKE_INTR;

        #ifdef USB_UART_WAKEUP_ISR_EXIT_CALLBACK
            USB_UART_WAKEUP_ISR_ExitCallback();
        #endif /* USB_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (USB_UART_RX_WAKEUP_IRQ) */
#endif /* (USB_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
