/*******************************************************************************
* File Name: qa1.h  
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

#if !defined(CY_PINS_qa1_H) /* Pins qa1_H */
#define CY_PINS_qa1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "qa1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 qa1__PORT == 15 && ((qa1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    qa1_Write(uint8 value);
void    qa1_SetDriveMode(uint8 mode);
uint8   qa1_ReadDataReg(void);
uint8   qa1_Read(void);
void    qa1_SetInterruptMode(uint16 position, uint16 mode);
uint8   qa1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the qa1_SetDriveMode() function.
     *  @{
     */
        #define qa1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define qa1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define qa1_DM_RES_UP          PIN_DM_RES_UP
        #define qa1_DM_RES_DWN         PIN_DM_RES_DWN
        #define qa1_DM_OD_LO           PIN_DM_OD_LO
        #define qa1_DM_OD_HI           PIN_DM_OD_HI
        #define qa1_DM_STRONG          PIN_DM_STRONG
        #define qa1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define qa1_MASK               qa1__MASK
#define qa1_SHIFT              qa1__SHIFT
#define qa1_WIDTH              1u

/* Interrupt constants */
#if defined(qa1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qa1_SetInterruptMode() function.
     *  @{
     */
        #define qa1_INTR_NONE      (uint16)(0x0000u)
        #define qa1_INTR_RISING    (uint16)(0x0001u)
        #define qa1_INTR_FALLING   (uint16)(0x0002u)
        #define qa1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define qa1_INTR_MASK      (0x01u) 
#endif /* (qa1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qa1_PS                     (* (reg8 *) qa1__PS)
/* Data Register */
#define qa1_DR                     (* (reg8 *) qa1__DR)
/* Port Number */
#define qa1_PRT_NUM                (* (reg8 *) qa1__PRT) 
/* Connect to Analog Globals */                                                  
#define qa1_AG                     (* (reg8 *) qa1__AG)                       
/* Analog MUX bux enable */
#define qa1_AMUX                   (* (reg8 *) qa1__AMUX) 
/* Bidirectional Enable */                                                        
#define qa1_BIE                    (* (reg8 *) qa1__BIE)
/* Bit-mask for Aliased Register Access */
#define qa1_BIT_MASK               (* (reg8 *) qa1__BIT_MASK)
/* Bypass Enable */
#define qa1_BYP                    (* (reg8 *) qa1__BYP)
/* Port wide control signals */                                                   
#define qa1_CTL                    (* (reg8 *) qa1__CTL)
/* Drive Modes */
#define qa1_DM0                    (* (reg8 *) qa1__DM0) 
#define qa1_DM1                    (* (reg8 *) qa1__DM1)
#define qa1_DM2                    (* (reg8 *) qa1__DM2) 
/* Input Buffer Disable Override */
#define qa1_INP_DIS                (* (reg8 *) qa1__INP_DIS)
/* LCD Common or Segment Drive */
#define qa1_LCD_COM_SEG            (* (reg8 *) qa1__LCD_COM_SEG)
/* Enable Segment LCD */
#define qa1_LCD_EN                 (* (reg8 *) qa1__LCD_EN)
/* Slew Rate Control */
#define qa1_SLW                    (* (reg8 *) qa1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define qa1_PRTDSI__CAPS_SEL       (* (reg8 *) qa1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define qa1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) qa1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define qa1_PRTDSI__OE_SEL0        (* (reg8 *) qa1__PRTDSI__OE_SEL0) 
#define qa1_PRTDSI__OE_SEL1        (* (reg8 *) qa1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define qa1_PRTDSI__OUT_SEL0       (* (reg8 *) qa1__PRTDSI__OUT_SEL0) 
#define qa1_PRTDSI__OUT_SEL1       (* (reg8 *) qa1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define qa1_PRTDSI__SYNC_OUT       (* (reg8 *) qa1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(qa1__SIO_CFG)
    #define qa1_SIO_HYST_EN        (* (reg8 *) qa1__SIO_HYST_EN)
    #define qa1_SIO_REG_HIFREQ     (* (reg8 *) qa1__SIO_REG_HIFREQ)
    #define qa1_SIO_CFG            (* (reg8 *) qa1__SIO_CFG)
    #define qa1_SIO_DIFF           (* (reg8 *) qa1__SIO_DIFF)
#endif /* (qa1__SIO_CFG) */

/* Interrupt Registers */
#if defined(qa1__INTSTAT)
    #define qa1_INTSTAT            (* (reg8 *) qa1__INTSTAT)
    #define qa1_SNAP               (* (reg8 *) qa1__SNAP)
    
	#define qa1_0_INTTYPE_REG 		(* (reg8 *) qa1__0__INTTYPE)
#endif /* (qa1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_qa1_H */


/* [] END OF FILE */
