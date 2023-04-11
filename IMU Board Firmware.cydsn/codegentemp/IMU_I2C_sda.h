/*******************************************************************************
* File Name: IMU_I2C_sda.h  
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

#if !defined(CY_PINS_IMU_I2C_sda_H) /* Pins IMU_I2C_sda_H */
#define CY_PINS_IMU_I2C_sda_H

#include "cytypes.h"
#include "cyfitter.h"
#include "IMU_I2C_sda_aliases.h"


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
} IMU_I2C_sda_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   IMU_I2C_sda_Read(void);
void    IMU_I2C_sda_Write(uint8 value);
uint8   IMU_I2C_sda_ReadDataReg(void);
#if defined(IMU_I2C_sda__PC) || (CY_PSOC4_4200L) 
    void    IMU_I2C_sda_SetDriveMode(uint8 mode);
#endif
void    IMU_I2C_sda_SetInterruptMode(uint16 position, uint16 mode);
uint8   IMU_I2C_sda_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void IMU_I2C_sda_Sleep(void); 
void IMU_I2C_sda_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(IMU_I2C_sda__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define IMU_I2C_sda_DRIVE_MODE_BITS        (3)
    #define IMU_I2C_sda_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - IMU_I2C_sda_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the IMU_I2C_sda_SetDriveMode() function.
         *  @{
         */
        #define IMU_I2C_sda_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define IMU_I2C_sda_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define IMU_I2C_sda_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define IMU_I2C_sda_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define IMU_I2C_sda_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define IMU_I2C_sda_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define IMU_I2C_sda_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define IMU_I2C_sda_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define IMU_I2C_sda_MASK               IMU_I2C_sda__MASK
#define IMU_I2C_sda_SHIFT              IMU_I2C_sda__SHIFT
#define IMU_I2C_sda_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in IMU_I2C_sda_SetInterruptMode() function.
     *  @{
     */
        #define IMU_I2C_sda_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define IMU_I2C_sda_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define IMU_I2C_sda_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define IMU_I2C_sda_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(IMU_I2C_sda__SIO)
    #define IMU_I2C_sda_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(IMU_I2C_sda__PC) && (CY_PSOC4_4200L)
    #define IMU_I2C_sda_USBIO_ENABLE               ((uint32)0x80000000u)
    #define IMU_I2C_sda_USBIO_DISABLE              ((uint32)(~IMU_I2C_sda_USBIO_ENABLE))
    #define IMU_I2C_sda_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define IMU_I2C_sda_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define IMU_I2C_sda_USBIO_ENTER_SLEEP          ((uint32)((1u << IMU_I2C_sda_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << IMU_I2C_sda_USBIO_SUSPEND_DEL_SHIFT)))
    #define IMU_I2C_sda_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << IMU_I2C_sda_USBIO_SUSPEND_SHIFT)))
    #define IMU_I2C_sda_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << IMU_I2C_sda_USBIO_SUSPEND_DEL_SHIFT)))
    #define IMU_I2C_sda_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(IMU_I2C_sda__PC)
    /* Port Configuration */
    #define IMU_I2C_sda_PC                 (* (reg32 *) IMU_I2C_sda__PC)
#endif
/* Pin State */
#define IMU_I2C_sda_PS                     (* (reg32 *) IMU_I2C_sda__PS)
/* Data Register */
#define IMU_I2C_sda_DR                     (* (reg32 *) IMU_I2C_sda__DR)
/* Input Buffer Disable Override */
#define IMU_I2C_sda_INP_DIS                (* (reg32 *) IMU_I2C_sda__PC2)

/* Interrupt configuration Registers */
#define IMU_I2C_sda_INTCFG                 (* (reg32 *) IMU_I2C_sda__INTCFG)
#define IMU_I2C_sda_INTSTAT                (* (reg32 *) IMU_I2C_sda__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define IMU_I2C_sda_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(IMU_I2C_sda__SIO)
    #define IMU_I2C_sda_SIO_REG            (* (reg32 *) IMU_I2C_sda__SIO)
#endif /* (IMU_I2C_sda__SIO_CFG) */

/* USBIO registers */
#if !defined(IMU_I2C_sda__PC) && (CY_PSOC4_4200L)
    #define IMU_I2C_sda_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define IMU_I2C_sda_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define IMU_I2C_sda_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define IMU_I2C_sda_DRIVE_MODE_SHIFT       (0x00u)
#define IMU_I2C_sda_DRIVE_MODE_MASK        (0x07u << IMU_I2C_sda_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins IMU_I2C_sda_H */


/* [] END OF FILE */
