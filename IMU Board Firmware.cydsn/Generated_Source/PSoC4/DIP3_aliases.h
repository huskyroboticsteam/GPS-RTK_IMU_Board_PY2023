/*******************************************************************************
* File Name: DIP3.h  
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

#if !defined(CY_PINS_DIP3_ALIASES_H) /* Pins DIP3_ALIASES_H */
#define CY_PINS_DIP3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DIP3_0			(DIP3__0__PC)
#define DIP3_0_PS		(DIP3__0__PS)
#define DIP3_0_PC		(DIP3__0__PC)
#define DIP3_0_DR		(DIP3__0__DR)
#define DIP3_0_SHIFT	(DIP3__0__SHIFT)
#define DIP3_0_INTR	((uint16)((uint16)0x0003u << (DIP3__0__SHIFT*2u)))

#define DIP3_INTR_ALL	 ((uint16)(DIP3_0_INTR))


#endif /* End Pins DIP3_ALIASES_H */


/* [] END OF FILE */
