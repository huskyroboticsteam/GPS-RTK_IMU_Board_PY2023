/*******************************************************************************
* File Name: IMU_RST.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IMU_RST_ALIASES_H) /* Pins IMU_RST_ALIASES_H */
#define CY_PINS_IMU_RST_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define IMU_RST_0			(IMU_RST__0__PC)
#define IMU_RST_0_PS		(IMU_RST__0__PS)
#define IMU_RST_0_PC		(IMU_RST__0__PC)
#define IMU_RST_0_DR		(IMU_RST__0__DR)
#define IMU_RST_0_SHIFT	(IMU_RST__0__SHIFT)
#define IMU_RST_0_INTR	((uint16)((uint16)0x0003u << (IMU_RST__0__SHIFT*2u)))

#define IMU_RST_INTR_ALL	 ((uint16)(IMU_RST_0_INTR))


#endif /* End Pins IMU_RST_ALIASES_H */


/* [] END OF FILE */
