/*******************************************************************************
* File Name: DBG.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "DBG.h"

static DBG_BACKUP_STRUCT  DBG_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DBG_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet DBG_SUT.c usage_DBG_Sleep_Wakeup
*******************************************************************************/
void DBG_Sleep(void)
{
    #if defined(DBG__PC)
        DBG_backup.pcState = DBG_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DBG_backup.usbState = DBG_CR1_REG;
            DBG_USB_POWER_REG |= DBG_USBIO_ENTER_SLEEP;
            DBG_CR1_REG &= DBG_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DBG__SIO)
        DBG_backup.sioState = DBG_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DBG_SIO_REG &= (uint32)(~DBG_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DBG_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to DBG_Sleep() for an example usage.
*******************************************************************************/
void DBG_Wakeup(void)
{
    #if defined(DBG__PC)
        DBG_PC = DBG_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DBG_USB_POWER_REG &= DBG_USBIO_EXIT_SLEEP_PH1;
            DBG_CR1_REG = DBG_backup.usbState;
            DBG_USB_POWER_REG &= DBG_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DBG__SIO)
        DBG_SIO_REG = DBG_backup.sioState;
    #endif
}


/* [] END OF FILE */
