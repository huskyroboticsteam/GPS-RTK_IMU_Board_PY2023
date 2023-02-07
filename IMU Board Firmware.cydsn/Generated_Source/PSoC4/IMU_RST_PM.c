/*******************************************************************************
* File Name: IMU_RST.c  
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
#include "IMU_RST.h"

static IMU_RST_BACKUP_STRUCT  IMU_RST_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: IMU_RST_Sleep
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
*  \snippet IMU_RST_SUT.c usage_IMU_RST_Sleep_Wakeup
*******************************************************************************/
void IMU_RST_Sleep(void)
{
    #if defined(IMU_RST__PC)
        IMU_RST_backup.pcState = IMU_RST_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            IMU_RST_backup.usbState = IMU_RST_CR1_REG;
            IMU_RST_USB_POWER_REG |= IMU_RST_USBIO_ENTER_SLEEP;
            IMU_RST_CR1_REG &= IMU_RST_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(IMU_RST__SIO)
        IMU_RST_backup.sioState = IMU_RST_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        IMU_RST_SIO_REG &= (uint32)(~IMU_RST_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: IMU_RST_Wakeup
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
*  Refer to IMU_RST_Sleep() for an example usage.
*******************************************************************************/
void IMU_RST_Wakeup(void)
{
    #if defined(IMU_RST__PC)
        IMU_RST_PC = IMU_RST_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            IMU_RST_USB_POWER_REG &= IMU_RST_USBIO_EXIT_SLEEP_PH1;
            IMU_RST_CR1_REG = IMU_RST_backup.usbState;
            IMU_RST_USB_POWER_REG &= IMU_RST_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(IMU_RST__SIO)
        IMU_RST_SIO_REG = IMU_RST_backup.sioState;
    #endif
}


/* [] END OF FILE */
