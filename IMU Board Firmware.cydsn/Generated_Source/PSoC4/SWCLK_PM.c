/*******************************************************************************
* File Name: SWCLK.c  
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
#include "SWCLK.h"

static SWCLK_BACKUP_STRUCT  SWCLK_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SWCLK_Sleep
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
*  \snippet SWCLK_SUT.c usage_SWCLK_Sleep_Wakeup
*******************************************************************************/
void SWCLK_Sleep(void)
{
    #if defined(SWCLK__PC)
        SWCLK_backup.pcState = SWCLK_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SWCLK_backup.usbState = SWCLK_CR1_REG;
            SWCLK_USB_POWER_REG |= SWCLK_USBIO_ENTER_SLEEP;
            SWCLK_CR1_REG &= SWCLK_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWCLK__SIO)
        SWCLK_backup.sioState = SWCLK_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SWCLK_SIO_REG &= (uint32)(~SWCLK_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SWCLK_Wakeup
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
*  Refer to SWCLK_Sleep() for an example usage.
*******************************************************************************/
void SWCLK_Wakeup(void)
{
    #if defined(SWCLK__PC)
        SWCLK_PC = SWCLK_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SWCLK_USB_POWER_REG &= SWCLK_USBIO_EXIT_SLEEP_PH1;
            SWCLK_CR1_REG = SWCLK_backup.usbState;
            SWCLK_USB_POWER_REG &= SWCLK_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SWCLK__SIO)
        SWCLK_SIO_REG = SWCLK_backup.sioState;
    #endif
}


/* [] END OF FILE */
