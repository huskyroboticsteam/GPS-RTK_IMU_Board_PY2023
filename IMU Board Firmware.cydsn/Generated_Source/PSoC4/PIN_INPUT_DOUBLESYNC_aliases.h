/*******************************************************************************
* File Name: PIN_INPUT_DOUBLESYNC.h  
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

#if !defined(CY_PINS_PIN_INPUT_DOUBLESYNC_ALIASES_H) /* Pins PIN_INPUT_DOUBLESYNC_ALIASES_H */
#define CY_PINS_PIN_INPUT_DOUBLESYNC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PIN_INPUT_DOUBLESYNC_0			(PIN_INPUT_DOUBLESYNC__0__PC)
#define PIN_INPUT_DOUBLESYNC_0_PS		(PIN_INPUT_DOUBLESYNC__0__PS)
#define PIN_INPUT_DOUBLESYNC_0_PC		(PIN_INPUT_DOUBLESYNC__0__PC)
#define PIN_INPUT_DOUBLESYNC_0_DR		(PIN_INPUT_DOUBLESYNC__0__DR)
#define PIN_INPUT_DOUBLESYNC_0_SHIFT	(PIN_INPUT_DOUBLESYNC__0__SHIFT)
#define PIN_INPUT_DOUBLESYNC_0_INTR	((uint16)((uint16)0x0003u << (PIN_INPUT_DOUBLESYNC__0__SHIFT*2u)))

#define PIN_INPUT_DOUBLESYNC_INTR_ALL	 ((uint16)(PIN_INPUT_DOUBLESYNC_0_INTR))


#endif /* End Pins PIN_INPUT_DOUBLESYNC_ALIASES_H */


/* [] END OF FILE */
