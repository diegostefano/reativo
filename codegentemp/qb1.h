/*******************************************************************************
* File Name: qb1.h  
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

#if !defined(CY_PINS_qb1_H) /* Pins qb1_H */
#define CY_PINS_qb1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "qb1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 qb1__PORT == 15 && ((qb1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    qb1_Write(uint8 value);
void    qb1_SetDriveMode(uint8 mode);
uint8   qb1_ReadDataReg(void);
uint8   qb1_Read(void);
void    qb1_SetInterruptMode(uint16 position, uint16 mode);
uint8   qb1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the qb1_SetDriveMode() function.
     *  @{
     */
        #define qb1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define qb1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define qb1_DM_RES_UP          PIN_DM_RES_UP
        #define qb1_DM_RES_DWN         PIN_DM_RES_DWN
        #define qb1_DM_OD_LO           PIN_DM_OD_LO
        #define qb1_DM_OD_HI           PIN_DM_OD_HI
        #define qb1_DM_STRONG          PIN_DM_STRONG
        #define qb1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define qb1_MASK               qb1__MASK
#define qb1_SHIFT              qb1__SHIFT
#define qb1_WIDTH              1u

/* Interrupt constants */
#if defined(qb1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in qb1_SetInterruptMode() function.
     *  @{
     */
        #define qb1_INTR_NONE      (uint16)(0x0000u)
        #define qb1_INTR_RISING    (uint16)(0x0001u)
        #define qb1_INTR_FALLING   (uint16)(0x0002u)
        #define qb1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define qb1_INTR_MASK      (0x01u) 
#endif /* (qb1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define qb1_PS                     (* (reg8 *) qb1__PS)
/* Data Register */
#define qb1_DR                     (* (reg8 *) qb1__DR)
/* Port Number */
#define qb1_PRT_NUM                (* (reg8 *) qb1__PRT) 
/* Connect to Analog Globals */                                                  
#define qb1_AG                     (* (reg8 *) qb1__AG)                       
/* Analog MUX bux enable */
#define qb1_AMUX                   (* (reg8 *) qb1__AMUX) 
/* Bidirectional Enable */                                                        
#define qb1_BIE                    (* (reg8 *) qb1__BIE)
/* Bit-mask for Aliased Register Access */
#define qb1_BIT_MASK               (* (reg8 *) qb1__BIT_MASK)
/* Bypass Enable */
#define qb1_BYP                    (* (reg8 *) qb1__BYP)
/* Port wide control signals */                                                   
#define qb1_CTL                    (* (reg8 *) qb1__CTL)
/* Drive Modes */
#define qb1_DM0                    (* (reg8 *) qb1__DM0) 
#define qb1_DM1                    (* (reg8 *) qb1__DM1)
#define qb1_DM2                    (* (reg8 *) qb1__DM2) 
/* Input Buffer Disable Override */
#define qb1_INP_DIS                (* (reg8 *) qb1__INP_DIS)
/* LCD Common or Segment Drive */
#define qb1_LCD_COM_SEG            (* (reg8 *) qb1__LCD_COM_SEG)
/* Enable Segment LCD */
#define qb1_LCD_EN                 (* (reg8 *) qb1__LCD_EN)
/* Slew Rate Control */
#define qb1_SLW                    (* (reg8 *) qb1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define qb1_PRTDSI__CAPS_SEL       (* (reg8 *) qb1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define qb1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) qb1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define qb1_PRTDSI__OE_SEL0        (* (reg8 *) qb1__PRTDSI__OE_SEL0) 
#define qb1_PRTDSI__OE_SEL1        (* (reg8 *) qb1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define qb1_PRTDSI__OUT_SEL0       (* (reg8 *) qb1__PRTDSI__OUT_SEL0) 
#define qb1_PRTDSI__OUT_SEL1       (* (reg8 *) qb1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define qb1_PRTDSI__SYNC_OUT       (* (reg8 *) qb1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(qb1__SIO_CFG)
    #define qb1_SIO_HYST_EN        (* (reg8 *) qb1__SIO_HYST_EN)
    #define qb1_SIO_REG_HIFREQ     (* (reg8 *) qb1__SIO_REG_HIFREQ)
    #define qb1_SIO_CFG            (* (reg8 *) qb1__SIO_CFG)
    #define qb1_SIO_DIFF           (* (reg8 *) qb1__SIO_DIFF)
#endif /* (qb1__SIO_CFG) */

/* Interrupt Registers */
#if defined(qb1__INTSTAT)
    #define qb1_INTSTAT            (* (reg8 *) qb1__INTSTAT)
    #define qb1_SNAP               (* (reg8 *) qb1__SNAP)
    
	#define qb1_0_INTTYPE_REG 		(* (reg8 *) qb1__0__INTTYPE)
#endif /* (qb1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_qb1_H */


/* [] END OF FILE */
