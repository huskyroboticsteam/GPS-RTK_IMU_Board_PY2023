/*******************************************************************************
* File Name: BAT_STAT.h  
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

#if !defined(CY_PINS_BAT_STAT_ALIASES_H) /* Pins BAT_STAT_ALIASES_H */
#define CY_PINS_BAT_STAT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BAT_STAT_0			(BAT_STAT__0__PC)
#define BAT_STAT_0_PS		(BAT_STAT__0__PS)
#define BAT_STAT_0_PC		(BAT_STAT__0__PC)
#define BAT_STAT_0_DR		(BAT_STAT__0__DR)
#define BAT_STAT_0_SHIFT	(BAT_STAT__0__SHIFT)
#define BAT_STAT_0_INTR	((uint16)((uint16)0x0003u << (BAT_STAT__0__SHIFT*2u)))

#define BAT_STAT_INTR_ALL	 ((uint16)(BAT_STAT_0_INTR))


#endif /* End Pins BAT_STAT_ALIASES_H */


/* [] END OF FILE */
