/*******************************************************************************
* File Name: BAT_STAT.h  
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

#if !defined(CY_PINS_BAT_STAT_H) /* Pins BAT_STAT_H */
#define CY_PINS_BAT_STAT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BAT_STAT_aliases.h"


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
} BAT_STAT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BAT_STAT_Read(void);
void    BAT_STAT_Write(uint8 value);
uint8   BAT_STAT_ReadDataReg(void);
#if defined(BAT_STAT__PC) || (CY_PSOC4_4200L) 
    void    BAT_STAT_SetDriveMode(uint8 mode);
#endif
void    BAT_STAT_SetInterruptMode(uint16 position, uint16 mode);
uint8   BAT_STAT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BAT_STAT_Sleep(void); 
void BAT_STAT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BAT_STAT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BAT_STAT_DRIVE_MODE_BITS        (3)
    #define BAT_STAT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BAT_STAT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BAT_STAT_SetDriveMode() function.
         *  @{
         */
        #define BAT_STAT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BAT_STAT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BAT_STAT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BAT_STAT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BAT_STAT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BAT_STAT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BAT_STAT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BAT_STAT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BAT_STAT_MASK               BAT_STAT__MASK
#define BAT_STAT_SHIFT              BAT_STAT__SHIFT
#define BAT_STAT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BAT_STAT_SetInterruptMode() function.
     *  @{
     */
        #define BAT_STAT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BAT_STAT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BAT_STAT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BAT_STAT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BAT_STAT__SIO)
    #define BAT_STAT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BAT_STAT__PC) && (CY_PSOC4_4200L)
    #define BAT_STAT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BAT_STAT_USBIO_DISABLE              ((uint32)(~BAT_STAT_USBIO_ENABLE))
    #define BAT_STAT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BAT_STAT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BAT_STAT_USBIO_ENTER_SLEEP          ((uint32)((1u << BAT_STAT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BAT_STAT_USBIO_SUSPEND_DEL_SHIFT)))
    #define BAT_STAT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BAT_STAT_USBIO_SUSPEND_SHIFT)))
    #define BAT_STAT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BAT_STAT_USBIO_SUSPEND_DEL_SHIFT)))
    #define BAT_STAT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BAT_STAT__PC)
    /* Port Configuration */
    #define BAT_STAT_PC                 (* (reg32 *) BAT_STAT__PC)
#endif
/* Pin State */
#define BAT_STAT_PS                     (* (reg32 *) BAT_STAT__PS)
/* Data Register */
#define BAT_STAT_DR                     (* (reg32 *) BAT_STAT__DR)
/* Input Buffer Disable Override */
#define BAT_STAT_INP_DIS                (* (reg32 *) BAT_STAT__PC2)

/* Interrupt configuration Registers */
#define BAT_STAT_INTCFG                 (* (reg32 *) BAT_STAT__INTCFG)
#define BAT_STAT_INTSTAT                (* (reg32 *) BAT_STAT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BAT_STAT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BAT_STAT__SIO)
    #define BAT_STAT_SIO_REG            (* (reg32 *) BAT_STAT__SIO)
#endif /* (BAT_STAT__SIO_CFG) */

/* USBIO registers */
#if !defined(BAT_STAT__PC) && (CY_PSOC4_4200L)
    #define BAT_STAT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BAT_STAT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BAT_STAT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BAT_STAT_DRIVE_MODE_SHIFT       (0x00u)
#define BAT_STAT_DRIVE_MODE_MASK        (0x07u << BAT_STAT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BAT_STAT_H */


/* [] END OF FILE */
