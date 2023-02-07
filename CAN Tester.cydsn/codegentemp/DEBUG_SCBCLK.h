/*******************************************************************************
* File Name: DEBUG_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_DEBUG_SCBCLK_H)
#define CY_CLOCK_DEBUG_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void DEBUG_SCBCLK_StartEx(uint32 alignClkDiv);
#define DEBUG_SCBCLK_Start() \
    DEBUG_SCBCLK_StartEx(DEBUG_SCBCLK__PA_DIV_ID)

#else

void DEBUG_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void DEBUG_SCBCLK_Stop(void);

void DEBUG_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 DEBUG_SCBCLK_GetDividerRegister(void);
uint8  DEBUG_SCBCLK_GetFractionalDividerRegister(void);

#define DEBUG_SCBCLK_Enable()                         DEBUG_SCBCLK_Start()
#define DEBUG_SCBCLK_Disable()                        DEBUG_SCBCLK_Stop()
#define DEBUG_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    DEBUG_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define DEBUG_SCBCLK_SetDivider(clkDivider)           DEBUG_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define DEBUG_SCBCLK_SetDividerValue(clkDivider)      DEBUG_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define DEBUG_SCBCLK_DIV_ID     DEBUG_SCBCLK__DIV_ID

#define DEBUG_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define DEBUG_SCBCLK_CTRL_REG   (*(reg32 *)DEBUG_SCBCLK__CTRL_REGISTER)
#define DEBUG_SCBCLK_DIV_REG    (*(reg32 *)DEBUG_SCBCLK__DIV_REGISTER)

#define DEBUG_SCBCLK_CMD_DIV_SHIFT          (0u)
#define DEBUG_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define DEBUG_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define DEBUG_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define DEBUG_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << DEBUG_SCBCLK_CMD_DISABLE_SHIFT))
#define DEBUG_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << DEBUG_SCBCLK_CMD_ENABLE_SHIFT))

#define DEBUG_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define DEBUG_SCBCLK_DIV_FRAC_SHIFT (3u)
#define DEBUG_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define DEBUG_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define DEBUG_SCBCLK_DIV_REG        (*(reg32 *)DEBUG_SCBCLK__REGISTER)
#define DEBUG_SCBCLK_ENABLE_REG     DEBUG_SCBCLK_DIV_REG
#define DEBUG_SCBCLK_DIV_FRAC_MASK  DEBUG_SCBCLK__FRAC_MASK
#define DEBUG_SCBCLK_DIV_FRAC_SHIFT (16u)
#define DEBUG_SCBCLK_DIV_INT_MASK   DEBUG_SCBCLK__DIVIDER_MASK
#define DEBUG_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_DEBUG_SCBCLK_H) */

/* [] END OF FILE */
