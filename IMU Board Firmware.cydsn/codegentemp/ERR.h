/*******************************************************************************
* File Name: ERR.h  
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

#if !defined(CY_PINS_ERR_H) /* Pins ERR_H */
#define CY_PINS_ERR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ERR_aliases.h"


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
} ERR_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ERR_Read(void);
void    ERR_Write(uint8 value);
uint8   ERR_ReadDataReg(void);
#if defined(ERR__PC) || (CY_PSOC4_4200L) 
    void    ERR_SetDriveMode(uint8 mode);
#endif
void    ERR_SetInterruptMode(uint16 position, uint16 mode);
uint8   ERR_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ERR_Sleep(void); 
void ERR_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ERR__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ERR_DRIVE_MODE_BITS        (3)
    #define ERR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ERR_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ERR_SetDriveMode() function.
         *  @{
         */
        #define ERR_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ERR_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ERR_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ERR_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ERR_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ERR_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ERR_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ERR_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ERR_MASK               ERR__MASK
#define ERR_SHIFT              ERR__SHIFT
#define ERR_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ERR_SetInterruptMode() function.
     *  @{
     */
        #define ERR_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ERR_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ERR_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ERR_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ERR__SIO)
    #define ERR_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ERR__PC) && (CY_PSOC4_4200L)
    #define ERR_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ERR_USBIO_DISABLE              ((uint32)(~ERR_USBIO_ENABLE))
    #define ERR_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ERR_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ERR_USBIO_ENTER_SLEEP          ((uint32)((1u << ERR_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ERR_USBIO_SUSPEND_DEL_SHIFT)))
    #define ERR_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ERR_USBIO_SUSPEND_SHIFT)))
    #define ERR_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ERR_USBIO_SUSPEND_DEL_SHIFT)))
    #define ERR_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ERR__PC)
    /* Port Configuration */
    #define ERR_PC                 (* (reg32 *) ERR__PC)
#endif
/* Pin State */
#define ERR_PS                     (* (reg32 *) ERR__PS)
/* Data Register */
#define ERR_DR                     (* (reg32 *) ERR__DR)
/* Input Buffer Disable Override */
#define ERR_INP_DIS                (* (reg32 *) ERR__PC2)

/* Interrupt configuration Registers */
#define ERR_INTCFG                 (* (reg32 *) ERR__INTCFG)
#define ERR_INTSTAT                (* (reg32 *) ERR__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ERR_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ERR__SIO)
    #define ERR_SIO_REG            (* (reg32 *) ERR__SIO)
#endif /* (ERR__SIO_CFG) */

/* USBIO registers */
#if !defined(ERR__PC) && (CY_PSOC4_4200L)
    #define ERR_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ERR_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ERR_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ERR_DRIVE_MODE_SHIFT       (0x00u)
#define ERR_DRIVE_MODE_MASK        (0x07u << ERR_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ERR_H */


/* [] END OF FILE */
