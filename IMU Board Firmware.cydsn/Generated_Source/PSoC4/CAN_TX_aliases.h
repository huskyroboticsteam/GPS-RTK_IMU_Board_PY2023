/*******************************************************************************
* File Name: CAN_TX.h  
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

#if !defined(CY_PINS_CAN_TX_ALIASES_H) /* Pins CAN_TX_ALIASES_H */
#define CY_PINS_CAN_TX_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CAN_TX_0			(CAN_TX__0__PC)
#define CAN_TX_0_PS		(CAN_TX__0__PS)
#define CAN_TX_0_PC		(CAN_TX__0__PC)
#define CAN_TX_0_DR		(CAN_TX__0__DR)
#define CAN_TX_0_SHIFT	(CAN_TX__0__SHIFT)
#define CAN_TX_0_INTR	((uint16)((uint16)0x0003u << (CAN_TX__0__SHIFT*2u)))

#define CAN_TX_INTR_ALL	 ((uint16)(CAN_TX_0_INTR))


#endif /* End Pins CAN_TX_ALIASES_H */


/* [] END OF FILE */
