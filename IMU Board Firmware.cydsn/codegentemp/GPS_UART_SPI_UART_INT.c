/***************************************************************************//**
* \file GPS_UART_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "GPS_UART_PVT.h"
#include "GPS_UART_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (GPS_UART_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: GPS_UART_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(GPS_UART_SPI_UART_ISR)
{
#if (GPS_UART_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (GPS_UART_INTERNAL_RX_SW_BUFFER_CONST) */

#if (GPS_UART_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (GPS_UART_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef GPS_UART_SPI_UART_ISR_ENTRY_CALLBACK
    GPS_UART_SPI_UART_ISR_EntryCallback();
#endif /* GPS_UART_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != GPS_UART_customIntrHandler)
    {
        GPS_UART_customIntrHandler();
    }

    #if(GPS_UART_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        GPS_UART_ClearSpiExtClkInterruptSource(GPS_UART_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (GPS_UART_CHECK_RX_SW_BUFFER)
    {
        if (GPS_UART_CHECK_INTR_RX_MASKED(GPS_UART_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (GPS_UART_rxBufferHead + 1u);

                /* Adjust local head index */
                if (GPS_UART_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == GPS_UART_rxBufferTail)
                {
                    #if (GPS_UART_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        GPS_UART_INTR_RX_MASK_REG &= ~GPS_UART_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) GPS_UART_RX_FIFO_RD_REG;
                        GPS_UART_rxBufferOverflow = (uint8) GPS_UART_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    GPS_UART_PutWordInRxBuffer(locHead, GPS_UART_RX_FIFO_RD_REG);

                    /* Move head index */
                    GPS_UART_rxBufferHead = locHead;
                }
            }
            while(0u != GPS_UART_GET_RX_FIFO_ENTRIES);

            GPS_UART_ClearRxInterruptSource(GPS_UART_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (GPS_UART_CHECK_TX_SW_BUFFER)
    {
        if (GPS_UART_CHECK_INTR_TX_MASKED(GPS_UART_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (GPS_UART_txBufferHead != GPS_UART_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (GPS_UART_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (GPS_UART_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    GPS_UART_TX_FIFO_WR_REG = GPS_UART_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    GPS_UART_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    GPS_UART_DISABLE_INTR_TX(GPS_UART_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (GPS_UART_SPI_UART_FIFO_SIZE != GPS_UART_GET_TX_FIFO_ENTRIES);

            GPS_UART_ClearTxInterruptSource(GPS_UART_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef GPS_UART_SPI_UART_ISR_EXIT_CALLBACK
    GPS_UART_SPI_UART_ISR_ExitCallback();
#endif /* GPS_UART_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (GPS_UART_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
