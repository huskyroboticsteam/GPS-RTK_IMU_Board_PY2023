/*******************************************************************************
* File Name: SWDIO.h  
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

#if !defined(CY_PINS_SWDIO_ALIASES_H) /* Pins SWDIO_ALIASES_H */
#define CY_PINS_SWDIO_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWDIO_0			(SWDIO__0__PC)
#define SWDIO_0_PS		(SWDIO__0__PS)
#define SWDIO_0_PC		(SWDIO__0__PC)
#define SWDIO_0_DR		(SWDIO__0__DR)
#define SWDIO_0_SHIFT	(SWDIO__0__SHIFT)
#define SWDIO_0_INTR	((uint16)((uint16)0x0003u << (SWDIO__0__SHIFT*2u)))

#define SWDIO_INTR_ALL	 ((uint16)(SWDIO_0_INTR))


#endif /* End Pins SWDIO_ALIASES_H */


/* [] END OF FILE */
