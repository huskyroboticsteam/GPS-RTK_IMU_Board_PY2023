/*******************************************************************************
* File Name: TXD.h  
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

#if !defined(CY_PINS_TXD_ALIASES_H) /* Pins TXD_ALIASES_H */
#define CY_PINS_TXD_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define TXD_0			(TXD__0__PC)
#define TXD_0_PS		(TXD__0__PS)
#define TXD_0_PC		(TXD__0__PC)
#define TXD_0_DR		(TXD__0__DR)
#define TXD_0_SHIFT	(TXD__0__SHIFT)
#define TXD_0_INTR	((uint16)((uint16)0x0003u << (TXD__0__SHIFT*2u)))

#define TXD_INTR_ALL	 ((uint16)(TXD_0_INTR))


#endif /* End Pins TXD_ALIASES_H */


/* [] END OF FILE */
