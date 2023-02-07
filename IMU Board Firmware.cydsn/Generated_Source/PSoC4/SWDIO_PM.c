/*******************************************************************************
* File Name: SWDIO.c  
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
#include "SWDIO.h"

static SWDIO_BACKUP_STRUCT  SWDIO_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SWDIO_Sleep
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
*  \snippet SWDIO_SUT.c usage_SWDIO_Sleep_Wakeup
*******************************************************************************/
void SWDIO_Sleep(void)
{
    #if defined(SWDIO__PC)
        SWDIO_backup.pcState = SWDIO_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SWDIO_backup.usbState = SWDIO_CR1_REG;
            SWDIO_USB_POWER_REG |= SWDIO_USBIO_ENTER_SLEEP;
            SWDIO_CR1_REG &= SWDIO_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWDIO__SIO)
        SWDIO_backup.sioState = SWDIO_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SWDIO_SIO_REG &= (uint32)(~SWDIO_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SWDIO_Wakeup
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
*  Refer to SWDIO_Sleep() for an example usage.
*******************************************************************************/
void SWDIO_Wakeup(void)
{
    #if defined(SWDIO__PC)
        SWDIO_PC = SWDIO_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SWDIO_USB_POWER_REG &= SWDIO_USBIO_EXIT_SLEEP_PH1;
            SWDIO_CR1_REG = SWDIO_backup.usbState;
            SWDIO_USB_POWER_REG &= SWDIO_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWDIO__SIO)
        SWDIO_SIO_REG = SWDIO_backup.sioState;
    #endif
}


/* [] END OF FILE */
