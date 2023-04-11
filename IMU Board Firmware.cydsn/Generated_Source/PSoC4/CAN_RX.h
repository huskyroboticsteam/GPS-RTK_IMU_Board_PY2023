/*******************************************************************************
* File Name: CAN_RX.h  
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

#if !defined(CY_PINS_CAN_RX_H) /* Pins CAN_RX_H */
#define CY_PINS_CAN_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CAN_RX_aliases.h"


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
} CAN_RX_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CAN_RX_Read(void);
void    CAN_RX_Write(uint8 value);
uint8   CAN_RX_ReadDataReg(void);
#if defined(CAN_RX__PC) || (CY_PSOC4_4200L) 
    void    CAN_RX_SetDriveMode(uint8 mode);
#endif
void    CAN_RX_SetInterruptMode(uint16 position, uint16 mode);
uint8   CAN_RX_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CAN_RX_Sleep(void); 
void CAN_RX_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CAN_RX__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CAN_RX_DRIVE_MODE_BITS        (3)
    #define CAN_RX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CAN_RX_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CAN_RX_SetDriveMode() function.
         *  @{
         */
        #define CAN_RX_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CAN_RX_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CAN_RX_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CAN_RX_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CAN_RX_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CAN_RX_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CAN_RX_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CAN_RX_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CAN_RX_MASK               CAN_RX__MASK
#define CAN_RX_SHIFT              CAN_RX__SHIFT
#define CAN_RX_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CAN_RX_SetInterruptMode() function.
     *  @{
     */
        #define CAN_RX_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CAN_RX_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CAN_RX_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CAN_RX_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CAN_RX__SIO)
    #define CAN_RX_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CAN_RX__PC) && (CY_PSOC4_4200L)
    #define CAN_RX_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CAN_RX_USBIO_DISABLE              ((uint32)(~CAN_RX_USBIO_ENABLE))
    #define CAN_RX_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CAN_RX_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CAN_RX_USBIO_ENTER_SLEEP          ((uint32)((1u << CAN_RX_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CAN_RX_USBIO_SUSPEND_DEL_SHIFT)))
    #define CAN_RX_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CAN_RX_USBIO_SUSPEND_SHIFT)))
    #define CAN_RX_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CAN_RX_USBIO_SUSPEND_DEL_SHIFT)))
    #define CAN_RX_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CAN_RX__PC)
    /* Port Configuration */
    #define CAN_RX_PC                 (* (reg32 *) CAN_RX__PC)
#endif
/* Pin State */
#define CAN_RX_PS                     (* (reg32 *) CAN_RX__PS)
/* Data Register */
#define CAN_RX_DR                     (* (reg32 *) CAN_RX__DR)
/* Input Buffer Disable Override */
#define CAN_RX_INP_DIS                (* (reg32 *) CAN_RX__PC2)

/* Interrupt configuration Registers */
#define CAN_RX_INTCFG                 (* (reg32 *) CAN_RX__INTCFG)
#define CAN_RX_INTSTAT                (* (reg32 *) CAN_RX__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CAN_RX_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CAN_RX__SIO)
    #define CAN_RX_SIO_REG            (* (reg32 *) CAN_RX__SIO)
#endif /* (CAN_RX__SIO_CFG) */

/* USBIO registers */
#if !defined(CAN_RX__PC) && (CY_PSOC4_4200L)
    #define CAN_RX_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CAN_RX_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CAN_RX_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CAN_RX_DRIVE_MODE_SHIFT       (0x00u)
#define CAN_RX_DRIVE_MODE_MASK        (0x07u << CAN_RX_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CAN_RX_H */


/* [] END OF FILE */
