/*******************************************************************************
* File Name: RXD.h  
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

#if !defined(CY_PINS_RXD_ALIASES_H) /* Pins RXD_ALIASES_H */
#define CY_PINS_RXD_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define RXD_0			(RXD__0__PC)
#define RXD_0_PS		(RXD__0__PS)
#define RXD_0_PC		(RXD__0__PC)
#define RXD_0_DR		(RXD__0__DR)
#define RXD_0_SHIFT	(RXD__0__SHIFT)
#define RXD_0_INTR	((uint16)((uint16)0x0003u << (RXD__0__SHIFT*2u)))

#define RXD_INTR_ALL	 ((uint16)(RXD_0_INTR))


#endif /* End Pins RXD_ALIASES_H */


/* [] END OF FILE */
