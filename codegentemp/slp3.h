/*******************************************************************************
* File Name: slp3.h  
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

#if !defined(CY_PINS_slp3_H) /* Pins slp3_H */
#define CY_PINS_slp3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slp3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slp3__PORT == 15 && ((slp3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slp3_Write(uint8 value);
void    slp3_SetDriveMode(uint8 mode);
uint8   slp3_ReadDataReg(void);
uint8   slp3_Read(void);
void    slp3_SetInterruptMode(uint16 position, uint16 mode);
uint8   slp3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slp3_SetDriveMode() function.
     *  @{
     */
        #define slp3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slp3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slp3_DM_RES_UP          PIN_DM_RES_UP
        #define slp3_DM_RES_DWN         PIN_DM_RES_DWN
        #define slp3_DM_OD_LO           PIN_DM_OD_LO
        #define slp3_DM_OD_HI           PIN_DM_OD_HI
        #define slp3_DM_STRONG          PIN_DM_STRONG
        #define slp3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slp3_MASK               slp3__MASK
#define slp3_SHIFT              slp3__SHIFT
#define slp3_WIDTH              1u

/* Interrupt constants */
#if defined(slp3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slp3_SetInterruptMode() function.
     *  @{
     */
        #define slp3_INTR_NONE      (uint16)(0x0000u)
        #define slp3_INTR_RISING    (uint16)(0x0001u)
        #define slp3_INTR_FALLING   (uint16)(0x0002u)
        #define slp3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slp3_INTR_MASK      (0x01u) 
#endif /* (slp3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slp3_PS                     (* (reg8 *) slp3__PS)
/* Data Register */
#define slp3_DR                     (* (reg8 *) slp3__DR)
/* Port Number */
#define slp3_PRT_NUM                (* (reg8 *) slp3__PRT) 
/* Connect to Analog Globals */                                                  
#define slp3_AG                     (* (reg8 *) slp3__AG)                       
/* Analog MUX bux enable */
#define slp3_AMUX                   (* (reg8 *) slp3__AMUX) 
/* Bidirectional Enable */                                                        
#define slp3_BIE                    (* (reg8 *) slp3__BIE)
/* Bit-mask for Aliased Register Access */
#define slp3_BIT_MASK               (* (reg8 *) slp3__BIT_MASK)
/* Bypass Enable */
#define slp3_BYP                    (* (reg8 *) slp3__BYP)
/* Port wide control signals */                                                   
#define slp3_CTL                    (* (reg8 *) slp3__CTL)
/* Drive Modes */
#define slp3_DM0                    (* (reg8 *) slp3__DM0) 
#define slp3_DM1                    (* (reg8 *) slp3__DM1)
#define slp3_DM2                    (* (reg8 *) slp3__DM2) 
/* Input Buffer Disable Override */
#define slp3_INP_DIS                (* (reg8 *) slp3__INP_DIS)
/* LCD Common or Segment Drive */
#define slp3_LCD_COM_SEG            (* (reg8 *) slp3__LCD_COM_SEG)
/* Enable Segment LCD */
#define slp3_LCD_EN                 (* (reg8 *) slp3__LCD_EN)
/* Slew Rate Control */
#define slp3_SLW                    (* (reg8 *) slp3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slp3_PRTDSI__CAPS_SEL       (* (reg8 *) slp3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slp3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slp3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slp3_PRTDSI__OE_SEL0        (* (reg8 *) slp3__PRTDSI__OE_SEL0) 
#define slp3_PRTDSI__OE_SEL1        (* (reg8 *) slp3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slp3_PRTDSI__OUT_SEL0       (* (reg8 *) slp3__PRTDSI__OUT_SEL0) 
#define slp3_PRTDSI__OUT_SEL1       (* (reg8 *) slp3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slp3_PRTDSI__SYNC_OUT       (* (reg8 *) slp3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slp3__SIO_CFG)
    #define slp3_SIO_HYST_EN        (* (reg8 *) slp3__SIO_HYST_EN)
    #define slp3_SIO_REG_HIFREQ     (* (reg8 *) slp3__SIO_REG_HIFREQ)
    #define slp3_SIO_CFG            (* (reg8 *) slp3__SIO_CFG)
    #define slp3_SIO_DIFF           (* (reg8 *) slp3__SIO_DIFF)
#endif /* (slp3__SIO_CFG) */

/* Interrupt Registers */
#if defined(slp3__INTSTAT)
    #define slp3_INTSTAT            (* (reg8 *) slp3__INTSTAT)
    #define slp3_SNAP               (* (reg8 *) slp3__SNAP)
    
	#define slp3_0_INTTYPE_REG 		(* (reg8 *) slp3__0__INTTYPE)
#endif /* (slp3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slp3_H */


/* [] END OF FILE */
