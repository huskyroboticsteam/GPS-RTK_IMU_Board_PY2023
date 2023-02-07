/*******************************************************************************
* File Name: IMU_I2C_SCBCLK.h
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

#if !defined(CY_CLOCK_IMU_I2C_SCBCLK_H)
#define CY_CLOCK_IMU_I2C_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void IMU_I2C_SCBCLK_StartEx(uint32 alignClkDiv);
#define IMU_I2C_SCBCLK_Start() \
    IMU_I2C_SCBCLK_StartEx(IMU_I2C_SCBCLK__PA_DIV_ID)

#else

void IMU_I2C_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void IMU_I2C_SCBCLK_Stop(void);

void IMU_I2C_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 IMU_I2C_SCBCLK_GetDividerRegister(void);
uint8  IMU_I2C_SCBCLK_GetFractionalDividerRegister(void);

#define IMU_I2C_SCBCLK_Enable()                         IMU_I2C_SCBCLK_Start()
#define IMU_I2C_SCBCLK_Disable()                        IMU_I2C_SCBCLK_Stop()
#define IMU_I2C_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    IMU_I2C_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define IMU_I2C_SCBCLK_SetDivider(clkDivider)           IMU_I2C_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define IMU_I2C_SCBCLK_SetDividerValue(clkDivider)      IMU_I2C_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define IMU_I2C_SCBCLK_DIV_ID     IMU_I2C_SCBCLK__DIV_ID

#define IMU_I2C_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define IMU_I2C_SCBCLK_CTRL_REG   (*(reg32 *)IMU_I2C_SCBCLK__CTRL_REGISTER)
#define IMU_I2C_SCBCLK_DIV_REG    (*(reg32 *)IMU_I2C_SCBCLK__DIV_REGISTER)

#define IMU_I2C_SCBCLK_CMD_DIV_SHIFT          (0u)
#define IMU_I2C_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define IMU_I2C_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define IMU_I2C_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define IMU_I2C_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << IMU_I2C_SCBCLK_CMD_DISABLE_SHIFT))
#define IMU_I2C_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << IMU_I2C_SCBCLK_CMD_ENABLE_SHIFT))

#define IMU_I2C_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define IMU_I2C_SCBCLK_DIV_FRAC_SHIFT (3u)
#define IMU_I2C_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define IMU_I2C_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define IMU_I2C_SCBCLK_DIV_REG        (*(reg32 *)IMU_I2C_SCBCLK__REGISTER)
#define IMU_I2C_SCBCLK_ENABLE_REG     IMU_I2C_SCBCLK_DIV_REG
#define IMU_I2C_SCBCLK_DIV_FRAC_MASK  IMU_I2C_SCBCLK__FRAC_MASK
#define IMU_I2C_SCBCLK_DIV_FRAC_SHIFT (16u)
#define IMU_I2C_SCBCLK_DIV_INT_MASK   IMU_I2C_SCBCLK__DIVIDER_MASK
#define IMU_I2C_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_IMU_I2C_SCBCLK_H) */

/* [] END OF FILE */
