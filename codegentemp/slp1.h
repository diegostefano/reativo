/*******************************************************************************
* File Name: slp1.h  
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

#if !defined(CY_PINS_slp1_H) /* Pins slp1_H */
#define CY_PINS_slp1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slp1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slp1__PORT == 15 && ((slp1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slp1_Write(uint8 value);
void    slp1_SetDriveMode(uint8 mode);
uint8   slp1_ReadDataReg(void);
uint8   slp1_Read(void);
void    slp1_SetInterruptMode(uint16 position, uint16 mode);
uint8   slp1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slp1_SetDriveMode() function.
     *  @{
     */
        #define slp1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slp1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slp1_DM_RES_UP          PIN_DM_RES_UP
        #define slp1_DM_RES_DWN         PIN_DM_RES_DWN
        #define slp1_DM_OD_LO           PIN_DM_OD_LO
        #define slp1_DM_OD_HI           PIN_DM_OD_HI
        #define slp1_DM_STRONG          PIN_DM_STRONG
        #define slp1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slp1_MASK               slp1__MASK
#define slp1_SHIFT              slp1__SHIFT
#define slp1_WIDTH              1u

/* Interrupt constants */
#if defined(slp1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slp1_SetInterruptMode() function.
     *  @{
     */
        #define slp1_INTR_NONE      (uint16)(0x0000u)
        #define slp1_INTR_RISING    (uint16)(0x0001u)
        #define slp1_INTR_FALLING   (uint16)(0x0002u)
        #define slp1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slp1_INTR_MASK      (0x01u) 
#endif /* (slp1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slp1_PS                     (* (reg8 *) slp1__PS)
/* Data Register */
#define slp1_DR                     (* (reg8 *) slp1__DR)
/* Port Number */
#define slp1_PRT_NUM                (* (reg8 *) slp1__PRT) 
/* Connect to Analog Globals */                                                  
#define slp1_AG                     (* (reg8 *) slp1__AG)                       
/* Analog MUX bux enable */
#define slp1_AMUX                   (* (reg8 *) slp1__AMUX) 
/* Bidirectional Enable */                                                        
#define slp1_BIE                    (* (reg8 *) slp1__BIE)
/* Bit-mask for Aliased Register Access */
#define slp1_BIT_MASK               (* (reg8 *) slp1__BIT_MASK)
/* Bypass Enable */
#define slp1_BYP                    (* (reg8 *) slp1__BYP)
/* Port wide control signals */                                                   
#define slp1_CTL                    (* (reg8 *) slp1__CTL)
/* Drive Modes */
#define slp1_DM0                    (* (reg8 *) slp1__DM0) 
#define slp1_DM1                    (* (reg8 *) slp1__DM1)
#define slp1_DM2                    (* (reg8 *) slp1__DM2) 
/* Input Buffer Disable Override */
#define slp1_INP_DIS                (* (reg8 *) slp1__INP_DIS)
/* LCD Common or Segment Drive */
#define slp1_LCD_COM_SEG            (* (reg8 *) slp1__LCD_COM_SEG)
/* Enable Segment LCD */
#define slp1_LCD_EN                 (* (reg8 *) slp1__LCD_EN)
/* Slew Rate Control */
#define slp1_SLW                    (* (reg8 *) slp1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slp1_PRTDSI__CAPS_SEL       (* (reg8 *) slp1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slp1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slp1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slp1_PRTDSI__OE_SEL0        (* (reg8 *) slp1__PRTDSI__OE_SEL0) 
#define slp1_PRTDSI__OE_SEL1        (* (reg8 *) slp1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slp1_PRTDSI__OUT_SEL0       (* (reg8 *) slp1__PRTDSI__OUT_SEL0) 
#define slp1_PRTDSI__OUT_SEL1       (* (reg8 *) slp1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slp1_PRTDSI__SYNC_OUT       (* (reg8 *) slp1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slp1__SIO_CFG)
    #define slp1_SIO_HYST_EN        (* (reg8 *) slp1__SIO_HYST_EN)
    #define slp1_SIO_REG_HIFREQ     (* (reg8 *) slp1__SIO_REG_HIFREQ)
    #define slp1_SIO_CFG            (* (reg8 *) slp1__SIO_CFG)
    #define slp1_SIO_DIFF           (* (reg8 *) slp1__SIO_DIFF)
#endif /* (slp1__SIO_CFG) */

/* Interrupt Registers */
#if defined(slp1__INTSTAT)
    #define slp1_INTSTAT            (* (reg8 *) slp1__INTSTAT)
    #define slp1_SNAP               (* (reg8 *) slp1__SNAP)
    
	#define slp1_0_INTTYPE_REG 		(* (reg8 *) slp1__0__INTTYPE)
#endif /* (slp1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slp1_H */


/* [] END OF FILE */
