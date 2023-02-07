/***************************************************************************//**
* \file DEBUG_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_DEBUG_H)
#define CY_SCB_PINS_DEBUG_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define DEBUG_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define DEBUG_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define DEBUG_REMOVE_TX_SDA_MISO_PIN      (1u)
#define DEBUG_REMOVE_CTS_SCLK_PIN      (1u)
#define DEBUG_REMOVE_RTS_SS0_PIN      (1u)
#define DEBUG_REMOVE_SS1_PIN                 (1u)
#define DEBUG_REMOVE_SS2_PIN                 (1u)
#define DEBUG_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define DEBUG_REMOVE_I2C_PINS                (1u)
#define DEBUG_REMOVE_SPI_MASTER_PINS         (1u)
#define DEBUG_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define DEBUG_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define DEBUG_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define DEBUG_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define DEBUG_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define DEBUG_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define DEBUG_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define DEBUG_REMOVE_SPI_SLAVE_PINS          (1u)
#define DEBUG_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define DEBUG_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define DEBUG_REMOVE_UART_TX_PIN             (0u)
#define DEBUG_REMOVE_UART_RX_TX_PIN          (1u)
#define DEBUG_REMOVE_UART_RX_PIN             (0u)
#define DEBUG_REMOVE_UART_RX_WAKE_PIN        (1u)
#define DEBUG_REMOVE_UART_RTS_PIN            (1u)
#define DEBUG_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define DEBUG_RX_WAKE_SCL_MOSI_PIN (0u == DEBUG_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define DEBUG_RX_SCL_MOSI_PIN     (0u == DEBUG_REMOVE_RX_SCL_MOSI_PIN)
#define DEBUG_TX_SDA_MISO_PIN     (0u == DEBUG_REMOVE_TX_SDA_MISO_PIN)
#define DEBUG_CTS_SCLK_PIN     (0u == DEBUG_REMOVE_CTS_SCLK_PIN)
#define DEBUG_RTS_SS0_PIN     (0u == DEBUG_REMOVE_RTS_SS0_PIN)
#define DEBUG_SS1_PIN                (0u == DEBUG_REMOVE_SS1_PIN)
#define DEBUG_SS2_PIN                (0u == DEBUG_REMOVE_SS2_PIN)
#define DEBUG_SS3_PIN                (0u == DEBUG_REMOVE_SS3_PIN)

/* Mode defined pins */
#define DEBUG_I2C_PINS               (0u == DEBUG_REMOVE_I2C_PINS)
#define DEBUG_SPI_MASTER_PINS        (0u == DEBUG_REMOVE_SPI_MASTER_PINS)
#define DEBUG_SPI_MASTER_SCLK_PIN    (0u == DEBUG_REMOVE_SPI_MASTER_SCLK_PIN)
#define DEBUG_SPI_MASTER_MOSI_PIN    (0u == DEBUG_REMOVE_SPI_MASTER_MOSI_PIN)
#define DEBUG_SPI_MASTER_MISO_PIN    (0u == DEBUG_REMOVE_SPI_MASTER_MISO_PIN)
#define DEBUG_SPI_MASTER_SS0_PIN     (0u == DEBUG_REMOVE_SPI_MASTER_SS0_PIN)
#define DEBUG_SPI_MASTER_SS1_PIN     (0u == DEBUG_REMOVE_SPI_MASTER_SS1_PIN)
#define DEBUG_SPI_MASTER_SS2_PIN     (0u == DEBUG_REMOVE_SPI_MASTER_SS2_PIN)
#define DEBUG_SPI_MASTER_SS3_PIN     (0u == DEBUG_REMOVE_SPI_MASTER_SS3_PIN)
#define DEBUG_SPI_SLAVE_PINS         (0u == DEBUG_REMOVE_SPI_SLAVE_PINS)
#define DEBUG_SPI_SLAVE_MOSI_PIN     (0u == DEBUG_REMOVE_SPI_SLAVE_MOSI_PIN)
#define DEBUG_SPI_SLAVE_MISO_PIN     (0u == DEBUG_REMOVE_SPI_SLAVE_MISO_PIN)
#define DEBUG_UART_TX_PIN            (0u == DEBUG_REMOVE_UART_TX_PIN)
#define DEBUG_UART_RX_TX_PIN         (0u == DEBUG_REMOVE_UART_RX_TX_PIN)
#define DEBUG_UART_RX_PIN            (0u == DEBUG_REMOVE_UART_RX_PIN)
#define DEBUG_UART_RX_WAKE_PIN       (0u == DEBUG_REMOVE_UART_RX_WAKE_PIN)
#define DEBUG_UART_RTS_PIN           (0u == DEBUG_REMOVE_UART_RTS_PIN)
#define DEBUG_UART_CTS_PIN           (0u == DEBUG_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (DEBUG_RX_WAKE_SCL_MOSI_PIN)
    #include "DEBUG_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (DEBUG_RX_SCL_MOSI) */

#if (DEBUG_RX_SCL_MOSI_PIN)
    #include "DEBUG_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (DEBUG_RX_SCL_MOSI) */

#if (DEBUG_TX_SDA_MISO_PIN)
    #include "DEBUG_uart_tx_i2c_sda_spi_miso.h"
#endif /* (DEBUG_TX_SDA_MISO) */

#if (DEBUG_CTS_SCLK_PIN)
    #include "DEBUG_uart_cts_spi_sclk.h"
#endif /* (DEBUG_CTS_SCLK) */

#if (DEBUG_RTS_SS0_PIN)
    #include "DEBUG_uart_rts_spi_ss0.h"
#endif /* (DEBUG_RTS_SS0_PIN) */

#if (DEBUG_SS1_PIN)
    #include "DEBUG_spi_ss1.h"
#endif /* (DEBUG_SS1_PIN) */

#if (DEBUG_SS2_PIN)
    #include "DEBUG_spi_ss2.h"
#endif /* (DEBUG_SS2_PIN) */

#if (DEBUG_SS3_PIN)
    #include "DEBUG_spi_ss3.h"
#endif /* (DEBUG_SS3_PIN) */

#if (DEBUG_I2C_PINS)
    #include "DEBUG_scl.h"
    #include "DEBUG_sda.h"
#endif /* (DEBUG_I2C_PINS) */

#if (DEBUG_SPI_MASTER_PINS)
#if (DEBUG_SPI_MASTER_SCLK_PIN)
    #include "DEBUG_sclk_m.h"
#endif /* (DEBUG_SPI_MASTER_SCLK_PIN) */

#if (DEBUG_SPI_MASTER_MOSI_PIN)
    #include "DEBUG_mosi_m.h"
#endif /* (DEBUG_SPI_MASTER_MOSI_PIN) */

#if (DEBUG_SPI_MASTER_MISO_PIN)
    #include "DEBUG_miso_m.h"
#endif /*(DEBUG_SPI_MASTER_MISO_PIN) */
#endif /* (DEBUG_SPI_MASTER_PINS) */

#if (DEBUG_SPI_SLAVE_PINS)
    #include "DEBUG_sclk_s.h"
    #include "DEBUG_ss_s.h"

#if (DEBUG_SPI_SLAVE_MOSI_PIN)
    #include "DEBUG_mosi_s.h"
#endif /* (DEBUG_SPI_SLAVE_MOSI_PIN) */

#if (DEBUG_SPI_SLAVE_MISO_PIN)
    #include "DEBUG_miso_s.h"
#endif /*(DEBUG_SPI_SLAVE_MISO_PIN) */
#endif /* (DEBUG_SPI_SLAVE_PINS) */

#if (DEBUG_SPI_MASTER_SS0_PIN)
    #include "DEBUG_ss0_m.h"
#endif /* (DEBUG_SPI_MASTER_SS0_PIN) */

#if (DEBUG_SPI_MASTER_SS1_PIN)
    #include "DEBUG_ss1_m.h"
#endif /* (DEBUG_SPI_MASTER_SS1_PIN) */

#if (DEBUG_SPI_MASTER_SS2_PIN)
    #include "DEBUG_ss2_m.h"
#endif /* (DEBUG_SPI_MASTER_SS2_PIN) */

#if (DEBUG_SPI_MASTER_SS3_PIN)
    #include "DEBUG_ss3_m.h"
#endif /* (DEBUG_SPI_MASTER_SS3_PIN) */

#if (DEBUG_UART_TX_PIN)
    #include "DEBUG_tx.h"
#endif /* (DEBUG_UART_TX_PIN) */

#if (DEBUG_UART_RX_TX_PIN)
    #include "DEBUG_rx_tx.h"
#endif /* (DEBUG_UART_RX_TX_PIN) */

#if (DEBUG_UART_RX_PIN)
    #include "DEBUG_rx.h"
#endif /* (DEBUG_UART_RX_PIN) */

#if (DEBUG_UART_RX_WAKE_PIN)
    #include "DEBUG_rx_wake.h"
#endif /* (DEBUG_UART_RX_WAKE_PIN) */

#if (DEBUG_UART_RTS_PIN)
    #include "DEBUG_rts.h"
#endif /* (DEBUG_UART_RTS_PIN) */

#if (DEBUG_UART_CTS_PIN)
    #include "DEBUG_cts.h"
#endif /* (DEBUG_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (DEBUG_RX_SCL_MOSI_PIN)
    #define DEBUG_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define DEBUG_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define DEBUG_RX_SCL_MOSI_HSIOM_MASK      (DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define DEBUG_RX_SCL_MOSI_HSIOM_POS       (DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define DEBUG_RX_SCL_MOSI_HSIOM_SEL_GPIO  (DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define DEBUG_RX_SCL_MOSI_HSIOM_SEL_I2C   (DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define DEBUG_RX_SCL_MOSI_HSIOM_SEL_SPI   (DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define DEBUG_RX_SCL_MOSI_HSIOM_SEL_UART  (DEBUG_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_MASK      (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_POS       (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define DEBUG_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define DEBUG_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define DEBUG_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) DEBUG_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (DEBUG_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) DEBUG_INTCFG_TYPE_MASK << \
                                                                           DEBUG_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins DEBUG_RX_SCL_MOSI_PIN or DEBUG_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (DEBUG_RX_SCL_MOSI_PIN) */

#if (DEBUG_TX_SDA_MISO_PIN)
    #define DEBUG_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define DEBUG_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define DEBUG_TX_SDA_MISO_HSIOM_MASK      (DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define DEBUG_TX_SDA_MISO_HSIOM_POS       (DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define DEBUG_TX_SDA_MISO_HSIOM_SEL_GPIO  (DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define DEBUG_TX_SDA_MISO_HSIOM_SEL_I2C   (DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define DEBUG_TX_SDA_MISO_HSIOM_SEL_SPI   (DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define DEBUG_TX_SDA_MISO_HSIOM_SEL_UART  (DEBUG_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (DEBUG_TX_SDA_MISO_PIN) */

#if (DEBUG_CTS_SCLK_PIN)
    #define DEBUG_CTS_SCLK_HSIOM_REG   (*(reg32 *) DEBUG_uart_cts_spi_sclk__0__HSIOM)
    #define DEBUG_CTS_SCLK_HSIOM_PTR   ( (reg32 *) DEBUG_uart_cts_spi_sclk__0__HSIOM)
    
    #define DEBUG_CTS_SCLK_HSIOM_MASK      (DEBUG_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define DEBUG_CTS_SCLK_HSIOM_POS       (DEBUG_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define DEBUG_CTS_SCLK_HSIOM_SEL_GPIO  (DEBUG_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define DEBUG_CTS_SCLK_HSIOM_SEL_I2C   (DEBUG_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define DEBUG_CTS_SCLK_HSIOM_SEL_SPI   (DEBUG_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define DEBUG_CTS_SCLK_HSIOM_SEL_UART  (DEBUG_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (DEBUG_CTS_SCLK_PIN) */

#if (DEBUG_RTS_SS0_PIN)
    #define DEBUG_RTS_SS0_HSIOM_REG   (*(reg32 *) DEBUG_uart_rts_spi_ss0__0__HSIOM)
    #define DEBUG_RTS_SS0_HSIOM_PTR   ( (reg32 *) DEBUG_uart_rts_spi_ss0__0__HSIOM)
    
    #define DEBUG_RTS_SS0_HSIOM_MASK      (DEBUG_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define DEBUG_RTS_SS0_HSIOM_POS       (DEBUG_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define DEBUG_RTS_SS0_HSIOM_SEL_GPIO  (DEBUG_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define DEBUG_RTS_SS0_HSIOM_SEL_I2C   (DEBUG_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define DEBUG_RTS_SS0_HSIOM_SEL_SPI   (DEBUG_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1)
    #define DEBUG_RTS_SS0_HSIOM_SEL_UART  (DEBUG_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(DEBUG_CY_SCBIP_V0 || DEBUG_CY_SCBIP_V1) */
#endif /* (DEBUG_RTS_SS0_PIN) */

#if (DEBUG_SS1_PIN)
    #define DEBUG_SS1_HSIOM_REG  (*(reg32 *) DEBUG_spi_ss1__0__HSIOM)
    #define DEBUG_SS1_HSIOM_PTR  ( (reg32 *) DEBUG_spi_ss1__0__HSIOM)
    
    #define DEBUG_SS1_HSIOM_MASK     (DEBUG_spi_ss1__0__HSIOM_MASK)
    #define DEBUG_SS1_HSIOM_POS      (DEBUG_spi_ss1__0__HSIOM_SHIFT)
    #define DEBUG_SS1_HSIOM_SEL_GPIO (DEBUG_spi_ss1__0__HSIOM_GPIO)
    #define DEBUG_SS1_HSIOM_SEL_I2C  (DEBUG_spi_ss1__0__HSIOM_I2C)
    #define DEBUG_SS1_HSIOM_SEL_SPI  (DEBUG_spi_ss1__0__HSIOM_SPI)
#endif /* (DEBUG_SS1_PIN) */

#if (DEBUG_SS2_PIN)
    #define DEBUG_SS2_HSIOM_REG     (*(reg32 *) DEBUG_spi_ss2__0__HSIOM)
    #define DEBUG_SS2_HSIOM_PTR     ( (reg32 *) DEBUG_spi_ss2__0__HSIOM)
    
    #define DEBUG_SS2_HSIOM_MASK     (DEBUG_spi_ss2__0__HSIOM_MASK)
    #define DEBUG_SS2_HSIOM_POS      (DEBUG_spi_ss2__0__HSIOM_SHIFT)
    #define DEBUG_SS2_HSIOM_SEL_GPIO (DEBUG_spi_ss2__0__HSIOM_GPIO)
    #define DEBUG_SS2_HSIOM_SEL_I2C  (DEBUG_spi_ss2__0__HSIOM_I2C)
    #define DEBUG_SS2_HSIOM_SEL_SPI  (DEBUG_spi_ss2__0__HSIOM_SPI)
#endif /* (DEBUG_SS2_PIN) */

#if (DEBUG_SS3_PIN)
    #define DEBUG_SS3_HSIOM_REG     (*(reg32 *) DEBUG_spi_ss3__0__HSIOM)
    #define DEBUG_SS3_HSIOM_PTR     ( (reg32 *) DEBUG_spi_ss3__0__HSIOM)
    
    #define DEBUG_SS3_HSIOM_MASK     (DEBUG_spi_ss3__0__HSIOM_MASK)
    #define DEBUG_SS3_HSIOM_POS      (DEBUG_spi_ss3__0__HSIOM_SHIFT)
    #define DEBUG_SS3_HSIOM_SEL_GPIO (DEBUG_spi_ss3__0__HSIOM_GPIO)
    #define DEBUG_SS3_HSIOM_SEL_I2C  (DEBUG_spi_ss3__0__HSIOM_I2C)
    #define DEBUG_SS3_HSIOM_SEL_SPI  (DEBUG_spi_ss3__0__HSIOM_SPI)
#endif /* (DEBUG_SS3_PIN) */

#if (DEBUG_I2C_PINS)
    #define DEBUG_SCL_HSIOM_REG  (*(reg32 *) DEBUG_scl__0__HSIOM)
    #define DEBUG_SCL_HSIOM_PTR  ( (reg32 *) DEBUG_scl__0__HSIOM)
    
    #define DEBUG_SCL_HSIOM_MASK     (DEBUG_scl__0__HSIOM_MASK)
    #define DEBUG_SCL_HSIOM_POS      (DEBUG_scl__0__HSIOM_SHIFT)
    #define DEBUG_SCL_HSIOM_SEL_GPIO (DEBUG_sda__0__HSIOM_GPIO)
    #define DEBUG_SCL_HSIOM_SEL_I2C  (DEBUG_sda__0__HSIOM_I2C)
    
    #define DEBUG_SDA_HSIOM_REG  (*(reg32 *) DEBUG_sda__0__HSIOM)
    #define DEBUG_SDA_HSIOM_PTR  ( (reg32 *) DEBUG_sda__0__HSIOM)
    
    #define DEBUG_SDA_HSIOM_MASK     (DEBUG_sda__0__HSIOM_MASK)
    #define DEBUG_SDA_HSIOM_POS      (DEBUG_sda__0__HSIOM_SHIFT)
    #define DEBUG_SDA_HSIOM_SEL_GPIO (DEBUG_sda__0__HSIOM_GPIO)
    #define DEBUG_SDA_HSIOM_SEL_I2C  (DEBUG_sda__0__HSIOM_I2C)
#endif /* (DEBUG_I2C_PINS) */

#if (DEBUG_SPI_SLAVE_PINS)
    #define DEBUG_SCLK_S_HSIOM_REG   (*(reg32 *) DEBUG_sclk_s__0__HSIOM)
    #define DEBUG_SCLK_S_HSIOM_PTR   ( (reg32 *) DEBUG_sclk_s__0__HSIOM)
    
    #define DEBUG_SCLK_S_HSIOM_MASK      (DEBUG_sclk_s__0__HSIOM_MASK)
    #define DEBUG_SCLK_S_HSIOM_POS       (DEBUG_sclk_s__0__HSIOM_SHIFT)
    #define DEBUG_SCLK_S_HSIOM_SEL_GPIO  (DEBUG_sclk_s__0__HSIOM_GPIO)
    #define DEBUG_SCLK_S_HSIOM_SEL_SPI   (DEBUG_sclk_s__0__HSIOM_SPI)
    
    #define DEBUG_SS0_S_HSIOM_REG    (*(reg32 *) DEBUG_ss0_s__0__HSIOM)
    #define DEBUG_SS0_S_HSIOM_PTR    ( (reg32 *) DEBUG_ss0_s__0__HSIOM)
    
    #define DEBUG_SS0_S_HSIOM_MASK       (DEBUG_ss0_s__0__HSIOM_MASK)
    #define DEBUG_SS0_S_HSIOM_POS        (DEBUG_ss0_s__0__HSIOM_SHIFT)
    #define DEBUG_SS0_S_HSIOM_SEL_GPIO   (DEBUG_ss0_s__0__HSIOM_GPIO)  
    #define DEBUG_SS0_S_HSIOM_SEL_SPI    (DEBUG_ss0_s__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_SLAVE_PINS) */

#if (DEBUG_SPI_SLAVE_MOSI_PIN)
    #define DEBUG_MOSI_S_HSIOM_REG   (*(reg32 *) DEBUG_mosi_s__0__HSIOM)
    #define DEBUG_MOSI_S_HSIOM_PTR   ( (reg32 *) DEBUG_mosi_s__0__HSIOM)
    
    #define DEBUG_MOSI_S_HSIOM_MASK      (DEBUG_mosi_s__0__HSIOM_MASK)
    #define DEBUG_MOSI_S_HSIOM_POS       (DEBUG_mosi_s__0__HSIOM_SHIFT)
    #define DEBUG_MOSI_S_HSIOM_SEL_GPIO  (DEBUG_mosi_s__0__HSIOM_GPIO)
    #define DEBUG_MOSI_S_HSIOM_SEL_SPI   (DEBUG_mosi_s__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_SLAVE_MOSI_PIN) */

#if (DEBUG_SPI_SLAVE_MISO_PIN)
    #define DEBUG_MISO_S_HSIOM_REG   (*(reg32 *) DEBUG_miso_s__0__HSIOM)
    #define DEBUG_MISO_S_HSIOM_PTR   ( (reg32 *) DEBUG_miso_s__0__HSIOM)
    
    #define DEBUG_MISO_S_HSIOM_MASK      (DEBUG_miso_s__0__HSIOM_MASK)
    #define DEBUG_MISO_S_HSIOM_POS       (DEBUG_miso_s__0__HSIOM_SHIFT)
    #define DEBUG_MISO_S_HSIOM_SEL_GPIO  (DEBUG_miso_s__0__HSIOM_GPIO)
    #define DEBUG_MISO_S_HSIOM_SEL_SPI   (DEBUG_miso_s__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_SLAVE_MISO_PIN) */

#if (DEBUG_SPI_MASTER_MISO_PIN)
    #define DEBUG_MISO_M_HSIOM_REG   (*(reg32 *) DEBUG_miso_m__0__HSIOM)
    #define DEBUG_MISO_M_HSIOM_PTR   ( (reg32 *) DEBUG_miso_m__0__HSIOM)
    
    #define DEBUG_MISO_M_HSIOM_MASK      (DEBUG_miso_m__0__HSIOM_MASK)
    #define DEBUG_MISO_M_HSIOM_POS       (DEBUG_miso_m__0__HSIOM_SHIFT)
    #define DEBUG_MISO_M_HSIOM_SEL_GPIO  (DEBUG_miso_m__0__HSIOM_GPIO)
    #define DEBUG_MISO_M_HSIOM_SEL_SPI   (DEBUG_miso_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_MISO_PIN) */

#if (DEBUG_SPI_MASTER_MOSI_PIN)
    #define DEBUG_MOSI_M_HSIOM_REG   (*(reg32 *) DEBUG_mosi_m__0__HSIOM)
    #define DEBUG_MOSI_M_HSIOM_PTR   ( (reg32 *) DEBUG_mosi_m__0__HSIOM)
    
    #define DEBUG_MOSI_M_HSIOM_MASK      (DEBUG_mosi_m__0__HSIOM_MASK)
    #define DEBUG_MOSI_M_HSIOM_POS       (DEBUG_mosi_m__0__HSIOM_SHIFT)
    #define DEBUG_MOSI_M_HSIOM_SEL_GPIO  (DEBUG_mosi_m__0__HSIOM_GPIO)
    #define DEBUG_MOSI_M_HSIOM_SEL_SPI   (DEBUG_mosi_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_MOSI_PIN) */

#if (DEBUG_SPI_MASTER_SCLK_PIN)
    #define DEBUG_SCLK_M_HSIOM_REG   (*(reg32 *) DEBUG_sclk_m__0__HSIOM)
    #define DEBUG_SCLK_M_HSIOM_PTR   ( (reg32 *) DEBUG_sclk_m__0__HSIOM)
    
    #define DEBUG_SCLK_M_HSIOM_MASK      (DEBUG_sclk_m__0__HSIOM_MASK)
    #define DEBUG_SCLK_M_HSIOM_POS       (DEBUG_sclk_m__0__HSIOM_SHIFT)
    #define DEBUG_SCLK_M_HSIOM_SEL_GPIO  (DEBUG_sclk_m__0__HSIOM_GPIO)
    #define DEBUG_SCLK_M_HSIOM_SEL_SPI   (DEBUG_sclk_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_SCLK_PIN) */

#if (DEBUG_SPI_MASTER_SS0_PIN)
    #define DEBUG_SS0_M_HSIOM_REG    (*(reg32 *) DEBUG_ss0_m__0__HSIOM)
    #define DEBUG_SS0_M_HSIOM_PTR    ( (reg32 *) DEBUG_ss0_m__0__HSIOM)
    
    #define DEBUG_SS0_M_HSIOM_MASK       (DEBUG_ss0_m__0__HSIOM_MASK)
    #define DEBUG_SS0_M_HSIOM_POS        (DEBUG_ss0_m__0__HSIOM_SHIFT)
    #define DEBUG_SS0_M_HSIOM_SEL_GPIO   (DEBUG_ss0_m__0__HSIOM_GPIO)
    #define DEBUG_SS0_M_HSIOM_SEL_SPI    (DEBUG_ss0_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_SS0_PIN) */

#if (DEBUG_SPI_MASTER_SS1_PIN)
    #define DEBUG_SS1_M_HSIOM_REG    (*(reg32 *) DEBUG_ss1_m__0__HSIOM)
    #define DEBUG_SS1_M_HSIOM_PTR    ( (reg32 *) DEBUG_ss1_m__0__HSIOM)
    
    #define DEBUG_SS1_M_HSIOM_MASK       (DEBUG_ss1_m__0__HSIOM_MASK)
    #define DEBUG_SS1_M_HSIOM_POS        (DEBUG_ss1_m__0__HSIOM_SHIFT)
    #define DEBUG_SS1_M_HSIOM_SEL_GPIO   (DEBUG_ss1_m__0__HSIOM_GPIO)
    #define DEBUG_SS1_M_HSIOM_SEL_SPI    (DEBUG_ss1_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_SS1_PIN) */

#if (DEBUG_SPI_MASTER_SS2_PIN)
    #define DEBUG_SS2_M_HSIOM_REG    (*(reg32 *) DEBUG_ss2_m__0__HSIOM)
    #define DEBUG_SS2_M_HSIOM_PTR    ( (reg32 *) DEBUG_ss2_m__0__HSIOM)
    
    #define DEBUG_SS2_M_HSIOM_MASK       (DEBUG_ss2_m__0__HSIOM_MASK)
    #define DEBUG_SS2_M_HSIOM_POS        (DEBUG_ss2_m__0__HSIOM_SHIFT)
    #define DEBUG_SS2_M_HSIOM_SEL_GPIO   (DEBUG_ss2_m__0__HSIOM_GPIO)
    #define DEBUG_SS2_M_HSIOM_SEL_SPI    (DEBUG_ss2_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_SS2_PIN) */

#if (DEBUG_SPI_MASTER_SS3_PIN)
    #define DEBUG_SS3_M_HSIOM_REG    (*(reg32 *) DEBUG_ss3_m__0__HSIOM)
    #define DEBUG_SS3_M_HSIOM_PTR    ( (reg32 *) DEBUG_ss3_m__0__HSIOM)
    
    #define DEBUG_SS3_M_HSIOM_MASK      (DEBUG_ss3_m__0__HSIOM_MASK)
    #define DEBUG_SS3_M_HSIOM_POS       (DEBUG_ss3_m__0__HSIOM_SHIFT)
    #define DEBUG_SS3_M_HSIOM_SEL_GPIO  (DEBUG_ss3_m__0__HSIOM_GPIO)
    #define DEBUG_SS3_M_HSIOM_SEL_SPI   (DEBUG_ss3_m__0__HSIOM_SPI)
#endif /* (DEBUG_SPI_MASTER_SS3_PIN) */

#if (DEBUG_UART_RX_PIN)
    #define DEBUG_RX_HSIOM_REG   (*(reg32 *) DEBUG_rx__0__HSIOM)
    #define DEBUG_RX_HSIOM_PTR   ( (reg32 *) DEBUG_rx__0__HSIOM)
    
    #define DEBUG_RX_HSIOM_MASK      (DEBUG_rx__0__HSIOM_MASK)
    #define DEBUG_RX_HSIOM_POS       (DEBUG_rx__0__HSIOM_SHIFT)
    #define DEBUG_RX_HSIOM_SEL_GPIO  (DEBUG_rx__0__HSIOM_GPIO)
    #define DEBUG_RX_HSIOM_SEL_UART  (DEBUG_rx__0__HSIOM_UART)
#endif /* (DEBUG_UART_RX_PIN) */

#if (DEBUG_UART_RX_WAKE_PIN)
    #define DEBUG_RX_WAKE_HSIOM_REG   (*(reg32 *) DEBUG_rx_wake__0__HSIOM)
    #define DEBUG_RX_WAKE_HSIOM_PTR   ( (reg32 *) DEBUG_rx_wake__0__HSIOM)
    
    #define DEBUG_RX_WAKE_HSIOM_MASK      (DEBUG_rx_wake__0__HSIOM_MASK)
    #define DEBUG_RX_WAKE_HSIOM_POS       (DEBUG_rx_wake__0__HSIOM_SHIFT)
    #define DEBUG_RX_WAKE_HSIOM_SEL_GPIO  (DEBUG_rx_wake__0__HSIOM_GPIO)
    #define DEBUG_RX_WAKE_HSIOM_SEL_UART  (DEBUG_rx_wake__0__HSIOM_UART)
#endif /* (DEBUG_UART_WAKE_RX_PIN) */

#if (DEBUG_UART_CTS_PIN)
    #define DEBUG_CTS_HSIOM_REG   (*(reg32 *) DEBUG_cts__0__HSIOM)
    #define DEBUG_CTS_HSIOM_PTR   ( (reg32 *) DEBUG_cts__0__HSIOM)
    
    #define DEBUG_CTS_HSIOM_MASK      (DEBUG_cts__0__HSIOM_MASK)
    #define DEBUG_CTS_HSIOM_POS       (DEBUG_cts__0__HSIOM_SHIFT)
    #define DEBUG_CTS_HSIOM_SEL_GPIO  (DEBUG_cts__0__HSIOM_GPIO)
    #define DEBUG_CTS_HSIOM_SEL_UART  (DEBUG_cts__0__HSIOM_UART)
#endif /* (DEBUG_UART_CTS_PIN) */

#if (DEBUG_UART_TX_PIN)
    #define DEBUG_TX_HSIOM_REG   (*(reg32 *) DEBUG_tx__0__HSIOM)
    #define DEBUG_TX_HSIOM_PTR   ( (reg32 *) DEBUG_tx__0__HSIOM)
    
    #define DEBUG_TX_HSIOM_MASK      (DEBUG_tx__0__HSIOM_MASK)
    #define DEBUG_TX_HSIOM_POS       (DEBUG_tx__0__HSIOM_SHIFT)
    #define DEBUG_TX_HSIOM_SEL_GPIO  (DEBUG_tx__0__HSIOM_GPIO)
    #define DEBUG_TX_HSIOM_SEL_UART  (DEBUG_tx__0__HSIOM_UART)
#endif /* (DEBUG_UART_TX_PIN) */

#if (DEBUG_UART_RX_TX_PIN)
    #define DEBUG_RX_TX_HSIOM_REG   (*(reg32 *) DEBUG_rx_tx__0__HSIOM)
    #define DEBUG_RX_TX_HSIOM_PTR   ( (reg32 *) DEBUG_rx_tx__0__HSIOM)
    
    #define DEBUG_RX_TX_HSIOM_MASK      (DEBUG_rx_tx__0__HSIOM_MASK)
    #define DEBUG_RX_TX_HSIOM_POS       (DEBUG_rx_tx__0__HSIOM_SHIFT)
    #define DEBUG_RX_TX_HSIOM_SEL_GPIO  (DEBUG_rx_tx__0__HSIOM_GPIO)
    #define DEBUG_RX_TX_HSIOM_SEL_UART  (DEBUG_rx_tx__0__HSIOM_UART)
#endif /* (DEBUG_UART_RX_TX_PIN) */

#if (DEBUG_UART_RTS_PIN)
    #define DEBUG_RTS_HSIOM_REG      (*(reg32 *) DEBUG_rts__0__HSIOM)
    #define DEBUG_RTS_HSIOM_PTR      ( (reg32 *) DEBUG_rts__0__HSIOM)
    
    #define DEBUG_RTS_HSIOM_MASK     (DEBUG_rts__0__HSIOM_MASK)
    #define DEBUG_RTS_HSIOM_POS      (DEBUG_rts__0__HSIOM_SHIFT)    
    #define DEBUG_RTS_HSIOM_SEL_GPIO (DEBUG_rts__0__HSIOM_GPIO)
    #define DEBUG_RTS_HSIOM_SEL_UART (DEBUG_rts__0__HSIOM_UART)    
#endif /* (DEBUG_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define DEBUG_HSIOM_DEF_SEL      (0x00u)
#define DEBUG_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for DEBUG_CY_SCBIP_V0 
* and DEBUG_CY_SCBIP_V1. It is not recommended to use them for 
* DEBUG_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define DEBUG_HSIOM_UART_SEL     (0x09u)
#define DEBUG_HSIOM_I2C_SEL      (0x0Eu)
#define DEBUG_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define DEBUG_RX_SCL_MOSI_PIN_INDEX       (0u)
#define DEBUG_TX_SDA_MISO_PIN_INDEX       (1u)
#define DEBUG_CTS_SCLK_PIN_INDEX       (2u)
#define DEBUG_RTS_SS0_PIN_INDEX       (3u)
#define DEBUG_SS1_PIN_INDEX                  (4u)
#define DEBUG_SS2_PIN_INDEX                  (5u)
#define DEBUG_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define DEBUG_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define DEBUG_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << DEBUG_RX_SCL_MOSI_PIN_INDEX)
#define DEBUG_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << DEBUG_TX_SDA_MISO_PIN_INDEX)
#define DEBUG_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << DEBUG_CTS_SCLK_PIN_INDEX)
#define DEBUG_RTS_SS0_PIN_MASK     ((uint32) 0x01u << DEBUG_RTS_SS0_PIN_INDEX)
#define DEBUG_SS1_PIN_MASK                ((uint32) 0x01u << DEBUG_SS1_PIN_INDEX)
#define DEBUG_SS2_PIN_MASK                ((uint32) 0x01u << DEBUG_SS2_PIN_INDEX)
#define DEBUG_SS3_PIN_MASK                ((uint32) 0x01u << DEBUG_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define DEBUG_INTCFG_TYPE_MASK           (0x03u)
#define DEBUG_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define DEBUG_PIN_DM_ALG_HIZ  (0u)
#define DEBUG_PIN_DM_DIG_HIZ  (1u)
#define DEBUG_PIN_DM_OD_LO    (4u)
#define DEBUG_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define DEBUG_DM_MASK    (0x7u)
#define DEBUG_DM_SIZE    (3u)
#define DEBUG_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) DEBUG_DM_MASK << (DEBUG_DM_SIZE * (pos)))) >> \
                                                              (DEBUG_DM_SIZE * (pos)) )

#if (DEBUG_TX_SDA_MISO_PIN)
    #define DEBUG_CHECK_TX_SDA_MISO_PIN_USED \
                (DEBUG_PIN_DM_ALG_HIZ != \
                    DEBUG_GET_P4_PIN_DM(DEBUG_uart_tx_i2c_sda_spi_miso_PC, \
                                                   DEBUG_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (DEBUG_TX_SDA_MISO_PIN) */

#if (DEBUG_RTS_SS0_PIN)
    #define DEBUG_CHECK_RTS_SS0_PIN_USED \
                (DEBUG_PIN_DM_ALG_HIZ != \
                    DEBUG_GET_P4_PIN_DM(DEBUG_uart_rts_spi_ss0_PC, \
                                                   DEBUG_uart_rts_spi_ss0_SHIFT))
#endif /* (DEBUG_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define DEBUG_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define DEBUG_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define DEBUG_SET_HSIOM_SEL(reg, mask, pos, sel) DEBUG_SET_REGISTER_BITS(reg, mask, pos, sel)
#define DEBUG_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        DEBUG_SET_REGISTER_BITS(reg, mask, pos, intType)
#define DEBUG_SET_INP_DIS(reg, mask, val) DEBUG_SET_REGISTER_BIT(reg, mask, val)

/* DEBUG_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  DEBUG_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (DEBUG_CY_SCBIP_V0)
#if (DEBUG_I2C_PINS)
    #define DEBUG_SET_I2C_SCL_DR(val) DEBUG_scl_Write(val)

    #define DEBUG_SET_I2C_SCL_HSIOM_SEL(sel) \
                          DEBUG_SET_HSIOM_SEL(DEBUG_SCL_HSIOM_REG,  \
                                                         DEBUG_SCL_HSIOM_MASK, \
                                                         DEBUG_SCL_HSIOM_POS,  \
                                                         (sel))
    #define DEBUG_WAIT_SCL_SET_HIGH  (0u == DEBUG_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
    #define DEBUG_SET_I2C_SCL_DR(val) \
                            DEBUG_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define DEBUG_SET_I2C_SCL_HSIOM_SEL(sel) \
                    DEBUG_SET_HSIOM_SEL(DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   DEBUG_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   DEBUG_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define DEBUG_WAIT_SCL_SET_HIGH  (0u == DEBUG_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (DEBUG_RX_SCL_MOSI_PIN)
    #define DEBUG_SET_I2C_SCL_DR(val) \
                            DEBUG_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define DEBUG_SET_I2C_SCL_HSIOM_SEL(sel) \
                            DEBUG_SET_HSIOM_SEL(DEBUG_RX_SCL_MOSI_HSIOM_REG,  \
                                                           DEBUG_RX_SCL_MOSI_HSIOM_MASK, \
                                                           DEBUG_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define DEBUG_WAIT_SCL_SET_HIGH  (0u == DEBUG_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define DEBUG_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define DEBUG_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define DEBUG_WAIT_SCL_SET_HIGH  (0u)
#endif /* (DEBUG_I2C_PINS) */

/* SCB I2C: sda signal */
#if (DEBUG_I2C_PINS)
    #define DEBUG_WAIT_SDA_SET_HIGH  (0u == DEBUG_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (DEBUG_TX_SDA_MISO_PIN)
    #define DEBUG_WAIT_SDA_SET_HIGH  (0u == DEBUG_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define DEBUG_WAIT_SDA_SET_HIGH  (0u)
#endif /* (DEBUG_MOSI_SCL_RX_PIN) */
#endif /* (DEBUG_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (DEBUG_RX_SCL_MOSI_PIN)
    #define DEBUG_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (DEBUG_RX_WAKE_SCL_MOSI_PIN)
    #define DEBUG_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) DEBUG_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(DEBUG_UART_RX_WAKE_PIN)
    #define DEBUG_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) DEBUG_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (DEBUG_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define DEBUG_REMOVE_MOSI_SCL_RX_WAKE_PIN    DEBUG_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define DEBUG_REMOVE_MOSI_SCL_RX_PIN         DEBUG_REMOVE_RX_SCL_MOSI_PIN
#define DEBUG_REMOVE_MISO_SDA_TX_PIN         DEBUG_REMOVE_TX_SDA_MISO_PIN
#ifndef DEBUG_REMOVE_SCLK_PIN
#define DEBUG_REMOVE_SCLK_PIN                DEBUG_REMOVE_CTS_SCLK_PIN
#endif /* DEBUG_REMOVE_SCLK_PIN */
#ifndef DEBUG_REMOVE_SS0_PIN
#define DEBUG_REMOVE_SS0_PIN                 DEBUG_REMOVE_RTS_SS0_PIN
#endif /* DEBUG_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define DEBUG_MOSI_SCL_RX_WAKE_PIN   DEBUG_RX_WAKE_SCL_MOSI_PIN
#define DEBUG_MOSI_SCL_RX_PIN        DEBUG_RX_SCL_MOSI_PIN
#define DEBUG_MISO_SDA_TX_PIN        DEBUG_TX_SDA_MISO_PIN
#ifndef DEBUG_SCLK_PIN
#define DEBUG_SCLK_PIN               DEBUG_CTS_SCLK_PIN
#endif /* DEBUG_SCLK_PIN */
#ifndef DEBUG_SS0_PIN
#define DEBUG_SS0_PIN                DEBUG_RTS_SS0_PIN
#endif /* DEBUG_SS0_PIN */

#if (DEBUG_MOSI_SCL_RX_WAKE_PIN)
    #define DEBUG_MOSI_SCL_RX_WAKE_HSIOM_REG     DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DEBUG_MOSI_SCL_RX_WAKE_HSIOM_PTR     DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DEBUG_MOSI_SCL_RX_WAKE_HSIOM_MASK    DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DEBUG_MOSI_SCL_RX_WAKE_HSIOM_POS     DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define DEBUG_MOSI_SCL_RX_WAKE_INTCFG_REG    DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DEBUG_MOSI_SCL_RX_WAKE_INTCFG_PTR    DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define DEBUG_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define DEBUG_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  DEBUG_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (DEBUG_RX_WAKE_SCL_MOSI_PIN) */

#if (DEBUG_MOSI_SCL_RX_PIN)
    #define DEBUG_MOSI_SCL_RX_HSIOM_REG      DEBUG_RX_SCL_MOSI_HSIOM_REG
    #define DEBUG_MOSI_SCL_RX_HSIOM_PTR      DEBUG_RX_SCL_MOSI_HSIOM_PTR
    #define DEBUG_MOSI_SCL_RX_HSIOM_MASK     DEBUG_RX_SCL_MOSI_HSIOM_MASK
    #define DEBUG_MOSI_SCL_RX_HSIOM_POS      DEBUG_RX_SCL_MOSI_HSIOM_POS
#endif /* (DEBUG_MOSI_SCL_RX_PIN) */

#if (DEBUG_MISO_SDA_TX_PIN)
    #define DEBUG_MISO_SDA_TX_HSIOM_REG      DEBUG_TX_SDA_MISO_HSIOM_REG
    #define DEBUG_MISO_SDA_TX_HSIOM_PTR      DEBUG_TX_SDA_MISO_HSIOM_REG
    #define DEBUG_MISO_SDA_TX_HSIOM_MASK     DEBUG_TX_SDA_MISO_HSIOM_REG
    #define DEBUG_MISO_SDA_TX_HSIOM_POS      DEBUG_TX_SDA_MISO_HSIOM_REG
#endif /* (DEBUG_MISO_SDA_TX_PIN_PIN) */

#if (DEBUG_SCLK_PIN)
    #ifndef DEBUG_SCLK_HSIOM_REG
    #define DEBUG_SCLK_HSIOM_REG     DEBUG_CTS_SCLK_HSIOM_REG
    #define DEBUG_SCLK_HSIOM_PTR     DEBUG_CTS_SCLK_HSIOM_PTR
    #define DEBUG_SCLK_HSIOM_MASK    DEBUG_CTS_SCLK_HSIOM_MASK
    #define DEBUG_SCLK_HSIOM_POS     DEBUG_CTS_SCLK_HSIOM_POS
    #endif /* DEBUG_SCLK_HSIOM_REG */
#endif /* (DEBUG_SCLK_PIN) */

#if (DEBUG_SS0_PIN)
    #ifndef DEBUG_SS0_HSIOM_REG
    #define DEBUG_SS0_HSIOM_REG      DEBUG_RTS_SS0_HSIOM_REG
    #define DEBUG_SS0_HSIOM_PTR      DEBUG_RTS_SS0_HSIOM_PTR
    #define DEBUG_SS0_HSIOM_MASK     DEBUG_RTS_SS0_HSIOM_MASK
    #define DEBUG_SS0_HSIOM_POS      DEBUG_RTS_SS0_HSIOM_POS
    #endif /* DEBUG_SS0_HSIOM_REG */
#endif /* (DEBUG_SS0_PIN) */

#define DEBUG_MOSI_SCL_RX_WAKE_PIN_INDEX DEBUG_RX_WAKE_SCL_MOSI_PIN_INDEX
#define DEBUG_MOSI_SCL_RX_PIN_INDEX      DEBUG_RX_SCL_MOSI_PIN_INDEX
#define DEBUG_MISO_SDA_TX_PIN_INDEX      DEBUG_TX_SDA_MISO_PIN_INDEX
#ifndef DEBUG_SCLK_PIN_INDEX
#define DEBUG_SCLK_PIN_INDEX             DEBUG_CTS_SCLK_PIN_INDEX
#endif /* DEBUG_SCLK_PIN_INDEX */
#ifndef DEBUG_SS0_PIN_INDEX
#define DEBUG_SS0_PIN_INDEX              DEBUG_RTS_SS0_PIN_INDEX
#endif /* DEBUG_SS0_PIN_INDEX */

#define DEBUG_MOSI_SCL_RX_WAKE_PIN_MASK DEBUG_RX_WAKE_SCL_MOSI_PIN_MASK
#define DEBUG_MOSI_SCL_RX_PIN_MASK      DEBUG_RX_SCL_MOSI_PIN_MASK
#define DEBUG_MISO_SDA_TX_PIN_MASK      DEBUG_TX_SDA_MISO_PIN_MASK
#ifndef DEBUG_SCLK_PIN_MASK
#define DEBUG_SCLK_PIN_MASK             DEBUG_CTS_SCLK_PIN_MASK
#endif /* DEBUG_SCLK_PIN_MASK */
#ifndef DEBUG_SS0_PIN_MASK
#define DEBUG_SS0_PIN_MASK              DEBUG_RTS_SS0_PIN_MASK
#endif /* DEBUG_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_DEBUG_H) */


/* [] END OF FILE */
