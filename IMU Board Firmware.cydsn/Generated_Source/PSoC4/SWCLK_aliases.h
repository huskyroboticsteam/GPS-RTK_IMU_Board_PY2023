/*******************************************************************************
* File Name: SWCLK.h  
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

#if !defined(CY_PINS_SWCLK_ALIASES_H) /* Pins SWCLK_ALIASES_H */
#define CY_PINS_SWCLK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWCLK_0			(SWCLK__0__PC)
#define SWCLK_0_PS		(SWCLK__0__PS)
#define SWCLK_0_PC		(SWCLK__0__PC)
#define SWCLK_0_DR		(SWCLK__0__DR)
#define SWCLK_0_SHIFT	(SWCLK__0__SHIFT)
#define SWCLK_0_INTR	((uint16)((uint16)0x0003u << (SWCLK__0__SHIFT*2u)))

#define SWCLK_INTR_ALL	 ((uint16)(SWCLK_0_INTR))


#endif /* End Pins SWCLK_ALIASES_H */


/* [] END OF FILE */
