/*******************************************************************************
* File Name: DBG.h  
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

#if !defined(CY_PINS_DBG_ALIASES_H) /* Pins DBG_ALIASES_H */
#define CY_PINS_DBG_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DBG_0			(DBG__0__PC)
#define DBG_0_PS		(DBG__0__PS)
#define DBG_0_PC		(DBG__0__PC)
#define DBG_0_DR		(DBG__0__DR)
#define DBG_0_SHIFT	(DBG__0__SHIFT)
#define DBG_0_INTR	((uint16)((uint16)0x0003u << (DBG__0__SHIFT*2u)))

#define DBG_INTR_ALL	 ((uint16)(DBG_0_INTR))


#endif /* End Pins DBG_ALIASES_H */


/* [] END OF FILE */
