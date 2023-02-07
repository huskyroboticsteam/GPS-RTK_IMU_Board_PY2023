/*******************************************************************************
* File Name: SWCLK.h  
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

#if !defined(CY_PINS_SWCLK_H) /* Pins SWCLK_H */
#define CY_PINS_SWCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWCLK_aliases.h"


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
} SWCLK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWCLK_Read(void);
void    SWCLK_Write(uint8 value);
uint8   SWCLK_ReadDataReg(void);
#if defined(SWCLK__PC) || (CY_PSOC4_4200L) 
    void    SWCLK_SetDriveMode(uint8 mode);
#endif
void    SWCLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWCLK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWCLK_Sleep(void); 
void SWCLK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWCLK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWCLK_DRIVE_MODE_BITS        (3)
    #define SWCLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWCLK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWCLK_SetDriveMode() function.
         *  @{
         */
        #define SWCLK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWCLK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWCLK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWCLK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWCLK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWCLK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWCLK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWCLK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWCLK_MASK               SWCLK__MASK
#define SWCLK_SHIFT              SWCLK__SHIFT
#define SWCLK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWCLK_SetInterruptMode() function.
     *  @{
     */
        #define SWCLK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWCLK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWCLK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWCLK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWCLK__SIO)
    #define SWCLK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWCLK__PC) && (CY_PSOC4_4200L)
    #define SWCLK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWCLK_USBIO_DISABLE              ((uint32)(~SWCLK_USBIO_ENABLE))
    #define SWCLK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWCLK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWCLK_USBIO_ENTER_SLEEP          ((uint32)((1u << SWCLK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWCLK_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWCLK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWCLK_USBIO_SUSPEND_SHIFT)))
    #define SWCLK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWCLK_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWCLK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWCLK__PC)
    /* Port Configuration */
    #define SWCLK_PC                 (* (reg32 *) SWCLK__PC)
#endif
/* Pin State */
#define SWCLK_PS                     (* (reg32 *) SWCLK__PS)
/* Data Register */
#define SWCLK_DR                     (* (reg32 *) SWCLK__DR)
/* Input Buffer Disable Override */
#define SWCLK_INP_DIS                (* (reg32 *) SWCLK__PC2)

/* Interrupt configuration Registers */
#define SWCLK_INTCFG                 (* (reg32 *) SWCLK__INTCFG)
#define SWCLK_INTSTAT                (* (reg32 *) SWCLK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWCLK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWCLK__SIO)
    #define SWCLK_SIO_REG            (* (reg32 *) SWCLK__SIO)
#endif /* (SWCLK__SIO_CFG) */

/* USBIO registers */
#if !defined(SWCLK__PC) && (CY_PSOC4_4200L)
    #define SWCLK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWCLK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWCLK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWCLK_DRIVE_MODE_SHIFT       (0x00u)
#define SWCLK_DRIVE_MODE_MASK        (0x07u << SWCLK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWCLK_H */


/* [] END OF FILE */
