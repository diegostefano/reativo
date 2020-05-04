/*******************************************************************************
* File Name: slp2.h  
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

#if !defined(CY_PINS_slp2_H) /* Pins slp2_H */
#define CY_PINS_slp2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "slp2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 slp2__PORT == 15 && ((slp2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    slp2_Write(uint8 value);
void    slp2_SetDriveMode(uint8 mode);
uint8   slp2_ReadDataReg(void);
uint8   slp2_Read(void);
void    slp2_SetInterruptMode(uint16 position, uint16 mode);
uint8   slp2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the slp2_SetDriveMode() function.
     *  @{
     */
        #define slp2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define slp2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define slp2_DM_RES_UP          PIN_DM_RES_UP
        #define slp2_DM_RES_DWN         PIN_DM_RES_DWN
        #define slp2_DM_OD_LO           PIN_DM_OD_LO
        #define slp2_DM_OD_HI           PIN_DM_OD_HI
        #define slp2_DM_STRONG          PIN_DM_STRONG
        #define slp2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define slp2_MASK               slp2__MASK
#define slp2_SHIFT              slp2__SHIFT
#define slp2_WIDTH              1u

/* Interrupt constants */
#if defined(slp2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in slp2_SetInterruptMode() function.
     *  @{
     */
        #define slp2_INTR_NONE      (uint16)(0x0000u)
        #define slp2_INTR_RISING    (uint16)(0x0001u)
        #define slp2_INTR_FALLING   (uint16)(0x0002u)
        #define slp2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define slp2_INTR_MASK      (0x01u) 
#endif /* (slp2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define slp2_PS                     (* (reg8 *) slp2__PS)
/* Data Register */
#define slp2_DR                     (* (reg8 *) slp2__DR)
/* Port Number */
#define slp2_PRT_NUM                (* (reg8 *) slp2__PRT) 
/* Connect to Analog Globals */                                                  
#define slp2_AG                     (* (reg8 *) slp2__AG)                       
/* Analog MUX bux enable */
#define slp2_AMUX                   (* (reg8 *) slp2__AMUX) 
/* Bidirectional Enable */                                                        
#define slp2_BIE                    (* (reg8 *) slp2__BIE)
/* Bit-mask for Aliased Register Access */
#define slp2_BIT_MASK               (* (reg8 *) slp2__BIT_MASK)
/* Bypass Enable */
#define slp2_BYP                    (* (reg8 *) slp2__BYP)
/* Port wide control signals */                                                   
#define slp2_CTL                    (* (reg8 *) slp2__CTL)
/* Drive Modes */
#define slp2_DM0                    (* (reg8 *) slp2__DM0) 
#define slp2_DM1                    (* (reg8 *) slp2__DM1)
#define slp2_DM2                    (* (reg8 *) slp2__DM2) 
/* Input Buffer Disable Override */
#define slp2_INP_DIS                (* (reg8 *) slp2__INP_DIS)
/* LCD Common or Segment Drive */
#define slp2_LCD_COM_SEG            (* (reg8 *) slp2__LCD_COM_SEG)
/* Enable Segment LCD */
#define slp2_LCD_EN                 (* (reg8 *) slp2__LCD_EN)
/* Slew Rate Control */
#define slp2_SLW                    (* (reg8 *) slp2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define slp2_PRTDSI__CAPS_SEL       (* (reg8 *) slp2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define slp2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) slp2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define slp2_PRTDSI__OE_SEL0        (* (reg8 *) slp2__PRTDSI__OE_SEL0) 
#define slp2_PRTDSI__OE_SEL1        (* (reg8 *) slp2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define slp2_PRTDSI__OUT_SEL0       (* (reg8 *) slp2__PRTDSI__OUT_SEL0) 
#define slp2_PRTDSI__OUT_SEL1       (* (reg8 *) slp2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define slp2_PRTDSI__SYNC_OUT       (* (reg8 *) slp2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(slp2__SIO_CFG)
    #define slp2_SIO_HYST_EN        (* (reg8 *) slp2__SIO_HYST_EN)
    #define slp2_SIO_REG_HIFREQ     (* (reg8 *) slp2__SIO_REG_HIFREQ)
    #define slp2_SIO_CFG            (* (reg8 *) slp2__SIO_CFG)
    #define slp2_SIO_DIFF           (* (reg8 *) slp2__SIO_DIFF)
#endif /* (slp2__SIO_CFG) */

/* Interrupt Registers */
#if defined(slp2__INTSTAT)
    #define slp2_INTSTAT            (* (reg8 *) slp2__INTSTAT)
    #define slp2_SNAP               (* (reg8 *) slp2__SNAP)
    
	#define slp2_0_INTTYPE_REG 		(* (reg8 *) slp2__0__INTTYPE)
#endif /* (slp2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_slp2_H */


/* [] END OF FILE */
