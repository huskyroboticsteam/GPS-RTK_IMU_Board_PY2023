/*******************************************************************************
* File Name: PIN_OUTPUT_TRANSPARENT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PIN_OUTPUT_TRANSPARENT_H) /* Pins PIN_OUTPUT_TRANSPARENT_H */
#define CY_PINS_PIN_OUTPUT_TRANSPARENT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN_OUTPUT_TRANSPARENT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PIN_OUTPUT_TRANSPARENT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PIN_OUTPUT_TRANSPARENT_Read(void);
void    PIN_OUTPUT_TRANSPARENT_Write(uint8 value);
uint8   PIN_OUTPUT_TRANSPARENT_ReadDataReg(void);
#if defined(PIN_OUTPUT_TRANSPARENT__PC) || (CY_PSOC4_4200L) 
    void    PIN_OUTPUT_TRANSPARENT_SetDriveMode(uint8 mode);
#endif
void    PIN_OUTPUT_TRANSPARENT_SetInterruptMode(uint16 position, uint16 mode);
uint8   PIN_OUTPUT_TRANSPARENT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PIN_OUTPUT_TRANSPARENT_Sleep(void); 
void PIN_OUTPUT_TRANSPARENT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PIN_OUTPUT_TRANSPARENT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PIN_OUTPUT_TRANSPARENT_DRIVE_MODE_BITS        (3)
    #define PIN_OUTPUT_TRANSPARENT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN_OUTPUT_TRANSPARENT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PIN_OUTPUT_TRANSPARENT_SetDriveMode() function.
         *  @{
         */
        #define PIN_OUTPUT_TRANSPARENT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PIN_OUTPUT_TRANSPARENT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PIN_OUTPUT_TRANSPARENT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PIN_OUTPUT_TRANSPARENT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PIN_OUTPUT_TRANSPARENT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PIN_OUTPUT_TRANSPARENT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PIN_OUTPUT_TRANSPARENT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PIN_OUTPUT_TRANSPARENT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PIN_OUTPUT_TRANSPARENT_MASK               PIN_OUTPUT_TRANSPARENT__MASK
#define PIN_OUTPUT_TRANSPARENT_SHIFT              PIN_OUTPUT_TRANSPARENT__SHIFT
#define PIN_OUTPUT_TRANSPARENT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PIN_OUTPUT_TRANSPARENT_SetInterruptMode() function.
     *  @{
     */
        #define PIN_OUTPUT_TRANSPARENT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PIN_OUTPUT_TRANSPARENT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PIN_OUTPUT_TRANSPARENT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PIN_OUTPUT_TRANSPARENT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PIN_OUTPUT_TRANSPARENT__SIO)
    #define PIN_OUTPUT_TRANSPARENT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PIN_OUTPUT_TRANSPARENT__PC) && (CY_PSOC4_4200L)
    #define PIN_OUTPUT_TRANSPARENT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PIN_OUTPUT_TRANSPARENT_USBIO_DISABLE              ((uint32)(~PIN_OUTPUT_TRANSPARENT_USBIO_ENABLE))
    #define PIN_OUTPUT_TRANSPARENT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PIN_OUTPUT_TRANSPARENT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PIN_OUTPUT_TRANSPARENT_USBIO_ENTER_SLEEP          ((uint32)((1u << PIN_OUTPUT_TRANSPARENT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PIN_OUTPUT_TRANSPARENT_USBIO_SUSPEND_DEL_SHIFT)))
    #define PIN_OUTPUT_TRANSPARENT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PIN_OUTPUT_TRANSPARENT_USBIO_SUSPEND_SHIFT)))
    #define PIN_OUTPUT_TRANSPARENT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PIN_OUTPUT_TRANSPARENT_USBIO_SUSPEND_DEL_SHIFT)))
    #define PIN_OUTPUT_TRANSPARENT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PIN_OUTPUT_TRANSPARENT__PC)
    /* Port Configuration */
    #define PIN_OUTPUT_TRANSPARENT_PC                 (* (reg32 *) PIN_OUTPUT_TRANSPARENT__PC)
#endif
/* Pin State */
#define PIN_OUTPUT_TRANSPARENT_PS                     (* (reg32 *) PIN_OUTPUT_TRANSPARENT__PS)
/* Data Register */
#define PIN_OUTPUT_TRANSPARENT_DR                     (* (reg32 *) PIN_OUTPUT_TRANSPARENT__DR)
/* Input Buffer Disable Override */
#define PIN_OUTPUT_TRANSPARENT_INP_DIS                (* (reg32 *) PIN_OUTPUT_TRANSPARENT__PC2)

/* Interrupt configuration Registers */
#define PIN_OUTPUT_TRANSPARENT_INTCFG                 (* (reg32 *) PIN_OUTPUT_TRANSPARENT__INTCFG)
#define PIN_OUTPUT_TRANSPARENT_INTSTAT                (* (reg32 *) PIN_OUTPUT_TRANSPARENT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PIN_OUTPUT_TRANSPARENT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PIN_OUTPUT_TRANSPARENT__SIO)
    #define PIN_OUTPUT_TRANSPARENT_SIO_REG            (* (reg32 *) PIN_OUTPUT_TRANSPARENT__SIO)
#endif /* (PIN_OUTPUT_TRANSPARENT__SIO_CFG) */

/* USBIO registers */
#if !defined(PIN_OUTPUT_TRANSPARENT__PC) && (CY_PSOC4_4200L)
    #define PIN_OUTPUT_TRANSPARENT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PIN_OUTPUT_TRANSPARENT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PIN_OUTPUT_TRANSPARENT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PIN_OUTPUT_TRANSPARENT_DRIVE_MODE_SHIFT       (0x00u)
#define PIN_OUTPUT_TRANSPARENT_DRIVE_MODE_MASK        (0x07u << PIN_OUTPUT_TRANSPARENT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PIN_OUTPUT_TRANSPARENT_H */


/* [] END OF FILE */
