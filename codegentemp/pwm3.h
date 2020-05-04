/*******************************************************************************
* File Name: pwm3.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pwm3_H) /* Pins pwm3_H */
#define CY_PINS_pwm3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pwm3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pwm3__PORT == 15 && ((pwm3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pwm3_Write(uint8 value);
void    pwm3_SetDriveMode(uint8 mode);
uint8   pwm3_ReadDataReg(void);
uint8   pwm3_Read(void);
void    pwm3_SetInterruptMode(uint16 position, uint16 mode);
uint8   pwm3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pwm3_SetDriveMode() function.
     *  @{
     */
        #define pwm3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pwm3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pwm3_DM_RES_UP          PIN_DM_RES_UP
        #define pwm3_DM_RES_DWN         PIN_DM_RES_DWN
        #define pwm3_DM_OD_LO           PIN_DM_OD_LO
        #define pwm3_DM_OD_HI           PIN_DM_OD_HI
        #define pwm3_DM_STRONG          PIN_DM_STRONG
        #define pwm3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pwm3_MASK               pwm3__MASK
#define pwm3_SHIFT              pwm3__SHIFT
#define pwm3_WIDTH              1u

/* Interrupt constants */
#if defined(pwm3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pwm3_SetInterruptMode() function.
     *  @{
     */
        #define pwm3_INTR_NONE      (uint16)(0x0000u)
        #define pwm3_INTR_RISING    (uint16)(0x0001u)
        #define pwm3_INTR_FALLING   (uint16)(0x0002u)
        #define pwm3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pwm3_INTR_MASK      (0x01u) 
#endif /* (pwm3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pwm3_PS                     (* (reg8 *) pwm3__PS)
/* Data Register */
#define pwm3_DR                     (* (reg8 *) pwm3__DR)
/* Port Number */
#define pwm3_PRT_NUM                (* (reg8 *) pwm3__PRT) 
/* Connect to Analog Globals */                                                  
#define pwm3_AG                     (* (reg8 *) pwm3__AG)                       
/* Analog MUX bux enable */
#define pwm3_AMUX                   (* (reg8 *) pwm3__AMUX) 
/* Bidirectional Enable */                                                        
#define pwm3_BIE                    (* (reg8 *) pwm3__BIE)
/* Bit-mask for Aliased Register Access */
#define pwm3_BIT_MASK               (* (reg8 *) pwm3__BIT_MASK)
/* Bypass Enable */
#define pwm3_BYP                    (* (reg8 *) pwm3__BYP)
/* Port wide control signals */                                                   
#define pwm3_CTL                    (* (reg8 *) pwm3__CTL)
/* Drive Modes */
#define pwm3_DM0                    (* (reg8 *) pwm3__DM0) 
#define pwm3_DM1                    (* (reg8 *) pwm3__DM1)
#define pwm3_DM2                    (* (reg8 *) pwm3__DM2) 
/* Input Buffer Disable Override */
#define pwm3_INP_DIS                (* (reg8 *) pwm3__INP_DIS)
/* LCD Common or Segment Drive */
#define pwm3_LCD_COM_SEG            (* (reg8 *) pwm3__LCD_COM_SEG)
/* Enable Segment LCD */
#define pwm3_LCD_EN                 (* (reg8 *) pwm3__LCD_EN)
/* Slew Rate Control */
#define pwm3_SLW                    (* (reg8 *) pwm3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pwm3_PRTDSI__CAPS_SEL       (* (reg8 *) pwm3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pwm3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pwm3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pwm3_PRTDSI__OE_SEL0        (* (reg8 *) pwm3__PRTDSI__OE_SEL0) 
#define pwm3_PRTDSI__OE_SEL1        (* (reg8 *) pwm3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pwm3_PRTDSI__OUT_SEL0       (* (reg8 *) pwm3__PRTDSI__OUT_SEL0) 
#define pwm3_PRTDSI__OUT_SEL1       (* (reg8 *) pwm3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pwm3_PRTDSI__SYNC_OUT       (* (reg8 *) pwm3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pwm3__SIO_CFG)
    #define pwm3_SIO_HYST_EN        (* (reg8 *) pwm3__SIO_HYST_EN)
    #define pwm3_SIO_REG_HIFREQ     (* (reg8 *) pwm3__SIO_REG_HIFREQ)
    #define pwm3_SIO_CFG            (* (reg8 *) pwm3__SIO_CFG)
    #define pwm3_SIO_DIFF           (* (reg8 *) pwm3__SIO_DIFF)
#endif /* (pwm3__SIO_CFG) */

/* Interrupt Registers */
#if defined(pwm3__INTSTAT)
    #define pwm3_INTSTAT            (* (reg8 *) pwm3__INTSTAT)
    #define pwm3_SNAP               (* (reg8 *) pwm3__SNAP)
    
	#define pwm3_0_INTTYPE_REG 		(* (reg8 *) pwm3__0__INTTYPE)
#endif /* (pwm3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pwm3_H */


/* [] END OF FILE */
