/*******************************************************************************
* File Name: qa2.h  
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

#if !defined(CY_PINS_qa2_H) /* Pins qa2_H */
#define CY_PINS_qa2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "qa2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 qa2__PORT == 15 && ((qa2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    qa2_Write(uint8 value);
void    qa2_SetDriveMode(uint8 mode);
uint8   qa2_ReadDataReg(void);
uint8   qa2_Read(void);
void    qa2_SetInterruptMode(uint16 position, uint16 mode);
uint8   qa2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the qa2_SetDriveMode() function.
     *  @{
     */
        #define qa2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define qa2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define qa2_DM_RES_UP          PIN_DM_RES_UP
        #define qa2_DM_RES_DWN         PIN_DM_RES_DWN
        #define qa2_DM_OD_LO           PIN_DM_OD_LO
        #define qa2_DM_OD_HI           PIN_DM_OD_HI
        #define qa2_DM_STRONG          PIN_DM_STRONG
        #define qa2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define qa2_MASK               qa2__MASK
#define qa2_SHIFT              qa2__SHIFT
#define qa2_WIDTH              1u

/* Interrupt constants */
#if defined(qa2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qa2_SetInterruptMode() function.
     *  @{
     */
        #define qa2_INTR_NONE      (uint16)(0x0000u)
        #define qa2_INTR_RISING    (uint16)(0x0001u)
        #define qa2_INTR_FALLING   (uint16)(0x0002u)
        #define qa2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define qa2_INTR_MASK      (0x01u) 
#endif /* (qa2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qa2_PS                     (* (reg8 *) qa2__PS)
/* Data Register */
#define qa2_DR                     (* (reg8 *) qa2__DR)
/* Port Number */
#define qa2_PRT_NUM                (* (reg8 *) qa2__PRT) 
/* Connect to Analog Globals */                                                  
#define qa2_AG                     (* (reg8 *) qa2__AG)                       
/* Analog MUX bux enable */
#define qa2_AMUX                   (* (reg8 *) qa2__AMUX) 
/* Bidirectional Enable */                                                        
#define qa2_BIE                    (* (reg8 *) qa2__BIE)
/* Bit-mask for Aliased Register Access */
#define qa2_BIT_MASK               (* (reg8 *) qa2__BIT_MASK)
/* Bypass Enable */
#define qa2_BYP                    (* (reg8 *) qa2__BYP)
/* Port wide control signals */                                                   
#define qa2_CTL                    (* (reg8 *) qa2__CTL)
/* Drive Modes */
#define qa2_DM0                    (* (reg8 *) qa2__DM0) 
#define qa2_DM1                    (* (reg8 *) qa2__DM1)
#define qa2_DM2                    (* (reg8 *) qa2__DM2) 
/* Input Buffer Disable Override */
#define qa2_INP_DIS                (* (reg8 *) qa2__INP_DIS)
/* LCD Common or Segment Drive */
#define qa2_LCD_COM_SEG            (* (reg8 *) qa2__LCD_COM_SEG)
/* Enable Segment LCD */
#define qa2_LCD_EN                 (* (reg8 *) qa2__LCD_EN)
/* Slew Rate Control */
#define qa2_SLW                    (* (reg8 *) qa2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define qa2_PRTDSI__CAPS_SEL       (* (reg8 *) qa2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define qa2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) qa2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define qa2_PRTDSI__OE_SEL0        (* (reg8 *) qa2__PRTDSI__OE_SEL0) 
#define qa2_PRTDSI__OE_SEL1        (* (reg8 *) qa2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define qa2_PRTDSI__OUT_SEL0       (* (reg8 *) qa2__PRTDSI__OUT_SEL0) 
#define qa2_PRTDSI__OUT_SEL1       (* (reg8 *) qa2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define qa2_PRTDSI__SYNC_OUT       (* (reg8 *) qa2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(qa2__SIO_CFG)
    #define qa2_SIO_HYST_EN        (* (reg8 *) qa2__SIO_HYST_EN)
    #define qa2_SIO_REG_HIFREQ     (* (reg8 *) qa2__SIO_REG_HIFREQ)
    #define qa2_SIO_CFG            (* (reg8 *) qa2__SIO_CFG)
    #define qa2_SIO_DIFF           (* (reg8 *) qa2__SIO_DIFF)
#endif /* (qa2__SIO_CFG) */

/* Interrupt Registers */
#if defined(qa2__INTSTAT)
    #define qa2_INTSTAT            (* (reg8 *) qa2__INTSTAT)
    #define qa2_SNAP               (* (reg8 *) qa2__SNAP)
    
	#define qa2_0_INTTYPE_REG 		(* (reg8 *) qa2__0__INTTYPE)
#endif /* (qa2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_qa2_H */


/* [] END OF FILE */
