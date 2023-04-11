/*******************************************************************************
* File Name: ERR.h  
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

#if !defined(CY_PINS_ERR_ALIASES_H) /* Pins ERR_ALIASES_H */
#define CY_PINS_ERR_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ERR_0			(ERR__0__PC)
#define ERR_0_PS		(ERR__0__PS)
#define ERR_0_PC		(ERR__0__PC)
#define ERR_0_DR		(ERR__0__DR)
#define ERR_0_SHIFT	(ERR__0__SHIFT)
#define ERR_0_INTR	((uint16)((uint16)0x0003u << (ERR__0__SHIFT*2u)))

#define ERR_INTR_ALL	 ((uint16)(ERR_0_INTR))


#endif /* End Pins ERR_ALIASES_H */


/* [] END OF FILE */
